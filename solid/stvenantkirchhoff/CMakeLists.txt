###  CMakeLists.txt ---

#  Author(s): Christophe Prud'homme <christophe.prudhomme@feelpp.org>
#       Date: 2015-02-20
#
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
set_directory_properties(PROPERTIES EXCLUDE_FROM_ALL TRUE)
feelpp_add_application(qs_stvenant_kirchhoff_2d SRCS qs_stvenant_kirchhoff.cpp CFG qs_stvenant_kirchhoff.cfg beam DEFS FEELPP_DIM=2 FEELPP_ORDER=2)
feelpp_add_application(qs_stvenant_kirchhoff_3d SRCS qs_stvenant_kirchhoff.cpp CFG qs_stvenant_kirchhoff.cfg DEFS FEELPP_DIM=3 FEELPP_ORDER=2)
