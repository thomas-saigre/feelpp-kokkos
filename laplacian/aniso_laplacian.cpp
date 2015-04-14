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
    ("model", po::value< std::string >()-> default_value("model"), "Name of our model")
    ("verbose", po::value< bool >()-> default_value( true ), "Display information during execution")
    ;

  Environment env( _argc=argc, _argv=argv,
      _desc=laplacianoptions,
      _about=about(_name="qs_laplacian",
        _author="Feel++ Consortium",
        _email="feelpp-devel@feelpp.org"));
  //! [env]

  //! [load_model]
  ModelProperties model(soption("model"));
  //! [load_model]
  //! [get_bc]
  map_scalar_field<2> bc_u { model.boundaryConditions().getScalarFields<2>("velocity","dirichlet") };
  //! [get_bc]
  //! [get_mat]
  ModelMaterials materials; model.materials();
  //! [get_mat]
  if(boption("verbose") && Environment::isMasterRank() )
    std::cout << "Model " << soption("model") << " loaded." << std::endl;

  //! [rhs]
  auto f = expr( soption(_name="functions.f"), "f" );
  //! [rhs]

  //! [function_space]
  auto mesh = loadMesh(_mesh=new Mesh<Simplex<MODEL_DIM>>);
  auto Vh = Pch<2>( mesh );
  auto u = Vh->element();
  auto v = Vh->element();
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
    if(boption("verbose") && Environment::isMasterRank() )
      std::cout << "[Materials] - Laoding data for " << it.name() << " with diffusion coef " << it.k11() << std::endl;
    a = integrate(_range=markedelements(mesh,it.name()),_expr=it.k11()*inner(gradt(u),grad(v)) );
  }
  //! [materials]
  
  //! [boundary]
  for(auto it : bc_u){
    if(boption("verbose") && Environment::isMasterRank() )
      std::cout << "[BC] - Applying " << it.second << " on " << it.first << std::endl;
    a+=on(_range=markedfaces(mesh,it.first), _rhs=l, _element=u, _expr=it.second );
  }
  //! [boundary]
  
  //! [solve]
  a.solve(_rhs=l,_solution=u);
  //! [solve]

  //! [export]
  if(boption("exporter.export")){
  auto e = exporter( _mesh=mesh );
  e->addRegions();
  e->add( "u", u );
  e->add( "g", v );
  e->save();
  }
  //! [export]
  return 0;
}
//! [global]
