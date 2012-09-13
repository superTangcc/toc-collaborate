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

#ifndef FINITE_DIFFERENCE_H
#define FINITE_DIFFERENCE_H

namespace olb {

    namespace fd {

        template<typename T>
        T centralGradient(T u_p1, T u_m1) {
            return (u_p1 - u_m1) / (T)2;
        }

        template<typename T>
        T boundaryGradient(T u_0, T u_1, T u_2) {
            return (-(T)3*u_0 + (T)4*u_1 - (T)1*u_2) / (T)2;
        }

        template<typename T>
        T boundaryZeroGradient(T u_1, T u_2) {
            return (T)4/(T)3*u_1 - (T)1/(T)3*u_2;
        }

    }  // namespace fd

}  // namespace olb


#endif
