#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <pochoir.hpp>

using namespace std;

void check_result(int t, int j, int i, double a, double b)
{
	if (abs(a - b) < (1e-6)) {
//		printf("a(%d, %d, %d) == b(%d, %d, %d) == %f : passed!\n", t, j, i, t, j, i, a);
} else {
		printf("a(%d, %d, %d) = %f, b(%d, %d, %d) = %f : FAILED!\n", t, j, i, a, t, j, i, b);
	}

}

template <typename T> T aperiodic_2D (
	/* Known*/ Pochoir_Array <T, 2> &arr, int t, int i, int j) {
    return 0;
}

template <typename T> T periodic_2D (
	/* Known*/ Pochoir_Array <T, 2> &arr, int t, int i, int j) {
    const int arr_size_1 = arr.size(1);
    const int arr_size_0 = arr.size(0);

    int new_i = (i >= arr_size_1) ? (i - arr_size_1) : (i < 0 ? i + arr_size_1 : i);
    int new_j = (j >= arr_size_0) ? (j - arr_size_0) : (j < 0 ? j + arr_size_0 : j);

    /* we use arr.get(...) instead of arr(...) to implement different boundary
     * checking strategy: In arr(...), if off-boundary access occurs, we call
     * boundary function to supply a value; in arr.get(...), if off-boundary 
     * access occurs, we will print the off-boundary access and quit!
     */
    return arr.get(t, new_i, new_j);
    // return arr.get(t, -1, -1);
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
    
	/* Known */ Pochoir_Shape <2> heat_shape_2D [6] = {{0, 0, 0}, {-1, 1, 0}, {-1, 0, 0}, {-1, -1, 0}, {-1, 0, -1}, {-1, 0, 1}};

	/* toggle: 2; slopes: [1,1] */

	/* Known*/ Pochoir_Array <double, 2> a ( N_SIZE, N_SIZE ) , b ( N_SIZE, N_SIZE ) ;
/* Known */a.Register_Shape(heat_shape_2D);
	a.Register_Boundary(aperiodic_2D); /* Register_Boundary */
	/* Known */b.Register_Shape(heat_shape_2D);
	b.Register_Boundary(aperiodic_2D); /* Register_Boundary */
	for (int i = 0; i < N_SIZE; ++i) {
	for (int j = 0; j < N_SIZE; ++j) {
        a(0, i, j) = 1.0 * (rand() % BASE); 
        a(1, i, j) = 0; 
        b(0, i, j) = a(0, i, j);
        b(1, i, j) = 0;
	} }

	cout << "a(T+1, J, I) = 0.125 * (a(T, J+1, I) - 2.0 * a(T, J, I) + a(T, J-1, I)) + 0.125 * (a(T, J, I+1) - 2.0 * a(T, J, I) + a(T, J, I-1)) + a(T, J, I)" << endl;
	gettimeofday(&start, 0);
    for (int times = 0; times < 1; ++times) {
   	for (int t = 0; t < T_SIZE; ++t) {
    for (int i = 0; i <= N_SIZE-1; ++i) {
	for (int j = 0; j <= N_SIZE-1; ++j) {
        a(t+1, i, j) = 0.125 * (a(t, i+1, j) - 2.0 * a(t, i, j) + a(t, i-1, j)) + 0.125 * (a(t, i, j+1) - 2.0 * a(t, i, j) + a(t, i, j-1)) + a(t, i, j); } } }
    }
	gettimeofday(&end, 0);
	std::cout << "Pochoir ET: consumed time :" << 1.0e3 * tdiff(&end, &start)/1 << "ms" << std::endl;

	gettimeofday(&start, 0);
    for (int times = 0; times < 1; ++times) {
	for (int t = 0; t < T_SIZE; ++t) {
    _Cilk_for (int i = 0; i <= N_SIZE-1; ++i) {
	for (int j = 0; j <= N_SIZE-1; ++j) {
        b(t+1, i, j) = 0.125 * (b(t, i+1, j) - 2.0 * b(t, i, j) + b(t, i-1, j)) + 0.125 * (b(t, i, j+1) - 2.0 * b(t, i, j) + b(t, i, j-1)) + b(t, i, j); } } }
    }
	gettimeofday(&end, 0);
	std::cout << "Naive Loop: consumed time :" << 1.0e3 * tdiff(&end, &start)/1 << "ms" << std::endl;

	t = T_SIZE;
	for (int i = 0; i <= N_SIZE-1; ++i) {
	for (int j = 0; j <= N_SIZE-1; ++j) {
		check_result(t, i, j, a.interior(t, i, j), b.interior(t, i, j));
	} } 

	return 0;
}

