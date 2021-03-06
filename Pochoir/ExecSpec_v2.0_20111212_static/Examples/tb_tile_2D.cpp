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

int main(int argc, char * argv[])
{
    const int BASE = 1024;
    int t;
    struct timeval start, end;
    double min_tdiff = INF;
    /* the 1D spatial dimension has 'N' points */
    int N = 0, T = 0;
    double umin, umax;
    char pochoir_plan_file_name[100];

    if (argc < 3) {
        printf("argc < 3, quit! \n");
        exit(1);
    }
    N = StrToInt(argv[1]);
    T = StrToInt(argv[2]);
    printf("N = %d, T = %d\n", N, T);
    Pochoir_Shape_1D oned_3pt[] = {{0, 0}, {-1, 0}, {-1, -1}, {-1, 1}};
    Pochoir_Shape_1D shape_k0[] = {{0, 0}, {-1, -1}, {-1, 0}, {-1, 1}};
    Pochoir_Shape_1D shape_k1[] = {{0, 0}, {-1, -1}, {-1, 0}, {-1, 1}};
    Pochoir_Shape_1D shape_k2[] = {{0, 0}, {-1, -1}, {-1, 0}, {-1, 1}};
    Pochoir_Shape_1D shape_k3[] = {{0, 0}, {-1, -1}, {-1, 0}, {-1, 1}};
    Pochoir_Array_1D(double) a(N);
    Pochoir_Array_1D(double) b(N);
    Pochoir_1D leap_frog;
    a.Register_Boundary(periodic_1D);
    b.Register_Shape(oned_3pt);
    b.Register_Boundary(periodic_1D);

    Pochoir_Guard_1D_Begin(guard_interior, t, i)
        if (t > T/2 && i > N/2) {
            /* up right rectangle */
            return true;
        } else {
            return false;
        }
    Pochoir_Guard_1D_End(guard_interior)

    Pochoir_Guard_1D_Begin(guard_exterior, t, i)
        return (!guard_interior(t, i));
    Pochoir_Guard_1D_End(guard_exterior)

    Pochoir_Kernel_1D_Begin(k0, t, i)
#if DEBUG
        printf("<i0> a(%d, %d) = f(a(%d, %d) <%.3f>, a(%d, %d) <%.3f>, a(%d, %d) <%.3f>)\n", t, i, t-1, i-1, a(t-1, i-1), t-1, i, a(t-1, i), t-1, i+1, a(t-1, i+1));
        printf("<i0> a(%d, %d) : %.3f -> ", t, i, a(t, i));
#endif
        a(t, i) = 0.1 * a(t-1, i-1) + 0.15 * a(t-1, i) + 0.189 * a(t-1, i+1) + 0.8;
#if DEBUG
        printf("%.3f\n", a(t, i));
#endif
    Pochoir_Kernel_1D_End(k0, shape_k0)

    Pochoir_Kernel_1D_Begin(k1, t, i)
#if DEBUG
        printf("<i1> a(%d, %d) = f(a(%d, %d) <%.3f>, a(%d, %d) <%.3f>, a(%d, %d) <%.3f>)\n", t, i, t-1, i-1, a(t-1, i-1), t-1, i, a(t-1, i), t-1, i+1, a(t-1, i+1));
        printf("<i1> a(%d, %d) : %.3f -> ", t, i, a(t, i));
#endif
        a(t, i) = 0.2 * a(t-1, i-1) + 0.25 * a(t-1, i) + 0.281 * a(t-1, i+1) + 0.8;
#if DEBUG
        printf("%.3f\n", a(t, i));
#endif
    Pochoir_Kernel_1D_End(k1, shape_k1)

    Pochoir_Kernel_1D_Begin(k2, t, i)
#if DEBUG
        printf("<i2> a(%d, %d) = f(a(%d, %d) <%.3f>, a(%d, %d) <%.3f>, a(%d, %d) <%.3f>)\n", t, i, t-1, i-1, a(t-1, i-1), t-1, i, a(t-1, i), t-1, i+1, a(t-1, i+1));
        printf("<i2> a(%d, %d) : %.3f -> ", t, i, a(t, i));
#endif
        a(t, i) = 0.3 * a(t-1, i-1) - 0.35 * a(t-1, i) - 0.389 * a(t-1, i+1) - 0.8;
#if DEBUG
        printf("%.3f\n", a(t, i));
#endif
    Pochoir_Kernel_1D_End(k2, shape_k2)

    Pochoir_Kernel_1D_Begin(k3, t, i)
#if DEBUG
        printf("<e0> a(%d, %d) = f(a(%d, %d) <%.3f>, a(%d, %d) <%.3f>, a(%d, %d) <%.3f>)\n", t, i, t-1, i-1, a(t-1, i-1), t-1, i, a(t-1, i), t-1, i+1, a(t-1, i+1));
        printf("<e0> a(%d, %d) : %.3f -> ", t, i, a(t, i));
#endif
        a(t, i) = 0.4 * a(t-1, i-1) - 0.45 * a(t-1, i) - 0.489 * a(t-1, i+1) - 0.4;
#if DEBUG
        printf("%.3f\n", a(t, i));
#endif
    Pochoir_Kernel_1D_End(k3, shape_k3)

    printf("Pochoir_Kernel size = %d, sizeof(int) = %d\n", sizeof(k3), sizeof(int));
    /* this is a 2D checkerboard style tiling of the entire rectangular region/domain */
    Pochoir_Kernel<1> tile0[2] = {};
    Pochoir_Kernel<1> tile1[2] = {k0, k1};
    Pochoir_Kernel<1> tile_2D_checkerboard[2][2] = {{k0, k1}, {k2, k3}};
    leap_frog.Register_Tile_Kernels(Default_Guard_1D, tile_2D_checkerboard);
    leap_frog.Register_Array(a);

    /* initialization */
    for (int i = 0; i < N; ++i) {
        a(0, i) = 1.0 * (rand() % BASE);
        b(0, i) = a(0, i);
    }

    Pochoir_Plan<1> & l_plan = leap_frog.Gen_Plan(T);
    sprintf(pochoir_plan_file_name, "pochoir_%d_%d.dat", N, T);
    leap_frog.Store_Plan(pochoir_plan_file_name, l_plan);
    Pochoir_Plan<1> & ll_plan = leap_frog.Load_Plan(pochoir_plan_file_name);
//    leap_frog.Load_Plan();
    for (int times = 0; times < TIMES; ++times) {
        gettimeofday(&start, 0);
        leap_frog.Run(ll_plan);
//        leap_frog.Run(T);
        gettimeofday(&end, 0);
        min_tdiff = min(min_tdiff, (1.0e3 * tdiff(&end, &start)));
    }
    printf("Pochoir time = %.6f ms\n", min_tdiff);
//    std::cout << "Pochoir time : " << min_tdiff << " ms" << std::endl;

    min_tdiff = INF;
#if !POCHOIR
    /* cilk_for */
    for (int times = 0; times < TIMES; ++times) {
        gettimeofday(&start, 0);
        for (int t = 1; t < T + 1; ++t) {
            for (int i = 0; i < N; ++i) {
                if ((t - 1) % 2 == 0 && i % 2 == 0) {
                    /* k0 */
#if DEBUG
                        printf("<i0> b(%d, %d) = f(b(%d, %d) <%.3f>, b(%d, %d) <%.3f>, b(%d, %d) <%.3f>)\n", t, i, t-1, i-1, b(t-1, i-1), t-1, i, b(t-1, i), t-1, i+1, b(t-1, i+1));
                        printf("<i0> b(%d, %d) : %.3f -> ", t, i, b(t, i));
#endif
                        b(t, i) = 0.1 * b(t-1, i-1) + 0.15 * b(t-1, i) + 0.189 * b(t-1, i+1) + 0.8;
#if DEBUG
                        printf("%.3f\n", b(t, i));
#endif
                } else if ((t - 1) % 2 == 0 && i % 2 == 1) {
                    /* k1 */
#if DEBUG
                        printf("<i1> b(%d, %d) = f(b(%d, %d) <%.3f>, b(%d, %d) <%.3f>, b(%d, %d) <%.3f>)\n", t, i, t-1, i-1, b(t-1, i-1), t-1, i, b(t-1, i), t-1, i+1, b(t-1, i+1));
                        printf("<i1> b(%d, %d) : %.3f -> ", t, i, b(t, i));
#endif
                        b(t, i) = 0.2 * b(t-1, i-1) + 0.25 * b(t-1, i) + 0.281 * b(t-1, i+1) + 0.8;
#if DEBUG
                        printf("%.3f\n", b(t, i));
#endif
                } else if ((t - 1) % 2 == 1 && i % 2 == 0) {
                    /* k2 */
#if DEBUG
                        printf("<i2> b(%d, %d) = f(b(%d, %d) <%.3f>, b(%d, %d) <%.3f>, b(%d, %d) <%.3f>)\n", t, i, t-1, i-1, b(t-1, i-1), t-1, i, b(t-1, i), t-1, i+1, b(t-1, i+1));
                        printf("<i2> b(%d, %d) : %.3f -> ", t, i, b(t, i));
#endif
                        b(t, i) = 0.3 * b(t-1, i-1) - 0.35 * b(t-1, i) - 0.389 * b(t-1, i+1) - 0.8;
#if DEBUG
                        printf("%.3f\n", b(t, i));
#endif
                } else if ((t - 1) % 2 == 1 && i % 2 == 1) {
                    /* k3 */
#if DEBUG
                        printf("<e0> b(%d, %d) = f(b(%d, %d) <%.3f>, b(%d, %d) <%.3f>, b(%d, %d) <%.3f>)\n", t, i, t-1, i-1, b(t-1, i-1), t-1, i, b(t-1, i), t-1, i+1, b(t-1, i+1));
                        printf("<e0> b(%d, %d) : %.3f -> ", t, i, b(t, i));
#endif
                        b(t, i) = 0.4 * b(t-1, i-1) - 0.45 * b(t-1, i) - 0.489 * b(t-1, i+1) - 0.4;
#if DEBUG
                        printf("%.3f\n", b(t, i));
#endif
                }
            }
        }
        gettimeofday(&end, 0);
        min_tdiff = min(min_tdiff, (1.0e3 * tdiff(&end, &start)));
    }
#endif
    printf("Parallel Loop time = %.6f ms\n", min_tdiff);
//    std::cout << "Parallel Loop time : " << min_tdiff << " ms" << std::endl;

    /* check results! */
    t = T;
    for (int i = 0; i < N; ++i) {
        check_result(t, i, a(t, i), b(t, i));
    } 

    return 0;
}

