
	/* Pochoir_Kernel <2> tile_3D_checkerboard_0[ 2 ][ 2 ][ 2 ] = {{{k_0_0, k_0_1}, {k_0_2, k_0_3}}, {{k_0_4, k_0_5}, {k_0_6, k_0_7}}}; */
	/* k_0_0[0,0,0]; k_0_1[0,0,1]; k_0_2[0,1,0]; k_0_3[0,1,1]; k_0_4[1,0,0]; k_0_5[1,0,1]; k_0_6[1,1,0]; k_0_7[1,1,1] */
	
	/* Pochoir_Kernel <2> tile_2D_checkerboard_1[ 2 ][ 2 ] = {{k_1_0, k_1_1}, {k_1_2, k_1_3}}; */
	/* k_1_0[0,0]; k_1_1[0,1]; k_1_2[1,0]; k_1_3[1,1] */
	
	/* Pochoir_Kernel <2> tile_1D_checkerboard_2[ 2 ] = {k_2_0, k_2_1}; */
	/* k_2_0[0]; k_2_1[1] */
	
	/* Pochoir_Kernel <2> tile_3D_checkerboard_3[ 2 ][ 2 ][ 2 ] = {{{k_3_0, k_3_1}, {k_3_2, k_3_3}}, {{k_3_4, k_3_5}, {k_3_6, k_3_7}}}; */
	/* k_3_0[0,0,0]; k_3_1[0,0,1]; k_3_2[0,1,0]; k_3_3[0,1,1]; k_3_4[1,0,0]; k_3_5[1,0,1]; k_3_6[1,1,0]; k_3_7[1,1,1] */
	
	/* Pochoir_Kernel <2> tile_2D_checkerboard_4[ 2 ][ 2 ] = {{k_4_0, k_4_1}, {k_4_2, k_4_3}}; */
	/* k_4_0[0,0]; k_4_1[0,1]; k_4_2[1,0]; k_4_3[1,1] */
	
	/* Pochoir_Kernel <2> tile_1D_checkerboard_5[ 2 ] = {k_5_0, k_5_1}; */
	/* k_5_0[0]; k_5_1[1] */
	
	
	#include <cstdio>
	#include <cstdlib>
	#include <cassert>
	#include <pochoir.hpp>
	
	/* Original Codes */
	/* known Guard ! */ auto __g_exclusive_0__ = [&] (int t, int i, int j) -> bool {
	if (((i < 665 / 2 && j < 665 / 2))) {
	{return ((true));
	
	
	}
	} else {{return ((false));
	
	
	}}
	
	};
	/* known Guard ! */ auto __g_exclusive_1__ = [&] (int t, int i, int j) -> bool {
	if (((i >= 665 / 2 && j >= 665 / 2))) {
	{return ((true));
	
	
	}
	} else {{return ((false));
	
	
	}}
	
	};
	/* known Guard ! */ auto __g_inclusive_0__ = [&] (int t, int i, int j) -> bool {
	if (((i < 665 / 2 && j < 665 / 2 && t < 65 / 2))) {
	{return ((true));
	
	
	}
	} else {{return ((false));
	
	
	}}
	
	};
	/* known Guard ! */ auto __g_inclusive_1__ = [&] (int t, int i, int j) -> bool {
	if (((i >= 665 / 4 && i < 665 / 3 && j >= 665 / 4 && j < 665 / 3 && t < 65 * 2 / 3))) {
	{return ((true));
	
	
	}
	} else {{return ((false));
	
	
	}}
	
	};
	/* known Guard ! */ auto __g_tiny_inclusive_0__ = [&] (int t, int i, int j) -> bool {
	if (((i >= 1 && i < 5 && j >= 1 && j < 5 && t > 1 && t <= 2))) {
	{return ((true));
	
	
	}
	} else {{return ((false));
	
	
	}}
	
	};
	/* known Guard ! */ auto __g_tiny_inclusive_1__ = [&] (int t, int i, int j) -> bool {
	if (((i > 5 && i <= 10 && j > 5 && j <= 10 && t > 2 && t < 4))) {
	{return ((true));
	
	
	}
	} else {{return ((false));
	
	
	}}
	
	};
	
	/* Generated Codes */
	
	/* 
	[<000000, 000000>
,<010000, 010000>
,<100000, 100000>
,<010000, 000000>
,<100000, 000000>
,<101000, 101000>
,<101000, 000000>
,<101100, 101000>
,<111000, 000000>
,<101100, 101100>
,<100100, 100000>
,<100100, 100100>
,<111010, 000000>
,<101001, 101000>
,<110000, 000000>
,<111111, 000000>
]
	 */
	
	
	/* <000000, 000000>
 */
	auto __POCHOIR_Guard_0__ = [&]  ( int t, int i0, int i1 )  -> bool {
	return ( !__g_exclusive_0__ ( t + -1, i0, i1 )  && !__g_exclusive_1__ ( t + -1, i0, i1 )  && !__g_inclusive_0__ ( t + -1, i0, i1 )  && !__g_inclusive_1__ ( t + -1, i0, i1 )  && !__g_tiny_inclusive_0__ ( t + -1, i0, i1 )  && !__g_tiny_inclusive_1__ ( t + -1, i0, i1 )  );
	 };
	static Pochoir_Guard <2> POCHOIR_Guard_0 ( __POCHOIR_Guard_0__ ); 

	/* <000000, 000000>
 */
	
	
	/* 
	__Pochoir_NULL__ - PNULL
	 */
	/* __Pochoir_NULL_ */ 
	/* 0 */ 
	/* PNULL */ 
	/* [0] */ 
	/* [1] */ 
	/* 
	PMTile (sizes = [1], latest_tile_order = 0), terms = 
		PMTileTerm (indices = [0], sizes = [1], latest_tile_order = 0), item = __Pochoir_NULL_
	 */ 
	static 
	Pochoir_Shape <2> __POCHOIR_Shape__0__ [ ] = {{0, 0, 0}, {-1, 0, -1}, {-1, 0, 1}, {-1, 1, 0}, {-1, -1, 0}, {-1, 0, 0}};
	/* toggle: 2; slopes: [] */
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_cond_boundary_kernel_0__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_boundary_kernel_0__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	/* tile_op all PNULL */ 
	
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
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_boundary_kernel_0__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	/* tile_op all PNULL */ 
	
	} /* end for t */
	}
	};
	static __Pointer_boundary_kernel_0__ * _Pointer_boundary_kernel_0 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_boundary_kernel_0 = NULL;
	#undef pmod_lu
	
	
	
	/* KNOWN */
	class __Pointer_cond_interior_kernel_0__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_interior_kernel_0__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	/* tile_op all PNULL */ 
	
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
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_interior_kernel_0__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	/* tile_op all PNULL */ 
	
	} /* end for t */
	}
	};
	static __Pointer_interior_kernel_0__ * _Pointer_interior_kernel_0 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_interior_kernel_0 = NULL;
	
	
	
	/* <010000, 010000>
 */
	auto __POCHOIR_Guard_1__ = [&]  ( int t, int i0, int i1 )  -> bool {
	return ( !__g_exclusive_0__ ( t + -1, i0, i1 )  && __g_exclusive_1__ ( t + -1, i0, i1 )  && !__g_inclusive_0__ ( t + -1, i0, i1 )  && !__g_inclusive_1__ ( t + -1, i0, i1 )  && !__g_tiny_inclusive_0__ ( t + -1, i0, i1 )  && !__g_tiny_inclusive_1__ ( t + -1, i0, i1 )  );
	 };
	static Pochoir_Guard <2> POCHOIR_Guard_1 ( __POCHOIR_Guard_1__ ); 

	/* <010000, 010000>
 */
	
	
	/* 
	tile_2D_checkerboard_1 - PSERIAL;
	__Pochoir_NULL__ - PNULL
	 */
	/* k_1_0, k_1_1, k_1_2, k_1_3, __Pochoir_NULL_ */ 
	/* 1, 1, 1, 1, 0 */ 
	/* PSERIAL, PSERIAL, PSERIAL, PSERIAL, PNULL */ 
	/* [0,0], [0,1], [1,0], [1,1], [0] */ 
	/* [2,2], [2,2], [2,2], [2,2], [1] */ 
	/* 
	PMTile (sizes = [2,2], latest_tile_order = 1), terms = 
		PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 1), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 1), item = k_1_0
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 1), item = k_1_1
		PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 1), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 1), item = k_1_2
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 1), item = k_1_3
	 */ 
	static 
	Pochoir_Shape <2> __POCHOIR_Shape__1__ [ ] = {{0, 0, 0}, {-1, 0, -1}, {-1, 0, 1}, {-1, 1, 0}, {-1, -1, 0}, {-1, 0, 0}};
	/* toggle: 2; slopes: [] */
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_cond_boundary_kernel_1__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_boundary_kernel_1__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.11000000000000001 * a(t - 1, i - 1, j) + 0.151 * a(t - 1, i, j) + 0.151 * a(t - 1, i + 1, j) - 0.11000000000000001 * a(t - 1, i, j - 1) - 0.151 * a(t - 1, i, j) - 0.151 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.21000000000000002 * a(t - 1, i - 1, j) + 0.251 * a(t - 1, i, j) + 0.251 * a(t - 1, i + 1, j) - 0.21000000000000002 * a(t - 1, i, j - 1) - 0.251 * a(t - 1, i, j) - 0.251 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.31 * a(t - 1, i - 1, j) + 0.351 * a(t - 1, i, j) + 0.351 * a(t - 1, i + 1, j) - 0.31 * a(t - 1, i, j - 1) - 0.351 * a(t - 1, i, j) - 0.351 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.41 * a(t - 1, i - 1, j) + 0.45099999999999996 * a(t - 1, i, j) + 0.45099999999999996 * a(t - 1, i + 1, j) - 0.41 * a(t - 1, i, j - 1) - 0.45099999999999996 * a(t - 1, i, j) - 0.45099999999999996 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
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
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_boundary_kernel_1__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.11000000000000001 * a(t - 1, i - 1, j) + 0.151 * a(t - 1, i, j) + 0.151 * a(t - 1, i + 1, j) - 0.11000000000000001 * a(t - 1, i, j - 1) - 0.151 * a(t - 1, i, j) - 0.151 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.21000000000000002 * a(t - 1, i - 1, j) + 0.251 * a(t - 1, i, j) + 0.251 * a(t - 1, i + 1, j) - 0.21000000000000002 * a(t - 1, i, j - 1) - 0.251 * a(t - 1, i, j) - 0.251 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.31 * a(t - 1, i - 1, j) + 0.351 * a(t - 1, i, j) + 0.351 * a(t - 1, i + 1, j) - 0.31 * a(t - 1, i, j - 1) - 0.351 * a(t - 1, i, j) - 0.351 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.41 * a(t - 1, i - 1, j) + 0.45099999999999996 * a(t - 1, i, j) + 0.45099999999999996 * a(t - 1, i + 1, j) - 0.41 * a(t - 1, i, j - 1) - 0.45099999999999996 * a(t - 1, i, j) - 0.45099999999999996 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
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
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_interior_kernel_1__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.11000000000000001 * pt_a_1[l_a_stride_1 * (-1)] + 0.151 * pt_a_1[0] + 0.151 * pt_a_1[l_a_stride_1 * (1)] - 0.11000000000000001 * pt_a_1[l_a_stride_0 * (-1)] - 0.151 * pt_a_1[0] - 0.151 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.21000000000000002 * pt_a_1[l_a_stride_1 * (-1)] + 0.251 * pt_a_1[0] + 0.251 * pt_a_1[l_a_stride_1 * (1)] - 0.21000000000000002 * pt_a_1[l_a_stride_0 * (-1)] - 0.251 * pt_a_1[0] - 0.251 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.31 * pt_a_1[l_a_stride_1 * (-1)] + 0.351 * pt_a_1[0] + 0.351 * pt_a_1[l_a_stride_1 * (1)] - 0.31 * pt_a_1[l_a_stride_0 * (-1)] - 0.351 * pt_a_1[0] - 0.351 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.41 * pt_a_1[l_a_stride_1 * (-1)] + 0.45099999999999996 * pt_a_1[0] + 0.45099999999999996 * pt_a_1[l_a_stride_1 * (1)] - 0.41 * pt_a_1[l_a_stride_0 * (-1)] - 0.45099999999999996 * pt_a_1[0] - 0.45099999999999996 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
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
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_interior_kernel_1__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.11000000000000001 * pt_a_1[l_a_stride_1 * (-1)] + 0.151 * pt_a_1[0] + 0.151 * pt_a_1[l_a_stride_1 * (1)] - 0.11000000000000001 * pt_a_1[l_a_stride_0 * (-1)] - 0.151 * pt_a_1[0] - 0.151 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.21000000000000002 * pt_a_1[l_a_stride_1 * (-1)] + 0.251 * pt_a_1[0] + 0.251 * pt_a_1[l_a_stride_1 * (1)] - 0.21000000000000002 * pt_a_1[l_a_stride_0 * (-1)] - 0.251 * pt_a_1[0] - 0.251 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.31 * pt_a_1[l_a_stride_1 * (-1)] + 0.351 * pt_a_1[0] + 0.351 * pt_a_1[l_a_stride_1 * (1)] - 0.31 * pt_a_1[l_a_stride_0 * (-1)] - 0.351 * pt_a_1[0] - 0.351 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.41 * pt_a_1[l_a_stride_1 * (-1)] + 0.45099999999999996 * pt_a_1[0] + 0.45099999999999996 * pt_a_1[l_a_stride_1 * (1)] - 0.41 * pt_a_1[l_a_stride_0 * (-1)] - 0.45099999999999996 * pt_a_1[0] - 0.45099999999999996 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
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
	
	
	
	/* <100000, 100000>
 */
	auto __POCHOIR_Guard_2__ = [&]  ( int t, int i0, int i1 )  -> bool {
	return ( __g_exclusive_0__ ( t + -1, i0, i1 )  && !__g_exclusive_1__ ( t + -1, i0, i1 )  && !__g_inclusive_0__ ( t + -1, i0, i1 )  && !__g_inclusive_1__ ( t + -1, i0, i1 )  && !__g_tiny_inclusive_0__ ( t + -1, i0, i1 )  && !__g_tiny_inclusive_1__ ( t + -1, i0, i1 )  );
	 };
	static Pochoir_Guard <2> POCHOIR_Guard_2 ( __POCHOIR_Guard_2__ ); 

	/* <100000, 100000>
 */
	
	
	/* 
	tile_3D_checkerboard_0 - PSERIAL;
	__Pochoir_NULL__ - PNULL
	 */
	/* k_0_0, k_0_1, k_0_2, k_0_3, k_0_4, k_0_5, k_0_6, k_0_7, __Pochoir_NULL_ */ 
	/* 0, 0, 0, 0, 0, 0, 0, 0, 0 */ 
	/* PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PNULL */ 
	/* [0,0,0], [0,0,1], [0,1,0], [0,1,1], [1,0,0], [1,0,1], [1,1,0], [1,1,1], [0] */ 
	/* [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [1] */ 
	/* 
	PMTile (sizes = [2,2,2], latest_tile_order = 0), terms = 
		PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_0
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_1
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_2
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_3
		PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_4
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_5
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_6
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_7
	 */ 
	static 
	Pochoir_Shape <2> __POCHOIR_Shape__2__ [ ] = {{0, 0, 0}, {-1, 0, -1}, {-1, 0, 1}, {-1, 1, 0}, {-1, -1, 0}, {-1, 0, 0}};
	/* toggle: 2; slopes: [] */
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_cond_boundary_kernel_2__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_boundary_kernel_2__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.1 * a(t - 1, i - 1, j) + 0.15 * a(t - 1, i, j) + 0.15 * a(t - 1, i + 1, j) - 0.1 * a(t - 1, i, j - 1) - 0.15 * a(t - 1, i, j) - 0.15 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.2 * a(t - 1, i - 1, j) + 0.25 * a(t - 1, i, j) + 0.25 * a(t - 1, i + 1, j) - 0.2 * a(t - 1, i, j - 1) - 0.25 * a(t - 1, i, j) - 0.25 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.3 * a(t - 1, i - 1, j) + 0.35 * a(t - 1, i, j) + 0.35 * a(t - 1, i + 1, j) - 0.3 * a(t - 1, i, j - 1) - 0.35 * a(t - 1, i, j) - 0.35 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.4 * a(t - 1, i - 1, j) + 0.45 * a(t - 1, i, j) + 0.45 * a(t - 1, i + 1, j) - 0.4 * a(t - 1, i, j - 1) - 0.45 * a(t - 1, i, j) - 0.45 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.5 * a(t - 1, i - 1, j) + 0.55 * a(t - 1, i, j) + 0.55 * a(t - 1, i + 1, j) - 0.5 * a(t - 1, i, j - 1) - 0.55 * a(t - 1, i, j) - 0.55 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.6 * a(t - 1, i - 1, j) + 0.65 * a(t - 1, i, j) + 0.65 * a(t - 1, i + 1, j) - 0.6 * a(t - 1, i, j - 1) - 0.65 * a(t - 1, i, j) - 0.65 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.7 * a(t - 1, i - 1, j) + 0.75 * a(t - 1, i, j) + 0.75 * a(t - 1, i + 1, j) - 0.7 * a(t - 1, i, j - 1) - 0.75 * a(t - 1, i, j) - 0.75 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8 * a(t - 1, i - 1, j) + 0.85 * a(t - 1, i, j) + 0.85 * a(t - 1, i + 1, j) - 0.8 * a(t - 1, i, j - 1) - 0.85 * a(t - 1, i, j) - 0.85 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
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
	static __Pointer_cond_boundary_kernel_2__ * _Pointer_cond_boundary_kernel_2 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_boundary_kernel_2 = NULL;
	#undef pmod_lu
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_boundary_kernel_2__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_boundary_kernel_2__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.1 * a(t - 1, i - 1, j) + 0.15 * a(t - 1, i, j) + 0.15 * a(t - 1, i + 1, j) - 0.1 * a(t - 1, i, j - 1) - 0.15 * a(t - 1, i, j) - 0.15 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.2 * a(t - 1, i - 1, j) + 0.25 * a(t - 1, i, j) + 0.25 * a(t - 1, i + 1, j) - 0.2 * a(t - 1, i, j - 1) - 0.25 * a(t - 1, i, j) - 0.25 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.3 * a(t - 1, i - 1, j) + 0.35 * a(t - 1, i, j) + 0.35 * a(t - 1, i + 1, j) - 0.3 * a(t - 1, i, j - 1) - 0.35 * a(t - 1, i, j) - 0.35 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.4 * a(t - 1, i - 1, j) + 0.45 * a(t - 1, i, j) + 0.45 * a(t - 1, i + 1, j) - 0.4 * a(t - 1, i, j - 1) - 0.45 * a(t - 1, i, j) - 0.45 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.5 * a(t - 1, i - 1, j) + 0.55 * a(t - 1, i, j) + 0.55 * a(t - 1, i + 1, j) - 0.5 * a(t - 1, i, j - 1) - 0.55 * a(t - 1, i, j) - 0.55 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.6 * a(t - 1, i - 1, j) + 0.65 * a(t - 1, i, j) + 0.65 * a(t - 1, i + 1, j) - 0.6 * a(t - 1, i, j - 1) - 0.65 * a(t - 1, i, j) - 0.65 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.7 * a(t - 1, i - 1, j) + 0.75 * a(t - 1, i, j) + 0.75 * a(t - 1, i + 1, j) - 0.7 * a(t - 1, i, j - 1) - 0.75 * a(t - 1, i, j) - 0.75 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8 * a(t - 1, i - 1, j) + 0.85 * a(t - 1, i, j) + 0.85 * a(t - 1, i + 1, j) - 0.8 * a(t - 1, i, j - 1) - 0.85 * a(t - 1, i, j) - 0.85 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
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
	static __Pointer_boundary_kernel_2__ * _Pointer_boundary_kernel_2 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_boundary_kernel_2 = NULL;
	#undef pmod_lu
	
	
	
	/* KNOWN */
	class __Pointer_cond_interior_kernel_2__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_interior_kernel_2__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.1 * pt_a_1[l_a_stride_1 * (-1)] + 0.15 * pt_a_1[0] + 0.15 * pt_a_1[l_a_stride_1 * (1)] - 0.1 * pt_a_1[l_a_stride_0 * (-1)] - 0.15 * pt_a_1[0] - 0.15 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.2 * pt_a_1[l_a_stride_1 * (-1)] + 0.25 * pt_a_1[0] + 0.25 * pt_a_1[l_a_stride_1 * (1)] - 0.2 * pt_a_1[l_a_stride_0 * (-1)] - 0.25 * pt_a_1[0] - 0.25 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.3 * pt_a_1[l_a_stride_1 * (-1)] + 0.35 * pt_a_1[0] + 0.35 * pt_a_1[l_a_stride_1 * (1)] - 0.3 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] - 0.35 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.4 * pt_a_1[l_a_stride_1 * (-1)] + 0.45 * pt_a_1[0] + 0.45 * pt_a_1[l_a_stride_1 * (1)] - 0.4 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] - 0.45 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.5 * pt_a_1[l_a_stride_1 * (-1)] + 0.55 * pt_a_1[0] + 0.55 * pt_a_1[l_a_stride_1 * (1)] - 0.5 * pt_a_1[l_a_stride_0 * (-1)] - 0.55 * pt_a_1[0] - 0.55 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.6 * pt_a_1[l_a_stride_1 * (-1)] + 0.65 * pt_a_1[0] + 0.65 * pt_a_1[l_a_stride_1 * (1)] - 0.6 * pt_a_1[l_a_stride_0 * (-1)] - 0.65 * pt_a_1[0] - 0.65 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.7 * pt_a_1[l_a_stride_1 * (-1)] + 0.75 * pt_a_1[0] + 0.75 * pt_a_1[l_a_stride_1 * (1)] - 0.7 * pt_a_1[l_a_stride_0 * (-1)] - 0.75 * pt_a_1[0] - 0.75 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.8 * pt_a_1[l_a_stride_1 * (-1)] + 0.85 * pt_a_1[0] + 0.85 * pt_a_1[l_a_stride_1 * (1)] - 0.8 * pt_a_1[l_a_stride_0 * (-1)] - 0.85 * pt_a_1[0] - 0.85 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
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
	static __Pointer_cond_interior_kernel_2__ * _Pointer_cond_interior_kernel_2 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_interior_kernel_2 = NULL;
	
	
	
	
	/* KNOWN */
	class __Pointer_interior_kernel_2__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_interior_kernel_2__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.1 * pt_a_1[l_a_stride_1 * (-1)] + 0.15 * pt_a_1[0] + 0.15 * pt_a_1[l_a_stride_1 * (1)] - 0.1 * pt_a_1[l_a_stride_0 * (-1)] - 0.15 * pt_a_1[0] - 0.15 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.2 * pt_a_1[l_a_stride_1 * (-1)] + 0.25 * pt_a_1[0] + 0.25 * pt_a_1[l_a_stride_1 * (1)] - 0.2 * pt_a_1[l_a_stride_0 * (-1)] - 0.25 * pt_a_1[0] - 0.25 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.3 * pt_a_1[l_a_stride_1 * (-1)] + 0.35 * pt_a_1[0] + 0.35 * pt_a_1[l_a_stride_1 * (1)] - 0.3 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] - 0.35 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.4 * pt_a_1[l_a_stride_1 * (-1)] + 0.45 * pt_a_1[0] + 0.45 * pt_a_1[l_a_stride_1 * (1)] - 0.4 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] - 0.45 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.5 * pt_a_1[l_a_stride_1 * (-1)] + 0.55 * pt_a_1[0] + 0.55 * pt_a_1[l_a_stride_1 * (1)] - 0.5 * pt_a_1[l_a_stride_0 * (-1)] - 0.55 * pt_a_1[0] - 0.55 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.6 * pt_a_1[l_a_stride_1 * (-1)] + 0.65 * pt_a_1[0] + 0.65 * pt_a_1[l_a_stride_1 * (1)] - 0.6 * pt_a_1[l_a_stride_0 * (-1)] - 0.65 * pt_a_1[0] - 0.65 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.7 * pt_a_1[l_a_stride_1 * (-1)] + 0.75 * pt_a_1[0] + 0.75 * pt_a_1[l_a_stride_1 * (1)] - 0.7 * pt_a_1[l_a_stride_0 * (-1)] - 0.75 * pt_a_1[0] - 0.75 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.8 * pt_a_1[l_a_stride_1 * (-1)] + 0.85 * pt_a_1[0] + 0.85 * pt_a_1[l_a_stride_1 * (1)] - 0.8 * pt_a_1[l_a_stride_0 * (-1)] - 0.85 * pt_a_1[0] - 0.85 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
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
	static __Pointer_interior_kernel_2__ * _Pointer_interior_kernel_2 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_interior_kernel_2 = NULL;
	
	
	
	/* <010000, 000000>
 */
	auto __POCHOIR_Guard_3__ = [&]  ( int t, int i0, int i1 )  -> bool {
	return ( !__g_exclusive_0__ ( t + -1, i0, i1 )  && !__g_inclusive_0__ ( t + -1, i0, i1 )  && !__g_inclusive_1__ ( t + -1, i0, i1 )  && !__g_tiny_inclusive_0__ ( t + -1, i0, i1 )  && !__g_tiny_inclusive_1__ ( t + -1, i0, i1 )  );
	 };
	static Pochoir_Guard <2> POCHOIR_Guard_3 ( __POCHOIR_Guard_3__ ); 

	/* <010000, 000000>
 */
	
	
	/* 
	tile_2D_checkerboard_1 - PINCLUSIVE;
	__Pochoir_NULL__ - PNULL
	 */
	/* k_1_0, k_1_1, k_1_2, k_1_3, __Pochoir_NULL_ */ 
	/* 1, 1, 1, 1, 0 */ 
	/* PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PNULL */ 
	/* [0,0], [0,1], [1,0], [1,1], [0] */ 
	/* [2,2], [2,2], [2,2], [2,2], [1] */ 
	/* 
	PMTile (sizes = [2,2], latest_tile_order = 1), terms = 
		PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 1), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 1), item = k_1_0
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 1), item = k_1_1
		PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 1), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 1), item = k_1_2
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 1), item = k_1_3
	 */ 
	static 
	Pochoir_Shape <2> __POCHOIR_Shape__3__ [ ] = {{0, 0, 0}, {-1, 0, -1}, {-1, 0, 1}, {-1, 1, 0}, {-1, -1, 0}, {-1, 0, 0}};
	/* toggle: 2; slopes: [] */
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_cond_boundary_kernel_3__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_boundary_kernel_3__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.11000000000000001 * a(t - 1, i - 1, j) + 0.151 * a(t - 1, i, j) + 0.151 * a(t - 1, i + 1, j) - 0.11000000000000001 * a(t - 1, i, j - 1) - 0.151 * a(t - 1, i, j) - 0.151 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.21000000000000002 * a(t - 1, i - 1, j) + 0.251 * a(t - 1, i, j) + 0.251 * a(t - 1, i + 1, j) - 0.21000000000000002 * a(t - 1, i, j - 1) - 0.251 * a(t - 1, i, j) - 0.251 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.31 * a(t - 1, i - 1, j) + 0.351 * a(t - 1, i, j) + 0.351 * a(t - 1, i + 1, j) - 0.31 * a(t - 1, i, j - 1) - 0.351 * a(t - 1, i, j) - 0.351 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.41 * a(t - 1, i - 1, j) + 0.45099999999999996 * a(t - 1, i, j) + 0.45099999999999996 * a(t - 1, i + 1, j) - 0.41 * a(t - 1, i, j - 1) - 0.45099999999999996 * a(t - 1, i, j) - 0.45099999999999996 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
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
	static __Pointer_cond_boundary_kernel_3__ * _Pointer_cond_boundary_kernel_3 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_boundary_kernel_3 = NULL;
	#undef pmod_lu
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_boundary_kernel_3__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_boundary_kernel_3__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.11000000000000001 * a(t - 1, i - 1, j) + 0.151 * a(t - 1, i, j) + 0.151 * a(t - 1, i + 1, j) - 0.11000000000000001 * a(t - 1, i, j - 1) - 0.151 * a(t - 1, i, j) - 0.151 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.21000000000000002 * a(t - 1, i - 1, j) + 0.251 * a(t - 1, i, j) + 0.251 * a(t - 1, i + 1, j) - 0.21000000000000002 * a(t - 1, i, j - 1) - 0.251 * a(t - 1, i, j) - 0.251 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.31 * a(t - 1, i - 1, j) + 0.351 * a(t - 1, i, j) + 0.351 * a(t - 1, i + 1, j) - 0.31 * a(t - 1, i, j - 1) - 0.351 * a(t - 1, i, j) - 0.351 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.41 * a(t - 1, i - 1, j) + 0.45099999999999996 * a(t - 1, i, j) + 0.45099999999999996 * a(t - 1, i + 1, j) - 0.41 * a(t - 1, i, j - 1) - 0.45099999999999996 * a(t - 1, i, j) - 0.45099999999999996 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
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
	static __Pointer_boundary_kernel_3__ * _Pointer_boundary_kernel_3 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_boundary_kernel_3 = NULL;
	#undef pmod_lu
	
	
	
	/* KNOWN */
	class __Pointer_cond_interior_kernel_3__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_interior_kernel_3__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11000000000000001 * pt_a_1[l_a_stride_1 * (-1)] + 0.151 * pt_a_1[0] + 0.151 * pt_a_1[l_a_stride_1 * (1)] - 0.11000000000000001 * pt_a_1[l_a_stride_0 * (-1)] - 0.151 * pt_a_1[0] - 0.151 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21000000000000002 * pt_a_1[l_a_stride_1 * (-1)] + 0.251 * pt_a_1[0] + 0.251 * pt_a_1[l_a_stride_1 * (1)] - 0.21000000000000002 * pt_a_1[l_a_stride_0 * (-1)] - 0.251 * pt_a_1[0] - 0.251 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.31 * pt_a_1[l_a_stride_1 * (-1)] + 0.351 * pt_a_1[0] + 0.351 * pt_a_1[l_a_stride_1 * (1)] - 0.31 * pt_a_1[l_a_stride_0 * (-1)] - 0.351 * pt_a_1[0] - 0.351 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.41 * pt_a_1[l_a_stride_1 * (-1)] + 0.45099999999999996 * pt_a_1[0] + 0.45099999999999996 * pt_a_1[l_a_stride_1 * (1)] - 0.41 * pt_a_1[l_a_stride_0 * (-1)] - 0.45099999999999996 * pt_a_1[0] - 0.45099999999999996 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
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
	static __Pointer_cond_interior_kernel_3__ * _Pointer_cond_interior_kernel_3 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_interior_kernel_3 = NULL;
	
	
	
	
	/* KNOWN */
	class __Pointer_interior_kernel_3__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_interior_kernel_3__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11000000000000001 * pt_a_1[l_a_stride_1 * (-1)] + 0.151 * pt_a_1[0] + 0.151 * pt_a_1[l_a_stride_1 * (1)] - 0.11000000000000001 * pt_a_1[l_a_stride_0 * (-1)] - 0.151 * pt_a_1[0] - 0.151 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21000000000000002 * pt_a_1[l_a_stride_1 * (-1)] + 0.251 * pt_a_1[0] + 0.251 * pt_a_1[l_a_stride_1 * (1)] - 0.21000000000000002 * pt_a_1[l_a_stride_0 * (-1)] - 0.251 * pt_a_1[0] - 0.251 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.31 * pt_a_1[l_a_stride_1 * (-1)] + 0.351 * pt_a_1[0] + 0.351 * pt_a_1[l_a_stride_1 * (1)] - 0.31 * pt_a_1[l_a_stride_0 * (-1)] - 0.351 * pt_a_1[0] - 0.351 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.41 * pt_a_1[l_a_stride_1 * (-1)] + 0.45099999999999996 * pt_a_1[0] + 0.45099999999999996 * pt_a_1[l_a_stride_1 * (1)] - 0.41 * pt_a_1[l_a_stride_0 * (-1)] - 0.45099999999999996 * pt_a_1[0] - 0.45099999999999996 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
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
	static __Pointer_interior_kernel_3__ * _Pointer_interior_kernel_3 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_interior_kernel_3 = NULL;
	
	
	
	/* <100000, 000000>
 */
	auto __POCHOIR_Guard_4__ = [&]  ( int t, int i0, int i1 )  -> bool {
	return ( !__g_exclusive_1__ ( t + -1, i0, i1 )  && !__g_inclusive_0__ ( t + -1, i0, i1 )  && !__g_inclusive_1__ ( t + -1, i0, i1 )  && !__g_tiny_inclusive_0__ ( t + -1, i0, i1 )  && !__g_tiny_inclusive_1__ ( t + -1, i0, i1 )  );
	 };
	static Pochoir_Guard <2> POCHOIR_Guard_4 ( __POCHOIR_Guard_4__ ); 

	/* <100000, 000000>
 */
	
	
	/* 
	tile_3D_checkerboard_0 - PINCLUSIVE;
	__Pochoir_NULL__ - PNULL
	 */
	/* k_0_0, k_0_1, k_0_2, k_0_3, k_0_4, k_0_5, k_0_6, k_0_7, __Pochoir_NULL_ */ 
	/* 0, 0, 0, 0, 0, 0, 0, 0, 0 */ 
	/* PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PNULL */ 
	/* [0,0,0], [0,0,1], [0,1,0], [0,1,1], [1,0,0], [1,0,1], [1,1,0], [1,1,1], [0] */ 
	/* [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [1] */ 
	/* 
	PMTile (sizes = [2,2,2], latest_tile_order = 0), terms = 
		PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_0
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_1
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_2
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_3
		PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_4
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_5
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_6
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_7
	 */ 
	static 
	Pochoir_Shape <2> __POCHOIR_Shape__4__ [ ] = {{0, 0, 0}, {-1, 0, -1}, {-1, 0, 1}, {-1, 1, 0}, {-1, -1, 0}, {-1, 0, 0}};
	/* toggle: 2; slopes: [] */
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_cond_boundary_kernel_4__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_boundary_kernel_4__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.1 * a(t - 1, i - 1, j) + 0.15 * a(t - 1, i, j) + 0.15 * a(t - 1, i + 1, j) - 0.1 * a(t - 1, i, j - 1) - 0.15 * a(t - 1, i, j) - 0.15 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.2 * a(t - 1, i - 1, j) + 0.25 * a(t - 1, i, j) + 0.25 * a(t - 1, i + 1, j) - 0.2 * a(t - 1, i, j - 1) - 0.25 * a(t - 1, i, j) - 0.25 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.3 * a(t - 1, i - 1, j) + 0.35 * a(t - 1, i, j) + 0.35 * a(t - 1, i + 1, j) - 0.3 * a(t - 1, i, j - 1) - 0.35 * a(t - 1, i, j) - 0.35 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.4 * a(t - 1, i - 1, j) + 0.45 * a(t - 1, i, j) + 0.45 * a(t - 1, i + 1, j) - 0.4 * a(t - 1, i, j - 1) - 0.45 * a(t - 1, i, j) - 0.45 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.5 * a(t - 1, i - 1, j) + 0.55 * a(t - 1, i, j) + 0.55 * a(t - 1, i + 1, j) - 0.5 * a(t - 1, i, j - 1) - 0.55 * a(t - 1, i, j) - 0.55 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.6 * a(t - 1, i - 1, j) + 0.65 * a(t - 1, i, j) + 0.65 * a(t - 1, i + 1, j) - 0.6 * a(t - 1, i, j - 1) - 0.65 * a(t - 1, i, j) - 0.65 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.7 * a(t - 1, i - 1, j) + 0.75 * a(t - 1, i, j) + 0.75 * a(t - 1, i + 1, j) - 0.7 * a(t - 1, i, j - 1) - 0.75 * a(t - 1, i, j) - 0.75 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8 * a(t - 1, i - 1, j) + 0.85 * a(t - 1, i, j) + 0.85 * a(t - 1, i + 1, j) - 0.8 * a(t - 1, i, j - 1) - 0.85 * a(t - 1, i, j) - 0.85 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
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
	static __Pointer_cond_boundary_kernel_4__ * _Pointer_cond_boundary_kernel_4 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_boundary_kernel_4 = NULL;
	#undef pmod_lu
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_boundary_kernel_4__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_boundary_kernel_4__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.1 * a(t - 1, i - 1, j) + 0.15 * a(t - 1, i, j) + 0.15 * a(t - 1, i + 1, j) - 0.1 * a(t - 1, i, j - 1) - 0.15 * a(t - 1, i, j) - 0.15 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.2 * a(t - 1, i - 1, j) + 0.25 * a(t - 1, i, j) + 0.25 * a(t - 1, i + 1, j) - 0.2 * a(t - 1, i, j - 1) - 0.25 * a(t - 1, i, j) - 0.25 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.3 * a(t - 1, i - 1, j) + 0.35 * a(t - 1, i, j) + 0.35 * a(t - 1, i + 1, j) - 0.3 * a(t - 1, i, j - 1) - 0.35 * a(t - 1, i, j) - 0.35 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.4 * a(t - 1, i - 1, j) + 0.45 * a(t - 1, i, j) + 0.45 * a(t - 1, i + 1, j) - 0.4 * a(t - 1, i, j - 1) - 0.45 * a(t - 1, i, j) - 0.45 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.5 * a(t - 1, i - 1, j) + 0.55 * a(t - 1, i, j) + 0.55 * a(t - 1, i + 1, j) - 0.5 * a(t - 1, i, j - 1) - 0.55 * a(t - 1, i, j) - 0.55 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.6 * a(t - 1, i - 1, j) + 0.65 * a(t - 1, i, j) + 0.65 * a(t - 1, i + 1, j) - 0.6 * a(t - 1, i, j - 1) - 0.65 * a(t - 1, i, j) - 0.65 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.7 * a(t - 1, i - 1, j) + 0.75 * a(t - 1, i, j) + 0.75 * a(t - 1, i + 1, j) - 0.7 * a(t - 1, i, j - 1) - 0.75 * a(t - 1, i, j) - 0.75 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8 * a(t - 1, i - 1, j) + 0.85 * a(t - 1, i, j) + 0.85 * a(t - 1, i + 1, j) - 0.8 * a(t - 1, i, j - 1) - 0.85 * a(t - 1, i, j) - 0.85 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
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
	static __Pointer_boundary_kernel_4__ * _Pointer_boundary_kernel_4 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_boundary_kernel_4 = NULL;
	#undef pmod_lu
	
	
	
	/* KNOWN */
	class __Pointer_cond_interior_kernel_4__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_interior_kernel_4__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.1 * pt_a_1[l_a_stride_1 * (-1)] + 0.15 * pt_a_1[0] + 0.15 * pt_a_1[l_a_stride_1 * (1)] - 0.1 * pt_a_1[l_a_stride_0 * (-1)] - 0.15 * pt_a_1[0] - 0.15 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.2 * pt_a_1[l_a_stride_1 * (-1)] + 0.25 * pt_a_1[0] + 0.25 * pt_a_1[l_a_stride_1 * (1)] - 0.2 * pt_a_1[l_a_stride_0 * (-1)] - 0.25 * pt_a_1[0] - 0.25 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.3 * pt_a_1[l_a_stride_1 * (-1)] + 0.35 * pt_a_1[0] + 0.35 * pt_a_1[l_a_stride_1 * (1)] - 0.3 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] - 0.35 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.4 * pt_a_1[l_a_stride_1 * (-1)] + 0.45 * pt_a_1[0] + 0.45 * pt_a_1[l_a_stride_1 * (1)] - 0.4 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] - 0.45 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.5 * pt_a_1[l_a_stride_1 * (-1)] + 0.55 * pt_a_1[0] + 0.55 * pt_a_1[l_a_stride_1 * (1)] - 0.5 * pt_a_1[l_a_stride_0 * (-1)] - 0.55 * pt_a_1[0] - 0.55 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.6 * pt_a_1[l_a_stride_1 * (-1)] + 0.65 * pt_a_1[0] + 0.65 * pt_a_1[l_a_stride_1 * (1)] - 0.6 * pt_a_1[l_a_stride_0 * (-1)] - 0.65 * pt_a_1[0] - 0.65 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.7 * pt_a_1[l_a_stride_1 * (-1)] + 0.75 * pt_a_1[0] + 0.75 * pt_a_1[l_a_stride_1 * (1)] - 0.7 * pt_a_1[l_a_stride_0 * (-1)] - 0.75 * pt_a_1[0] - 0.75 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.8 * pt_a_1[l_a_stride_1 * (-1)] + 0.85 * pt_a_1[0] + 0.85 * pt_a_1[l_a_stride_1 * (1)] - 0.8 * pt_a_1[l_a_stride_0 * (-1)] - 0.85 * pt_a_1[0] - 0.85 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
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
	static __Pointer_cond_interior_kernel_4__ * _Pointer_cond_interior_kernel_4 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_interior_kernel_4 = NULL;
	
	
	
	
	/* KNOWN */
	class __Pointer_interior_kernel_4__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_interior_kernel_4__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.1 * pt_a_1[l_a_stride_1 * (-1)] + 0.15 * pt_a_1[0] + 0.15 * pt_a_1[l_a_stride_1 * (1)] - 0.1 * pt_a_1[l_a_stride_0 * (-1)] - 0.15 * pt_a_1[0] - 0.15 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.2 * pt_a_1[l_a_stride_1 * (-1)] + 0.25 * pt_a_1[0] + 0.25 * pt_a_1[l_a_stride_1 * (1)] - 0.2 * pt_a_1[l_a_stride_0 * (-1)] - 0.25 * pt_a_1[0] - 0.25 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.3 * pt_a_1[l_a_stride_1 * (-1)] + 0.35 * pt_a_1[0] + 0.35 * pt_a_1[l_a_stride_1 * (1)] - 0.3 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] - 0.35 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.4 * pt_a_1[l_a_stride_1 * (-1)] + 0.45 * pt_a_1[0] + 0.45 * pt_a_1[l_a_stride_1 * (1)] - 0.4 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] - 0.45 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.5 * pt_a_1[l_a_stride_1 * (-1)] + 0.55 * pt_a_1[0] + 0.55 * pt_a_1[l_a_stride_1 * (1)] - 0.5 * pt_a_1[l_a_stride_0 * (-1)] - 0.55 * pt_a_1[0] - 0.55 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.6 * pt_a_1[l_a_stride_1 * (-1)] + 0.65 * pt_a_1[0] + 0.65 * pt_a_1[l_a_stride_1 * (1)] - 0.6 * pt_a_1[l_a_stride_0 * (-1)] - 0.65 * pt_a_1[0] - 0.65 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.7 * pt_a_1[l_a_stride_1 * (-1)] + 0.75 * pt_a_1[0] + 0.75 * pt_a_1[l_a_stride_1 * (1)] - 0.7 * pt_a_1[l_a_stride_0 * (-1)] - 0.75 * pt_a_1[0] - 0.75 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.8 * pt_a_1[l_a_stride_1 * (-1)] + 0.85 * pt_a_1[0] + 0.85 * pt_a_1[l_a_stride_1 * (1)] - 0.8 * pt_a_1[l_a_stride_0 * (-1)] - 0.85 * pt_a_1[0] - 0.85 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
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
	static __Pointer_interior_kernel_4__ * _Pointer_interior_kernel_4 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_interior_kernel_4 = NULL;
	
	
	
	/* <101000, 101000>
 */
	auto __POCHOIR_Guard_5__ = [&]  ( int t, int i0, int i1 )  -> bool {
	return ( __g_exclusive_0__ ( t + -1, i0, i1 )  && !__g_exclusive_1__ ( t + -1, i0, i1 )  && __g_inclusive_0__ ( t + -1, i0, i1 )  && !__g_inclusive_1__ ( t + -1, i0, i1 )  && !__g_tiny_inclusive_0__ ( t + -1, i0, i1 )  && !__g_tiny_inclusive_1__ ( t + -1, i0, i1 )  );
	 };
	static Pochoir_Guard <2> POCHOIR_Guard_5 ( __POCHOIR_Guard_5__ ); 

	/* <101000, 101000>
 */
	
	
	/* 
	tile_3D_checkerboard_0 - PSERIAL;
	tile_1D_checkerboard_2 - PSERIAL;
	__Pochoir_NULL__ - PNULL
	 */
	/* k_0_0, k_0_1, k_0_2, k_0_3, k_0_4, k_0_5, k_0_6, k_0_7, k_2_0, k_2_1, __Pochoir_NULL_ */ 
	/* 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0 */ 
	/* PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PNULL */ 
	/* [0,0,0], [0,0,1], [0,1,0], [0,1,1], [1,0,0], [1,0,1], [1,1,0], [1,1,1], [0], [1], [0] */ 
	/* [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2], [2], [1] */ 
	/* 
	PMTile (sizes = [2,2,2], latest_tile_order = 2), terms = 
		PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 2), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_0
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_1
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_2
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_3
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 2), item = k_2_0
		PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 2), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_4
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_5
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_6
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_7
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 2), item = k_2_1
	 */ 
	static 
	Pochoir_Shape <2> __POCHOIR_Shape__5__ [ ] = {{0, 0, 0}, {-1, 0, -1}, {-1, 0, 1}, {-1, 1, 0}, {-1, -1, 0}, {-1, 0, 0}};
	/* toggle: 2; slopes: [] */
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_cond_boundary_kernel_5__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_boundary_kernel_5__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.1 * a(t - 1, i - 1, j) + 0.15 * a(t - 1, i, j) + 0.15 * a(t - 1, i + 1, j) - 0.1 * a(t - 1, i, j - 1) - 0.15 * a(t - 1, i, j) - 0.15 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.2 * a(t - 1, i - 1, j) + 0.25 * a(t - 1, i, j) + 0.25 * a(t - 1, i + 1, j) - 0.2 * a(t - 1, i, j - 1) - 0.25 * a(t - 1, i, j) - 0.25 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.3 * a(t - 1, i - 1, j) + 0.35 * a(t - 1, i, j) + 0.35 * a(t - 1, i + 1, j) - 0.3 * a(t - 1, i, j - 1) - 0.35 * a(t - 1, i, j) - 0.35 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.4 * a(t - 1, i - 1, j) + 0.45 * a(t - 1, i, j) + 0.45 * a(t - 1, i + 1, j) - 0.4 * a(t - 1, i, j - 1) - 0.45 * a(t - 1, i, j) - 0.45 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.12 * a(t - 1, i - 1, j) + 0.152 * a(t - 1, i, j) + 0.152 * a(t - 1, i + 1, j) - 0.12 * a(t - 1, i, j - 1) - 0.152 * a(t - 1, i, j) - 0.152 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.5 * a(t - 1, i - 1, j) + 0.55 * a(t - 1, i, j) + 0.55 * a(t - 1, i + 1, j) - 0.5 * a(t - 1, i, j - 1) - 0.55 * a(t - 1, i, j) - 0.55 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.6 * a(t - 1, i - 1, j) + 0.65 * a(t - 1, i, j) + 0.65 * a(t - 1, i + 1, j) - 0.6 * a(t - 1, i, j - 1) - 0.65 * a(t - 1, i, j) - 0.65 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.7 * a(t - 1, i - 1, j) + 0.75 * a(t - 1, i, j) + 0.75 * a(t - 1, i + 1, j) - 0.7 * a(t - 1, i, j - 1) - 0.75 * a(t - 1, i, j) - 0.75 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8 * a(t - 1, i - 1, j) + 0.85 * a(t - 1, i, j) + 0.85 * a(t - 1, i + 1, j) - 0.8 * a(t - 1, i, j - 1) - 0.85 * a(t - 1, i, j) - 0.85 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.22000000000000003 * a(t - 1, i - 1, j) + 0.252 * a(t - 1, i, j) + 0.252 * a(t - 1, i + 1, j) - 0.22000000000000003 * a(t - 1, i, j - 1) - 0.252 * a(t - 1, i, j) - 0.252 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
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
	static __Pointer_cond_boundary_kernel_5__ * _Pointer_cond_boundary_kernel_5 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_boundary_kernel_5 = NULL;
	#undef pmod_lu
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_boundary_kernel_5__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_boundary_kernel_5__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.1 * a(t - 1, i - 1, j) + 0.15 * a(t - 1, i, j) + 0.15 * a(t - 1, i + 1, j) - 0.1 * a(t - 1, i, j - 1) - 0.15 * a(t - 1, i, j) - 0.15 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.2 * a(t - 1, i - 1, j) + 0.25 * a(t - 1, i, j) + 0.25 * a(t - 1, i + 1, j) - 0.2 * a(t - 1, i, j - 1) - 0.25 * a(t - 1, i, j) - 0.25 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.3 * a(t - 1, i - 1, j) + 0.35 * a(t - 1, i, j) + 0.35 * a(t - 1, i + 1, j) - 0.3 * a(t - 1, i, j - 1) - 0.35 * a(t - 1, i, j) - 0.35 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.4 * a(t - 1, i - 1, j) + 0.45 * a(t - 1, i, j) + 0.45 * a(t - 1, i + 1, j) - 0.4 * a(t - 1, i, j - 1) - 0.45 * a(t - 1, i, j) - 0.45 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.12 * a(t - 1, i - 1, j) + 0.152 * a(t - 1, i, j) + 0.152 * a(t - 1, i + 1, j) - 0.12 * a(t - 1, i, j - 1) - 0.152 * a(t - 1, i, j) - 0.152 * a(t - 1, i, j + 1);
	
	
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.5 * a(t - 1, i - 1, j) + 0.55 * a(t - 1, i, j) + 0.55 * a(t - 1, i + 1, j) - 0.5 * a(t - 1, i, j - 1) - 0.55 * a(t - 1, i, j) - 0.55 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.6 * a(t - 1, i - 1, j) + 0.65 * a(t - 1, i, j) + 0.65 * a(t - 1, i + 1, j) - 0.6 * a(t - 1, i, j - 1) - 0.65 * a(t - 1, i, j) - 0.65 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.7 * a(t - 1, i - 1, j) + 0.75 * a(t - 1, i, j) + 0.75 * a(t - 1, i + 1, j) - 0.7 * a(t - 1, i, j - 1) - 0.75 * a(t - 1, i, j) - 0.75 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8 * a(t - 1, i - 1, j) + 0.85 * a(t - 1, i, j) + 0.85 * a(t - 1, i + 1, j) - 0.8 * a(t - 1, i, j - 1) - 0.85 * a(t - 1, i, j) - 0.85 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.22000000000000003 * a(t - 1, i - 1, j) + 0.252 * a(t - 1, i, j) + 0.252 * a(t - 1, i + 1, j) - 0.22000000000000003 * a(t - 1, i, j - 1) - 0.252 * a(t - 1, i, j) - 0.252 * a(t - 1, i, j + 1);
	
	
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
	static __Pointer_boundary_kernel_5__ * _Pointer_boundary_kernel_5 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_boundary_kernel_5 = NULL;
	#undef pmod_lu
	
	
	
	/* KNOWN */
	class __Pointer_cond_interior_kernel_5__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_interior_kernel_5__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.1 * pt_a_1[l_a_stride_1 * (-1)] + 0.15 * pt_a_1[0] + 0.15 * pt_a_1[l_a_stride_1 * (1)] - 0.1 * pt_a_1[l_a_stride_0 * (-1)] - 0.15 * pt_a_1[0] - 0.15 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.2 * pt_a_1[l_a_stride_1 * (-1)] + 0.25 * pt_a_1[0] + 0.25 * pt_a_1[l_a_stride_1 * (1)] - 0.2 * pt_a_1[l_a_stride_0 * (-1)] - 0.25 * pt_a_1[0] - 0.25 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.3 * pt_a_1[l_a_stride_1 * (-1)] + 0.35 * pt_a_1[0] + 0.35 * pt_a_1[l_a_stride_1 * (1)] - 0.3 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] - 0.35 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.4 * pt_a_1[l_a_stride_1 * (-1)] + 0.45 * pt_a_1[0] + 0.45 * pt_a_1[l_a_stride_1 * (1)] - 0.4 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] - 0.45 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.12 * pt_a_1[l_a_stride_1 * (-1)] + 0.152 * pt_a_1[0] + 0.152 * pt_a_1[l_a_stride_1 * (1)] - 0.12 * pt_a_1[l_a_stride_0 * (-1)] - 0.152 * pt_a_1[0] - 0.152 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.5 * pt_a_1[l_a_stride_1 * (-1)] + 0.55 * pt_a_1[0] + 0.55 * pt_a_1[l_a_stride_1 * (1)] - 0.5 * pt_a_1[l_a_stride_0 * (-1)] - 0.55 * pt_a_1[0] - 0.55 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.6 * pt_a_1[l_a_stride_1 * (-1)] + 0.65 * pt_a_1[0] + 0.65 * pt_a_1[l_a_stride_1 * (1)] - 0.6 * pt_a_1[l_a_stride_0 * (-1)] - 0.65 * pt_a_1[0] - 0.65 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.7 * pt_a_1[l_a_stride_1 * (-1)] + 0.75 * pt_a_1[0] + 0.75 * pt_a_1[l_a_stride_1 * (1)] - 0.7 * pt_a_1[l_a_stride_0 * (-1)] - 0.75 * pt_a_1[0] - 0.75 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.8 * pt_a_1[l_a_stride_1 * (-1)] + 0.85 * pt_a_1[0] + 0.85 * pt_a_1[l_a_stride_1 * (1)] - 0.8 * pt_a_1[l_a_stride_0 * (-1)] - 0.85 * pt_a_1[0] - 0.85 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.22000000000000003 * pt_a_1[l_a_stride_1 * (-1)] + 0.252 * pt_a_1[0] + 0.252 * pt_a_1[l_a_stride_1 * (1)] - 0.22000000000000003 * pt_a_1[l_a_stride_0 * (-1)] - 0.252 * pt_a_1[0] - 0.252 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
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
	static __Pointer_cond_interior_kernel_5__ * _Pointer_cond_interior_kernel_5 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_interior_kernel_5 = NULL;
	
	
	
	
	/* KNOWN */
	class __Pointer_interior_kernel_5__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_interior_kernel_5__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.1 * pt_a_1[l_a_stride_1 * (-1)] + 0.15 * pt_a_1[0] + 0.15 * pt_a_1[l_a_stride_1 * (1)] - 0.1 * pt_a_1[l_a_stride_0 * (-1)] - 0.15 * pt_a_1[0] - 0.15 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.2 * pt_a_1[l_a_stride_1 * (-1)] + 0.25 * pt_a_1[0] + 0.25 * pt_a_1[l_a_stride_1 * (1)] - 0.2 * pt_a_1[l_a_stride_0 * (-1)] - 0.25 * pt_a_1[0] - 0.25 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.3 * pt_a_1[l_a_stride_1 * (-1)] + 0.35 * pt_a_1[0] + 0.35 * pt_a_1[l_a_stride_1 * (1)] - 0.3 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] - 0.35 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.4 * pt_a_1[l_a_stride_1 * (-1)] + 0.45 * pt_a_1[0] + 0.45 * pt_a_1[l_a_stride_1 * (1)] - 0.4 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] - 0.45 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.12 * pt_a_1[l_a_stride_1 * (-1)] + 0.152 * pt_a_1[0] + 0.152 * pt_a_1[l_a_stride_1 * (1)] - 0.12 * pt_a_1[l_a_stride_0 * (-1)] - 0.152 * pt_a_1[0] - 0.152 * pt_a_1[l_a_stride_0 * (1)];
	
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.5 * pt_a_1[l_a_stride_1 * (-1)] + 0.55 * pt_a_1[0] + 0.55 * pt_a_1[l_a_stride_1 * (1)] - 0.5 * pt_a_1[l_a_stride_0 * (-1)] - 0.55 * pt_a_1[0] - 0.55 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.6 * pt_a_1[l_a_stride_1 * (-1)] + 0.65 * pt_a_1[0] + 0.65 * pt_a_1[l_a_stride_1 * (1)] - 0.6 * pt_a_1[l_a_stride_0 * (-1)] - 0.65 * pt_a_1[0] - 0.65 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.7 * pt_a_1[l_a_stride_1 * (-1)] + 0.75 * pt_a_1[0] + 0.75 * pt_a_1[l_a_stride_1 * (1)] - 0.7 * pt_a_1[l_a_stride_0 * (-1)] - 0.75 * pt_a_1[0] - 0.75 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.8 * pt_a_1[l_a_stride_1 * (-1)] + 0.85 * pt_a_1[0] + 0.85 * pt_a_1[l_a_stride_1 * (1)] - 0.8 * pt_a_1[l_a_stride_0 * (-1)] - 0.85 * pt_a_1[0] - 0.85 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.22000000000000003 * pt_a_1[l_a_stride_1 * (-1)] + 0.252 * pt_a_1[0] + 0.252 * pt_a_1[l_a_stride_1 * (1)] - 0.22000000000000003 * pt_a_1[l_a_stride_0 * (-1)] - 0.252 * pt_a_1[0] - 0.252 * pt_a_1[l_a_stride_0 * (1)];
	
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
	static __Pointer_interior_kernel_5__ * _Pointer_interior_kernel_5 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_interior_kernel_5 = NULL;
	
	
	
	/* <101000, 000000>
 */
	auto __POCHOIR_Guard_6__ = [&]  ( int t, int i0, int i1 )  -> bool {
	return ( !__g_exclusive_1__ ( t + -1, i0, i1 )  && !__g_inclusive_1__ ( t + -1, i0, i1 )  && !__g_tiny_inclusive_0__ ( t + -1, i0, i1 )  && !__g_tiny_inclusive_1__ ( t + -1, i0, i1 )  );
	 };
	static Pochoir_Guard <2> POCHOIR_Guard_6 ( __POCHOIR_Guard_6__ ); 

	/* <101000, 000000>
 */
	
	
	/* 
	tile_3D_checkerboard_0 - PINCLUSIVE;
	tile_1D_checkerboard_2 - PINCLUSIVE;
	__Pochoir_NULL__ - PNULL
	 */
	/* k_0_0, k_0_1, k_0_2, k_0_3, k_0_4, k_0_5, k_0_6, k_0_7, k_2_0, k_2_1, __Pochoir_NULL_ */ 
	/* 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0 */ 
	/* PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PNULL */ 
	/* [0,0,0], [0,0,1], [0,1,0], [0,1,1], [1,0,0], [1,0,1], [1,1,0], [1,1,1], [0], [1], [0] */ 
	/* [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2], [2], [1] */ 
	/* 
	PMTile (sizes = [2,2,2], latest_tile_order = 2), terms = 
		PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 2), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_0
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_1
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_2
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_3
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 2), item = k_2_0
		PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 2), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_4
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_5
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_6
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_7
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 2), item = k_2_1
	 */ 
	static 
	Pochoir_Shape <2> __POCHOIR_Shape__6__ [ ] = {{0, 0, 0}, {-1, 0, -1}, {-1, 0, 1}, {-1, 1, 0}, {-1, -1, 0}, {-1, 0, 0}};
	/* toggle: 2; slopes: [] */
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_cond_boundary_kernel_6__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_boundary_kernel_6__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.1 * a(t - 1, i - 1, j) + 0.15 * a(t - 1, i, j) + 0.15 * a(t - 1, i + 1, j) - 0.1 * a(t - 1, i, j - 1) - 0.15 * a(t - 1, i, j) - 0.15 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.2 * a(t - 1, i - 1, j) + 0.25 * a(t - 1, i, j) + 0.25 * a(t - 1, i + 1, j) - 0.2 * a(t - 1, i, j - 1) - 0.25 * a(t - 1, i, j) - 0.25 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.3 * a(t - 1, i - 1, j) + 0.35 * a(t - 1, i, j) + 0.35 * a(t - 1, i + 1, j) - 0.3 * a(t - 1, i, j - 1) - 0.35 * a(t - 1, i, j) - 0.35 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.4 * a(t - 1, i - 1, j) + 0.45 * a(t - 1, i, j) + 0.45 * a(t - 1, i + 1, j) - 0.4 * a(t - 1, i, j - 1) - 0.45 * a(t - 1, i, j) - 0.45 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.12 * a(t - 1, i - 1, j) + 0.152 * a(t - 1, i, j) + 0.152 * a(t - 1, i + 1, j) - 0.12 * a(t - 1, i, j - 1) - 0.152 * a(t - 1, i, j) - 0.152 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.5 * a(t - 1, i - 1, j) + 0.55 * a(t - 1, i, j) + 0.55 * a(t - 1, i + 1, j) - 0.5 * a(t - 1, i, j - 1) - 0.55 * a(t - 1, i, j) - 0.55 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.6 * a(t - 1, i - 1, j) + 0.65 * a(t - 1, i, j) + 0.65 * a(t - 1, i + 1, j) - 0.6 * a(t - 1, i, j - 1) - 0.65 * a(t - 1, i, j) - 0.65 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.7 * a(t - 1, i - 1, j) + 0.75 * a(t - 1, i, j) + 0.75 * a(t - 1, i + 1, j) - 0.7 * a(t - 1, i, j - 1) - 0.75 * a(t - 1, i, j) - 0.75 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8 * a(t - 1, i - 1, j) + 0.85 * a(t - 1, i, j) + 0.85 * a(t - 1, i + 1, j) - 0.8 * a(t - 1, i, j - 1) - 0.85 * a(t - 1, i, j) - 0.85 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.22000000000000003 * a(t - 1, i - 1, j) + 0.252 * a(t - 1, i, j) + 0.252 * a(t - 1, i + 1, j) - 0.22000000000000003 * a(t - 1, i, j - 1) - 0.252 * a(t - 1, i, j) - 0.252 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
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
	static __Pointer_cond_boundary_kernel_6__ * _Pointer_cond_boundary_kernel_6 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_boundary_kernel_6 = NULL;
	#undef pmod_lu
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_boundary_kernel_6__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_boundary_kernel_6__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.1 * a(t - 1, i - 1, j) + 0.15 * a(t - 1, i, j) + 0.15 * a(t - 1, i + 1, j) - 0.1 * a(t - 1, i, j - 1) - 0.15 * a(t - 1, i, j) - 0.15 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.2 * a(t - 1, i - 1, j) + 0.25 * a(t - 1, i, j) + 0.25 * a(t - 1, i + 1, j) - 0.2 * a(t - 1, i, j - 1) - 0.25 * a(t - 1, i, j) - 0.25 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.3 * a(t - 1, i - 1, j) + 0.35 * a(t - 1, i, j) + 0.35 * a(t - 1, i + 1, j) - 0.3 * a(t - 1, i, j - 1) - 0.35 * a(t - 1, i, j) - 0.35 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.4 * a(t - 1, i - 1, j) + 0.45 * a(t - 1, i, j) + 0.45 * a(t - 1, i + 1, j) - 0.4 * a(t - 1, i, j - 1) - 0.45 * a(t - 1, i, j) - 0.45 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.12 * a(t - 1, i - 1, j) + 0.152 * a(t - 1, i, j) + 0.152 * a(t - 1, i + 1, j) - 0.12 * a(t - 1, i, j - 1) - 0.152 * a(t - 1, i, j) - 0.152 * a(t - 1, i, j + 1);
	
	
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.5 * a(t - 1, i - 1, j) + 0.55 * a(t - 1, i, j) + 0.55 * a(t - 1, i + 1, j) - 0.5 * a(t - 1, i, j - 1) - 0.55 * a(t - 1, i, j) - 0.55 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.6 * a(t - 1, i - 1, j) + 0.65 * a(t - 1, i, j) + 0.65 * a(t - 1, i + 1, j) - 0.6 * a(t - 1, i, j - 1) - 0.65 * a(t - 1, i, j) - 0.65 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.7 * a(t - 1, i - 1, j) + 0.75 * a(t - 1, i, j) + 0.75 * a(t - 1, i + 1, j) - 0.7 * a(t - 1, i, j - 1) - 0.75 * a(t - 1, i, j) - 0.75 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8 * a(t - 1, i - 1, j) + 0.85 * a(t - 1, i, j) + 0.85 * a(t - 1, i + 1, j) - 0.8 * a(t - 1, i, j - 1) - 0.85 * a(t - 1, i, j) - 0.85 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.22000000000000003 * a(t - 1, i - 1, j) + 0.252 * a(t - 1, i, j) + 0.252 * a(t - 1, i + 1, j) - 0.22000000000000003 * a(t - 1, i, j - 1) - 0.252 * a(t - 1, i, j) - 0.252 * a(t - 1, i, j + 1);
	
	
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
	static __Pointer_boundary_kernel_6__ * _Pointer_boundary_kernel_6 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_boundary_kernel_6 = NULL;
	#undef pmod_lu
	
	
	
	/* KNOWN */
	class __Pointer_cond_interior_kernel_6__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_interior_kernel_6__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.1 * pt_a_1[l_a_stride_1 * (-1)] + 0.15 * pt_a_1[0] + 0.15 * pt_a_1[l_a_stride_1 * (1)] - 0.1 * pt_a_1[l_a_stride_0 * (-1)] - 0.15 * pt_a_1[0] - 0.15 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.2 * pt_a_1[l_a_stride_1 * (-1)] + 0.25 * pt_a_1[0] + 0.25 * pt_a_1[l_a_stride_1 * (1)] - 0.2 * pt_a_1[l_a_stride_0 * (-1)] - 0.25 * pt_a_1[0] - 0.25 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.3 * pt_a_1[l_a_stride_1 * (-1)] + 0.35 * pt_a_1[0] + 0.35 * pt_a_1[l_a_stride_1 * (1)] - 0.3 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] - 0.35 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.4 * pt_a_1[l_a_stride_1 * (-1)] + 0.45 * pt_a_1[0] + 0.45 * pt_a_1[l_a_stride_1 * (1)] - 0.4 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] - 0.45 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.12 * pt_a_1[l_a_stride_1 * (-1)] + 0.152 * pt_a_1[0] + 0.152 * pt_a_1[l_a_stride_1 * (1)] - 0.12 * pt_a_1[l_a_stride_0 * (-1)] - 0.152 * pt_a_1[0] - 0.152 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.5 * pt_a_1[l_a_stride_1 * (-1)] + 0.55 * pt_a_1[0] + 0.55 * pt_a_1[l_a_stride_1 * (1)] - 0.5 * pt_a_1[l_a_stride_0 * (-1)] - 0.55 * pt_a_1[0] - 0.55 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.6 * pt_a_1[l_a_stride_1 * (-1)] + 0.65 * pt_a_1[0] + 0.65 * pt_a_1[l_a_stride_1 * (1)] - 0.6 * pt_a_1[l_a_stride_0 * (-1)] - 0.65 * pt_a_1[0] - 0.65 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.7 * pt_a_1[l_a_stride_1 * (-1)] + 0.75 * pt_a_1[0] + 0.75 * pt_a_1[l_a_stride_1 * (1)] - 0.7 * pt_a_1[l_a_stride_0 * (-1)] - 0.75 * pt_a_1[0] - 0.75 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.8 * pt_a_1[l_a_stride_1 * (-1)] + 0.85 * pt_a_1[0] + 0.85 * pt_a_1[l_a_stride_1 * (1)] - 0.8 * pt_a_1[l_a_stride_0 * (-1)] - 0.85 * pt_a_1[0] - 0.85 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.22000000000000003 * pt_a_1[l_a_stride_1 * (-1)] + 0.252 * pt_a_1[0] + 0.252 * pt_a_1[l_a_stride_1 * (1)] - 0.22000000000000003 * pt_a_1[l_a_stride_0 * (-1)] - 0.252 * pt_a_1[0] - 0.252 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
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
	static __Pointer_cond_interior_kernel_6__ * _Pointer_cond_interior_kernel_6 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_interior_kernel_6 = NULL;
	
	
	
	
	/* KNOWN */
	class __Pointer_interior_kernel_6__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_interior_kernel_6__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.1 * pt_a_1[l_a_stride_1 * (-1)] + 0.15 * pt_a_1[0] + 0.15 * pt_a_1[l_a_stride_1 * (1)] - 0.1 * pt_a_1[l_a_stride_0 * (-1)] - 0.15 * pt_a_1[0] - 0.15 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.2 * pt_a_1[l_a_stride_1 * (-1)] + 0.25 * pt_a_1[0] + 0.25 * pt_a_1[l_a_stride_1 * (1)] - 0.2 * pt_a_1[l_a_stride_0 * (-1)] - 0.25 * pt_a_1[0] - 0.25 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.3 * pt_a_1[l_a_stride_1 * (-1)] + 0.35 * pt_a_1[0] + 0.35 * pt_a_1[l_a_stride_1 * (1)] - 0.3 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] - 0.35 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.4 * pt_a_1[l_a_stride_1 * (-1)] + 0.45 * pt_a_1[0] + 0.45 * pt_a_1[l_a_stride_1 * (1)] - 0.4 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] - 0.45 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.12 * pt_a_1[l_a_stride_1 * (-1)] + 0.152 * pt_a_1[0] + 0.152 * pt_a_1[l_a_stride_1 * (1)] - 0.12 * pt_a_1[l_a_stride_0 * (-1)] - 0.152 * pt_a_1[0] - 0.152 * pt_a_1[l_a_stride_0 * (1)];
	
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.5 * pt_a_1[l_a_stride_1 * (-1)] + 0.55 * pt_a_1[0] + 0.55 * pt_a_1[l_a_stride_1 * (1)] - 0.5 * pt_a_1[l_a_stride_0 * (-1)] - 0.55 * pt_a_1[0] - 0.55 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.6 * pt_a_1[l_a_stride_1 * (-1)] + 0.65 * pt_a_1[0] + 0.65 * pt_a_1[l_a_stride_1 * (1)] - 0.6 * pt_a_1[l_a_stride_0 * (-1)] - 0.65 * pt_a_1[0] - 0.65 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.7 * pt_a_1[l_a_stride_1 * (-1)] + 0.75 * pt_a_1[0] + 0.75 * pt_a_1[l_a_stride_1 * (1)] - 0.7 * pt_a_1[l_a_stride_0 * (-1)] - 0.75 * pt_a_1[0] - 0.75 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.8 * pt_a_1[l_a_stride_1 * (-1)] + 0.85 * pt_a_1[0] + 0.85 * pt_a_1[l_a_stride_1 * (1)] - 0.8 * pt_a_1[l_a_stride_0 * (-1)] - 0.85 * pt_a_1[0] - 0.85 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.22000000000000003 * pt_a_1[l_a_stride_1 * (-1)] + 0.252 * pt_a_1[0] + 0.252 * pt_a_1[l_a_stride_1 * (1)] - 0.22000000000000003 * pt_a_1[l_a_stride_0 * (-1)] - 0.252 * pt_a_1[0] - 0.252 * pt_a_1[l_a_stride_0 * (1)];
	
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
	static __Pointer_interior_kernel_6__ * _Pointer_interior_kernel_6 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_interior_kernel_6 = NULL;
	
	
	
	/* <101100, 101000>
 */
	auto __POCHOIR_Guard_7__ = [&]  ( int t, int i0, int i1 )  -> bool {
	return ( __g_exclusive_0__ ( t + -1, i0, i1 )  && !__g_exclusive_1__ ( t + -1, i0, i1 )  && __g_inclusive_0__ ( t + -1, i0, i1 )  && !__g_tiny_inclusive_0__ ( t + -1, i0, i1 )  && !__g_tiny_inclusive_1__ ( t + -1, i0, i1 )  );
	 };
	static Pochoir_Guard <2> POCHOIR_Guard_7 ( __POCHOIR_Guard_7__ ); 

	/* <101100, 101000>
 */
	
	
	/* 
	tile_3D_checkerboard_0 - PSERIAL;
	tile_1D_checkerboard_2 - PSERIAL;
	tile_3D_checkerboard_3 - PINCLUSIVE;
	__Pochoir_NULL__ - PNULL
	 */
	/* k_0_0, k_0_1, k_0_2, k_0_3, k_0_4, k_0_5, k_0_6, k_0_7, k_2_0, k_2_1, k_3_0, k_3_1, k_3_2, k_3_3, k_3_4, k_3_5, k_3_6, k_3_7, __Pochoir_NULL_ */ 
	/* 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 0 */ 
	/* PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PNULL */ 
	/* [0,0,0], [0,0,1], [0,1,0], [0,1,1], [1,0,0], [1,0,1], [1,1,0], [1,1,1], [0], [1], [0,0,0], [0,0,1], [0,1,0], [0,1,1], [1,0,0], [1,0,1], [1,1,0], [1,1,1], [0] */ 
	/* [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2], [2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [1] */ 
	/* 
	PMTile (sizes = [2,2,2], latest_tile_order = 3), terms = 
		PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_0
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_1
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_2
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_3
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 2), item = k_2_0
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = k_3_0
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = k_3_1
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = k_3_2
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = k_3_3
		PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_4
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_5
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_6
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_7
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 2), item = k_2_1
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = k_3_4
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = k_3_5
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = k_3_6
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = k_3_7
	 */ 
	static 
	Pochoir_Shape <2> __POCHOIR_Shape__7__ [ ] = {{0, 0, 0}, {-1, 0, -1}, {-1, 0, 1}, {-1, 1, 0}, {-1, -1, 0}, {-1, 0, 0}};
	/* toggle: 2; slopes: [] */
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_cond_boundary_kernel_7__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_boundary_kernel_7__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.1 * a(t - 1, i - 1, j) + 0.15 * a(t - 1, i, j) + 0.15 * a(t - 1, i + 1, j) - 0.1 * a(t - 1, i, j - 1) - 0.15 * a(t - 1, i, j) - 0.15 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.2 * a(t - 1, i - 1, j) + 0.25 * a(t - 1, i, j) + 0.25 * a(t - 1, i + 1, j) - 0.2 * a(t - 1, i, j - 1) - 0.25 * a(t - 1, i, j) - 0.25 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.3 * a(t - 1, i - 1, j) + 0.35 * a(t - 1, i, j) + 0.35 * a(t - 1, i + 1, j) - 0.3 * a(t - 1, i, j - 1) - 0.35 * a(t - 1, i, j) - 0.35 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.4 * a(t - 1, i - 1, j) + 0.45 * a(t - 1, i, j) + 0.45 * a(t - 1, i + 1, j) - 0.4 * a(t - 1, i, j - 1) - 0.45 * a(t - 1, i, j) - 0.45 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.12 * a(t - 1, i - 1, j) + 0.152 * a(t - 1, i, j) + 0.152 * a(t - 1, i + 1, j) - 0.12 * a(t - 1, i, j - 1) - 0.152 * a(t - 1, i, j) - 0.152 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.13 * a(t - 1, i - 1, j) + 0.153 * a(t - 1, i, j) + 0.153 * a(t - 1, i + 1, j) - 0.13 * a(t - 1, i, j - 1) - 0.153 * a(t - 1, i, j) - 0.153 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.22999999999999998 * a(t - 1, i - 1, j) + 0.253 * a(t - 1, i, j) + 0.253 * a(t - 1, i + 1, j) - 0.22999999999999998 * a(t - 1, i, j - 1) - 0.253 * a(t - 1, i, j) - 0.253 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.32999999999999996 * a(t - 1, i - 1, j) + 0.35300000000000004 * a(t - 1, i, j) + 0.35300000000000004 * a(t - 1, i + 1, j) - 0.32999999999999996 * a(t - 1, i, j - 1) - 0.35300000000000004 * a(t - 1, i, j) - 0.35300000000000004 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.43 * a(t - 1, i - 1, j) + 0.453 * a(t - 1, i, j) + 0.453 * a(t - 1, i + 1, j) - 0.43 * a(t - 1, i, j - 1) - 0.453 * a(t - 1, i, j) - 0.453 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.5 * a(t - 1, i - 1, j) + 0.55 * a(t - 1, i, j) + 0.55 * a(t - 1, i + 1, j) - 0.5 * a(t - 1, i, j - 1) - 0.55 * a(t - 1, i, j) - 0.55 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.6 * a(t - 1, i - 1, j) + 0.65 * a(t - 1, i, j) + 0.65 * a(t - 1, i + 1, j) - 0.6 * a(t - 1, i, j - 1) - 0.65 * a(t - 1, i, j) - 0.65 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.7 * a(t - 1, i - 1, j) + 0.75 * a(t - 1, i, j) + 0.75 * a(t - 1, i + 1, j) - 0.7 * a(t - 1, i, j - 1) - 0.75 * a(t - 1, i, j) - 0.75 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8 * a(t - 1, i - 1, j) + 0.85 * a(t - 1, i, j) + 0.85 * a(t - 1, i + 1, j) - 0.8 * a(t - 1, i, j - 1) - 0.85 * a(t - 1, i, j) - 0.85 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.22000000000000003 * a(t - 1, i - 1, j) + 0.252 * a(t - 1, i, j) + 0.252 * a(t - 1, i + 1, j) - 0.22000000000000003 * a(t - 1, i, j - 1) - 0.252 * a(t - 1, i, j) - 0.252 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.53 * a(t - 1, i - 1, j) + 0.553 * a(t - 1, i, j) + 0.553 * a(t - 1, i + 1, j) - 0.53 * a(t - 1, i, j - 1) - 0.553 * a(t - 1, i, j) - 0.553 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.63 * a(t - 1, i - 1, j) + 0.653 * a(t - 1, i, j) + 0.653 * a(t - 1, i + 1, j) - 0.63 * a(t - 1, i, j - 1) - 0.653 * a(t - 1, i, j) - 0.653 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.73 * a(t - 1, i - 1, j) + 0.753 * a(t - 1, i, j) + 0.753 * a(t - 1, i + 1, j) - 0.73 * a(t - 1, i, j - 1) - 0.753 * a(t - 1, i, j) - 0.753 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8300000000000001 * a(t - 1, i - 1, j) + 0.853 * a(t - 1, i, j) + 0.853 * a(t - 1, i + 1, j) - 0.8300000000000001 * a(t - 1, i, j - 1) - 0.853 * a(t - 1, i, j) - 0.853 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
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
	static __Pointer_cond_boundary_kernel_7__ * _Pointer_cond_boundary_kernel_7 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_boundary_kernel_7 = NULL;
	#undef pmod_lu
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_boundary_kernel_7__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_boundary_kernel_7__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.1 * a(t - 1, i - 1, j) + 0.15 * a(t - 1, i, j) + 0.15 * a(t - 1, i + 1, j) - 0.1 * a(t - 1, i, j - 1) - 0.15 * a(t - 1, i, j) - 0.15 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.2 * a(t - 1, i - 1, j) + 0.25 * a(t - 1, i, j) + 0.25 * a(t - 1, i + 1, j) - 0.2 * a(t - 1, i, j - 1) - 0.25 * a(t - 1, i, j) - 0.25 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.3 * a(t - 1, i - 1, j) + 0.35 * a(t - 1, i, j) + 0.35 * a(t - 1, i + 1, j) - 0.3 * a(t - 1, i, j - 1) - 0.35 * a(t - 1, i, j) - 0.35 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.4 * a(t - 1, i - 1, j) + 0.45 * a(t - 1, i, j) + 0.45 * a(t - 1, i + 1, j) - 0.4 * a(t - 1, i, j - 1) - 0.45 * a(t - 1, i, j) - 0.45 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.12 * a(t - 1, i - 1, j) + 0.152 * a(t - 1, i, j) + 0.152 * a(t - 1, i + 1, j) - 0.12 * a(t - 1, i, j - 1) - 0.152 * a(t - 1, i, j) - 0.152 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.13 * a(t - 1, i - 1, j) + 0.153 * a(t - 1, i, j) + 0.153 * a(t - 1, i + 1, j) - 0.13 * a(t - 1, i, j - 1) - 0.153 * a(t - 1, i, j) - 0.153 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.22999999999999998 * a(t - 1, i - 1, j) + 0.253 * a(t - 1, i, j) + 0.253 * a(t - 1, i + 1, j) - 0.22999999999999998 * a(t - 1, i, j - 1) - 0.253 * a(t - 1, i, j) - 0.253 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.32999999999999996 * a(t - 1, i - 1, j) + 0.35300000000000004 * a(t - 1, i, j) + 0.35300000000000004 * a(t - 1, i + 1, j) - 0.32999999999999996 * a(t - 1, i, j - 1) - 0.35300000000000004 * a(t - 1, i, j) - 0.35300000000000004 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.43 * a(t - 1, i - 1, j) + 0.453 * a(t - 1, i, j) + 0.453 * a(t - 1, i + 1, j) - 0.43 * a(t - 1, i, j - 1) - 0.453 * a(t - 1, i, j) - 0.453 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.5 * a(t - 1, i - 1, j) + 0.55 * a(t - 1, i, j) + 0.55 * a(t - 1, i + 1, j) - 0.5 * a(t - 1, i, j - 1) - 0.55 * a(t - 1, i, j) - 0.55 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.6 * a(t - 1, i - 1, j) + 0.65 * a(t - 1, i, j) + 0.65 * a(t - 1, i + 1, j) - 0.6 * a(t - 1, i, j - 1) - 0.65 * a(t - 1, i, j) - 0.65 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.7 * a(t - 1, i - 1, j) + 0.75 * a(t - 1, i, j) + 0.75 * a(t - 1, i + 1, j) - 0.7 * a(t - 1, i, j - 1) - 0.75 * a(t - 1, i, j) - 0.75 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8 * a(t - 1, i - 1, j) + 0.85 * a(t - 1, i, j) + 0.85 * a(t - 1, i + 1, j) - 0.8 * a(t - 1, i, j - 1) - 0.85 * a(t - 1, i, j) - 0.85 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.22000000000000003 * a(t - 1, i - 1, j) + 0.252 * a(t - 1, i, j) + 0.252 * a(t - 1, i + 1, j) - 0.22000000000000003 * a(t - 1, i, j - 1) - 0.252 * a(t - 1, i, j) - 0.252 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.53 * a(t - 1, i - 1, j) + 0.553 * a(t - 1, i, j) + 0.553 * a(t - 1, i + 1, j) - 0.53 * a(t - 1, i, j - 1) - 0.553 * a(t - 1, i, j) - 0.553 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.63 * a(t - 1, i - 1, j) + 0.653 * a(t - 1, i, j) + 0.653 * a(t - 1, i + 1, j) - 0.63 * a(t - 1, i, j - 1) - 0.653 * a(t - 1, i, j) - 0.653 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.73 * a(t - 1, i - 1, j) + 0.753 * a(t - 1, i, j) + 0.753 * a(t - 1, i + 1, j) - 0.73 * a(t - 1, i, j - 1) - 0.753 * a(t - 1, i, j) - 0.753 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8300000000000001 * a(t - 1, i - 1, j) + 0.853 * a(t - 1, i, j) + 0.853 * a(t - 1, i + 1, j) - 0.8300000000000001 * a(t - 1, i, j - 1) - 0.853 * a(t - 1, i, j) - 0.853 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
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
	static __Pointer_boundary_kernel_7__ * _Pointer_boundary_kernel_7 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_boundary_kernel_7 = NULL;
	#undef pmod_lu
	
	
	
	/* KNOWN */
	class __Pointer_cond_interior_kernel_7__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_interior_kernel_7__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.1 * pt_a_1[l_a_stride_1 * (-1)] + 0.15 * pt_a_1[0] + 0.15 * pt_a_1[l_a_stride_1 * (1)] - 0.1 * pt_a_1[l_a_stride_0 * (-1)] - 0.15 * pt_a_1[0] - 0.15 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.2 * pt_a_1[l_a_stride_1 * (-1)] + 0.25 * pt_a_1[0] + 0.25 * pt_a_1[l_a_stride_1 * (1)] - 0.2 * pt_a_1[l_a_stride_0 * (-1)] - 0.25 * pt_a_1[0] - 0.25 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.3 * pt_a_1[l_a_stride_1 * (-1)] + 0.35 * pt_a_1[0] + 0.35 * pt_a_1[l_a_stride_1 * (1)] - 0.3 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] - 0.35 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.4 * pt_a_1[l_a_stride_1 * (-1)] + 0.45 * pt_a_1[0] + 0.45 * pt_a_1[l_a_stride_1 * (1)] - 0.4 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] - 0.45 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.12 * pt_a_1[l_a_stride_1 * (-1)] + 0.152 * pt_a_1[0] + 0.152 * pt_a_1[l_a_stride_1 * (1)] - 0.12 * pt_a_1[l_a_stride_0 * (-1)] - 0.152 * pt_a_1[0] - 0.152 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.13 * pt_a_1[l_a_stride_1 * (-1)] + 0.153 * pt_a_1[0] + 0.153 * pt_a_1[l_a_stride_1 * (1)] - 0.13 * pt_a_1[l_a_stride_0 * (-1)] - 0.153 * pt_a_1[0] - 0.153 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.22999999999999998 * pt_a_1[l_a_stride_1 * (-1)] + 0.253 * pt_a_1[0] + 0.253 * pt_a_1[l_a_stride_1 * (1)] - 0.22999999999999998 * pt_a_1[l_a_stride_0 * (-1)] - 0.253 * pt_a_1[0] - 0.253 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.32999999999999996 * pt_a_1[l_a_stride_1 * (-1)] + 0.35300000000000004 * pt_a_1[0] + 0.35300000000000004 * pt_a_1[l_a_stride_1 * (1)] - 0.32999999999999996 * pt_a_1[l_a_stride_0 * (-1)] - 0.35300000000000004 * pt_a_1[0] - 0.35300000000000004 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.43 * pt_a_1[l_a_stride_1 * (-1)] + 0.453 * pt_a_1[0] + 0.453 * pt_a_1[l_a_stride_1 * (1)] - 0.43 * pt_a_1[l_a_stride_0 * (-1)] - 0.453 * pt_a_1[0] - 0.453 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.5 * pt_a_1[l_a_stride_1 * (-1)] + 0.55 * pt_a_1[0] + 0.55 * pt_a_1[l_a_stride_1 * (1)] - 0.5 * pt_a_1[l_a_stride_0 * (-1)] - 0.55 * pt_a_1[0] - 0.55 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.6 * pt_a_1[l_a_stride_1 * (-1)] + 0.65 * pt_a_1[0] + 0.65 * pt_a_1[l_a_stride_1 * (1)] - 0.6 * pt_a_1[l_a_stride_0 * (-1)] - 0.65 * pt_a_1[0] - 0.65 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.7 * pt_a_1[l_a_stride_1 * (-1)] + 0.75 * pt_a_1[0] + 0.75 * pt_a_1[l_a_stride_1 * (1)] - 0.7 * pt_a_1[l_a_stride_0 * (-1)] - 0.75 * pt_a_1[0] - 0.75 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.8 * pt_a_1[l_a_stride_1 * (-1)] + 0.85 * pt_a_1[0] + 0.85 * pt_a_1[l_a_stride_1 * (1)] - 0.8 * pt_a_1[l_a_stride_0 * (-1)] - 0.85 * pt_a_1[0] - 0.85 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.22000000000000003 * pt_a_1[l_a_stride_1 * (-1)] + 0.252 * pt_a_1[0] + 0.252 * pt_a_1[l_a_stride_1 * (1)] - 0.22000000000000003 * pt_a_1[l_a_stride_0 * (-1)] - 0.252 * pt_a_1[0] - 0.252 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.53 * pt_a_1[l_a_stride_1 * (-1)] + 0.553 * pt_a_1[0] + 0.553 * pt_a_1[l_a_stride_1 * (1)] - 0.53 * pt_a_1[l_a_stride_0 * (-1)] - 0.553 * pt_a_1[0] - 0.553 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.63 * pt_a_1[l_a_stride_1 * (-1)] + 0.653 * pt_a_1[0] + 0.653 * pt_a_1[l_a_stride_1 * (1)] - 0.63 * pt_a_1[l_a_stride_0 * (-1)] - 0.653 * pt_a_1[0] - 0.653 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.73 * pt_a_1[l_a_stride_1 * (-1)] + 0.753 * pt_a_1[0] + 0.753 * pt_a_1[l_a_stride_1 * (1)] - 0.73 * pt_a_1[l_a_stride_0 * (-1)] - 0.753 * pt_a_1[0] - 0.753 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.8300000000000001 * pt_a_1[l_a_stride_1 * (-1)] + 0.853 * pt_a_1[0] + 0.853 * pt_a_1[l_a_stride_1 * (1)] - 0.8300000000000001 * pt_a_1[l_a_stride_0 * (-1)] - 0.853 * pt_a_1[0] - 0.853 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
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
	static __Pointer_cond_interior_kernel_7__ * _Pointer_cond_interior_kernel_7 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_interior_kernel_7 = NULL;
	
	
	
	
	/* KNOWN */
	class __Pointer_interior_kernel_7__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_interior_kernel_7__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.1 * pt_a_1[l_a_stride_1 * (-1)] + 0.15 * pt_a_1[0] + 0.15 * pt_a_1[l_a_stride_1 * (1)] - 0.1 * pt_a_1[l_a_stride_0 * (-1)] - 0.15 * pt_a_1[0] - 0.15 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.2 * pt_a_1[l_a_stride_1 * (-1)] + 0.25 * pt_a_1[0] + 0.25 * pt_a_1[l_a_stride_1 * (1)] - 0.2 * pt_a_1[l_a_stride_0 * (-1)] - 0.25 * pt_a_1[0] - 0.25 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.3 * pt_a_1[l_a_stride_1 * (-1)] + 0.35 * pt_a_1[0] + 0.35 * pt_a_1[l_a_stride_1 * (1)] - 0.3 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] - 0.35 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.4 * pt_a_1[l_a_stride_1 * (-1)] + 0.45 * pt_a_1[0] + 0.45 * pt_a_1[l_a_stride_1 * (1)] - 0.4 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] - 0.45 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.12 * pt_a_1[l_a_stride_1 * (-1)] + 0.152 * pt_a_1[0] + 0.152 * pt_a_1[l_a_stride_1 * (1)] - 0.12 * pt_a_1[l_a_stride_0 * (-1)] - 0.152 * pt_a_1[0] - 0.152 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.13 * pt_a_1[l_a_stride_1 * (-1)] + 0.153 * pt_a_1[0] + 0.153 * pt_a_1[l_a_stride_1 * (1)] - 0.13 * pt_a_1[l_a_stride_0 * (-1)] - 0.153 * pt_a_1[0] - 0.153 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.22999999999999998 * pt_a_1[l_a_stride_1 * (-1)] + 0.253 * pt_a_1[0] + 0.253 * pt_a_1[l_a_stride_1 * (1)] - 0.22999999999999998 * pt_a_1[l_a_stride_0 * (-1)] - 0.253 * pt_a_1[0] - 0.253 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.32999999999999996 * pt_a_1[l_a_stride_1 * (-1)] + 0.35300000000000004 * pt_a_1[0] + 0.35300000000000004 * pt_a_1[l_a_stride_1 * (1)] - 0.32999999999999996 * pt_a_1[l_a_stride_0 * (-1)] - 0.35300000000000004 * pt_a_1[0] - 0.35300000000000004 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.43 * pt_a_1[l_a_stride_1 * (-1)] + 0.453 * pt_a_1[0] + 0.453 * pt_a_1[l_a_stride_1 * (1)] - 0.43 * pt_a_1[l_a_stride_0 * (-1)] - 0.453 * pt_a_1[0] - 0.453 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.5 * pt_a_1[l_a_stride_1 * (-1)] + 0.55 * pt_a_1[0] + 0.55 * pt_a_1[l_a_stride_1 * (1)] - 0.5 * pt_a_1[l_a_stride_0 * (-1)] - 0.55 * pt_a_1[0] - 0.55 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.6 * pt_a_1[l_a_stride_1 * (-1)] + 0.65 * pt_a_1[0] + 0.65 * pt_a_1[l_a_stride_1 * (1)] - 0.6 * pt_a_1[l_a_stride_0 * (-1)] - 0.65 * pt_a_1[0] - 0.65 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.7 * pt_a_1[l_a_stride_1 * (-1)] + 0.75 * pt_a_1[0] + 0.75 * pt_a_1[l_a_stride_1 * (1)] - 0.7 * pt_a_1[l_a_stride_0 * (-1)] - 0.75 * pt_a_1[0] - 0.75 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.8 * pt_a_1[l_a_stride_1 * (-1)] + 0.85 * pt_a_1[0] + 0.85 * pt_a_1[l_a_stride_1 * (1)] - 0.8 * pt_a_1[l_a_stride_0 * (-1)] - 0.85 * pt_a_1[0] - 0.85 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.22000000000000003 * pt_a_1[l_a_stride_1 * (-1)] + 0.252 * pt_a_1[0] + 0.252 * pt_a_1[l_a_stride_1 * (1)] - 0.22000000000000003 * pt_a_1[l_a_stride_0 * (-1)] - 0.252 * pt_a_1[0] - 0.252 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.53 * pt_a_1[l_a_stride_1 * (-1)] + 0.553 * pt_a_1[0] + 0.553 * pt_a_1[l_a_stride_1 * (1)] - 0.53 * pt_a_1[l_a_stride_0 * (-1)] - 0.553 * pt_a_1[0] - 0.553 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.63 * pt_a_1[l_a_stride_1 * (-1)] + 0.653 * pt_a_1[0] + 0.653 * pt_a_1[l_a_stride_1 * (1)] - 0.63 * pt_a_1[l_a_stride_0 * (-1)] - 0.653 * pt_a_1[0] - 0.653 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.73 * pt_a_1[l_a_stride_1 * (-1)] + 0.753 * pt_a_1[0] + 0.753 * pt_a_1[l_a_stride_1 * (1)] - 0.73 * pt_a_1[l_a_stride_0 * (-1)] - 0.753 * pt_a_1[0] - 0.753 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.8300000000000001 * pt_a_1[l_a_stride_1 * (-1)] + 0.853 * pt_a_1[0] + 0.853 * pt_a_1[l_a_stride_1 * (1)] - 0.8300000000000001 * pt_a_1[l_a_stride_0 * (-1)] - 0.853 * pt_a_1[0] - 0.853 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
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
	static __Pointer_interior_kernel_7__ * _Pointer_interior_kernel_7 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_interior_kernel_7 = NULL;
	
	
	
	/* <111000, 000000>
 */
	auto __POCHOIR_Guard_8__ = [&]  ( int t, int i0, int i1 )  -> bool {
	return ( !__g_inclusive_1__ ( t + -1, i0, i1 )  && !__g_tiny_inclusive_0__ ( t + -1, i0, i1 )  && !__g_tiny_inclusive_1__ ( t + -1, i0, i1 )  );
	 };
	static Pochoir_Guard <2> POCHOIR_Guard_8 ( __POCHOIR_Guard_8__ ); 

	/* <111000, 000000>
 */
	
	
	/* 
	tile_3D_checkerboard_0 - PINCLUSIVE;
	tile_2D_checkerboard_1 - PINCLUSIVE;
	tile_1D_checkerboard_2 - PINCLUSIVE;
	__Pochoir_NULL__ - PNULL
	 */
	/* k_0_0, k_0_1, k_0_2, k_0_3, k_0_4, k_0_5, k_0_6, k_0_7, k_1_0, k_1_1, k_1_2, k_1_3, k_2_0, k_2_1, __Pochoir_NULL_ */ 
	/* 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 0 */ 
	/* PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PNULL */ 
	/* [0,0,0], [0,0,1], [0,1,0], [0,1,1], [1,0,0], [1,0,1], [1,1,0], [1,1,1], [0,0], [0,1], [1,0], [1,1], [0], [1], [0] */ 
	/* [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2], [2,2], [2,2], [2,2], [2], [2], [1] */ 
	/* 
	PMTile (sizes = [2,2,2], latest_tile_order = 2), terms = 
		PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 2), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 1), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_0
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_1
				PMTileTerm (indices = [], sizes = [], latest_tile_order = 1), item = k_1_0
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 1), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_2
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_3
				PMTileTerm (indices = [], sizes = [], latest_tile_order = 1), item = k_1_1
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 2), item = k_2_0
		PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 2), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 1), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_4
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_5
				PMTileTerm (indices = [], sizes = [], latest_tile_order = 1), item = k_1_2
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 1), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_6
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_7
				PMTileTerm (indices = [], sizes = [], latest_tile_order = 1), item = k_1_3
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 2), item = k_2_1
	 */ 
	static 
	Pochoir_Shape <2> __POCHOIR_Shape__8__ [ ] = {{0, 0, 0}, {-1, 0, -1}, {-1, 0, 1}, {-1, 1, 0}, {-1, -1, 0}, {-1, 0, 0}};
	/* toggle: 2; slopes: [] */
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_cond_boundary_kernel_8__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_boundary_kernel_8__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.1 * a(t - 1, i - 1, j) + 0.15 * a(t - 1, i, j) + 0.15 * a(t - 1, i + 1, j) - 0.1 * a(t - 1, i, j - 1) - 0.15 * a(t - 1, i, j) - 0.15 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.2 * a(t - 1, i - 1, j) + 0.25 * a(t - 1, i, j) + 0.25 * a(t - 1, i + 1, j) - 0.2 * a(t - 1, i, j - 1) - 0.25 * a(t - 1, i, j) - 0.25 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.11000000000000001 * a(t - 1, i - 1, j) + 0.151 * a(t - 1, i, j) + 0.151 * a(t - 1, i + 1, j) - 0.11000000000000001 * a(t - 1, i, j - 1) - 0.151 * a(t - 1, i, j) - 0.151 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.3 * a(t - 1, i - 1, j) + 0.35 * a(t - 1, i, j) + 0.35 * a(t - 1, i + 1, j) - 0.3 * a(t - 1, i, j - 1) - 0.35 * a(t - 1, i, j) - 0.35 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.4 * a(t - 1, i - 1, j) + 0.45 * a(t - 1, i, j) + 0.45 * a(t - 1, i + 1, j) - 0.4 * a(t - 1, i, j - 1) - 0.45 * a(t - 1, i, j) - 0.45 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.21000000000000002 * a(t - 1, i - 1, j) + 0.251 * a(t - 1, i, j) + 0.251 * a(t - 1, i + 1, j) - 0.21000000000000002 * a(t - 1, i, j - 1) - 0.251 * a(t - 1, i, j) - 0.251 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.12 * a(t - 1, i - 1, j) + 0.152 * a(t - 1, i, j) + 0.152 * a(t - 1, i + 1, j) - 0.12 * a(t - 1, i, j - 1) - 0.152 * a(t - 1, i, j) - 0.152 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.5 * a(t - 1, i - 1, j) + 0.55 * a(t - 1, i, j) + 0.55 * a(t - 1, i + 1, j) - 0.5 * a(t - 1, i, j - 1) - 0.55 * a(t - 1, i, j) - 0.55 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.6 * a(t - 1, i - 1, j) + 0.65 * a(t - 1, i, j) + 0.65 * a(t - 1, i + 1, j) - 0.6 * a(t - 1, i, j - 1) - 0.65 * a(t - 1, i, j) - 0.65 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.31 * a(t - 1, i - 1, j) + 0.351 * a(t - 1, i, j) + 0.351 * a(t - 1, i + 1, j) - 0.31 * a(t - 1, i, j - 1) - 0.351 * a(t - 1, i, j) - 0.351 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.7 * a(t - 1, i - 1, j) + 0.75 * a(t - 1, i, j) + 0.75 * a(t - 1, i + 1, j) - 0.7 * a(t - 1, i, j - 1) - 0.75 * a(t - 1, i, j) - 0.75 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8 * a(t - 1, i - 1, j) + 0.85 * a(t - 1, i, j) + 0.85 * a(t - 1, i + 1, j) - 0.8 * a(t - 1, i, j - 1) - 0.85 * a(t - 1, i, j) - 0.85 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.41 * a(t - 1, i - 1, j) + 0.45099999999999996 * a(t - 1, i, j) + 0.45099999999999996 * a(t - 1, i + 1, j) - 0.41 * a(t - 1, i, j - 1) - 0.45099999999999996 * a(t - 1, i, j) - 0.45099999999999996 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.22000000000000003 * a(t - 1, i - 1, j) + 0.252 * a(t - 1, i, j) + 0.252 * a(t - 1, i + 1, j) - 0.22000000000000003 * a(t - 1, i, j - 1) - 0.252 * a(t - 1, i, j) - 0.252 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
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
	static __Pointer_cond_boundary_kernel_8__ * _Pointer_cond_boundary_kernel_8 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_boundary_kernel_8 = NULL;
	#undef pmod_lu
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_boundary_kernel_8__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_boundary_kernel_8__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.1 * a(t - 1, i - 1, j) + 0.15 * a(t - 1, i, j) + 0.15 * a(t - 1, i + 1, j) - 0.1 * a(t - 1, i, j - 1) - 0.15 * a(t - 1, i, j) - 0.15 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.2 * a(t - 1, i - 1, j) + 0.25 * a(t - 1, i, j) + 0.25 * a(t - 1, i + 1, j) - 0.2 * a(t - 1, i, j - 1) - 0.25 * a(t - 1, i, j) - 0.25 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.11000000000000001 * a(t - 1, i - 1, j) + 0.151 * a(t - 1, i, j) + 0.151 * a(t - 1, i + 1, j) - 0.11000000000000001 * a(t - 1, i, j - 1) - 0.151 * a(t - 1, i, j) - 0.151 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.3 * a(t - 1, i - 1, j) + 0.35 * a(t - 1, i, j) + 0.35 * a(t - 1, i + 1, j) - 0.3 * a(t - 1, i, j - 1) - 0.35 * a(t - 1, i, j) - 0.35 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.4 * a(t - 1, i - 1, j) + 0.45 * a(t - 1, i, j) + 0.45 * a(t - 1, i + 1, j) - 0.4 * a(t - 1, i, j - 1) - 0.45 * a(t - 1, i, j) - 0.45 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.21000000000000002 * a(t - 1, i - 1, j) + 0.251 * a(t - 1, i, j) + 0.251 * a(t - 1, i + 1, j) - 0.21000000000000002 * a(t - 1, i, j - 1) - 0.251 * a(t - 1, i, j) - 0.251 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.12 * a(t - 1, i - 1, j) + 0.152 * a(t - 1, i, j) + 0.152 * a(t - 1, i + 1, j) - 0.12 * a(t - 1, i, j - 1) - 0.152 * a(t - 1, i, j) - 0.152 * a(t - 1, i, j + 1);
	
	
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.5 * a(t - 1, i - 1, j) + 0.55 * a(t - 1, i, j) + 0.55 * a(t - 1, i + 1, j) - 0.5 * a(t - 1, i, j - 1) - 0.55 * a(t - 1, i, j) - 0.55 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.6 * a(t - 1, i - 1, j) + 0.65 * a(t - 1, i, j) + 0.65 * a(t - 1, i + 1, j) - 0.6 * a(t - 1, i, j - 1) - 0.65 * a(t - 1, i, j) - 0.65 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.31 * a(t - 1, i - 1, j) + 0.351 * a(t - 1, i, j) + 0.351 * a(t - 1, i + 1, j) - 0.31 * a(t - 1, i, j - 1) - 0.351 * a(t - 1, i, j) - 0.351 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.7 * a(t - 1, i - 1, j) + 0.75 * a(t - 1, i, j) + 0.75 * a(t - 1, i + 1, j) - 0.7 * a(t - 1, i, j - 1) - 0.75 * a(t - 1, i, j) - 0.75 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8 * a(t - 1, i - 1, j) + 0.85 * a(t - 1, i, j) + 0.85 * a(t - 1, i + 1, j) - 0.8 * a(t - 1, i, j - 1) - 0.85 * a(t - 1, i, j) - 0.85 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.41 * a(t - 1, i - 1, j) + 0.45099999999999996 * a(t - 1, i, j) + 0.45099999999999996 * a(t - 1, i + 1, j) - 0.41 * a(t - 1, i, j - 1) - 0.45099999999999996 * a(t - 1, i, j) - 0.45099999999999996 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.22000000000000003 * a(t - 1, i - 1, j) + 0.252 * a(t - 1, i, j) + 0.252 * a(t - 1, i + 1, j) - 0.22000000000000003 * a(t - 1, i, j - 1) - 0.252 * a(t - 1, i, j) - 0.252 * a(t - 1, i, j + 1);
	
	
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
	static __Pointer_boundary_kernel_8__ * _Pointer_boundary_kernel_8 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_boundary_kernel_8 = NULL;
	#undef pmod_lu
	
	
	
	/* KNOWN */
	class __Pointer_cond_interior_kernel_8__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_interior_kernel_8__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.1 * pt_a_1[l_a_stride_1 * (-1)] + 0.15 * pt_a_1[0] + 0.15 * pt_a_1[l_a_stride_1 * (1)] - 0.1 * pt_a_1[l_a_stride_0 * (-1)] - 0.15 * pt_a_1[0] - 0.15 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.2 * pt_a_1[l_a_stride_1 * (-1)] + 0.25 * pt_a_1[0] + 0.25 * pt_a_1[l_a_stride_1 * (1)] - 0.2 * pt_a_1[l_a_stride_0 * (-1)] - 0.25 * pt_a_1[0] - 0.25 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11000000000000001 * pt_a_1[l_a_stride_1 * (-1)] + 0.151 * pt_a_1[0] + 0.151 * pt_a_1[l_a_stride_1 * (1)] - 0.11000000000000001 * pt_a_1[l_a_stride_0 * (-1)] - 0.151 * pt_a_1[0] - 0.151 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.3 * pt_a_1[l_a_stride_1 * (-1)] + 0.35 * pt_a_1[0] + 0.35 * pt_a_1[l_a_stride_1 * (1)] - 0.3 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] - 0.35 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.4 * pt_a_1[l_a_stride_1 * (-1)] + 0.45 * pt_a_1[0] + 0.45 * pt_a_1[l_a_stride_1 * (1)] - 0.4 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] - 0.45 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21000000000000002 * pt_a_1[l_a_stride_1 * (-1)] + 0.251 * pt_a_1[0] + 0.251 * pt_a_1[l_a_stride_1 * (1)] - 0.21000000000000002 * pt_a_1[l_a_stride_0 * (-1)] - 0.251 * pt_a_1[0] - 0.251 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.12 * pt_a_1[l_a_stride_1 * (-1)] + 0.152 * pt_a_1[0] + 0.152 * pt_a_1[l_a_stride_1 * (1)] - 0.12 * pt_a_1[l_a_stride_0 * (-1)] - 0.152 * pt_a_1[0] - 0.152 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.5 * pt_a_1[l_a_stride_1 * (-1)] + 0.55 * pt_a_1[0] + 0.55 * pt_a_1[l_a_stride_1 * (1)] - 0.5 * pt_a_1[l_a_stride_0 * (-1)] - 0.55 * pt_a_1[0] - 0.55 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.6 * pt_a_1[l_a_stride_1 * (-1)] + 0.65 * pt_a_1[0] + 0.65 * pt_a_1[l_a_stride_1 * (1)] - 0.6 * pt_a_1[l_a_stride_0 * (-1)] - 0.65 * pt_a_1[0] - 0.65 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.31 * pt_a_1[l_a_stride_1 * (-1)] + 0.351 * pt_a_1[0] + 0.351 * pt_a_1[l_a_stride_1 * (1)] - 0.31 * pt_a_1[l_a_stride_0 * (-1)] - 0.351 * pt_a_1[0] - 0.351 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.7 * pt_a_1[l_a_stride_1 * (-1)] + 0.75 * pt_a_1[0] + 0.75 * pt_a_1[l_a_stride_1 * (1)] - 0.7 * pt_a_1[l_a_stride_0 * (-1)] - 0.75 * pt_a_1[0] - 0.75 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.8 * pt_a_1[l_a_stride_1 * (-1)] + 0.85 * pt_a_1[0] + 0.85 * pt_a_1[l_a_stride_1 * (1)] - 0.8 * pt_a_1[l_a_stride_0 * (-1)] - 0.85 * pt_a_1[0] - 0.85 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.41 * pt_a_1[l_a_stride_1 * (-1)] + 0.45099999999999996 * pt_a_1[0] + 0.45099999999999996 * pt_a_1[l_a_stride_1 * (1)] - 0.41 * pt_a_1[l_a_stride_0 * (-1)] - 0.45099999999999996 * pt_a_1[0] - 0.45099999999999996 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.22000000000000003 * pt_a_1[l_a_stride_1 * (-1)] + 0.252 * pt_a_1[0] + 0.252 * pt_a_1[l_a_stride_1 * (1)] - 0.22000000000000003 * pt_a_1[l_a_stride_0 * (-1)] - 0.252 * pt_a_1[0] - 0.252 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
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
	static __Pointer_cond_interior_kernel_8__ * _Pointer_cond_interior_kernel_8 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_interior_kernel_8 = NULL;
	
	
	
	
	/* KNOWN */
	class __Pointer_interior_kernel_8__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_interior_kernel_8__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.1 * pt_a_1[l_a_stride_1 * (-1)] + 0.15 * pt_a_1[0] + 0.15 * pt_a_1[l_a_stride_1 * (1)] - 0.1 * pt_a_1[l_a_stride_0 * (-1)] - 0.15 * pt_a_1[0] - 0.15 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.2 * pt_a_1[l_a_stride_1 * (-1)] + 0.25 * pt_a_1[0] + 0.25 * pt_a_1[l_a_stride_1 * (1)] - 0.2 * pt_a_1[l_a_stride_0 * (-1)] - 0.25 * pt_a_1[0] - 0.25 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11000000000000001 * pt_a_1[l_a_stride_1 * (-1)] + 0.151 * pt_a_1[0] + 0.151 * pt_a_1[l_a_stride_1 * (1)] - 0.11000000000000001 * pt_a_1[l_a_stride_0 * (-1)] - 0.151 * pt_a_1[0] - 0.151 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.3 * pt_a_1[l_a_stride_1 * (-1)] + 0.35 * pt_a_1[0] + 0.35 * pt_a_1[l_a_stride_1 * (1)] - 0.3 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] - 0.35 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.4 * pt_a_1[l_a_stride_1 * (-1)] + 0.45 * pt_a_1[0] + 0.45 * pt_a_1[l_a_stride_1 * (1)] - 0.4 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] - 0.45 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21000000000000002 * pt_a_1[l_a_stride_1 * (-1)] + 0.251 * pt_a_1[0] + 0.251 * pt_a_1[l_a_stride_1 * (1)] - 0.21000000000000002 * pt_a_1[l_a_stride_0 * (-1)] - 0.251 * pt_a_1[0] - 0.251 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.12 * pt_a_1[l_a_stride_1 * (-1)] + 0.152 * pt_a_1[0] + 0.152 * pt_a_1[l_a_stride_1 * (1)] - 0.12 * pt_a_1[l_a_stride_0 * (-1)] - 0.152 * pt_a_1[0] - 0.152 * pt_a_1[l_a_stride_0 * (1)];
	
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.5 * pt_a_1[l_a_stride_1 * (-1)] + 0.55 * pt_a_1[0] + 0.55 * pt_a_1[l_a_stride_1 * (1)] - 0.5 * pt_a_1[l_a_stride_0 * (-1)] - 0.55 * pt_a_1[0] - 0.55 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.6 * pt_a_1[l_a_stride_1 * (-1)] + 0.65 * pt_a_1[0] + 0.65 * pt_a_1[l_a_stride_1 * (1)] - 0.6 * pt_a_1[l_a_stride_0 * (-1)] - 0.65 * pt_a_1[0] - 0.65 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.31 * pt_a_1[l_a_stride_1 * (-1)] + 0.351 * pt_a_1[0] + 0.351 * pt_a_1[l_a_stride_1 * (1)] - 0.31 * pt_a_1[l_a_stride_0 * (-1)] - 0.351 * pt_a_1[0] - 0.351 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.7 * pt_a_1[l_a_stride_1 * (-1)] + 0.75 * pt_a_1[0] + 0.75 * pt_a_1[l_a_stride_1 * (1)] - 0.7 * pt_a_1[l_a_stride_0 * (-1)] - 0.75 * pt_a_1[0] - 0.75 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.8 * pt_a_1[l_a_stride_1 * (-1)] + 0.85 * pt_a_1[0] + 0.85 * pt_a_1[l_a_stride_1 * (1)] - 0.8 * pt_a_1[l_a_stride_0 * (-1)] - 0.85 * pt_a_1[0] - 0.85 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.41 * pt_a_1[l_a_stride_1 * (-1)] + 0.45099999999999996 * pt_a_1[0] + 0.45099999999999996 * pt_a_1[l_a_stride_1 * (1)] - 0.41 * pt_a_1[l_a_stride_0 * (-1)] - 0.45099999999999996 * pt_a_1[0] - 0.45099999999999996 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.22000000000000003 * pt_a_1[l_a_stride_1 * (-1)] + 0.252 * pt_a_1[0] + 0.252 * pt_a_1[l_a_stride_1 * (1)] - 0.22000000000000003 * pt_a_1[l_a_stride_0 * (-1)] - 0.252 * pt_a_1[0] - 0.252 * pt_a_1[l_a_stride_0 * (1)];
	
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
	static __Pointer_interior_kernel_8__ * _Pointer_interior_kernel_8 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_interior_kernel_8 = NULL;
	
	
	
	/* <101100, 101100>
 */
	auto __POCHOIR_Guard_9__ = [&]  ( int t, int i0, int i1 )  -> bool {
	return ( __g_exclusive_0__ ( t + -1, i0, i1 )  && !__g_exclusive_1__ ( t + -1, i0, i1 )  && __g_inclusive_0__ ( t + -1, i0, i1 )  && __g_inclusive_1__ ( t + -1, i0, i1 )  && !__g_tiny_inclusive_0__ ( t + -1, i0, i1 )  && !__g_tiny_inclusive_1__ ( t + -1, i0, i1 )  );
	 };
	static Pochoir_Guard <2> POCHOIR_Guard_9 ( __POCHOIR_Guard_9__ ); 

	/* <101100, 101100>
 */
	
	
	/* 
	tile_3D_checkerboard_0 - PSERIAL;
	tile_1D_checkerboard_2 - PSERIAL;
	tile_3D_checkerboard_3 - PSERIAL;
	__Pochoir_NULL__ - PNULL
	 */
	/* k_0_0, k_0_1, k_0_2, k_0_3, k_0_4, k_0_5, k_0_6, k_0_7, k_2_0, k_2_1, k_3_0, k_3_1, k_3_2, k_3_3, k_3_4, k_3_5, k_3_6, k_3_7, __Pochoir_NULL_ */ 
	/* 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 0 */ 
	/* PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PNULL */ 
	/* [0,0,0], [0,0,1], [0,1,0], [0,1,1], [1,0,0], [1,0,1], [1,1,0], [1,1,1], [0], [1], [0,0,0], [0,0,1], [0,1,0], [0,1,1], [1,0,0], [1,0,1], [1,1,0], [1,1,1], [0] */ 
	/* [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2], [2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [1] */ 
	/* 
	PMTile (sizes = [2,2,2], latest_tile_order = 3), terms = 
		PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_0
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_1
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_2
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_3
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 2), item = k_2_0
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = k_3_0
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = k_3_1
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = k_3_2
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = k_3_3
		PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_4
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_5
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_6
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_7
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 2), item = k_2_1
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = k_3_4
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = k_3_5
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = k_3_6
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = k_3_7
	 */ 
	static 
	Pochoir_Shape <2> __POCHOIR_Shape__9__ [ ] = {{0, 0, 0}, {-1, 0, -1}, {-1, 0, 1}, {-1, 1, 0}, {-1, -1, 0}, {-1, 0, 0}};
	/* toggle: 2; slopes: [] */
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_cond_boundary_kernel_9__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_boundary_kernel_9__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.1 * a(t - 1, i - 1, j) + 0.15 * a(t - 1, i, j) + 0.15 * a(t - 1, i + 1, j) - 0.1 * a(t - 1, i, j - 1) - 0.15 * a(t - 1, i, j) - 0.15 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.2 * a(t - 1, i - 1, j) + 0.25 * a(t - 1, i, j) + 0.25 * a(t - 1, i + 1, j) - 0.2 * a(t - 1, i, j - 1) - 0.25 * a(t - 1, i, j) - 0.25 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.3 * a(t - 1, i - 1, j) + 0.35 * a(t - 1, i, j) + 0.35 * a(t - 1, i + 1, j) - 0.3 * a(t - 1, i, j - 1) - 0.35 * a(t - 1, i, j) - 0.35 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.4 * a(t - 1, i - 1, j) + 0.45 * a(t - 1, i, j) + 0.45 * a(t - 1, i + 1, j) - 0.4 * a(t - 1, i, j - 1) - 0.45 * a(t - 1, i, j) - 0.45 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.12 * a(t - 1, i - 1, j) + 0.152 * a(t - 1, i, j) + 0.152 * a(t - 1, i + 1, j) - 0.12 * a(t - 1, i, j - 1) - 0.152 * a(t - 1, i, j) - 0.152 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.13 * a(t - 1, i - 1, j) + 0.153 * a(t - 1, i, j) + 0.153 * a(t - 1, i + 1, j) - 0.13 * a(t - 1, i, j - 1) - 0.153 * a(t - 1, i, j) - 0.153 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.22999999999999998 * a(t - 1, i - 1, j) + 0.253 * a(t - 1, i, j) + 0.253 * a(t - 1, i + 1, j) - 0.22999999999999998 * a(t - 1, i, j - 1) - 0.253 * a(t - 1, i, j) - 0.253 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.32999999999999996 * a(t - 1, i - 1, j) + 0.35300000000000004 * a(t - 1, i, j) + 0.35300000000000004 * a(t - 1, i + 1, j) - 0.32999999999999996 * a(t - 1, i, j - 1) - 0.35300000000000004 * a(t - 1, i, j) - 0.35300000000000004 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.43 * a(t - 1, i - 1, j) + 0.453 * a(t - 1, i, j) + 0.453 * a(t - 1, i + 1, j) - 0.43 * a(t - 1, i, j - 1) - 0.453 * a(t - 1, i, j) - 0.453 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.5 * a(t - 1, i - 1, j) + 0.55 * a(t - 1, i, j) + 0.55 * a(t - 1, i + 1, j) - 0.5 * a(t - 1, i, j - 1) - 0.55 * a(t - 1, i, j) - 0.55 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.6 * a(t - 1, i - 1, j) + 0.65 * a(t - 1, i, j) + 0.65 * a(t - 1, i + 1, j) - 0.6 * a(t - 1, i, j - 1) - 0.65 * a(t - 1, i, j) - 0.65 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.7 * a(t - 1, i - 1, j) + 0.75 * a(t - 1, i, j) + 0.75 * a(t - 1, i + 1, j) - 0.7 * a(t - 1, i, j - 1) - 0.75 * a(t - 1, i, j) - 0.75 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8 * a(t - 1, i - 1, j) + 0.85 * a(t - 1, i, j) + 0.85 * a(t - 1, i + 1, j) - 0.8 * a(t - 1, i, j - 1) - 0.85 * a(t - 1, i, j) - 0.85 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.22000000000000003 * a(t - 1, i - 1, j) + 0.252 * a(t - 1, i, j) + 0.252 * a(t - 1, i + 1, j) - 0.22000000000000003 * a(t - 1, i, j - 1) - 0.252 * a(t - 1, i, j) - 0.252 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.53 * a(t - 1, i - 1, j) + 0.553 * a(t - 1, i, j) + 0.553 * a(t - 1, i + 1, j) - 0.53 * a(t - 1, i, j - 1) - 0.553 * a(t - 1, i, j) - 0.553 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.63 * a(t - 1, i - 1, j) + 0.653 * a(t - 1, i, j) + 0.653 * a(t - 1, i + 1, j) - 0.63 * a(t - 1, i, j - 1) - 0.653 * a(t - 1, i, j) - 0.653 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.73 * a(t - 1, i - 1, j) + 0.753 * a(t - 1, i, j) + 0.753 * a(t - 1, i + 1, j) - 0.73 * a(t - 1, i, j - 1) - 0.753 * a(t - 1, i, j) - 0.753 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8300000000000001 * a(t - 1, i - 1, j) + 0.853 * a(t - 1, i, j) + 0.853 * a(t - 1, i + 1, j) - 0.8300000000000001 * a(t - 1, i, j - 1) - 0.853 * a(t - 1, i, j) - 0.853 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
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
	static __Pointer_cond_boundary_kernel_9__ * _Pointer_cond_boundary_kernel_9 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_boundary_kernel_9 = NULL;
	#undef pmod_lu
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_boundary_kernel_9__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_boundary_kernel_9__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.1 * a(t - 1, i - 1, j) + 0.15 * a(t - 1, i, j) + 0.15 * a(t - 1, i + 1, j) - 0.1 * a(t - 1, i, j - 1) - 0.15 * a(t - 1, i, j) - 0.15 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.2 * a(t - 1, i - 1, j) + 0.25 * a(t - 1, i, j) + 0.25 * a(t - 1, i + 1, j) - 0.2 * a(t - 1, i, j - 1) - 0.25 * a(t - 1, i, j) - 0.25 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.3 * a(t - 1, i - 1, j) + 0.35 * a(t - 1, i, j) + 0.35 * a(t - 1, i + 1, j) - 0.3 * a(t - 1, i, j - 1) - 0.35 * a(t - 1, i, j) - 0.35 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.4 * a(t - 1, i - 1, j) + 0.45 * a(t - 1, i, j) + 0.45 * a(t - 1, i + 1, j) - 0.4 * a(t - 1, i, j - 1) - 0.45 * a(t - 1, i, j) - 0.45 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.12 * a(t - 1, i - 1, j) + 0.152 * a(t - 1, i, j) + 0.152 * a(t - 1, i + 1, j) - 0.12 * a(t - 1, i, j - 1) - 0.152 * a(t - 1, i, j) - 0.152 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.13 * a(t - 1, i - 1, j) + 0.153 * a(t - 1, i, j) + 0.153 * a(t - 1, i + 1, j) - 0.13 * a(t - 1, i, j - 1) - 0.153 * a(t - 1, i, j) - 0.153 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.22999999999999998 * a(t - 1, i - 1, j) + 0.253 * a(t - 1, i, j) + 0.253 * a(t - 1, i + 1, j) - 0.22999999999999998 * a(t - 1, i, j - 1) - 0.253 * a(t - 1, i, j) - 0.253 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.32999999999999996 * a(t - 1, i - 1, j) + 0.35300000000000004 * a(t - 1, i, j) + 0.35300000000000004 * a(t - 1, i + 1, j) - 0.32999999999999996 * a(t - 1, i, j - 1) - 0.35300000000000004 * a(t - 1, i, j) - 0.35300000000000004 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.43 * a(t - 1, i - 1, j) + 0.453 * a(t - 1, i, j) + 0.453 * a(t - 1, i + 1, j) - 0.43 * a(t - 1, i, j - 1) - 0.453 * a(t - 1, i, j) - 0.453 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.5 * a(t - 1, i - 1, j) + 0.55 * a(t - 1, i, j) + 0.55 * a(t - 1, i + 1, j) - 0.5 * a(t - 1, i, j - 1) - 0.55 * a(t - 1, i, j) - 0.55 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.6 * a(t - 1, i - 1, j) + 0.65 * a(t - 1, i, j) + 0.65 * a(t - 1, i + 1, j) - 0.6 * a(t - 1, i, j - 1) - 0.65 * a(t - 1, i, j) - 0.65 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.7 * a(t - 1, i - 1, j) + 0.75 * a(t - 1, i, j) + 0.75 * a(t - 1, i + 1, j) - 0.7 * a(t - 1, i, j - 1) - 0.75 * a(t - 1, i, j) - 0.75 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8 * a(t - 1, i - 1, j) + 0.85 * a(t - 1, i, j) + 0.85 * a(t - 1, i + 1, j) - 0.8 * a(t - 1, i, j - 1) - 0.85 * a(t - 1, i, j) - 0.85 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.22000000000000003 * a(t - 1, i - 1, j) + 0.252 * a(t - 1, i, j) + 0.252 * a(t - 1, i + 1, j) - 0.22000000000000003 * a(t - 1, i, j - 1) - 0.252 * a(t - 1, i, j) - 0.252 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.53 * a(t - 1, i - 1, j) + 0.553 * a(t - 1, i, j) + 0.553 * a(t - 1, i + 1, j) - 0.53 * a(t - 1, i, j - 1) - 0.553 * a(t - 1, i, j) - 0.553 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.63 * a(t - 1, i - 1, j) + 0.653 * a(t - 1, i, j) + 0.653 * a(t - 1, i + 1, j) - 0.63 * a(t - 1, i, j - 1) - 0.653 * a(t - 1, i, j) - 0.653 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.73 * a(t - 1, i - 1, j) + 0.753 * a(t - 1, i, j) + 0.753 * a(t - 1, i + 1, j) - 0.73 * a(t - 1, i, j - 1) - 0.753 * a(t - 1, i, j) - 0.753 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8300000000000001 * a(t - 1, i - 1, j) + 0.853 * a(t - 1, i, j) + 0.853 * a(t - 1, i + 1, j) - 0.8300000000000001 * a(t - 1, i, j - 1) - 0.853 * a(t - 1, i, j) - 0.853 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
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
	static __Pointer_boundary_kernel_9__ * _Pointer_boundary_kernel_9 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_boundary_kernel_9 = NULL;
	#undef pmod_lu
	
	
	
	/* KNOWN */
	class __Pointer_cond_interior_kernel_9__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_interior_kernel_9__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.1 * pt_a_1[l_a_stride_1 * (-1)] + 0.15 * pt_a_1[0] + 0.15 * pt_a_1[l_a_stride_1 * (1)] - 0.1 * pt_a_1[l_a_stride_0 * (-1)] - 0.15 * pt_a_1[0] - 0.15 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.2 * pt_a_1[l_a_stride_1 * (-1)] + 0.25 * pt_a_1[0] + 0.25 * pt_a_1[l_a_stride_1 * (1)] - 0.2 * pt_a_1[l_a_stride_0 * (-1)] - 0.25 * pt_a_1[0] - 0.25 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.3 * pt_a_1[l_a_stride_1 * (-1)] + 0.35 * pt_a_1[0] + 0.35 * pt_a_1[l_a_stride_1 * (1)] - 0.3 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] - 0.35 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.4 * pt_a_1[l_a_stride_1 * (-1)] + 0.45 * pt_a_1[0] + 0.45 * pt_a_1[l_a_stride_1 * (1)] - 0.4 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] - 0.45 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.12 * pt_a_1[l_a_stride_1 * (-1)] + 0.152 * pt_a_1[0] + 0.152 * pt_a_1[l_a_stride_1 * (1)] - 0.12 * pt_a_1[l_a_stride_0 * (-1)] - 0.152 * pt_a_1[0] - 0.152 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.13 * pt_a_1[l_a_stride_1 * (-1)] + 0.153 * pt_a_1[0] + 0.153 * pt_a_1[l_a_stride_1 * (1)] - 0.13 * pt_a_1[l_a_stride_0 * (-1)] - 0.153 * pt_a_1[0] - 0.153 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.22999999999999998 * pt_a_1[l_a_stride_1 * (-1)] + 0.253 * pt_a_1[0] + 0.253 * pt_a_1[l_a_stride_1 * (1)] - 0.22999999999999998 * pt_a_1[l_a_stride_0 * (-1)] - 0.253 * pt_a_1[0] - 0.253 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.32999999999999996 * pt_a_1[l_a_stride_1 * (-1)] + 0.35300000000000004 * pt_a_1[0] + 0.35300000000000004 * pt_a_1[l_a_stride_1 * (1)] - 0.32999999999999996 * pt_a_1[l_a_stride_0 * (-1)] - 0.35300000000000004 * pt_a_1[0] - 0.35300000000000004 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.43 * pt_a_1[l_a_stride_1 * (-1)] + 0.453 * pt_a_1[0] + 0.453 * pt_a_1[l_a_stride_1 * (1)] - 0.43 * pt_a_1[l_a_stride_0 * (-1)] - 0.453 * pt_a_1[0] - 0.453 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.5 * pt_a_1[l_a_stride_1 * (-1)] + 0.55 * pt_a_1[0] + 0.55 * pt_a_1[l_a_stride_1 * (1)] - 0.5 * pt_a_1[l_a_stride_0 * (-1)] - 0.55 * pt_a_1[0] - 0.55 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.6 * pt_a_1[l_a_stride_1 * (-1)] + 0.65 * pt_a_1[0] + 0.65 * pt_a_1[l_a_stride_1 * (1)] - 0.6 * pt_a_1[l_a_stride_0 * (-1)] - 0.65 * pt_a_1[0] - 0.65 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.7 * pt_a_1[l_a_stride_1 * (-1)] + 0.75 * pt_a_1[0] + 0.75 * pt_a_1[l_a_stride_1 * (1)] - 0.7 * pt_a_1[l_a_stride_0 * (-1)] - 0.75 * pt_a_1[0] - 0.75 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.8 * pt_a_1[l_a_stride_1 * (-1)] + 0.85 * pt_a_1[0] + 0.85 * pt_a_1[l_a_stride_1 * (1)] - 0.8 * pt_a_1[l_a_stride_0 * (-1)] - 0.85 * pt_a_1[0] - 0.85 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.22000000000000003 * pt_a_1[l_a_stride_1 * (-1)] + 0.252 * pt_a_1[0] + 0.252 * pt_a_1[l_a_stride_1 * (1)] - 0.22000000000000003 * pt_a_1[l_a_stride_0 * (-1)] - 0.252 * pt_a_1[0] - 0.252 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.53 * pt_a_1[l_a_stride_1 * (-1)] + 0.553 * pt_a_1[0] + 0.553 * pt_a_1[l_a_stride_1 * (1)] - 0.53 * pt_a_1[l_a_stride_0 * (-1)] - 0.553 * pt_a_1[0] - 0.553 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.63 * pt_a_1[l_a_stride_1 * (-1)] + 0.653 * pt_a_1[0] + 0.653 * pt_a_1[l_a_stride_1 * (1)] - 0.63 * pt_a_1[l_a_stride_0 * (-1)] - 0.653 * pt_a_1[0] - 0.653 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.73 * pt_a_1[l_a_stride_1 * (-1)] + 0.753 * pt_a_1[0] + 0.753 * pt_a_1[l_a_stride_1 * (1)] - 0.73 * pt_a_1[l_a_stride_0 * (-1)] - 0.753 * pt_a_1[0] - 0.753 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.8300000000000001 * pt_a_1[l_a_stride_1 * (-1)] + 0.853 * pt_a_1[0] + 0.853 * pt_a_1[l_a_stride_1 * (1)] - 0.8300000000000001 * pt_a_1[l_a_stride_0 * (-1)] - 0.853 * pt_a_1[0] - 0.853 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
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
	static __Pointer_cond_interior_kernel_9__ * _Pointer_cond_interior_kernel_9 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_interior_kernel_9 = NULL;
	
	
	
	
	/* KNOWN */
	class __Pointer_interior_kernel_9__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_interior_kernel_9__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.1 * pt_a_1[l_a_stride_1 * (-1)] + 0.15 * pt_a_1[0] + 0.15 * pt_a_1[l_a_stride_1 * (1)] - 0.1 * pt_a_1[l_a_stride_0 * (-1)] - 0.15 * pt_a_1[0] - 0.15 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.2 * pt_a_1[l_a_stride_1 * (-1)] + 0.25 * pt_a_1[0] + 0.25 * pt_a_1[l_a_stride_1 * (1)] - 0.2 * pt_a_1[l_a_stride_0 * (-1)] - 0.25 * pt_a_1[0] - 0.25 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.3 * pt_a_1[l_a_stride_1 * (-1)] + 0.35 * pt_a_1[0] + 0.35 * pt_a_1[l_a_stride_1 * (1)] - 0.3 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] - 0.35 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.4 * pt_a_1[l_a_stride_1 * (-1)] + 0.45 * pt_a_1[0] + 0.45 * pt_a_1[l_a_stride_1 * (1)] - 0.4 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] - 0.45 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.12 * pt_a_1[l_a_stride_1 * (-1)] + 0.152 * pt_a_1[0] + 0.152 * pt_a_1[l_a_stride_1 * (1)] - 0.12 * pt_a_1[l_a_stride_0 * (-1)] - 0.152 * pt_a_1[0] - 0.152 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.13 * pt_a_1[l_a_stride_1 * (-1)] + 0.153 * pt_a_1[0] + 0.153 * pt_a_1[l_a_stride_1 * (1)] - 0.13 * pt_a_1[l_a_stride_0 * (-1)] - 0.153 * pt_a_1[0] - 0.153 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.22999999999999998 * pt_a_1[l_a_stride_1 * (-1)] + 0.253 * pt_a_1[0] + 0.253 * pt_a_1[l_a_stride_1 * (1)] - 0.22999999999999998 * pt_a_1[l_a_stride_0 * (-1)] - 0.253 * pt_a_1[0] - 0.253 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.32999999999999996 * pt_a_1[l_a_stride_1 * (-1)] + 0.35300000000000004 * pt_a_1[0] + 0.35300000000000004 * pt_a_1[l_a_stride_1 * (1)] - 0.32999999999999996 * pt_a_1[l_a_stride_0 * (-1)] - 0.35300000000000004 * pt_a_1[0] - 0.35300000000000004 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.43 * pt_a_1[l_a_stride_1 * (-1)] + 0.453 * pt_a_1[0] + 0.453 * pt_a_1[l_a_stride_1 * (1)] - 0.43 * pt_a_1[l_a_stride_0 * (-1)] - 0.453 * pt_a_1[0] - 0.453 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.5 * pt_a_1[l_a_stride_1 * (-1)] + 0.55 * pt_a_1[0] + 0.55 * pt_a_1[l_a_stride_1 * (1)] - 0.5 * pt_a_1[l_a_stride_0 * (-1)] - 0.55 * pt_a_1[0] - 0.55 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.6 * pt_a_1[l_a_stride_1 * (-1)] + 0.65 * pt_a_1[0] + 0.65 * pt_a_1[l_a_stride_1 * (1)] - 0.6 * pt_a_1[l_a_stride_0 * (-1)] - 0.65 * pt_a_1[0] - 0.65 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.7 * pt_a_1[l_a_stride_1 * (-1)] + 0.75 * pt_a_1[0] + 0.75 * pt_a_1[l_a_stride_1 * (1)] - 0.7 * pt_a_1[l_a_stride_0 * (-1)] - 0.75 * pt_a_1[0] - 0.75 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.8 * pt_a_1[l_a_stride_1 * (-1)] + 0.85 * pt_a_1[0] + 0.85 * pt_a_1[l_a_stride_1 * (1)] - 0.8 * pt_a_1[l_a_stride_0 * (-1)] - 0.85 * pt_a_1[0] - 0.85 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.22000000000000003 * pt_a_1[l_a_stride_1 * (-1)] + 0.252 * pt_a_1[0] + 0.252 * pt_a_1[l_a_stride_1 * (1)] - 0.22000000000000003 * pt_a_1[l_a_stride_0 * (-1)] - 0.252 * pt_a_1[0] - 0.252 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.53 * pt_a_1[l_a_stride_1 * (-1)] + 0.553 * pt_a_1[0] + 0.553 * pt_a_1[l_a_stride_1 * (1)] - 0.53 * pt_a_1[l_a_stride_0 * (-1)] - 0.553 * pt_a_1[0] - 0.553 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.63 * pt_a_1[l_a_stride_1 * (-1)] + 0.653 * pt_a_1[0] + 0.653 * pt_a_1[l_a_stride_1 * (1)] - 0.63 * pt_a_1[l_a_stride_0 * (-1)] - 0.653 * pt_a_1[0] - 0.653 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.73 * pt_a_1[l_a_stride_1 * (-1)] + 0.753 * pt_a_1[0] + 0.753 * pt_a_1[l_a_stride_1 * (1)] - 0.73 * pt_a_1[l_a_stride_0 * (-1)] - 0.753 * pt_a_1[0] - 0.753 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.8300000000000001 * pt_a_1[l_a_stride_1 * (-1)] + 0.853 * pt_a_1[0] + 0.853 * pt_a_1[l_a_stride_1 * (1)] - 0.8300000000000001 * pt_a_1[l_a_stride_0 * (-1)] - 0.853 * pt_a_1[0] - 0.853 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
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
	static __Pointer_interior_kernel_9__ * _Pointer_interior_kernel_9 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_interior_kernel_9 = NULL;
	
	
	
	/* <100100, 100000>
 */
	auto __POCHOIR_Guard_10__ = [&]  ( int t, int i0, int i1 )  -> bool {
	return ( __g_exclusive_0__ ( t + -1, i0, i1 )  && !__g_exclusive_1__ ( t + -1, i0, i1 )  && !__g_inclusive_0__ ( t + -1, i0, i1 )  && !__g_tiny_inclusive_0__ ( t + -1, i0, i1 )  && !__g_tiny_inclusive_1__ ( t + -1, i0, i1 )  );
	 };
	static Pochoir_Guard <2> POCHOIR_Guard_10 ( __POCHOIR_Guard_10__ ); 

	/* <100100, 100000>
 */
	
	
	/* 
	tile_3D_checkerboard_0 - PSERIAL;
	tile_3D_checkerboard_3 - PINCLUSIVE;
	__Pochoir_NULL__ - PNULL
	 */
	/* k_0_0, k_0_1, k_0_2, k_0_3, k_0_4, k_0_5, k_0_6, k_0_7, k_3_0, k_3_1, k_3_2, k_3_3, k_3_4, k_3_5, k_3_6, k_3_7, __Pochoir_NULL_ */ 
	/* 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0 */ 
	/* PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PNULL */ 
	/* [0,0,0], [0,0,1], [0,1,0], [0,1,1], [1,0,0], [1,0,1], [1,1,0], [1,1,1], [0,0,0], [0,0,1], [0,1,0], [0,1,1], [1,0,0], [1,0,1], [1,1,0], [1,1,1], [0] */ 
	/* [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [1] */ 
	/* 
	PMTile (sizes = [2,2,2], latest_tile_order = 3), terms = 
		PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = k_0_0, k_3_0
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = k_0_1, k_3_1
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = k_0_2, k_3_2
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = k_0_3, k_3_3
		PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = k_0_4, k_3_4
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = k_0_5, k_3_5
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = k_0_6, k_3_6
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = k_0_7, k_3_7
	 */ 
	static 
	Pochoir_Shape <2> __POCHOIR_Shape__10__ [ ] = {{0, 0, 0}, {-1, 0, -1}, {-1, 0, 1}, {-1, 1, 0}, {-1, -1, 0}, {-1, 0, 0}};
	/* toggle: 2; slopes: [] */
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_cond_boundary_kernel_10__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_boundary_kernel_10__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.1 * a(t - 1, i - 1, j) + 0.15 * a(t - 1, i, j) + 0.15 * a(t - 1, i + 1, j) - 0.1 * a(t - 1, i, j - 1) - 0.15 * a(t - 1, i, j) - 0.15 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.13 * a(t - 1, i - 1, j) + 0.153 * a(t - 1, i, j) + 0.153 * a(t - 1, i + 1, j) - 0.13 * a(t - 1, i, j - 1) - 0.153 * a(t - 1, i, j) - 0.153 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.2 * a(t - 1, i - 1, j) + 0.25 * a(t - 1, i, j) + 0.25 * a(t - 1, i + 1, j) - 0.2 * a(t - 1, i, j - 1) - 0.25 * a(t - 1, i, j) - 0.25 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.22999999999999998 * a(t - 1, i - 1, j) + 0.253 * a(t - 1, i, j) + 0.253 * a(t - 1, i + 1, j) - 0.22999999999999998 * a(t - 1, i, j - 1) - 0.253 * a(t - 1, i, j) - 0.253 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.3 * a(t - 1, i - 1, j) + 0.35 * a(t - 1, i, j) + 0.35 * a(t - 1, i + 1, j) - 0.3 * a(t - 1, i, j - 1) - 0.35 * a(t - 1, i, j) - 0.35 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.32999999999999996 * a(t - 1, i - 1, j) + 0.35300000000000004 * a(t - 1, i, j) + 0.35300000000000004 * a(t - 1, i + 1, j) - 0.32999999999999996 * a(t - 1, i, j - 1) - 0.35300000000000004 * a(t - 1, i, j) - 0.35300000000000004 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.4 * a(t - 1, i - 1, j) + 0.45 * a(t - 1, i, j) + 0.45 * a(t - 1, i + 1, j) - 0.4 * a(t - 1, i, j - 1) - 0.45 * a(t - 1, i, j) - 0.45 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.43 * a(t - 1, i - 1, j) + 0.453 * a(t - 1, i, j) + 0.453 * a(t - 1, i + 1, j) - 0.43 * a(t - 1, i, j - 1) - 0.453 * a(t - 1, i, j) - 0.453 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.5 * a(t - 1, i - 1, j) + 0.55 * a(t - 1, i, j) + 0.55 * a(t - 1, i + 1, j) - 0.5 * a(t - 1, i, j - 1) - 0.55 * a(t - 1, i, j) - 0.55 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.53 * a(t - 1, i - 1, j) + 0.553 * a(t - 1, i, j) + 0.553 * a(t - 1, i + 1, j) - 0.53 * a(t - 1, i, j - 1) - 0.553 * a(t - 1, i, j) - 0.553 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.6 * a(t - 1, i - 1, j) + 0.65 * a(t - 1, i, j) + 0.65 * a(t - 1, i + 1, j) - 0.6 * a(t - 1, i, j - 1) - 0.65 * a(t - 1, i, j) - 0.65 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.63 * a(t - 1, i - 1, j) + 0.653 * a(t - 1, i, j) + 0.653 * a(t - 1, i + 1, j) - 0.63 * a(t - 1, i, j - 1) - 0.653 * a(t - 1, i, j) - 0.653 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.7 * a(t - 1, i - 1, j) + 0.75 * a(t - 1, i, j) + 0.75 * a(t - 1, i + 1, j) - 0.7 * a(t - 1, i, j - 1) - 0.75 * a(t - 1, i, j) - 0.75 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.73 * a(t - 1, i - 1, j) + 0.753 * a(t - 1, i, j) + 0.753 * a(t - 1, i + 1, j) - 0.73 * a(t - 1, i, j - 1) - 0.753 * a(t - 1, i, j) - 0.753 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8 * a(t - 1, i - 1, j) + 0.85 * a(t - 1, i, j) + 0.85 * a(t - 1, i + 1, j) - 0.8 * a(t - 1, i, j - 1) - 0.85 * a(t - 1, i, j) - 0.85 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8300000000000001 * a(t - 1, i - 1, j) + 0.853 * a(t - 1, i, j) + 0.853 * a(t - 1, i + 1, j) - 0.8300000000000001 * a(t - 1, i, j - 1) - 0.853 * a(t - 1, i, j) - 0.853 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
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
	static __Pointer_cond_boundary_kernel_10__ * _Pointer_cond_boundary_kernel_10 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_boundary_kernel_10 = NULL;
	#undef pmod_lu
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_boundary_kernel_10__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_boundary_kernel_10__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.1 * a(t - 1, i - 1, j) + 0.15 * a(t - 1, i, j) + 0.15 * a(t - 1, i + 1, j) - 0.1 * a(t - 1, i, j - 1) - 0.15 * a(t - 1, i, j) - 0.15 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.13 * a(t - 1, i - 1, j) + 0.153 * a(t - 1, i, j) + 0.153 * a(t - 1, i + 1, j) - 0.13 * a(t - 1, i, j - 1) - 0.153 * a(t - 1, i, j) - 0.153 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.2 * a(t - 1, i - 1, j) + 0.25 * a(t - 1, i, j) + 0.25 * a(t - 1, i + 1, j) - 0.2 * a(t - 1, i, j - 1) - 0.25 * a(t - 1, i, j) - 0.25 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.22999999999999998 * a(t - 1, i - 1, j) + 0.253 * a(t - 1, i, j) + 0.253 * a(t - 1, i + 1, j) - 0.22999999999999998 * a(t - 1, i, j - 1) - 0.253 * a(t - 1, i, j) - 0.253 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.3 * a(t - 1, i - 1, j) + 0.35 * a(t - 1, i, j) + 0.35 * a(t - 1, i + 1, j) - 0.3 * a(t - 1, i, j - 1) - 0.35 * a(t - 1, i, j) - 0.35 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.32999999999999996 * a(t - 1, i - 1, j) + 0.35300000000000004 * a(t - 1, i, j) + 0.35300000000000004 * a(t - 1, i + 1, j) - 0.32999999999999996 * a(t - 1, i, j - 1) - 0.35300000000000004 * a(t - 1, i, j) - 0.35300000000000004 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.4 * a(t - 1, i - 1, j) + 0.45 * a(t - 1, i, j) + 0.45 * a(t - 1, i + 1, j) - 0.4 * a(t - 1, i, j - 1) - 0.45 * a(t - 1, i, j) - 0.45 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.43 * a(t - 1, i - 1, j) + 0.453 * a(t - 1, i, j) + 0.453 * a(t - 1, i + 1, j) - 0.43 * a(t - 1, i, j - 1) - 0.453 * a(t - 1, i, j) - 0.453 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.5 * a(t - 1, i - 1, j) + 0.55 * a(t - 1, i, j) + 0.55 * a(t - 1, i + 1, j) - 0.5 * a(t - 1, i, j - 1) - 0.55 * a(t - 1, i, j) - 0.55 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.53 * a(t - 1, i - 1, j) + 0.553 * a(t - 1, i, j) + 0.553 * a(t - 1, i + 1, j) - 0.53 * a(t - 1, i, j - 1) - 0.553 * a(t - 1, i, j) - 0.553 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.6 * a(t - 1, i - 1, j) + 0.65 * a(t - 1, i, j) + 0.65 * a(t - 1, i + 1, j) - 0.6 * a(t - 1, i, j - 1) - 0.65 * a(t - 1, i, j) - 0.65 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.63 * a(t - 1, i - 1, j) + 0.653 * a(t - 1, i, j) + 0.653 * a(t - 1, i + 1, j) - 0.63 * a(t - 1, i, j - 1) - 0.653 * a(t - 1, i, j) - 0.653 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.7 * a(t - 1, i - 1, j) + 0.75 * a(t - 1, i, j) + 0.75 * a(t - 1, i + 1, j) - 0.7 * a(t - 1, i, j - 1) - 0.75 * a(t - 1, i, j) - 0.75 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.73 * a(t - 1, i - 1, j) + 0.753 * a(t - 1, i, j) + 0.753 * a(t - 1, i + 1, j) - 0.73 * a(t - 1, i, j - 1) - 0.753 * a(t - 1, i, j) - 0.753 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8 * a(t - 1, i - 1, j) + 0.85 * a(t - 1, i, j) + 0.85 * a(t - 1, i + 1, j) - 0.8 * a(t - 1, i, j - 1) - 0.85 * a(t - 1, i, j) - 0.85 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8300000000000001 * a(t - 1, i - 1, j) + 0.853 * a(t - 1, i, j) + 0.853 * a(t - 1, i + 1, j) - 0.8300000000000001 * a(t - 1, i, j - 1) - 0.853 * a(t - 1, i, j) - 0.853 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
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
	static __Pointer_boundary_kernel_10__ * _Pointer_boundary_kernel_10 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_boundary_kernel_10 = NULL;
	#undef pmod_lu
	
	
	
	/* KNOWN */
	class __Pointer_cond_interior_kernel_10__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_interior_kernel_10__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.1 * pt_a_1[l_a_stride_1 * (-1)] + 0.15 * pt_a_1[0] + 0.15 * pt_a_1[l_a_stride_1 * (1)] - 0.1 * pt_a_1[l_a_stride_0 * (-1)] - 0.15 * pt_a_1[0] - 0.15 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.13 * pt_a_1[l_a_stride_1 * (-1)] + 0.153 * pt_a_1[0] + 0.153 * pt_a_1[l_a_stride_1 * (1)] - 0.13 * pt_a_1[l_a_stride_0 * (-1)] - 0.153 * pt_a_1[0] - 0.153 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.2 * pt_a_1[l_a_stride_1 * (-1)] + 0.25 * pt_a_1[0] + 0.25 * pt_a_1[l_a_stride_1 * (1)] - 0.2 * pt_a_1[l_a_stride_0 * (-1)] - 0.25 * pt_a_1[0] - 0.25 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.22999999999999998 * pt_a_1[l_a_stride_1 * (-1)] + 0.253 * pt_a_1[0] + 0.253 * pt_a_1[l_a_stride_1 * (1)] - 0.22999999999999998 * pt_a_1[l_a_stride_0 * (-1)] - 0.253 * pt_a_1[0] - 0.253 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.3 * pt_a_1[l_a_stride_1 * (-1)] + 0.35 * pt_a_1[0] + 0.35 * pt_a_1[l_a_stride_1 * (1)] - 0.3 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] - 0.35 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.32999999999999996 * pt_a_1[l_a_stride_1 * (-1)] + 0.35300000000000004 * pt_a_1[0] + 0.35300000000000004 * pt_a_1[l_a_stride_1 * (1)] - 0.32999999999999996 * pt_a_1[l_a_stride_0 * (-1)] - 0.35300000000000004 * pt_a_1[0] - 0.35300000000000004 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.4 * pt_a_1[l_a_stride_1 * (-1)] + 0.45 * pt_a_1[0] + 0.45 * pt_a_1[l_a_stride_1 * (1)] - 0.4 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] - 0.45 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.43 * pt_a_1[l_a_stride_1 * (-1)] + 0.453 * pt_a_1[0] + 0.453 * pt_a_1[l_a_stride_1 * (1)] - 0.43 * pt_a_1[l_a_stride_0 * (-1)] - 0.453 * pt_a_1[0] - 0.453 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.5 * pt_a_1[l_a_stride_1 * (-1)] + 0.55 * pt_a_1[0] + 0.55 * pt_a_1[l_a_stride_1 * (1)] - 0.5 * pt_a_1[l_a_stride_0 * (-1)] - 0.55 * pt_a_1[0] - 0.55 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.53 * pt_a_1[l_a_stride_1 * (-1)] + 0.553 * pt_a_1[0] + 0.553 * pt_a_1[l_a_stride_1 * (1)] - 0.53 * pt_a_1[l_a_stride_0 * (-1)] - 0.553 * pt_a_1[0] - 0.553 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.6 * pt_a_1[l_a_stride_1 * (-1)] + 0.65 * pt_a_1[0] + 0.65 * pt_a_1[l_a_stride_1 * (1)] - 0.6 * pt_a_1[l_a_stride_0 * (-1)] - 0.65 * pt_a_1[0] - 0.65 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.63 * pt_a_1[l_a_stride_1 * (-1)] + 0.653 * pt_a_1[0] + 0.653 * pt_a_1[l_a_stride_1 * (1)] - 0.63 * pt_a_1[l_a_stride_0 * (-1)] - 0.653 * pt_a_1[0] - 0.653 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.7 * pt_a_1[l_a_stride_1 * (-1)] + 0.75 * pt_a_1[0] + 0.75 * pt_a_1[l_a_stride_1 * (1)] - 0.7 * pt_a_1[l_a_stride_0 * (-1)] - 0.75 * pt_a_1[0] - 0.75 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.73 * pt_a_1[l_a_stride_1 * (-1)] + 0.753 * pt_a_1[0] + 0.753 * pt_a_1[l_a_stride_1 * (1)] - 0.73 * pt_a_1[l_a_stride_0 * (-1)] - 0.753 * pt_a_1[0] - 0.753 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.8 * pt_a_1[l_a_stride_1 * (-1)] + 0.85 * pt_a_1[0] + 0.85 * pt_a_1[l_a_stride_1 * (1)] - 0.8 * pt_a_1[l_a_stride_0 * (-1)] - 0.85 * pt_a_1[0] - 0.85 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.8300000000000001 * pt_a_1[l_a_stride_1 * (-1)] + 0.853 * pt_a_1[0] + 0.853 * pt_a_1[l_a_stride_1 * (1)] - 0.8300000000000001 * pt_a_1[l_a_stride_0 * (-1)] - 0.853 * pt_a_1[0] - 0.853 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
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
	static __Pointer_cond_interior_kernel_10__ * _Pointer_cond_interior_kernel_10 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_interior_kernel_10 = NULL;
	
	
	
	
	/* KNOWN */
	class __Pointer_interior_kernel_10__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_interior_kernel_10__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.1 * pt_a_1[l_a_stride_1 * (-1)] + 0.15 * pt_a_1[0] + 0.15 * pt_a_1[l_a_stride_1 * (1)] - 0.1 * pt_a_1[l_a_stride_0 * (-1)] - 0.15 * pt_a_1[0] - 0.15 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.13 * pt_a_1[l_a_stride_1 * (-1)] + 0.153 * pt_a_1[0] + 0.153 * pt_a_1[l_a_stride_1 * (1)] - 0.13 * pt_a_1[l_a_stride_0 * (-1)] - 0.153 * pt_a_1[0] - 0.153 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.2 * pt_a_1[l_a_stride_1 * (-1)] + 0.25 * pt_a_1[0] + 0.25 * pt_a_1[l_a_stride_1 * (1)] - 0.2 * pt_a_1[l_a_stride_0 * (-1)] - 0.25 * pt_a_1[0] - 0.25 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.22999999999999998 * pt_a_1[l_a_stride_1 * (-1)] + 0.253 * pt_a_1[0] + 0.253 * pt_a_1[l_a_stride_1 * (1)] - 0.22999999999999998 * pt_a_1[l_a_stride_0 * (-1)] - 0.253 * pt_a_1[0] - 0.253 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.3 * pt_a_1[l_a_stride_1 * (-1)] + 0.35 * pt_a_1[0] + 0.35 * pt_a_1[l_a_stride_1 * (1)] - 0.3 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] - 0.35 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.32999999999999996 * pt_a_1[l_a_stride_1 * (-1)] + 0.35300000000000004 * pt_a_1[0] + 0.35300000000000004 * pt_a_1[l_a_stride_1 * (1)] - 0.32999999999999996 * pt_a_1[l_a_stride_0 * (-1)] - 0.35300000000000004 * pt_a_1[0] - 0.35300000000000004 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.4 * pt_a_1[l_a_stride_1 * (-1)] + 0.45 * pt_a_1[0] + 0.45 * pt_a_1[l_a_stride_1 * (1)] - 0.4 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] - 0.45 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.43 * pt_a_1[l_a_stride_1 * (-1)] + 0.453 * pt_a_1[0] + 0.453 * pt_a_1[l_a_stride_1 * (1)] - 0.43 * pt_a_1[l_a_stride_0 * (-1)] - 0.453 * pt_a_1[0] - 0.453 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.5 * pt_a_1[l_a_stride_1 * (-1)] + 0.55 * pt_a_1[0] + 0.55 * pt_a_1[l_a_stride_1 * (1)] - 0.5 * pt_a_1[l_a_stride_0 * (-1)] - 0.55 * pt_a_1[0] - 0.55 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.53 * pt_a_1[l_a_stride_1 * (-1)] + 0.553 * pt_a_1[0] + 0.553 * pt_a_1[l_a_stride_1 * (1)] - 0.53 * pt_a_1[l_a_stride_0 * (-1)] - 0.553 * pt_a_1[0] - 0.553 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.6 * pt_a_1[l_a_stride_1 * (-1)] + 0.65 * pt_a_1[0] + 0.65 * pt_a_1[l_a_stride_1 * (1)] - 0.6 * pt_a_1[l_a_stride_0 * (-1)] - 0.65 * pt_a_1[0] - 0.65 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.63 * pt_a_1[l_a_stride_1 * (-1)] + 0.653 * pt_a_1[0] + 0.653 * pt_a_1[l_a_stride_1 * (1)] - 0.63 * pt_a_1[l_a_stride_0 * (-1)] - 0.653 * pt_a_1[0] - 0.653 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.7 * pt_a_1[l_a_stride_1 * (-1)] + 0.75 * pt_a_1[0] + 0.75 * pt_a_1[l_a_stride_1 * (1)] - 0.7 * pt_a_1[l_a_stride_0 * (-1)] - 0.75 * pt_a_1[0] - 0.75 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.73 * pt_a_1[l_a_stride_1 * (-1)] + 0.753 * pt_a_1[0] + 0.753 * pt_a_1[l_a_stride_1 * (1)] - 0.73 * pt_a_1[l_a_stride_0 * (-1)] - 0.753 * pt_a_1[0] - 0.753 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.8 * pt_a_1[l_a_stride_1 * (-1)] + 0.85 * pt_a_1[0] + 0.85 * pt_a_1[l_a_stride_1 * (1)] - 0.8 * pt_a_1[l_a_stride_0 * (-1)] - 0.85 * pt_a_1[0] - 0.85 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.8300000000000001 * pt_a_1[l_a_stride_1 * (-1)] + 0.853 * pt_a_1[0] + 0.853 * pt_a_1[l_a_stride_1 * (1)] - 0.8300000000000001 * pt_a_1[l_a_stride_0 * (-1)] - 0.853 * pt_a_1[0] - 0.853 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
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
	static __Pointer_interior_kernel_10__ * _Pointer_interior_kernel_10 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_interior_kernel_10 = NULL;
	
	
	
	/* <100100, 100100>
 */
	auto __POCHOIR_Guard_11__ = [&]  ( int t, int i0, int i1 )  -> bool {
	return ( __g_exclusive_0__ ( t + -1, i0, i1 )  && !__g_exclusive_1__ ( t + -1, i0, i1 )  && !__g_inclusive_0__ ( t + -1, i0, i1 )  && __g_inclusive_1__ ( t + -1, i0, i1 )  && !__g_tiny_inclusive_0__ ( t + -1, i0, i1 )  && !__g_tiny_inclusive_1__ ( t + -1, i0, i1 )  );
	 };
	static Pochoir_Guard <2> POCHOIR_Guard_11 ( __POCHOIR_Guard_11__ ); 

	/* <100100, 100100>
 */
	
	
	/* 
	tile_3D_checkerboard_0 - PSERIAL;
	tile_3D_checkerboard_3 - PSERIAL;
	__Pochoir_NULL__ - PNULL
	 */
	/* k_0_0, k_0_1, k_0_2, k_0_3, k_0_4, k_0_5, k_0_6, k_0_7, k_3_0, k_3_1, k_3_2, k_3_3, k_3_4, k_3_5, k_3_6, k_3_7, __Pochoir_NULL_ */ 
	/* 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0 */ 
	/* PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PNULL */ 
	/* [0,0,0], [0,0,1], [0,1,0], [0,1,1], [1,0,0], [1,0,1], [1,1,0], [1,1,1], [0,0,0], [0,0,1], [0,1,0], [0,1,1], [1,0,0], [1,0,1], [1,1,0], [1,1,1], [0] */ 
	/* [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [1] */ 
	/* 
	PMTile (sizes = [2,2,2], latest_tile_order = 3), terms = 
		PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = k_0_0, k_3_0
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = k_0_1, k_3_1
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = k_0_2, k_3_2
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = k_0_3, k_3_3
		PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = k_0_4, k_3_4
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = k_0_5, k_3_5
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = k_0_6, k_3_6
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = k_0_7, k_3_7
	 */ 
	static 
	Pochoir_Shape <2> __POCHOIR_Shape__11__ [ ] = {{0, 0, 0}, {-1, 0, -1}, {-1, 0, 1}, {-1, 1, 0}, {-1, -1, 0}, {-1, 0, 0}};
	/* toggle: 2; slopes: [] */
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_cond_boundary_kernel_11__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_boundary_kernel_11__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.1 * a(t - 1, i - 1, j) + 0.15 * a(t - 1, i, j) + 0.15 * a(t - 1, i + 1, j) - 0.1 * a(t - 1, i, j - 1) - 0.15 * a(t - 1, i, j) - 0.15 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.13 * a(t - 1, i - 1, j) + 0.153 * a(t - 1, i, j) + 0.153 * a(t - 1, i + 1, j) - 0.13 * a(t - 1, i, j - 1) - 0.153 * a(t - 1, i, j) - 0.153 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.2 * a(t - 1, i - 1, j) + 0.25 * a(t - 1, i, j) + 0.25 * a(t - 1, i + 1, j) - 0.2 * a(t - 1, i, j - 1) - 0.25 * a(t - 1, i, j) - 0.25 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.22999999999999998 * a(t - 1, i - 1, j) + 0.253 * a(t - 1, i, j) + 0.253 * a(t - 1, i + 1, j) - 0.22999999999999998 * a(t - 1, i, j - 1) - 0.253 * a(t - 1, i, j) - 0.253 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.3 * a(t - 1, i - 1, j) + 0.35 * a(t - 1, i, j) + 0.35 * a(t - 1, i + 1, j) - 0.3 * a(t - 1, i, j - 1) - 0.35 * a(t - 1, i, j) - 0.35 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.32999999999999996 * a(t - 1, i - 1, j) + 0.35300000000000004 * a(t - 1, i, j) + 0.35300000000000004 * a(t - 1, i + 1, j) - 0.32999999999999996 * a(t - 1, i, j - 1) - 0.35300000000000004 * a(t - 1, i, j) - 0.35300000000000004 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.4 * a(t - 1, i - 1, j) + 0.45 * a(t - 1, i, j) + 0.45 * a(t - 1, i + 1, j) - 0.4 * a(t - 1, i, j - 1) - 0.45 * a(t - 1, i, j) - 0.45 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.43 * a(t - 1, i - 1, j) + 0.453 * a(t - 1, i, j) + 0.453 * a(t - 1, i + 1, j) - 0.43 * a(t - 1, i, j - 1) - 0.453 * a(t - 1, i, j) - 0.453 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.5 * a(t - 1, i - 1, j) + 0.55 * a(t - 1, i, j) + 0.55 * a(t - 1, i + 1, j) - 0.5 * a(t - 1, i, j - 1) - 0.55 * a(t - 1, i, j) - 0.55 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.53 * a(t - 1, i - 1, j) + 0.553 * a(t - 1, i, j) + 0.553 * a(t - 1, i + 1, j) - 0.53 * a(t - 1, i, j - 1) - 0.553 * a(t - 1, i, j) - 0.553 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.6 * a(t - 1, i - 1, j) + 0.65 * a(t - 1, i, j) + 0.65 * a(t - 1, i + 1, j) - 0.6 * a(t - 1, i, j - 1) - 0.65 * a(t - 1, i, j) - 0.65 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.63 * a(t - 1, i - 1, j) + 0.653 * a(t - 1, i, j) + 0.653 * a(t - 1, i + 1, j) - 0.63 * a(t - 1, i, j - 1) - 0.653 * a(t - 1, i, j) - 0.653 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.7 * a(t - 1, i - 1, j) + 0.75 * a(t - 1, i, j) + 0.75 * a(t - 1, i + 1, j) - 0.7 * a(t - 1, i, j - 1) - 0.75 * a(t - 1, i, j) - 0.75 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.73 * a(t - 1, i - 1, j) + 0.753 * a(t - 1, i, j) + 0.753 * a(t - 1, i + 1, j) - 0.73 * a(t - 1, i, j - 1) - 0.753 * a(t - 1, i, j) - 0.753 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8 * a(t - 1, i - 1, j) + 0.85 * a(t - 1, i, j) + 0.85 * a(t - 1, i + 1, j) - 0.8 * a(t - 1, i, j - 1) - 0.85 * a(t - 1, i, j) - 0.85 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8300000000000001 * a(t - 1, i - 1, j) + 0.853 * a(t - 1, i, j) + 0.853 * a(t - 1, i + 1, j) - 0.8300000000000001 * a(t - 1, i, j - 1) - 0.853 * a(t - 1, i, j) - 0.853 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
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
	static __Pointer_cond_boundary_kernel_11__ * _Pointer_cond_boundary_kernel_11 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_boundary_kernel_11 = NULL;
	#undef pmod_lu
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_boundary_kernel_11__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_boundary_kernel_11__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.1 * a(t - 1, i - 1, j) + 0.15 * a(t - 1, i, j) + 0.15 * a(t - 1, i + 1, j) - 0.1 * a(t - 1, i, j - 1) - 0.15 * a(t - 1, i, j) - 0.15 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.13 * a(t - 1, i - 1, j) + 0.153 * a(t - 1, i, j) + 0.153 * a(t - 1, i + 1, j) - 0.13 * a(t - 1, i, j - 1) - 0.153 * a(t - 1, i, j) - 0.153 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.2 * a(t - 1, i - 1, j) + 0.25 * a(t - 1, i, j) + 0.25 * a(t - 1, i + 1, j) - 0.2 * a(t - 1, i, j - 1) - 0.25 * a(t - 1, i, j) - 0.25 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.22999999999999998 * a(t - 1, i - 1, j) + 0.253 * a(t - 1, i, j) + 0.253 * a(t - 1, i + 1, j) - 0.22999999999999998 * a(t - 1, i, j - 1) - 0.253 * a(t - 1, i, j) - 0.253 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.3 * a(t - 1, i - 1, j) + 0.35 * a(t - 1, i, j) + 0.35 * a(t - 1, i + 1, j) - 0.3 * a(t - 1, i, j - 1) - 0.35 * a(t - 1, i, j) - 0.35 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.32999999999999996 * a(t - 1, i - 1, j) + 0.35300000000000004 * a(t - 1, i, j) + 0.35300000000000004 * a(t - 1, i + 1, j) - 0.32999999999999996 * a(t - 1, i, j - 1) - 0.35300000000000004 * a(t - 1, i, j) - 0.35300000000000004 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.4 * a(t - 1, i - 1, j) + 0.45 * a(t - 1, i, j) + 0.45 * a(t - 1, i + 1, j) - 0.4 * a(t - 1, i, j - 1) - 0.45 * a(t - 1, i, j) - 0.45 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.43 * a(t - 1, i - 1, j) + 0.453 * a(t - 1, i, j) + 0.453 * a(t - 1, i + 1, j) - 0.43 * a(t - 1, i, j - 1) - 0.453 * a(t - 1, i, j) - 0.453 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.5 * a(t - 1, i - 1, j) + 0.55 * a(t - 1, i, j) + 0.55 * a(t - 1, i + 1, j) - 0.5 * a(t - 1, i, j - 1) - 0.55 * a(t - 1, i, j) - 0.55 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.53 * a(t - 1, i - 1, j) + 0.553 * a(t - 1, i, j) + 0.553 * a(t - 1, i + 1, j) - 0.53 * a(t - 1, i, j - 1) - 0.553 * a(t - 1, i, j) - 0.553 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.6 * a(t - 1, i - 1, j) + 0.65 * a(t - 1, i, j) + 0.65 * a(t - 1, i + 1, j) - 0.6 * a(t - 1, i, j - 1) - 0.65 * a(t - 1, i, j) - 0.65 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.63 * a(t - 1, i - 1, j) + 0.653 * a(t - 1, i, j) + 0.653 * a(t - 1, i + 1, j) - 0.63 * a(t - 1, i, j - 1) - 0.653 * a(t - 1, i, j) - 0.653 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.7 * a(t - 1, i - 1, j) + 0.75 * a(t - 1, i, j) + 0.75 * a(t - 1, i + 1, j) - 0.7 * a(t - 1, i, j - 1) - 0.75 * a(t - 1, i, j) - 0.75 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.73 * a(t - 1, i - 1, j) + 0.753 * a(t - 1, i, j) + 0.753 * a(t - 1, i + 1, j) - 0.73 * a(t - 1, i, j - 1) - 0.753 * a(t - 1, i, j) - 0.753 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8 * a(t - 1, i - 1, j) + 0.85 * a(t - 1, i, j) + 0.85 * a(t - 1, i + 1, j) - 0.8 * a(t - 1, i, j - 1) - 0.85 * a(t - 1, i, j) - 0.85 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8300000000000001 * a(t - 1, i - 1, j) + 0.853 * a(t - 1, i, j) + 0.853 * a(t - 1, i + 1, j) - 0.8300000000000001 * a(t - 1, i, j - 1) - 0.853 * a(t - 1, i, j) - 0.853 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
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
	static __Pointer_boundary_kernel_11__ * _Pointer_boundary_kernel_11 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_boundary_kernel_11 = NULL;
	#undef pmod_lu
	
	
	
	/* KNOWN */
	class __Pointer_cond_interior_kernel_11__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_interior_kernel_11__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.1 * pt_a_1[l_a_stride_1 * (-1)] + 0.15 * pt_a_1[0] + 0.15 * pt_a_1[l_a_stride_1 * (1)] - 0.1 * pt_a_1[l_a_stride_0 * (-1)] - 0.15 * pt_a_1[0] - 0.15 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.13 * pt_a_1[l_a_stride_1 * (-1)] + 0.153 * pt_a_1[0] + 0.153 * pt_a_1[l_a_stride_1 * (1)] - 0.13 * pt_a_1[l_a_stride_0 * (-1)] - 0.153 * pt_a_1[0] - 0.153 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.2 * pt_a_1[l_a_stride_1 * (-1)] + 0.25 * pt_a_1[0] + 0.25 * pt_a_1[l_a_stride_1 * (1)] - 0.2 * pt_a_1[l_a_stride_0 * (-1)] - 0.25 * pt_a_1[0] - 0.25 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.22999999999999998 * pt_a_1[l_a_stride_1 * (-1)] + 0.253 * pt_a_1[0] + 0.253 * pt_a_1[l_a_stride_1 * (1)] - 0.22999999999999998 * pt_a_1[l_a_stride_0 * (-1)] - 0.253 * pt_a_1[0] - 0.253 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.3 * pt_a_1[l_a_stride_1 * (-1)] + 0.35 * pt_a_1[0] + 0.35 * pt_a_1[l_a_stride_1 * (1)] - 0.3 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] - 0.35 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.32999999999999996 * pt_a_1[l_a_stride_1 * (-1)] + 0.35300000000000004 * pt_a_1[0] + 0.35300000000000004 * pt_a_1[l_a_stride_1 * (1)] - 0.32999999999999996 * pt_a_1[l_a_stride_0 * (-1)] - 0.35300000000000004 * pt_a_1[0] - 0.35300000000000004 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.4 * pt_a_1[l_a_stride_1 * (-1)] + 0.45 * pt_a_1[0] + 0.45 * pt_a_1[l_a_stride_1 * (1)] - 0.4 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] - 0.45 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.43 * pt_a_1[l_a_stride_1 * (-1)] + 0.453 * pt_a_1[0] + 0.453 * pt_a_1[l_a_stride_1 * (1)] - 0.43 * pt_a_1[l_a_stride_0 * (-1)] - 0.453 * pt_a_1[0] - 0.453 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.5 * pt_a_1[l_a_stride_1 * (-1)] + 0.55 * pt_a_1[0] + 0.55 * pt_a_1[l_a_stride_1 * (1)] - 0.5 * pt_a_1[l_a_stride_0 * (-1)] - 0.55 * pt_a_1[0] - 0.55 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.53 * pt_a_1[l_a_stride_1 * (-1)] + 0.553 * pt_a_1[0] + 0.553 * pt_a_1[l_a_stride_1 * (1)] - 0.53 * pt_a_1[l_a_stride_0 * (-1)] - 0.553 * pt_a_1[0] - 0.553 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.6 * pt_a_1[l_a_stride_1 * (-1)] + 0.65 * pt_a_1[0] + 0.65 * pt_a_1[l_a_stride_1 * (1)] - 0.6 * pt_a_1[l_a_stride_0 * (-1)] - 0.65 * pt_a_1[0] - 0.65 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.63 * pt_a_1[l_a_stride_1 * (-1)] + 0.653 * pt_a_1[0] + 0.653 * pt_a_1[l_a_stride_1 * (1)] - 0.63 * pt_a_1[l_a_stride_0 * (-1)] - 0.653 * pt_a_1[0] - 0.653 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.7 * pt_a_1[l_a_stride_1 * (-1)] + 0.75 * pt_a_1[0] + 0.75 * pt_a_1[l_a_stride_1 * (1)] - 0.7 * pt_a_1[l_a_stride_0 * (-1)] - 0.75 * pt_a_1[0] - 0.75 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.73 * pt_a_1[l_a_stride_1 * (-1)] + 0.753 * pt_a_1[0] + 0.753 * pt_a_1[l_a_stride_1 * (1)] - 0.73 * pt_a_1[l_a_stride_0 * (-1)] - 0.753 * pt_a_1[0] - 0.753 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.8 * pt_a_1[l_a_stride_1 * (-1)] + 0.85 * pt_a_1[0] + 0.85 * pt_a_1[l_a_stride_1 * (1)] - 0.8 * pt_a_1[l_a_stride_0 * (-1)] - 0.85 * pt_a_1[0] - 0.85 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.8300000000000001 * pt_a_1[l_a_stride_1 * (-1)] + 0.853 * pt_a_1[0] + 0.853 * pt_a_1[l_a_stride_1 * (1)] - 0.8300000000000001 * pt_a_1[l_a_stride_0 * (-1)] - 0.853 * pt_a_1[0] - 0.853 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
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
	static __Pointer_cond_interior_kernel_11__ * _Pointer_cond_interior_kernel_11 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_interior_kernel_11 = NULL;
	
	
	
	
	/* KNOWN */
	class __Pointer_interior_kernel_11__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_interior_kernel_11__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.1 * pt_a_1[l_a_stride_1 * (-1)] + 0.15 * pt_a_1[0] + 0.15 * pt_a_1[l_a_stride_1 * (1)] - 0.1 * pt_a_1[l_a_stride_0 * (-1)] - 0.15 * pt_a_1[0] - 0.15 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.13 * pt_a_1[l_a_stride_1 * (-1)] + 0.153 * pt_a_1[0] + 0.153 * pt_a_1[l_a_stride_1 * (1)] - 0.13 * pt_a_1[l_a_stride_0 * (-1)] - 0.153 * pt_a_1[0] - 0.153 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.2 * pt_a_1[l_a_stride_1 * (-1)] + 0.25 * pt_a_1[0] + 0.25 * pt_a_1[l_a_stride_1 * (1)] - 0.2 * pt_a_1[l_a_stride_0 * (-1)] - 0.25 * pt_a_1[0] - 0.25 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.22999999999999998 * pt_a_1[l_a_stride_1 * (-1)] + 0.253 * pt_a_1[0] + 0.253 * pt_a_1[l_a_stride_1 * (1)] - 0.22999999999999998 * pt_a_1[l_a_stride_0 * (-1)] - 0.253 * pt_a_1[0] - 0.253 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.3 * pt_a_1[l_a_stride_1 * (-1)] + 0.35 * pt_a_1[0] + 0.35 * pt_a_1[l_a_stride_1 * (1)] - 0.3 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] - 0.35 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.32999999999999996 * pt_a_1[l_a_stride_1 * (-1)] + 0.35300000000000004 * pt_a_1[0] + 0.35300000000000004 * pt_a_1[l_a_stride_1 * (1)] - 0.32999999999999996 * pt_a_1[l_a_stride_0 * (-1)] - 0.35300000000000004 * pt_a_1[0] - 0.35300000000000004 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.4 * pt_a_1[l_a_stride_1 * (-1)] + 0.45 * pt_a_1[0] + 0.45 * pt_a_1[l_a_stride_1 * (1)] - 0.4 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] - 0.45 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.43 * pt_a_1[l_a_stride_1 * (-1)] + 0.453 * pt_a_1[0] + 0.453 * pt_a_1[l_a_stride_1 * (1)] - 0.43 * pt_a_1[l_a_stride_0 * (-1)] - 0.453 * pt_a_1[0] - 0.453 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.5 * pt_a_1[l_a_stride_1 * (-1)] + 0.55 * pt_a_1[0] + 0.55 * pt_a_1[l_a_stride_1 * (1)] - 0.5 * pt_a_1[l_a_stride_0 * (-1)] - 0.55 * pt_a_1[0] - 0.55 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.53 * pt_a_1[l_a_stride_1 * (-1)] + 0.553 * pt_a_1[0] + 0.553 * pt_a_1[l_a_stride_1 * (1)] - 0.53 * pt_a_1[l_a_stride_0 * (-1)] - 0.553 * pt_a_1[0] - 0.553 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.6 * pt_a_1[l_a_stride_1 * (-1)] + 0.65 * pt_a_1[0] + 0.65 * pt_a_1[l_a_stride_1 * (1)] - 0.6 * pt_a_1[l_a_stride_0 * (-1)] - 0.65 * pt_a_1[0] - 0.65 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.63 * pt_a_1[l_a_stride_1 * (-1)] + 0.653 * pt_a_1[0] + 0.653 * pt_a_1[l_a_stride_1 * (1)] - 0.63 * pt_a_1[l_a_stride_0 * (-1)] - 0.653 * pt_a_1[0] - 0.653 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.7 * pt_a_1[l_a_stride_1 * (-1)] + 0.75 * pt_a_1[0] + 0.75 * pt_a_1[l_a_stride_1 * (1)] - 0.7 * pt_a_1[l_a_stride_0 * (-1)] - 0.75 * pt_a_1[0] - 0.75 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.73 * pt_a_1[l_a_stride_1 * (-1)] + 0.753 * pt_a_1[0] + 0.753 * pt_a_1[l_a_stride_1 * (1)] - 0.73 * pt_a_1[l_a_stride_0 * (-1)] - 0.753 * pt_a_1[0] - 0.753 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.8 * pt_a_1[l_a_stride_1 * (-1)] + 0.85 * pt_a_1[0] + 0.85 * pt_a_1[l_a_stride_1 * (1)] - 0.8 * pt_a_1[l_a_stride_0 * (-1)] - 0.85 * pt_a_1[0] - 0.85 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.8300000000000001 * pt_a_1[l_a_stride_1 * (-1)] + 0.853 * pt_a_1[0] + 0.853 * pt_a_1[l_a_stride_1 * (1)] - 0.8300000000000001 * pt_a_1[l_a_stride_0 * (-1)] - 0.853 * pt_a_1[0] - 0.853 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
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
	static __Pointer_interior_kernel_11__ * _Pointer_interior_kernel_11 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_interior_kernel_11 = NULL;
	
	
	
	/* <111010, 000000>
 */
	auto __POCHOIR_Guard_12__ = [&]  ( int t, int i0, int i1 )  -> bool {
	return ( !__g_inclusive_1__ ( t + -1, i0, i1 )  && !__g_tiny_inclusive_1__ ( t + -1, i0, i1 )  );
	 };
	static Pochoir_Guard <2> POCHOIR_Guard_12 ( __POCHOIR_Guard_12__ ); 

	/* <111010, 000000>
 */
	
	
	/* 
	tile_3D_checkerboard_0 - PINCLUSIVE;
	tile_2D_checkerboard_1 - PINCLUSIVE;
	tile_1D_checkerboard_2 - PINCLUSIVE;
	tile_2D_checkerboard_4 - PINCLUSIVE;
	__Pochoir_NULL__ - PNULL
	 */
	/* k_0_0, k_0_1, k_0_2, k_0_3, k_0_4, k_0_5, k_0_6, k_0_7, k_1_0, k_1_1, k_1_2, k_1_3, k_2_0, k_2_1, k_4_0, k_4_1, k_4_2, k_4_3, __Pochoir_NULL_ */ 
	/* 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 4, 4, 4, 4, 0 */ 
	/* PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PNULL */ 
	/* [0,0,0], [0,0,1], [0,1,0], [0,1,1], [1,0,0], [1,0,1], [1,1,0], [1,1,1], [0,0], [0,1], [1,0], [1,1], [0], [1], [0,0], [0,1], [1,0], [1,1], [0] */ 
	/* [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2], [2,2], [2,2], [2,2], [2], [2], [2,2], [2,2], [2,2], [2,2], [1] */ 
	/* 
	PMTile (sizes = [2,2,2], latest_tile_order = 4), terms = 
		PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 4), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 1), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_0
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_1
				PMTileTerm (indices = [], sizes = [], latest_tile_order = 1), item = k_1_0
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 1), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_2
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_3
				PMTileTerm (indices = [], sizes = [], latest_tile_order = 1), item = k_1_1
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 2), item = k_2_0
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 4), item = k_4_0
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 4), item = k_4_1
		PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 4), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 1), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_4
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_5
				PMTileTerm (indices = [], sizes = [], latest_tile_order = 1), item = k_1_2
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 1), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_6
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_7
				PMTileTerm (indices = [], sizes = [], latest_tile_order = 1), item = k_1_3
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 2), item = k_2_1
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 4), item = k_4_2
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 4), item = k_4_3
	 */ 
	static 
	Pochoir_Shape <2> __POCHOIR_Shape__12__ [ ] = {{0, 0, 0}, {-1, 0, -1}, {-1, 0, 1}, {-1, 1, 0}, {-1, -1, 0}, {-1, 0, 0}};
	/* toggle: 2; slopes: [] */
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_cond_boundary_kernel_12__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_boundary_kernel_12__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.1 * a(t - 1, i - 1, j) + 0.15 * a(t - 1, i, j) + 0.15 * a(t - 1, i + 1, j) - 0.1 * a(t - 1, i, j - 1) - 0.15 * a(t - 1, i, j) - 0.15 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.2 * a(t - 1, i - 1, j) + 0.25 * a(t - 1, i, j) + 0.25 * a(t - 1, i + 1, j) - 0.2 * a(t - 1, i, j - 1) - 0.25 * a(t - 1, i, j) - 0.25 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.11000000000000001 * a(t - 1, i - 1, j) + 0.151 * a(t - 1, i, j) + 0.151 * a(t - 1, i + 1, j) - 0.11000000000000001 * a(t - 1, i, j - 1) - 0.151 * a(t - 1, i, j) - 0.151 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.3 * a(t - 1, i - 1, j) + 0.35 * a(t - 1, i, j) + 0.35 * a(t - 1, i + 1, j) - 0.3 * a(t - 1, i, j - 1) - 0.35 * a(t - 1, i, j) - 0.35 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.4 * a(t - 1, i - 1, j) + 0.45 * a(t - 1, i, j) + 0.45 * a(t - 1, i + 1, j) - 0.4 * a(t - 1, i, j - 1) - 0.45 * a(t - 1, i, j) - 0.45 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.21000000000000002 * a(t - 1, i - 1, j) + 0.251 * a(t - 1, i, j) + 0.251 * a(t - 1, i + 1, j) - 0.21000000000000002 * a(t - 1, i, j - 1) - 0.251 * a(t - 1, i, j) - 0.251 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.12 * a(t - 1, i - 1, j) + 0.152 * a(t - 1, i, j) + 0.152 * a(t - 1, i + 1, j) - 0.12 * a(t - 1, i, j - 1) - 0.152 * a(t - 1, i, j) - 0.152 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.13999999999999999 * a(t - 1, i - 1, j) + 0.154 * a(t - 1, i, j) + 0.154 * a(t - 1, i + 1, j) - 0.13999999999999999 * a(t - 1, i, j - 1) - 0.154 * a(t - 1, i, j) - 0.154 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.24 * a(t - 1, i - 1, j) + 0.254 * a(t - 1, i, j) + 0.254 * a(t - 1, i + 1, j) - 0.24 * a(t - 1, i, j - 1) - 0.254 * a(t - 1, i, j) - 0.254 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.5 * a(t - 1, i - 1, j) + 0.55 * a(t - 1, i, j) + 0.55 * a(t - 1, i + 1, j) - 0.5 * a(t - 1, i, j - 1) - 0.55 * a(t - 1, i, j) - 0.55 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.6 * a(t - 1, i - 1, j) + 0.65 * a(t - 1, i, j) + 0.65 * a(t - 1, i + 1, j) - 0.6 * a(t - 1, i, j - 1) - 0.65 * a(t - 1, i, j) - 0.65 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.31 * a(t - 1, i - 1, j) + 0.351 * a(t - 1, i, j) + 0.351 * a(t - 1, i + 1, j) - 0.31 * a(t - 1, i, j - 1) - 0.351 * a(t - 1, i, j) - 0.351 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.7 * a(t - 1, i - 1, j) + 0.75 * a(t - 1, i, j) + 0.75 * a(t - 1, i + 1, j) - 0.7 * a(t - 1, i, j - 1) - 0.75 * a(t - 1, i, j) - 0.75 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8 * a(t - 1, i - 1, j) + 0.85 * a(t - 1, i, j) + 0.85 * a(t - 1, i + 1, j) - 0.8 * a(t - 1, i, j - 1) - 0.85 * a(t - 1, i, j) - 0.85 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.41 * a(t - 1, i - 1, j) + 0.45099999999999996 * a(t - 1, i, j) + 0.45099999999999996 * a(t - 1, i + 1, j) - 0.41 * a(t - 1, i, j - 1) - 0.45099999999999996 * a(t - 1, i, j) - 0.45099999999999996 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.22000000000000003 * a(t - 1, i - 1, j) + 0.252 * a(t - 1, i, j) + 0.252 * a(t - 1, i + 1, j) - 0.22000000000000003 * a(t - 1, i, j - 1) - 0.252 * a(t - 1, i, j) - 0.252 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.33999999999999997 * a(t - 1, i - 1, j) + 0.354 * a(t - 1, i, j) + 0.354 * a(t - 1, i + 1, j) - 0.33999999999999997 * a(t - 1, i, j - 1) - 0.354 * a(t - 1, i, j) - 0.354 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.44000000000000006 * a(t - 1, i - 1, j) + 0.454 * a(t - 1, i, j) + 0.454 * a(t - 1, i + 1, j) - 0.44000000000000006 * a(t - 1, i, j - 1) - 0.454 * a(t - 1, i, j) - 0.454 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
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
	static __Pointer_cond_boundary_kernel_12__ * _Pointer_cond_boundary_kernel_12 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_boundary_kernel_12 = NULL;
	#undef pmod_lu
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_boundary_kernel_12__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_boundary_kernel_12__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.1 * a(t - 1, i - 1, j) + 0.15 * a(t - 1, i, j) + 0.15 * a(t - 1, i + 1, j) - 0.1 * a(t - 1, i, j - 1) - 0.15 * a(t - 1, i, j) - 0.15 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.2 * a(t - 1, i - 1, j) + 0.25 * a(t - 1, i, j) + 0.25 * a(t - 1, i + 1, j) - 0.2 * a(t - 1, i, j - 1) - 0.25 * a(t - 1, i, j) - 0.25 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.11000000000000001 * a(t - 1, i - 1, j) + 0.151 * a(t - 1, i, j) + 0.151 * a(t - 1, i + 1, j) - 0.11000000000000001 * a(t - 1, i, j - 1) - 0.151 * a(t - 1, i, j) - 0.151 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.3 * a(t - 1, i - 1, j) + 0.35 * a(t - 1, i, j) + 0.35 * a(t - 1, i + 1, j) - 0.3 * a(t - 1, i, j - 1) - 0.35 * a(t - 1, i, j) - 0.35 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.4 * a(t - 1, i - 1, j) + 0.45 * a(t - 1, i, j) + 0.45 * a(t - 1, i + 1, j) - 0.4 * a(t - 1, i, j - 1) - 0.45 * a(t - 1, i, j) - 0.45 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.21000000000000002 * a(t - 1, i - 1, j) + 0.251 * a(t - 1, i, j) + 0.251 * a(t - 1, i + 1, j) - 0.21000000000000002 * a(t - 1, i, j - 1) - 0.251 * a(t - 1, i, j) - 0.251 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.12 * a(t - 1, i - 1, j) + 0.152 * a(t - 1, i, j) + 0.152 * a(t - 1, i + 1, j) - 0.12 * a(t - 1, i, j - 1) - 0.152 * a(t - 1, i, j) - 0.152 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.13999999999999999 * a(t - 1, i - 1, j) + 0.154 * a(t - 1, i, j) + 0.154 * a(t - 1, i + 1, j) - 0.13999999999999999 * a(t - 1, i, j - 1) - 0.154 * a(t - 1, i, j) - 0.154 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.24 * a(t - 1, i - 1, j) + 0.254 * a(t - 1, i, j) + 0.254 * a(t - 1, i + 1, j) - 0.24 * a(t - 1, i, j - 1) - 0.254 * a(t - 1, i, j) - 0.254 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.5 * a(t - 1, i - 1, j) + 0.55 * a(t - 1, i, j) + 0.55 * a(t - 1, i + 1, j) - 0.5 * a(t - 1, i, j - 1) - 0.55 * a(t - 1, i, j) - 0.55 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.6 * a(t - 1, i - 1, j) + 0.65 * a(t - 1, i, j) + 0.65 * a(t - 1, i + 1, j) - 0.6 * a(t - 1, i, j - 1) - 0.65 * a(t - 1, i, j) - 0.65 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.31 * a(t - 1, i - 1, j) + 0.351 * a(t - 1, i, j) + 0.351 * a(t - 1, i + 1, j) - 0.31 * a(t - 1, i, j - 1) - 0.351 * a(t - 1, i, j) - 0.351 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.7 * a(t - 1, i - 1, j) + 0.75 * a(t - 1, i, j) + 0.75 * a(t - 1, i + 1, j) - 0.7 * a(t - 1, i, j - 1) - 0.75 * a(t - 1, i, j) - 0.75 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8 * a(t - 1, i - 1, j) + 0.85 * a(t - 1, i, j) + 0.85 * a(t - 1, i + 1, j) - 0.8 * a(t - 1, i, j - 1) - 0.85 * a(t - 1, i, j) - 0.85 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.41 * a(t - 1, i - 1, j) + 0.45099999999999996 * a(t - 1, i, j) + 0.45099999999999996 * a(t - 1, i + 1, j) - 0.41 * a(t - 1, i, j - 1) - 0.45099999999999996 * a(t - 1, i, j) - 0.45099999999999996 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.22000000000000003 * a(t - 1, i - 1, j) + 0.252 * a(t - 1, i, j) + 0.252 * a(t - 1, i + 1, j) - 0.22000000000000003 * a(t - 1, i, j - 1) - 0.252 * a(t - 1, i, j) - 0.252 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.33999999999999997 * a(t - 1, i - 1, j) + 0.354 * a(t - 1, i, j) + 0.354 * a(t - 1, i + 1, j) - 0.33999999999999997 * a(t - 1, i, j - 1) - 0.354 * a(t - 1, i, j) - 0.354 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.44000000000000006 * a(t - 1, i - 1, j) + 0.454 * a(t - 1, i, j) + 0.454 * a(t - 1, i + 1, j) - 0.44000000000000006 * a(t - 1, i, j - 1) - 0.454 * a(t - 1, i, j) - 0.454 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
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
	static __Pointer_boundary_kernel_12__ * _Pointer_boundary_kernel_12 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_boundary_kernel_12 = NULL;
	#undef pmod_lu
	
	
	
	/* KNOWN */
	class __Pointer_cond_interior_kernel_12__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_interior_kernel_12__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.1 * pt_a_1[l_a_stride_1 * (-1)] + 0.15 * pt_a_1[0] + 0.15 * pt_a_1[l_a_stride_1 * (1)] - 0.1 * pt_a_1[l_a_stride_0 * (-1)] - 0.15 * pt_a_1[0] - 0.15 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.2 * pt_a_1[l_a_stride_1 * (-1)] + 0.25 * pt_a_1[0] + 0.25 * pt_a_1[l_a_stride_1 * (1)] - 0.2 * pt_a_1[l_a_stride_0 * (-1)] - 0.25 * pt_a_1[0] - 0.25 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11000000000000001 * pt_a_1[l_a_stride_1 * (-1)] + 0.151 * pt_a_1[0] + 0.151 * pt_a_1[l_a_stride_1 * (1)] - 0.11000000000000001 * pt_a_1[l_a_stride_0 * (-1)] - 0.151 * pt_a_1[0] - 0.151 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.3 * pt_a_1[l_a_stride_1 * (-1)] + 0.35 * pt_a_1[0] + 0.35 * pt_a_1[l_a_stride_1 * (1)] - 0.3 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] - 0.35 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.4 * pt_a_1[l_a_stride_1 * (-1)] + 0.45 * pt_a_1[0] + 0.45 * pt_a_1[l_a_stride_1 * (1)] - 0.4 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] - 0.45 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21000000000000002 * pt_a_1[l_a_stride_1 * (-1)] + 0.251 * pt_a_1[0] + 0.251 * pt_a_1[l_a_stride_1 * (1)] - 0.21000000000000002 * pt_a_1[l_a_stride_0 * (-1)] - 0.251 * pt_a_1[0] - 0.251 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.12 * pt_a_1[l_a_stride_1 * (-1)] + 0.152 * pt_a_1[0] + 0.152 * pt_a_1[l_a_stride_1 * (1)] - 0.12 * pt_a_1[l_a_stride_0 * (-1)] - 0.152 * pt_a_1[0] - 0.152 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.13999999999999999 * pt_a_1[l_a_stride_1 * (-1)] + 0.154 * pt_a_1[0] + 0.154 * pt_a_1[l_a_stride_1 * (1)] - 0.13999999999999999 * pt_a_1[l_a_stride_0 * (-1)] - 0.154 * pt_a_1[0] - 0.154 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.24 * pt_a_1[l_a_stride_1 * (-1)] + 0.254 * pt_a_1[0] + 0.254 * pt_a_1[l_a_stride_1 * (1)] - 0.24 * pt_a_1[l_a_stride_0 * (-1)] - 0.254 * pt_a_1[0] - 0.254 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.5 * pt_a_1[l_a_stride_1 * (-1)] + 0.55 * pt_a_1[0] + 0.55 * pt_a_1[l_a_stride_1 * (1)] - 0.5 * pt_a_1[l_a_stride_0 * (-1)] - 0.55 * pt_a_1[0] - 0.55 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.6 * pt_a_1[l_a_stride_1 * (-1)] + 0.65 * pt_a_1[0] + 0.65 * pt_a_1[l_a_stride_1 * (1)] - 0.6 * pt_a_1[l_a_stride_0 * (-1)] - 0.65 * pt_a_1[0] - 0.65 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.31 * pt_a_1[l_a_stride_1 * (-1)] + 0.351 * pt_a_1[0] + 0.351 * pt_a_1[l_a_stride_1 * (1)] - 0.31 * pt_a_1[l_a_stride_0 * (-1)] - 0.351 * pt_a_1[0] - 0.351 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.7 * pt_a_1[l_a_stride_1 * (-1)] + 0.75 * pt_a_1[0] + 0.75 * pt_a_1[l_a_stride_1 * (1)] - 0.7 * pt_a_1[l_a_stride_0 * (-1)] - 0.75 * pt_a_1[0] - 0.75 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.8 * pt_a_1[l_a_stride_1 * (-1)] + 0.85 * pt_a_1[0] + 0.85 * pt_a_1[l_a_stride_1 * (1)] - 0.8 * pt_a_1[l_a_stride_0 * (-1)] - 0.85 * pt_a_1[0] - 0.85 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.41 * pt_a_1[l_a_stride_1 * (-1)] + 0.45099999999999996 * pt_a_1[0] + 0.45099999999999996 * pt_a_1[l_a_stride_1 * (1)] - 0.41 * pt_a_1[l_a_stride_0 * (-1)] - 0.45099999999999996 * pt_a_1[0] - 0.45099999999999996 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.22000000000000003 * pt_a_1[l_a_stride_1 * (-1)] + 0.252 * pt_a_1[0] + 0.252 * pt_a_1[l_a_stride_1 * (1)] - 0.22000000000000003 * pt_a_1[l_a_stride_0 * (-1)] - 0.252 * pt_a_1[0] - 0.252 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.33999999999999997 * pt_a_1[l_a_stride_1 * (-1)] + 0.354 * pt_a_1[0] + 0.354 * pt_a_1[l_a_stride_1 * (1)] - 0.33999999999999997 * pt_a_1[l_a_stride_0 * (-1)] - 0.354 * pt_a_1[0] - 0.354 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.44000000000000006 * pt_a_1[l_a_stride_1 * (-1)] + 0.454 * pt_a_1[0] + 0.454 * pt_a_1[l_a_stride_1 * (1)] - 0.44000000000000006 * pt_a_1[l_a_stride_0 * (-1)] - 0.454 * pt_a_1[0] - 0.454 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
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
	static __Pointer_cond_interior_kernel_12__ * _Pointer_cond_interior_kernel_12 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_interior_kernel_12 = NULL;
	
	
	
	
	/* KNOWN */
	class __Pointer_interior_kernel_12__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_interior_kernel_12__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.1 * pt_a_1[l_a_stride_1 * (-1)] + 0.15 * pt_a_1[0] + 0.15 * pt_a_1[l_a_stride_1 * (1)] - 0.1 * pt_a_1[l_a_stride_0 * (-1)] - 0.15 * pt_a_1[0] - 0.15 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.2 * pt_a_1[l_a_stride_1 * (-1)] + 0.25 * pt_a_1[0] + 0.25 * pt_a_1[l_a_stride_1 * (1)] - 0.2 * pt_a_1[l_a_stride_0 * (-1)] - 0.25 * pt_a_1[0] - 0.25 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11000000000000001 * pt_a_1[l_a_stride_1 * (-1)] + 0.151 * pt_a_1[0] + 0.151 * pt_a_1[l_a_stride_1 * (1)] - 0.11000000000000001 * pt_a_1[l_a_stride_0 * (-1)] - 0.151 * pt_a_1[0] - 0.151 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.3 * pt_a_1[l_a_stride_1 * (-1)] + 0.35 * pt_a_1[0] + 0.35 * pt_a_1[l_a_stride_1 * (1)] - 0.3 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] - 0.35 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.4 * pt_a_1[l_a_stride_1 * (-1)] + 0.45 * pt_a_1[0] + 0.45 * pt_a_1[l_a_stride_1 * (1)] - 0.4 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] - 0.45 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21000000000000002 * pt_a_1[l_a_stride_1 * (-1)] + 0.251 * pt_a_1[0] + 0.251 * pt_a_1[l_a_stride_1 * (1)] - 0.21000000000000002 * pt_a_1[l_a_stride_0 * (-1)] - 0.251 * pt_a_1[0] - 0.251 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.12 * pt_a_1[l_a_stride_1 * (-1)] + 0.152 * pt_a_1[0] + 0.152 * pt_a_1[l_a_stride_1 * (1)] - 0.12 * pt_a_1[l_a_stride_0 * (-1)] - 0.152 * pt_a_1[0] - 0.152 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.13999999999999999 * pt_a_1[l_a_stride_1 * (-1)] + 0.154 * pt_a_1[0] + 0.154 * pt_a_1[l_a_stride_1 * (1)] - 0.13999999999999999 * pt_a_1[l_a_stride_0 * (-1)] - 0.154 * pt_a_1[0] - 0.154 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.24 * pt_a_1[l_a_stride_1 * (-1)] + 0.254 * pt_a_1[0] + 0.254 * pt_a_1[l_a_stride_1 * (1)] - 0.24 * pt_a_1[l_a_stride_0 * (-1)] - 0.254 * pt_a_1[0] - 0.254 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.5 * pt_a_1[l_a_stride_1 * (-1)] + 0.55 * pt_a_1[0] + 0.55 * pt_a_1[l_a_stride_1 * (1)] - 0.5 * pt_a_1[l_a_stride_0 * (-1)] - 0.55 * pt_a_1[0] - 0.55 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.6 * pt_a_1[l_a_stride_1 * (-1)] + 0.65 * pt_a_1[0] + 0.65 * pt_a_1[l_a_stride_1 * (1)] - 0.6 * pt_a_1[l_a_stride_0 * (-1)] - 0.65 * pt_a_1[0] - 0.65 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.31 * pt_a_1[l_a_stride_1 * (-1)] + 0.351 * pt_a_1[0] + 0.351 * pt_a_1[l_a_stride_1 * (1)] - 0.31 * pt_a_1[l_a_stride_0 * (-1)] - 0.351 * pt_a_1[0] - 0.351 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.7 * pt_a_1[l_a_stride_1 * (-1)] + 0.75 * pt_a_1[0] + 0.75 * pt_a_1[l_a_stride_1 * (1)] - 0.7 * pt_a_1[l_a_stride_0 * (-1)] - 0.75 * pt_a_1[0] - 0.75 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.8 * pt_a_1[l_a_stride_1 * (-1)] + 0.85 * pt_a_1[0] + 0.85 * pt_a_1[l_a_stride_1 * (1)] - 0.8 * pt_a_1[l_a_stride_0 * (-1)] - 0.85 * pt_a_1[0] - 0.85 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.41 * pt_a_1[l_a_stride_1 * (-1)] + 0.45099999999999996 * pt_a_1[0] + 0.45099999999999996 * pt_a_1[l_a_stride_1 * (1)] - 0.41 * pt_a_1[l_a_stride_0 * (-1)] - 0.45099999999999996 * pt_a_1[0] - 0.45099999999999996 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.22000000000000003 * pt_a_1[l_a_stride_1 * (-1)] + 0.252 * pt_a_1[0] + 0.252 * pt_a_1[l_a_stride_1 * (1)] - 0.22000000000000003 * pt_a_1[l_a_stride_0 * (-1)] - 0.252 * pt_a_1[0] - 0.252 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.33999999999999997 * pt_a_1[l_a_stride_1 * (-1)] + 0.354 * pt_a_1[0] + 0.354 * pt_a_1[l_a_stride_1 * (1)] - 0.33999999999999997 * pt_a_1[l_a_stride_0 * (-1)] - 0.354 * pt_a_1[0] - 0.354 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.44000000000000006 * pt_a_1[l_a_stride_1 * (-1)] + 0.454 * pt_a_1[0] + 0.454 * pt_a_1[l_a_stride_1 * (1)] - 0.44000000000000006 * pt_a_1[l_a_stride_0 * (-1)] - 0.454 * pt_a_1[0] - 0.454 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
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
	static __Pointer_interior_kernel_12__ * _Pointer_interior_kernel_12 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_interior_kernel_12 = NULL;
	
	
	
	/* <101001, 101000>
 */
	auto __POCHOIR_Guard_13__ = [&]  ( int t, int i0, int i1 )  -> bool {
	return ( __g_exclusive_0__ ( t + -1, i0, i1 )  && !__g_exclusive_1__ ( t + -1, i0, i1 )  && __g_inclusive_0__ ( t + -1, i0, i1 )  && !__g_inclusive_1__ ( t + -1, i0, i1 )  && !__g_tiny_inclusive_0__ ( t + -1, i0, i1 )  );
	 };
	static Pochoir_Guard <2> POCHOIR_Guard_13 ( __POCHOIR_Guard_13__ ); 

	/* <101001, 101000>
 */
	
	
	/* 
	tile_3D_checkerboard_0 - PSERIAL;
	tile_1D_checkerboard_2 - PSERIAL;
	tile_1D_checkerboard_5 - PINCLUSIVE;
	__Pochoir_NULL__ - PNULL
	 */
	/* k_0_0, k_0_1, k_0_2, k_0_3, k_0_4, k_0_5, k_0_6, k_0_7, k_2_0, k_2_1, k_5_0, k_5_1, __Pochoir_NULL_ */ 
	/* 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 5, 5, 0 */ 
	/* PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PINCLUSIVE, PINCLUSIVE, PNULL */ 
	/* [0,0,0], [0,0,1], [0,1,0], [0,1,1], [1,0,0], [1,0,1], [1,1,0], [1,1,1], [0], [1], [0], [1], [0] */ 
	/* [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2], [2], [2], [2], [1] */ 
	/* 
	PMTile (sizes = [2,2,2], latest_tile_order = 5), terms = 
		PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 5), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_0
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_1
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_2
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_3
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 2), item = k_2_0
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 5), item = k_5_0
		PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 5), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_4
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_5
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_6
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_7
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 2), item = k_2_1
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 5), item = k_5_1
	 */ 
	static 
	Pochoir_Shape <2> __POCHOIR_Shape__13__ [ ] = {{0, 0, 0}, {-1, 0, -1}, {-1, 0, 1}, {-1, 1, 0}, {-1, -1, 0}, {-1, 0, 0}};
	/* toggle: 2; slopes: [] */
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_cond_boundary_kernel_13__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_boundary_kernel_13__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.1 * a(t - 1, i - 1, j) + 0.15 * a(t - 1, i, j) + 0.15 * a(t - 1, i + 1, j) - 0.1 * a(t - 1, i, j - 1) - 0.15 * a(t - 1, i, j) - 0.15 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.2 * a(t - 1, i - 1, j) + 0.25 * a(t - 1, i, j) + 0.25 * a(t - 1, i + 1, j) - 0.2 * a(t - 1, i, j - 1) - 0.25 * a(t - 1, i, j) - 0.25 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.3 * a(t - 1, i - 1, j) + 0.35 * a(t - 1, i, j) + 0.35 * a(t - 1, i + 1, j) - 0.3 * a(t - 1, i, j - 1) - 0.35 * a(t - 1, i, j) - 0.35 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.4 * a(t - 1, i - 1, j) + 0.45 * a(t - 1, i, j) + 0.45 * a(t - 1, i + 1, j) - 0.4 * a(t - 1, i, j - 1) - 0.45 * a(t - 1, i, j) - 0.45 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.12 * a(t - 1, i - 1, j) + 0.152 * a(t - 1, i, j) + 0.152 * a(t - 1, i + 1, j) - 0.12 * a(t - 1, i, j - 1) - 0.152 * a(t - 1, i, j) - 0.152 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.15 * a(t - 1, i - 1, j) + 0.155 * a(t - 1, i, j) + 0.155 * a(t - 1, i + 1, j) - 0.15 * a(t - 1, i, j - 1) - 0.155 * a(t - 1, i, j) - 0.155 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.5 * a(t - 1, i - 1, j) + 0.55 * a(t - 1, i, j) + 0.55 * a(t - 1, i + 1, j) - 0.5 * a(t - 1, i, j - 1) - 0.55 * a(t - 1, i, j) - 0.55 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.6 * a(t - 1, i - 1, j) + 0.65 * a(t - 1, i, j) + 0.65 * a(t - 1, i + 1, j) - 0.6 * a(t - 1, i, j - 1) - 0.65 * a(t - 1, i, j) - 0.65 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.7 * a(t - 1, i - 1, j) + 0.75 * a(t - 1, i, j) + 0.75 * a(t - 1, i + 1, j) - 0.7 * a(t - 1, i, j - 1) - 0.75 * a(t - 1, i, j) - 0.75 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8 * a(t - 1, i - 1, j) + 0.85 * a(t - 1, i, j) + 0.85 * a(t - 1, i + 1, j) - 0.8 * a(t - 1, i, j - 1) - 0.85 * a(t - 1, i, j) - 0.85 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.22000000000000003 * a(t - 1, i - 1, j) + 0.252 * a(t - 1, i, j) + 0.252 * a(t - 1, i + 1, j) - 0.22000000000000003 * a(t - 1, i, j - 1) - 0.252 * a(t - 1, i, j) - 0.252 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.25 * a(t - 1, i - 1, j) + 0.255 * a(t - 1, i, j) + 0.255 * a(t - 1, i + 1, j) - 0.25 * a(t - 1, i, j - 1) - 0.255 * a(t - 1, i, j) - 0.255 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
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
	static __Pointer_cond_boundary_kernel_13__ * _Pointer_cond_boundary_kernel_13 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_boundary_kernel_13 = NULL;
	#undef pmod_lu
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_boundary_kernel_13__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_boundary_kernel_13__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.1 * a(t - 1, i - 1, j) + 0.15 * a(t - 1, i, j) + 0.15 * a(t - 1, i + 1, j) - 0.1 * a(t - 1, i, j - 1) - 0.15 * a(t - 1, i, j) - 0.15 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.2 * a(t - 1, i - 1, j) + 0.25 * a(t - 1, i, j) + 0.25 * a(t - 1, i + 1, j) - 0.2 * a(t - 1, i, j - 1) - 0.25 * a(t - 1, i, j) - 0.25 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.3 * a(t - 1, i - 1, j) + 0.35 * a(t - 1, i, j) + 0.35 * a(t - 1, i + 1, j) - 0.3 * a(t - 1, i, j - 1) - 0.35 * a(t - 1, i, j) - 0.35 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.4 * a(t - 1, i - 1, j) + 0.45 * a(t - 1, i, j) + 0.45 * a(t - 1, i + 1, j) - 0.4 * a(t - 1, i, j - 1) - 0.45 * a(t - 1, i, j) - 0.45 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.12 * a(t - 1, i - 1, j) + 0.152 * a(t - 1, i, j) + 0.152 * a(t - 1, i + 1, j) - 0.12 * a(t - 1, i, j - 1) - 0.152 * a(t - 1, i, j) - 0.152 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.15 * a(t - 1, i - 1, j) + 0.155 * a(t - 1, i, j) + 0.155 * a(t - 1, i + 1, j) - 0.15 * a(t - 1, i, j - 1) - 0.155 * a(t - 1, i, j) - 0.155 * a(t - 1, i, j + 1);
	
	
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.5 * a(t - 1, i - 1, j) + 0.55 * a(t - 1, i, j) + 0.55 * a(t - 1, i + 1, j) - 0.5 * a(t - 1, i, j - 1) - 0.55 * a(t - 1, i, j) - 0.55 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.6 * a(t - 1, i - 1, j) + 0.65 * a(t - 1, i, j) + 0.65 * a(t - 1, i + 1, j) - 0.6 * a(t - 1, i, j - 1) - 0.65 * a(t - 1, i, j) - 0.65 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.7 * a(t - 1, i - 1, j) + 0.75 * a(t - 1, i, j) + 0.75 * a(t - 1, i + 1, j) - 0.7 * a(t - 1, i, j - 1) - 0.75 * a(t - 1, i, j) - 0.75 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8 * a(t - 1, i - 1, j) + 0.85 * a(t - 1, i, j) + 0.85 * a(t - 1, i + 1, j) - 0.8 * a(t - 1, i, j - 1) - 0.85 * a(t - 1, i, j) - 0.85 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.22000000000000003 * a(t - 1, i - 1, j) + 0.252 * a(t - 1, i, j) + 0.252 * a(t - 1, i + 1, j) - 0.22000000000000003 * a(t - 1, i, j - 1) - 0.252 * a(t - 1, i, j) - 0.252 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.25 * a(t - 1, i - 1, j) + 0.255 * a(t - 1, i, j) + 0.255 * a(t - 1, i + 1, j) - 0.25 * a(t - 1, i, j - 1) - 0.255 * a(t - 1, i, j) - 0.255 * a(t - 1, i, j + 1);
	
	
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
	static __Pointer_boundary_kernel_13__ * _Pointer_boundary_kernel_13 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_boundary_kernel_13 = NULL;
	#undef pmod_lu
	
	
	
	/* KNOWN */
	class __Pointer_cond_interior_kernel_13__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_interior_kernel_13__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.1 * pt_a_1[l_a_stride_1 * (-1)] + 0.15 * pt_a_1[0] + 0.15 * pt_a_1[l_a_stride_1 * (1)] - 0.1 * pt_a_1[l_a_stride_0 * (-1)] - 0.15 * pt_a_1[0] - 0.15 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.2 * pt_a_1[l_a_stride_1 * (-1)] + 0.25 * pt_a_1[0] + 0.25 * pt_a_1[l_a_stride_1 * (1)] - 0.2 * pt_a_1[l_a_stride_0 * (-1)] - 0.25 * pt_a_1[0] - 0.25 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.3 * pt_a_1[l_a_stride_1 * (-1)] + 0.35 * pt_a_1[0] + 0.35 * pt_a_1[l_a_stride_1 * (1)] - 0.3 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] - 0.35 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.4 * pt_a_1[l_a_stride_1 * (-1)] + 0.45 * pt_a_1[0] + 0.45 * pt_a_1[l_a_stride_1 * (1)] - 0.4 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] - 0.45 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.12 * pt_a_1[l_a_stride_1 * (-1)] + 0.152 * pt_a_1[0] + 0.152 * pt_a_1[l_a_stride_1 * (1)] - 0.12 * pt_a_1[l_a_stride_0 * (-1)] - 0.152 * pt_a_1[0] - 0.152 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.15 * pt_a_1[l_a_stride_1 * (-1)] + 0.155 * pt_a_1[0] + 0.155 * pt_a_1[l_a_stride_1 * (1)] - 0.15 * pt_a_1[l_a_stride_0 * (-1)] - 0.155 * pt_a_1[0] - 0.155 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.5 * pt_a_1[l_a_stride_1 * (-1)] + 0.55 * pt_a_1[0] + 0.55 * pt_a_1[l_a_stride_1 * (1)] - 0.5 * pt_a_1[l_a_stride_0 * (-1)] - 0.55 * pt_a_1[0] - 0.55 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.6 * pt_a_1[l_a_stride_1 * (-1)] + 0.65 * pt_a_1[0] + 0.65 * pt_a_1[l_a_stride_1 * (1)] - 0.6 * pt_a_1[l_a_stride_0 * (-1)] - 0.65 * pt_a_1[0] - 0.65 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.7 * pt_a_1[l_a_stride_1 * (-1)] + 0.75 * pt_a_1[0] + 0.75 * pt_a_1[l_a_stride_1 * (1)] - 0.7 * pt_a_1[l_a_stride_0 * (-1)] - 0.75 * pt_a_1[0] - 0.75 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.8 * pt_a_1[l_a_stride_1 * (-1)] + 0.85 * pt_a_1[0] + 0.85 * pt_a_1[l_a_stride_1 * (1)] - 0.8 * pt_a_1[l_a_stride_0 * (-1)] - 0.85 * pt_a_1[0] - 0.85 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.22000000000000003 * pt_a_1[l_a_stride_1 * (-1)] + 0.252 * pt_a_1[0] + 0.252 * pt_a_1[l_a_stride_1 * (1)] - 0.22000000000000003 * pt_a_1[l_a_stride_0 * (-1)] - 0.252 * pt_a_1[0] - 0.252 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.25 * pt_a_1[l_a_stride_1 * (-1)] + 0.255 * pt_a_1[0] + 0.255 * pt_a_1[l_a_stride_1 * (1)] - 0.25 * pt_a_1[l_a_stride_0 * (-1)] - 0.255 * pt_a_1[0] - 0.255 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
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
	static __Pointer_cond_interior_kernel_13__ * _Pointer_cond_interior_kernel_13 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_interior_kernel_13 = NULL;
	
	
	
	
	/* KNOWN */
	class __Pointer_interior_kernel_13__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_interior_kernel_13__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.1 * pt_a_1[l_a_stride_1 * (-1)] + 0.15 * pt_a_1[0] + 0.15 * pt_a_1[l_a_stride_1 * (1)] - 0.1 * pt_a_1[l_a_stride_0 * (-1)] - 0.15 * pt_a_1[0] - 0.15 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.2 * pt_a_1[l_a_stride_1 * (-1)] + 0.25 * pt_a_1[0] + 0.25 * pt_a_1[l_a_stride_1 * (1)] - 0.2 * pt_a_1[l_a_stride_0 * (-1)] - 0.25 * pt_a_1[0] - 0.25 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.3 * pt_a_1[l_a_stride_1 * (-1)] + 0.35 * pt_a_1[0] + 0.35 * pt_a_1[l_a_stride_1 * (1)] - 0.3 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] - 0.35 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.4 * pt_a_1[l_a_stride_1 * (-1)] + 0.45 * pt_a_1[0] + 0.45 * pt_a_1[l_a_stride_1 * (1)] - 0.4 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] - 0.45 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.12 * pt_a_1[l_a_stride_1 * (-1)] + 0.152 * pt_a_1[0] + 0.152 * pt_a_1[l_a_stride_1 * (1)] - 0.12 * pt_a_1[l_a_stride_0 * (-1)] - 0.152 * pt_a_1[0] - 0.152 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.15 * pt_a_1[l_a_stride_1 * (-1)] + 0.155 * pt_a_1[0] + 0.155 * pt_a_1[l_a_stride_1 * (1)] - 0.15 * pt_a_1[l_a_stride_0 * (-1)] - 0.155 * pt_a_1[0] - 0.155 * pt_a_1[l_a_stride_0 * (1)];
	
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.5 * pt_a_1[l_a_stride_1 * (-1)] + 0.55 * pt_a_1[0] + 0.55 * pt_a_1[l_a_stride_1 * (1)] - 0.5 * pt_a_1[l_a_stride_0 * (-1)] - 0.55 * pt_a_1[0] - 0.55 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.6 * pt_a_1[l_a_stride_1 * (-1)] + 0.65 * pt_a_1[0] + 0.65 * pt_a_1[l_a_stride_1 * (1)] - 0.6 * pt_a_1[l_a_stride_0 * (-1)] - 0.65 * pt_a_1[0] - 0.65 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.7 * pt_a_1[l_a_stride_1 * (-1)] + 0.75 * pt_a_1[0] + 0.75 * pt_a_1[l_a_stride_1 * (1)] - 0.7 * pt_a_1[l_a_stride_0 * (-1)] - 0.75 * pt_a_1[0] - 0.75 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.8 * pt_a_1[l_a_stride_1 * (-1)] + 0.85 * pt_a_1[0] + 0.85 * pt_a_1[l_a_stride_1 * (1)] - 0.8 * pt_a_1[l_a_stride_0 * (-1)] - 0.85 * pt_a_1[0] - 0.85 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	}
	
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.22000000000000003 * pt_a_1[l_a_stride_1 * (-1)] + 0.252 * pt_a_1[0] + 0.252 * pt_a_1[l_a_stride_1 * (1)] - 0.22000000000000003 * pt_a_1[l_a_stride_0 * (-1)] - 0.252 * pt_a_1[0] - 0.252 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.25 * pt_a_1[l_a_stride_1 * (-1)] + 0.255 * pt_a_1[0] + 0.255 * pt_a_1[l_a_stride_1 * (1)] - 0.25 * pt_a_1[l_a_stride_0 * (-1)] - 0.255 * pt_a_1[0] - 0.255 * pt_a_1[l_a_stride_0 * (1)];
	
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
	static __Pointer_interior_kernel_13__ * _Pointer_interior_kernel_13 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_interior_kernel_13 = NULL;
	
	
	
	/* <110000, 000000>
 */
	auto __POCHOIR_Guard_14__ = [&]  ( int t, int i0, int i1 )  -> bool {
	return ( !__g_inclusive_0__ ( t + -1, i0, i1 )  && !__g_inclusive_1__ ( t + -1, i0, i1 )  && !__g_tiny_inclusive_0__ ( t + -1, i0, i1 )  && !__g_tiny_inclusive_1__ ( t + -1, i0, i1 )  );
	 };
	static Pochoir_Guard <2> POCHOIR_Guard_14 ( __POCHOIR_Guard_14__ ); 

	/* <110000, 000000>
 */
	
	
	/* 
	tile_3D_checkerboard_0 - PINCLUSIVE;
	tile_2D_checkerboard_1 - PINCLUSIVE;
	__Pochoir_NULL__ - PNULL
	 */
	/* k_0_0, k_0_1, k_0_2, k_0_3, k_0_4, k_0_5, k_0_6, k_0_7, k_1_0, k_1_1, k_1_2, k_1_3, __Pochoir_NULL_ */ 
	/* 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0 */ 
	/* PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PNULL */ 
	/* [0,0,0], [0,0,1], [0,1,0], [0,1,1], [1,0,0], [1,0,1], [1,1,0], [1,1,1], [0,0], [0,1], [1,0], [1,1], [0] */ 
	/* [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2], [2,2], [2,2], [2,2], [1] */ 
	/* 
	PMTile (sizes = [2,2,2], latest_tile_order = 1), terms = 
		PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 1), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 1), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_0
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_1
				PMTileTerm (indices = [], sizes = [], latest_tile_order = 1), item = k_1_0
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 1), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_2
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_3
				PMTileTerm (indices = [], sizes = [], latest_tile_order = 1), item = k_1_1
		PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 1), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 1), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_4
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_5
				PMTileTerm (indices = [], sizes = [], latest_tile_order = 1), item = k_1_2
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 1), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_6
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_7
				PMTileTerm (indices = [], sizes = [], latest_tile_order = 1), item = k_1_3
	 */ 
	static 
	Pochoir_Shape <2> __POCHOIR_Shape__14__ [ ] = {{0, 0, 0}, {-1, 0, -1}, {-1, 0, 1}, {-1, 1, 0}, {-1, -1, 0}, {-1, 0, 0}};
	/* toggle: 2; slopes: [] */
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_cond_boundary_kernel_14__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_boundary_kernel_14__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.1 * a(t - 1, i - 1, j) + 0.15 * a(t - 1, i, j) + 0.15 * a(t - 1, i + 1, j) - 0.1 * a(t - 1, i, j - 1) - 0.15 * a(t - 1, i, j) - 0.15 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.2 * a(t - 1, i - 1, j) + 0.25 * a(t - 1, i, j) + 0.25 * a(t - 1, i + 1, j) - 0.2 * a(t - 1, i, j - 1) - 0.25 * a(t - 1, i, j) - 0.25 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.11000000000000001 * a(t - 1, i - 1, j) + 0.151 * a(t - 1, i, j) + 0.151 * a(t - 1, i + 1, j) - 0.11000000000000001 * a(t - 1, i, j - 1) - 0.151 * a(t - 1, i, j) - 0.151 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.3 * a(t - 1, i - 1, j) + 0.35 * a(t - 1, i, j) + 0.35 * a(t - 1, i + 1, j) - 0.3 * a(t - 1, i, j - 1) - 0.35 * a(t - 1, i, j) - 0.35 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.4 * a(t - 1, i - 1, j) + 0.45 * a(t - 1, i, j) + 0.45 * a(t - 1, i + 1, j) - 0.4 * a(t - 1, i, j - 1) - 0.45 * a(t - 1, i, j) - 0.45 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.21000000000000002 * a(t - 1, i - 1, j) + 0.251 * a(t - 1, i, j) + 0.251 * a(t - 1, i + 1, j) - 0.21000000000000002 * a(t - 1, i, j - 1) - 0.251 * a(t - 1, i, j) - 0.251 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.5 * a(t - 1, i - 1, j) + 0.55 * a(t - 1, i, j) + 0.55 * a(t - 1, i + 1, j) - 0.5 * a(t - 1, i, j - 1) - 0.55 * a(t - 1, i, j) - 0.55 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.6 * a(t - 1, i - 1, j) + 0.65 * a(t - 1, i, j) + 0.65 * a(t - 1, i + 1, j) - 0.6 * a(t - 1, i, j - 1) - 0.65 * a(t - 1, i, j) - 0.65 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.31 * a(t - 1, i - 1, j) + 0.351 * a(t - 1, i, j) + 0.351 * a(t - 1, i + 1, j) - 0.31 * a(t - 1, i, j - 1) - 0.351 * a(t - 1, i, j) - 0.351 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.7 * a(t - 1, i - 1, j) + 0.75 * a(t - 1, i, j) + 0.75 * a(t - 1, i + 1, j) - 0.7 * a(t - 1, i, j - 1) - 0.75 * a(t - 1, i, j) - 0.75 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8 * a(t - 1, i - 1, j) + 0.85 * a(t - 1, i, j) + 0.85 * a(t - 1, i + 1, j) - 0.8 * a(t - 1, i, j - 1) - 0.85 * a(t - 1, i, j) - 0.85 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.41 * a(t - 1, i - 1, j) + 0.45099999999999996 * a(t - 1, i, j) + 0.45099999999999996 * a(t - 1, i + 1, j) - 0.41 * a(t - 1, i, j - 1) - 0.45099999999999996 * a(t - 1, i, j) - 0.45099999999999996 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
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
	static __Pointer_cond_boundary_kernel_14__ * _Pointer_cond_boundary_kernel_14 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_boundary_kernel_14 = NULL;
	#undef pmod_lu
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_boundary_kernel_14__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_boundary_kernel_14__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.1 * a(t - 1, i - 1, j) + 0.15 * a(t - 1, i, j) + 0.15 * a(t - 1, i + 1, j) - 0.1 * a(t - 1, i, j - 1) - 0.15 * a(t - 1, i, j) - 0.15 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.2 * a(t - 1, i - 1, j) + 0.25 * a(t - 1, i, j) + 0.25 * a(t - 1, i + 1, j) - 0.2 * a(t - 1, i, j - 1) - 0.25 * a(t - 1, i, j) - 0.25 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.11000000000000001 * a(t - 1, i - 1, j) + 0.151 * a(t - 1, i, j) + 0.151 * a(t - 1, i + 1, j) - 0.11000000000000001 * a(t - 1, i, j - 1) - 0.151 * a(t - 1, i, j) - 0.151 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.3 * a(t - 1, i - 1, j) + 0.35 * a(t - 1, i, j) + 0.35 * a(t - 1, i + 1, j) - 0.3 * a(t - 1, i, j - 1) - 0.35 * a(t - 1, i, j) - 0.35 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.4 * a(t - 1, i - 1, j) + 0.45 * a(t - 1, i, j) + 0.45 * a(t - 1, i + 1, j) - 0.4 * a(t - 1, i, j - 1) - 0.45 * a(t - 1, i, j) - 0.45 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.21000000000000002 * a(t - 1, i - 1, j) + 0.251 * a(t - 1, i, j) + 0.251 * a(t - 1, i + 1, j) - 0.21000000000000002 * a(t - 1, i, j - 1) - 0.251 * a(t - 1, i, j) - 0.251 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.5 * a(t - 1, i - 1, j) + 0.55 * a(t - 1, i, j) + 0.55 * a(t - 1, i + 1, j) - 0.5 * a(t - 1, i, j - 1) - 0.55 * a(t - 1, i, j) - 0.55 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.6 * a(t - 1, i - 1, j) + 0.65 * a(t - 1, i, j) + 0.65 * a(t - 1, i + 1, j) - 0.6 * a(t - 1, i, j - 1) - 0.65 * a(t - 1, i, j) - 0.65 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.31 * a(t - 1, i - 1, j) + 0.351 * a(t - 1, i, j) + 0.351 * a(t - 1, i + 1, j) - 0.31 * a(t - 1, i, j - 1) - 0.351 * a(t - 1, i, j) - 0.351 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.7 * a(t - 1, i - 1, j) + 0.75 * a(t - 1, i, j) + 0.75 * a(t - 1, i + 1, j) - 0.7 * a(t - 1, i, j - 1) - 0.75 * a(t - 1, i, j) - 0.75 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8 * a(t - 1, i - 1, j) + 0.85 * a(t - 1, i, j) + 0.85 * a(t - 1, i + 1, j) - 0.8 * a(t - 1, i, j - 1) - 0.85 * a(t - 1, i, j) - 0.85 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.41 * a(t - 1, i - 1, j) + 0.45099999999999996 * a(t - 1, i, j) + 0.45099999999999996 * a(t - 1, i + 1, j) - 0.41 * a(t - 1, i, j - 1) - 0.45099999999999996 * a(t - 1, i, j) - 0.45099999999999996 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
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
	static __Pointer_boundary_kernel_14__ * _Pointer_boundary_kernel_14 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_boundary_kernel_14 = NULL;
	#undef pmod_lu
	
	
	
	/* KNOWN */
	class __Pointer_cond_interior_kernel_14__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_interior_kernel_14__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.1 * pt_a_1[l_a_stride_1 * (-1)] + 0.15 * pt_a_1[0] + 0.15 * pt_a_1[l_a_stride_1 * (1)] - 0.1 * pt_a_1[l_a_stride_0 * (-1)] - 0.15 * pt_a_1[0] - 0.15 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.2 * pt_a_1[l_a_stride_1 * (-1)] + 0.25 * pt_a_1[0] + 0.25 * pt_a_1[l_a_stride_1 * (1)] - 0.2 * pt_a_1[l_a_stride_0 * (-1)] - 0.25 * pt_a_1[0] - 0.25 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11000000000000001 * pt_a_1[l_a_stride_1 * (-1)] + 0.151 * pt_a_1[0] + 0.151 * pt_a_1[l_a_stride_1 * (1)] - 0.11000000000000001 * pt_a_1[l_a_stride_0 * (-1)] - 0.151 * pt_a_1[0] - 0.151 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.3 * pt_a_1[l_a_stride_1 * (-1)] + 0.35 * pt_a_1[0] + 0.35 * pt_a_1[l_a_stride_1 * (1)] - 0.3 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] - 0.35 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.4 * pt_a_1[l_a_stride_1 * (-1)] + 0.45 * pt_a_1[0] + 0.45 * pt_a_1[l_a_stride_1 * (1)] - 0.4 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] - 0.45 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21000000000000002 * pt_a_1[l_a_stride_1 * (-1)] + 0.251 * pt_a_1[0] + 0.251 * pt_a_1[l_a_stride_1 * (1)] - 0.21000000000000002 * pt_a_1[l_a_stride_0 * (-1)] - 0.251 * pt_a_1[0] - 0.251 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.5 * pt_a_1[l_a_stride_1 * (-1)] + 0.55 * pt_a_1[0] + 0.55 * pt_a_1[l_a_stride_1 * (1)] - 0.5 * pt_a_1[l_a_stride_0 * (-1)] - 0.55 * pt_a_1[0] - 0.55 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.6 * pt_a_1[l_a_stride_1 * (-1)] + 0.65 * pt_a_1[0] + 0.65 * pt_a_1[l_a_stride_1 * (1)] - 0.6 * pt_a_1[l_a_stride_0 * (-1)] - 0.65 * pt_a_1[0] - 0.65 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.31 * pt_a_1[l_a_stride_1 * (-1)] + 0.351 * pt_a_1[0] + 0.351 * pt_a_1[l_a_stride_1 * (1)] - 0.31 * pt_a_1[l_a_stride_0 * (-1)] - 0.351 * pt_a_1[0] - 0.351 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.7 * pt_a_1[l_a_stride_1 * (-1)] + 0.75 * pt_a_1[0] + 0.75 * pt_a_1[l_a_stride_1 * (1)] - 0.7 * pt_a_1[l_a_stride_0 * (-1)] - 0.75 * pt_a_1[0] - 0.75 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.8 * pt_a_1[l_a_stride_1 * (-1)] + 0.85 * pt_a_1[0] + 0.85 * pt_a_1[l_a_stride_1 * (1)] - 0.8 * pt_a_1[l_a_stride_0 * (-1)] - 0.85 * pt_a_1[0] - 0.85 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.41 * pt_a_1[l_a_stride_1 * (-1)] + 0.45099999999999996 * pt_a_1[0] + 0.45099999999999996 * pt_a_1[l_a_stride_1 * (1)] - 0.41 * pt_a_1[l_a_stride_0 * (-1)] - 0.45099999999999996 * pt_a_1[0] - 0.45099999999999996 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
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
	static __Pointer_cond_interior_kernel_14__ * _Pointer_cond_interior_kernel_14 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_interior_kernel_14 = NULL;
	
	
	
	
	/* KNOWN */
	class __Pointer_interior_kernel_14__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_interior_kernel_14__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.1 * pt_a_1[l_a_stride_1 * (-1)] + 0.15 * pt_a_1[0] + 0.15 * pt_a_1[l_a_stride_1 * (1)] - 0.1 * pt_a_1[l_a_stride_0 * (-1)] - 0.15 * pt_a_1[0] - 0.15 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.2 * pt_a_1[l_a_stride_1 * (-1)] + 0.25 * pt_a_1[0] + 0.25 * pt_a_1[l_a_stride_1 * (1)] - 0.2 * pt_a_1[l_a_stride_0 * (-1)] - 0.25 * pt_a_1[0] - 0.25 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11000000000000001 * pt_a_1[l_a_stride_1 * (-1)] + 0.151 * pt_a_1[0] + 0.151 * pt_a_1[l_a_stride_1 * (1)] - 0.11000000000000001 * pt_a_1[l_a_stride_0 * (-1)] - 0.151 * pt_a_1[0] - 0.151 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.3 * pt_a_1[l_a_stride_1 * (-1)] + 0.35 * pt_a_1[0] + 0.35 * pt_a_1[l_a_stride_1 * (1)] - 0.3 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] - 0.35 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.4 * pt_a_1[l_a_stride_1 * (-1)] + 0.45 * pt_a_1[0] + 0.45 * pt_a_1[l_a_stride_1 * (1)] - 0.4 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] - 0.45 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21000000000000002 * pt_a_1[l_a_stride_1 * (-1)] + 0.251 * pt_a_1[0] + 0.251 * pt_a_1[l_a_stride_1 * (1)] - 0.21000000000000002 * pt_a_1[l_a_stride_0 * (-1)] - 0.251 * pt_a_1[0] - 0.251 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.5 * pt_a_1[l_a_stride_1 * (-1)] + 0.55 * pt_a_1[0] + 0.55 * pt_a_1[l_a_stride_1 * (1)] - 0.5 * pt_a_1[l_a_stride_0 * (-1)] - 0.55 * pt_a_1[0] - 0.55 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.6 * pt_a_1[l_a_stride_1 * (-1)] + 0.65 * pt_a_1[0] + 0.65 * pt_a_1[l_a_stride_1 * (1)] - 0.6 * pt_a_1[l_a_stride_0 * (-1)] - 0.65 * pt_a_1[0] - 0.65 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.31 * pt_a_1[l_a_stride_1 * (-1)] + 0.351 * pt_a_1[0] + 0.351 * pt_a_1[l_a_stride_1 * (1)] - 0.31 * pt_a_1[l_a_stride_0 * (-1)] - 0.351 * pt_a_1[0] - 0.351 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.7 * pt_a_1[l_a_stride_1 * (-1)] + 0.75 * pt_a_1[0] + 0.75 * pt_a_1[l_a_stride_1 * (1)] - 0.7 * pt_a_1[l_a_stride_0 * (-1)] - 0.75 * pt_a_1[0] - 0.75 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.8 * pt_a_1[l_a_stride_1 * (-1)] + 0.85 * pt_a_1[0] + 0.85 * pt_a_1[l_a_stride_1 * (1)] - 0.8 * pt_a_1[l_a_stride_0 * (-1)] - 0.85 * pt_a_1[0] - 0.85 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.41 * pt_a_1[l_a_stride_1 * (-1)] + 0.45099999999999996 * pt_a_1[0] + 0.45099999999999996 * pt_a_1[l_a_stride_1 * (1)] - 0.41 * pt_a_1[l_a_stride_0 * (-1)] - 0.45099999999999996 * pt_a_1[0] - 0.45099999999999996 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
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
	static __Pointer_interior_kernel_14__ * _Pointer_interior_kernel_14 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_interior_kernel_14 = NULL;
	
	
	
	/* <111111, 000000>
 */
	auto __POCHOIR_Guard_15__ = [&]  ( int t, int i0, int i1 )  -> bool {
	return ( true );
	 };
	static Pochoir_Guard <2> POCHOIR_Guard_15 ( __POCHOIR_Guard_15__ ); 

	/* <111111, 000000>
 */
	
	
	/* 
	tile_3D_checkerboard_0 - PINCLUSIVE;
	tile_2D_checkerboard_1 - PINCLUSIVE;
	tile_1D_checkerboard_2 - PINCLUSIVE;
	tile_3D_checkerboard_3 - PINCLUSIVE;
	tile_2D_checkerboard_4 - PINCLUSIVE;
	tile_1D_checkerboard_5 - PINCLUSIVE;
	__Pochoir_NULL__ - PNULL
	 */
	/* k_0_0, k_0_1, k_0_2, k_0_3, k_0_4, k_0_5, k_0_6, k_0_7, k_1_0, k_1_1, k_1_2, k_1_3, k_2_0, k_2_1, k_3_0, k_3_1, k_3_2, k_3_3, k_3_4, k_3_5, k_3_6, k_3_7, k_4_0, k_4_1, k_4_2, k_4_3, k_5_0, k_5_1, __Pochoir_NULL_ */ 
	/* 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 0 */ 
	/* PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PNULL */ 
	/* [0,0,0], [0,0,1], [0,1,0], [0,1,1], [1,0,0], [1,0,1], [1,1,0], [1,1,1], [0,0], [0,1], [1,0], [1,1], [0], [1], [0,0,0], [0,0,1], [0,1,0], [0,1,1], [1,0,0], [1,0,1], [1,1,0], [1,1,1], [0,0], [0,1], [1,0], [1,1], [0], [1], [0] */ 
	/* [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2], [2,2], [2,2], [2,2], [2], [2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2,2], [2,2], [2,2], [2,2], [2,2], [2], [2], [1] */ 
	/* 
	PMTile (sizes = [2,2,2], latest_tile_order = 5), terms = 
		PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 5), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 1), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_0
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_1
				PMTileTerm (indices = [], sizes = [], latest_tile_order = 1), item = k_1_0
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 1), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_2
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_3
				PMTileTerm (indices = [], sizes = [], latest_tile_order = 1), item = k_1_1
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 2), item = k_2_0
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 4), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = k_3_0
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = k_3_1
				PMTileTerm (indices = [], sizes = [], latest_tile_order = 4), item = k_4_0
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 4), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = k_3_2
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = k_3_3
				PMTileTerm (indices = [], sizes = [], latest_tile_order = 4), item = k_4_1
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 5), item = k_5_0
		PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 5), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 1), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_4
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_5
				PMTileTerm (indices = [], sizes = [], latest_tile_order = 1), item = k_1_2
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 1), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_0_6
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_0_7
				PMTileTerm (indices = [], sizes = [], latest_tile_order = 1), item = k_1_3
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 2), item = k_2_1
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 4), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = k_3_4
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = k_3_5
				PMTileTerm (indices = [], sizes = [], latest_tile_order = 4), item = k_4_2
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 4), item = 
				PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = k_3_6
				PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = k_3_7
				PMTileTerm (indices = [], sizes = [], latest_tile_order = 4), item = k_4_3
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 5), item = k_5_1
	 */ 
	static 
	Pochoir_Shape <2> __POCHOIR_Shape__15__ [ ] = {{0, 0, 0}, {-1, 0, -1}, {-1, 0, 1}, {-1, 1, 0}, {-1, -1, 0}, {-1, 0, 0}};
	/* toggle: 2; slopes: [] */
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_cond_boundary_kernel_15__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_boundary_kernel_15__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.1 * a(t - 1, i - 1, j) + 0.15 * a(t - 1, i, j) + 0.15 * a(t - 1, i + 1, j) - 0.1 * a(t - 1, i, j - 1) - 0.15 * a(t - 1, i, j) - 0.15 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.2 * a(t - 1, i - 1, j) + 0.25 * a(t - 1, i, j) + 0.25 * a(t - 1, i + 1, j) - 0.2 * a(t - 1, i, j - 1) - 0.25 * a(t - 1, i, j) - 0.25 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.11000000000000001 * a(t - 1, i - 1, j) + 0.151 * a(t - 1, i, j) + 0.151 * a(t - 1, i + 1, j) - 0.11000000000000001 * a(t - 1, i, j - 1) - 0.151 * a(t - 1, i, j) - 0.151 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.3 * a(t - 1, i - 1, j) + 0.35 * a(t - 1, i, j) + 0.35 * a(t - 1, i + 1, j) - 0.3 * a(t - 1, i, j - 1) - 0.35 * a(t - 1, i, j) - 0.35 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.4 * a(t - 1, i - 1, j) + 0.45 * a(t - 1, i, j) + 0.45 * a(t - 1, i + 1, j) - 0.4 * a(t - 1, i, j - 1) - 0.45 * a(t - 1, i, j) - 0.45 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.21000000000000002 * a(t - 1, i - 1, j) + 0.251 * a(t - 1, i, j) + 0.251 * a(t - 1, i + 1, j) - 0.21000000000000002 * a(t - 1, i, j - 1) - 0.251 * a(t - 1, i, j) - 0.251 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.12 * a(t - 1, i - 1, j) + 0.152 * a(t - 1, i, j) + 0.152 * a(t - 1, i + 1, j) - 0.12 * a(t - 1, i, j - 1) - 0.152 * a(t - 1, i, j) - 0.152 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.13 * a(t - 1, i - 1, j) + 0.153 * a(t - 1, i, j) + 0.153 * a(t - 1, i + 1, j) - 0.13 * a(t - 1, i, j - 1) - 0.153 * a(t - 1, i, j) - 0.153 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.22999999999999998 * a(t - 1, i - 1, j) + 0.253 * a(t - 1, i, j) + 0.253 * a(t - 1, i + 1, j) - 0.22999999999999998 * a(t - 1, i, j - 1) - 0.253 * a(t - 1, i, j) - 0.253 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.13999999999999999 * a(t - 1, i - 1, j) + 0.154 * a(t - 1, i, j) + 0.154 * a(t - 1, i + 1, j) - 0.13999999999999999 * a(t - 1, i, j - 1) - 0.154 * a(t - 1, i, j) - 0.154 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.32999999999999996 * a(t - 1, i - 1, j) + 0.35300000000000004 * a(t - 1, i, j) + 0.35300000000000004 * a(t - 1, i + 1, j) - 0.32999999999999996 * a(t - 1, i, j - 1) - 0.35300000000000004 * a(t - 1, i, j) - 0.35300000000000004 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.43 * a(t - 1, i - 1, j) + 0.453 * a(t - 1, i, j) + 0.453 * a(t - 1, i + 1, j) - 0.43 * a(t - 1, i, j - 1) - 0.453 * a(t - 1, i, j) - 0.453 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.24 * a(t - 1, i - 1, j) + 0.254 * a(t - 1, i, j) + 0.254 * a(t - 1, i + 1, j) - 0.24 * a(t - 1, i, j - 1) - 0.254 * a(t - 1, i, j) - 0.254 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.15 * a(t - 1, i - 1, j) + 0.155 * a(t - 1, i, j) + 0.155 * a(t - 1, i + 1, j) - 0.15 * a(t - 1, i, j - 1) - 0.155 * a(t - 1, i, j) - 0.155 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.5 * a(t - 1, i - 1, j) + 0.55 * a(t - 1, i, j) + 0.55 * a(t - 1, i + 1, j) - 0.5 * a(t - 1, i, j - 1) - 0.55 * a(t - 1, i, j) - 0.55 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.6 * a(t - 1, i - 1, j) + 0.65 * a(t - 1, i, j) + 0.65 * a(t - 1, i + 1, j) - 0.6 * a(t - 1, i, j - 1) - 0.65 * a(t - 1, i, j) - 0.65 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.31 * a(t - 1, i - 1, j) + 0.351 * a(t - 1, i, j) + 0.351 * a(t - 1, i + 1, j) - 0.31 * a(t - 1, i, j - 1) - 0.351 * a(t - 1, i, j) - 0.351 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.7 * a(t - 1, i - 1, j) + 0.75 * a(t - 1, i, j) + 0.75 * a(t - 1, i + 1, j) - 0.7 * a(t - 1, i, j - 1) - 0.75 * a(t - 1, i, j) - 0.75 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8 * a(t - 1, i - 1, j) + 0.85 * a(t - 1, i, j) + 0.85 * a(t - 1, i + 1, j) - 0.8 * a(t - 1, i, j - 1) - 0.85 * a(t - 1, i, j) - 0.85 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.41 * a(t - 1, i - 1, j) + 0.45099999999999996 * a(t - 1, i, j) + 0.45099999999999996 * a(t - 1, i + 1, j) - 0.41 * a(t - 1, i, j - 1) - 0.45099999999999996 * a(t - 1, i, j) - 0.45099999999999996 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.22000000000000003 * a(t - 1, i - 1, j) + 0.252 * a(t - 1, i, j) + 0.252 * a(t - 1, i + 1, j) - 0.22000000000000003 * a(t - 1, i, j - 1) - 0.252 * a(t - 1, i, j) - 0.252 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.53 * a(t - 1, i - 1, j) + 0.553 * a(t - 1, i, j) + 0.553 * a(t - 1, i + 1, j) - 0.53 * a(t - 1, i, j - 1) - 0.553 * a(t - 1, i, j) - 0.553 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.63 * a(t - 1, i - 1, j) + 0.653 * a(t - 1, i, j) + 0.653 * a(t - 1, i + 1, j) - 0.63 * a(t - 1, i, j - 1) - 0.653 * a(t - 1, i, j) - 0.653 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.33999999999999997 * a(t - 1, i - 1, j) + 0.354 * a(t - 1, i, j) + 0.354 * a(t - 1, i + 1, j) - 0.33999999999999997 * a(t - 1, i, j - 1) - 0.354 * a(t - 1, i, j) - 0.354 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.73 * a(t - 1, i - 1, j) + 0.753 * a(t - 1, i, j) + 0.753 * a(t - 1, i + 1, j) - 0.73 * a(t - 1, i, j - 1) - 0.753 * a(t - 1, i, j) - 0.753 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8300000000000001 * a(t - 1, i - 1, j) + 0.853 * a(t - 1, i, j) + 0.853 * a(t - 1, i + 1, j) - 0.8300000000000001 * a(t - 1, i, j - 1) - 0.853 * a(t - 1, i, j) - 0.853 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.44000000000000006 * a(t - 1, i - 1, j) + 0.454 * a(t - 1, i, j) + 0.454 * a(t - 1, i + 1, j) - 0.44000000000000006 * a(t - 1, i, j - 1) - 0.454 * a(t - 1, i, j) - 0.454 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.25 * a(t - 1, i - 1, j) + 0.255 * a(t - 1, i, j) + 0.255 * a(t - 1, i + 1, j) - 0.25 * a(t - 1, i, j - 1) - 0.255 * a(t - 1, i, j) - 0.255 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
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
	static __Pointer_cond_boundary_kernel_15__ * _Pointer_cond_boundary_kernel_15 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_boundary_kernel_15 = NULL;
	#undef pmod_lu
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_boundary_kernel_15__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_boundary_kernel_15__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	
	for (int old_i = l_grid.x0[1]; old_i < l_grid.x1[1]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[1], l_phys_grid.x1[1]);
	
	#pragma ivdep
	for (int old_j = l_grid.x0[0]; old_j < l_grid.x1[0]; ++old_j) {
	int j = pmod_lu(old_j, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.1 * a(t - 1, i - 1, j) + 0.15 * a(t - 1, i, j) + 0.15 * a(t - 1, i + 1, j) - 0.1 * a(t - 1, i, j - 1) - 0.15 * a(t - 1, i, j) - 0.15 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.2 * a(t - 1, i - 1, j) + 0.25 * a(t - 1, i, j) + 0.25 * a(t - 1, i + 1, j) - 0.2 * a(t - 1, i, j - 1) - 0.25 * a(t - 1, i, j) - 0.25 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.11000000000000001 * a(t - 1, i - 1, j) + 0.151 * a(t - 1, i, j) + 0.151 * a(t - 1, i + 1, j) - 0.11000000000000001 * a(t - 1, i, j - 1) - 0.151 * a(t - 1, i, j) - 0.151 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.3 * a(t - 1, i - 1, j) + 0.35 * a(t - 1, i, j) + 0.35 * a(t - 1, i + 1, j) - 0.3 * a(t - 1, i, j - 1) - 0.35 * a(t - 1, i, j) - 0.35 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.4 * a(t - 1, i - 1, j) + 0.45 * a(t - 1, i, j) + 0.45 * a(t - 1, i + 1, j) - 0.4 * a(t - 1, i, j - 1) - 0.45 * a(t - 1, i, j) - 0.45 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.21000000000000002 * a(t - 1, i - 1, j) + 0.251 * a(t - 1, i, j) + 0.251 * a(t - 1, i + 1, j) - 0.21000000000000002 * a(t - 1, i, j - 1) - 0.251 * a(t - 1, i, j) - 0.251 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.12 * a(t - 1, i - 1, j) + 0.152 * a(t - 1, i, j) + 0.152 * a(t - 1, i + 1, j) - 0.12 * a(t - 1, i, j - 1) - 0.152 * a(t - 1, i, j) - 0.152 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.13 * a(t - 1, i - 1, j) + 0.153 * a(t - 1, i, j) + 0.153 * a(t - 1, i + 1, j) - 0.13 * a(t - 1, i, j - 1) - 0.153 * a(t - 1, i, j) - 0.153 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.22999999999999998 * a(t - 1, i - 1, j) + 0.253 * a(t - 1, i, j) + 0.253 * a(t - 1, i + 1, j) - 0.22999999999999998 * a(t - 1, i, j - 1) - 0.253 * a(t - 1, i, j) - 0.253 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.13999999999999999 * a(t - 1, i - 1, j) + 0.154 * a(t - 1, i, j) + 0.154 * a(t - 1, i + 1, j) - 0.13999999999999999 * a(t - 1, i, j - 1) - 0.154 * a(t - 1, i, j) - 0.154 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.32999999999999996 * a(t - 1, i - 1, j) + 0.35300000000000004 * a(t - 1, i, j) + 0.35300000000000004 * a(t - 1, i + 1, j) - 0.32999999999999996 * a(t - 1, i, j - 1) - 0.35300000000000004 * a(t - 1, i, j) - 0.35300000000000004 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.43 * a(t - 1, i - 1, j) + 0.453 * a(t - 1, i, j) + 0.453 * a(t - 1, i + 1, j) - 0.43 * a(t - 1, i, j - 1) - 0.453 * a(t - 1, i, j) - 0.453 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.24 * a(t - 1, i - 1, j) + 0.254 * a(t - 1, i, j) + 0.254 * a(t - 1, i + 1, j) - 0.24 * a(t - 1, i, j - 1) - 0.254 * a(t - 1, i, j) - 0.254 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.15 * a(t - 1, i - 1, j) + 0.155 * a(t - 1, i, j) + 0.155 * a(t - 1, i + 1, j) - 0.15 * a(t - 1, i, j - 1) - 0.155 * a(t - 1, i, j) - 0.155 * a(t - 1, i, j + 1);
	
	
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.5 * a(t - 1, i - 1, j) + 0.55 * a(t - 1, i, j) + 0.55 * a(t - 1, i + 1, j) - 0.5 * a(t - 1, i, j - 1) - 0.55 * a(t - 1, i, j) - 0.55 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.6 * a(t - 1, i - 1, j) + 0.65 * a(t - 1, i, j) + 0.65 * a(t - 1, i + 1, j) - 0.6 * a(t - 1, i, j - 1) - 0.65 * a(t - 1, i, j) - 0.65 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.31 * a(t - 1, i - 1, j) + 0.351 * a(t - 1, i, j) + 0.351 * a(t - 1, i + 1, j) - 0.31 * a(t - 1, i, j - 1) - 0.351 * a(t - 1, i, j) - 0.351 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.7 * a(t - 1, i - 1, j) + 0.75 * a(t - 1, i, j) + 0.75 * a(t - 1, i + 1, j) - 0.7 * a(t - 1, i, j - 1) - 0.75 * a(t - 1, i, j) - 0.75 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8 * a(t - 1, i - 1, j) + 0.85 * a(t - 1, i, j) + 0.85 * a(t - 1, i + 1, j) - 0.8 * a(t - 1, i, j - 1) - 0.85 * a(t - 1, i, j) - 0.85 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.41 * a(t - 1, i - 1, j) + 0.45099999999999996 * a(t - 1, i, j) + 0.45099999999999996 * a(t - 1, i + 1, j) - 0.41 * a(t - 1, i, j - 1) - 0.45099999999999996 * a(t - 1, i, j) - 0.45099999999999996 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.22000000000000003 * a(t - 1, i - 1, j) + 0.252 * a(t - 1, i, j) + 0.252 * a(t - 1, i + 1, j) - 0.22000000000000003 * a(t - 1, i, j - 1) - 0.252 * a(t - 1, i, j) - 0.252 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.53 * a(t - 1, i - 1, j) + 0.553 * a(t - 1, i, j) + 0.553 * a(t - 1, i + 1, j) - 0.53 * a(t - 1, i, j - 1) - 0.553 * a(t - 1, i, j) - 0.553 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.63 * a(t - 1, i - 1, j) + 0.653 * a(t - 1, i, j) + 0.653 * a(t - 1, i + 1, j) - 0.63 * a(t - 1, i, j - 1) - 0.653 * a(t - 1, i, j) - 0.653 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.33999999999999997 * a(t - 1, i - 1, j) + 0.354 * a(t - 1, i, j) + 0.354 * a(t - 1, i + 1, j) - 0.33999999999999997 * a(t - 1, i, j - 1) - 0.354 * a(t - 1, i, j) - 0.354 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.73 * a(t - 1, i - 1, j) + 0.753 * a(t - 1, i, j) + 0.753 * a(t - 1, i + 1, j) - 0.73 * a(t - 1, i, j - 1) - 0.753 * a(t - 1, i, j) - 0.753 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.8300000000000001 * a(t - 1, i - 1, j) + 0.853 * a(t - 1, i, j) + 0.853 * a(t - 1, i + 1, j) - 0.8300000000000001 * a(t - 1, i, j - 1) - 0.853 * a(t - 1, i, j) - 0.853 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.44000000000000006 * a(t - 1, i - 1, j) + 0.454 * a(t - 1, i, j) + 0.454 * a(t - 1, i + 1, j) - 0.44000000000000006 * a(t - 1, i, j - 1) - 0.454 * a(t - 1, i, j) - 0.454 * a(t - 1, i, j + 1);
	
	
	#undef a(t, i, j)
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i, j) a.boundary(t, i, j)
	a(t, i, j) = 0.25 * a(t - 1, i - 1, j) + 0.255 * a(t - 1, i, j) + 0.255 * a(t - 1, i + 1, j) - 0.25 * a(t - 1, i, j - 1) - 0.255 * a(t - 1, i, j) - 0.255 * a(t - 1, i, j + 1);
	
	
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
	static __Pointer_boundary_kernel_15__ * _Pointer_boundary_kernel_15 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_boundary_kernel_15 = NULL;
	#undef pmod_lu
	
	
	
	/* KNOWN */
	class __Pointer_cond_interior_kernel_15__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_cond_interior_kernel_15__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.1 * pt_a_1[l_a_stride_1 * (-1)] + 0.15 * pt_a_1[0] + 0.15 * pt_a_1[l_a_stride_1 * (1)] - 0.1 * pt_a_1[l_a_stride_0 * (-1)] - 0.15 * pt_a_1[0] - 0.15 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.2 * pt_a_1[l_a_stride_1 * (-1)] + 0.25 * pt_a_1[0] + 0.25 * pt_a_1[l_a_stride_1 * (1)] - 0.2 * pt_a_1[l_a_stride_0 * (-1)] - 0.25 * pt_a_1[0] - 0.25 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11000000000000001 * pt_a_1[l_a_stride_1 * (-1)] + 0.151 * pt_a_1[0] + 0.151 * pt_a_1[l_a_stride_1 * (1)] - 0.11000000000000001 * pt_a_1[l_a_stride_0 * (-1)] - 0.151 * pt_a_1[0] - 0.151 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.3 * pt_a_1[l_a_stride_1 * (-1)] + 0.35 * pt_a_1[0] + 0.35 * pt_a_1[l_a_stride_1 * (1)] - 0.3 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] - 0.35 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.4 * pt_a_1[l_a_stride_1 * (-1)] + 0.45 * pt_a_1[0] + 0.45 * pt_a_1[l_a_stride_1 * (1)] - 0.4 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] - 0.45 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21000000000000002 * pt_a_1[l_a_stride_1 * (-1)] + 0.251 * pt_a_1[0] + 0.251 * pt_a_1[l_a_stride_1 * (1)] - 0.21000000000000002 * pt_a_1[l_a_stride_0 * (-1)] - 0.251 * pt_a_1[0] - 0.251 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.12 * pt_a_1[l_a_stride_1 * (-1)] + 0.152 * pt_a_1[0] + 0.152 * pt_a_1[l_a_stride_1 * (1)] - 0.12 * pt_a_1[l_a_stride_0 * (-1)] - 0.152 * pt_a_1[0] - 0.152 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.13 * pt_a_1[l_a_stride_1 * (-1)] + 0.153 * pt_a_1[0] + 0.153 * pt_a_1[l_a_stride_1 * (1)] - 0.13 * pt_a_1[l_a_stride_0 * (-1)] - 0.153 * pt_a_1[0] - 0.153 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.22999999999999998 * pt_a_1[l_a_stride_1 * (-1)] + 0.253 * pt_a_1[0] + 0.253 * pt_a_1[l_a_stride_1 * (1)] - 0.22999999999999998 * pt_a_1[l_a_stride_0 * (-1)] - 0.253 * pt_a_1[0] - 0.253 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.13999999999999999 * pt_a_1[l_a_stride_1 * (-1)] + 0.154 * pt_a_1[0] + 0.154 * pt_a_1[l_a_stride_1 * (1)] - 0.13999999999999999 * pt_a_1[l_a_stride_0 * (-1)] - 0.154 * pt_a_1[0] - 0.154 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.32999999999999996 * pt_a_1[l_a_stride_1 * (-1)] + 0.35300000000000004 * pt_a_1[0] + 0.35300000000000004 * pt_a_1[l_a_stride_1 * (1)] - 0.32999999999999996 * pt_a_1[l_a_stride_0 * (-1)] - 0.35300000000000004 * pt_a_1[0] - 0.35300000000000004 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.43 * pt_a_1[l_a_stride_1 * (-1)] + 0.453 * pt_a_1[0] + 0.453 * pt_a_1[l_a_stride_1 * (1)] - 0.43 * pt_a_1[l_a_stride_0 * (-1)] - 0.453 * pt_a_1[0] - 0.453 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.24 * pt_a_1[l_a_stride_1 * (-1)] + 0.254 * pt_a_1[0] + 0.254 * pt_a_1[l_a_stride_1 * (1)] - 0.24 * pt_a_1[l_a_stride_0 * (-1)] - 0.254 * pt_a_1[0] - 0.254 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.15 * pt_a_1[l_a_stride_1 * (-1)] + 0.155 * pt_a_1[0] + 0.155 * pt_a_1[l_a_stride_1 * (1)] - 0.15 * pt_a_1[l_a_stride_0 * (-1)] - 0.155 * pt_a_1[0] - 0.155 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.5 * pt_a_1[l_a_stride_1 * (-1)] + 0.55 * pt_a_1[0] + 0.55 * pt_a_1[l_a_stride_1 * (1)] - 0.5 * pt_a_1[l_a_stride_0 * (-1)] - 0.55 * pt_a_1[0] - 0.55 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.6 * pt_a_1[l_a_stride_1 * (-1)] + 0.65 * pt_a_1[0] + 0.65 * pt_a_1[l_a_stride_1 * (1)] - 0.6 * pt_a_1[l_a_stride_0 * (-1)] - 0.65 * pt_a_1[0] - 0.65 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.31 * pt_a_1[l_a_stride_1 * (-1)] + 0.351 * pt_a_1[0] + 0.351 * pt_a_1[l_a_stride_1 * (1)] - 0.31 * pt_a_1[l_a_stride_0 * (-1)] - 0.351 * pt_a_1[0] - 0.351 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.7 * pt_a_1[l_a_stride_1 * (-1)] + 0.75 * pt_a_1[0] + 0.75 * pt_a_1[l_a_stride_1 * (1)] - 0.7 * pt_a_1[l_a_stride_0 * (-1)] - 0.75 * pt_a_1[0] - 0.75 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.8 * pt_a_1[l_a_stride_1 * (-1)] + 0.85 * pt_a_1[0] + 0.85 * pt_a_1[l_a_stride_1 * (1)] - 0.8 * pt_a_1[l_a_stride_0 * (-1)] - 0.85 * pt_a_1[0] - 0.85 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.41 * pt_a_1[l_a_stride_1 * (-1)] + 0.45099999999999996 * pt_a_1[0] + 0.45099999999999996 * pt_a_1[l_a_stride_1 * (1)] - 0.41 * pt_a_1[l_a_stride_0 * (-1)] - 0.45099999999999996 * pt_a_1[0] - 0.45099999999999996 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.22000000000000003 * pt_a_1[l_a_stride_1 * (-1)] + 0.252 * pt_a_1[0] + 0.252 * pt_a_1[l_a_stride_1 * (1)] - 0.22000000000000003 * pt_a_1[l_a_stride_0 * (-1)] - 0.252 * pt_a_1[0] - 0.252 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.53 * pt_a_1[l_a_stride_1 * (-1)] + 0.553 * pt_a_1[0] + 0.553 * pt_a_1[l_a_stride_1 * (1)] - 0.53 * pt_a_1[l_a_stride_0 * (-1)] - 0.553 * pt_a_1[0] - 0.553 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.63 * pt_a_1[l_a_stride_1 * (-1)] + 0.653 * pt_a_1[0] + 0.653 * pt_a_1[l_a_stride_1 * (1)] - 0.63 * pt_a_1[l_a_stride_0 * (-1)] - 0.653 * pt_a_1[0] - 0.653 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.33999999999999997 * pt_a_1[l_a_stride_1 * (-1)] + 0.354 * pt_a_1[0] + 0.354 * pt_a_1[l_a_stride_1 * (1)] - 0.33999999999999997 * pt_a_1[l_a_stride_0 * (-1)] - 0.354 * pt_a_1[0] - 0.354 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.73 * pt_a_1[l_a_stride_1 * (-1)] + 0.753 * pt_a_1[0] + 0.753 * pt_a_1[l_a_stride_1 * (1)] - 0.73 * pt_a_1[l_a_stride_0 * (-1)] - 0.753 * pt_a_1[0] - 0.753 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.8300000000000001 * pt_a_1[l_a_stride_1 * (-1)] + 0.853 * pt_a_1[0] + 0.853 * pt_a_1[l_a_stride_1 * (1)] - 0.8300000000000001 * pt_a_1[l_a_stride_0 * (-1)] - 0.853 * pt_a_1[0] - 0.853 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.44000000000000006 * pt_a_1[l_a_stride_1 * (-1)] + 0.454 * pt_a_1[0] + 0.454 * pt_a_1[l_a_stride_1 * (1)] - 0.44000000000000006 * pt_a_1[l_a_stride_0 * (-1)] - 0.454 * pt_a_1[0] - 0.454 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.25 * pt_a_1[l_a_stride_1 * (-1)] + 0.255 * pt_a_1[0] + 0.255 * pt_a_1[l_a_stride_1 * (1)] - 0.25 * pt_a_1[l_a_stride_0 * (-1)] - 0.255 * pt_a_1[0] - 0.255 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
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
	static __Pointer_cond_interior_kernel_15__ * _Pointer_cond_interior_kernel_15 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_cond_interior_kernel_15 = NULL;
	
	
	
	
	/* KNOWN */
	class __Pointer_interior_kernel_15__ {
	private: 
	Pochoir <2> & leap_frog; 
	Pochoir_Array <double, 2> & a; 
	public: 
	__Pointer_interior_kernel_15__(Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <2> const & grid) {
	Grid_Info <2> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_1, gap_a_0;
	const int l_a_stride_1 = a.stride(1), l_a_stride_0 = a.stride(0);

	Grid_Info <2> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.1 * pt_a_1[l_a_stride_1 * (-1)] + 0.15 * pt_a_1[0] + 0.15 * pt_a_1[l_a_stride_1 * (1)] - 0.1 * pt_a_1[l_a_stride_0 * (-1)] - 0.15 * pt_a_1[0] - 0.15 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.2 * pt_a_1[l_a_stride_1 * (-1)] + 0.25 * pt_a_1[0] + 0.25 * pt_a_1[l_a_stride_1 * (1)] - 0.2 * pt_a_1[l_a_stride_0 * (-1)] - 0.25 * pt_a_1[0] - 0.25 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11000000000000001 * pt_a_1[l_a_stride_1 * (-1)] + 0.151 * pt_a_1[0] + 0.151 * pt_a_1[l_a_stride_1 * (1)] - 0.11000000000000001 * pt_a_1[l_a_stride_0 * (-1)] - 0.151 * pt_a_1[0] - 0.151 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.3 * pt_a_1[l_a_stride_1 * (-1)] + 0.35 * pt_a_1[0] + 0.35 * pt_a_1[l_a_stride_1 * (1)] - 0.3 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] - 0.35 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.4 * pt_a_1[l_a_stride_1 * (-1)] + 0.45 * pt_a_1[0] + 0.45 * pt_a_1[l_a_stride_1 * (1)] - 0.4 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] - 0.45 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21000000000000002 * pt_a_1[l_a_stride_1 * (-1)] + 0.251 * pt_a_1[0] + 0.251 * pt_a_1[l_a_stride_1 * (1)] - 0.21000000000000002 * pt_a_1[l_a_stride_0 * (-1)] - 0.251 * pt_a_1[0] - 0.251 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.12 * pt_a_1[l_a_stride_1 * (-1)] + 0.152 * pt_a_1[0] + 0.152 * pt_a_1[l_a_stride_1 * (1)] - 0.12 * pt_a_1[l_a_stride_0 * (-1)] - 0.152 * pt_a_1[0] - 0.152 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.13 * pt_a_1[l_a_stride_1 * (-1)] + 0.153 * pt_a_1[0] + 0.153 * pt_a_1[l_a_stride_1 * (1)] - 0.13 * pt_a_1[l_a_stride_0 * (-1)] - 0.153 * pt_a_1[0] - 0.153 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.22999999999999998 * pt_a_1[l_a_stride_1 * (-1)] + 0.253 * pt_a_1[0] + 0.253 * pt_a_1[l_a_stride_1 * (1)] - 0.22999999999999998 * pt_a_1[l_a_stride_0 * (-1)] - 0.253 * pt_a_1[0] - 0.253 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.13999999999999999 * pt_a_1[l_a_stride_1 * (-1)] + 0.154 * pt_a_1[0] + 0.154 * pt_a_1[l_a_stride_1 * (1)] - 0.13999999999999999 * pt_a_1[l_a_stride_0 * (-1)] - 0.154 * pt_a_1[0] - 0.154 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.32999999999999996 * pt_a_1[l_a_stride_1 * (-1)] + 0.35300000000000004 * pt_a_1[0] + 0.35300000000000004 * pt_a_1[l_a_stride_1 * (1)] - 0.32999999999999996 * pt_a_1[l_a_stride_0 * (-1)] - 0.35300000000000004 * pt_a_1[0] - 0.35300000000000004 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.43 * pt_a_1[l_a_stride_1 * (-1)] + 0.453 * pt_a_1[0] + 0.453 * pt_a_1[l_a_stride_1 * (1)] - 0.43 * pt_a_1[l_a_stride_0 * (-1)] - 0.453 * pt_a_1[0] - 0.453 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.24 * pt_a_1[l_a_stride_1 * (-1)] + 0.254 * pt_a_1[0] + 0.254 * pt_a_1[l_a_stride_1 * (1)] - 0.24 * pt_a_1[l_a_stride_0 * (-1)] - 0.254 * pt_a_1[0] - 0.254 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.15 * pt_a_1[l_a_stride_1 * (-1)] + 0.155 * pt_a_1[0] + 0.155 * pt_a_1[l_a_stride_1 * (1)] - 0.15 * pt_a_1[l_a_stride_0 * (-1)] - 0.155 * pt_a_1[0] - 0.155 * pt_a_1[l_a_stride_0 * (1)];
	
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
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.5 * pt_a_1[l_a_stride_1 * (-1)] + 0.55 * pt_a_1[0] + 0.55 * pt_a_1[l_a_stride_1 * (1)] - 0.5 * pt_a_1[l_a_stride_0 * (-1)] - 0.55 * pt_a_1[0] - 0.55 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.6 * pt_a_1[l_a_stride_1 * (-1)] + 0.65 * pt_a_1[0] + 0.65 * pt_a_1[l_a_stride_1 * (1)] - 0.6 * pt_a_1[l_a_stride_0 * (-1)] - 0.65 * pt_a_1[0] - 0.65 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.31 * pt_a_1[l_a_stride_1 * (-1)] + 0.351 * pt_a_1[0] + 0.351 * pt_a_1[l_a_stride_1 * (1)] - 0.31 * pt_a_1[l_a_stride_0 * (-1)] - 0.351 * pt_a_1[0] - 0.351 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.7 * pt_a_1[l_a_stride_1 * (-1)] + 0.75 * pt_a_1[0] + 0.75 * pt_a_1[l_a_stride_1 * (1)] - 0.7 * pt_a_1[l_a_stride_0 * (-1)] - 0.75 * pt_a_1[0] - 0.75 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.8 * pt_a_1[l_a_stride_1 * (-1)] + 0.85 * pt_a_1[0] + 0.85 * pt_a_1[l_a_stride_1 * (1)] - 0.8 * pt_a_1[l_a_stride_0 * (-1)] - 0.85 * pt_a_1[0] - 0.85 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.41 * pt_a_1[l_a_stride_1 * (-1)] + 0.45099999999999996 * pt_a_1[0] + 0.45099999999999996 * pt_a_1[l_a_stride_1 * (1)] - 0.41 * pt_a_1[l_a_stride_0 * (-1)] - 0.45099999999999996 * pt_a_1[0] - 0.45099999999999996 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.22000000000000003 * pt_a_1[l_a_stride_1 * (-1)] + 0.252 * pt_a_1[0] + 0.252 * pt_a_1[l_a_stride_1 * (1)] - 0.22000000000000003 * pt_a_1[l_a_stride_0 * (-1)] - 0.252 * pt_a_1[0] - 0.252 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	if ((i & 0x1) == 0) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.53 * pt_a_1[l_a_stride_1 * (-1)] + 0.553 * pt_a_1[0] + 0.553 * pt_a_1[l_a_stride_1 * (1)] - 0.53 * pt_a_1[l_a_stride_0 * (-1)] - 0.553 * pt_a_1[0] - 0.553 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.63 * pt_a_1[l_a_stride_1 * (-1)] + 0.653 * pt_a_1[0] + 0.653 * pt_a_1[l_a_stride_1 * (1)] - 0.63 * pt_a_1[l_a_stride_0 * (-1)] - 0.653 * pt_a_1[0] - 0.653 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.33999999999999997 * pt_a_1[l_a_stride_1 * (-1)] + 0.354 * pt_a_1[0] + 0.354 * pt_a_1[l_a_stride_1 * (1)] - 0.33999999999999997 * pt_a_1[l_a_stride_0 * (-1)] - 0.354 * pt_a_1[0] - 0.354 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if ((j & 0x1) == 0) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.73 * pt_a_1[l_a_stride_1 * (-1)] + 0.753 * pt_a_1[0] + 0.753 * pt_a_1[l_a_stride_1 * (1)] - 0.73 * pt_a_1[l_a_stride_0 * (-1)] - 0.753 * pt_a_1[0] - 0.753 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	} else 
	if ((j & 0x1) == 1) {
	
	if (__g_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.8300000000000001 * pt_a_1[l_a_stride_1 * (-1)] + 0.853 * pt_a_1[0] + 0.853 * pt_a_1[l_a_stride_1 * (1)] - 0.8300000000000001 * pt_a_1[l_a_stride_0 * (-1)] - 0.853 * pt_a_1[0] - 0.853 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_tiny_inclusive_0__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.44000000000000006 * pt_a_1[l_a_stride_1 * (-1)] + 0.454 * pt_a_1[0] + 0.454 * pt_a_1[l_a_stride_1 * (1)] - 0.44000000000000006 * pt_a_1[l_a_stride_0 * (-1)] - 0.454 * pt_a_1[0] - 0.454 * pt_a_1[l_a_stride_0 * (1)];
	
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i, j ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.25 * pt_a_1[l_a_stride_1 * (-1)] + 0.255 * pt_a_1[0] + 0.255 * pt_a_1[l_a_stride_1 * (1)] - 0.25 * pt_a_1[l_a_stride_0 * (-1)] - 0.255 * pt_a_1[0] - 0.255 * pt_a_1[l_a_stride_0 * (1)];
	
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
	static __Pointer_interior_kernel_15__ * _Pointer_interior_kernel_15 = NULL;
	static Pochoir_Base_Kernel <2> * Pointer_interior_kernel_15 = NULL;
	
	
	
	extern "C" 
	int Create_Lambdas (Pochoir <2> & _leap_frog, Pochoir_Array <double, 2> & _a){
	
		_Pointer_boundary_kernel_0 = new __Pointer_boundary_kernel_0__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_0), 2 >  * l_Pointer_boundary_kernel_0 = NULL;
		l_Pointer_boundary_kernel_0 = new Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_0), 2 > ((*_Pointer_boundary_kernel_0), __POCHOIR_Shape__0__);
		Pointer_boundary_kernel_0 = l_Pointer_boundary_kernel_0;
	
		_Pointer_boundary_kernel_1 = new __Pointer_boundary_kernel_1__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_1), 2 >  * l_Pointer_boundary_kernel_1 = NULL;
		l_Pointer_boundary_kernel_1 = new Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_1), 2 > ((*_Pointer_boundary_kernel_1), __POCHOIR_Shape__1__);
		Pointer_boundary_kernel_1 = l_Pointer_boundary_kernel_1;
	
		_Pointer_boundary_kernel_2 = new __Pointer_boundary_kernel_2__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_2), 2 >  * l_Pointer_boundary_kernel_2 = NULL;
		l_Pointer_boundary_kernel_2 = new Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_2), 2 > ((*_Pointer_boundary_kernel_2), __POCHOIR_Shape__2__);
		Pointer_boundary_kernel_2 = l_Pointer_boundary_kernel_2;
	
		_Pointer_boundary_kernel_3 = new __Pointer_boundary_kernel_3__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_3), 2 >  * l_Pointer_boundary_kernel_3 = NULL;
		l_Pointer_boundary_kernel_3 = new Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_3), 2 > ((*_Pointer_boundary_kernel_3), __POCHOIR_Shape__3__);
		Pointer_boundary_kernel_3 = l_Pointer_boundary_kernel_3;
	
		_Pointer_boundary_kernel_4 = new __Pointer_boundary_kernel_4__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_4), 2 >  * l_Pointer_boundary_kernel_4 = NULL;
		l_Pointer_boundary_kernel_4 = new Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_4), 2 > ((*_Pointer_boundary_kernel_4), __POCHOIR_Shape__4__);
		Pointer_boundary_kernel_4 = l_Pointer_boundary_kernel_4;
	
		_Pointer_boundary_kernel_5 = new __Pointer_boundary_kernel_5__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_5), 2 >  * l_Pointer_boundary_kernel_5 = NULL;
		l_Pointer_boundary_kernel_5 = new Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_5), 2 > ((*_Pointer_boundary_kernel_5), __POCHOIR_Shape__5__);
		Pointer_boundary_kernel_5 = l_Pointer_boundary_kernel_5;
	
		_Pointer_boundary_kernel_6 = new __Pointer_boundary_kernel_6__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_6), 2 >  * l_Pointer_boundary_kernel_6 = NULL;
		l_Pointer_boundary_kernel_6 = new Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_6), 2 > ((*_Pointer_boundary_kernel_6), __POCHOIR_Shape__6__);
		Pointer_boundary_kernel_6 = l_Pointer_boundary_kernel_6;
	
		_Pointer_boundary_kernel_7 = new __Pointer_boundary_kernel_7__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_7), 2 >  * l_Pointer_boundary_kernel_7 = NULL;
		l_Pointer_boundary_kernel_7 = new Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_7), 2 > ((*_Pointer_boundary_kernel_7), __POCHOIR_Shape__7__);
		Pointer_boundary_kernel_7 = l_Pointer_boundary_kernel_7;
	
		_Pointer_boundary_kernel_8 = new __Pointer_boundary_kernel_8__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_8), 2 >  * l_Pointer_boundary_kernel_8 = NULL;
		l_Pointer_boundary_kernel_8 = new Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_8), 2 > ((*_Pointer_boundary_kernel_8), __POCHOIR_Shape__8__);
		Pointer_boundary_kernel_8 = l_Pointer_boundary_kernel_8;
	
		_Pointer_boundary_kernel_9 = new __Pointer_boundary_kernel_9__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_9), 2 >  * l_Pointer_boundary_kernel_9 = NULL;
		l_Pointer_boundary_kernel_9 = new Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_9), 2 > ((*_Pointer_boundary_kernel_9), __POCHOIR_Shape__9__);
		Pointer_boundary_kernel_9 = l_Pointer_boundary_kernel_9;
	
		_Pointer_boundary_kernel_10 = new __Pointer_boundary_kernel_10__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_10), 2 >  * l_Pointer_boundary_kernel_10 = NULL;
		l_Pointer_boundary_kernel_10 = new Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_10), 2 > ((*_Pointer_boundary_kernel_10), __POCHOIR_Shape__10__);
		Pointer_boundary_kernel_10 = l_Pointer_boundary_kernel_10;
	
		_Pointer_boundary_kernel_11 = new __Pointer_boundary_kernel_11__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_11), 2 >  * l_Pointer_boundary_kernel_11 = NULL;
		l_Pointer_boundary_kernel_11 = new Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_11), 2 > ((*_Pointer_boundary_kernel_11), __POCHOIR_Shape__11__);
		Pointer_boundary_kernel_11 = l_Pointer_boundary_kernel_11;
	
		_Pointer_boundary_kernel_12 = new __Pointer_boundary_kernel_12__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_12), 2 >  * l_Pointer_boundary_kernel_12 = NULL;
		l_Pointer_boundary_kernel_12 = new Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_12), 2 > ((*_Pointer_boundary_kernel_12), __POCHOIR_Shape__12__);
		Pointer_boundary_kernel_12 = l_Pointer_boundary_kernel_12;
	
		_Pointer_boundary_kernel_13 = new __Pointer_boundary_kernel_13__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_13), 2 >  * l_Pointer_boundary_kernel_13 = NULL;
		l_Pointer_boundary_kernel_13 = new Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_13), 2 > ((*_Pointer_boundary_kernel_13), __POCHOIR_Shape__13__);
		Pointer_boundary_kernel_13 = l_Pointer_boundary_kernel_13;
	
		_Pointer_boundary_kernel_14 = new __Pointer_boundary_kernel_14__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_14), 2 >  * l_Pointer_boundary_kernel_14 = NULL;
		l_Pointer_boundary_kernel_14 = new Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_14), 2 > ((*_Pointer_boundary_kernel_14), __POCHOIR_Shape__14__);
		Pointer_boundary_kernel_14 = l_Pointer_boundary_kernel_14;
	
		_Pointer_boundary_kernel_15 = new __Pointer_boundary_kernel_15__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_15), 2 >  * l_Pointer_boundary_kernel_15 = NULL;
		l_Pointer_boundary_kernel_15 = new Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_15), 2 > ((*_Pointer_boundary_kernel_15), __POCHOIR_Shape__15__);
		Pointer_boundary_kernel_15 = l_Pointer_boundary_kernel_15;
	
		_Pointer_cond_boundary_kernel_0 = new __Pointer_cond_boundary_kernel_0__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_0), 2 >  * l_Pointer_cond_boundary_kernel_0 = NULL;
		l_Pointer_cond_boundary_kernel_0 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_0), 2 > ((*_Pointer_cond_boundary_kernel_0), __POCHOIR_Shape__0__);
		Pointer_cond_boundary_kernel_0 = l_Pointer_cond_boundary_kernel_0;
	
		_Pointer_cond_boundary_kernel_1 = new __Pointer_cond_boundary_kernel_1__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_1), 2 >  * l_Pointer_cond_boundary_kernel_1 = NULL;
		l_Pointer_cond_boundary_kernel_1 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_1), 2 > ((*_Pointer_cond_boundary_kernel_1), __POCHOIR_Shape__1__);
		Pointer_cond_boundary_kernel_1 = l_Pointer_cond_boundary_kernel_1;
	
		_Pointer_cond_boundary_kernel_2 = new __Pointer_cond_boundary_kernel_2__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_2), 2 >  * l_Pointer_cond_boundary_kernel_2 = NULL;
		l_Pointer_cond_boundary_kernel_2 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_2), 2 > ((*_Pointer_cond_boundary_kernel_2), __POCHOIR_Shape__2__);
		Pointer_cond_boundary_kernel_2 = l_Pointer_cond_boundary_kernel_2;
	
		_Pointer_cond_boundary_kernel_3 = new __Pointer_cond_boundary_kernel_3__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_3), 2 >  * l_Pointer_cond_boundary_kernel_3 = NULL;
		l_Pointer_cond_boundary_kernel_3 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_3), 2 > ((*_Pointer_cond_boundary_kernel_3), __POCHOIR_Shape__3__);
		Pointer_cond_boundary_kernel_3 = l_Pointer_cond_boundary_kernel_3;
	
		_Pointer_cond_boundary_kernel_4 = new __Pointer_cond_boundary_kernel_4__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_4), 2 >  * l_Pointer_cond_boundary_kernel_4 = NULL;
		l_Pointer_cond_boundary_kernel_4 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_4), 2 > ((*_Pointer_cond_boundary_kernel_4), __POCHOIR_Shape__4__);
		Pointer_cond_boundary_kernel_4 = l_Pointer_cond_boundary_kernel_4;
	
		_Pointer_cond_boundary_kernel_5 = new __Pointer_cond_boundary_kernel_5__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_5), 2 >  * l_Pointer_cond_boundary_kernel_5 = NULL;
		l_Pointer_cond_boundary_kernel_5 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_5), 2 > ((*_Pointer_cond_boundary_kernel_5), __POCHOIR_Shape__5__);
		Pointer_cond_boundary_kernel_5 = l_Pointer_cond_boundary_kernel_5;
	
		_Pointer_cond_boundary_kernel_6 = new __Pointer_cond_boundary_kernel_6__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_6), 2 >  * l_Pointer_cond_boundary_kernel_6 = NULL;
		l_Pointer_cond_boundary_kernel_6 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_6), 2 > ((*_Pointer_cond_boundary_kernel_6), __POCHOIR_Shape__6__);
		Pointer_cond_boundary_kernel_6 = l_Pointer_cond_boundary_kernel_6;
	
		_Pointer_cond_boundary_kernel_7 = new __Pointer_cond_boundary_kernel_7__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_7), 2 >  * l_Pointer_cond_boundary_kernel_7 = NULL;
		l_Pointer_cond_boundary_kernel_7 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_7), 2 > ((*_Pointer_cond_boundary_kernel_7), __POCHOIR_Shape__7__);
		Pointer_cond_boundary_kernel_7 = l_Pointer_cond_boundary_kernel_7;
	
		_Pointer_cond_boundary_kernel_8 = new __Pointer_cond_boundary_kernel_8__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_8), 2 >  * l_Pointer_cond_boundary_kernel_8 = NULL;
		l_Pointer_cond_boundary_kernel_8 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_8), 2 > ((*_Pointer_cond_boundary_kernel_8), __POCHOIR_Shape__8__);
		Pointer_cond_boundary_kernel_8 = l_Pointer_cond_boundary_kernel_8;
	
		_Pointer_cond_boundary_kernel_9 = new __Pointer_cond_boundary_kernel_9__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_9), 2 >  * l_Pointer_cond_boundary_kernel_9 = NULL;
		l_Pointer_cond_boundary_kernel_9 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_9), 2 > ((*_Pointer_cond_boundary_kernel_9), __POCHOIR_Shape__9__);
		Pointer_cond_boundary_kernel_9 = l_Pointer_cond_boundary_kernel_9;
	
		_Pointer_cond_boundary_kernel_10 = new __Pointer_cond_boundary_kernel_10__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_10), 2 >  * l_Pointer_cond_boundary_kernel_10 = NULL;
		l_Pointer_cond_boundary_kernel_10 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_10), 2 > ((*_Pointer_cond_boundary_kernel_10), __POCHOIR_Shape__10__);
		Pointer_cond_boundary_kernel_10 = l_Pointer_cond_boundary_kernel_10;
	
		_Pointer_cond_boundary_kernel_11 = new __Pointer_cond_boundary_kernel_11__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_11), 2 >  * l_Pointer_cond_boundary_kernel_11 = NULL;
		l_Pointer_cond_boundary_kernel_11 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_11), 2 > ((*_Pointer_cond_boundary_kernel_11), __POCHOIR_Shape__11__);
		Pointer_cond_boundary_kernel_11 = l_Pointer_cond_boundary_kernel_11;
	
		_Pointer_cond_boundary_kernel_12 = new __Pointer_cond_boundary_kernel_12__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_12), 2 >  * l_Pointer_cond_boundary_kernel_12 = NULL;
		l_Pointer_cond_boundary_kernel_12 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_12), 2 > ((*_Pointer_cond_boundary_kernel_12), __POCHOIR_Shape__12__);
		Pointer_cond_boundary_kernel_12 = l_Pointer_cond_boundary_kernel_12;
	
		_Pointer_cond_boundary_kernel_13 = new __Pointer_cond_boundary_kernel_13__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_13), 2 >  * l_Pointer_cond_boundary_kernel_13 = NULL;
		l_Pointer_cond_boundary_kernel_13 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_13), 2 > ((*_Pointer_cond_boundary_kernel_13), __POCHOIR_Shape__13__);
		Pointer_cond_boundary_kernel_13 = l_Pointer_cond_boundary_kernel_13;
	
		_Pointer_cond_boundary_kernel_14 = new __Pointer_cond_boundary_kernel_14__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_14), 2 >  * l_Pointer_cond_boundary_kernel_14 = NULL;
		l_Pointer_cond_boundary_kernel_14 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_14), 2 > ((*_Pointer_cond_boundary_kernel_14), __POCHOIR_Shape__14__);
		Pointer_cond_boundary_kernel_14 = l_Pointer_cond_boundary_kernel_14;
	
		_Pointer_cond_boundary_kernel_15 = new __Pointer_cond_boundary_kernel_15__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_15), 2 >  * l_Pointer_cond_boundary_kernel_15 = NULL;
		l_Pointer_cond_boundary_kernel_15 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_15), 2 > ((*_Pointer_cond_boundary_kernel_15), __POCHOIR_Shape__15__);
		Pointer_cond_boundary_kernel_15 = l_Pointer_cond_boundary_kernel_15;
	
		_Pointer_interior_kernel_0 = new __Pointer_interior_kernel_0__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_0), 2 >  * l_Pointer_interior_kernel_0 = NULL;
		l_Pointer_interior_kernel_0 = new Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_0), 2 > ((*_Pointer_interior_kernel_0), __POCHOIR_Shape__0__);
		Pointer_interior_kernel_0 = l_Pointer_interior_kernel_0;
	
		_Pointer_interior_kernel_1 = new __Pointer_interior_kernel_1__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_1), 2 >  * l_Pointer_interior_kernel_1 = NULL;
		l_Pointer_interior_kernel_1 = new Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_1), 2 > ((*_Pointer_interior_kernel_1), __POCHOIR_Shape__1__);
		Pointer_interior_kernel_1 = l_Pointer_interior_kernel_1;
	
		_Pointer_interior_kernel_2 = new __Pointer_interior_kernel_2__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_2), 2 >  * l_Pointer_interior_kernel_2 = NULL;
		l_Pointer_interior_kernel_2 = new Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_2), 2 > ((*_Pointer_interior_kernel_2), __POCHOIR_Shape__2__);
		Pointer_interior_kernel_2 = l_Pointer_interior_kernel_2;
	
		_Pointer_interior_kernel_3 = new __Pointer_interior_kernel_3__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_3), 2 >  * l_Pointer_interior_kernel_3 = NULL;
		l_Pointer_interior_kernel_3 = new Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_3), 2 > ((*_Pointer_interior_kernel_3), __POCHOIR_Shape__3__);
		Pointer_interior_kernel_3 = l_Pointer_interior_kernel_3;
	
		_Pointer_interior_kernel_4 = new __Pointer_interior_kernel_4__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_4), 2 >  * l_Pointer_interior_kernel_4 = NULL;
		l_Pointer_interior_kernel_4 = new Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_4), 2 > ((*_Pointer_interior_kernel_4), __POCHOIR_Shape__4__);
		Pointer_interior_kernel_4 = l_Pointer_interior_kernel_4;
	
		_Pointer_interior_kernel_5 = new __Pointer_interior_kernel_5__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_5), 2 >  * l_Pointer_interior_kernel_5 = NULL;
		l_Pointer_interior_kernel_5 = new Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_5), 2 > ((*_Pointer_interior_kernel_5), __POCHOIR_Shape__5__);
		Pointer_interior_kernel_5 = l_Pointer_interior_kernel_5;
	
		_Pointer_interior_kernel_6 = new __Pointer_interior_kernel_6__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_6), 2 >  * l_Pointer_interior_kernel_6 = NULL;
		l_Pointer_interior_kernel_6 = new Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_6), 2 > ((*_Pointer_interior_kernel_6), __POCHOIR_Shape__6__);
		Pointer_interior_kernel_6 = l_Pointer_interior_kernel_6;
	
		_Pointer_interior_kernel_7 = new __Pointer_interior_kernel_7__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_7), 2 >  * l_Pointer_interior_kernel_7 = NULL;
		l_Pointer_interior_kernel_7 = new Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_7), 2 > ((*_Pointer_interior_kernel_7), __POCHOIR_Shape__7__);
		Pointer_interior_kernel_7 = l_Pointer_interior_kernel_7;
	
		_Pointer_interior_kernel_8 = new __Pointer_interior_kernel_8__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_8), 2 >  * l_Pointer_interior_kernel_8 = NULL;
		l_Pointer_interior_kernel_8 = new Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_8), 2 > ((*_Pointer_interior_kernel_8), __POCHOIR_Shape__8__);
		Pointer_interior_kernel_8 = l_Pointer_interior_kernel_8;
	
		_Pointer_interior_kernel_9 = new __Pointer_interior_kernel_9__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_9), 2 >  * l_Pointer_interior_kernel_9 = NULL;
		l_Pointer_interior_kernel_9 = new Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_9), 2 > ((*_Pointer_interior_kernel_9), __POCHOIR_Shape__9__);
		Pointer_interior_kernel_9 = l_Pointer_interior_kernel_9;
	
		_Pointer_interior_kernel_10 = new __Pointer_interior_kernel_10__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_10), 2 >  * l_Pointer_interior_kernel_10 = NULL;
		l_Pointer_interior_kernel_10 = new Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_10), 2 > ((*_Pointer_interior_kernel_10), __POCHOIR_Shape__10__);
		Pointer_interior_kernel_10 = l_Pointer_interior_kernel_10;
	
		_Pointer_interior_kernel_11 = new __Pointer_interior_kernel_11__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_11), 2 >  * l_Pointer_interior_kernel_11 = NULL;
		l_Pointer_interior_kernel_11 = new Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_11), 2 > ((*_Pointer_interior_kernel_11), __POCHOIR_Shape__11__);
		Pointer_interior_kernel_11 = l_Pointer_interior_kernel_11;
	
		_Pointer_interior_kernel_12 = new __Pointer_interior_kernel_12__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_12), 2 >  * l_Pointer_interior_kernel_12 = NULL;
		l_Pointer_interior_kernel_12 = new Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_12), 2 > ((*_Pointer_interior_kernel_12), __POCHOIR_Shape__12__);
		Pointer_interior_kernel_12 = l_Pointer_interior_kernel_12;
	
		_Pointer_interior_kernel_13 = new __Pointer_interior_kernel_13__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_13), 2 >  * l_Pointer_interior_kernel_13 = NULL;
		l_Pointer_interior_kernel_13 = new Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_13), 2 > ((*_Pointer_interior_kernel_13), __POCHOIR_Shape__13__);
		Pointer_interior_kernel_13 = l_Pointer_interior_kernel_13;
	
		_Pointer_interior_kernel_14 = new __Pointer_interior_kernel_14__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_14), 2 >  * l_Pointer_interior_kernel_14 = NULL;
		l_Pointer_interior_kernel_14 = new Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_14), 2 > ((*_Pointer_interior_kernel_14), __POCHOIR_Shape__14__);
		Pointer_interior_kernel_14 = l_Pointer_interior_kernel_14;
	
		_Pointer_interior_kernel_15 = new __Pointer_interior_kernel_15__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_15), 2 >  * l_Pointer_interior_kernel_15 = NULL;
		l_Pointer_interior_kernel_15 = new Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_15), 2 > ((*_Pointer_interior_kernel_15), __POCHOIR_Shape__15__);
		Pointer_interior_kernel_15 = l_Pointer_interior_kernel_15;
	
		_Pointer_cond_interior_kernel_0 = new __Pointer_cond_interior_kernel_0__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_0), 2 >  * l_Pointer_cond_interior_kernel_0 = NULL;
		l_Pointer_cond_interior_kernel_0 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_0), 2 > ((*_Pointer_cond_interior_kernel_0), __POCHOIR_Shape__0__);
		Pointer_cond_interior_kernel_0 = l_Pointer_cond_interior_kernel_0;
	
		_Pointer_cond_interior_kernel_1 = new __Pointer_cond_interior_kernel_1__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_1), 2 >  * l_Pointer_cond_interior_kernel_1 = NULL;
		l_Pointer_cond_interior_kernel_1 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_1), 2 > ((*_Pointer_cond_interior_kernel_1), __POCHOIR_Shape__1__);
		Pointer_cond_interior_kernel_1 = l_Pointer_cond_interior_kernel_1;
	
		_Pointer_cond_interior_kernel_2 = new __Pointer_cond_interior_kernel_2__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_2), 2 >  * l_Pointer_cond_interior_kernel_2 = NULL;
		l_Pointer_cond_interior_kernel_2 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_2), 2 > ((*_Pointer_cond_interior_kernel_2), __POCHOIR_Shape__2__);
		Pointer_cond_interior_kernel_2 = l_Pointer_cond_interior_kernel_2;
	
		_Pointer_cond_interior_kernel_3 = new __Pointer_cond_interior_kernel_3__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_3), 2 >  * l_Pointer_cond_interior_kernel_3 = NULL;
		l_Pointer_cond_interior_kernel_3 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_3), 2 > ((*_Pointer_cond_interior_kernel_3), __POCHOIR_Shape__3__);
		Pointer_cond_interior_kernel_3 = l_Pointer_cond_interior_kernel_3;
	
		_Pointer_cond_interior_kernel_4 = new __Pointer_cond_interior_kernel_4__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_4), 2 >  * l_Pointer_cond_interior_kernel_4 = NULL;
		l_Pointer_cond_interior_kernel_4 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_4), 2 > ((*_Pointer_cond_interior_kernel_4), __POCHOIR_Shape__4__);
		Pointer_cond_interior_kernel_4 = l_Pointer_cond_interior_kernel_4;
	
		_Pointer_cond_interior_kernel_5 = new __Pointer_cond_interior_kernel_5__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_5), 2 >  * l_Pointer_cond_interior_kernel_5 = NULL;
		l_Pointer_cond_interior_kernel_5 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_5), 2 > ((*_Pointer_cond_interior_kernel_5), __POCHOIR_Shape__5__);
		Pointer_cond_interior_kernel_5 = l_Pointer_cond_interior_kernel_5;
	
		_Pointer_cond_interior_kernel_6 = new __Pointer_cond_interior_kernel_6__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_6), 2 >  * l_Pointer_cond_interior_kernel_6 = NULL;
		l_Pointer_cond_interior_kernel_6 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_6), 2 > ((*_Pointer_cond_interior_kernel_6), __POCHOIR_Shape__6__);
		Pointer_cond_interior_kernel_6 = l_Pointer_cond_interior_kernel_6;
	
		_Pointer_cond_interior_kernel_7 = new __Pointer_cond_interior_kernel_7__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_7), 2 >  * l_Pointer_cond_interior_kernel_7 = NULL;
		l_Pointer_cond_interior_kernel_7 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_7), 2 > ((*_Pointer_cond_interior_kernel_7), __POCHOIR_Shape__7__);
		Pointer_cond_interior_kernel_7 = l_Pointer_cond_interior_kernel_7;
	
		_Pointer_cond_interior_kernel_8 = new __Pointer_cond_interior_kernel_8__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_8), 2 >  * l_Pointer_cond_interior_kernel_8 = NULL;
		l_Pointer_cond_interior_kernel_8 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_8), 2 > ((*_Pointer_cond_interior_kernel_8), __POCHOIR_Shape__8__);
		Pointer_cond_interior_kernel_8 = l_Pointer_cond_interior_kernel_8;
	
		_Pointer_cond_interior_kernel_9 = new __Pointer_cond_interior_kernel_9__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_9), 2 >  * l_Pointer_cond_interior_kernel_9 = NULL;
		l_Pointer_cond_interior_kernel_9 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_9), 2 > ((*_Pointer_cond_interior_kernel_9), __POCHOIR_Shape__9__);
		Pointer_cond_interior_kernel_9 = l_Pointer_cond_interior_kernel_9;
	
		_Pointer_cond_interior_kernel_10 = new __Pointer_cond_interior_kernel_10__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_10), 2 >  * l_Pointer_cond_interior_kernel_10 = NULL;
		l_Pointer_cond_interior_kernel_10 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_10), 2 > ((*_Pointer_cond_interior_kernel_10), __POCHOIR_Shape__10__);
		Pointer_cond_interior_kernel_10 = l_Pointer_cond_interior_kernel_10;
	
		_Pointer_cond_interior_kernel_11 = new __Pointer_cond_interior_kernel_11__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_11), 2 >  * l_Pointer_cond_interior_kernel_11 = NULL;
		l_Pointer_cond_interior_kernel_11 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_11), 2 > ((*_Pointer_cond_interior_kernel_11), __POCHOIR_Shape__11__);
		Pointer_cond_interior_kernel_11 = l_Pointer_cond_interior_kernel_11;
	
		_Pointer_cond_interior_kernel_12 = new __Pointer_cond_interior_kernel_12__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_12), 2 >  * l_Pointer_cond_interior_kernel_12 = NULL;
		l_Pointer_cond_interior_kernel_12 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_12), 2 > ((*_Pointer_cond_interior_kernel_12), __POCHOIR_Shape__12__);
		Pointer_cond_interior_kernel_12 = l_Pointer_cond_interior_kernel_12;
	
		_Pointer_cond_interior_kernel_13 = new __Pointer_cond_interior_kernel_13__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_13), 2 >  * l_Pointer_cond_interior_kernel_13 = NULL;
		l_Pointer_cond_interior_kernel_13 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_13), 2 > ((*_Pointer_cond_interior_kernel_13), __POCHOIR_Shape__13__);
		Pointer_cond_interior_kernel_13 = l_Pointer_cond_interior_kernel_13;
	
		_Pointer_cond_interior_kernel_14 = new __Pointer_cond_interior_kernel_14__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_14), 2 >  * l_Pointer_cond_interior_kernel_14 = NULL;
		l_Pointer_cond_interior_kernel_14 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_14), 2 > ((*_Pointer_cond_interior_kernel_14), __POCHOIR_Shape__14__);
		Pointer_cond_interior_kernel_14 = l_Pointer_cond_interior_kernel_14;
	
		_Pointer_cond_interior_kernel_15 = new __Pointer_cond_interior_kernel_15__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_15), 2 >  * l_Pointer_cond_interior_kernel_15 = NULL;
		l_Pointer_cond_interior_kernel_15 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_15), 2 > ((*_Pointer_cond_interior_kernel_15), __POCHOIR_Shape__15__);
		Pointer_cond_interior_kernel_15 = l_Pointer_cond_interior_kernel_15;
	
		return 0;
	}

	extern "C" 
	int Destroy_Lambdas (void) { 
	
		delete _Pointer_boundary_kernel_0;
		delete Pointer_boundary_kernel_0;
		delete _Pointer_boundary_kernel_1;
		delete Pointer_boundary_kernel_1;
		delete _Pointer_boundary_kernel_2;
		delete Pointer_boundary_kernel_2;
		delete _Pointer_boundary_kernel_3;
		delete Pointer_boundary_kernel_3;
		delete _Pointer_boundary_kernel_4;
		delete Pointer_boundary_kernel_4;
		delete _Pointer_boundary_kernel_5;
		delete Pointer_boundary_kernel_5;
		delete _Pointer_boundary_kernel_6;
		delete Pointer_boundary_kernel_6;
		delete _Pointer_boundary_kernel_7;
		delete Pointer_boundary_kernel_7;
		delete _Pointer_boundary_kernel_8;
		delete Pointer_boundary_kernel_8;
		delete _Pointer_boundary_kernel_9;
		delete Pointer_boundary_kernel_9;
		delete _Pointer_boundary_kernel_10;
		delete Pointer_boundary_kernel_10;
		delete _Pointer_boundary_kernel_11;
		delete Pointer_boundary_kernel_11;
		delete _Pointer_boundary_kernel_12;
		delete Pointer_boundary_kernel_12;
		delete _Pointer_boundary_kernel_13;
		delete Pointer_boundary_kernel_13;
		delete _Pointer_boundary_kernel_14;
		delete Pointer_boundary_kernel_14;
		delete _Pointer_boundary_kernel_15;
		delete Pointer_boundary_kernel_15;
		delete _Pointer_cond_boundary_kernel_0;
		delete Pointer_cond_boundary_kernel_0;
		delete _Pointer_cond_boundary_kernel_1;
		delete Pointer_cond_boundary_kernel_1;
		delete _Pointer_cond_boundary_kernel_2;
		delete Pointer_cond_boundary_kernel_2;
		delete _Pointer_cond_boundary_kernel_3;
		delete Pointer_cond_boundary_kernel_3;
		delete _Pointer_cond_boundary_kernel_4;
		delete Pointer_cond_boundary_kernel_4;
		delete _Pointer_cond_boundary_kernel_5;
		delete Pointer_cond_boundary_kernel_5;
		delete _Pointer_cond_boundary_kernel_6;
		delete Pointer_cond_boundary_kernel_6;
		delete _Pointer_cond_boundary_kernel_7;
		delete Pointer_cond_boundary_kernel_7;
		delete _Pointer_cond_boundary_kernel_8;
		delete Pointer_cond_boundary_kernel_8;
		delete _Pointer_cond_boundary_kernel_9;
		delete Pointer_cond_boundary_kernel_9;
		delete _Pointer_cond_boundary_kernel_10;
		delete Pointer_cond_boundary_kernel_10;
		delete _Pointer_cond_boundary_kernel_11;
		delete Pointer_cond_boundary_kernel_11;
		delete _Pointer_cond_boundary_kernel_12;
		delete Pointer_cond_boundary_kernel_12;
		delete _Pointer_cond_boundary_kernel_13;
		delete Pointer_cond_boundary_kernel_13;
		delete _Pointer_cond_boundary_kernel_14;
		delete Pointer_cond_boundary_kernel_14;
		delete _Pointer_cond_boundary_kernel_15;
		delete Pointer_cond_boundary_kernel_15;
		delete _Pointer_interior_kernel_0;
		delete Pointer_interior_kernel_0;
		delete _Pointer_interior_kernel_1;
		delete Pointer_interior_kernel_1;
		delete _Pointer_interior_kernel_2;
		delete Pointer_interior_kernel_2;
		delete _Pointer_interior_kernel_3;
		delete Pointer_interior_kernel_3;
		delete _Pointer_interior_kernel_4;
		delete Pointer_interior_kernel_4;
		delete _Pointer_interior_kernel_5;
		delete Pointer_interior_kernel_5;
		delete _Pointer_interior_kernel_6;
		delete Pointer_interior_kernel_6;
		delete _Pointer_interior_kernel_7;
		delete Pointer_interior_kernel_7;
		delete _Pointer_interior_kernel_8;
		delete Pointer_interior_kernel_8;
		delete _Pointer_interior_kernel_9;
		delete Pointer_interior_kernel_9;
		delete _Pointer_interior_kernel_10;
		delete Pointer_interior_kernel_10;
		delete _Pointer_interior_kernel_11;
		delete Pointer_interior_kernel_11;
		delete _Pointer_interior_kernel_12;
		delete Pointer_interior_kernel_12;
		delete _Pointer_interior_kernel_13;
		delete Pointer_interior_kernel_13;
		delete _Pointer_interior_kernel_14;
		delete Pointer_interior_kernel_14;
		delete _Pointer_interior_kernel_15;
		delete Pointer_interior_kernel_15;
		delete _Pointer_cond_interior_kernel_0;
		delete Pointer_cond_interior_kernel_0;
		delete _Pointer_cond_interior_kernel_1;
		delete Pointer_cond_interior_kernel_1;
		delete _Pointer_cond_interior_kernel_2;
		delete Pointer_cond_interior_kernel_2;
		delete _Pointer_cond_interior_kernel_3;
		delete Pointer_cond_interior_kernel_3;
		delete _Pointer_cond_interior_kernel_4;
		delete Pointer_cond_interior_kernel_4;
		delete _Pointer_cond_interior_kernel_5;
		delete Pointer_cond_interior_kernel_5;
		delete _Pointer_cond_interior_kernel_6;
		delete Pointer_cond_interior_kernel_6;
		delete _Pointer_cond_interior_kernel_7;
		delete Pointer_cond_interior_kernel_7;
		delete _Pointer_cond_interior_kernel_8;
		delete Pointer_cond_interior_kernel_8;
		delete _Pointer_cond_interior_kernel_9;
		delete Pointer_cond_interior_kernel_9;
		delete _Pointer_cond_interior_kernel_10;
		delete Pointer_cond_interior_kernel_10;
		delete _Pointer_cond_interior_kernel_11;
		delete Pointer_cond_interior_kernel_11;
		delete _Pointer_cond_interior_kernel_12;
		delete Pointer_cond_interior_kernel_12;
		delete _Pointer_cond_interior_kernel_13;
		delete Pointer_cond_interior_kernel_13;
		delete _Pointer_cond_interior_kernel_14;
		delete Pointer_cond_interior_kernel_14;
		delete _Pointer_cond_interior_kernel_15;
		delete Pointer_cond_interior_kernel_15;
		return 0;
	}
	extern "C" 
	int Register_Lambdas (Pochoir < 2 > & leap_frog) { 
		leap_frog.Register_Tile_Obase_Kernels(POCHOIR_Guard_0, 2, (*Pointer_interior_kernel_0), (*Pointer_cond_interior_kernel_0), (*Pointer_boundary_kernel_0), (*Pointer_cond_boundary_kernel_0));
		leap_frog.Register_Tile_Obase_Kernels(POCHOIR_Guard_1, 2, (*Pointer_interior_kernel_1), (*Pointer_cond_interior_kernel_1), (*Pointer_boundary_kernel_1), (*Pointer_cond_boundary_kernel_1));
		leap_frog.Register_Tile_Obase_Kernels(POCHOIR_Guard_2, 2, (*Pointer_interior_kernel_2), (*Pointer_cond_interior_kernel_2), (*Pointer_boundary_kernel_2), (*Pointer_cond_boundary_kernel_2));
		leap_frog.Register_Tile_Obase_Kernels(POCHOIR_Guard_3, 2, (*Pointer_interior_kernel_3), (*Pointer_cond_interior_kernel_3), (*Pointer_boundary_kernel_3), (*Pointer_cond_boundary_kernel_3));
		leap_frog.Register_Tile_Obase_Kernels(POCHOIR_Guard_4, 2, (*Pointer_interior_kernel_4), (*Pointer_cond_interior_kernel_4), (*Pointer_boundary_kernel_4), (*Pointer_cond_boundary_kernel_4));
		leap_frog.Register_Tile_Obase_Kernels(POCHOIR_Guard_5, 2, (*Pointer_interior_kernel_5), (*Pointer_cond_interior_kernel_5), (*Pointer_boundary_kernel_5), (*Pointer_cond_boundary_kernel_5));
		leap_frog.Register_Tile_Obase_Kernels(POCHOIR_Guard_6, 2, (*Pointer_interior_kernel_6), (*Pointer_cond_interior_kernel_6), (*Pointer_boundary_kernel_6), (*Pointer_cond_boundary_kernel_6));
		leap_frog.Register_Tile_Obase_Kernels(POCHOIR_Guard_7, 2, (*Pointer_interior_kernel_7), (*Pointer_cond_interior_kernel_7), (*Pointer_boundary_kernel_7), (*Pointer_cond_boundary_kernel_7));
		leap_frog.Register_Tile_Obase_Kernels(POCHOIR_Guard_8, 2, (*Pointer_interior_kernel_8), (*Pointer_cond_interior_kernel_8), (*Pointer_boundary_kernel_8), (*Pointer_cond_boundary_kernel_8));
		leap_frog.Register_Tile_Obase_Kernels(POCHOIR_Guard_9, 2, (*Pointer_interior_kernel_9), (*Pointer_cond_interior_kernel_9), (*Pointer_boundary_kernel_9), (*Pointer_cond_boundary_kernel_9));
		leap_frog.Register_Tile_Obase_Kernels(POCHOIR_Guard_10, 2, (*Pointer_interior_kernel_10), (*Pointer_cond_interior_kernel_10), (*Pointer_boundary_kernel_10), (*Pointer_cond_boundary_kernel_10));
		leap_frog.Register_Tile_Obase_Kernels(POCHOIR_Guard_11, 2, (*Pointer_interior_kernel_11), (*Pointer_cond_interior_kernel_11), (*Pointer_boundary_kernel_11), (*Pointer_cond_boundary_kernel_11));
		leap_frog.Register_Tile_Obase_Kernels(POCHOIR_Guard_12, 2, (*Pointer_interior_kernel_12), (*Pointer_cond_interior_kernel_12), (*Pointer_boundary_kernel_12), (*Pointer_cond_boundary_kernel_12));
		leap_frog.Register_Tile_Obase_Kernels(POCHOIR_Guard_13, 2, (*Pointer_interior_kernel_13), (*Pointer_cond_interior_kernel_13), (*Pointer_boundary_kernel_13), (*Pointer_cond_boundary_kernel_13));
		leap_frog.Register_Tile_Obase_Kernels(POCHOIR_Guard_14, 2, (*Pointer_interior_kernel_14), (*Pointer_cond_interior_kernel_14), (*Pointer_boundary_kernel_14), (*Pointer_cond_boundary_kernel_14));
		leap_frog.Register_Tile_Obase_Kernels(POCHOIR_Guard_15, 2, (*Pointer_interior_kernel_15), (*Pointer_cond_interior_kernel_15), (*Pointer_boundary_kernel_15), (*Pointer_cond_boundary_kernel_15));
	
		return 0;
	}
	
	extern "C" {
		void *__dso_handle = NULL;
	}
