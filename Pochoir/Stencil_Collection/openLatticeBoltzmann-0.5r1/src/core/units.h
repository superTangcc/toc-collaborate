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

#ifndef UNITS_H
#define UNITS_H

#include "complexGrids/mpiManager/mpiManager.h"
#include "io/parallelIO.h"
#include <string>
#include <fstream>
#include "singleton.h"

namespace olb {

/// Conversion between dimensionless and lattice units with on-lattice boundaries
template<typename T>
class LBunits {
public:
    /// Constructor
    /** \param latticeU_  velocity in lattice units (proportional to Mach number)
     *  \param Re_ Reynolds number
     *  \param N_  resolution (a lattice of size 1 has N_+1 cells)
     *  \param lx_ x-length in dimensionless units (e.g. 1)
     *  \param ly_ y-length in dimensionless units (e.g. 1)
     *  \param lz_ z-length in dimensionless units (e.g. 1)
     */
    LBunits(T latticeU_, T Re_, int resolution_, T lx_, T ly_, T lz_=T() )
        : latticeU(latticeU_), Re(Re_), resolution(resolution_), lx(lx_), ly(ly_), lz(lz_)
    { }
    /// velocity in lattice units (proportional to Mach number)
    T getLatticeU() const { return latticeU; }
    /// Reynolds number
    T getRe() const      { return Re; }
    /// resolution
    int getResolution() const { return resolution; }
    /// x-length in dimensionless units
    T getLx() const      { return lx; }
    /// y-length in dimensionless units
    T getLy() const      { return ly; }
    /// z-length in dimensionless units
    T getLz() const      { return lz; }
    /// lattice spacing in dimensionless units
    T getDeltaX() const  { return (T)1/(T)getResolution(); }
    /// time step in dimensionless units
    T getDeltaT() const  { return getDeltaX()*getLatticeU(); }
    /// conversion from dimensionless to lattice units for space coordinate
    int nCell(T l) const { return (int)(l/getDeltaX()+(T)0.5); }
    /// conversion from dimensionless to lattice units for time coordinate
    int nStep(T t) const { return (int)(t/getDeltaT()+(T)0.5); }
    /// number of lattice cells in x-direction
    int getNx(bool offLattice=false) const { return nCell(lx)+1+(int)offLattice; }
    /// number of lattice cells in y-direction
    int getNy(bool offLattice=false) const { return nCell(ly)+1+(int)offLattice; }
    /// number of lattice cells in z-direction
    int getNz(bool offLattice=false) const { return nCell(lz)+1+(int)offLattice; }
    /// viscosity in lattice units
    T getLatticeNu() const { return getLatticeU()*getResolution()/Re; }
    /// relaxation time
    T getTau() const       { return (T)3*getLatticeNu()+(T)0.5; }
    /// relaxation frequency
    T getOmega() const     { return (T)1 / getTau(); }
private:
    T latticeU, Re;
    int resolution;
    T lx, ly, lz;
};

template<typename T>
void writeLogFile(LBunits<T> const& converter,
                  std::string const& title)
{
    std::string fullName = singleton::directories().getLogOutDir() + "olbLog.dat";
    olb_ofstream ofile(fullName.c_str());
    ofile << title << "\n\n";
    ofile << "Velocity in lattice units: u=" << converter.getLatticeU() << "\n";
    ofile << "Reynolds number:           Re=" << converter.getRe() << "\n";
    ofile << "Lattice resolution:        N=" << converter.getResolution() << "\n";
    ofile << "Extent of the system:      lx=" << converter.getLx() << "\n";
    ofile << "Extent of the system:      ly=" << converter.getLy() << "\n";
    ofile << "Extent of the system:      lz=" << converter.getLz() << "\n";
    ofile << "Grid spacing deltaX:       dx=" << converter.getDeltaX() << "\n";
    ofile << "Time step deltaT:          dt=" << converter.getDeltaT() << "\n";
}

}  // namespace olb

#endif
