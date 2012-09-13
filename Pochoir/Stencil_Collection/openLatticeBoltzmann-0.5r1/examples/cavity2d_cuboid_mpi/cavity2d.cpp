/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2006 Mathias J. Krause, Jonas Latt, Vincent Heuveline
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


#include "olb2D.h"
#ifndef OLB_PRECOMPILED // Unless precompiled version is used,
  #include "olb2D.hh"   // include full template code
#endif

#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include "olb2D.h"


using namespace olb;
using namespace olb::descriptors;
using namespace olb::graphics;
using namespace std;

typedef double T;

void iniGeometry( SuperLattice2D<T,D2Q9Descriptor>& lattice,
                  LBunits<T> const& converter,
                  Dynamics<T, D2Q9Descriptor>& bulkDynamics,
                  sOnLatticeBoundaryCondition2D<T,D2Q9Descriptor>& bc )
{
    const int nx = converter.getNx();
    const int ny = converter.getNy();

    const T omega = converter.getOmega();

    lattice.defineDynamics(0,nx-1, 0,ny-1, &bulkDynamics);

    bc.addVelocityBoundary0N(   0,   0,   1,ny-2, omega);
    bc.addVelocityBoundary0P(nx-1,nx-1,   1,ny-2, omega);
    bc.addVelocityBoundary1N(   1,nx-2,   0,   0, omega);
    bc.addVelocityBoundary1P(   1,nx-2,ny-1,ny-1, omega);

    bc.addExternalVelocityCornerNN(   0,   0, omega);
    bc.addExternalVelocityCornerNP(   0,ny-1, omega);
    bc.addExternalVelocityCornerPN(nx-1,   0, omega);
    bc.addExternalVelocityCornerPP(nx-1,ny-1, omega);

    T vel_a[] = { T(), T()};

    lattice.defineRhoU    (0, nx-1, 0, ny-1, (T)1, vel_a);
    lattice.iniEquilibrium(0, nx-1, 0, ny-1, (T)1, vel_a);

    T u = converter.getLatticeU();
    T vel_b[] = { u, T() };

    lattice.defineRhoU    (1, nx-2, ny-1, ny-1, (T)1, vel_b);
    lattice.iniEquilibrium(1, nx-2, ny-1, ny-1, (T)1, vel_b);

    lattice.initialize();
}

void writeVTK(SuperLattice2D<T,D2Q9Descriptor>& sLattice,
              LBunits<T> const& converter, int iter)
{
    vector<ScalarField2D<T> > scalar;
    vector<TensorField2D<T,2> > tensor;

    for (int iC=0; iC<sLattice.get_load().size(); iC++) {
        BlockStatistics2D<T,D2Q9Descriptor> statistics(sLattice.get_lattice(iC));
        scalar.push_back(statistics.getPressure() );
        tensor.push_back(statistics.getVelocity() );
    }

    CuboidVTKout2D<T>::writeFlowField (
            createFileName("vtk", iter, 6),
            "Pressure", scalar,
            "Velocity", tensor,
            sLattice.get_cGeometry(), sLattice.get_load(), converter.getDeltaT() );

}

int main(int argc, char **argv) {

    olbInit(&argc, &argv);

    singleton::directories().setOutputDir("./tmp/");

    LBunits<T> converter(
            (T) 1./128., // uMax
            (T) 1000.,   // Re
            128,         // N
            1.,          // lx
            1.           // ly 
    );
    const T logT     = (T)1.;
    const T vtkSave  = (T)1.;
    const T maxT     = (T)30.;

    writeLogFile(converter, "2D cavity");

    #ifdef PARALLEL_MODE_MPI
        CuboidGeometry2D<T> cGeometry(0, 0, 1, converter.getNx(),
                                     converter.getNy(), singleton::mpi().getSize());
    #else
        CuboidGeometry2D<T> cGeometry(0, 0, 1, converter.getNx(),
                                     converter.getNy(), 7);
    #endif

    cGeometry.printStatistics();


    SuperLattice2D<T, D2Q9Descriptor> sLattice(cGeometry,1);


    ConstRhoBGKdynamics<T, D2Q9Descriptor> bulkDynamics (
        converter.getOmega(), instances::getBulkMomenta<T,D2Q9Descriptor>());


    sOnLatticeBoundaryCondition2D<T,D2Q9Descriptor> sBoundaryCondition(sLattice);
    createInterpBoundaryCondition2D<T,D2Q9Descriptor>(sBoundaryCondition);

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
