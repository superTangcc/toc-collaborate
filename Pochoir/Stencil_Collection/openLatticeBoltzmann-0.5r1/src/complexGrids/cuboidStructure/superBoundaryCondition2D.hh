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
 * A helper for initialising 2D boundaries -- generic implementation.
 */


#ifndef SUPER_BOUNDARY_CONDITION_2D_HH
#define SUPER_BOUNDARY_CONDITION_2D_HH

#include <vector>
#include "core/boundaryCondition2D.h"
#include "superBoundaryCondition2D.h"
#include "superLattice2D.h"


namespace olb {


///////// class superBoundaryCondition2D ///////////////////////////////

template<typename T, template<typename U> class Lattice>
sOnLatticeBoundaryCondition2D<T,Lattice>::
    sOnLatticeBoundaryCondition2D (SuperLattice2D<T,Lattice>& sLattice ):_sLattice(sLattice) {
}

template<typename T, template<typename U> class Lattice>
sOnLatticeBoundaryCondition2D<T,Lattice>::
    sOnLatticeBoundaryCondition2D(sOnLatticeBoundaryCondition2D<T,Lattice> const& rhs):_sLattice(rhs._sLattice) {

    _blockBCs = rhs._blockBCs;
    _overlap = rhs._overlap;
}

template<typename T, template<typename U> class Lattice>
sOnLatticeBoundaryCondition2D<T,Lattice> sOnLatticeBoundaryCondition2D<T,Lattice>::operator=(
    sOnLatticeBoundaryCondition2D<T,Lattice> rhs) {

    sOnLatticeBoundaryCondition2D<T,Lattice> tmp(rhs);
    return tmp;
}

template<typename T, template<typename U> class Lattice>
sOnLatticeBoundaryCondition2D<T,Lattice>::
    ~sOnLatticeBoundaryCondition2D() {

    for (unsigned iC=0; iC<_blockBCs.size(); iC++) {
        delete _blockBCs[iC];
    }
}


template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition2D<T,Lattice>::
        addVelocityBoundary0N(T x0, T x1, T y0, T y1, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1, y0, y1,
                                   locX0, locX1, locY0, locY1, overlap)) {
            _blockBCs[iC]->addVelocityBoundary0N(locX0, locX1, locY0, locY1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1, y0, y1,
                                   locX0, locX1, locY0, locY1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition2D<T,Lattice>::
        addVelocityBoundary0P(T x0, T x1, T y0, T y1, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1, y0, y1,
                                   locX0, locX1, locY0, locY1, overlap)) {
            _blockBCs[iC]->addVelocityBoundary0P(locX0, locX1, locY0, locY1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1, y0, y1,
                                   locX0, locX1, locY0, locY1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition2D<T,Lattice>::
        addVelocityBoundary1N(T x0, T x1, T y0, T y1, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1, y0, y1,
                                   locX0, locX1, locY0, locY1, overlap)) {
            _blockBCs[iC]->addVelocityBoundary1N(locX0, locX1, locY0, locY1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1, y0, y1,
                                   locX0, locX1, locY0, locY1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition2D<T,Lattice>::
        addVelocityBoundary1P(T x0, T x1, T y0, T y1, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1, y0, y1,
                                   locX0, locX1, locY0, locY1, overlap)) {
            _blockBCs[iC]->addVelocityBoundary1P(locX0, locX1, locY0, locY1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1, y0, y1,
                                   locX0, locX1, locY0, locY1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition2D<T,Lattice>::
        addPressureBoundary0N(T x0, T x1, T y0, T y1, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1, y0, y1,
                                   locX0, locX1, locY0, locY1, overlap)) {
            _blockBCs[iC]->addPressureBoundary0N(locX0, locX1, locY0, locY1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1, y0, y1,
                                   locX0, locX1, locY0, locY1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition2D<T,Lattice>::
        addPressureBoundary0P(T x0, T x1, T y0, T y1, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1, y0, y1,
                                   locX0, locX1, locY0, locY1, overlap)) {
            _blockBCs[iC]->addPressureBoundary0P(locX0, locX1, locY0, locY1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1, y0, y1,
                                   locX0, locX1, locY0, locY1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition2D<T,Lattice>::
        addPressureBoundary1N(T x0, T x1, T y0, T y1, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1, y0, y1,
                                   locX0, locX1, locY0, locY1, overlap)) {
            _blockBCs[iC]->addPressureBoundary1N(locX0, locX1, locY0, locY1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1, y0, y1,
                                   locX0, locX1, locY0, locY1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition2D<T,Lattice>::
        addPressureBoundary1P(T x0, T x1, T y0, T y1, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX0, locX1, locY0, locY1;
    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1, y0, y1,
                                   locX0, locX1, locY0, locY1, overlap)) {
            _blockBCs[iC]->addPressureBoundary1P(locX0, locX1, locY0, locY1, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1, y0, y1,
                                   locX0, locX1, locY0, locY1)) {
            addPoints2CommBC(locX0, locX1, locY0, locY1, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition2D<T,Lattice>::
        addExternalVelocityCornerNN(T x, T y, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX, locY;

    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y,
                                   locX, locY, overlap)) {
            _blockBCs[iC]->addExternalVelocityCornerNN(locX, locY, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y,
                                   locX, locY)) {
            addPoints2CommBC(locX, locX, locY, locY, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition2D<T,Lattice>::
        addExternalVelocityCornerNP(T x, T y, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX, locY;

    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y,
                                   locX, locY, overlap)) {
            _blockBCs[iC]->addExternalVelocityCornerNP(locX, locY, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y,
                                   locX, locY)) {
            addPoints2CommBC(locX, locX, locY, locY, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition2D<T,Lattice>::
        addExternalVelocityCornerPN(T x, T y, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX, locY;

    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y,
                                   locX, locY, overlap)) {
            _blockBCs[iC]->addExternalVelocityCornerPN(locX, locY, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y,
                                   locX, locY)) {
            addPoints2CommBC(locX, locX, locY, locY, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition2D<T,Lattice>::
        addExternalVelocityCornerPP(T x, T y, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX, locY;

    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y,
                                   locX, locY, overlap)) {
            _blockBCs[iC]->addExternalVelocityCornerPP(locX, locY, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y,
                                   locX, locY)) {
            addPoints2CommBC(locX, locX, locY, locY, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition2D<T,Lattice>::
        addInternalVelocityCornerNN(T x, T y, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX, locY;

    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y,
                                   locX, locY, overlap)) {
            _blockBCs[iC]->addInternalVelocityCornerNN(locX, locY, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y,
                                   locX, locY)) {
            addPoints2CommBC(locX, locX, locY, locY, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition2D<T,Lattice>::
        addInternalVelocityCornerNP(T x, T y, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX, locY;

    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y,
                                   locX, locY, overlap)) {
            _blockBCs[iC]->addInternalVelocityCornerNP(locX, locY, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y,
                                   locX, locY)) {
            addPoints2CommBC(locX, locX, locY, locY, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition2D<T,Lattice>::
        addInternalVelocityCornerPN(T x, T y, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX, locY;

    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y,
                                   locX, locY, overlap)) {
            _blockBCs[iC]->addInternalVelocityCornerPN(locX, locY, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y,
                                   locX, locY)) {
            addPoints2CommBC(locX, locX, locY, locY, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition2D<T,Lattice>::
        addInternalVelocityCornerPP(T x, T y, T omega) {

    int overlap = _sLattice.get_overlap();
    int nC = _sLattice.get_load().size();
    int locX, locY;

    for (int iC=0; iC<nC; iC++) {
        int iCglob = _sLattice.get_load().glob(iC);
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y,
                                   locX, locY, overlap)) {
            _blockBCs[iC]->addInternalVelocityCornerPP(locX, locY, omega);
        }
        if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y,
                                   locX, locY)) {
            addPoints2CommBC(locX, locX, locY, locY, iCglob);
        }
    }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition2D<T,Lattice>::
        addPoints2CommBC(int x0, int x1, int y0, int y1, int iCglob) {

    if (_overlap!=0) {
        int nC  = _sLattice.get_cGeometry().get_nC();
        T globX = _sLattice.get_cGeometry().get_cuboid(iCglob).get_globPosX();
        T globY = _sLattice.get_cGeometry().get_cuboid(iCglob).get_globPosY();
        T delta = _sLattice.get_cGeometry().get_cuboid(iCglob).get_delta();

        for (int iOverl=1; iOverl<=_overlap; iOverl++) {
            for (int iX=x0-iOverl; iX<=x1+iOverl; iX++) {
                for (int iY=y0-iOverl; iY<=y1+iOverl; iY++) {
                    if (iX==x0-iOverl || iX==x1+iOverl ||
                                iY==y0-iOverl || iY==y1+iOverl) {
                        T nextX = globX +iX*delta;
                        T nextY = globY +iY*delta;
                        int found_iC = _sLattice.get_cGeometry().get_iC(nextX, nextY);
                        if (found_iC!=nC && found_iC!=iCglob) {
                            _sLattice.get_commBC().add_cell(iCglob, nextX, nextY);
                        }
                    }
                }
            }
        }
    }
}

////////////////// Factory functions //////////////////////////////////

template<typename T, template<typename U> class Lattice, typename MixinDynamics>
void createLocalBoundaryCondition2D(sOnLatticeBoundaryCondition2D<T,Lattice>& sBC) {

    int nC = sBC.get_sLattice().get_load().size();
    sBC.set_overlap(0);
    for (int iC=0; iC<nC; iC++) {
        OnLatticeBoundaryCondition2D<T,Lattice>* blockBC
            = createLocalBoundaryCondition2D(sBC.get_sLattice().get_blockLattice(iC));
        sBC.get_blockBCs().push_back(blockBC);
    }
}

template<typename T, template<typename U> class Lattice, typename MixinDynamics>
void createInterpBoundaryCondition2D(sOnLatticeBoundaryCondition2D<T,Lattice>& sBC) {

    int nC = sBC.get_sLattice().get_load().size();
    sBC.set_overlap(1);
    for (int iC=0; iC<nC; iC++) {
        OnLatticeBoundaryCondition2D<T,Lattice>* blockBC
            = createInterpBoundaryCondition2D(sBC.get_sLattice().get_blockLattice(iC));
        sBC.get_blockBCs().push_back(blockBC);
    }
}

}  // namespace olb

#endif
