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
 * The description of a vector of 3D cuboid  -- generic implementation.
 */


#ifndef CUBOID_GEOMETRY_3D_HH
#define CUBOID_GEOMETRY_3D_HH

#include <iostream>
#include <math.h>
#include <vector>
#include "cuboid3D.h"
#include "cuboidGeometry3D.h"


namespace olb {

////////////////////// Class CuboidGeometry3D /////////////////////////

template<typename T>
CuboidGeometry3D<T>::CuboidGeometry3D(T globPosX, T globPosY, T globPosZ, 
                             T delta, int nX, int nY, int nZ, int nC) {
    //_cuboids.reserve(10000);
    Cuboid3D<T> cuboid(globPosX, globPosY, globPosZ, delta, nX, nY, nZ);
    add(cuboid);
    split(0, nC);
}


template<typename T>
Cuboid3D<T>& CuboidGeometry3D<T>::get_cuboid(int i) {
    return _cuboids[i];
}

template<typename T>
Cuboid3D<T> const& CuboidGeometry3D<T>::get_cuboid(int i) const {
    return _cuboids[i]; 
}


template<typename T>
int CuboidGeometry3D<T>::get_nC() const { return _cuboids.size(); }

template<typename T>
T CuboidGeometry3D<T>::get_minRatio() const {
    T minRatio = 1.;
    for (unsigned i=0; i<_cuboids.size(); i++) {
        if((T)_cuboids[i].get_nX()/(T)_cuboids[i].get_nY() < minRatio) {
            minRatio = (T)_cuboids[i].get_nX()/(T)_cuboids[i].get_nY();
        }
        if((T)_cuboids[i].get_nY()/(T)_cuboids[i].get_nZ() < minRatio) {
            minRatio = (T)_cuboids[i].get_nY()/(T)_cuboids[i].get_nZ();
        }
        if((T)_cuboids[i].get_nZ()/(T)_cuboids[i].get_nX() < minRatio) {
            minRatio = (T)_cuboids[i].get_nZ()/(T)_cuboids[i].get_nX();
        }
    }
    return minRatio;
}

template<typename T>
T CuboidGeometry3D<T>::get_maxRatio() const {
    T maxRatio = 1.;
    for (unsigned i=0; i<_cuboids.size(); i++) {
        if((T)_cuboids[i].get_nX()/(T)_cuboids[i].get_nY() > maxRatio) {
            maxRatio = (T)_cuboids[i].get_nX()/(T)_cuboids[i].get_nY();
        }
        if((T)_cuboids[i].get_nY()/(T)_cuboids[i].get_nZ() > maxRatio) {
            maxRatio = (T)_cuboids[i].get_nY()/(T)_cuboids[i].get_nZ();
        }
        if((T)_cuboids[i].get_nZ()/(T)_cuboids[i].get_nX() > maxRatio) {
            maxRatio = (T)_cuboids[i].get_nZ()/(T)_cuboids[i].get_nX();
        }
    }
    return maxRatio;
}

template<typename T>
T CuboidGeometry3D<T>::get_minVolume() const {
    T minVolume = _cuboids[0].get_volume();
    for (unsigned i=0; i<_cuboids.size(); i++) {
        if(_cuboids[i].get_volume() < minVolume) {
            minVolume = _cuboids[i].get_volume();
        }
    }
    return minVolume;
}

template<typename T>
T CuboidGeometry3D<T>::get_maxVolume() const {
    T maxVolume = _cuboids[0].get_volume();
    for (unsigned i=0; i<_cuboids.size(); i++) {
        if(_cuboids[i].get_volume() > maxVolume) {
            maxVolume = _cuboids[i].get_volume();
        }
    }
    return maxVolume;
}

template<typename T>
int CuboidGeometry3D<T>::get_minNodes() const {
    int minNodes = _cuboids[0].get_nNodesVolume();
    for (unsigned i=0; i<_cuboids.size(); i++) {
        if(_cuboids[i].get_nNodesVolume() < minNodes) {
            minNodes = _cuboids[i].get_nNodesVolume();
        }
    }
    return minNodes;
}

template<typename T>
int CuboidGeometry3D<T>::get_maxNodes() const {
    int maxNodes = _cuboids[0].get_nNodesVolume();
    for (unsigned i=0; i<_cuboids.size(); i++) {
        if(_cuboids[i].get_nNodesVolume() > maxNodes) {
            maxNodes = _cuboids[i].get_nNodesVolume();
        }
    }
    return maxNodes;
}

template<typename T>
T CuboidGeometry3D<T>::get_minDelta() const {
    T minDelta = _cuboids[0].get_delta();
    for (unsigned i=0; i<_cuboids.size(); i++) {
        if(_cuboids[i].get_delta() < minDelta) {
            minDelta = _cuboids[i].get_delta();
        }
    }
    return minDelta;
}

template<typename T>
T CuboidGeometry3D<T>::get_maxDelta() const {
    T maxDelta = _cuboids[0].get_delta();
    for (unsigned i=0; i<_cuboids.size(); i++) {
        if(_cuboids[i].get_delta() > maxDelta) {
            maxDelta = _cuboids[i].get_delta();
        }
    }
    return maxDelta;
}

template<typename T>
Cuboid3D<T> CuboidGeometry3D<T>::get_motherC() const {

    Cuboid3D<T> found;
    if(_cuboids.size()==0) {
        found.init(0, 0, 0, 0, 0, 0, 0);
        return found;
    }

    T delta = _cuboids[0].get_delta();
    T globPosXmin = _cuboids[0].get_globPosX();
    T globPosYmin = _cuboids[0].get_globPosY();
    T globPosZmin = _cuboids[0].get_globPosZ();
    T globPosXmax = _cuboids[0].get_globPosX() + delta*(_cuboids[0].get_nX()-1);
    T globPosYmax = _cuboids[0].get_globPosY() + delta*(_cuboids[0].get_nY()-1);
    T globPosZmax = _cuboids[0].get_globPosZ() + delta*(_cuboids[0].get_nZ()-1);

    for (unsigned i=1; i<_cuboids.size(); i++) {
        if(delta > _cuboids[i].get_delta() ) {
            delta = _cuboids[i].get_delta();
        }
        if(globPosXmin > _cuboids[i].get_globPosX() ) {
            globPosXmin = _cuboids[i].get_globPosX();
        }
        if(globPosYmin > _cuboids[i].get_globPosY() ) {
            globPosYmin = _cuboids[i].get_globPosY();
        }
        if(globPosZmin > _cuboids[i].get_globPosZ() ) {
            globPosZmin = _cuboids[i].get_globPosZ();
        }

        if(globPosXmax < _cuboids[i].get_globPosX() 
                            + delta*(_cuboids[i].get_nX()-1)) {
            globPosXmax = _cuboids[i].get_globPosX() 
                            + delta*(_cuboids[i].get_nX()-1);
        }
        if(globPosYmax < _cuboids[i].get_globPosY() 
                            + delta*(_cuboids[i].get_nY()-1)) {
            globPosYmax = _cuboids[i].get_globPosY() 
                            + delta*(_cuboids[i].get_nY()-1);
        }
        if(globPosZmax < _cuboids[i].get_globPosZ() 
                            + delta*(_cuboids[i].get_nZ()-1)) {
            globPosZmax = _cuboids[i].get_globPosZ() 
                            + delta*(_cuboids[i].get_nZ()-1);
        }
    }
    int nX = int(ceil((globPosXmax - globPosXmin)/delta))+1;
    int nY = int(ceil((globPosYmax - globPosYmin)/delta))+1;
    int nZ = int(ceil((globPosZmax - globPosZmin)/delta))+1;

    found.init(globPosXmin, globPosYmin, globPosZmin, delta, nX, nY, nZ); 

    return found;
}

template<typename T>
void CuboidGeometry3D<T>::printStatistics() const {
    std::cout << "---Cuboid Stucture Statistics---" << std::endl; 
    std::cout << " Number of Cuboids: " << "\t" << get_nC() << std::endl;
    std::cout << " Delta (min): " << "\t" << "\t" << get_minDelta() << std::endl;
    std::cout << "       (max): " << "\t" << "\t" << get_maxDelta() << std::endl;
    std::cout << " Ratio (min): " << "\t" << "\t" << get_minRatio() << std::endl;
    std::cout << "       (max): " << "\t" << "\t" << get_maxRatio() << std::endl;
    std::cout << " Nodes (min): " << "\t" << "\t" << get_minNodes() << std::endl;
    std::cout << "       (max): " << "\t" << "\t" << get_maxNodes() << std::endl;
    std::cout << "--------------------------------" << std::endl;
}


template<typename T>
int CuboidGeometry3D<T>::get_iC(T globX, T globY, T globZ) const {
    unsigned i;
    int tempX, tempY, tempZ;
    for (i=0; i<_cuboids.size(); i++) {
        if (_cuboids[i].checkPoint(globX, globY, globZ, tempX, tempY, tempZ)) return (int)i;
    }
    return (int)i;
}

template<typename T>
int CuboidGeometry3D<T>::get_iC(T globX, T globY, T globZ,
         int orientationX, int orientationY, int orientationZ) const {
    unsigned i;
    for (i=0; i<_cuboids.size(); i++) {
        if (_cuboids[i].checkPoint(globX, globY, globZ) &&
            _cuboids[i].checkPoint(globX + orientationX/_cuboids[i].get_delta(),
                         globY + orientationY/_cuboids[i].get_delta(),
                         globZ + orientationZ/_cuboids[i].get_delta())) {
           return (int)i;
        }
    }
    return (int)i;
}

template<typename T>
void CuboidGeometry3D<T>::add(Cuboid3D<T> cuboid) {

    _cuboids.push_back(cuboid);
}

template<typename T>
void CuboidGeometry3D<T>::remove(int iC) {

    _cuboids.erase(_cuboids.begin() + iC);
}

template<typename T>
void CuboidGeometry3D<T>::split(int iC, int p) {

    Cuboid3D<T> temp(_cuboids[iC].get_globPosX(),_cuboids[iC].get_globPosY(),
        _cuboids[iC].get_globPosZ(),  _cuboids[iC].get_delta(),
        _cuboids[iC].get_nX(), _cuboids[iC].get_nY(), _cuboids[iC].get_nZ());
    temp.divide(p, _cuboids);
    remove(iC);
}


}  // namespace olb

#endif
