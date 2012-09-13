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

#ifndef POST_PROCESSING_HH
#define POST_PROCESSING_HH

#include <cmath>
#include "blockLattice2D.h"
#include "blockLattice3D.h"
#include "util.h"

namespace olb {

////////////////////// Class LatticeStatistics /////////////////

template<typename T>
LatticeStatistics<T>::LatticeStatistics() {
    initialize();
}

template<typename T>
LatticeStatistics<T>::~LatticeStatistics() {
}

template<typename T>
void LatticeStatistics<T>::reset() {
    // avoid division by zero
    if (sum_nCells == 0) {
        average_rho = T();
        average_energy = T();
        maxU = T();
        numCells = 0;
        if (firstCall) firstCall = false;
    }
    else {
        // The average density is actually used in the "ConstRhoBgk" model.
        // Depending on the simulation setup, it is possible that it has
        // a nonsensical value before the simulation is started. Therefore,
        // it is initialized at 1.
        if (firstCall) {
            average_rho = (T)1;
            firstCall = false;
        }
        else {
            average_rho = sum_rho / (T)sum_nCells;
        }
        average_energy = (T)0.5 * sum_uSqr / (T)sum_nCells;
        maxU           = sqrt(max_uSqr);
        numCells       = sum_nCells;
    }

    sum_rho  = T();
    sum_uSqr = T();
    max_uSqr = T();
    sum_nCells = 0;
}

template<typename T>
void LatticeStatistics<T>::reset (
        T average_rho_, T average_energy_, T maxU_, int numCells_ )
{
    average_rho    = average_rho_;
    average_energy = average_energy_;
    maxU           = maxU_;
    numCells       = numCells_;

    sum_rho  = T();
    sum_uSqr = T();
    max_uSqr = T();
    sum_nCells = 0;
}

template<typename T>
void LatticeStatistics<T>::initialize() {

    sum_rho  = T();
    sum_uSqr = T();
    max_uSqr = T();
    sum_nCells = 0;

    average_rho    = (T)1;
    average_energy = T();
    maxU           = T();

    firstCall = true;
}


////////////////////// Class PostProcessorGenerator2D /////////////////

template<typename T, template<typename U> class Lattice>
PostProcessorGenerator2D<T,Lattice>::PostProcessorGenerator2D (
        int x0_, int x1_, int y0_, int y1_)
    : x0(x0_), x1(x1_), y0(y0_), y1(y1_)
{ }

template<typename T, template<typename U> class Lattice>
void PostProcessorGenerator2D<T,Lattice>::shift(int deltaX, int deltaY) {
    x0 += deltaX;
    x1 += deltaX;
    y0 += deltaY;
    y1 += deltaY;
}

template<typename T, template<typename U> class Lattice>
bool PostProcessorGenerator2D<T,Lattice>::
    extract(int x0_, int x1_, int y0_, int y1_)
{
    int newX0, newX1, newY0, newY1;
    if ( util::intersect (
                x0, x1, y0, y1,
                x0_, x1_, y0_, y1_,
                newX0, newX1, newY0, newY1 ) )
    {
        x0 = newX0;
        x1 = newX1;
        y0 = newY0;
        y1 = newY1;
        return true;
    }
    else {
        return false;
    }
}


////////////////////// Class LatticeCouplingGenerator2D /////////////////

template<typename T, template<typename U> class Lattice>
LatticeCouplingGenerator2D<T,Lattice>::LatticeCouplingGenerator2D (
        int x0_, int x1_, int y0_, int y1_)
    : x0(x0_), x1(x1_), y0(y0_), y1(y1_)
{ }

template<typename T, template<typename U> class Lattice>
void LatticeCouplingGenerator2D<T,Lattice>::shift(int deltaX, int deltaY) {
    x0 += deltaX;
    x1 += deltaX;
    y0 += deltaY;
    y1 += deltaY;
}

template<typename T, template<typename U> class Lattice>
bool LatticeCouplingGenerator2D<T,Lattice>::extract(int x0_, int x1_, int y0_, int y1_)
{
    int newX0, newX1, newY0, newY1;
    if ( util::intersect (
                x0, x1, y0, y1,
                x0_, x1_, y0_, y1_,
                newX0, newX1, newY0, newY1 ) )
    {
        x0 = newX0;
        x1 = newX1;
        y0 = newY0;
        y1 = newY1;
        return true;
    }
    else {
        return false;
    }
}


////////////////////// Class StatisticsPostProcessor2D //////////////

template<typename T, template<typename U> class Lattice>
StatisticsPostProcessor2D<T,Lattice>::StatisticsPostProcessor2D()
{ }

#ifndef PARALLEL_MODE_OMP
template<typename T, template<typename U> class Lattice>
void StatisticsPostProcessor2D<T,Lattice>::process (
        BlockLattice2D<T,Lattice>& blockLattice )
{
    blockLattice.getStatistics().reset();
}
#endif


#ifdef PARALLEL_MODE_OMP
template<typename T, template<typename U> class Lattice>
void StatisticsPostProcessor2D<T,Lattice>::process (
        BlockLattice2D<T,Lattice>& blockLattice )
{
        #pragma omp parallel
            blockLattice.getStatistics().reset();

        int numCells     = 0;
        T average_rho    = T();
        T average_energy = T();
        T maxU           = T();

        #pragma omp parallel
        {
            #pragma omp critical
            {
                numCells       += blockLattice.getStatistics().getNumCells();
                average_rho    += blockLattice.getStatistics().getAverageRho()
                                *blockLattice.getStatistics().getNumCells();
                average_energy += blockLattice.getStatistics().getAverageEnergy()
                                *blockLattice.getStatistics().getNumCells();
                if (maxU<blockLattice.getStatistics().getMaxU())
                    maxU        = blockLattice.getStatistics().getMaxU();
            }
        }
        if (numCells==0) {
            // avoid division by zero
            average_rho = T();
            average_energy = T();
            maxU = T();
            numCells = 0;
        }
        else {
            average_rho    = average_rho / numCells;
            average_energy = average_energy / numCells;
        }
        #pragma omp parallel
            blockLattice.getStatistics().reset(average_rho,average_energy, maxU, numCells);
}
#endif

template<typename T, template<typename U> class Lattice>
void StatisticsPostProcessor2D<T,Lattice>::
    subscribeReductions(BlockLattice2D<T,Lattice>& blockLattice, Reductor<T>* reductor)
{
    reductor -> subscribeAverage (
                    blockLattice.getStatistics().getNumCells(),
                    blockLattice.getStatistics().getAverageRho() );
    reductor -> subscribeAverage (
                    blockLattice.getStatistics().getNumCells(),
                    blockLattice.getStatistics().getAverageEnergy() );
    reductor -> subscribeMax( blockLattice.getStatistics().getMaxU() );
}


////////////////////// Class StatPPGenerator2D //////////////

template<typename T, template<typename U> class Lattice>
StatPPGenerator2D<T,Lattice>::StatPPGenerator2D()
    : PostProcessorGenerator2D<T,Lattice>(-1,-1,-1,-1)
{ }

template<typename T, template<typename U> class Lattice>
PostProcessor2D<T,Lattice>* StatPPGenerator2D<T,Lattice>::generate() const
{
    return new StatisticsPostProcessor2D<T,Lattice>;
}


template<typename T, template<typename U> class Lattice>
PostProcessorGenerator2D<T,Lattice>*
    StatPPGenerator2D<T,Lattice>::clone() const
{
    return new StatPPGenerator2D;
}


////////////////////// Class PostProcessorGenerator3D /////////////////

template<typename T, template<typename U> class Lattice>
PostProcessorGenerator3D<T,Lattice>::PostProcessorGenerator3D (
        int x0_, int x1_, int y0_, int y1_, int z0_, int z1_)
    : x0(x0_), x1(x1_), y0(y0_), y1(y1_), z0(z0_), z1(z1_)
{ }

template<typename T, template<typename U> class Lattice>
void PostProcessorGenerator3D<T,Lattice>::shift (
        int deltaX, int deltaY, int deltaZ )
{
    x0 += deltaX;
    x1 += deltaX;
    y0 += deltaY;
    y1 += deltaY;
    z0 += deltaZ;
    z1 += deltaZ;
}

template<typename T, template<typename U> class Lattice>
bool PostProcessorGenerator3D<T,Lattice>::
    extract(int x0_, int x1_, int y0_, int y1_, int z0_, int z1_)
{
    int newX0, newX1, newY0, newY1, newZ0, newZ1;
    if ( util::intersect (
                x0, x1, y0, y1, z0, z1,
                x0_, x1_, y0_, y1_, z0_, z1_,
                newX0, newX1, newY0, newY1, newZ0, newZ1 ) )
    {
        x0 = newX0;
        x1 = newX1;
        y0 = newY0;
        y1 = newY1;
        z0 = newZ0;
        z1 = newZ1;
        return true;
    }
    else {
        return false;
    }
}

////////////////////// Class LatticeCouplingGenerator3D /////////////////

template<typename T, template<typename U> class Lattice>
LatticeCouplingGenerator3D<T,Lattice>::LatticeCouplingGenerator3D (
        int x0_, int x1_, int y0_, int y1_, int z0_, int z1_)
    : x0(x0_), x1(x1_), y0(y0_), y1(y1_), z0(z0_), z1(z1_)
{ }

template<typename T, template<typename U> class Lattice>
void LatticeCouplingGenerator3D<T,Lattice>::shift (
        int deltaX, int deltaY, int deltaZ )
{
    x0 += deltaX;
    x1 += deltaX;
    y0 += deltaY;
    y1 += deltaY;
    z0 += deltaZ;
    z1 += deltaZ;
}

template<typename T, template<typename U> class Lattice>
bool LatticeCouplingGenerator3D<T,Lattice>::
    extract(int x0_, int x1_, int y0_, int y1_, int z0_, int z1_)
{
    int newX0, newX1, newY0, newY1, newZ0, newZ1;
    if ( util::intersect (
                x0, x1, y0, y1, z0, z1,
                x0_, x1_, y0_, y1_, z0_, z1_,
                newX0, newX1, newY0, newY1, newZ0, newZ1 ) )
    {
        x0 = newX0;
        x1 = newX1;
        y0 = newY0;
        y1 = newY1;
        z0 = newZ0;
        z1 = newZ1;
        return true;
    }
    else {
        return false;
    }
}


////////////////////// Class StatisticsPostProcessor3D //////////////

template<typename T, template<typename U> class Lattice>
StatisticsPostProcessor3D<T,Lattice>::StatisticsPostProcessor3D()
{ }

#ifndef PARALLEL_MODE_OMP
template<typename T, template<typename U> class Lattice>
void StatisticsPostProcessor3D<T,Lattice>::process (
        BlockLattice3D<T,Lattice>& blockLattice )
{
    blockLattice.getStatistics().reset();
}
#endif

#ifdef PARALLEL_MODE_OMP
template<typename T, template<typename U> class Lattice>
void StatisticsPostProcessor3D<T,Lattice>::process (
        BlockLattice3D<T,Lattice>& blockLattice )
{
        #pragma omp parallel
            blockLattice.getStatistics().reset();

        int numCells     = 0;
        T average_rho    = T();
        T average_energy = T();
        T maxU           = T();

        #pragma omp parallel
        {
            #pragma omp critical
            {
                numCells       += blockLattice.getStatistics().getNumCells();
                average_rho    += blockLattice.getStatistics().getAverageRho()
                                *blockLattice.getStatistics().getNumCells();
                average_energy += blockLattice.getStatistics().getAverageEnergy()
                                *blockLattice.getStatistics().getNumCells();
                if (maxU<blockLattice.getStatistics().getMaxU())
                    maxU        = blockLattice.getStatistics().getMaxU();
            }
        }
        if (numCells==0) {
            // avoid division by zero
            average_rho = T();
            average_energy = T();
            maxU = T();
            numCells = 0;
        }
        else {
            average_rho    = average_rho / numCells;
            average_energy = average_energy / numCells;
        }
        #pragma omp parallel
            blockLattice.getStatistics().reset(average_rho,average_energy, maxU, numCells);
}
#endif

template<typename T, template<typename U> class Lattice>
void StatisticsPostProcessor3D<T,Lattice>::
    subscribeReductions(BlockLattice3D<T,Lattice>& blockLattice, Reductor<T>* reductor)
{
    reductor -> subscribeAverage (
                    blockLattice.getStatistics().getNumCells(),
                    blockLattice.getStatistics().getAverageRho() );
    reductor -> subscribeAverage (
                    blockLattice.getStatistics().getNumCells(),
                    blockLattice.getStatistics().getAverageEnergy() );
    reductor -> subscribeMax( blockLattice.getStatistics().getMaxU() );
}


////////////////////// Class StatPPGenerator3D //////////////

template<typename T, template<typename U> class Lattice>
StatPPGenerator3D<T,Lattice>::StatPPGenerator3D()
    : PostProcessorGenerator3D<T,Lattice>(-1,-1,-1,-1,-1,-1)
{ }

template<typename T, template<typename U> class Lattice>
PostProcessor3D<T,Lattice>* StatPPGenerator3D<T,Lattice>::generate() const {
    return new StatisticsPostProcessor3D<T,Lattice>;
}


template<typename T, template<typename U> class Lattice>
PostProcessorGenerator3D<T,Lattice>* StatPPGenerator3D<T,Lattice>::clone() const {
    return new StatPPGenerator3D;
}




}  // namespace olb

#endif
