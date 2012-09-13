/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007 Mathias Krause
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


#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

#include <vector>
#include <map>

namespace olb {

class loadBalancer {
    private:
        int locChunkSize;
        int firstGlobNum;
        int lastGlobNum;
        std::map<int,int> _loc;
        std::vector<int> _glob;
        std::map<int,int> _rank;
    public:
        loadBalancer() {};
        loadBalancer(int rank, int size, int globChunkSize, int offset);
        void init_chunkD(int rank, int size, int globChunkSize, int offset);
        int get_locChunkSize() const;
        int get_firstGlobNum() const;
        int get_lastGlobNum() const;
        int loc(const int& glob);
        int loc(int glob) const;
        int glob(int loc) const;
        int rank(const int& glob);
        int rank(int glob) const;
        int size();
        int size() const;
    }; 

}  // namespace olb

#endif 
