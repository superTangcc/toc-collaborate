#include <cstdio>
#include <cstdlib>
#include <pochoir.hpp>
#include <iostream>

using namespace std;

void check_result(int t, int i, double a, double b)
{
	if (abs(a - b) < (1e-6)) {
//		printf("a(%d, %d) == b(%d, %d) == %f : passed!\n", t, i, t, i, a);
} else {
		printf("a(%d, %d) = %f, b(%d, %d) = %f : FAILED!\n", t, i, a, t, i, b);
	}
}

template <typename T> T aperiodic_1D (
	/* Known*/ Pochoir_Array <T, 1> &arr, int t, int i) {
    return 0;
}

template <typename T> T periodic_1D (
	/* Known*/ Pochoir_Array <T, 1> &arr, int t, int i) {
    const int arr_size_0 = arr.size(0);

    int new_i = (i >= arr_size_0) ? (i - arr_size_0) : (i < 0 ? i + arr_size_0 : i);

    /* we use arr.get(...) instead of arr(...) to implement different boundary
     * checking strategy: In arr(...), if off-boundary access occurs, we call
     * boundary function to supply a value; in arr.get(...), if off-boundary 
     * access occurs, we will print the off-boundary access and quit!
     */
    return arr.get(t, new_i);
}

int main(int argc, char * argv[])
{
	const int BASE = 1024;
	int t;
	struct timeval start, end;
    int N_SIZE = 0, T_SIZE = 0;

    if (argc < 3) {
        printf("argc < 3, quit! \n");
        exit(1);
    }
    N_SIZE = StrToInt(argv[1]);
    T_SIZE = StrToInt(argv[2]);
    printf("N_SIZE = %d, T_SIZE = %d\n", N_SIZE, T_SIZE);
    
	/* Known */ Pochoir_Shape <1> heat_shape_1D [4] = {{0, 0}, {-1, 1}, {-1, 0}, {-1, -1}};

	/* toggle: 2; slopes: [1] */

	/* Known*/ Pochoir_Array <double, 1> a ( N_SIZE ) , b ( N_SIZE ) ;
/* Known */a.Register_Shape(heat_shape_1D);
	a.Register_Boundary(aperiodic_1D); /* Register_Boundary */
	/* Known */b.Register_Shape(heat_shape_1D);
	b.Register_Boundary(aperiodic_1D); /* Register_Boundary */
	for (int i = 0; i < N_SIZE; ++i) {
        a(0, i) = 1.0 * (rand() % BASE); 
        a(1, i) = 0; 
        b(0, i) = a(0, i);
        b(1, i) = 0;
	} 

	cout << "a(T+1, J) = 0.125 * (a(T, I+1) - 2.0 * a(T, I) + a(T, I-1)) + a(T, I)" << endl;
	gettimeofday(&start, 0);
    for (int times = 0; times < 1; ++times) {
   	for (int t = 0; t < T_SIZE; ++t) {
    for (int i = 0; i <= N_SIZE-1; ++i) {
        a(t+1, i) = 0.125 * (a(t, i+1) - 2.0 * a(t, i) + a(t, i-1)) + a(t, i); } }
    }
	gettimeofday(&end, 0);
	std::cout << "Pochoir ET: consumed time :" << 1.0e3 * tdiff(&end, &start)/1 << "ms" << std::endl;

	gettimeofday(&start, 0);
    for (int times = 0; times < 1; ++times) {
	for (int t = 0; t < T_SIZE; ++t) {
    _Cilk_for (int i = 0; i <= N_SIZE-1; ++i) {
        b(t+1, i) = 0.125 * (b(t, i+1) - 2.0 * b(t, i) + b(t, i-1)) + b(t, i); } }
    }
	gettimeofday(&end, 0);
	std::cout << "Naive Loop: consumed time :" << 1.0e3 * tdiff(&end, &start)/1 << "ms" << std::endl;

	t = T_SIZE;
	for (int i = 0; i <= N_SIZE-1; ++i) {
		check_result(t, i, a.interior(t, i), b.interior(t, i));
	}  

	return 0;
}

