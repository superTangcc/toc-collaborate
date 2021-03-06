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


    #ifdef PARALLEL_MODE_OMP

        #include <omp.h>
        #include "ompManager.h"

        void ompManager::init() {
            set_dynamic(0);
            size = omp_get_max_threads();
            rank = omp_get_thread_num();
        }

        int ompManager::get_size() const {
            return size;
        }

        int ompManager::get_rank() const { 
            return rank; 
        }

        void ompManager::set_dynamic(int dynamicThreads) { 
            omp_set_dynamic(dynamicThreads);
        }

        ompManager omp;

    #endif


