/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007 Orestis Malaspinas, Jonas Latt
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

#include "extendedFiniteDifferenceBoundary3D.h"
#include "extendedFiniteDifferenceBoundary3D.hh"
#include "core/boundaryPostProcessors3D.h"
#include "core/boundaryPostProcessors3D.hh"
#include "core/postProcessing.h"
#include "core/postProcessing.hh"
#include "core/latticeDescriptors.h"
#include "core/latticeDescriptors.hh"


namespace olb {

template class ExtendedFdPlaneBoundaryPostProcessor3D<double, descriptors::D3Q19Descriptor,          0,1>;
template class ExtendedFdPlaneBoundaryProcessorGenerator3D<double, descriptors::D3Q19Descriptor, 0,1>;
template class ExtendedFdPlaneBoundaryPostProcessor3D<double, descriptors::D3Q19Descriptor,          0,-1>;
template class ExtendedFdPlaneBoundaryProcessorGenerator3D<double, descriptors::D3Q19Descriptor, 0,-1>;
template class ExtendedFdPlaneBoundaryPostProcessor3D<double, descriptors::D3Q19Descriptor,          1,1>;
template class ExtendedFdPlaneBoundaryProcessorGenerator3D<double, descriptors::D3Q19Descriptor, 1,1>;
template class ExtendedFdPlaneBoundaryPostProcessor3D<double, descriptors::D3Q19Descriptor,          1,-1>;
template class ExtendedFdPlaneBoundaryProcessorGenerator3D<double, descriptors::D3Q19Descriptor, 1,-1>;
template class ExtendedFdPlaneBoundaryPostProcessor3D<double, descriptors::D3Q19Descriptor,          2,1>;
template class ExtendedFdPlaneBoundaryProcessorGenerator3D<double, descriptors::D3Q19Descriptor, 2,1>;
template class ExtendedFdPlaneBoundaryPostProcessor3D<double, descriptors::D3Q19Descriptor,          2,-1>;
template class ExtendedFdPlaneBoundaryProcessorGenerator3D<double, descriptors::D3Q19Descriptor, 2,-1>;


template class BoundaryConditionInstantiator3D
    <
        double, descriptors::D3Q19Descriptor,
        ExtendedFdBoundaryManager3D < double, descriptors::D3Q19Descriptor,
                                      BGKdynamics<double,descriptors::D3Q19Descriptor> >
    >;

template OnLatticeBoundaryCondition3D<double,descriptors::D3Q19Descriptor>*
    createExtendedFdBoundaryCondition3D < double,descriptors::D3Q19Descriptor,
                                          BGKdynamics<double,descriptors::D3Q19Descriptor> >
   (
        BlockStructure3D<double,descriptors::D3Q19Descriptor>& block
   );

}  // namespace olb
