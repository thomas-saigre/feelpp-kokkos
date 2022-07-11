###  TEMPLATE.txt.tpl; coding: utf-8 ---

#  Author(s): Christophe Prud'homme <prudhomme@unistra.fr>
#       Date: 2012-12-16
#
#  Copyright (C) 2012 Feel++ Consortium
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
# tag::minimal[]
cmake_minimum_required(VERSION 3.0) # <1>
project(minimal) # <2>

# find Feel++ package
find_package(Feel++
  PATHS
  $ENV{FEELPP_DIR}/share/feelpp/feel/cmake/modules
  /usr/share/feelpp/feel/cmake/modules
  /usr/share/feelpp/cmake/modules
  /usr/local/share/feelpp/feel/cmake/modules
  REQUIRED) # <3>

# create application feelpp_minimal
feelpp_add_application( app SRCS minimal.cpp) # <4>
# end::minimal[]
