/*
 **********************************************************************************
 *  Copyright (C) 2010-2011  Massachusetts Institute of Technology
 *  Copyright (C) 2010-2011  Yuan Tang <yuantang@csail.mit.edu>
 *                           Charles E. Leiserson <cel@mit.edu>
 *   
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   Suggestsions:                  yuantang@csail.mit.edu
 *   Bugs:                          yuantang@csail.mit.edu
 *
 *********************************************************************************
 */

/* test bench for 2D checkerboard style stencil in Pochoir
 */
#include <cstdio>
#include <cstddef>
// #include <iostream>
#include <cstdlib>
#include <sys/time.h>
#include <cmath>

#include <pochoir.hpp>

// using namespace std;
#define TIMES 1
#define TOLERANCE (1e-6)

void check_result(int t, int i, double a, double b)
{
    if (abs(a - b) < TOLERANCE) {
    //    printf("a(%d, %d) == b(%d, %d) == %f : passed!\n", t, i, t, i, a);
    } else {
        printf("a(%d, %d) = %f, b(%d, %d) = %f : FAILED!\n", t, i, a, t, i, b);
    }
}

Pochoir_Boundary_1D(periodic_1D, arr, t, i)
    const int arr_size_0 = arr.size(0);

    int new_i = (i >= arr_size_0) ? (i - arr_size_0) : (i < 0 ? i + arr_size_0 : i);

    return arr.get(t, new_i);
Pochoir_Boundary_End

Pochoir_Boundary_1D(aperiodic_1D, arr, t, i)
    return 0;
Pochoir_Boundary_End

#define N 55
#define T 55

