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
 * The description of a single 2D cuboid -- header file.
 */

#ifndef CUBOID_2D_H
#define CUBOID_2D_H

#include <vector>


/// All OpenLB code is contained in this namespace.
namespace olb {

/// A regular single 2D cuboid is the basic component of a 2D cuboid
/// structure which defines the grid.
/** A cuboid is given with its left lower corner, the number of nodes 
 * in the direction x and y and the distance between two nodes.
 * Among after useful methods a cuboid can divide itself in a given 
 * number of disjoint subcuboids. The number of nodes at the boundary 
 * is minimized.
 *
 * This class is not intended to be derived from.
 */

template<typename T>
class Cuboid2D {
    private:
        /// Global position of the left lower corner of the cuboid
        T   _globPosX, _globPosY;
        /// Distance to the next node
        T   _delta;
        /// Number of nodes in the direction x and y
        int _nX, _nY;
    public:
        /// Constructor
        Cuboid2D() {};
        /// Construction of a cuboid
        Cuboid2D(T globPosX, T globPosY, T delta, int nX, int nY);
        /// Initializes the cuboid
        void init(T globPosX, T globPosY, T delta, int nX, int nY); 

        /// Read access to left lower corner coordinates
        T get_globPosX() const;
        T get_globPosY() const;
        /// Read access to the distance of cuboid nodes
        T get_delta() const;
        /// Read access to cuboid width
        int get_nX() const;
        /// Read access to cuboid height
        int get_nY() const;
        /// Returns the volume of the cuboid
        T get_volume() const;
        /// Returns the number of Nodes in the volume 
        int get_nNodesVolume() const;
        /// Returns the perimeter of the cuboid
        T get_perimeter() const;
        /// Returns the number of Nodes at the perimeter
        int get_nNodesPerimeter() const;
        /// Prints cuboid details
        void print() const;

        /// Checks whether a point (globX/gloxY) is contained in the cuboid
        /// extended with an layer of size overlap*delta
        bool checkPoint(T globX, T globY, int overlap = 0) const;
        /// Checks whether a point (globX/gloxY) is contained and is a node 
        /// in the cuboid extended with an layer of size overlap*delta and 
        /// returns the local active node
        bool checkPoint(T globX, T globY, int &locX, int &locY, int overlap = 0) const;
        /// Checks whether there is an intersection with the cuboid extended 
        /// with an layer of size overlap*delta
        bool checkInters(T globX0, T globX1, T globY0, T globY1, int overlap = 0) const;
        /// Checks whether there is an intersection and returns the local
        /// active node range which can be empty by means of locX0=1, locX1=0,
        /// locY0=1, locY1=0 of the cuboid extended with an layer of size
        /// overlap*delta
        bool checkInters(T globX0, T globX1, T globY0, T globY1, 
                   int &locX0, int &locX1, int &locY0, int &locY1,
                   int overlap = 0) const;

        /// Divides the cuboid in p*q cuboids and add the to the given vector
        void divide(int p, int q, std::vector<Cuboid2D<T> > &childrenC) const;
        /// Divides the cuboid in p cuboids and add the to the given vector
        void divide(int p, std::vector<Cuboid2D<T> > &childrenC) const;
};

}  // namespace olb

#endif
