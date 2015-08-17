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
#include <feel/feel.hpp>
#include <feel/feelmodels/fluid/fluidmechanics.hpp>

int main(int argc, char**argv )
{
    //! [marker1]
    using namespace Feel;
	Environment env( _argc=argc, _argv=argv,
                     _desc=fluidMechanics_options("fm"),
                     _about=about(_name="qs_stokes",
                                  _author="Feel++ Consortium",
                                  _email="feelpp-devel@feelpp.org"));
    const int dim = FEELPP_DIM;
    const int pressure_order = FEELPP_ORDER;
    tic();
    auto mesh = loadMesh( _mesh=new Mesh<Simplex<dim>> );
    toc("FM/Mesh built");
    tic();
    // Taylar-Hood P_{N+1}/P_N, N=pressure_order
    auto Vh = THch<pressure_order>( mesh );
    toc("FM/Space built");

    tic();
    FluidMechanics<decltype(Vh)> fm( "fm", Vh );
    toc("FM/Stokes built");

    tic();
    fm.solve();
    toc("[FM/Stokes] solve");

    tic();
    fm.exportResults();
    toc("[FM/Stokes] export");
    
    return 0;
}
//! [main]
