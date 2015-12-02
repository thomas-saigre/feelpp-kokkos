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

# First look for the libraries to use
# Useful if quickstart is built on its own outside the build directory
if(TARGET feelpp_modelcore )
    set(MODELCORE_FOUND "YES")
else()
    find_library(MODELCORE_FOUND
        NAMES feelpp_modelcore 
        PATHS ${FEELPP_INSTALL_DIR}/lib
        )
endif()
if(TARGET feelpp_model_fluidmec2dP2P1G1)
    set(MODEL_FLUIDMEC2DP2P1G1_FOUND "YES")
else()
    find_library(MODEL_FLUIDMEC2DP2P1G1_FOUND
        NAMES feelpp_model_fluidmec2dP2P1G1 
        PATHS ${FEELPP_INSTALL_DIR}/lib
        )
endif()
if(TARGET feelpp_model_fluidmec3dP2P1G1)
    set(MODEL_FLUIDMEC3DP2P1G1_FOUND "YES")
else()
    find_library(MODEL_FLUIDMEC3DP2P1G1_FOUND
        NAMES feelpp_model_fluidmec3dP2P1G1
        PATHS ${FEELPP_INSTALL_DIR}/lib
        )
endif()

if(MODELCORE_FOUND AND MODEL_FLUIDMEC2DP2P1G1_FOUND)
    feelpp_add_application( qs_stokes_2d SRCS qs_stokes.cpp INCLUDE_IN_ALL DEFS FEELPP_DIM=2 FEELPP_ORDER=2 LINK_LIBRARIES feelpp_modelcore feelpp_model_fluidmec2dP2P1G1 )
    install(TARGETS feelpp_qs_stokes_2d
            RUNTIME DESTINATION bin/ 
            COMPONENT Quickstart)
    add_dependencies(quickstart feelpp_qs_stokes_2d)
else()
    message(STATUS "feelpp_qs_stokes_2d app is disabled, due to a missing library") 
endif()

if(MODELCORE_FOUND AND MODEL_FLUIDMEC3DP2P1G1_FOUND)
    feelpp_add_application( qs_stokes_3d SRCS qs_stokes.cpp INCLUDE_IN_ALL DEFS FEELPP_DIM=3 FEELPP_ORDER=2 LINK_LIBRARIES feelpp_modelcore feelpp_model_fluidmec3dP2P1G1 )
    install(TARGETS feelpp_qs_stokes_3d
            RUNTIME DESTINATION bin/ 
            COMPONENT Quickstart)
    add_dependencies(quickstart feelpp_qs_stokes_3d)
else()
    message(STATUS "feelpp_qs_stokes_3d app is disabled, due to a missing library") 
endif()

if(MODELCORE_FOUND AND MODEL_FLUIDMEC2DP2P1G1_FOUND AND MODEL_FLUIDMEC3DP2P1G1_FOUND)
    feelpp_add_testcase(poiseuille) 
else()
    message(STATUS "poiseuille testcase is disabled, due to a missing library") 
endif()
