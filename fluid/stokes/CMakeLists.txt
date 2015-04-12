###  CMakeLists.txt; coding: utf-8 --- 

#  Author(s): Christophe Prud'homme <christophe.prudhomme@feelpp.org>
#       Date: 06 Feb 2015
#
#  Copyright (C) 2015 Feel++ Consortium
#
# Distributed under the GPL(GNU Public License):
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#
#


feelpp_add_application( qs_stokes_2d SRCS qs_stokes.cpp INCLUDE_IN_ALL CFG qs_stokes.cfg DEFS FEELPP_DIM=2 FEELPP_ORDER=2 )
feelpp_add_application( qs_stokes_3d SRCS qs_stokes.cpp INCLUDE_IN_ALL CFG qs_stokes.cfg DEFS FEELPP_DIM=3 FEELPP_ORDER=2 )
install(TARGETS feelpp_qs_stokes_2d DESTINATION bin/ COMPONENT Bin )
install(TARGETS feelpp_qs_stokes_3d DESTINATION bin/ COMPONENT Bin )

add_dependencies(quickstart feelpp_qs_stokes_2d)
add_dependencies(quickstart feelpp_qs_stokes_3d)
