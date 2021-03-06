/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2008 Orestis Malaspinas, Andrea Parmigiani
 *  Address: EPFL, STI-LIN Station 9, 1015 Lausanne, Switzerland 
 *  E-mail: orestis.malaspinas@epfl.ch
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

#include "olb2D.h"
#include "olb2D.hh"
#include <cstdlib>
#include <iostream>

using namespace olb;
using namespace olb::descriptors;
using namespace olb::graphics;
using namespace std;

typedef double T;
#define DESCRIPTOR ForcedShanChenD2Q9Descriptor


void iniGeometry( BlockStructure2D<T, DESCRIPTOR>& latticeOne,
                  BlockStructure2D<T, DESCRIPTOR>& latticeTwo,
                  Dynamics<T, DESCRIPTOR>& bulkDynamics1,
                  Dynamics<T, DESCRIPTOR>& bulkDynamics2,
                  Dynamics<T, DESCRIPTOR>& bounceBackRho0,
                  Dynamics<T, DESCRIPTOR>& bounceBackRho1,
                  T force
                )
{
    // The setup is: periodicity along horizontal direction, bounce-back on top
    // and bottom. The upper half is initially filled with fluid 1 + random noise,
    // and the lower half with fluid 2. Only fluid 1 experiences a forces,
    // directed downwards.
    T noise      = 1.e-2;
    
    int nx = latticeOne.getNx();
    int ny = latticeOne.getNy();
    
    latticeOne.defineDynamics(0,nx-1, 0,ny-1, &bulkDynamics1);
    latticeTwo.defineDynamics(0,nx-1, 0,ny-1, &bulkDynamics2);

    latticeOne.defineDynamics(0,nx-1, 0,0, &bounceBackRho0);
    latticeTwo.defineDynamics(0,nx-1, 0,0, &bounceBackRho1);
    latticeOne.defineDynamics(0,nx-1, ny-1,ny-1, &bounceBackRho1);
    latticeTwo.defineDynamics(0,nx-1, ny-1,ny-1, &bounceBackRho0);
   
    for (int iX=0; iX<nx; ++iX) {
        for (int iY=0; iY<ny; ++iY) {
            T f[2] = {0.,-force};
            T zeroVelocity[2] = {0.,0.};
            T noForce[2] = {0.,0.};
            T rho1 = (T)1;
            T rho2 = (T)1;
            if (iY>ny/2) {
                rho2 = 0.;
                rho1 += (double)random()/(double)RAND_MAX * noise;
                rho1 += force*DESCRIPTOR<T>::invCs2* ((T)ny - (T)iY - (T)ny/(T)2);
            }
            else {
                rho1 = 0.;
            }

            Cell<T,DESCRIPTOR>& cell1 = latticeOne.get(iX,iY);
            cell1.defineRhoU(rho1, zeroVelocity);
            cell1.iniEquilibrium(rho1, zeroVelocity);
            cell1.defineExternalField (
                    DESCRIPTOR<T>::ExternalField::forceBeginsAt,
                    DESCRIPTOR<T>::ExternalField::sizeOfForce, f );
        
            Cell<T,DESCRIPTOR>& cell2 = latticeTwo.get(iX,iY);
            cell2.defineRhoU(rho2, zeroVelocity);
            cell2.iniEquilibrium(rho2, zeroVelocity);
            cell2.defineExternalField (
                    DESCRIPTOR<T>::ExternalField::forceBeginsAt,
                    DESCRIPTOR<T>::ExternalField::sizeOfForce, noForce );
        }
    }
    
    latticeOne.initialize();
    latticeTwo.initialize();
}

void plotStatistics(BlockStructure2D<T, DESCRIPTOR>&    latticeTwo,
                    BlockStructure2D<T, DESCRIPTOR>&    latticeOne, int iT)
{
	cout << "Writing Gif\n";
    ImageWriter<T> imageCreator("leeloo.map");
    imageCreator.writeScaledGif(createFileName("p", iT, 6), latticeOne.getDataAnalysis().getPressure());
}

int main(int argc, char *argv[])
{
    olbInit(&argc, &argv);
    singleton::directories().setOutputDir("./tmp/");
    
    const T omega1 = 1.0;
    const T omega2 = 1.0;
    const int nx   = 600;
    const int ny   = 400;
    const T G      = 0.1;
    T force        = 0.15/(T)ny;
    const int maxIter  = 1000000;
    const int saveIter = 100;
    const int statIter = 10;

#ifndef PARALLEL_MODE_MPI  // sequential program execution
    MultiDataDistribution2D distribution = createRegularDataDistribution( nx, ny, 1, 1, 1 );
#else                      // parallel program execution
    MultiDataDistribution2D distribution = createRegularDataDistribution( nx, ny );
#endif
    // Use a multi-block lattice even in sequential program execution. In this
    //   way, it is easier to have periodic boundaries, because one can
    //   access periodic data from the lattice envelope
    MultiBlockLattice2D<T, DESCRIPTOR> latticeOne(distribution);
    MultiBlockLattice2D<T, DESCRIPTOR> latticeTwo(distribution);

    BGKdynamics<T, DESCRIPTOR> bulkDynamics1 (
                omega1, instances::getExternalVelocityMomenta<T,DESCRIPTOR>() );
    BGKdynamics<T, DESCRIPTOR> bulkDynamics2 (
                omega2, instances::getExternalVelocityMomenta<T,DESCRIPTOR>() );

    // A bounce-back node with fictitious density 1,
    //   which is experienced by the partner fluid
    BounceBack<T, DESCRIPTOR> bounceBackRho1( 1. );
    // A bounce-back node with fictitious density 0,
    //   which is experienced by the partner fluid
    BounceBack<T, DESCRIPTOR> bounceBackRho0( 0. );
    
    vector<SpatiallyExtendedObject2D* > partnerForOne;
    partnerForOne.push_back(&latticeTwo);
    
    ForcedShanChenCouplingGenerator2D<T,DESCRIPTOR> coupling(0,nx-1,1,ny-2,G);
    latticeOne.addLatticeCoupling(coupling, partnerForOne);

    iniGeometry(latticeOne, latticeTwo, bulkDynamics1, bulkDynamics2,
                bounceBackRho0, bounceBackRho1, force);
	
    int iT = 0;
    cout << "starting simulation" << endl;
    for (iT=0; iT<maxIter; ++iT) {
        if (iT%statIter==0 && iT > 0) {
            cout << "average rho fluid one = "   << latticeOne.getStatistics().getAverageRho();
            cout << ", average rho fluid two = " << latticeTwo.getStatistics().getAverageRho() <<"\n";
        }
        if (iT%saveIter==0) {
            plotStatistics(latticeTwo, latticeOne, iT);
        }

        latticeOne.collideAndStream(true);
        latticeTwo.collideAndStream(true);

        latticeOne.executeCoupling();
        latticeTwo.executeCoupling();
    }
}

