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
 * A collection of dynamics classes (e.g. BGK) with which a Cell object
 * can be instantiated -- generic implementation.
 */
#ifndef MRT_DYNAMICS_HH
#define MRT_DYNAMICS_HH

#include <algorithm>
#include <limits>
#include "mrtHelpers.h"

namespace olb {

//==============================================================================//
/////////////////////////// Class MRTdynamics ///////////////////////////////
//==============================================================================//
/** \param omega_ relaxation parameter, related to the dynamic viscosity
 *  \param momenta_ a Momenta object to know how to compute velocity momenta
 *  \param lambda_ will be used as an 
 */
template<typename T, template<typename U> class Lattice>
MRTdynamics<T,Lattice>::MRTdynamics (
        T omega_, Momenta<T,Lattice>& momenta_ )
    : BasicDynamics<T,Lattice>(momenta_), omega(omega_), lambda(omega_)
{
    T rt[Lattice<T>::q]; // relaxation times vector.
    for (int iPop  = 0; iPop < Lattice<T>::q; ++iPop)
    {
        rt[iPop] = Lattice<T>::S[iPop];
    }
    for (int iPop  = 0; iPop < Lattice<T>::shearIndexes; ++iPop)
    {
        rt[Lattice<T>::shearViscIndexes[iPop]] = omega;
    }
    for (int iPop = 0; iPop < Lattice<T>::q; ++iPop)
    {
        for (int jPop = 0; jPop < Lattice<T>::q; ++jPop)
        {
            invM_S[iPop][jPop] = T();
            for (int kPop = 0; kPop < Lattice<T>::q; ++kPop)
            {
                if (kPop == jPop)
                {
                    invM_S[iPop][jPop] += Lattice<T>::invM[iPop][kPop] * 
                            rt[kPop];
                }
            }
        }
    }
    
}

template<typename T, template<typename U> class Lattice>
MRTdynamics<T,Lattice>* MRTdynamics<T,Lattice>::clone() const 
{
    return new MRTdynamics<T,Lattice>(*this);
}
 
template<typename T, template<typename U> class Lattice>
T MRTdynamics<T,Lattice>::computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const
{
    return lbHelpers<T,Lattice>::equilibrium(iPop, rho, u, uSqr);
}

template<typename T, template<typename U> class Lattice>
void MRTdynamics<T,Lattice>::collide (
        Cell<T,Lattice>& cell,
        LatticeStatistics<T>& statistics )
{
    typedef Lattice<T> L;
    typedef mrtHelpers<T,Lattice> mrtH;
    
    T rho, u[L::d];
    this->momenta.computeRhoU(cell, rho, u);
    
    T uSqr = mrtH::mrtCollision(cell,rho,u,invM_S);
    
    if (cell.takesStatistics()) {
        statistics.gatherStats(rho, uSqr);
    }
}

template<typename T, template<typename U> class Lattice>
void MRTdynamics<T,Lattice>::staticCollide (
        Cell<T,Lattice>& cell,
        const T u[Lattice<T>::d],
        LatticeStatistics<T>& statistics )
{
    typedef Lattice<T> L;
    typedef lbHelpers<T,Lattice> lbH;
    
    assert(false);
}

template<typename T, template<typename U> class Lattice>
T MRTdynamics<T,Lattice>::getOmega() const 
{
    return omega;
}

template<typename T, template<typename U> class Lattice>
void MRTdynamics<T,Lattice>::setOmega(T omega_) 
{
    omega = omega_;
}

template<typename T, template<typename U> class Lattice>
T MRTdynamics<T,Lattice>::getLambda() const 
{
    return lambda;
}

template<typename T, template<typename U> class Lattice>
void MRTdynamics<T,Lattice>::setLambda(T lambda_) 
{
    lambda = lambda_;
}

}

#endif

