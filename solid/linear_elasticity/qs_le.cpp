/* -*- mode: c++; coding: utf-8; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4; show-trailing-whitespace: t  -*-
 
 This file is part of the Feel++ library
 
 Author(s): Christophe Prud'homme <christophe.prudhomme@feelpp.org>
 Date: 20 Feb 2015
 
 Copyright (C) 2015 Feel++ Consortium
 
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
#include <feel/feel.hpp>
#include <feel/feelcore/units.hpp>

inline
Feel::po::options_description
makeOptions()
{
    Feel::po::options_description linearelasticityoptions( "Linearelasticity options" );
    linearelasticityoptions.add_options()
        ( "E", Feel::po::value<double>()->default_value( 1.4e6 ), "Young modulus" )
        ( "nu", Feel::po::value<double>()->default_value( 0.4 ), "Poisson coefficient" )
        ;
    return linearelasticityoptions;
}

int main( int argc, char** argv )
{
    using namespace Feel;
    Environment env( _argc=argc, _argv=argv,
                     _desc=makeOptions(),
                     _about=about(_name="qs_le",
                                  _author="Feel++ Consortium",
                                  _email="feelpp-devel@feelpp.org") );

    const int dim = FEELPP_DIM;
    const int order = FEELPP_ORDER;
    auto  mesh = loadMesh( _mesh = new Mesh<Simplex<dim>> );
    auto Xh = Pchv<order>( mesh );
    Xh->printInfo();

    auto u = Xh->element();
    auto v = Xh->element();

    auto E = doption(_name="E");
    const double nu = doption(_name="nu");

    auto mu = E/( 2*( 1+nu ) );
    auto lambda = E*nu/( ( 1+nu )*( 1-2*nu ) );
    if ( Environment::isMasterRank() )
        std::cout << "lambda = " << lambda << "\n"
                  << "mu     = " << mu << "\n";
    tic();
    auto force = expr<dim,1>( soption( "functions.f" ) );
    auto l = form1( _test=Xh );
    l = integrate( elements( mesh ), trans( force ) *id( v ) );
    toc("right hand side assembly");
    
    tic();
    auto deft = sym(gradt(u));
    auto def = sym(grad(u));
    auto a = form2( _test=Xh, _trial=Xh);
    a = integrate( _range=elements( mesh ),
                   _expr=lambda*divt( u )*div( v )  +
                   2.*mu*trace( trans( deft )*def ) );
    toc("volumic terms assembly");
    /*
     * retrieve vector fields from boundary condition factory
     */
    auto dirichlet_conditions = BoundaryConditionFactory::instance().getVectorFields<dim> ( "displacement", "Dirichlet" );
    auto neumann_conditions = BoundaryConditionFactory::instance().getVectorFields<dim> ( "displacement", "Neumann" );
    tic();
    for( auto const& n : neumann_conditions )
    {
        a += integrate( _range=markedfaces( mesh, marker(n) ),
                        _expr=trans(expression(n))*id(v) );
    }
    toc("neumann boundary condition terms assembly");
    tic();
    for( auto const& d : dirichlet_conditions )
    {
        a += on( _range=markedfaces( mesh, marker(d)), _element=u, _rhs=l, _expr=expression(d) );
    }
    toc("dirichlet boundary condition terms assembly");

    a.solve( _solution=u, _rhs=l );

    tic();
    auto e = exporter( _mesh=mesh );
    e->add( "displacement", u );
    e->save();
    toc("exporter");
} 


