/* -*- mode: c++; coding: utf-8; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4; show-trailing-whitespace: t  -*- vim:set fenc=utf-8:ft=tcl:et:sw=4:ts=4:sts=4

   This file is part of the Feel++ library

   Author(s): Christophe Prud'homme <christophe.prudhomme@feelpp.org>
Date     : Tue Feb 25 11:58:30 2014

Copyright (C) 2014 Feel++ Consortium

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
//! [global]
#include <feel/feel.hpp>
//! [include]
#include <feel/feelmodels/modelproperties.hpp>
//! [include]

int main(int argc, char**argv )
{
  //! [env]
  using namespace Feel;
  po::options_description laplacianoptions( "Laplacian options" );
  laplacianoptions.add_options()
    ("myModel", po::value< std::string >()-> default_value("model"), "Name of our model")
    ("myVerbose", po::value< bool >()-> default_value( true ), "Display information during execution")
    ;

  Environment env( _argc=argc, _argv=argv,
      _desc=laplacianoptions,
      _about=about(_name="aniso_laplacian",
        _author="Feel++ Consortium",
        _email="feelpp-devel@feelpp.org"));
  //! [env]

  //! [load_model]
  ModelProperties model(Environment::expand(soption("myModel")));
  //! [load_model]
  //! [get_bc]
  map_scalar_field<2> bc_u { model.boundaryConditions().getScalarFields<2>("velocity","dirichlet") };
  //! [get_bc]
  //! [get_mat]
  ModelMaterials materials = model.materials();
  //! [get_mat]

  if(boption("myVerbose") && Environment::isMasterRank() )
    std::cout << "Model " << Environment::expand( soption("myModel")) << " loaded." << std::endl;

  //! [rhs]
  auto f = expr( soption(_name="functions.f"), "f" );
  //! [rhs]

  //! [function_space]
  auto mesh = loadMesh(_mesh=new Mesh<Simplex<MODEL_DIM>>);
  auto Vh = Pch<2>( mesh );
  auto u = Vh->element();
  auto v = Vh->element();
  auto k11 = Vh->element();
  auto k12 = Vh->element();
  auto k22 = Vh->element();
#if MODEL_DIM == 3
  auto k13 = Vh->element();
  auto k23 = Vh->element();
  auto k33 = Vh->element();
#endif
  //! [function_space]
  
  //! [forms]
  auto a = form2( _trial=Vh, _test=Vh);
  auto l = form1( _test=Vh );
  //! [forms]

  //! [applying_rhs]
  l = integrate(_range=elements(mesh),_expr=f*id(v));
  //! [applying_rhs]

  //! [materials]
  for(auto it : materials)
  {
    if(boption("myVerbose") && Environment::isMasterRank() )
      std::cout << "[Materials] - Laoding data for " << it.name() << " with diffusion coef " << it.k11() << std::endl;
    k11 += vf::project(_range=markedelements(mesh,it.name()),_expr=it.k11());
    k12 += vf::project(_range=markedelements(mesh,it.name()),_expr=it.k12());
    k22 += vf::project(_range=markedelements(mesh,it.name()),_expr=it.k22());
#if MODEL_DIM == 3
    k13 += vf::project(_range=markedelements(mesh,it.name()),_expr=it.k13());
    k23 += vf::project(_range=markedelements(mesh,it.name()),_expr=it.k23());
    k33 += vf::project(_range=markedelements(mesh,it.name()),_expr=it.k33());
#endif
  }
#if MODEL_DIM == 2
    a += integrate(_range=elements(mesh),_expr=inner(mat<MODEL_DIM,MODEL_DIM>(idv(k11), idv(k12), idv(k12), idv(k22) )*trans(gradt(u)),trans(grad(v))) );
#else
    a += integrate(_range=elements(mesh),_expr=inner(mat<MODEL_DIM,MODEL_DIM>(idv(k11), idv(k12), idv(k13), idv(k12), idv(k22), idv(k23), idv(k31), idv(k32), idv(k33))*trans(gradt(u)),trans(grad(v))) );
#endif
  }
  //! [materials]
  
  //! [boundary]
  for(auto it : bc_u){
    if(boption("myVerbose") && Environment::isMasterRank() )
      std::cout << "[BC] - Applying " << it.second << " on " << it.first << std::endl;
    a+=on(_range=markedfaces(mesh,it.first), _rhs=l, _element=u, _expr=it.second );
  }
  //! [boundary]
  
  //! [solve]
  a.solve(_rhs=l,_solution=u);
  //! [solve]

  //! [export]
  auto e = exporter( _mesh=mesh );
  for(auto const &it : model.postProcess()["Force"] )
  {
    switch(it){
      case "diffused":
        e->add("diffused",u);
        break;
      case "k11":
        e->add("k_11",k_11);
        break;
      case "k12":
        e->add("k_12",k_12);
        break;
      case "k11":
        e->add("k_22",k_22);
        break;
#if MODEL_DIM == 3
      case "k13":
        e->add("k_13",k_13);
        break;
      case "k11":
        e->add("k_23",k_23);
        break;
      case "k33":
        e->add("k_33",k_33);
        break;
#endif
    }
  }
  e->save();
  //! [export]
  return 0;
}
//! [global]
