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
#include <feel/feelmodels/solid/stvenantkirchhoff.hpp>
#include <feel/feel.hpp>

int
main( int argc, char** argv )
{

    using namespace Feel;
	Environment env( _argc=argc, _argv=argv,
                     _desc=stvenantkirchhoff_options("svk"),
                     _about=about(_name="qs_sk",
                                  _author="Feel++ Consortium",
                                  _email="feelpp-devel@feelpp.org"));
    
    const int dim = FEELPP_DIM;
    const int order = FEELPP_ORDER;
    auto  mesh = loadMesh( _mesh = new Mesh<Simplex<dim>> );
    auto Vh = Pchv<order>( mesh );
    Vh->printInfo();

    StVenantKirchhoff<decltype(Vh)> svk( "svk", Vh );
    svk.init();
    // get a reference to displacement computed by svk
    // it gets updated at each solve()
    auto const& u = svk.displacement();

    auto ts = svk.ts();
    for ( ; !ts->isFinished(); ts->next(u) )
    {
        if ( Environment::isMasterRank() )
        {
            std::cout << "============================================================\n";
            std::cout << "time : " << ts->time() << "s\n";
        }
        svk.solve();
        svk.exportResults();
    }
    

}
