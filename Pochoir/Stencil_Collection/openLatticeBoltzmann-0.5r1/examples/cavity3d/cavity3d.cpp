/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2006 Jonas Latt
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
#define DESCRIPTOR D3Q19Descriptor

void iniGeometry( BlockStructure3D<T,DESCRIPTOR>& lattice,
                  LBunits<T> const& converter,
                  Dynamics<T, DESCRIPTOR>& bulkDynamics,
                  OnLatticeBoundaryCondition3D<T,DESCRIPTOR>& bc )
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

    for (int iX=0; iX<nx; ++iX) {
        for (int iY=0; iY<ny; ++iY) {
            for (int iZ=0; iZ<nz; ++iZ) {
                T vel[] = { T(), T(), T() };
                lattice.get(iX,iY,iZ).defineRhoU((T)1, vel);
                lattice.get(iX,iY,iZ).iniEquilibrium((T)1, vel);
            }
        }
    }

    for (int iX=0; iX<nx; ++iX) {
        for (int iZ=0; iZ<nz; ++iZ) {
            T u = sqrt((T)2)/(T)2 * converter.getLatticeU();
            T vel[] = { u, T(), u };
            lattice.get(iX,ny-1,iZ).defineRhoU((T)1, vel);
            lattice.get(iX,ny-1,iZ).iniEquilibrium((T)1, vel);
        }
    }

    lattice.initialize();
}

void writeGifs(BlockStructure3D<T,DESCRIPTOR>& lattice,
               LBunits<T> const& converter, int iter)
{
    const int imSize = 600;
    int nz = converter.getNz();

    ImageWriter<T> imageWriter("leeloo");
    DataAnalysisBase3D<T,DESCRIPTOR> const& analysis = lattice.getDataAnalysis();
    imageWriter.writeScaledGif(createFileName("uz", iter, 6),
                               analysis.getVelocityNorm().sliceZ(nz/2),
                               imSize, imSize );
}

void writeVTK(BlockStructure3D<T,DESCRIPTOR>& lattice,
              LBunits<T> const& converter, int iter)
{
    DataAnalysisBase3D<T,DESCRIPTOR> const& analysis = lattice.getDataAnalysis();
    T dx = converter.getDeltaX();
    T dt = converter.getDeltaT();
    VtkImageOutput3D<T> vtkOut(createFileName("vtk", iter, 6), dx);
    vtkOut.writeData<float>(analysis.getVorticityNorm(), "vorticityNorm", (T)1/dt);
    vtkOut.writeData<3,float>(analysis.getVelocity(), "velocity", dx/dt);
}

int main(int argc, char* argv[]) {
    olbInit(&argc, &argv);
    singleton::directories().setOutputDir("./tmp/");

    LBunits<T> converter(
            (T) 1e-2,  // uMax
            (T) 100.,  // Re
            60,        // N
            1.,        // lx
            1.,        // ly
            1.         // lz
    );
    const T logT     = (T)1/(T)100;
    const T imSave   = (T)1/(T)40;
    const T vtkSave  = (T)1.;
    const T maxT     = (T)10.1;

    writeLogFile(converter, "3D diagonal cavity");

#ifndef PARALLEL_MODE_MPI  // sequential program execution
    BlockLattice3D<T, DESCRIPTOR> lattice(converter.getNx(), converter.getNy(), converter.getNz() );
#else                      // parallel program execution
    MultiBlockLattice3D<T, DESCRIPTOR> lattice (
        createRegularDataDistribution( converter.getNx(), converter.getNy(), converter.getNz() ) );
#endif

    ConstRhoBGKdynamics<T, DESCRIPTOR> bulkDynamics (
                      converter.getOmega(),
                      instances::getBulkMomenta<T,DESCRIPTOR>()
    );

    OnLatticeBoundaryCondition3D<T,DESCRIPTOR>* boundaryCondition
        = createInterpBoundaryCondition3D(lattice);

    iniGeometry(lattice, converter, bulkDynamics, *boundaryCondition);

    int iT=0;
    for (iT=0; iT<converter.nStep(maxT); ++iT) {
        if (iT%converter.nStep(logT)==0) {
            cout << "step " << iT
                 << "; t=" << iT*converter.getDeltaT()
                 << "; av energy="
                 << lattice.getStatistics().getAverageEnergy()
                 << "; av rho="
                 << lattice.getStatistics().getAverageRho() << endl;
        }

        if (iT%converter.nStep(imSave)==0 && iT>0) {
            cout << "Saving Gif ..." << endl;
            writeGifs(lattice, converter, iT);
        }

        if (iT%converter.nStep(vtkSave)==0 && iT>0) {
            cout << "Saving VTK file ..." << endl;
            writeVTK(lattice, converter, iT);
        }

        lattice.collideAndStream(false);
    }
    cout << iT << endl;

    delete boundaryCondition;
}
