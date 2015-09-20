/* -*- mode: c++; coding: utf-8; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4; show-trailing-whitespace: t  -*- vim:set fenc=utf-8:ft=tcl:et:sw=4:ts=4:sts=4

   This file is part of the Feel++ library

   Author(s): Christophe Prud'homme <christophe.prudhomme@feelpp.org>
   Date     : Tue Feb 25 12:13:15 2014

   Copyright (C) 2014-2015 Feel++ Consortium

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
//! [main]
#include <feel/feelmodels/fluid/fluidmechanics.hpp>

int main(int argc, char**argv )
{
    //! [marker1]
    using namespace Feel;
	Environment env( _argc=argc, _argv=argv,
                     _desc=fluidMechanics_options("fm"),
                     _about=about(_name="qs_stokes",
                                  _author="Feel++ Consortium",
                                  _email="feelpp-devel@feelpp.org"),
                     _directory="." );

    const int dim = FEELPP_DIM;
    const int velocity_order = FEELPP_ORDER;
    const int pressure_order = FEELPP_ORDER-1;

    typedef FeelModels::FluidMechanics< Simplex<FEELPP_DIM,1>,
                                        Lagrange<velocity_order, Vectorial,Continuous,PointSetFekete>,
                                        Lagrange<pressure_order, Scalar,Continuous,PointSetFekete> > model_type;
    auto fm = model_type::New("fm");

    fm->init();
    fm->printAndSaveInfo();

    if ( fm->isStationary() )
    {
        fm->solve();
        fm->exportResults();
    }
    else
    {
        for ( ; !fm->timeStepBase()->isFinished(); fm->updateTimeStep() )
        {
            if (fm->worldComm().isMasterRank())
            {
                std::cout << "============================================================\n";
                std::cout << "time simulation: " << fm->time() << "s \n";
                std::cout << "============================================================\n";
            }

            fm->solve();
            fm->exportResults();
        }
    }

    return 0;
}
//! [main]
