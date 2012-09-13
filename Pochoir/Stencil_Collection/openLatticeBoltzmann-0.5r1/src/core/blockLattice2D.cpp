/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2006, 2007 Jonas Latt
 *  Address: Rue General Dufour 24,  1211 Geneva 4, Switzerland 
 *  E-mail: jonas.latt@gmail.com
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public 
 *  License along with this program; if not, write to the Free 
 *  Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA  02110-1301, USA.
*/

/** \file
 * The dynamics of a 2D block lattice -- template instantiation.
 */
#include "blockLattice2D.h"
#include "blockLattice2D.hh"
#include "latticeDescriptors.h"
#include "latticeDescriptors.hh"

namespace olb {

    template class BlockLattice2D<double, descriptors::D2Q9Descriptor>;
    template class BlockLatticeSerializer2D<double, descriptors::D2Q9Descriptor>;
    template class BlockLatticeUnSerializer2D<double, descriptors::D2Q9Descriptor>;

}
