/* -*- mode: c++; coding: utf-8; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4; show-trailing-whitespace: t -*- vim:fenc=utf-8:ft=tcl:et:sw=4:ts=4:sts=4

  This file is part of the Feel library

  Author(s): Vincent Chabannes <vincent.chabannes@feelpp.org>
             Christophe Prud'homme <christophe.prudhomme@feelpp.org>
       Date: 2014-02-24

  Copyright (C) 2012-2015 Feel++ Consortium

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3.0 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include <feel/feel.hpp>

inline
Feel::po::options_description
makeOptions()
{
    Feel::po::options_description stvenantkirchhoffoptions( "StVenantKirchhoff problem options" );
    stvenantkirchhoffoptions.add_options()
    ( "young-modulus", Feel::po::value<double>()->default_value( 1.4e6 ), "young-modulus" )
    ( "poisson-coeff", Feel::po::value<double>()->default_value( 0.4 ), "poisson-coeff" )
    ( "rho", Feel::po::value<double>()->default_value( 1000 ), "density [kg/m^3]" )
    ( "gravity-cst", Feel::po::value<double>()->default_value( 2 ), "gravity-cst" )
    ;
    return stvenantkirchhoffoptions;
}

int
main( int argc, char** argv )
{

    using namespace Feel;
	Environment env( _argc=argc, _argv=argv,
                     _desc=makeOptions(),
                     _about=about(_name="qs_sk",
                                  _author="Feel++ Consortium",
                                  _email="feelpp-devel@feelpp.org"));

    double meshSize = option(_name="gmsh.hsize").as<double>();
    double youngmodulus=option(_name="young-modulus").as<double>();
    double coeffpoisson=option(_name="poisson-coeff").as<double>();
    double coefflame2 = youngmodulus/(2*(1+coeffpoisson));// mu
    double coefflame1 = youngmodulus*coeffpoisson/((1+coeffpoisson)*(1-2*coeffpoisson));// lambda
    double rho=option(_name="rho").as<double>();
    double gravityCst=option(_name="gravity-cst").as<double>();

    const int dim = FEELPP_DIM;
    const int order = FEELPP_ORDER;
    auto  mesh = loadMesh( _mesh = new Mesh<Simplex<dim>> );
    auto Vh = Pchv<order>( mesh );
    Vh->printInfo();
    auto u = Vh->element();
    auto v = Vh->element();

    auto Res = backend()->newVector( Vh );
    auto Jac = backend()->newMatrix( Vh, Vh );

    auto e = exporter( _mesh=mesh );

    auto ts = newmark( _space=Vh, _name="structure",_rank_proc_in_files_name=true );
    auto Id = eye<dim,dim>();
    auto gravityForce = -rho*gravityCst*oneY();

    auto dirichlet_conditions = BoundaryConditionFactory::instance().getVectorFields<dim> ( "displacement", "Dirichlet" );
    auto neumann_conditions = BoundaryConditionFactory::instance().getVectorFields<dim> ( "displacement", "Neumann" );
    
    // start or restart
    if ( !ts->isRestart() )
    {
      ts->start();
    }
    else
    {
        double ti = ts->restart();
        u = ts->previousUnknown();
        if ( e->doExport() ) e->restart(ti);
    }

    for ( ; !ts->isFinished(); ts->next(u) )
    {
        if ( Environment::isMasterRank() )
        {
            std::cout << "============================================================\n";
            std::cout << "time : " << ts->time() << "s\n";
        }

        auto Jacobian = [=](const vector_ptrtype& X, sparse_matrix_ptrtype& J)
            {
                auto u = Vh->element();
                u = *X;
                auto Fv = Id + gradv(u);
                auto Ev = sym(gradv(u)) + 0.5*trans(gradv(u))*gradv(u);
                auto Sv = coefflame1*trace(Ev)*Id + 2*coefflame2*Ev;
                auto dF = gradt(u);
                auto dE = sym(gradt(u)) + 0.5*(trans(gradv(u))*gradt(u) + trans(gradt(u))*gradv(u));
                auto dS = coefflame1*trace(dE)*Id + 2*coefflame2*dE;

                auto a = form2( _test=Vh, _trial=Vh, _matrix=J );

                a = integrate( _range=elements( mesh ),
                               _expr= inner( dF*val(Sv) + val(Fv)*dS , grad(v) ) );
                a += integrate( _range=elements( mesh ),
                                _expr= rho*inner( ts->polyDerivCoefficient()*idt(u),id( v ) ) );

                auto RR = backend()->newVector( Vh );
                for( auto const& d : dirichlet_conditions )
                {
                    a += on( _range=markedfaces( mesh, marker(d)), _element=u, _rhs=RR,
                             _expr=zero<dim,1>() );
                }
            };
        auto Residual = [&](const vector_ptrtype& X, vector_ptrtype& R)
            {
                auto u = Vh->element();
                u = *X;

                auto Fv = Id + gradv(u);
                auto Ev = sym(gradv(u)) + 0.5*trans(gradv(u))*gradv(u);
                auto Sv = coefflame1*trace(Ev)*Id + 2*coefflame2*Ev;

                auto r = form1( _test=Vh, _vector=R );
                r = integrate( _range=elements( mesh ),
                               _expr= inner( val(Fv*Sv) , grad(v) ) );
                r += integrate( _range=elements( mesh ),
                                _expr= -inner(gravityForce,id( v ) ) );
                r += integrate( _range=elements( mesh ),
                                _expr= rho*inner( ts->polyDerivCoefficient()*idv(u) -idv(ts->polyDeriv()),id( v ) ) );

                for( auto & n : neumann_conditions )
                {
                    // update n with respect to the current time in case it depends on time
                    expression(n).setParameterValues({{"t",ts->time()}});
                    r += integrate( _range=markedfaces( mesh, marker(n) ),
                                    _expr=trans(expression(n))*id(v) );
                }

                R->close();
                auto temp = Vh->element();
                temp = *R;
                for( auto const& d : dirichlet_conditions )
                {
                    temp.on( _range=markedfaces( mesh, marker(d)), _expr=zero<dim,1>() );
                }
                *R = temp;
            };
        
        // initial guess must satisfy the Dirichlet boundary conditions
        u.zero();
        for( auto const& d : dirichlet_conditions )
        {
            u.on( _range=markedfaces( mesh, marker(d)), _expr=expression(d));
        }
        
        backend()->nlSolver()->residual = Residual;
        backend()->nlSolver()->jacobian = Jacobian;
        backend()->nlSolve( _solution=u,_jacobian=Jac,_residual=Res );

        ts->updateFromDisp(u);
        e->step(ts->time())->add( "displacement", u );
        e->step(ts->time())->add( "velocity", ts->currentVelocity() );
        e->step(ts->time())->add( "acceleration", ts->currentAcceleration() );
        e->save();
    }


}
