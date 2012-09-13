/*
 * ============================================================================
 *
 *       Filename:  tb_meta.cpp
 *
 *    Description:  test bench for C++ template meta-programming technique
 *
 *        Version:  1.0
 *        Created:  03/02/2012 10:08:45 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan Tang (), yuantang@csail.mit.edu
 *        Company:  CSAIL, M.I.T.
 *
 * ============================================================================
 */

#include <cstdio>
#include <cstdlib>

template <int BASE, int EXP>
struct power {
    enum { value = BASE * power<BASE, EXP-1>::value };
};

template <int BASE>
struct power<BASE, 1> {
    enum { value = BASE };
};

template <int N_RANK>
class Pochoir_Array {
    public: 
        Pochoir_Array() {}
        template <int N_SIZE, typename I>
        void print(int (&shift)[N_SIZE], int (&index)[N_SIZE], I i) {
            shift[N_SIZE-1] = i;
            index[N_SIZE-1] = i+1;
            printf("%d\n", i);
        }

        template <int N_SIZE, typename I, typename ... IS>
        void print(int (&shift)[N_SIZE], int (&index)[N_SIZE], I idx, IS ... idxs) {
            int l_dim = 1 + sizeof ... (IS);
            shift[N_SIZE-l_dim] = idx;
            index[N_SIZE-l_dim] = idx+1;
            printf("%d, ", idx);
            print(shift, index, idxs ...);
        }

        void mprint(void) {
            int shift[N_RANK], index[N_RANK];
            print(shift, index, 0-1,1,1);
            for (int i = 0; i < N_RANK; ++i) {
                printf("shift[%d] = %d, index[%d] = %d\n", i, shift[i], i, index[i]);
            }

        }
};

#define T 2
#define N 5
#define N_RANK 3
int main(void) {
    printf("power(%d, %d) = %d\n", T, N, power<T, N>::value);
    Pochoir_Array<3> a;
    a.mprint();
    return 0;
}