int main(int argc, char * argv[])
{
    const int BASE = 1024;
    int t;
    struct timeval start, end;
    double min_tdiff = INF;
    /* the 1D spatial dimension has 'N' points */
    // int N = 0, T = 0;
    double umin, umax;
    char pochoir_plan_fname[100];

    if (argc < 3) {
        printf("argc < 3, quit! \n");
        exit(1);
    }
    // N = StrToInt(argv[1]);
    // T = StrToInt(argv[2]);
    printf("N = %d, T = %d\n", N, T);
    Pochoir_Shape_1D oned_3pt[] = {{0, 0}, {-1, 0}, {-1, -1}, {-1, 1}};
    Pochoir_Shape_1D shape_exclusive_0[] = {{0, 0}, {-1, -1}, {-1, 0}, {-1, 1}};
    Pochoir_Shape_1D shape_exclusive_1[] = {{0, 0}, {-1, -1}, {-1, 0}, {-1, 1}};
    Pochoir_Shape_1D shape_inclusive_0[] = {{0, 0}, {-1, -1}, {-1, 0}, {-1, 1}};
    Pochoir_Shape_1D shape_inclusive_1[] = {{0, 0}, {-1, -1}, {-1, 0}, {-1, 1}};
    Pochoir_Shape_1D shape_tiny_inclusive_0[] = {{0, 0}, {-1, -1}, {-1, 0}, {-1, 1}};
    Pochoir_Shape_1D shape_tiny_inclusive_1[] = {{0, 0}, {-1, -1}, {-1, 0}, {-1, 1}};
    Pochoir_Array_1D(double) a(N);
    Pochoir_Array_1D(double) b(N);
    Pochoir_1D overlap;
    a.Register_Boundary(aperiodic_1D);
    b.Register_Shape(oned_3pt);
    b.Register_Boundary(aperiodic_1D);

    Pochoir_Guard_1D_Begin(g_exclusive_0, t, i)
        if (i < N/2)
            return true;
        else
            return false;
    Pochoir_Guard_1D_End(g_exclusive_0)

    Pochoir_Guard_1D_Begin(g_exclusive_1, t, i)
        if (i >= N/2) 
            return true;
        else 
            return false;
    Pochoir_Guard_1D_End(g_exclusive_1)

    Pochoir_Guard_1D_Begin(g_inclusive_0, t, i)
        if (i < N/2 && t < T/2)
            return true;
        else
            return false;
    Pochoir_Guard_1D_End(g_inclusive_0)

    Pochoir_Guard_1D_Begin(g_inclusive_1, t, i)
        if (i >= N/4 && i < N/3 && t < T*2/3)
            return true;
        else
            return false;
    Pochoir_Guard_1D_End(g_inclusive_1);

    Pochoir_Guard_1D_Begin(g_tiny_inclusive_0, t, i)
        if (i >= 1 && i < 5 && t > 1 && t <= 2)
            return true;
        else
            return false;
    Pochoir_Guard_1D_End(g_tiny_inclusive_0)

    Pochoir_Guard_1D_Begin(g_tiny_inclusive_1, t, i)
        if (i > 5 && i <= 10 && t > 2 && t < 4)
            return true;
        else
            return false;
    Pochoir_Guard_1D_End(g_tiny_inclusive_1)

    Pochoir_Kernel_1D_Begin(k_exclusive_0, t, i)
#if DEBUG
        printf("<k_exclusive_0> : a(%d, %d)\n", t, i);
#endif
        a(t, i) = 0.11 * a(t-1, i-1) + 0.15 * a(t-1, i) + 0.185 * a(t-1, i+1) + 0.8;
    Pochoir_Kernel_1D_End(k_exclusive_0, shape_exclusive_0)

    Pochoir_Kernel_1D_Begin(k_exclusive_1, t, i)
#if DEBUG
        printf("<k_exclusive_1> : a(%d, %d)\n", t, i);
#endif
        a(t, i) = 0.21 * a(t-1, i-1) + 0.25 * a(t-1, i) + 0.285 * a(t-1, i+1) + 0.8;
    Pochoir_Kernel_1D_End(k_exclusive_1, shape_exclusive_1)

    Pochoir_Kernel_1D_Begin(k_inclusive_0, t, i)
#if DEBUG
        printf("<k_inclusive_0> : a(%d, %d)\n", t, i);
#endif
        a(t, i) = 0.31 * a(t-1, i-1) - 0.35 * a(t-1, i) + 0.385 * a(t-1, i+1) - 0.8;
    Pochoir_Kernel_1D_End(k_inclusive_0, shape_inclusive_0)

    Pochoir_Kernel_1D_Begin(k_inclusive_1, t, i)
#if DEBUG
        printf("<k_inclusive_1> : a(%d, %d)\n", t, i);
#endif
        a(t, i) = 0.41 * a(t-1, i-1) - 0.45 * a(t-1, i) + 0.485 * a(t-1, i+1) - 0.8;
    Pochoir_Kernel_1D_End(k_inclusive_1, shape_inclusive_1)

    Pochoir_Kernel_1D_Begin(k_tiny_inclusive_0, t, i)
#if DEBUG
        printf("<k_tiny_inclusive_0> : a(%d, %d)\n", t, i);
#endif
        a(t, i) = 0.51 * a(t-1, i-1) + 0.55 * a(t-1, i) - 0.585 * a(t-1, i+1) + 0.8;
    Pochoir_Kernel_1D_End(k_tiny_inclusive_0, shape_tiny_inclusive_0)

    Pochoir_Kernel_1D_Begin(k_tiny_inclusive_1, t, i)
#if DEBUG
        printf("<k_tiny_inclusive_1> : a(%d, %d)\n", t, i);
#endif
        a(t, i) = 0.61 * a(t-1, i-1) + 0.65 * a(t-1, i) - 0.685 * a(t-1, i+1) + 0.8;
    Pochoir_Kernel_1D_End(k_tiny_inclusive_1, shape_tiny_inclusive_1)

    /* this is a 2D checkerboard style tiling of the entire rectangular region/domain */
    overlap.Register_Tile_Kernels(g_exclusive_0, k_exclusive_0);
    overlap.Register_Tile_Kernels(g_exclusive_1, k_exclusive_1);
    overlap.Register_Tile_Kernels(g_inclusive_0, k_inclusive_0);
    overlap.Register_Tile_Kernels(g_inclusive_1, k_inclusive_1);
    overlap.Register_Tile_Kernels(g_tiny_inclusive_0, k_tiny_inclusive_0);
    overlap.Register_Tile_Kernels(g_tiny_inclusive_1, k_tiny_inclusive_1);
    overlap.Register_Array(a);

    /* initialization */
    for (int i = 0; i < N; ++i) {
        a(0, i) = 1.0 * (rand() % BASE);
        b(0, i) = a(0, i);
    }

    Pochoir_Plan<1> & l_plan = overlap.Gen_Plan(T);
    sprintf(pochoir_plan_fname, "pochoir_%d_%d.dat", N, T);
    overlap.Store_Plan(pochoir_plan_fname, l_plan);
    Pochoir_Plan<1> & ll_plan = overlap.Load_Plan(pochoir_plan_fname);
    for (int times = 0; times < TIMES; ++times) {
        gettimeofday(&start, 0);
        overlap.Run(ll_plan);
        gettimeofday(&end, 0);
        min_tdiff = min(min_tdiff, (1.0e3 * tdiff(&end, &start)));
    }
    printf("Pochoir time = %.6f milliseconds\n", min_tdiff);

    printf("\n--------------------------------------------------------------------------\n");
    min_tdiff = INF;
    /* cilk_for */
    for (int times = 0; times < TIMES; ++times) {
        gettimeofday(&start, 0);
        for (int t = 1; t < T + 1; ++t) {
            cilk_for (int i = 0; i < N; ++i) {
                if (g_exclusive_0(t, i)) {
                    /* k_exclusive_0 */
#if DEBUG
                    printf("<k_exclusive_0> : b(%d, %d)\n", t, i);
#endif
                    b(t, i) = 0.11 * b(t-1, i-1) + 0.15 * b(t-1, i) + 0.185 * b(t-1, i+1) + 0.8;
                } 
                if (g_exclusive_1(t, i)) {
                    /* k_exclusive_1 */
#if DEBUG
                    printf("<k_exclusive_1> : b(%d, %d)\n", t, i);
#endif
                    b(t, i) = 0.21 * b(t-1, i-1) + 0.25 * b(t-1, i) + 0.285 * b(t-1, i+1) + 0.8;
                }
                if (g_inclusive_0(t, i)) {
                    /* k_inclusive_0 */
#if DEBUG
                    printf("<k_inclusive_0> : b(%d, %d)\n", t, i);
#endif
                    b(t, i) = 0.31 * b(t-1, i-1) - 0.35 * b(t-1, i) + 0.385 * b(t-1, i+1) - 0.8;
                }
                if (g_inclusive_1(t, i)) {
                    /* k_inclusive_1 */
#if DEBUG
                    printf("<k_inclusive_1> : b(%d, %d)\n", t, i);
#endif
                    b(t, i) = 0.41 * b(t-1, i-1) - 0.45 * b(t-1, i) + 0.485 * b(t-1, i+1) - 0.8;
                }
                if (g_tiny_inclusive_0(t, i)) {
                    /* k_tiny_inclusive_0 */
#if DEBUG
                    printf("<k_tiny_inclusive_0> : b(%d, %d)\n", t, i);
#endif
                    b(t, i) = 0.51 * b(t-1, i-1) + 0.55 * b(t-1, i) - 0.585 * b(t-1, i+1) + 0.8;
                }
                if (g_tiny_inclusive_1(t, i)) {
                    /* k_tiny_inclusive_1 */
#if DEBUG
                    printf("<k_tiny_inclusive_1> : b(%d, %d)\n", t, i);
#endif
                    b(t, i) = 0.61 * b(t-1, i-1) + 0.65 * b(t-1, i) - 0.685 * b(t-1, i+1) + 0.8;
                }
            }
        }
        gettimeofday(&end, 0);
        min_tdiff = min(min_tdiff, (1.0e3 * tdiff(&end, &start)));
    }
    printf("Parallel Loop time = %.6f milliseconds\n", min_tdiff);
//    std::cout << "Parallel Loop time : " << min_tdiff << " ms" << std::endl;

    /* check results! */
    t = T;
    for (int i = 0; i < N; ++i) {
        check_result(t, i, a(t, i), b(t, i));
    } 

    return 0;
}

