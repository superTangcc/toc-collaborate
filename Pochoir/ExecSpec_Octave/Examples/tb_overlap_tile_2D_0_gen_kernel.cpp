
	/* Pochoir_Kernel <1> tile_exclusive_0[ 2 ][ 2 ] = {{k_exclusive_0_0, k_exclusive_0_1}, {k_exclusive_0_2, k_exclusive_0_3}}; */
	/* k_exclusive_0_0[0,0]; k_exclusive_0_1[0,1]; k_exclusive_0_2[1,0]; k_exclusive_0_3[1,1] */
	
	/* Pochoir_Kernel <1> tile_exclusive_1[ 2 ] = {k_exclusive_1_0, k_exclusive_1_1}; */
	/* k_exclusive_1_0[0]; k_exclusive_1_1[1] */
	
	/* Pochoir_Kernel <1> tile_inclusive_0[ 2 ][ 2 ] = {{k_inclusive_0_0, k_inclusive_0_1}, {k_inclusive_0_2, k_inclusive_0_3}}; */
	/* k_inclusive_0_0[0,0]; k_inclusive_0_1[0,1]; k_inclusive_0_2[1,0]; k_inclusive_0_3[1,1] */
	
	/* Pochoir_Kernel <1> tile_inclusive_1[ 2 ] = {k_inclusive_1_0, k_inclusive_1_1}; */
	/* k_inclusive_1_0[0]; k_inclusive_1_1[1] */
	
	/* Pochoir_Kernel <1> tile_tiny_inclusive_0[ 2 ][ 2 ] = {{k_tiny_inclusive_0_0, k_tiny_inclusive_0_1}, {k_tiny_inclusive_0_2, k_tiny_inclusive_0_3}}; */
	/* k_tiny_inclusive_0_0[0,0]; k_tiny_inclusive_0_1[0,1]; k_tiny_inclusive_0_2[1,0]; k_tiny_inclusive_0_3[1,1] */
	
	/* Pochoir_Kernel <1> tile_tiny_inclusive_1[ 2 ] = {k_tiny_inclusive_1_0, k_tiny_inclusive_1_1}; */
	/* k_tiny_inclusive_1_0[0]; k_tiny_inclusive_1_1[1] */
	
	
	#include <cstdio>
	#include <cstdlib>
	#include <cassert>
	#include <pochoir.hpp>
	
	/* Original Codes */
	/* known Guard ! */ auto __g_exclusive_0__ = [&] (int t, int i) -> bool {
	if (((i < 20 / 2))) {
	{return ((true));
	
	
	}
	} else {{return ((false));
	
	
	}}
	
	};
	/* known Guard ! */ auto __g_exclusive_1__ = [&] (int t, int i) -> bool {
	if (((i >= 20 / 2))) {
	{return ((true));
	
	
	}
	} else {{return ((false));
	
	
	}}
	
	};
	/* known Guard ! */ auto __g_inclusive_0__ = [&] (int t, int i) -> bool {
	if (((i < 20 / 2 && t < 10 / 2))) {
	{return ((true));
	
	
	}
	} else {{return ((false));
	
	
	}}
	
	};
	/* known Guard ! */ auto __g_inclusive_1__ = [&] (int t, int i) -> bool {
	if (((i >= 20 / 4 && i < 20 / 3 && t < 10 * 2 / 3))) {
	{return ((true));
	
	
	}
	} else {{return ((false));
	
	
	}}
	
	};
	/* known Guard ! */ auto __g_tiny_inclusive_0__ = [&] (int t, int i) -> bool {
	if (((i >= 1 && i < 5 && t > 1 && t <= 2))) {
	{return ((true));
	
	
	}
	} else {{return ((false));
	
	
	}}
	
	};
	/* known Guard ! */ auto __g_tiny_inclusive_1__ = [&] (int t, int i) -> bool {
	if (((i > 5 && i <= 10 && t > 2 && t < 4))) {
	{return ((true));
	
	
	}
	} else {{return ((false));
	
	
	}}
	
	};
	
	/* Generated Codes */
	
	/* 
	[<110000, 000000>
,<010000, 010000>
,<111100, 000000>
,<111001, 000000>
,<101111, 101000>
,<111010, 000000>
,<111000, 000000>
,<101100, 100000>
,<100000, 100000>
,<111111, 000000>
]
	 */
	
	
	/* <110000, 000000>
 */
	auto __POCHOIR_Guard_0__ = [&]  ( int t, int i0 )  -> bool {
	return ( !__g_inclusive_0__ ( t + -1, i0 )  && !__g_inclusive_1__ ( t + -1, i0 )  && !__g_tiny_inclusive_0__ ( t + -1, i0 )  && !__g_tiny_inclusive_1__ ( t + -1, i0 )  );
	 };
	static Pochoir_Guard <1> POCHOIR_Guard_0 ( __POCHOIR_Guard_0__ ); 

	/* <110000, 000000>
 */
	
	
	/* 
	tile_exclusive_0 - PINCLUSIVE;
	tile_exclusive_1 - PINCLUSIVE;
	__Pochoir_NULL__ - PNULL
	 */
	/* k_exclusive_0_0, k_exclusive_0_1, k_exclusive_0_2, k_exclusive_0_3, k_exclusive_1_0, k_exclusive_1_1, __Pochoir_NULL_ */ 
	/* 0, 0, 0, 0, 1, 1, 0 */ 
	/* PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PNULL */ 
	/* [0,0], [0,1], [1,0], [1,1], [0], [1], [0] */ 
	/* [2,2], [2,2], [2,2], [2,2], [2], [2], [1] */ 
	/* 
	PMTile (sizes = [2,2], latest_tile_order = 1), terms = 
		PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 1), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_exclusive_0_0
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_exclusive_0_1
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 1), item = k_exclusive_1_0
		PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 1), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_exclusive_0_2
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_exclusive_0_3
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 1), item = k_exclusive_1_1
	 */ 
	static 
	Pochoir_Shape <1> __POCHOIR_Shape__0__ [ ] = {{0, 0}, {-1, -1}, {-1, 0}, {-1, 1}};
	/* toggle: 2; slopes: [] */
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_cond_boundary_kernel_0__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_cond_boundary_kernel_0__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11000000000000001 * a(t - 1, i - 1) + 0.15 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11100000000000003 * a(t - 1, i - 1) + 0.151 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.21000000000000002 * a(t - 1, i - 1) + 0.25 * a(t - 1, i) + 0.28500000000000003 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11200000000000002 * a(t - 1, i - 1) + 0.152 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11299999999999999 * a(t - 1, i - 1) + 0.153 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.21200000000000002 * a(t - 1, i - 1) + 0.252 * a(t - 1, i) + 0.28500000000000003 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	}
	
	} 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	} /* end for t */
	}
	};
	static __Pointer_cond_boundary_kernel_0__ * _Pointer_cond_boundary_kernel_0 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_cond_boundary_kernel_0 = NULL;
	#undef pmod_lu
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_boundary_kernel_0__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_boundary_kernel_0__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11000000000000001 * a(t - 1, i - 1) + 0.15 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11100000000000003 * a(t - 1, i - 1) + 0.151 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.21000000000000002 * a(t - 1, i - 1) + 0.25 * a(t - 1, i) + 0.28500000000000003 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	
	} 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	++t;
	}
	{
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11200000000000002 * a(t - 1, i - 1) + 0.152 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11299999999999999 * a(t - 1, i - 1) + 0.153 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.21200000000000002 * a(t - 1, i - 1) + 0.252 * a(t - 1, i) + 0.28500000000000003 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	
	} 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	
	}
	} /* end for t */
	}
	};
	static __Pointer_boundary_kernel_0__ * _Pointer_boundary_kernel_0 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_boundary_kernel_0 = NULL;
	#undef pmod_lu
	
	
	
	/* KNOWN */
	class __Pointer_cond_interior_kernel_0__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_cond_interior_kernel_0__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	
	
	#pragma ivdep
	for (int i = l_grid.x0[0]; i < l_grid.x1[0]; ++i, 
	++pt_a_0, 
	++pt_a_1) {
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11000000000000001 * pt_a_1[l_a_stride_0 * (-1)] + 0.15 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11100000000000003 * pt_a_1[l_a_stride_0 * (-1)] + 0.151 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8099999999999999;
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21000000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.25 * pt_a_1[0] + 0.28500000000000003 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.152 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11299999999999999 * pt_a_1[l_a_stride_0 * (-1)] + 0.153 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8300000000000001;
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.252 * pt_a_1[0] + 0.28500000000000003 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	}
	
	} /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	} /* end for t */
	}
	};
	static __Pointer_cond_interior_kernel_0__ * _Pointer_cond_interior_kernel_0 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_cond_interior_kernel_0 = NULL;
	
	
	
	
	/* KNOWN */
	class __Pointer_interior_kernel_0__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_interior_kernel_0__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	
	
	#pragma ivdep
	for (int i = l_grid.x0[0]; i < l_grid.x1[0]; ++i, 
	++pt_a_0, 
	++pt_a_1) {
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11000000000000001 * pt_a_1[l_a_stride_0 * (-1)] + 0.15 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11100000000000003 * pt_a_1[l_a_stride_0 * (-1)] + 0.151 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8099999999999999;
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21000000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.25 * pt_a_1[0] + 0.28500000000000003 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	
	} /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	++t;
	}
	{
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	
	
	#pragma ivdep
	for (int i = l_grid.x0[0]; i < l_grid.x1[0]; ++i, 
	++pt_a_0, 
	++pt_a_1) {
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.152 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11299999999999999 * pt_a_1[l_a_stride_0 * (-1)] + 0.153 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8300000000000001;
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.252 * pt_a_1[0] + 0.28500000000000003 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	
	} /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	
	}
	} /* end for t */
	}
	};
	static __Pointer_interior_kernel_0__ * _Pointer_interior_kernel_0 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_interior_kernel_0 = NULL;
	
	
	
	/* <010000, 010000>
 */
	auto __POCHOIR_Guard_1__ = [&]  ( int t, int i0 )  -> bool {
	return ( !__g_exclusive_0__ ( t + -1, i0 )  && __g_exclusive_1__ ( t + -1, i0 )  && !__g_inclusive_0__ ( t + -1, i0 )  && !__g_inclusive_1__ ( t + -1, i0 )  && !__g_tiny_inclusive_0__ ( t + -1, i0 )  && !__g_tiny_inclusive_1__ ( t + -1, i0 )  );
	 };
	static Pochoir_Guard <1> POCHOIR_Guard_1 ( __POCHOIR_Guard_1__ ); 

	/* <010000, 010000>
 */
	
	
	/* 
	tile_exclusive_1 - PSERIAL;
	__Pochoir_NULL__ - PNULL
	 */
	/* k_exclusive_1_0, k_exclusive_1_1, __Pochoir_NULL_ */ 
	/* 1, 1, 0 */ 
	/* PSERIAL, PSERIAL, PNULL */ 
	/* [0], [1], [0] */ 
	/* [2], [2], [1] */ 
	/* 
	PMTile (sizes = [2], latest_tile_order = 1), terms = 
		PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 1), item = k_exclusive_1_0
		PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 1), item = k_exclusive_1_1
	 */ 
	static 
	Pochoir_Shape <1> __POCHOIR_Shape__1__ [ ] = {{0, 0}, {-1, -1}, {-1, 0}, {-1, 1}};
	/* toggle: 2; slopes: [] */
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_cond_boundary_kernel_1__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_cond_boundary_kernel_1__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	if (((t + -1) & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.21000000000000002 * a(t - 1, i - 1) + 0.25 * a(t - 1, i) + 0.28500000000000003 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.21200000000000002 * a(t - 1, i - 1) + 0.252 * a(t - 1, i) + 0.28500000000000003 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	}
	
	} 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	} /* end for t */
	}
	};
	static __Pointer_cond_boundary_kernel_1__ * _Pointer_cond_boundary_kernel_1 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_cond_boundary_kernel_1 = NULL;
	#undef pmod_lu
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_boundary_kernel_1__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_boundary_kernel_1__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.21000000000000002 * a(t - 1, i - 1) + 0.25 * a(t - 1, i) + 0.28500000000000003 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	
	} 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	++t;
	}
	{
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.21200000000000002 * a(t - 1, i - 1) + 0.252 * a(t - 1, i) + 0.28500000000000003 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	
	} 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	
	}
	} /* end for t */
	}
	};
	static __Pointer_boundary_kernel_1__ * _Pointer_boundary_kernel_1 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_boundary_kernel_1 = NULL;
	#undef pmod_lu
	
	
	
	/* KNOWN */
	class __Pointer_cond_interior_kernel_1__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_cond_interior_kernel_1__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	
	
	#pragma ivdep
	for (int i = l_grid.x0[0]; i < l_grid.x1[0]; ++i, 
	++pt_a_0, 
	++pt_a_1) {
	
	if (((t + -1) & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.21000000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.25 * pt_a_1[0] + 0.28500000000000003 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.21200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.252 * pt_a_1[0] + 0.28500000000000003 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	}
	
	} /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	} /* end for t */
	}
	};
	static __Pointer_cond_interior_kernel_1__ * _Pointer_cond_interior_kernel_1 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_cond_interior_kernel_1 = NULL;
	
	
	
	
	/* KNOWN */
	class __Pointer_interior_kernel_1__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_interior_kernel_1__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	
	
	#pragma ivdep
	for (int i = l_grid.x0[0]; i < l_grid.x1[0]; ++i, 
	++pt_a_0, 
	++pt_a_1) {
	
	
	
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.21000000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.25 * pt_a_1[0] + 0.28500000000000003 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	
	} /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	++t;
	}
	{
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	
	
	#pragma ivdep
	for (int i = l_grid.x0[0]; i < l_grid.x1[0]; ++i, 
	++pt_a_0, 
	++pt_a_1) {
	
	
	
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.21200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.252 * pt_a_1[0] + 0.28500000000000003 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	
	} /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	
	}
	} /* end for t */
	}
	};
	static __Pointer_interior_kernel_1__ * _Pointer_interior_kernel_1 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_interior_kernel_1 = NULL;
	
	
	
	/* <111100, 000000>
 */
	auto __POCHOIR_Guard_2__ = [&]  ( int t, int i0 )  -> bool {
	return ( !__g_tiny_inclusive_0__ ( t + -1, i0 )  && !__g_tiny_inclusive_1__ ( t + -1, i0 )  );
	 };
	static Pochoir_Guard <1> POCHOIR_Guard_2 ( __POCHOIR_Guard_2__ ); 

	/* <111100, 000000>
 */
	
	
	/* 
	tile_exclusive_0 - PINCLUSIVE;
	tile_exclusive_1 - PINCLUSIVE;
	tile_inclusive_0 - PINCLUSIVE;
	tile_inclusive_1 - PINCLUSIVE;
	__Pochoir_NULL__ - PNULL
	 */
	/* k_exclusive_0_0, k_exclusive_0_1, k_exclusive_0_2, k_exclusive_0_3, k_exclusive_1_0, k_exclusive_1_1, k_inclusive_0_0, k_inclusive_0_1, k_inclusive_0_2, k_inclusive_0_3, k_inclusive_1_0, k_inclusive_1_1, __Pochoir_NULL_ */ 
	/* 0, 0, 0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 0 */ 
	/* PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PNULL */ 
	/* [0,0], [0,1], [1,0], [1,1], [0], [1], [0,0], [0,1], [1,0], [1,1], [0], [1], [0] */ 
	/* [2,2], [2,2], [2,2], [2,2], [2], [2], [2,2], [2,2], [2,2], [2,2], [2], [2], [1] */ 
	/* 
	PMTile (sizes = [2,2], latest_tile_order = 3), terms = 
		PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_exclusive_0_0
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_exclusive_0_1
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 1), item = k_exclusive_1_0
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 2), item = k_inclusive_0_0
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 2), item = k_inclusive_0_1
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 3), item = k_inclusive_1_0
		PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_exclusive_0_2
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_exclusive_0_3
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 1), item = k_exclusive_1_1
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 2), item = k_inclusive_0_2
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 2), item = k_inclusive_0_3
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 3), item = k_inclusive_1_1
	 */ 
	static 
	Pochoir_Shape <1> __POCHOIR_Shape__2__ [ ] = {{0, 0}, {-1, -1}, {-1, 0}, {-1, 1}};
	/* toggle: 2; slopes: [] */
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_cond_boundary_kernel_2__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_cond_boundary_kernel_2__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11000000000000001 * a(t - 1, i - 1) + 0.15 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11100000000000003 * a(t - 1, i - 1) + 0.151 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.21000000000000002 * a(t - 1, i - 1) + 0.25 * a(t - 1, i) + 0.28500000000000003 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.31 * a(t - 1, i - 1) - 0.35 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.311 * a(t - 1, i - 1) - 0.351 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.41 * a(t - 1, i - 1) - 0.45 * a(t - 1, i) + 0.485 * a(t - 1, i + 1) - 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11200000000000002 * a(t - 1, i - 1) + 0.152 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11299999999999999 * a(t - 1, i - 1) + 0.153 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.21200000000000002 * a(t - 1, i - 1) + 0.252 * a(t - 1, i) + 0.28500000000000003 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.312 * a(t - 1, i - 1) - 0.352 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.313 * a(t - 1, i - 1) - 0.35300000000000004 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.414 * a(t - 1, i - 1) - 0.454 * a(t - 1, i) + 0.485 * a(t - 1, i + 1) - 0.8400000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	} 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	} /* end for t */
	}
	};
	static __Pointer_cond_boundary_kernel_2__ * _Pointer_cond_boundary_kernel_2 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_cond_boundary_kernel_2 = NULL;
	#undef pmod_lu
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_boundary_kernel_2__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_boundary_kernel_2__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11000000000000001 * a(t - 1, i - 1) + 0.15 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11100000000000003 * a(t - 1, i - 1) + 0.151 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.21000000000000002 * a(t - 1, i - 1) + 0.25 * a(t - 1, i) + 0.28500000000000003 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.31 * a(t - 1, i - 1) - 0.35 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.311 * a(t - 1, i - 1) - 0.351 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.41 * a(t - 1, i - 1) - 0.45 * a(t - 1, i) + 0.485 * a(t - 1, i + 1) - 0.8;
	
	
	#undef a(t, i)
	}
	
	
	} 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	++t;
	}
	{
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11200000000000002 * a(t - 1, i - 1) + 0.152 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11299999999999999 * a(t - 1, i - 1) + 0.153 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.21200000000000002 * a(t - 1, i - 1) + 0.252 * a(t - 1, i) + 0.28500000000000003 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.312 * a(t - 1, i - 1) - 0.352 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.313 * a(t - 1, i - 1) - 0.35300000000000004 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.414 * a(t - 1, i - 1) - 0.454 * a(t - 1, i) + 0.485 * a(t - 1, i + 1) - 0.8400000000000001;
	
	
	#undef a(t, i)
	}
	
	
	} 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	
	}
	} /* end for t */
	}
	};
	static __Pointer_boundary_kernel_2__ * _Pointer_boundary_kernel_2 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_boundary_kernel_2 = NULL;
	#undef pmod_lu
	
	
	
	/* KNOWN */
	class __Pointer_cond_interior_kernel_2__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_cond_interior_kernel_2__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	
	
	#pragma ivdep
	for (int i = l_grid.x0[0]; i < l_grid.x1[0]; ++i, 
	++pt_a_0, 
	++pt_a_1) {
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11000000000000001 * pt_a_1[l_a_stride_0 * (-1)] + 0.15 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11100000000000003 * pt_a_1[l_a_stride_0 * (-1)] + 0.151 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8099999999999999;
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21000000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.25 * pt_a_1[0] + 0.28500000000000003 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.31 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.311 * pt_a_1[l_a_stride_0 * (-1)] - 0.351 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8099999999999999;
	
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.41 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] + 0.485 * pt_a_1[l_a_stride_0 * (1)] - 0.8;
	
	}
	
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.152 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11299999999999999 * pt_a_1[l_a_stride_0 * (-1)] + 0.153 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8300000000000001;
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.252 * pt_a_1[0] + 0.28500000000000003 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.312 * pt_a_1[l_a_stride_0 * (-1)] - 0.352 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.313 * pt_a_1[l_a_stride_0 * (-1)] - 0.35300000000000004 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8300000000000001;
	
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.414 * pt_a_1[l_a_stride_0 * (-1)] - 0.454 * pt_a_1[0] + 0.485 * pt_a_1[l_a_stride_0 * (1)] - 0.8400000000000001;
	
	}
	
	}
	
	} /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	} /* end for t */
	}
	};
	static __Pointer_cond_interior_kernel_2__ * _Pointer_cond_interior_kernel_2 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_cond_interior_kernel_2 = NULL;
	
	
	
	
	/* KNOWN */
	class __Pointer_interior_kernel_2__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_interior_kernel_2__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	
	
	#pragma ivdep
	for (int i = l_grid.x0[0]; i < l_grid.x1[0]; ++i, 
	++pt_a_0, 
	++pt_a_1) {
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11000000000000001 * pt_a_1[l_a_stride_0 * (-1)] + 0.15 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11100000000000003 * pt_a_1[l_a_stride_0 * (-1)] + 0.151 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8099999999999999;
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21000000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.25 * pt_a_1[0] + 0.28500000000000003 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.31 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.311 * pt_a_1[l_a_stride_0 * (-1)] - 0.351 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8099999999999999;
	
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.41 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] + 0.485 * pt_a_1[l_a_stride_0 * (1)] - 0.8;
	
	}
	
	
	} /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	++t;
	}
	{
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	
	
	#pragma ivdep
	for (int i = l_grid.x0[0]; i < l_grid.x1[0]; ++i, 
	++pt_a_0, 
	++pt_a_1) {
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.152 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11299999999999999 * pt_a_1[l_a_stride_0 * (-1)] + 0.153 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8300000000000001;
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.252 * pt_a_1[0] + 0.28500000000000003 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.312 * pt_a_1[l_a_stride_0 * (-1)] - 0.352 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.313 * pt_a_1[l_a_stride_0 * (-1)] - 0.35300000000000004 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8300000000000001;
	
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.414 * pt_a_1[l_a_stride_0 * (-1)] - 0.454 * pt_a_1[0] + 0.485 * pt_a_1[l_a_stride_0 * (1)] - 0.8400000000000001;
	
	}
	
	
	} /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	
	}
	} /* end for t */
	}
	};
	static __Pointer_interior_kernel_2__ * _Pointer_interior_kernel_2 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_interior_kernel_2 = NULL;
	
	
	
	/* <111001, 000000>
 */
	auto __POCHOIR_Guard_3__ = [&]  ( int t, int i0 )  -> bool {
	return ( !__g_inclusive_1__ ( t + -1, i0 )  && !__g_tiny_inclusive_0__ ( t + -1, i0 )  );
	 };
	static Pochoir_Guard <1> POCHOIR_Guard_3 ( __POCHOIR_Guard_3__ ); 

	/* <111001, 000000>
 */
	
	
	/* 
	tile_exclusive_0 - PINCLUSIVE;
	tile_exclusive_1 - PINCLUSIVE;
	tile_inclusive_0 - PINCLUSIVE;
	tile_tiny_inclusive_1 - PINCLUSIVE;
	__Pochoir_NULL__ - PNULL
	 */
	/* k_exclusive_0_0, k_exclusive_0_1, k_exclusive_0_2, k_exclusive_0_3, k_exclusive_1_0, k_exclusive_1_1, k_inclusive_0_0, k_inclusive_0_1, k_inclusive_0_2, k_inclusive_0_3, k_tiny_inclusive_1_0, k_tiny_inclusive_1_1, __Pochoir_NULL_ */ 
	/* 0, 0, 0, 0, 1, 1, 2, 2, 2, 2, 5, 5, 0 */ 
	/* PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PNULL */ 
	/* [0,0], [0,1], [1,0], [1,1], [0], [1], [0,0], [0,1], [1,0], [1,1], [0], [1], [0] */ 
	/* [2,2], [2,2], [2,2], [2,2], [2], [2], [2,2], [2,2], [2,2], [2,2], [2], [2], [1] */ 
	/* 
	PMTile (sizes = [2,2], latest_tile_order = 5), terms = 
		PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 5), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_exclusive_0_0
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_exclusive_0_1
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 1), item = k_exclusive_1_0
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 2), item = k_inclusive_0_0
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 2), item = k_inclusive_0_1
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 5), item = k_tiny_inclusive_1_0
		PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 5), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_exclusive_0_2
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_exclusive_0_3
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 1), item = k_exclusive_1_1
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 2), item = k_inclusive_0_2
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 2), item = k_inclusive_0_3
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 5), item = k_tiny_inclusive_1_1
	 */ 
	static 
	Pochoir_Shape <1> __POCHOIR_Shape__3__ [ ] = {{0, 0}, {-1, -1}, {-1, 0}, {-1, 1}};
	/* toggle: 2; slopes: [] */
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_cond_boundary_kernel_3__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_cond_boundary_kernel_3__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11000000000000001 * a(t - 1, i - 1) + 0.15 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11100000000000003 * a(t - 1, i - 1) + 0.151 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.21000000000000002 * a(t - 1, i - 1) + 0.25 * a(t - 1, i) + 0.28500000000000003 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.31 * a(t - 1, i - 1) - 0.35 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.311 * a(t - 1, i - 1) - 0.351 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.61 * a(t - 1, i - 1) + 0.65 * a(t - 1, i) - 0.6849999999999998 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11200000000000002 * a(t - 1, i - 1) + 0.152 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11299999999999999 * a(t - 1, i - 1) + 0.153 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.21200000000000002 * a(t - 1, i - 1) + 0.252 * a(t - 1, i) + 0.28500000000000003 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.312 * a(t - 1, i - 1) - 0.352 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.313 * a(t - 1, i - 1) - 0.35300000000000004 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.616 * a(t - 1, i - 1) + 0.6559999999999999 * a(t - 1, i) - 0.6849999999999998 * a(t - 1, i + 1) + 0.86;
	
	
	#undef a(t, i)
	}
	
	}
	
	} 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	} /* end for t */
	}
	};
	static __Pointer_cond_boundary_kernel_3__ * _Pointer_cond_boundary_kernel_3 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_cond_boundary_kernel_3 = NULL;
	#undef pmod_lu
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_boundary_kernel_3__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_boundary_kernel_3__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11000000000000001 * a(t - 1, i - 1) + 0.15 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11100000000000003 * a(t - 1, i - 1) + 0.151 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.21000000000000002 * a(t - 1, i - 1) + 0.25 * a(t - 1, i) + 0.28500000000000003 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.31 * a(t - 1, i - 1) - 0.35 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.311 * a(t - 1, i - 1) - 0.351 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.61 * a(t - 1, i - 1) + 0.65 * a(t - 1, i) - 0.6849999999999998 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	
	} 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	++t;
	}
	{
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11200000000000002 * a(t - 1, i - 1) + 0.152 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11299999999999999 * a(t - 1, i - 1) + 0.153 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.21200000000000002 * a(t - 1, i - 1) + 0.252 * a(t - 1, i) + 0.28500000000000003 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.312 * a(t - 1, i - 1) - 0.352 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.313 * a(t - 1, i - 1) - 0.35300000000000004 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.616 * a(t - 1, i - 1) + 0.6559999999999999 * a(t - 1, i) - 0.6849999999999998 * a(t - 1, i + 1) + 0.86;
	
	
	#undef a(t, i)
	}
	
	
	} 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	
	}
	} /* end for t */
	}
	};
	static __Pointer_boundary_kernel_3__ * _Pointer_boundary_kernel_3 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_boundary_kernel_3 = NULL;
	#undef pmod_lu
	
	
	
	/* KNOWN */
	class __Pointer_cond_interior_kernel_3__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_cond_interior_kernel_3__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	
	
	#pragma ivdep
	for (int i = l_grid.x0[0]; i < l_grid.x1[0]; ++i, 
	++pt_a_0, 
	++pt_a_1) {
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11000000000000001 * pt_a_1[l_a_stride_0 * (-1)] + 0.15 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11100000000000003 * pt_a_1[l_a_stride_0 * (-1)] + 0.151 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8099999999999999;
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21000000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.25 * pt_a_1[0] + 0.28500000000000003 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.31 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.311 * pt_a_1[l_a_stride_0 * (-1)] - 0.351 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8099999999999999;
	
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.61 * pt_a_1[l_a_stride_0 * (-1)] + 0.65 * pt_a_1[0] - 0.6849999999999998 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.152 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11299999999999999 * pt_a_1[l_a_stride_0 * (-1)] + 0.153 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8300000000000001;
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.252 * pt_a_1[0] + 0.28500000000000003 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.312 * pt_a_1[l_a_stride_0 * (-1)] - 0.352 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.313 * pt_a_1[l_a_stride_0 * (-1)] - 0.35300000000000004 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8300000000000001;
	
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.616 * pt_a_1[l_a_stride_0 * (-1)] + 0.6559999999999999 * pt_a_1[0] - 0.6849999999999998 * pt_a_1[l_a_stride_0 * (1)] + 0.86;
	
	}
	
	}
	
	} /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	} /* end for t */
	}
	};
	static __Pointer_cond_interior_kernel_3__ * _Pointer_cond_interior_kernel_3 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_cond_interior_kernel_3 = NULL;
	
	
	
	
	/* KNOWN */
	class __Pointer_interior_kernel_3__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_interior_kernel_3__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	
	
	#pragma ivdep
	for (int i = l_grid.x0[0]; i < l_grid.x1[0]; ++i, 
	++pt_a_0, 
	++pt_a_1) {
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11000000000000001 * pt_a_1[l_a_stride_0 * (-1)] + 0.15 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11100000000000003 * pt_a_1[l_a_stride_0 * (-1)] + 0.151 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8099999999999999;
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21000000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.25 * pt_a_1[0] + 0.28500000000000003 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.31 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.311 * pt_a_1[l_a_stride_0 * (-1)] - 0.351 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8099999999999999;
	
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.61 * pt_a_1[l_a_stride_0 * (-1)] + 0.65 * pt_a_1[0] - 0.6849999999999998 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	
	} /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	++t;
	}
	{
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	
	
	#pragma ivdep
	for (int i = l_grid.x0[0]; i < l_grid.x1[0]; ++i, 
	++pt_a_0, 
	++pt_a_1) {
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.152 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11299999999999999 * pt_a_1[l_a_stride_0 * (-1)] + 0.153 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8300000000000001;
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.252 * pt_a_1[0] + 0.28500000000000003 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.312 * pt_a_1[l_a_stride_0 * (-1)] - 0.352 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.313 * pt_a_1[l_a_stride_0 * (-1)] - 0.35300000000000004 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8300000000000001;
	
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.616 * pt_a_1[l_a_stride_0 * (-1)] + 0.6559999999999999 * pt_a_1[0] - 0.6849999999999998 * pt_a_1[l_a_stride_0 * (1)] + 0.86;
	
	}
	
	
	} /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	
	}
	} /* end for t */
	}
	};
	static __Pointer_interior_kernel_3__ * _Pointer_interior_kernel_3 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_interior_kernel_3 = NULL;
	
	
	
	/* <101111, 101000>
 */
	auto __POCHOIR_Guard_4__ = [&]  ( int t, int i0 )  -> bool {
	return ( __g_exclusive_0__ ( t + -1, i0 )  && !__g_exclusive_1__ ( t + -1, i0 )  && __g_inclusive_0__ ( t + -1, i0 )  );
	 };
	static Pochoir_Guard <1> POCHOIR_Guard_4 ( __POCHOIR_Guard_4__ ); 

	/* <101111, 101000>
 */
	
	
	/* 
	tile_exclusive_0 - PSERIAL;
	tile_inclusive_0 - PSERIAL;
	tile_inclusive_1 - PINCLUSIVE;
	tile_tiny_inclusive_0 - PINCLUSIVE;
	tile_tiny_inclusive_1 - PINCLUSIVE;
	__Pochoir_NULL__ - PNULL
	 */
	/* k_exclusive_0_0, k_exclusive_0_1, k_exclusive_0_2, k_exclusive_0_3, k_inclusive_0_0, k_inclusive_0_1, k_inclusive_0_2, k_inclusive_0_3, k_inclusive_1_0, k_inclusive_1_1, k_tiny_inclusive_0_0, k_tiny_inclusive_0_1, k_tiny_inclusive_0_2, k_tiny_inclusive_0_3, k_tiny_inclusive_1_0, k_tiny_inclusive_1_1, __Pochoir_NULL_ */ 
	/* 0, 0, 0, 0, 2, 2, 2, 2, 3, 3, 4, 4, 4, 4, 5, 5, 0 */ 
	/* PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PSERIAL, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PNULL */ 
	/* [0,0], [0,1], [1,0], [1,1], [0,0], [0,1], [1,0], [1,1], [0], [1], [0,0], [0,1], [1,0], [1,1], [0], [1], [0] */ 
	/* [2,2], [2,2], [2,2], [2,2], [2,2], [2,2], [2,2], [2,2], [2], [2], [2,2], [2,2], [2,2], [2,2], [2], [2], [1] */ 
	/* 
	PMTile (sizes = [2,2], latest_tile_order = 5), terms = 
		PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 5), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 2), item = k_exclusive_0_0, k_inclusive_0_0
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 2), item = k_exclusive_0_1, k_inclusive_0_1
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 3), item = k_inclusive_1_0
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 4), item = k_tiny_inclusive_0_0
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 4), item = k_tiny_inclusive_0_1
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 5), item = k_tiny_inclusive_1_0
		PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 5), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 2), item = k_exclusive_0_2, k_inclusive_0_2
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 2), item = k_exclusive_0_3, k_inclusive_0_3
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 3), item = k_inclusive_1_1
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 4), item = k_tiny_inclusive_0_2
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 4), item = k_tiny_inclusive_0_3
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 5), item = k_tiny_inclusive_1_1
	 */ 
	static 
	Pochoir_Shape <1> __POCHOIR_Shape__4__ [ ] = {{0, 0}, {-1, -1}, {-1, 0}, {-1, 1}};
	/* toggle: 2; slopes: [] */
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_cond_boundary_kernel_4__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_cond_boundary_kernel_4__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11000000000000001 * a(t - 1, i - 1) + 0.15 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.31 * a(t - 1, i - 1) - 0.35 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11100000000000003 * a(t - 1, i - 1) + 0.151 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.311 * a(t - 1, i - 1) - 0.351 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.41 * a(t - 1, i - 1) - 0.45 * a(t - 1, i) + 0.485 * a(t - 1, i + 1) - 0.8;
	
	
	#undef a(t, i)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.51 * a(t - 1, i - 1) + 0.55 * a(t - 1, i) - 0.585 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.511 * a(t - 1, i - 1) + 0.5509999999999999 * a(t - 1, i) - 0.585 * a(t - 1, i + 1) + 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.61 * a(t - 1, i - 1) + 0.65 * a(t - 1, i) - 0.6849999999999998 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11200000000000002 * a(t - 1, i - 1) + 0.152 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.312 * a(t - 1, i - 1) - 0.352 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11299999999999999 * a(t - 1, i - 1) + 0.153 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.313 * a(t - 1, i - 1) - 0.35300000000000004 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.414 * a(t - 1, i - 1) - 0.454 * a(t - 1, i) + 0.485 * a(t - 1, i + 1) - 0.8400000000000001;
	
	
	#undef a(t, i)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.512 * a(t - 1, i - 1) + 0.5519999999999998 * a(t - 1, i) - 0.585 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.513 * a(t - 1, i - 1) + 0.553 * a(t - 1, i) - 0.585 * a(t - 1, i + 1) + 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.616 * a(t - 1, i - 1) + 0.6559999999999999 * a(t - 1, i) - 0.6849999999999998 * a(t - 1, i + 1) + 0.86;
	
	
	#undef a(t, i)
	}
	
	}
	
	} 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	} /* end for t */
	}
	};
	static __Pointer_cond_boundary_kernel_4__ * _Pointer_cond_boundary_kernel_4 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_cond_boundary_kernel_4 = NULL;
	#undef pmod_lu
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_boundary_kernel_4__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_boundary_kernel_4__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11000000000000001 * a(t - 1, i - 1) + 0.15 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.31 * a(t - 1, i - 1) - 0.35 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11100000000000003 * a(t - 1, i - 1) + 0.151 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.311 * a(t - 1, i - 1) - 0.351 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.41 * a(t - 1, i - 1) - 0.45 * a(t - 1, i) + 0.485 * a(t - 1, i + 1) - 0.8;
	
	
	#undef a(t, i)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.51 * a(t - 1, i - 1) + 0.55 * a(t - 1, i) - 0.585 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.511 * a(t - 1, i - 1) + 0.5509999999999999 * a(t - 1, i) - 0.585 * a(t - 1, i + 1) + 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.61 * a(t - 1, i - 1) + 0.65 * a(t - 1, i) - 0.6849999999999998 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	
	} 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	++t;
	}
	{
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11200000000000002 * a(t - 1, i - 1) + 0.152 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.312 * a(t - 1, i - 1) - 0.352 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11299999999999999 * a(t - 1, i - 1) + 0.153 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.313 * a(t - 1, i - 1) - 0.35300000000000004 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.414 * a(t - 1, i - 1) - 0.454 * a(t - 1, i) + 0.485 * a(t - 1, i + 1) - 0.8400000000000001;
	
	
	#undef a(t, i)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.512 * a(t - 1, i - 1) + 0.5519999999999998 * a(t - 1, i) - 0.585 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.513 * a(t - 1, i - 1) + 0.553 * a(t - 1, i) - 0.585 * a(t - 1, i + 1) + 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.616 * a(t - 1, i - 1) + 0.6559999999999999 * a(t - 1, i) - 0.6849999999999998 * a(t - 1, i + 1) + 0.86;
	
	
	#undef a(t, i)
	}
	
	
	} 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	
	}
	} /* end for t */
	}
	};
	static __Pointer_boundary_kernel_4__ * _Pointer_boundary_kernel_4 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_boundary_kernel_4 = NULL;
	#undef pmod_lu
	
	
	
	/* KNOWN */
	class __Pointer_cond_interior_kernel_4__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_cond_interior_kernel_4__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	
	
	#pragma ivdep
	for (int i = l_grid.x0[0]; i < l_grid.x1[0]; ++i, 
	++pt_a_0, 
	++pt_a_1) {
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.11000000000000001 * pt_a_1[l_a_stride_0 * (-1)] + 0.15 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.31 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.11100000000000003 * pt_a_1[l_a_stride_0 * (-1)] + 0.151 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8099999999999999;
	
	}
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.311 * pt_a_1[l_a_stride_0 * (-1)] - 0.351 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8099999999999999;
	
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.41 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] + 0.485 * pt_a_1[l_a_stride_0 * (1)] - 0.8;
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.51 * pt_a_1[l_a_stride_0 * (-1)] + 0.55 * pt_a_1[0] - 0.585 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.511 * pt_a_1[l_a_stride_0 * (-1)] + 0.5509999999999999 * pt_a_1[0] - 0.585 * pt_a_1[l_a_stride_0 * (1)] + 0.8099999999999999;
	
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.61 * pt_a_1[l_a_stride_0 * (-1)] + 0.65 * pt_a_1[0] - 0.6849999999999998 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.11200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.152 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.312 * pt_a_1[l_a_stride_0 * (-1)] - 0.352 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.11299999999999999 * pt_a_1[l_a_stride_0 * (-1)] + 0.153 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8300000000000001;
	
	}
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.313 * pt_a_1[l_a_stride_0 * (-1)] - 0.35300000000000004 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8300000000000001;
	
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.414 * pt_a_1[l_a_stride_0 * (-1)] - 0.454 * pt_a_1[0] + 0.485 * pt_a_1[l_a_stride_0 * (1)] - 0.8400000000000001;
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.512 * pt_a_1[l_a_stride_0 * (-1)] + 0.5519999999999998 * pt_a_1[0] - 0.585 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.513 * pt_a_1[l_a_stride_0 * (-1)] + 0.553 * pt_a_1[0] - 0.585 * pt_a_1[l_a_stride_0 * (1)] + 0.8300000000000001;
	
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.616 * pt_a_1[l_a_stride_0 * (-1)] + 0.6559999999999999 * pt_a_1[0] - 0.6849999999999998 * pt_a_1[l_a_stride_0 * (1)] + 0.86;
	
	}
	
	}
	
	} /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	} /* end for t */
	}
	};
	static __Pointer_cond_interior_kernel_4__ * _Pointer_cond_interior_kernel_4 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_cond_interior_kernel_4 = NULL;
	
	
	
	
	/* KNOWN */
	class __Pointer_interior_kernel_4__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_interior_kernel_4__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	
	
	#pragma ivdep
	for (int i = l_grid.x0[0]; i < l_grid.x1[0]; ++i, 
	++pt_a_0, 
	++pt_a_1) {
	
	
	
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.11000000000000001 * pt_a_1[l_a_stride_0 * (-1)] + 0.15 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.31 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.11100000000000003 * pt_a_1[l_a_stride_0 * (-1)] + 0.151 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8099999999999999;
	
	}
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.311 * pt_a_1[l_a_stride_0 * (-1)] - 0.351 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8099999999999999;
	
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.41 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] + 0.485 * pt_a_1[l_a_stride_0 * (1)] - 0.8;
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.51 * pt_a_1[l_a_stride_0 * (-1)] + 0.55 * pt_a_1[0] - 0.585 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.511 * pt_a_1[l_a_stride_0 * (-1)] + 0.5509999999999999 * pt_a_1[0] - 0.585 * pt_a_1[l_a_stride_0 * (1)] + 0.8099999999999999;
	
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.61 * pt_a_1[l_a_stride_0 * (-1)] + 0.65 * pt_a_1[0] - 0.6849999999999998 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	
	} /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	++t;
	}
	{
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	
	
	#pragma ivdep
	for (int i = l_grid.x0[0]; i < l_grid.x1[0]; ++i, 
	++pt_a_0, 
	++pt_a_1) {
	
	
	
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.11200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.152 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.312 * pt_a_1[l_a_stride_0 * (-1)] - 0.352 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.11299999999999999 * pt_a_1[l_a_stride_0 * (-1)] + 0.153 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8300000000000001;
	
	}
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.313 * pt_a_1[l_a_stride_0 * (-1)] - 0.35300000000000004 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8300000000000001;
	
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.414 * pt_a_1[l_a_stride_0 * (-1)] - 0.454 * pt_a_1[0] + 0.485 * pt_a_1[l_a_stride_0 * (1)] - 0.8400000000000001;
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.512 * pt_a_1[l_a_stride_0 * (-1)] + 0.5519999999999998 * pt_a_1[0] - 0.585 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.513 * pt_a_1[l_a_stride_0 * (-1)] + 0.553 * pt_a_1[0] - 0.585 * pt_a_1[l_a_stride_0 * (1)] + 0.8300000000000001;
	
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.616 * pt_a_1[l_a_stride_0 * (-1)] + 0.6559999999999999 * pt_a_1[0] - 0.6849999999999998 * pt_a_1[l_a_stride_0 * (1)] + 0.86;
	
	}
	
	
	} /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	
	}
	} /* end for t */
	}
	};
	static __Pointer_interior_kernel_4__ * _Pointer_interior_kernel_4 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_interior_kernel_4 = NULL;
	
	
	
	/* <111010, 000000>
 */
	auto __POCHOIR_Guard_5__ = [&]  ( int t, int i0 )  -> bool {
	return ( !__g_inclusive_1__ ( t + -1, i0 )  && !__g_tiny_inclusive_1__ ( t + -1, i0 )  );
	 };
	static Pochoir_Guard <1> POCHOIR_Guard_5 ( __POCHOIR_Guard_5__ ); 

	/* <111010, 000000>
 */
	
	
	/* 
	tile_exclusive_0 - PINCLUSIVE;
	tile_exclusive_1 - PINCLUSIVE;
	tile_inclusive_0 - PINCLUSIVE;
	tile_tiny_inclusive_0 - PINCLUSIVE;
	__Pochoir_NULL__ - PNULL
	 */
	/* k_exclusive_0_0, k_exclusive_0_1, k_exclusive_0_2, k_exclusive_0_3, k_exclusive_1_0, k_exclusive_1_1, k_inclusive_0_0, k_inclusive_0_1, k_inclusive_0_2, k_inclusive_0_3, k_tiny_inclusive_0_0, k_tiny_inclusive_0_1, k_tiny_inclusive_0_2, k_tiny_inclusive_0_3, __Pochoir_NULL_ */ 
	/* 0, 0, 0, 0, 1, 1, 2, 2, 2, 2, 4, 4, 4, 4, 0 */ 
	/* PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PNULL */ 
	/* [0,0], [0,1], [1,0], [1,1], [0], [1], [0,0], [0,1], [1,0], [1,1], [0,0], [0,1], [1,0], [1,1], [0] */ 
	/* [2,2], [2,2], [2,2], [2,2], [2], [2], [2,2], [2,2], [2,2], [2,2], [2,2], [2,2], [2,2], [2,2], [1] */ 
	/* 
	PMTile (sizes = [2,2], latest_tile_order = 4), terms = 
		PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 4), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_exclusive_0_0
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_exclusive_0_1
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 1), item = k_exclusive_1_0
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 4), item = k_inclusive_0_0, k_tiny_inclusive_0_0
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 4), item = k_inclusive_0_1, k_tiny_inclusive_0_1
		PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 4), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_exclusive_0_2
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_exclusive_0_3
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 1), item = k_exclusive_1_1
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 4), item = k_inclusive_0_2, k_tiny_inclusive_0_2
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 4), item = k_inclusive_0_3, k_tiny_inclusive_0_3
	 */ 
	static 
	Pochoir_Shape <1> __POCHOIR_Shape__5__ [ ] = {{0, 0}, {-1, -1}, {-1, 0}, {-1, 1}};
	/* toggle: 2; slopes: [] */
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_cond_boundary_kernel_5__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_cond_boundary_kernel_5__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11000000000000001 * a(t - 1, i - 1) + 0.15 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11100000000000003 * a(t - 1, i - 1) + 0.151 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.21000000000000002 * a(t - 1, i - 1) + 0.25 * a(t - 1, i) + 0.28500000000000003 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.31 * a(t - 1, i - 1) - 0.35 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8;
	
	
	#undef a(t, i)
	}
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.51 * a(t - 1, i - 1) + 0.55 * a(t - 1, i) - 0.585 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.311 * a(t - 1, i - 1) - 0.351 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.511 * a(t - 1, i - 1) + 0.5509999999999999 * a(t - 1, i) - 0.585 * a(t - 1, i + 1) + 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11200000000000002 * a(t - 1, i - 1) + 0.152 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11299999999999999 * a(t - 1, i - 1) + 0.153 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.21200000000000002 * a(t - 1, i - 1) + 0.252 * a(t - 1, i) + 0.28500000000000003 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.312 * a(t - 1, i - 1) - 0.352 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.82;
	
	
	#undef a(t, i)
	}
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.512 * a(t - 1, i - 1) + 0.5519999999999998 * a(t - 1, i) - 0.585 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.313 * a(t - 1, i - 1) - 0.35300000000000004 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.513 * a(t - 1, i - 1) + 0.553 * a(t - 1, i) - 0.585 * a(t - 1, i + 1) + 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	}
	
	} 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	} /* end for t */
	}
	};
	static __Pointer_cond_boundary_kernel_5__ * _Pointer_cond_boundary_kernel_5 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_cond_boundary_kernel_5 = NULL;
	#undef pmod_lu
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_boundary_kernel_5__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_boundary_kernel_5__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11000000000000001 * a(t - 1, i - 1) + 0.15 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11100000000000003 * a(t - 1, i - 1) + 0.151 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.21000000000000002 * a(t - 1, i - 1) + 0.25 * a(t - 1, i) + 0.28500000000000003 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.31 * a(t - 1, i - 1) - 0.35 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8;
	
	
	#undef a(t, i)
	}
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.51 * a(t - 1, i - 1) + 0.55 * a(t - 1, i) - 0.585 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.311 * a(t - 1, i - 1) - 0.351 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.511 * a(t - 1, i - 1) + 0.5509999999999999 * a(t - 1, i) - 0.585 * a(t - 1, i + 1) + 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	
	} 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	++t;
	}
	{
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11200000000000002 * a(t - 1, i - 1) + 0.152 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11299999999999999 * a(t - 1, i - 1) + 0.153 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.21200000000000002 * a(t - 1, i - 1) + 0.252 * a(t - 1, i) + 0.28500000000000003 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.312 * a(t - 1, i - 1) - 0.352 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.82;
	
	
	#undef a(t, i)
	}
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.512 * a(t - 1, i - 1) + 0.5519999999999998 * a(t - 1, i) - 0.585 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.313 * a(t - 1, i - 1) - 0.35300000000000004 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.513 * a(t - 1, i - 1) + 0.553 * a(t - 1, i) - 0.585 * a(t - 1, i + 1) + 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	} 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	
	}
	} /* end for t */
	}
	};
	static __Pointer_boundary_kernel_5__ * _Pointer_boundary_kernel_5 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_boundary_kernel_5 = NULL;
	#undef pmod_lu
	
	
	
	/* KNOWN */
	class __Pointer_cond_interior_kernel_5__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_cond_interior_kernel_5__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	
	
	#pragma ivdep
	for (int i = l_grid.x0[0]; i < l_grid.x1[0]; ++i, 
	++pt_a_0, 
	++pt_a_1) {
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11000000000000001 * pt_a_1[l_a_stride_0 * (-1)] + 0.15 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11100000000000003 * pt_a_1[l_a_stride_0 * (-1)] + 0.151 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8099999999999999;
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21000000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.25 * pt_a_1[0] + 0.28500000000000003 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.31 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8;
	
	}
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.51 * pt_a_1[l_a_stride_0 * (-1)] + 0.55 * pt_a_1[0] - 0.585 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.311 * pt_a_1[l_a_stride_0 * (-1)] - 0.351 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8099999999999999;
	
	}
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.511 * pt_a_1[l_a_stride_0 * (-1)] + 0.5509999999999999 * pt_a_1[0] - 0.585 * pt_a_1[l_a_stride_0 * (1)] + 0.8099999999999999;
	
	}
	
	}
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.152 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11299999999999999 * pt_a_1[l_a_stride_0 * (-1)] + 0.153 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8300000000000001;
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.252 * pt_a_1[0] + 0.28500000000000003 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.312 * pt_a_1[l_a_stride_0 * (-1)] - 0.352 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.82;
	
	}
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.512 * pt_a_1[l_a_stride_0 * (-1)] + 0.5519999999999998 * pt_a_1[0] - 0.585 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.313 * pt_a_1[l_a_stride_0 * (-1)] - 0.35300000000000004 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8300000000000001;
	
	}
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.513 * pt_a_1[l_a_stride_0 * (-1)] + 0.553 * pt_a_1[0] - 0.585 * pt_a_1[l_a_stride_0 * (1)] + 0.8300000000000001;
	
	}
	
	}
	}
	
	} /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	} /* end for t */
	}
	};
	static __Pointer_cond_interior_kernel_5__ * _Pointer_cond_interior_kernel_5 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_cond_interior_kernel_5 = NULL;
	
	
	
	
	/* KNOWN */
	class __Pointer_interior_kernel_5__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_interior_kernel_5__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	
	
	#pragma ivdep
	for (int i = l_grid.x0[0]; i < l_grid.x1[0]; ++i, 
	++pt_a_0, 
	++pt_a_1) {
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11000000000000001 * pt_a_1[l_a_stride_0 * (-1)] + 0.15 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11100000000000003 * pt_a_1[l_a_stride_0 * (-1)] + 0.151 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8099999999999999;
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21000000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.25 * pt_a_1[0] + 0.28500000000000003 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.31 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8;
	
	}
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.51 * pt_a_1[l_a_stride_0 * (-1)] + 0.55 * pt_a_1[0] - 0.585 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.311 * pt_a_1[l_a_stride_0 * (-1)] - 0.351 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8099999999999999;
	
	}
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.511 * pt_a_1[l_a_stride_0 * (-1)] + 0.5509999999999999 * pt_a_1[0] - 0.585 * pt_a_1[l_a_stride_0 * (1)] + 0.8099999999999999;
	
	}
	
	}
	
	} /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	++t;
	}
	{
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	
	
	#pragma ivdep
	for (int i = l_grid.x0[0]; i < l_grid.x1[0]; ++i, 
	++pt_a_0, 
	++pt_a_1) {
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.152 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11299999999999999 * pt_a_1[l_a_stride_0 * (-1)] + 0.153 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8300000000000001;
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.252 * pt_a_1[0] + 0.28500000000000003 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.312 * pt_a_1[l_a_stride_0 * (-1)] - 0.352 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.82;
	
	}
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.512 * pt_a_1[l_a_stride_0 * (-1)] + 0.5519999999999998 * pt_a_1[0] - 0.585 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.313 * pt_a_1[l_a_stride_0 * (-1)] - 0.35300000000000004 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8300000000000001;
	
	}
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.513 * pt_a_1[l_a_stride_0 * (-1)] + 0.553 * pt_a_1[0] - 0.585 * pt_a_1[l_a_stride_0 * (1)] + 0.8300000000000001;
	
	}
	
	}
	
	} /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	
	}
	} /* end for t */
	}
	};
	static __Pointer_interior_kernel_5__ * _Pointer_interior_kernel_5 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_interior_kernel_5 = NULL;
	
	
	
	/* <111000, 000000>
 */
	auto __POCHOIR_Guard_6__ = [&]  ( int t, int i0 )  -> bool {
	return ( !__g_inclusive_1__ ( t + -1, i0 )  && !__g_tiny_inclusive_0__ ( t + -1, i0 )  && !__g_tiny_inclusive_1__ ( t + -1, i0 )  );
	 };
	static Pochoir_Guard <1> POCHOIR_Guard_6 ( __POCHOIR_Guard_6__ ); 

	/* <111000, 000000>
 */
	
	
	/* 
	tile_exclusive_0 - PINCLUSIVE;
	tile_exclusive_1 - PINCLUSIVE;
	tile_inclusive_0 - PINCLUSIVE;
	__Pochoir_NULL__ - PNULL
	 */
	/* k_exclusive_0_0, k_exclusive_0_1, k_exclusive_0_2, k_exclusive_0_3, k_exclusive_1_0, k_exclusive_1_1, k_inclusive_0_0, k_inclusive_0_1, k_inclusive_0_2, k_inclusive_0_3, __Pochoir_NULL_ */ 
	/* 0, 0, 0, 0, 1, 1, 2, 2, 2, 2, 0 */ 
	/* PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PNULL */ 
	/* [0,0], [0,1], [1,0], [1,1], [0], [1], [0,0], [0,1], [1,0], [1,1], [0] */ 
	/* [2,2], [2,2], [2,2], [2,2], [2], [2], [2,2], [2,2], [2,2], [2,2], [1] */ 
	/* 
	PMTile (sizes = [2,2], latest_tile_order = 2), terms = 
		PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 2), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_exclusive_0_0
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_exclusive_0_1
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 1), item = k_exclusive_1_0
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 2), item = k_inclusive_0_0
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 2), item = k_inclusive_0_1
		PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 2), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_exclusive_0_2
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_exclusive_0_3
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 1), item = k_exclusive_1_1
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 2), item = k_inclusive_0_2
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 2), item = k_inclusive_0_3
	 */ 
	static 
	Pochoir_Shape <1> __POCHOIR_Shape__6__ [ ] = {{0, 0}, {-1, -1}, {-1, 0}, {-1, 1}};
	/* toggle: 2; slopes: [] */
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_cond_boundary_kernel_6__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_cond_boundary_kernel_6__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11000000000000001 * a(t - 1, i - 1) + 0.15 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11100000000000003 * a(t - 1, i - 1) + 0.151 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.21000000000000002 * a(t - 1, i - 1) + 0.25 * a(t - 1, i) + 0.28500000000000003 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.31 * a(t - 1, i - 1) - 0.35 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.311 * a(t - 1, i - 1) - 0.351 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11200000000000002 * a(t - 1, i - 1) + 0.152 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11299999999999999 * a(t - 1, i - 1) + 0.153 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.21200000000000002 * a(t - 1, i - 1) + 0.252 * a(t - 1, i) + 0.28500000000000003 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.312 * a(t - 1, i - 1) - 0.352 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.313 * a(t - 1, i - 1) - 0.35300000000000004 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	}
	
	} 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	} /* end for t */
	}
	};
	static __Pointer_cond_boundary_kernel_6__ * _Pointer_cond_boundary_kernel_6 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_cond_boundary_kernel_6 = NULL;
	#undef pmod_lu
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_boundary_kernel_6__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_boundary_kernel_6__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11000000000000001 * a(t - 1, i - 1) + 0.15 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11100000000000003 * a(t - 1, i - 1) + 0.151 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.21000000000000002 * a(t - 1, i - 1) + 0.25 * a(t - 1, i) + 0.28500000000000003 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.31 * a(t - 1, i - 1) - 0.35 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.311 * a(t - 1, i - 1) - 0.351 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	
	} 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	++t;
	}
	{
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11200000000000002 * a(t - 1, i - 1) + 0.152 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11299999999999999 * a(t - 1, i - 1) + 0.153 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.21200000000000002 * a(t - 1, i - 1) + 0.252 * a(t - 1, i) + 0.28500000000000003 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.312 * a(t - 1, i - 1) - 0.352 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.313 * a(t - 1, i - 1) - 0.35300000000000004 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	} 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	
	}
	} /* end for t */
	}
	};
	static __Pointer_boundary_kernel_6__ * _Pointer_boundary_kernel_6 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_boundary_kernel_6 = NULL;
	#undef pmod_lu
	
	
	
	/* KNOWN */
	class __Pointer_cond_interior_kernel_6__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_cond_interior_kernel_6__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	
	
	#pragma ivdep
	for (int i = l_grid.x0[0]; i < l_grid.x1[0]; ++i, 
	++pt_a_0, 
	++pt_a_1) {
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11000000000000001 * pt_a_1[l_a_stride_0 * (-1)] + 0.15 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11100000000000003 * pt_a_1[l_a_stride_0 * (-1)] + 0.151 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8099999999999999;
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21000000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.25 * pt_a_1[0] + 0.28500000000000003 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.31 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.311 * pt_a_1[l_a_stride_0 * (-1)] - 0.351 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8099999999999999;
	
	}
	
	}
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.152 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11299999999999999 * pt_a_1[l_a_stride_0 * (-1)] + 0.153 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8300000000000001;
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.252 * pt_a_1[0] + 0.28500000000000003 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.312 * pt_a_1[l_a_stride_0 * (-1)] - 0.352 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.313 * pt_a_1[l_a_stride_0 * (-1)] - 0.35300000000000004 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8300000000000001;
	
	}
	
	}
	}
	
	} /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	} /* end for t */
	}
	};
	static __Pointer_cond_interior_kernel_6__ * _Pointer_cond_interior_kernel_6 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_cond_interior_kernel_6 = NULL;
	
	
	
	
	/* KNOWN */
	class __Pointer_interior_kernel_6__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_interior_kernel_6__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	
	
	#pragma ivdep
	for (int i = l_grid.x0[0]; i < l_grid.x1[0]; ++i, 
	++pt_a_0, 
	++pt_a_1) {
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11000000000000001 * pt_a_1[l_a_stride_0 * (-1)] + 0.15 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11100000000000003 * pt_a_1[l_a_stride_0 * (-1)] + 0.151 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8099999999999999;
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21000000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.25 * pt_a_1[0] + 0.28500000000000003 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.31 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.311 * pt_a_1[l_a_stride_0 * (-1)] - 0.351 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8099999999999999;
	
	}
	
	}
	
	} /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	++t;
	}
	{
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	
	
	#pragma ivdep
	for (int i = l_grid.x0[0]; i < l_grid.x1[0]; ++i, 
	++pt_a_0, 
	++pt_a_1) {
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.152 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11299999999999999 * pt_a_1[l_a_stride_0 * (-1)] + 0.153 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8300000000000001;
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.252 * pt_a_1[0] + 0.28500000000000003 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.312 * pt_a_1[l_a_stride_0 * (-1)] - 0.352 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.313 * pt_a_1[l_a_stride_0 * (-1)] - 0.35300000000000004 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8300000000000001;
	
	}
	
	}
	
	} /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	
	}
	} /* end for t */
	}
	};
	static __Pointer_interior_kernel_6__ * _Pointer_interior_kernel_6 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_interior_kernel_6 = NULL;
	
	
	
	/* <101100, 100000>
 */
	auto __POCHOIR_Guard_7__ = [&]  ( int t, int i0 )  -> bool {
	return ( __g_exclusive_0__ ( t + -1, i0 )  && !__g_exclusive_1__ ( t + -1, i0 )  && !__g_tiny_inclusive_0__ ( t + -1, i0 )  && !__g_tiny_inclusive_1__ ( t + -1, i0 )  );
	 };
	static Pochoir_Guard <1> POCHOIR_Guard_7 ( __POCHOIR_Guard_7__ ); 

	/* <101100, 100000>
 */
	
	
	/* 
	tile_exclusive_0 - PSERIAL;
	tile_inclusive_0 - PINCLUSIVE;
	tile_inclusive_1 - PINCLUSIVE;
	__Pochoir_NULL__ - PNULL
	 */
	/* k_exclusive_0_0, k_exclusive_0_1, k_exclusive_0_2, k_exclusive_0_3, k_inclusive_0_0, k_inclusive_0_1, k_inclusive_0_2, k_inclusive_0_3, k_inclusive_1_0, k_inclusive_1_1, __Pochoir_NULL_ */ 
	/* 0, 0, 0, 0, 2, 2, 2, 2, 3, 3, 0 */ 
	/* PSERIAL, PSERIAL, PSERIAL, PSERIAL, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PNULL */ 
	/* [0,0], [0,1], [1,0], [1,1], [0,0], [0,1], [1,0], [1,1], [0], [1], [0] */ 
	/* [2,2], [2,2], [2,2], [2,2], [2,2], [2,2], [2,2], [2,2], [2], [2], [1] */ 
	/* 
	PMTile (sizes = [2,2], latest_tile_order = 3), terms = 
		PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 3), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 2), item = k_exclusive_0_0, k_inclusive_0_0
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 2), item = k_exclusive_0_1, k_inclusive_0_1
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 3), item = k_inclusive_1_0
		PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 3), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 2), item = k_exclusive_0_2, k_inclusive_0_2
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 2), item = k_exclusive_0_3, k_inclusive_0_3
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 3), item = k_inclusive_1_1
	 */ 
	static 
	Pochoir_Shape <1> __POCHOIR_Shape__7__ [ ] = {{0, 0}, {-1, -1}, {-1, 0}, {-1, 1}};
	/* toggle: 2; slopes: [] */
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_cond_boundary_kernel_7__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_cond_boundary_kernel_7__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11000000000000001 * a(t - 1, i - 1) + 0.15 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.31 * a(t - 1, i - 1) - 0.35 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11100000000000003 * a(t - 1, i - 1) + 0.151 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.311 * a(t - 1, i - 1) - 0.351 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.41 * a(t - 1, i - 1) - 0.45 * a(t - 1, i) + 0.485 * a(t - 1, i + 1) - 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11200000000000002 * a(t - 1, i - 1) + 0.152 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.312 * a(t - 1, i - 1) - 0.352 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11299999999999999 * a(t - 1, i - 1) + 0.153 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.313 * a(t - 1, i - 1) - 0.35300000000000004 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.414 * a(t - 1, i - 1) - 0.454 * a(t - 1, i) + 0.485 * a(t - 1, i + 1) - 0.8400000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	} 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	} /* end for t */
	}
	};
	static __Pointer_cond_boundary_kernel_7__ * _Pointer_cond_boundary_kernel_7 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_cond_boundary_kernel_7 = NULL;
	#undef pmod_lu
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_boundary_kernel_7__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_boundary_kernel_7__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11000000000000001 * a(t - 1, i - 1) + 0.15 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.31 * a(t - 1, i - 1) - 0.35 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11100000000000003 * a(t - 1, i - 1) + 0.151 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.311 * a(t - 1, i - 1) - 0.351 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.41 * a(t - 1, i - 1) - 0.45 * a(t - 1, i) + 0.485 * a(t - 1, i + 1) - 0.8;
	
	
	#undef a(t, i)
	}
	
	
	} 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	++t;
	}
	{
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11200000000000002 * a(t - 1, i - 1) + 0.152 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.312 * a(t - 1, i - 1) - 0.352 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11299999999999999 * a(t - 1, i - 1) + 0.153 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.313 * a(t - 1, i - 1) - 0.35300000000000004 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.414 * a(t - 1, i - 1) - 0.454 * a(t - 1, i) + 0.485 * a(t - 1, i + 1) - 0.8400000000000001;
	
	
	#undef a(t, i)
	}
	
	
	} 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	
	}
	} /* end for t */
	}
	};
	static __Pointer_boundary_kernel_7__ * _Pointer_boundary_kernel_7 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_boundary_kernel_7 = NULL;
	#undef pmod_lu
	
	
	
	/* KNOWN */
	class __Pointer_cond_interior_kernel_7__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_cond_interior_kernel_7__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	
	
	#pragma ivdep
	for (int i = l_grid.x0[0]; i < l_grid.x1[0]; ++i, 
	++pt_a_0, 
	++pt_a_1) {
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.11000000000000001 * pt_a_1[l_a_stride_0 * (-1)] + 0.15 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.31 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.11100000000000003 * pt_a_1[l_a_stride_0 * (-1)] + 0.151 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8099999999999999;
	
	}
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.311 * pt_a_1[l_a_stride_0 * (-1)] - 0.351 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8099999999999999;
	
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.41 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] + 0.485 * pt_a_1[l_a_stride_0 * (1)] - 0.8;
	
	}
	
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.11200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.152 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.312 * pt_a_1[l_a_stride_0 * (-1)] - 0.352 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.11299999999999999 * pt_a_1[l_a_stride_0 * (-1)] + 0.153 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8300000000000001;
	
	}
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.313 * pt_a_1[l_a_stride_0 * (-1)] - 0.35300000000000004 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8300000000000001;
	
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.414 * pt_a_1[l_a_stride_0 * (-1)] - 0.454 * pt_a_1[0] + 0.485 * pt_a_1[l_a_stride_0 * (1)] - 0.8400000000000001;
	
	}
	
	}
	
	} /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	} /* end for t */
	}
	};
	static __Pointer_cond_interior_kernel_7__ * _Pointer_cond_interior_kernel_7 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_cond_interior_kernel_7 = NULL;
	
	
	
	
	/* KNOWN */
	class __Pointer_interior_kernel_7__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_interior_kernel_7__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	
	
	#pragma ivdep
	for (int i = l_grid.x0[0]; i < l_grid.x1[0]; ++i, 
	++pt_a_0, 
	++pt_a_1) {
	
	
	
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.11000000000000001 * pt_a_1[l_a_stride_0 * (-1)] + 0.15 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.31 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.11100000000000003 * pt_a_1[l_a_stride_0 * (-1)] + 0.151 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8099999999999999;
	
	}
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.311 * pt_a_1[l_a_stride_0 * (-1)] - 0.351 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8099999999999999;
	
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.41 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] + 0.485 * pt_a_1[l_a_stride_0 * (1)] - 0.8;
	
	}
	
	
	} /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	++t;
	}
	{
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	
	
	#pragma ivdep
	for (int i = l_grid.x0[0]; i < l_grid.x1[0]; ++i, 
	++pt_a_0, 
	++pt_a_1) {
	
	
	
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.11200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.152 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.312 * pt_a_1[l_a_stride_0 * (-1)] - 0.352 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.11299999999999999 * pt_a_1[l_a_stride_0 * (-1)] + 0.153 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8300000000000001;
	
	}
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.313 * pt_a_1[l_a_stride_0 * (-1)] - 0.35300000000000004 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8300000000000001;
	
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.414 * pt_a_1[l_a_stride_0 * (-1)] - 0.454 * pt_a_1[0] + 0.485 * pt_a_1[l_a_stride_0 * (1)] - 0.8400000000000001;
	
	}
	
	
	} /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	
	}
	} /* end for t */
	}
	};
	static __Pointer_interior_kernel_7__ * _Pointer_interior_kernel_7 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_interior_kernel_7 = NULL;
	
	
	
	/* <100000, 100000>
 */
	auto __POCHOIR_Guard_8__ = [&]  ( int t, int i0 )  -> bool {
	return ( __g_exclusive_0__ ( t + -1, i0 )  && !__g_exclusive_1__ ( t + -1, i0 )  && !__g_inclusive_0__ ( t + -1, i0 )  && !__g_inclusive_1__ ( t + -1, i0 )  && !__g_tiny_inclusive_0__ ( t + -1, i0 )  && !__g_tiny_inclusive_1__ ( t + -1, i0 )  );
	 };
	static Pochoir_Guard <1> POCHOIR_Guard_8 ( __POCHOIR_Guard_8__ ); 

	/* <100000, 100000>
 */
	
	
	/* 
	tile_exclusive_0 - PSERIAL;
	__Pochoir_NULL__ - PNULL
	 */
	/* k_exclusive_0_0, k_exclusive_0_1, k_exclusive_0_2, k_exclusive_0_3, __Pochoir_NULL_ */ 
	/* 0, 0, 0, 0, 0 */ 
	/* PSERIAL, PSERIAL, PSERIAL, PSERIAL, PNULL */ 
	/* [0,0], [0,1], [1,0], [1,1], [0] */ 
	/* [2,2], [2,2], [2,2], [2,2], [1] */ 
	/* 
	PMTile (sizes = [2,2], latest_tile_order = 0), terms = 
		PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_exclusive_0_0
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_exclusive_0_1
		PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_exclusive_0_2
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_exclusive_0_3
	 */ 
	static 
	Pochoir_Shape <1> __POCHOIR_Shape__8__ [ ] = {{0, 0}, {-1, -1}, {-1, 0}, {-1, 1}};
	/* toggle: 2; slopes: [] */
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_cond_boundary_kernel_8__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_cond_boundary_kernel_8__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11000000000000001 * a(t - 1, i - 1) + 0.15 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11100000000000003 * a(t - 1, i - 1) + 0.151 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11200000000000002 * a(t - 1, i - 1) + 0.152 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11299999999999999 * a(t - 1, i - 1) + 0.153 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	}
	
	} 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	} /* end for t */
	}
	};
	static __Pointer_cond_boundary_kernel_8__ * _Pointer_cond_boundary_kernel_8 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_cond_boundary_kernel_8 = NULL;
	#undef pmod_lu
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_boundary_kernel_8__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_boundary_kernel_8__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11000000000000001 * a(t - 1, i - 1) + 0.15 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11100000000000003 * a(t - 1, i - 1) + 0.151 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	
	} 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	++t;
	}
	{
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11200000000000002 * a(t - 1, i - 1) + 0.152 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11299999999999999 * a(t - 1, i - 1) + 0.153 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	} 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	
	}
	} /* end for t */
	}
	};
	static __Pointer_boundary_kernel_8__ * _Pointer_boundary_kernel_8 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_boundary_kernel_8 = NULL;
	#undef pmod_lu
	
	
	
	/* KNOWN */
	class __Pointer_cond_interior_kernel_8__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_cond_interior_kernel_8__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	
	
	#pragma ivdep
	for (int i = l_grid.x0[0]; i < l_grid.x1[0]; ++i, 
	++pt_a_0, 
	++pt_a_1) {
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.11000000000000001 * pt_a_1[l_a_stride_0 * (-1)] + 0.15 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.11100000000000003 * pt_a_1[l_a_stride_0 * (-1)] + 0.151 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8099999999999999;
	
	}
	
	}
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.11200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.152 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.11299999999999999 * pt_a_1[l_a_stride_0 * (-1)] + 0.153 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8300000000000001;
	
	}
	
	}
	}
	
	} /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	} /* end for t */
	}
	};
	static __Pointer_cond_interior_kernel_8__ * _Pointer_cond_interior_kernel_8 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_cond_interior_kernel_8 = NULL;
	
	
	
	
	/* KNOWN */
	class __Pointer_interior_kernel_8__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_interior_kernel_8__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	
	
	#pragma ivdep
	for (int i = l_grid.x0[0]; i < l_grid.x1[0]; ++i, 
	++pt_a_0, 
	++pt_a_1) {
	
	
	
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.11000000000000001 * pt_a_1[l_a_stride_0 * (-1)] + 0.15 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.11100000000000003 * pt_a_1[l_a_stride_0 * (-1)] + 0.151 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8099999999999999;
	
	}
	
	}
	
	} /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	++t;
	}
	{
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	
	
	#pragma ivdep
	for (int i = l_grid.x0[0]; i < l_grid.x1[0]; ++i, 
	++pt_a_0, 
	++pt_a_1) {
	
	
	
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.11200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.152 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.11299999999999999 * pt_a_1[l_a_stride_0 * (-1)] + 0.153 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8300000000000001;
	
	}
	
	}
	
	} /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	
	}
	} /* end for t */
	}
	};
	static __Pointer_interior_kernel_8__ * _Pointer_interior_kernel_8 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_interior_kernel_8 = NULL;
	
	
	
	/* <111111, 000000>
 */
	auto __POCHOIR_Guard_9__ = [&]  ( int t, int i0 )  -> bool {
	return ( true );
	 };
	static Pochoir_Guard <1> POCHOIR_Guard_9 ( __POCHOIR_Guard_9__ ); 

	/* <111111, 000000>
 */
	
	
	/* 
	tile_exclusive_0 - PINCLUSIVE;
	tile_exclusive_1 - PINCLUSIVE;
	tile_inclusive_0 - PINCLUSIVE;
	tile_inclusive_1 - PINCLUSIVE;
	tile_tiny_inclusive_0 - PINCLUSIVE;
	tile_tiny_inclusive_1 - PINCLUSIVE;
	__Pochoir_NULL__ - PNULL
	 */
	/* k_exclusive_0_0, k_exclusive_0_1, k_exclusive_0_2, k_exclusive_0_3, k_exclusive_1_0, k_exclusive_1_1, k_inclusive_0_0, k_inclusive_0_1, k_inclusive_0_2, k_inclusive_0_3, k_inclusive_1_0, k_inclusive_1_1, k_tiny_inclusive_0_0, k_tiny_inclusive_0_1, k_tiny_inclusive_0_2, k_tiny_inclusive_0_3, k_tiny_inclusive_1_0, k_tiny_inclusive_1_1, __Pochoir_NULL_ */ 
	/* 0, 0, 0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 4, 4, 4, 4, 5, 5, 0 */ 
	/* PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PNULL */ 
	/* [0,0], [0,1], [1,0], [1,1], [0], [1], [0,0], [0,1], [1,0], [1,1], [0], [1], [0,0], [0,1], [1,0], [1,1], [0], [1], [0] */ 
	/* [2,2], [2,2], [2,2], [2,2], [2], [2], [2,2], [2,2], [2,2], [2,2], [2], [2], [2,2], [2,2], [2,2], [2,2], [2], [2], [1] */ 
	/* 
	PMTile (sizes = [2,2], latest_tile_order = 5), terms = 
		PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 5), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_exclusive_0_0
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_exclusive_0_1
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 1), item = k_exclusive_1_0
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 2), item = k_inclusive_0_0
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 2), item = k_inclusive_0_1
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 3), item = k_inclusive_1_0
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 4), item = k_tiny_inclusive_0_0
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 4), item = k_tiny_inclusive_0_1
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 5), item = k_tiny_inclusive_1_0
		PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 5), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k_exclusive_0_2
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k_exclusive_0_3
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 1), item = k_exclusive_1_1
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 2), item = k_inclusive_0_2
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 2), item = k_inclusive_0_3
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 3), item = k_inclusive_1_1
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 4), item = k_tiny_inclusive_0_2
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 4), item = k_tiny_inclusive_0_3
			PMTileTerm (indices = [], sizes = [], latest_tile_order = 5), item = k_tiny_inclusive_1_1
	 */ 
	static 
	Pochoir_Shape <1> __POCHOIR_Shape__9__ [ ] = {{0, 0}, {-1, -1}, {-1, 0}, {-1, 1}};
	/* toggle: 2; slopes: [] */
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_cond_boundary_kernel_9__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_cond_boundary_kernel_9__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11000000000000001 * a(t - 1, i - 1) + 0.15 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11100000000000003 * a(t - 1, i - 1) + 0.151 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.21000000000000002 * a(t - 1, i - 1) + 0.25 * a(t - 1, i) + 0.28500000000000003 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.31 * a(t - 1, i - 1) - 0.35 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.311 * a(t - 1, i - 1) - 0.351 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.41 * a(t - 1, i - 1) - 0.45 * a(t - 1, i) + 0.485 * a(t - 1, i + 1) - 0.8;
	
	
	#undef a(t, i)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.51 * a(t - 1, i - 1) + 0.55 * a(t - 1, i) - 0.585 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.511 * a(t - 1, i - 1) + 0.5509999999999999 * a(t - 1, i) - 0.585 * a(t - 1, i + 1) + 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.61 * a(t - 1, i - 1) + 0.65 * a(t - 1, i) - 0.6849999999999998 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11200000000000002 * a(t - 1, i - 1) + 0.152 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11299999999999999 * a(t - 1, i - 1) + 0.153 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.21200000000000002 * a(t - 1, i - 1) + 0.252 * a(t - 1, i) + 0.28500000000000003 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.312 * a(t - 1, i - 1) - 0.352 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.313 * a(t - 1, i - 1) - 0.35300000000000004 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.414 * a(t - 1, i - 1) - 0.454 * a(t - 1, i) + 0.485 * a(t - 1, i + 1) - 0.8400000000000001;
	
	
	#undef a(t, i)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.512 * a(t - 1, i - 1) + 0.5519999999999998 * a(t - 1, i) - 0.585 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.513 * a(t - 1, i - 1) + 0.553 * a(t - 1, i) - 0.585 * a(t - 1, i + 1) + 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.616 * a(t - 1, i - 1) + 0.6559999999999999 * a(t - 1, i) - 0.6849999999999998 * a(t - 1, i + 1) + 0.86;
	
	
	#undef a(t, i)
	}
	
	}
	
	} 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	} /* end for t */
	}
	};
	static __Pointer_cond_boundary_kernel_9__ * _Pointer_cond_boundary_kernel_9 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_cond_boundary_kernel_9 = NULL;
	#undef pmod_lu
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_boundary_kernel_9__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_boundary_kernel_9__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11000000000000001 * a(t - 1, i - 1) + 0.15 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11100000000000003 * a(t - 1, i - 1) + 0.151 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.21000000000000002 * a(t - 1, i - 1) + 0.25 * a(t - 1, i) + 0.28500000000000003 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.31 * a(t - 1, i - 1) - 0.35 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.311 * a(t - 1, i - 1) - 0.351 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.41 * a(t - 1, i - 1) - 0.45 * a(t - 1, i) + 0.485 * a(t - 1, i + 1) - 0.8;
	
	
	#undef a(t, i)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.51 * a(t - 1, i - 1) + 0.55 * a(t - 1, i) - 0.585 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.511 * a(t - 1, i - 1) + 0.5509999999999999 * a(t - 1, i) - 0.585 * a(t - 1, i + 1) + 0.8099999999999999;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.61 * a(t - 1, i - 1) + 0.65 * a(t - 1, i) - 0.6849999999999998 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	
	} 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	++t;
	}
	{
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11200000000000002 * a(t - 1, i - 1) + 0.152 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.11299999999999999 * a(t - 1, i - 1) + 0.153 * a(t - 1, i) + 0.185 * a(t - 1, i + 1) + 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.21200000000000002 * a(t - 1, i - 1) + 0.252 * a(t - 1, i) + 0.28500000000000003 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.312 * a(t - 1, i - 1) - 0.352 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.313 * a(t - 1, i - 1) - 0.35300000000000004 * a(t - 1, i) + 0.385 * a(t - 1, i + 1) - 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.414 * a(t - 1, i - 1) - 0.454 * a(t - 1, i) + 0.485 * a(t - 1, i + 1) - 0.8400000000000001;
	
	
	#undef a(t, i)
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.512 * a(t - 1, i - 1) + 0.5519999999999998 * a(t - 1, i) - 0.585 * a(t - 1, i + 1) + 0.82;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.513 * a(t - 1, i - 1) + 0.553 * a(t - 1, i) - 0.585 * a(t - 1, i + 1) + 0.8300000000000001;
	
	
	#undef a(t, i)
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.616 * a(t - 1, i - 1) + 0.6559999999999999 * a(t - 1, i) - 0.6849999999999998 * a(t - 1, i + 1) + 0.86;
	
	
	#undef a(t, i)
	}
	
	
	} 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	
	}
	} /* end for t */
	}
	};
	static __Pointer_boundary_kernel_9__ * _Pointer_boundary_kernel_9 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_boundary_kernel_9 = NULL;
	#undef pmod_lu
	
	
	
	/* KNOWN */
	class __Pointer_cond_interior_kernel_9__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_cond_interior_kernel_9__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	
	
	#pragma ivdep
	for (int i = l_grid.x0[0]; i < l_grid.x1[0]; ++i, 
	++pt_a_0, 
	++pt_a_1) {
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11000000000000001 * pt_a_1[l_a_stride_0 * (-1)] + 0.15 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11100000000000003 * pt_a_1[l_a_stride_0 * (-1)] + 0.151 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8099999999999999;
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21000000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.25 * pt_a_1[0] + 0.28500000000000003 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.31 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.311 * pt_a_1[l_a_stride_0 * (-1)] - 0.351 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8099999999999999;
	
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.41 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] + 0.485 * pt_a_1[l_a_stride_0 * (1)] - 0.8;
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.51 * pt_a_1[l_a_stride_0 * (-1)] + 0.55 * pt_a_1[0] - 0.585 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.511 * pt_a_1[l_a_stride_0 * (-1)] + 0.5509999999999999 * pt_a_1[0] - 0.585 * pt_a_1[l_a_stride_0 * (1)] + 0.8099999999999999;
	
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.61 * pt_a_1[l_a_stride_0 * (-1)] + 0.65 * pt_a_1[0] - 0.6849999999999998 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.152 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11299999999999999 * pt_a_1[l_a_stride_0 * (-1)] + 0.153 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8300000000000001;
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.252 * pt_a_1[0] + 0.28500000000000003 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.312 * pt_a_1[l_a_stride_0 * (-1)] - 0.352 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.313 * pt_a_1[l_a_stride_0 * (-1)] - 0.35300000000000004 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8300000000000001;
	
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.414 * pt_a_1[l_a_stride_0 * (-1)] - 0.454 * pt_a_1[0] + 0.485 * pt_a_1[l_a_stride_0 * (1)] - 0.8400000000000001;
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.512 * pt_a_1[l_a_stride_0 * (-1)] + 0.5519999999999998 * pt_a_1[0] - 0.585 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.513 * pt_a_1[l_a_stride_0 * (-1)] + 0.553 * pt_a_1[0] - 0.585 * pt_a_1[l_a_stride_0 * (1)] + 0.8300000000000001;
	
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.616 * pt_a_1[l_a_stride_0 * (-1)] + 0.6559999999999999 * pt_a_1[0] - 0.6849999999999998 * pt_a_1[l_a_stride_0 * (1)] + 0.86;
	
	}
	
	}
	
	} /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	} /* end for t */
	}
	};
	static __Pointer_cond_interior_kernel_9__ * _Pointer_cond_interior_kernel_9 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_cond_interior_kernel_9 = NULL;
	
	
	
	
	/* KNOWN */
	class __Pointer_interior_kernel_9__ {
	private: 
	Pochoir <1> & overlap; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_interior_kernel_9__(Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a) : overlap(_overlap), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = overlap.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	
	
	#pragma ivdep
	for (int i = l_grid.x0[0]; i < l_grid.x1[0]; ++i, 
	++pt_a_0, 
	++pt_a_1) {
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11000000000000001 * pt_a_1[l_a_stride_0 * (-1)] + 0.15 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11100000000000003 * pt_a_1[l_a_stride_0 * (-1)] + 0.151 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8099999999999999;
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21000000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.25 * pt_a_1[0] + 0.28500000000000003 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.31 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.311 * pt_a_1[l_a_stride_0 * (-1)] - 0.351 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8099999999999999;
	
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.41 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] + 0.485 * pt_a_1[l_a_stride_0 * (1)] - 0.8;
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.51 * pt_a_1[l_a_stride_0 * (-1)] + 0.55 * pt_a_1[0] - 0.585 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.511 * pt_a_1[l_a_stride_0 * (-1)] + 0.5509999999999999 * pt_a_1[0] - 0.585 * pt_a_1[l_a_stride_0 * (1)] + 0.8099999999999999;
	
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.61 * pt_a_1[l_a_stride_0 * (-1)] + 0.65 * pt_a_1[0] - 0.6849999999999998 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	
	} /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	++t;
	}
	{
	
	double * pt_a_1;
	double * pt_a_0;
	
	/* ["t","i"] */
	pt_a_0 = a_base + ((t) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	/* ["t","i"] */
	pt_a_1 = a_base + ((t - 1) & 0x1) * l_a_total_size + (l_grid.x0[0]) * l_a_stride_0;
	
	
	#pragma ivdep
	for (int i = l_grid.x0[0]; i < l_grid.x1[0]; ++i, 
	++pt_a_0, 
	++pt_a_1) {
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.152 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_exclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.11299999999999999 * pt_a_1[l_a_stride_0 * (-1)] + 0.153 * pt_a_1[0] + 0.185 * pt_a_1[l_a_stride_0 * (1)] + 0.8300000000000001;
	
	}
	
	}
	
	
	if (__g_exclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.21200000000000002 * pt_a_1[l_a_stride_0 * (-1)] + 0.252 * pt_a_1[0] + 0.28500000000000003 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.312 * pt_a_1[l_a_stride_0 * (-1)] - 0.352 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.313 * pt_a_1[l_a_stride_0 * (-1)] - 0.35300000000000004 * pt_a_1[0] + 0.385 * pt_a_1[l_a_stride_0 * (1)] - 0.8300000000000001;
	
	}
	
	}
	
	
	if (__g_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.414 * pt_a_1[l_a_stride_0 * (-1)] - 0.454 * pt_a_1[0] + 0.485 * pt_a_1[l_a_stride_0 * (1)] - 0.8400000000000001;
	
	}
	
	if ((i & 0x1) == 0) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.512 * pt_a_1[l_a_stride_0 * (-1)] + 0.5519999999999998 * pt_a_1[0] - 0.585 * pt_a_1[l_a_stride_0 * (1)] + 0.82;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__g_tiny_inclusive_0__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.513 * pt_a_1[l_a_stride_0 * (-1)] + 0.553 * pt_a_1[0] - 0.585 * pt_a_1[l_a_stride_0 * (1)] + 0.8300000000000001;
	
	}
	
	}
	
	
	if (__g_tiny_inclusive_1__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.616 * pt_a_1[l_a_stride_0 * (-1)] + 0.6559999999999999 * pt_a_1[0] - 0.6849999999999998 * pt_a_1[l_a_stride_0 * (1)] + 0.86;
	
	}
	
	
	} /* end for (sub-trapezoid) */ 
	
	/* Adjust sub-trapezoid! */
	l_grid.x0[0] += l_grid.dx0[0];
	l_grid.x1[0] += l_grid.dx1[0];
	
	}
	} /* end for t */
	}
	};
	static __Pointer_interior_kernel_9__ * _Pointer_interior_kernel_9 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_interior_kernel_9 = NULL;
	
	
	
	extern "C" 
	int Create_Lambdas (Pochoir <1> & _overlap, Pochoir_Array <double, 1> & _a){
	
		_Pointer_boundary_kernel_0 = new __Pointer_boundary_kernel_0__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_0), 1 >  * l_Pointer_boundary_kernel_0 = NULL;
		l_Pointer_boundary_kernel_0 = new Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_0), 1 > ((*_Pointer_boundary_kernel_0), __POCHOIR_Shape__0__);
		Pointer_boundary_kernel_0 = l_Pointer_boundary_kernel_0;
	
		_Pointer_boundary_kernel_1 = new __Pointer_boundary_kernel_1__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_1), 1 >  * l_Pointer_boundary_kernel_1 = NULL;
		l_Pointer_boundary_kernel_1 = new Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_1), 1 > ((*_Pointer_boundary_kernel_1), __POCHOIR_Shape__1__);
		Pointer_boundary_kernel_1 = l_Pointer_boundary_kernel_1;
	
		_Pointer_boundary_kernel_2 = new __Pointer_boundary_kernel_2__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_2), 1 >  * l_Pointer_boundary_kernel_2 = NULL;
		l_Pointer_boundary_kernel_2 = new Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_2), 1 > ((*_Pointer_boundary_kernel_2), __POCHOIR_Shape__2__);
		Pointer_boundary_kernel_2 = l_Pointer_boundary_kernel_2;
	
		_Pointer_boundary_kernel_3 = new __Pointer_boundary_kernel_3__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_3), 1 >  * l_Pointer_boundary_kernel_3 = NULL;
		l_Pointer_boundary_kernel_3 = new Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_3), 1 > ((*_Pointer_boundary_kernel_3), __POCHOIR_Shape__3__);
		Pointer_boundary_kernel_3 = l_Pointer_boundary_kernel_3;
	
		_Pointer_boundary_kernel_4 = new __Pointer_boundary_kernel_4__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_4), 1 >  * l_Pointer_boundary_kernel_4 = NULL;
		l_Pointer_boundary_kernel_4 = new Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_4), 1 > ((*_Pointer_boundary_kernel_4), __POCHOIR_Shape__4__);
		Pointer_boundary_kernel_4 = l_Pointer_boundary_kernel_4;
	
		_Pointer_boundary_kernel_5 = new __Pointer_boundary_kernel_5__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_5), 1 >  * l_Pointer_boundary_kernel_5 = NULL;
		l_Pointer_boundary_kernel_5 = new Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_5), 1 > ((*_Pointer_boundary_kernel_5), __POCHOIR_Shape__5__);
		Pointer_boundary_kernel_5 = l_Pointer_boundary_kernel_5;
	
		_Pointer_boundary_kernel_6 = new __Pointer_boundary_kernel_6__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_6), 1 >  * l_Pointer_boundary_kernel_6 = NULL;
		l_Pointer_boundary_kernel_6 = new Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_6), 1 > ((*_Pointer_boundary_kernel_6), __POCHOIR_Shape__6__);
		Pointer_boundary_kernel_6 = l_Pointer_boundary_kernel_6;
	
		_Pointer_boundary_kernel_7 = new __Pointer_boundary_kernel_7__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_7), 1 >  * l_Pointer_boundary_kernel_7 = NULL;
		l_Pointer_boundary_kernel_7 = new Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_7), 1 > ((*_Pointer_boundary_kernel_7), __POCHOIR_Shape__7__);
		Pointer_boundary_kernel_7 = l_Pointer_boundary_kernel_7;
	
		_Pointer_boundary_kernel_8 = new __Pointer_boundary_kernel_8__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_8), 1 >  * l_Pointer_boundary_kernel_8 = NULL;
		l_Pointer_boundary_kernel_8 = new Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_8), 1 > ((*_Pointer_boundary_kernel_8), __POCHOIR_Shape__8__);
		Pointer_boundary_kernel_8 = l_Pointer_boundary_kernel_8;
	
		_Pointer_boundary_kernel_9 = new __Pointer_boundary_kernel_9__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_9), 1 >  * l_Pointer_boundary_kernel_9 = NULL;
		l_Pointer_boundary_kernel_9 = new Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_9), 1 > ((*_Pointer_boundary_kernel_9), __POCHOIR_Shape__9__);
		Pointer_boundary_kernel_9 = l_Pointer_boundary_kernel_9;
	
		_Pointer_cond_boundary_kernel_0 = new __Pointer_cond_boundary_kernel_0__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_0), 1 >  * l_Pointer_cond_boundary_kernel_0 = NULL;
		l_Pointer_cond_boundary_kernel_0 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_0), 1 > ((*_Pointer_cond_boundary_kernel_0), __POCHOIR_Shape__0__);
		Pointer_cond_boundary_kernel_0 = l_Pointer_cond_boundary_kernel_0;
	
		_Pointer_cond_boundary_kernel_1 = new __Pointer_cond_boundary_kernel_1__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_1), 1 >  * l_Pointer_cond_boundary_kernel_1 = NULL;
		l_Pointer_cond_boundary_kernel_1 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_1), 1 > ((*_Pointer_cond_boundary_kernel_1), __POCHOIR_Shape__1__);
		Pointer_cond_boundary_kernel_1 = l_Pointer_cond_boundary_kernel_1;
	
		_Pointer_cond_boundary_kernel_2 = new __Pointer_cond_boundary_kernel_2__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_2), 1 >  * l_Pointer_cond_boundary_kernel_2 = NULL;
		l_Pointer_cond_boundary_kernel_2 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_2), 1 > ((*_Pointer_cond_boundary_kernel_2), __POCHOIR_Shape__2__);
		Pointer_cond_boundary_kernel_2 = l_Pointer_cond_boundary_kernel_2;
	
		_Pointer_cond_boundary_kernel_3 = new __Pointer_cond_boundary_kernel_3__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_3), 1 >  * l_Pointer_cond_boundary_kernel_3 = NULL;
		l_Pointer_cond_boundary_kernel_3 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_3), 1 > ((*_Pointer_cond_boundary_kernel_3), __POCHOIR_Shape__3__);
		Pointer_cond_boundary_kernel_3 = l_Pointer_cond_boundary_kernel_3;
	
		_Pointer_cond_boundary_kernel_4 = new __Pointer_cond_boundary_kernel_4__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_4), 1 >  * l_Pointer_cond_boundary_kernel_4 = NULL;
		l_Pointer_cond_boundary_kernel_4 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_4), 1 > ((*_Pointer_cond_boundary_kernel_4), __POCHOIR_Shape__4__);
		Pointer_cond_boundary_kernel_4 = l_Pointer_cond_boundary_kernel_4;
	
		_Pointer_cond_boundary_kernel_5 = new __Pointer_cond_boundary_kernel_5__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_5), 1 >  * l_Pointer_cond_boundary_kernel_5 = NULL;
		l_Pointer_cond_boundary_kernel_5 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_5), 1 > ((*_Pointer_cond_boundary_kernel_5), __POCHOIR_Shape__5__);
		Pointer_cond_boundary_kernel_5 = l_Pointer_cond_boundary_kernel_5;
	
		_Pointer_cond_boundary_kernel_6 = new __Pointer_cond_boundary_kernel_6__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_6), 1 >  * l_Pointer_cond_boundary_kernel_6 = NULL;
		l_Pointer_cond_boundary_kernel_6 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_6), 1 > ((*_Pointer_cond_boundary_kernel_6), __POCHOIR_Shape__6__);
		Pointer_cond_boundary_kernel_6 = l_Pointer_cond_boundary_kernel_6;
	
		_Pointer_cond_boundary_kernel_7 = new __Pointer_cond_boundary_kernel_7__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_7), 1 >  * l_Pointer_cond_boundary_kernel_7 = NULL;
		l_Pointer_cond_boundary_kernel_7 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_7), 1 > ((*_Pointer_cond_boundary_kernel_7), __POCHOIR_Shape__7__);
		Pointer_cond_boundary_kernel_7 = l_Pointer_cond_boundary_kernel_7;
	
		_Pointer_cond_boundary_kernel_8 = new __Pointer_cond_boundary_kernel_8__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_8), 1 >  * l_Pointer_cond_boundary_kernel_8 = NULL;
		l_Pointer_cond_boundary_kernel_8 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_8), 1 > ((*_Pointer_cond_boundary_kernel_8), __POCHOIR_Shape__8__);
		Pointer_cond_boundary_kernel_8 = l_Pointer_cond_boundary_kernel_8;
	
		_Pointer_cond_boundary_kernel_9 = new __Pointer_cond_boundary_kernel_9__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_9), 1 >  * l_Pointer_cond_boundary_kernel_9 = NULL;
		l_Pointer_cond_boundary_kernel_9 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_9), 1 > ((*_Pointer_cond_boundary_kernel_9), __POCHOIR_Shape__9__);
		Pointer_cond_boundary_kernel_9 = l_Pointer_cond_boundary_kernel_9;
	
		_Pointer_interior_kernel_0 = new __Pointer_interior_kernel_0__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_0), 1 >  * l_Pointer_interior_kernel_0 = NULL;
		l_Pointer_interior_kernel_0 = new Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_0), 1 > ((*_Pointer_interior_kernel_0), __POCHOIR_Shape__0__);
		Pointer_interior_kernel_0 = l_Pointer_interior_kernel_0;
	
		_Pointer_interior_kernel_1 = new __Pointer_interior_kernel_1__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_1), 1 >  * l_Pointer_interior_kernel_1 = NULL;
		l_Pointer_interior_kernel_1 = new Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_1), 1 > ((*_Pointer_interior_kernel_1), __POCHOIR_Shape__1__);
		Pointer_interior_kernel_1 = l_Pointer_interior_kernel_1;
	
		_Pointer_interior_kernel_2 = new __Pointer_interior_kernel_2__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_2), 1 >  * l_Pointer_interior_kernel_2 = NULL;
		l_Pointer_interior_kernel_2 = new Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_2), 1 > ((*_Pointer_interior_kernel_2), __POCHOIR_Shape__2__);
		Pointer_interior_kernel_2 = l_Pointer_interior_kernel_2;
	
		_Pointer_interior_kernel_3 = new __Pointer_interior_kernel_3__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_3), 1 >  * l_Pointer_interior_kernel_3 = NULL;
		l_Pointer_interior_kernel_3 = new Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_3), 1 > ((*_Pointer_interior_kernel_3), __POCHOIR_Shape__3__);
		Pointer_interior_kernel_3 = l_Pointer_interior_kernel_3;
	
		_Pointer_interior_kernel_4 = new __Pointer_interior_kernel_4__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_4), 1 >  * l_Pointer_interior_kernel_4 = NULL;
		l_Pointer_interior_kernel_4 = new Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_4), 1 > ((*_Pointer_interior_kernel_4), __POCHOIR_Shape__4__);
		Pointer_interior_kernel_4 = l_Pointer_interior_kernel_4;
	
		_Pointer_interior_kernel_5 = new __Pointer_interior_kernel_5__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_5), 1 >  * l_Pointer_interior_kernel_5 = NULL;
		l_Pointer_interior_kernel_5 = new Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_5), 1 > ((*_Pointer_interior_kernel_5), __POCHOIR_Shape__5__);
		Pointer_interior_kernel_5 = l_Pointer_interior_kernel_5;
	
		_Pointer_interior_kernel_6 = new __Pointer_interior_kernel_6__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_6), 1 >  * l_Pointer_interior_kernel_6 = NULL;
		l_Pointer_interior_kernel_6 = new Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_6), 1 > ((*_Pointer_interior_kernel_6), __POCHOIR_Shape__6__);
		Pointer_interior_kernel_6 = l_Pointer_interior_kernel_6;
	
		_Pointer_interior_kernel_7 = new __Pointer_interior_kernel_7__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_7), 1 >  * l_Pointer_interior_kernel_7 = NULL;
		l_Pointer_interior_kernel_7 = new Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_7), 1 > ((*_Pointer_interior_kernel_7), __POCHOIR_Shape__7__);
		Pointer_interior_kernel_7 = l_Pointer_interior_kernel_7;
	
		_Pointer_interior_kernel_8 = new __Pointer_interior_kernel_8__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_8), 1 >  * l_Pointer_interior_kernel_8 = NULL;
		l_Pointer_interior_kernel_8 = new Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_8), 1 > ((*_Pointer_interior_kernel_8), __POCHOIR_Shape__8__);
		Pointer_interior_kernel_8 = l_Pointer_interior_kernel_8;
	
		_Pointer_interior_kernel_9 = new __Pointer_interior_kernel_9__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_9), 1 >  * l_Pointer_interior_kernel_9 = NULL;
		l_Pointer_interior_kernel_9 = new Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_9), 1 > ((*_Pointer_interior_kernel_9), __POCHOIR_Shape__9__);
		Pointer_interior_kernel_9 = l_Pointer_interior_kernel_9;
	
		_Pointer_cond_interior_kernel_0 = new __Pointer_cond_interior_kernel_0__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_0), 1 >  * l_Pointer_cond_interior_kernel_0 = NULL;
		l_Pointer_cond_interior_kernel_0 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_0), 1 > ((*_Pointer_cond_interior_kernel_0), __POCHOIR_Shape__0__);
		Pointer_cond_interior_kernel_0 = l_Pointer_cond_interior_kernel_0;
	
		_Pointer_cond_interior_kernel_1 = new __Pointer_cond_interior_kernel_1__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_1), 1 >  * l_Pointer_cond_interior_kernel_1 = NULL;
		l_Pointer_cond_interior_kernel_1 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_1), 1 > ((*_Pointer_cond_interior_kernel_1), __POCHOIR_Shape__1__);
		Pointer_cond_interior_kernel_1 = l_Pointer_cond_interior_kernel_1;
	
		_Pointer_cond_interior_kernel_2 = new __Pointer_cond_interior_kernel_2__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_2), 1 >  * l_Pointer_cond_interior_kernel_2 = NULL;
		l_Pointer_cond_interior_kernel_2 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_2), 1 > ((*_Pointer_cond_interior_kernel_2), __POCHOIR_Shape__2__);
		Pointer_cond_interior_kernel_2 = l_Pointer_cond_interior_kernel_2;
	
		_Pointer_cond_interior_kernel_3 = new __Pointer_cond_interior_kernel_3__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_3), 1 >  * l_Pointer_cond_interior_kernel_3 = NULL;
		l_Pointer_cond_interior_kernel_3 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_3), 1 > ((*_Pointer_cond_interior_kernel_3), __POCHOIR_Shape__3__);
		Pointer_cond_interior_kernel_3 = l_Pointer_cond_interior_kernel_3;
	
		_Pointer_cond_interior_kernel_4 = new __Pointer_cond_interior_kernel_4__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_4), 1 >  * l_Pointer_cond_interior_kernel_4 = NULL;
		l_Pointer_cond_interior_kernel_4 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_4), 1 > ((*_Pointer_cond_interior_kernel_4), __POCHOIR_Shape__4__);
		Pointer_cond_interior_kernel_4 = l_Pointer_cond_interior_kernel_4;
	
		_Pointer_cond_interior_kernel_5 = new __Pointer_cond_interior_kernel_5__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_5), 1 >  * l_Pointer_cond_interior_kernel_5 = NULL;
		l_Pointer_cond_interior_kernel_5 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_5), 1 > ((*_Pointer_cond_interior_kernel_5), __POCHOIR_Shape__5__);
		Pointer_cond_interior_kernel_5 = l_Pointer_cond_interior_kernel_5;
	
		_Pointer_cond_interior_kernel_6 = new __Pointer_cond_interior_kernel_6__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_6), 1 >  * l_Pointer_cond_interior_kernel_6 = NULL;
		l_Pointer_cond_interior_kernel_6 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_6), 1 > ((*_Pointer_cond_interior_kernel_6), __POCHOIR_Shape__6__);
		Pointer_cond_interior_kernel_6 = l_Pointer_cond_interior_kernel_6;
	
		_Pointer_cond_interior_kernel_7 = new __Pointer_cond_interior_kernel_7__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_7), 1 >  * l_Pointer_cond_interior_kernel_7 = NULL;
		l_Pointer_cond_interior_kernel_7 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_7), 1 > ((*_Pointer_cond_interior_kernel_7), __POCHOIR_Shape__7__);
		Pointer_cond_interior_kernel_7 = l_Pointer_cond_interior_kernel_7;
	
		_Pointer_cond_interior_kernel_8 = new __Pointer_cond_interior_kernel_8__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_8), 1 >  * l_Pointer_cond_interior_kernel_8 = NULL;
		l_Pointer_cond_interior_kernel_8 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_8), 1 > ((*_Pointer_cond_interior_kernel_8), __POCHOIR_Shape__8__);
		Pointer_cond_interior_kernel_8 = l_Pointer_cond_interior_kernel_8;
	
		_Pointer_cond_interior_kernel_9 = new __Pointer_cond_interior_kernel_9__(_overlap, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_9), 1 >  * l_Pointer_cond_interior_kernel_9 = NULL;
		l_Pointer_cond_interior_kernel_9 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_9), 1 > ((*_Pointer_cond_interior_kernel_9), __POCHOIR_Shape__9__);
		Pointer_cond_interior_kernel_9 = l_Pointer_cond_interior_kernel_9;
	
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
		return 0;
	}
	extern "C" 
	int Register_Lambdas (Pochoir < 1 > & overlap) { 
		overlap.Register_Tile_Obase_Kernels(POCHOIR_Guard_0, 2, (*Pointer_interior_kernel_0), (*Pointer_cond_interior_kernel_0), (*Pointer_boundary_kernel_0), (*Pointer_cond_boundary_kernel_0));
		overlap.Register_Tile_Obase_Kernels(POCHOIR_Guard_1, 2, (*Pointer_interior_kernel_1), (*Pointer_cond_interior_kernel_1), (*Pointer_boundary_kernel_1), (*Pointer_cond_boundary_kernel_1));
		overlap.Register_Tile_Obase_Kernels(POCHOIR_Guard_2, 2, (*Pointer_interior_kernel_2), (*Pointer_cond_interior_kernel_2), (*Pointer_boundary_kernel_2), (*Pointer_cond_boundary_kernel_2));
		overlap.Register_Tile_Obase_Kernels(POCHOIR_Guard_3, 2, (*Pointer_interior_kernel_3), (*Pointer_cond_interior_kernel_3), (*Pointer_boundary_kernel_3), (*Pointer_cond_boundary_kernel_3));
		overlap.Register_Tile_Obase_Kernels(POCHOIR_Guard_4, 2, (*Pointer_interior_kernel_4), (*Pointer_cond_interior_kernel_4), (*Pointer_boundary_kernel_4), (*Pointer_cond_boundary_kernel_4));
		overlap.Register_Tile_Obase_Kernels(POCHOIR_Guard_5, 2, (*Pointer_interior_kernel_5), (*Pointer_cond_interior_kernel_5), (*Pointer_boundary_kernel_5), (*Pointer_cond_boundary_kernel_5));
		overlap.Register_Tile_Obase_Kernels(POCHOIR_Guard_6, 2, (*Pointer_interior_kernel_6), (*Pointer_cond_interior_kernel_6), (*Pointer_boundary_kernel_6), (*Pointer_cond_boundary_kernel_6));
		overlap.Register_Tile_Obase_Kernels(POCHOIR_Guard_7, 2, (*Pointer_interior_kernel_7), (*Pointer_cond_interior_kernel_7), (*Pointer_boundary_kernel_7), (*Pointer_cond_boundary_kernel_7));
		overlap.Register_Tile_Obase_Kernels(POCHOIR_Guard_8, 2, (*Pointer_interior_kernel_8), (*Pointer_cond_interior_kernel_8), (*Pointer_boundary_kernel_8), (*Pointer_cond_boundary_kernel_8));
		overlap.Register_Tile_Obase_Kernels(POCHOIR_Guard_9, 2, (*Pointer_interior_kernel_9), (*Pointer_cond_interior_kernel_9), (*Pointer_boundary_kernel_9), (*Pointer_cond_boundary_kernel_9));
	
		return 0;
	}
	
	extern "C" {
		void *__dso_handle = NULL;
	}
