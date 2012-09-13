/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007 Mathias J. Krause
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
 * A helper for initialising 3D boundaries -- generic implementation.
 */


#ifndef SUPER_BOUNDARY_CONDITION_3D_HH
#define SUPER_BOUNDARY_CONDITION_3D_HH

#include <vector>
#include "core/boundaryCondition3D.h"
#include "superBoundaryCondition3D.h"
#include "superLattice3D.h"


namespace olb {


///////// class superBoundaryCondition3D ///////////////////////////////

template<typename T, template<typename U> class Lattice>
sOnLatticeBoundaryCondition3D<T,Lattice>::
    sOnLatticeBoundaryCondition3D (SuperLattice3D<T,Lattice>& sLattice ):_sLattice(sLattice) {
}

template<typename T, template<typename U> class Lattice>
sOnLatticeBoundaryCondition3D<T,Lattice>::
    sOnLatticeBoundaryCondition3D(sOnLatticeBoundaryCondition3D<T,Lattice> const& rhs):_sLattice(rhs._sLattice) {

    _blockBCs = rhs._blockBCs;
    _overlap = rhs._overlap;
}

template<typename T, template<typename U> class Lattice>
sOnLatticeBoundaryCondition3D<T,Lattice> sOnLatticeBoundaryCondition3D<T,Lattice>::operator=(
    sOnLatticeBoundaryCondition3D<T,Lattice> rhs) {

    sOnLatticeBoundaryCondition3D<T,Lattice> tmp(rhs);
    return tmp;
}

template<typename T, template<typename U> class Lattice>
sOnLatticeBoundaryCondition3D<T,Lattice>::
    ~sOnLatticeBoundaryCondition3D() {

    for (unsigned iC=0; iC<_blockBCs.size(); iC++) {
        delete _blockBCs[iC];
    }
}


template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addVelocityBoundary0N(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addVelocityBoundary0N( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}


template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addVelocityBoundary0P(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addVelocityBoundary0P( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addVelocityBoundary1N(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addVelocityBoundary1N( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addVelocityBoundary1P(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addVelocityBoundary1P( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addVelocityBoundary2N(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addVelocityBoundary2N( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addVelocityBoundary2P(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addVelocityBoundary2P( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addPressureBoundary0N(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addPressureBoundary0N( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addPressureBoundary0P(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addPressureBoundary0P( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addPressureBoundary1N(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addPressureBoundary1N( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addPressureBoundary1P(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addPressureBoundary1P( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addPressureBoundary2N(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addPressureBoundary2N( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addPressureBoundary2P(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addPressureBoundary2P( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addExternalVelocityEdge0NN(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addExternalVelocityEdge0NN( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addExternalVelocityEdge0NP(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addExternalVelocityEdge0NP( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addExternalVelocityEdge0PN(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addExternalVelocityEdge0PN( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addExternalVelocityEdge0PP(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addExternalVelocityEdge0PP( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addExternalVelocityEdge1NN(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addExternalVelocityEdge1NN( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addExternalVelocityEdge1NP(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addExternalVelocityEdge1NP( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addExternalVelocityEdge1PN(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addExternalVelocityEdge1PN( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addExternalVelocityEdge1PP(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addExternalVelocityEdge1PP( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addExternalVelocityEdge2NN(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addExternalVelocityEdge2NN( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addExternalVelocityEdge2NP(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addExternalVelocityEdge2NP( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addExternalVelocityEdge2PN(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addExternalVelocityEdge2PN( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addExternalVelocityEdge2PP(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addExternalVelocityEdge2PP( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addInternalVelocityEdge0NN(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addInternalVelocityEdge0NN( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addInternalVelocityEdge0NP(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addInternalVelocityEdge0NP( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addInternalVelocityEdge0PN(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addInternalVelocityEdge0PN( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addInternalVelocityEdge0PP(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addInternalVelocityEdge0PP( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addInternalVelocityEdge1NN(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addInternalVelocityEdge1NN( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addInternalVelocityEdge1NP(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addInternalVelocityEdge1NP( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addInternalVelocityEdge1PN(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addInternalVelocityEdge1PN( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addInternalVelocityEdge1PP(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addInternalVelocityEdge1PP( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addInternalVelocityEdge2NN(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addInternalVelocityEdge2NN( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addInternalVelocityEdge2NP(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addInternalVelocityEdge2NP( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addInternalVelocityEdge2PN(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addInternalVelocityEdge2PN( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addInternalVelocityEdge2PP(T x0, T x1, T y0, T y1, T z0, T z1, T omega){

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1, locZ0, locZ1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters( x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1, overlap)) {
            _blockBCs[iC]->addInternalVelocityEdge2PP( 
                locX0, locX1, locY0, locY1, locZ0, locZ1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
            y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
        }
    }
}


template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addExternalVelocityCornerNNN(T x, T y, T z, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX, locY, locZ;

    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ, overlap)) {
            _blockBCs[iC]->addExternalVelocityCornerNNN(locX, locY, locZ, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ)) {
            addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addExternalVelocityCornerNNP(T x, T y, T z, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX, locY, locZ;

    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ, overlap)) {
            _blockBCs[iC]->addExternalVelocityCornerNNP(locX, locY, locZ, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ)) {
            addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addExternalVelocityCornerNPN(T x, T y, T z, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX, locY, locZ;

    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ, overlap)) {
            _blockBCs[iC]->addExternalVelocityCornerNPN(locX, locY, locZ, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ)) {
            addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addExternalVelocityCornerNPP(T x, T y, T z, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX, locY, locZ;

    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ, overlap)) {
            _blockBCs[iC]->addExternalVelocityCornerNPP(locX, locY, locZ, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ)) {
            addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addExternalVelocityCornerPNN(T x, T y, T z, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX, locY, locZ;

    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ, overlap)) {
            _blockBCs[iC]->addExternalVelocityCornerPNN(locX, locY, locZ, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ)) {
            addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addExternalVelocityCornerPNP(T x, T y, T z, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX, locY, locZ;

    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ, overlap)) {
            _blockBCs[iC]->addExternalVelocityCornerPNP(locX, locY, locZ, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ)) {
            addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addExternalVelocityCornerPPN(T x, T y, T z, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX, locY, locZ;

    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ, overlap)) {
            _blockBCs[iC]->addExternalVelocityCornerPPN(locX, locY, locZ, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ)) {
            addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addExternalVelocityCornerPPP(T x, T y, T z, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX, locY, locZ;

    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ, overlap)) {
            _blockBCs[iC]->addExternalVelocityCornerPPP(locX, locY, locZ, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ)) {
            addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addInternalVelocityCornerNNN(T x, T y, T z, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX, locY, locZ;

    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ, overlap)) {
            _blockBCs[iC]->addInternalVelocityCornerNNN(locX, locY, locZ, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ)) {
            addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addInternalVelocityCornerNNP(T x, T y, T z, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX, locY, locZ;

    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ, overlap)) {
            _blockBCs[iC]->addInternalVelocityCornerNNP(locX, locY, locZ, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ)) {
            addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addInternalVelocityCornerNPN(T x, T y, T z, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX, locY, locZ;

    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ, overlap)) {
            _blockBCs[iC]->addInternalVelocityCornerNPN(locX, locY, locZ, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ)) {
            addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addInternalVelocityCornerNPP(T x, T y, T z, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX, locY, locZ;

    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ, overlap)) {
            _blockBCs[iC]->addInternalVelocityCornerNPP(locX, locY, locZ, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ)) {
            addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addInternalVelocityCornerPNN(T x, T y, T z, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX, locY, locZ;

    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ, overlap)) {
            _blockBCs[iC]->addInternalVelocityCornerPNN(locX, locY, locZ, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ)) {
            addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addInternalVelocityCornerPNP(T x, T y, T z, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX, locY, locZ;

    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ, overlap)) {
            _blockBCs[iC]->addInternalVelocityCornerPNP(locX, locY, locZ, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ)) {
            addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addInternalVelocityCornerPPN(T x, T y, T z, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX, locY, locZ;

    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ, overlap)) {
            _blockBCs[iC]->addInternalVelocityCornerPPN(locX, locY, locZ, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ)) {
            addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addInternalVelocityCornerPPP(T x, T y, T z, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX, locY, locZ;

    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ, overlap)) {
            _blockBCs[iC]->addInternalVelocityCornerPPP(locX, locY, locZ, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
                                   locX, locY, locZ)) {
            addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
        }
    }
}


template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T,Lattice>::
        addPoints2CommBC(int x0, int x1, int y0, int y1, int z0, int z1, int iCglob) {

    if (_overlap!=0) {
        int nC  = _sLattice.get_cGeometry().get_nC();
        T globX = _sLattice.get_cGeometry().get_cuboid(iCglob).get_globPosX();
        T globY = _sLattice.get_cGeometry().get_cuboid(iCglob).get_globPosY();
        T globZ = _sLattice.get_cGeometry().get_cuboid(iCglob).get_globPosZ();
        T delta = _sLattice.get_cGeometry().get_cuboid(iCglob).get_delta();

        for (int iOverl=1; iOverl<=_overlap; iOverl++) {
            for (int iX=x0-iOverl; iX<=x1+iOverl; iX++) {
                for (int iY=y0-iOverl; iY<=y1+iOverl; iY++) {
                    for (int iZ=z0-iOverl; iZ<=z1+iOverl; iZ++) {
                        if (iX==x0-iOverl || iX==x1+iOverl ||
                            iY==y0-iOverl || iY==y1+iOverl ||
                            iZ==z0-iOverl || iZ==z1+iOverl) {
                            T nextX = globX +iX*delta;
                            T nextY = globY +iY*delta;
                            T nextZ = globZ +iZ*delta;
                            int found_iC = _sLattice.get_cGeometry().get_iC(nextX, nextY, nextZ);
                            if (found_iC!=nC && found_iC!=iCglob) {
                                _sLattice.get_commBC().add_cell(iCglob, nextX, nextY, nextZ);
                            }
                        }
                    }
                }
            }
        }
    }
}

////////////////// Factory functions //////////////////////////////////

template<typename T, template<typename U> class Lattice, typename MixinDynamics>
void createLocalBoundaryCondition3D(sOnLatticeBoundaryCondition3D<T,Lattice>& sBC) {

    int nC = sBC.get_sLattice().get_load().size();
    sBC.set_overlap(0);
    for (int iC=0; iC<nC; iC++) {
        OnLatticeBoundaryCondition3D<T,Lattice>* blockBC
            = createLocalBoundaryCondition3D(sBC.get_sLattice().get_blockLattice(iC));
        sBC.get_blockBCs().push_back(blockBC);
    }
}

template<typename T, template<typename U> class Lattice, typename MixinDynamics>
void createInterpBoundaryCondition3D(sOnLatticeBoundaryCondition3D<T,Lattice>& sBC) {

    int nC = sBC.get_sLattice().get_load().size();
    sBC.set_overlap(1);
    for (int iC=0; iC<nC; iC++) {
        OnLatticeBoundaryCondition3D<T,Lattice>* blockBC
            = createInterpBoundaryCondition3D(sBC.get_sLattice().get_blockLattice(iC));
        sBC.get_blockBCs().push_back(blockBC);
    }
}

}  // namespace olb

#endif
