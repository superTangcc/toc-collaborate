/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2006, 2007 Mathias J. Krause, Jonas Latt,
 *  Vincent Heuveline
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


#include "olb3D.h"
#ifndef OLB_PRECOMPILED // Unless precompiled version is used,
  #include "olb3D.hh"   // include full template code
#endif

#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>


using namespace olb;
using namespace olb::descriptors;
using namespace olb::graphics;
using namespace std;

typedef double T;

void iniGeometry( SuperLattice3D<T,D3Q19Descriptor>& lattice,
                  LBunits<T> const& converter,
                  Dynamics<T, D3Q19Descriptor>& bulkDynamics,
                  sOnLatticeBoundaryCondition3D<T,D3Q19Descriptor>& bc )
{
    const int nx = converter.getNx();
    const int ny = converter.getNy();
    const int nz = converter.getNz();

    const T omega = converter.getOmega();

    lattice.defineDynamics(0,nx-1, 0,ny-1, 0,nz-1, &bulkDynamics);

    bc.addVelocityBoundary0N(   0,   0,   1,ny-2,   1,nz-2, omega);
    bc.addVelocityBoundary0P(nx-1,nx-1,   1,ny-2,   1,nz-2, omega);
    bc.addVelocityBoundary1N(   1,nx-2,   0,   0,   1,nz-2, omega);
    bc.addVelocityBoundary1P(   1,nx-2,ny-1,ny-1,   1,nz-2, omega);
    bc.addVelocityBoundary2N(   1,nx-2,   1,ny-2,   0,   0, omega);
    bc.addVelocityBoundary2P(   1,nx-2,   1,ny-2,nz-1,nz-1, omega);

    bc.addExternalVelocityEdge0NN(   1,nx-2,   0,   0,   0,   0, omega);
    bc.addExternalVelocityEdge0NP(   1,nx-2,   0,   0,nz-1,nz-1, omega);
    bc.addExternalVelocityEdge0PN(   1,nx-2,ny-1,ny-1,   0,   0, omega);
    bc.addExternalVelocityEdge0PP(   1,nx-2,ny-1,ny-1,nz-1,nz-1, omega);

    bc.addExternalVelocityEdge1NN(   0,   0,   1,ny-2,   0,   0, omega);
    bc.addExternalVelocityEdge1NP(nx-1,nx-1,   1,ny-2,   0,   0, omega);
    bc.addExternalVelocityEdge1PN(   0,   0,   1,ny-2,nz-1,nz-1, omega);
    bc.addExternalVelocityEdge1PP(nx-1,nx-1,   1,ny-2,nz-1,nz-1, omega);

    bc.addExternalVelocityEdge2NN(   0,   0,   0,   0,   1,nz-2, omega);
    bc.addExternalVelocityEdge2NP(   0,   0,ny-1,ny-1,   1,nz-2, omega);
    bc.addExternalVelocityEdge2PN(nx-1,nx-1,   0,   0,   1,nz-2, omega);
    bc.addExternalVelocityEdge2PP(nx-1,nx-1,ny-1,ny-1,   1,nz-2, omega);

    bc.addExternalVelocityCornerNNN(   0,   0,   0, omega);
    bc.addExternalVelocityCornerNNP(   0,   0,nz-1, omega);
    bc.addExternalVelocityCornerNPN(   0,ny-1,   0, omega);
    bc.addExternalVelocityCornerNPP(   0,ny-1,nz-1, omega);
    bc.addExternalVelocityCornerPNN(nx-1,   0,   0, omega);
    bc.addExternalVelocityCornerPNP(nx-1,   0,nz-1, omega);
    bc.addExternalVelocityCornerPPN(nx-1,ny-1,   0, omega);
    bc.addExternalVelocityCornerPPP(nx-1,ny-1,nz-1, omega);


    T vel_a[] = { T(), T(), T()};

    lattice.defineRhoU    (0, nx-1, 0, ny-1, 0, nz-1, (T)1, vel_a);
    lattice.iniEquilibrium(0, nx-1, 0, ny-1, 0, nz-1, (T)1, vel_a);

    T u = converter.getLatticeU();
    T vel_b[] = { u, T(), T()};

    lattice.defineRhoU    (0, nx-1, ny-1, ny-1, 0, nz-1, (T)1, vel_b);
    lattice.iniEquilibrium(0, nx-1, ny-1, ny-1, 0, nz-1, (T)1, vel_b);

    lattice.initialize();
}

void writeVTK(SuperLattice3D<T,D3Q19Descriptor>& sLattice,
              LBunits<T> const& converter, int iter) {

    vector<ScalarField3D<T> > scalar;
    vector<TensorField3D<T,3> > tensor;

    for (int iC=0; iC<sLattice.get_load().size(); iC++) {
        BlockStatistics3D<T,D3Q19Descriptor> statistics(sLattice.get_lattice(iC));
        scalar.push_back(statistics.getPressure() );
        tensor.push_back(statistics.getVelocity() );
    }

    CuboidVTKout3D<T>::writeFlowField (
            createFileName("vtk", iter, 6),
            "Pressure", scalar,
            "Velocity", tensor,
            sLattice.get_cGeometry(), sLattice.get_load(), converter.getDeltaT() );
}

int main(int argc, char **argv) {

    olbInit(&argc, &argv);

    singleton::directories().setOutputDir("./tmp/");

    LBunits<T> converter(
            (T) 1e-1,   // uMax
            (T) 1000.,  // Re
            100,        // N
            1.,         // lx
            1.,         // ly
            1.          // lz
    );
    const T logT     = (T)1.;
    const T vtkSave  = (T)1.;
    const T maxT     = (T)20.;

    writeLogFile(converter, "3D cavity");

    #ifdef PARALLEL_MODE_MPI
        CuboidGeometry3D<T> cGeometry(0, 0, 0, 1, converter.getNx(),
            converter.getNy(), converter.getNz(), singleton::mpi().getSize());
    #else
        CuboidGeometry3D<T> cGeometry(0, 0, 0, 1, converter.getNx(),
            converter.getNy(), converter.getNz(), 7);
    #endif

    cGeometry.printStatistics();

    SuperLattice3D<T, D3Q19Descriptor> sLattice(cGeometry,1);


    ConstRhoBGKdynamics<T, D3Q19Descriptor> bulkDynamics (
        converter.getOmega(), instances::getBulkMomenta<T,D3Q19Descriptor>());


    sOnLatticeBoundaryCondition3D<T,D3Q19Descriptor> sBoundaryCondition(sLattice);
    createInterpBoundaryCondition3D<T,D3Q19Descriptor>(sBoundaryCondition);

    iniGeometry(sLattice, converter, bulkDynamics, sBoundaryCondition);

    int iT;
    for (iT=0; iT*converter.getDeltaT()<maxT; ++iT) {

        if (iT%converter.nStep(logT)==0) {
            cout << "step " << iT
                 << "; t=" << iT*converter.getDeltaT()
                 << "; av energy="
                 << sLattice.getStatistics().getAverageEnergy()
                 << "; av rho="
                 << sLattice.getStatistics().getAverageRho() << endl;
        }

        if (iT%converter.nStep(vtkSave)==0 && iT>0) {
            cout << "Saving VTK file ..." << endl;
            writeVTK(sLattice, converter, iT);
        }

        sLattice.collide();
        sLattice.stream();

        //sLattice.collideAndStream();
    }
    cout << iT << endl;

    return 0;
}

