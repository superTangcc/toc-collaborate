/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007 Jonas Latt and Bernd Stahl
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
 * A 3D multi data field -- template instantiation.
 */

#include "complexGrids/mpiManager/mpiManager.h"
#include "multiDataFieldHandler3D.h"
#include "multiDataFieldHandler3D.hh"
#include "core/latticeDescriptors.h"
#include "core/latticeDescriptors.hh"

namespace olb {

    template class SerialMultiDataFieldHandler3D<double>;

#ifdef PARALLEL_MODE_MPI
    template class ParallelMultiDataFieldHandler3D<double>;
#endif

}
