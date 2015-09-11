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
#include <feel/feelmodels/solid/solidmechanics.hpp>

int
main( int argc, char** argv )
{

    using namespace Feel;
	Environment env( _argc=argc, _argv=argv,
                     _desc=solidMechanics_options("sm"),
                     _about=about(_name="qs_sm",
                                  _author="Feel++ Consortium",
                                  _email="feelpp-devel@feelpp.org"),
                     _directory="." );

    const int dim = FEELPP_DIM;
    const int order = FEELPP_ORDER;
    typedef Simplex<dim,1> convex_type;
    typedef Lagrange<order, Vectorial,Continuous,PointSetFekete> basis_disp_type;
    typedef FeelModels::SolidMechanics< convex_type,basis_disp_type> model_type;
    auto sm = model_type::New("sm");
    sm->init();
    sm->printAndSaveInfo();

    if ( sm->isStationary() )
    {
            if ( Environment::isMasterRank() )
            {
                std::cout << "============================================================\n";
                std::cout << "stationary solve\n";
            }
            sm->solve();
            sm->exportResults();
    }
    else
    {
        for ( ; !sm->timeStepBase()->isFinished(); sm->updateTimeStep() )
        {
            if ( Environment::isMasterRank() )
            {
                std::cout << "============================================================\n";
                std::cout << "time : " << sm->time() << "s\n";
            }
            sm->solve();
            sm->exportResults();
        }
    }
}
