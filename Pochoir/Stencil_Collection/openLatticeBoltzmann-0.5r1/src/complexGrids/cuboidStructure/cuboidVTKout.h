/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2006, 2007 Mathias J. Krause, Jonas Latt
 *  Address: Wilhelm-Maybach-Str. 24, 68766 Hockenheim, Germany 
 *  E-mail: mathias.j.krause@gmx.de
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
 * A method to write vtk data for cuboid geometries
 * (only for uniform grids) -- header file.
 */

#ifndef CUBOID_VTK_OUT_H
#define CUBOID_VTK_OUT_H

#include "core/dataFields2D.h"
#include "core/dataFields3D.h"
#include "cuboidGeometry2D.h"
#include "cuboidGeometry3D.h"
#include "core/loadBalancer.h"
#include <sstream>
#include <iomanip>
#include <vector>

namespace olb {

template<typename T>
class CuboidVTKout2D {
    public:
        /// A method to write vtk data for uniform grids
        static void writeFlowField (
            std::string const& fName,
            std::string const& scalarFieldName,
            std::vector<ScalarField2D<T> > const& scalarField,
            std::string const& vectorFieldName,
            std::vector<TensorField2D<T,2> > const& vectorField,
            CuboidGeometry2D<T> const& cGeometry, 
            loadBalancer& load, T deltaT );
    private:
        static void writePreamble(std::string& fullName, int nx, int ny, T deltaX);
        static void writePiece(
            std::string& fullName,
            std::string const& scalarFieldName,
            ScalarField2D<T> const& scalarField,
            std::string const& vectorFieldName,
            TensorField2D<T,2> const& vectorField,
            T deltaX, T deltaT,
            int originX=0, int originY=0 );
        static void writePostScript(std::string& fullName);
};

template<typename T>
class CuboidVTKout3D {
    public:
        /// A method to write vtk data for uniform grids
        static void writeFlowField (
            std::string const& fName,
            std::string const& scalarFieldName,
            std::vector<ScalarField3D<T> > const& scalarField,
            std::string const& vectorFieldName,
            std::vector<TensorField3D<T,3> > const& vectorField,
            CuboidGeometry3D<T> const& cGeometry, 
            loadBalancer& load, T deltaT );
    private:
        static void writePreamble(std::string& fullName, int nx, int ny, int nz, T deltaX);
        static void writePiece(
            std::string& fullName,
            std::string const& scalarFieldName,
            ScalarField3D<T> const& scalarField,
            std::string const& vectorFieldName,
            TensorField3D<T,3> const& vectorField,
            T deltaX, T deltaT,
            int originX=0, int originY=0, int origin=0 );
        static void writePostScript(std::string& fullName);
};


}  // namespace olb

#endif
