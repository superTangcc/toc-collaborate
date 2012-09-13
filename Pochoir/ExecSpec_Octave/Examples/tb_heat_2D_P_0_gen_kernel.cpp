
	
	#include <cstdio>
	#include <cstdlib>
	#include <cassert>
	#include <pochoir.hpp>
	
	/* Original Codes */
	
	/* Generated Codes */
	
	/* 
	[<1, 1>
,<1, 0>
]
	 */
	
	
	/* <1, 1>
 */
	auto __POCHOIR_Guard_0__ = [&]  ( int t, int i0, int i1 )  -> bool {
	return ( __Default_Guard_2D__ ( t + -1, i0, i1 )  );
	 };
	static Pochoir_Guard <2> POCHOIR_Guard_0 ( __POCHOIR_Guard_0__ ); 

	/* <1, 1>
 */
	
	
	/* 
	heat_2D_fn - PSERIAL;
	__Pochoir_NULL__ - PNULL
	 */
	/* heat_2D_fn, __Pochoir_NULL_ */ 
	/* 0, 0 */ 
	/* PSERIAL, PNULL */ 
	/* [], [0] */ 
	/* [1], [1] */ 
	/* 
	PMTile (sizes = [1], latest_tile_order = 0), terms = 
		PMTileTerm (indices = [], sizes = [1], latest_tile_order = 0), item = heat_2D_fn
	 */ 
	static 
	Pochoir_Shape <2> __POCHOIR_Shape__0__ [ ] = {{0, 0, 0}, {-1, 1, 0}, {-1, 0, 0}, {-1, -1, 0}, {-1, 0, -1}, {-1, 0, 1}};
	/* toggle: 2; slopes: [] */
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_cond_boundary_kernel_0__ {
	private: 
	Pochoir <2> & heat_2D; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_boundary_kernel_0__(Pochoir <2> & _heat_2D, Pochoir_Array <double, 2> & _a) : heat_2D(_heat_2D), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = heat_2D.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.125 * (a(t - 1, i + 1, j) - 2.0 * a(t - 1, i, j) + a(t - 1, i - 1, j)) + 0.125 * (a(t - 1, i, j + 1) - 2.0 * a(t - 1, i, j) + a(t - 1, i, j - 1)) + a(t - 1, i, j);
	
	
	#undef a(t, i, j)
	}
	
	
	} } 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[1] += l_grid.dx0[1];
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[1] += l_grid.dx1[1];
	l_grid.x1[0] += l_grid.dx1[0];
	} /* end for t */
	}
	};
	static __Pointer_cond_boundary_kernel_0__ * _Pointer_cond_boundary_kernel_0 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_boundary_kernel_0 = NULL;
	#undef pmod_lu
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_boundary_kernel_0__ {
	private: 
	Pochoir <2> & heat_2D; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_boundary_kernel_0__(Pochoir <2> & _heat_2D, Pochoir_Array <double, 2> & _a) : heat_2D(_heat_2D), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = heat_2D.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.125 * (a(t - 1, i + 1, j) - 2.0 * a(t - 1, i, j) + a(t - 1, i - 1, j)) + 0.125 * (a(t - 1, i, j + 1) - 2.0 * a(t - 1, i, j) + a(t - 1, i, j - 1)) + a(t - 1, i, j);
	
	
	#undef a(t, i, j)
	}
	
	
	} } 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[1] += l_grid.dx0[1];
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[1] += l_grid.dx1[1];
	l_grid.x1[0] += l_grid.dx1[0];
	++t;
	}
	{
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.125 * (a(t - 1, i + 1, j) - 2.0 * a(t - 1, i, j) + a(t - 1, i - 1, j)) + 0.125 * (a(t - 1, i, j + 1) - 2.0 * a(t - 1, i, j) + a(t - 1, i, j - 1)) + a(t - 1, i, j);
	
	
	#undef a(t, i, j)
	}
	
	
	} } 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[1] += l_grid.dx0[1];
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[1] += l_grid.dx1[1];
	l_grid.x1[0] += l_grid.dx1[0];
	
	}
	} /* end for t */
	}
	};
	static __Pointer_boundary_kernel_0__ * _Pointer_boundary_kernel_0 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_boundary_kernel_0 = NULL;
	#undef pmod_lu
	
	
	
	/* KNOWN */
	class __Pointer_cond_interior_kernel_0__ {
	private: 
	Pochoir <2> & heat_2D; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_interior_kernel_0__(Pochoir <2> & _heat_2D, Pochoir_Array <double, 2> & _a) : heat_2D(_heat_2D), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = heat_2D.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i","j"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[1]) * l_a_stride_1 + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i","j"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[1]) * l_a_stride_1 + (l_grid.x0[0]) * l_a_stride_0;
	
	gap_a_1 = l_a_stride_1 + (l_grid.x0[0] - l_grid.x1[0]) * l_a_stride_0;
	for (int i = l_grid.x0[1]; i < l_grid.x1[1]; ++i, 
	pt_a_0 += gap_a_1, 
	pt_a_1 += gap_a_1) {
	
	#pragma ivdep
	for (int j = l_grid.x0[0]; j < l_grid.x1[0]; ++j, 
	++pt_a_0, 
	++pt_a_1) {
	
	
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.125 * (pt_a_1[l_a_stride_1 * (1)] - 2.0 * pt_a_1[0] + pt_a_1[l_a_stride_1 * (-1)]) + 0.125 * (pt_a_1[l_a_stride_0 * (1)] - 2.0 * pt_a_1[0] + pt_a_1[l_a_stride_0 * (-1)]) + pt_a_1[0];
	
	}
	
	
	} } /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[1] += l_grid.dx0[1];
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[1] += l_grid.dx1[1];
	l_grid.x1[0] += l_grid.dx1[0];
	} /* end for t */
	}
	};
	static __Pointer_cond_interior_kernel_0__ * _Pointer_cond_interior_kernel_0 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_interior_kernel_0 = NULL;
	
	
	
	
	/* KNOWN */
	class __Pointer_interior_kernel_0__ {
	private: 
	Pochoir <2> & heat_2D; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_interior_kernel_0__(Pochoir <2> & _heat_2D, Pochoir_Array <double, 2> & _a) : heat_2D(_heat_2D), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = heat_2D.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i","j"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[1]) * l_a_stride_1 + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i","j"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[1]) * l_a_stride_1 + (l_grid.x0[0]) * l_a_stride_0;
	
	gap_a_1 = l_a_stride_1 + (l_grid.x0[0] - l_grid.x1[0]) * l_a_stride_0;
	for (int i = l_grid.x0[1]; i < l_grid.x1[1]; ++i, 
	pt_a_0 += gap_a_1, 
	pt_a_1 += gap_a_1) {
	
	#pragma ivdep
	for (int j = l_grid.x0[0]; j < l_grid.x1[0]; ++j, 
	++pt_a_0, 
	++pt_a_1) {
	
	
	
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.125 * (pt_a_1[l_a_stride_1 * (1)] - 2.0 * pt_a_1[0] + pt_a_1[l_a_stride_1 * (-1)]) + 0.125 * (pt_a_1[l_a_stride_0 * (1)] - 2.0 * pt_a_1[0] + pt_a_1[l_a_stride_0 * (-1)]) + pt_a_1[0];
	
	}
	
	
	} } /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[1] += l_grid.dx0[1];
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[1] += l_grid.dx1[1];
	l_grid.x1[0] += l_grid.dx1[0];
	++t;
	}
	{
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i","j"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[1]) * l_a_stride_1 + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i","j"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[1]) * l_a_stride_1 + (l_grid.x0[0]) * l_a_stride_0;
	
	gap_a_1 = l_a_stride_1 + (l_grid.x0[0] - l_grid.x1[0]) * l_a_stride_0;
	for (int i = l_grid.x0[1]; i < l_grid.x1[1]; ++i, 
	pt_a_0 += gap_a_1, 
	pt_a_1 += gap_a_1) {
	
	#pragma ivdep
	for (int j = l_grid.x0[0]; j < l_grid.x1[0]; ++j, 
	++pt_a_0, 
	++pt_a_1) {
	
	
	
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.125 * (pt_a_1[l_a_stride_1 * (1)] - 2.0 * pt_a_1[0] + pt_a_1[l_a_stride_1 * (-1)]) + 0.125 * (pt_a_1[l_a_stride_0 * (1)] - 2.0 * pt_a_1[0] + pt_a_1[l_a_stride_0 * (-1)]) + pt_a_1[0];
	
	}
	
	
	} } /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[1] += l_grid.dx0[1];
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[1] += l_grid.dx1[1];
	l_grid.x1[0] += l_grid.dx1[0];
	
	}
	} /* end for t */
	}
	};
	static __Pointer_interior_kernel_0__ * _Pointer_interior_kernel_0 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_interior_kernel_0 = NULL;
	
	
	
	/* <1, 0>
 */
	auto __POCHOIR_Guard_1__ = [&]  ( int t, int i0, int i1 )  -> bool {
	return ( true );
	 };
	static Pochoir_Guard <2> POCHOIR_Guard_1 ( __POCHOIR_Guard_1__ ); 

	/* <1, 0>
 */
	
	
	/* 
	heat_2D_fn - PINCLUSIVE;
	__Pochoir_NULL__ - PNULL
	 */
	/* heat_2D_fn, __Pochoir_NULL_ */ 
	/* 0, 0 */ 
	/* PINCLUSIVE, PNULL */ 
	/* [], [0] */ 
	/* [1], [1] */ 
	/* 
	PMTile (sizes = [1], latest_tile_order = 0), terms = 
		PMTileTerm (indices = [], sizes = [1], latest_tile_order = 0), item = heat_2D_fn
	 */ 
	static 
	Pochoir_Shape <2> __POCHOIR_Shape__1__ [ ] = {{0, 0, 0}, {-1, 1, 0}, {-1, 0, 0}, {-1, -1, 0}, {-1, 0, -1}, {-1, 0, 1}};
	/* toggle: 2; slopes: [] */
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_cond_boundary_kernel_1__ {
	private: 
	Pochoir <2> & heat_2D; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_boundary_kernel_1__(Pochoir <2> & _heat_2D, Pochoir_Array <double, 2> & _a) : heat_2D(_heat_2D), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = heat_2D.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	if (__Default_Guard_2D__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.125 * (a(t - 1, i + 1, j) - 2.0 * a(t - 1, i, j) + a(t - 1, i - 1, j)) + 0.125 * (a(t - 1, i, j + 1) - 2.0 * a(t - 1, i, j) + a(t - 1, i, j - 1)) + a(t - 1, i, j);
	
	
	#undef a(t, i, j)
	}
	
	
	} } 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[1] += l_grid.dx0[1];
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[1] += l_grid.dx1[1];
	l_grid.x1[0] += l_grid.dx1[0];
	} /* end for t */
	}
	};
	static __Pointer_cond_boundary_kernel_1__ * _Pointer_cond_boundary_kernel_1 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_boundary_kernel_1 = NULL;
	#undef pmod_lu
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_boundary_kernel_1__ {
	private: 
	Pochoir <2> & heat_2D; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_boundary_kernel_1__(Pochoir <2> & _heat_2D, Pochoir_Array <double, 2> & _a) : heat_2D(_heat_2D), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = heat_2D.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if (__Default_Guard_2D__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.125 * (a(t - 1, i + 1, j) - 2.0 * a(t - 1, i, j) + a(t - 1, i - 1, j)) + 0.125 * (a(t - 1, i, j + 1) - 2.0 * a(t - 1, i, j) + a(t - 1, i, j - 1)) + a(t - 1, i, j);
	
	
	#undef a(t, i, j)
	}
	
	
	} } 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[1] += l_grid.dx0[1];
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[1] += l_grid.dx1[1];
	l_grid.x1[0] += l_grid.dx1[0];
	++t;
	}
	{
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if (__Default_Guard_2D__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.125 * (a(t - 1, i + 1, j) - 2.0 * a(t - 1, i, j) + a(t - 1, i - 1, j)) + 0.125 * (a(t - 1, i, j + 1) - 2.0 * a(t - 1, i, j) + a(t - 1, i, j - 1)) + a(t - 1, i, j);
	
	
	#undef a(t, i, j)
	}
	
	
	} } 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[1] += l_grid.dx0[1];
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[1] += l_grid.dx1[1];
	l_grid.x1[0] += l_grid.dx1[0];
	
	}
	} /* end for t */
	}
	};
	static __Pointer_boundary_kernel_1__ * _Pointer_boundary_kernel_1 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_boundary_kernel_1 = NULL;
	#undef pmod_lu
	
	
	
	/* KNOWN */
	class __Pointer_cond_interior_kernel_1__ {
	private: 
	Pochoir <2> & heat_2D; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_interior_kernel_1__(Pochoir <2> & _heat_2D, Pochoir_Array <double, 2> & _a) : heat_2D(_heat_2D), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = heat_2D.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i","j"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[1]) * l_a_stride_1 + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i","j"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[1]) * l_a_stride_1 + (l_grid.x0[0]) * l_a_stride_0;
	
	gap_a_1 = l_a_stride_1 + (l_grid.x0[0] - l_grid.x1[0]) * l_a_stride_0;
	for (int i = l_grid.x0[1]; i < l_grid.x1[1]; ++i, 
	pt_a_0 += gap_a_1, 
	pt_a_1 += gap_a_1) {
	
	#pragma ivdep
	for (int j = l_grid.x0[0]; j < l_grid.x1[0]; ++j, 
	++pt_a_0, 
	++pt_a_1) {
	
	
	
	if (__Default_Guard_2D__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.125 * (pt_a_1[l_a_stride_1 * (1)] - 2.0 * pt_a_1[0] + pt_a_1[l_a_stride_1 * (-1)]) + 0.125 * (pt_a_1[l_a_stride_0 * (1)] - 2.0 * pt_a_1[0] + pt_a_1[l_a_stride_0 * (-1)]) + pt_a_1[0];
	
	}
	
	
	} } /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[1] += l_grid.dx0[1];
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[1] += l_grid.dx1[1];
	l_grid.x1[0] += l_grid.dx1[0];
	} /* end for t */
	}
	};
	static __Pointer_cond_interior_kernel_1__ * _Pointer_cond_interior_kernel_1 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_interior_kernel_1 = NULL;
	
	
	
	
	/* KNOWN */
	class __Pointer_interior_kernel_1__ {
	private: 
	Pochoir <2> & heat_2D; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_interior_kernel_1__(Pochoir <2> & _heat_2D, Pochoir_Array <double, 2> & _a) : heat_2D(_heat_2D), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = heat_2D.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i","j"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[1]) * l_a_stride_1 + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i","j"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[1]) * l_a_stride_1 + (l_grid.x0[0]) * l_a_stride_0;
	
	gap_a_1 = l_a_stride_1 + (l_grid.x0[0] - l_grid.x1[0]) * l_a_stride_0;
	for (int i = l_grid.x0[1]; i < l_grid.x1[1]; ++i, 
	pt_a_0 += gap_a_1, 
	pt_a_1 += gap_a_1) {
	
	#pragma ivdep
	for (int j = l_grid.x0[0]; j < l_grid.x1[0]; ++j, 
	++pt_a_0, 
	++pt_a_1) {
	
	
	
	
	if (__Default_Guard_2D__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.125 * (pt_a_1[l_a_stride_1 * (1)] - 2.0 * pt_a_1[0] + pt_a_1[l_a_stride_1 * (-1)]) + 0.125 * (pt_a_1[l_a_stride_0 * (1)] - 2.0 * pt_a_1[0] + pt_a_1[l_a_stride_0 * (-1)]) + pt_a_1[0];
	
	}
	
	
	} } /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[1] += l_grid.dx0[1];
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[1] += l_grid.dx1[1];
	l_grid.x1[0] += l_grid.dx1[0];
	++t;
	}
	{
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i","j"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[1]) * l_a_stride_1 + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i","j"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[1]) * l_a_stride_1 + (l_grid.x0[0]) * l_a_stride_0;
	
	gap_a_1 = l_a_stride_1 + (l_grid.x0[0] - l_grid.x1[0]) * l_a_stride_0;
	for (int i = l_grid.x0[1]; i < l_grid.x1[1]; ++i, 
	pt_a_0 += gap_a_1, 
	pt_a_1 += gap_a_1) {
	
	#pragma ivdep
	for (int j = l_grid.x0[0]; j < l_grid.x1[0]; ++j, 
	++pt_a_0, 
	++pt_a_1) {
	
	
	
	
	if (__Default_Guard_2D__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.125 * (pt_a_1[l_a_stride_1 * (1)] - 2.0 * pt_a_1[0] + pt_a_1[l_a_stride_1 * (-1)]) + 0.125 * (pt_a_1[l_a_stride_0 * (1)] - 2.0 * pt_a_1[0] + pt_a_1[l_a_stride_0 * (-1)]) + pt_a_1[0];
	
	}
	
	
	} } /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[1] += l_grid.dx0[1];
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[1] += l_grid.dx1[1];
	l_grid.x1[0] += l_grid.dx1[0];
	
	}
	} /* end for t */
	}
	};
	static __Pointer_interior_kernel_1__ * _Pointer_interior_kernel_1 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_interior_kernel_1 = NULL;
	
	
	
	extern "C" 
	int Create_Lambdas (Pochoir <2> & _heat_2D, Pochoir_Array <double, 2> & _a){
	
		_Pointer_boundary_kernel_0 = new __Pointer_boundary_kernel_0__(_heat_2D, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_0), 2 >  * l_Pointer_boundary_kernel_0 = NULL;
		l_Pointer_boundary_kernel_0 = new Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_0), 2 > ((*_Pointer_boundary_kernel_0), __POCHOIR_Shape__0__);
		Pointer_boundary_kernel_0 = l_Pointer_boundary_kernel_0;
	
		_Pointer_boundary_kernel_1 = new __Pointer_boundary_kernel_1__(_heat_2D, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_1), 2 >  * l_Pointer_boundary_kernel_1 = NULL;
		l_Pointer_boundary_kernel_1 = new Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_1), 2 > ((*_Pointer_boundary_kernel_1), __POCHOIR_Shape__1__);
		Pointer_boundary_kernel_1 = l_Pointer_boundary_kernel_1;
	
		_Pointer_cond_boundary_kernel_0 = new __Pointer_cond_boundary_kernel_0__(_heat_2D, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_0), 2 >  * l_Pointer_cond_boundary_kernel_0 = NULL;
		l_Pointer_cond_boundary_kernel_0 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_0), 2 > ((*_Pointer_cond_boundary_kernel_0), __POCHOIR_Shape__0__);
		Pointer_cond_boundary_kernel_0 = l_Pointer_cond_boundary_kernel_0;
	
		_Pointer_cond_boundary_kernel_1 = new __Pointer_cond_boundary_kernel_1__(_heat_2D, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_1), 2 >  * l_Pointer_cond_boundary_kernel_1 = NULL;
		l_Pointer_cond_boundary_kernel_1 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_1), 2 > ((*_Pointer_cond_boundary_kernel_1), __POCHOIR_Shape__1__);
		Pointer_cond_boundary_kernel_1 = l_Pointer_cond_boundary_kernel_1;
	
		_Pointer_interior_kernel_0 = new __Pointer_interior_kernel_0__(_heat_2D, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_0), 2 >  * l_Pointer_interior_kernel_0 = NULL;
		l_Pointer_interior_kernel_0 = new Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_0), 2 > ((*_Pointer_interior_kernel_0), __POCHOIR_Shape__0__);
		Pointer_interior_kernel_0 = l_Pointer_interior_kernel_0;
	
		_Pointer_interior_kernel_1 = new __Pointer_interior_kernel_1__(_heat_2D, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_1), 2 >  * l_Pointer_interior_kernel_1 = NULL;
		l_Pointer_interior_kernel_1 = new Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_1), 2 > ((*_Pointer_interior_kernel_1), __POCHOIR_Shape__1__);
		Pointer_interior_kernel_1 = l_Pointer_interior_kernel_1;
	
		_Pointer_cond_interior_kernel_0 = new __Pointer_cond_interior_kernel_0__(_heat_2D, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_0), 2 >  * l_Pointer_cond_interior_kernel_0 = NULL;
		l_Pointer_cond_interior_kernel_0 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_0), 2 > ((*_Pointer_cond_interior_kernel_0), __POCHOIR_Shape__0__);
		Pointer_cond_interior_kernel_0 = l_Pointer_cond_interior_kernel_0;
	
		_Pointer_cond_interior_kernel_1 = new __Pointer_cond_interior_kernel_1__(_heat_2D, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_1), 2 >  * l_Pointer_cond_interior_kernel_1 = NULL;
		l_Pointer_cond_interior_kernel_1 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_1), 2 > ((*_Pointer_cond_interior_kernel_1), __POCHOIR_Shape__1__);
		Pointer_cond_interior_kernel_1 = l_Pointer_cond_interior_kernel_1;
	
		return 0;
	}

	extern "C" 
	int Destroy_Lambdas (void) { 
	
		delete _Pointer_boundary_kernel_0;
		delete Pointer_boundary_kernel_0;
		delete _Pointer_boundary_kernel_1;
		delete Pointer_boundary_kernel_1;
		delete _Pointer_cond_boundary_kernel_0;
		delete Pointer_cond_boundary_kernel_0;
		delete _Pointer_cond_boundary_kernel_1;
		delete Pointer_cond_boundary_kernel_1;
		delete _Pointer_interior_kernel_0;
		delete Pointer_interior_kernel_0;
		delete _Pointer_interior_kernel_1;
		delete Pointer_interior_kernel_1;
		delete _Pointer_cond_interior_kernel_0;
		delete Pointer_cond_interior_kernel_0;
		delete _Pointer_cond_interior_kernel_1;
		delete Pointer_cond_interior_kernel_1;
		return 0;
	}
	extern "C" 
	int Register_Lambdas (Pochoir < 2 > & heat_2D) { 
		heat_2D.Register_Tile_Obase_Kernels(POCHOIR_Guard_0, 2, (*Pointer_interior_kernel_0), (*Pointer_cond_interior_kernel_0), (*Pointer_boundary_kernel_0), (*Pointer_cond_boundary_kernel_0));
		heat_2D.Register_Tile_Obase_Kernels(POCHOIR_Guard_1, 2, (*Pointer_interior_kernel_1), (*Pointer_cond_interior_kernel_1), (*Pointer_boundary_kernel_1), (*Pointer_cond_boundary_kernel_1));
	
		return 0;
	}
	
	extern "C" {
		void *__dso_handle = NULL;
	}
