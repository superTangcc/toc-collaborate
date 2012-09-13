
	/* Pochoir_Kernel <1> tile_2D_checkerboard[ 2 ][ 2 ] = {{k0, k1}, {k2, k3}}; */
	/* k0[0,0]; k1[0,1]; k2[1,0]; k3[1,1] */
	
	
	#include <cstdio>
	#include <cstdlib>
	#include <cassert>
	#include <pochoir.hpp>
	
	/* Original Codes */
	/* known Guard ! */ auto __guard_interior__ = [&] (int t, int i) -> bool {
	if (((t > 500 / 2 && i > 5500 / 2))) {
	{{return ((true));
	
	
	}
	
	}
	} else {{{return ((false));
	
	
	}
	
	}}
	
	};
	/* known Guard ! */ auto __guard_exterior__ = [&] (int t, int i) -> bool {
	if (((t > 500 / 2 && i > 5500 / 2))) {
	{{return ((false));
	
	
	}
	
	}
	} else {{{return ((true));
	
	
	}
	
	}}
	
	};
	
	/* Generated Codes */
	
	/* 
	[<1, 1>
,<1, 0>
]
	 */
	
	
	/* <1, 1>
 */
	auto __POCHOIR_Guard_0__ = [&]  ( int t, int i0 )  -> bool {
	return ( __Default_Guard_1D__ ( t + -1, i0 )  );
	 };
	static Pochoir_Guard <1> POCHOIR_Guard_0 ( __POCHOIR_Guard_0__ ); 

	/* <1, 1>
 */
	
	
	/* 
	tile_2D_checkerboard - PSERIAL;
	__Pochoir_NULL__ - PNULL
	 */
	/* k0, k1, k2, k3, __Pochoir_NULL_ */ 
	/* 0, 0, 0, 0, 0 */ 
	/* PSERIAL, PSERIAL, PSERIAL, PSERIAL, PNULL */ 
	/* [0,0], [0,1], [1,0], [1,1], [0] */ 
	/* [2,2], [2,2], [2,2], [2,2], [1] */ 
	/* 
	PMTile (sizes = [2,2], latest_tile_order = 0), terms = 
		PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k0
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k1
		PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k2
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k3
	 */ 
	static 
	Pochoir_Shape <1> __POCHOIR_Shape__0__ [ ] = {{0, 0}, {-1, -1}, {-1, 0}, {-1, 1}};
	/* toggle: 2; slopes: [] */
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_cond_boundary_kernel_0__ {
	private: 
	Pochoir <1> & leap_frog; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_cond_boundary_kernel_0__(Pochoir <1> & _leap_frog, Pochoir_Array <double, 1> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.1 * a(t - 1, i - 1) + 0.15 * a(t - 1, i) + 0.189 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.2 * a(t - 1, i - 1) + 0.25 * a(t - 1, i) + 0.281 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	}
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.3 * a(t - 1, i - 1) - 0.35 * a(t - 1, i) - 0.389 * a(t - 1, i + 1) - 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.4 * a(t - 1, i - 1) - 0.45 * a(t - 1, i) - 0.489 * a(t - 1, i + 1) - 0.4;
	
	
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
	static __Pointer_cond_boundary_kernel_0__ * _Pointer_cond_boundary_kernel_0 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_cond_boundary_kernel_0 = NULL;
	#undef pmod_lu
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_boundary_kernel_0__ {
	private: 
	Pochoir <1> & leap_frog; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_boundary_kernel_0__(Pochoir <1> & _leap_frog, Pochoir_Array <double, 1> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.1 * a(t - 1, i - 1) + 0.15 * a(t - 1, i) + 0.189 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.2 * a(t - 1, i - 1) + 0.25 * a(t - 1, i) + 0.281 * a(t - 1, i + 1) + 0.8;
	
	
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
	a(t, i) = 0.3 * a(t - 1, i - 1) - 0.35 * a(t - 1, i) - 0.389 * a(t - 1, i + 1) - 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.4 * a(t - 1, i - 1) - 0.45 * a(t - 1, i) - 0.489 * a(t - 1, i + 1) - 0.4;
	
	
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
	static __Pointer_boundary_kernel_0__ * _Pointer_boundary_kernel_0 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_boundary_kernel_0 = NULL;
	#undef pmod_lu
	
	
	
	/* KNOWN */
	class __Pointer_cond_interior_kernel_0__ {
	private: 
	Pochoir <1> & leap_frog; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_cond_interior_kernel_0__(Pochoir <1> & _leap_frog, Pochoir_Array <double, 1> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = leap_frog.get_phys_grid();
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
	pt_a_0[0] = 0.1 * pt_a_1[l_a_stride_0 * (-1)] + 0.15 * pt_a_1[0] + 0.189 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.2 * pt_a_1[l_a_stride_0 * (-1)] + 0.25 * pt_a_1[0] + 0.281 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	}
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.3 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] - 0.389 * pt_a_1[l_a_stride_0 * (1)] - 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.4 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] - 0.489 * pt_a_1[l_a_stride_0 * (1)] - 0.4;
	
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
	static __Pointer_cond_interior_kernel_0__ * _Pointer_cond_interior_kernel_0 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_cond_interior_kernel_0 = NULL;
	
	
	
	
	/* KNOWN */
	class __Pointer_interior_kernel_0__ {
	private: 
	Pochoir <1> & leap_frog; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_interior_kernel_0__(Pochoir <1> & _leap_frog, Pochoir_Array <double, 1> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = leap_frog.get_phys_grid();
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
	pt_a_0[0] = 0.1 * pt_a_1[l_a_stride_0 * (-1)] + 0.15 * pt_a_1[0] + 0.189 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.2 * pt_a_1[l_a_stride_0 * (-1)] + 0.25 * pt_a_1[0] + 0.281 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
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
	pt_a_0[0] = 0.3 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] - 0.389 * pt_a_1[l_a_stride_0 * (1)] - 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	{/* PSERIAL */ 
	pt_a_0[0] = 0.4 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] - 0.489 * pt_a_1[l_a_stride_0 * (1)] - 0.4;
	
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
	static __Pointer_interior_kernel_0__ * _Pointer_interior_kernel_0 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_interior_kernel_0 = NULL;
	
	
	
	/* <1, 0>
 */
	auto __POCHOIR_Guard_1__ = [&]  ( int t, int i0 )  -> bool {
	return ( true );
	 };
	static Pochoir_Guard <1> POCHOIR_Guard_1 ( __POCHOIR_Guard_1__ ); 

	/* <1, 0>
 */
	
	
	/* 
	tile_2D_checkerboard - PINCLUSIVE;
	__Pochoir_NULL__ - PNULL
	 */
	/* k0, k1, k2, k3, __Pochoir_NULL_ */ 
	/* 0, 0, 0, 0, 0 */ 
	/* PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PINCLUSIVE, PNULL */ 
	/* [0,0], [0,1], [1,0], [1,1], [0] */ 
	/* [2,2], [2,2], [2,2], [2,2], [1] */ 
	/* 
	PMTile (sizes = [2,2], latest_tile_order = 0), terms = 
		PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k0
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k1
		PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = 
			PMTileTerm (indices = [0], sizes = [2], latest_tile_order = 0), item = k2
			PMTileTerm (indices = [1], sizes = [2], latest_tile_order = 0), item = k3
	 */ 
	static 
	Pochoir_Shape <1> __POCHOIR_Shape__1__ [ ] = {{0, 0}, {-1, -1}, {-1, 0}, {-1, 1}};
	/* toggle: 2; slopes: [] */
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_cond_boundary_kernel_1__ {
	private: 
	Pochoir <1> & leap_frog; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_cond_boundary_kernel_1__(Pochoir <1> & _leap_frog, Pochoir_Array <double, 1> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	if (((t + -1) & 0x1) == 0) {
	
	if ((i & 0x1) == 0) {
	
	if (__Default_Guard_1D__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.1 * a(t - 1, i - 1) + 0.15 * a(t - 1, i) + 0.189 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__Default_Guard_1D__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.2 * a(t - 1, i - 1) + 0.25 * a(t - 1, i) + 0.281 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	}
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if (__Default_Guard_1D__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.3 * a(t - 1, i - 1) - 0.35 * a(t - 1, i) - 0.389 * a(t - 1, i + 1) - 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__Default_Guard_1D__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.4 * a(t - 1, i - 1) - 0.45 * a(t - 1, i) - 0.489 * a(t - 1, i + 1) - 0.4;
	
	
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
	static __Pointer_cond_boundary_kernel_1__ * _Pointer_cond_boundary_kernel_1 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_cond_boundary_kernel_1 = NULL;
	#undef pmod_lu
	
	
	#define pmod_lu(a, lb, ub) ((a) - (((ub)-(lb)) & -((a)>=(ub))))
	/* KNOWN */
	class __Pointer_boundary_kernel_1__ {
	private: 
	Pochoir <1> & leap_frog; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_boundary_kernel_1__(Pochoir <1> & _leap_frog, Pochoir_Array <double, 1> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = leap_frog.get_phys_grid();
	for (int t = t0; t < t1; ++t) {
	
	{
	
	
	#pragma ivdep
	for (int old_i = l_grid.x0[0]; old_i < l_grid.x1[0]; ++old_i) {
	int i = pmod_lu(old_i, l_phys_grid.x0[0], l_phys_grid.x1[0]);
	
	
	
	
	if ((i & 0x1) == 0) {
	
	if (__Default_Guard_1D__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.1 * a(t - 1, i - 1) + 0.15 * a(t - 1, i) + 0.189 * a(t - 1, i + 1) + 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__Default_Guard_1D__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.2 * a(t - 1, i - 1) + 0.25 * a(t - 1, i) + 0.281 * a(t - 1, i + 1) + 0.8;
	
	
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
	
	if (__Default_Guard_1D__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.3 * a(t - 1, i - 1) - 0.35 * a(t - 1, i) - 0.389 * a(t - 1, i + 1) - 0.8;
	
	
	#undef a(t, i)
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__Default_Guard_1D__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	
	
	#define a(t, i) a.boundary(t, i)
	a(t, i) = 0.4 * a(t - 1, i - 1) - 0.45 * a(t - 1, i) - 0.489 * a(t - 1, i + 1) - 0.4;
	
	
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
	static __Pointer_boundary_kernel_1__ * _Pointer_boundary_kernel_1 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_boundary_kernel_1 = NULL;
	#undef pmod_lu
	
	
	
	/* KNOWN */
	class __Pointer_cond_interior_kernel_1__ {
	private: 
	Pochoir <1> & leap_frog; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_cond_interior_kernel_1__(Pochoir <1> & _leap_frog, Pochoir_Array <double, 1> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	if (__Default_Guard_1D__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.1 * pt_a_1[l_a_stride_0 * (-1)] + 0.15 * pt_a_1[0] + 0.189 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__Default_Guard_1D__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.2 * pt_a_1[l_a_stride_0 * (-1)] + 0.25 * pt_a_1[0] + 0.281 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	}
	} else 
	if (((t + -1) & 0x1) == 1) {
	
	if ((i & 0x1) == 0) {
	
	if (__Default_Guard_1D__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.3 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] - 0.389 * pt_a_1[l_a_stride_0 * (1)] - 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__Default_Guard_1D__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.4 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] - 0.489 * pt_a_1[l_a_stride_0 * (1)] - 0.4;
	
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
	static __Pointer_cond_interior_kernel_1__ * _Pointer_cond_interior_kernel_1 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_cond_interior_kernel_1 = NULL;
	
	
	
	
	/* KNOWN */
	class __Pointer_interior_kernel_1__ {
	private: 
	Pochoir <1> & leap_frog; 
	Pochoir_Array <double, 1> & a; 
	public: 
	__Pointer_interior_kernel_1__(Pochoir <1> & _leap_frog, Pochoir_Array <double, 1> & _a) : leap_frog(_leap_frog), a(_a) {} 
	inline void operator() (int t0, int t1,  Grid_Info <1> const & grid) {
	Grid_Info <1> l_grid = grid;
	double * a_base = a.data();
	const int l_a_total_size = a.total_size();
	
	int gap_a_0;
	const int l_a_stride_0 = a.stride(0);

	Grid_Info <1> const & l_phys_grid = leap_frog.get_phys_grid();
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
	
	if (__Default_Guard_1D__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.1 * pt_a_1[l_a_stride_0 * (-1)] + 0.15 * pt_a_1[0] + 0.189 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__Default_Guard_1D__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.2 * pt_a_1[l_a_stride_0 * (-1)] + 0.25 * pt_a_1[0] + 0.281 * pt_a_1[l_a_stride_0 * (1)] + 0.8;
	
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
	
	if (__Default_Guard_1D__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.3 * pt_a_1[l_a_stride_0 * (-1)] - 0.35 * pt_a_1[0] - 0.389 * pt_a_1[l_a_stride_0 * (1)] - 0.8;
	
	}
	
	} else 
	if ((i & 0x1) == 1) {
	
	if (__Default_Guard_1D__ ( t + -1, i ) ) {/* PINCLUSIVE */ 
	pt_a_0[0] = 0.4 * pt_a_1[l_a_stride_0 * (-1)] - 0.45 * pt_a_1[0] - 0.489 * pt_a_1[l_a_stride_0 * (1)] - 0.4;
	
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
	static __Pointer_interior_kernel_1__ * _Pointer_interior_kernel_1 = NULL;
	static Pochoir_Base_Kernel <1> * Pointer_interior_kernel_1 = NULL;
	
	
	
	extern "C" 
	int Create_Lambdas (Pochoir <1> & _leap_frog, Pochoir_Array <double, 1> & _a){
	
		_Pointer_boundary_kernel_0 = new __Pointer_boundary_kernel_0__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_0), 1 >  * l_Pointer_boundary_kernel_0 = NULL;
		l_Pointer_boundary_kernel_0 = new Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_0), 1 > ((*_Pointer_boundary_kernel_0), __POCHOIR_Shape__0__);
		Pointer_boundary_kernel_0 = l_Pointer_boundary_kernel_0;
	
		_Pointer_boundary_kernel_1 = new __Pointer_boundary_kernel_1__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_1), 1 >  * l_Pointer_boundary_kernel_1 = NULL;
		l_Pointer_boundary_kernel_1 = new Pochoir_Obase_Kernel < decltype(*_Pointer_boundary_kernel_1), 1 > ((*_Pointer_boundary_kernel_1), __POCHOIR_Shape__1__);
		Pointer_boundary_kernel_1 = l_Pointer_boundary_kernel_1;
	
		_Pointer_cond_boundary_kernel_0 = new __Pointer_cond_boundary_kernel_0__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_0), 1 >  * l_Pointer_cond_boundary_kernel_0 = NULL;
		l_Pointer_cond_boundary_kernel_0 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_0), 1 > ((*_Pointer_cond_boundary_kernel_0), __POCHOIR_Shape__0__);
		Pointer_cond_boundary_kernel_0 = l_Pointer_cond_boundary_kernel_0;
	
		_Pointer_cond_boundary_kernel_1 = new __Pointer_cond_boundary_kernel_1__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_1), 1 >  * l_Pointer_cond_boundary_kernel_1 = NULL;
		l_Pointer_cond_boundary_kernel_1 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_boundary_kernel_1), 1 > ((*_Pointer_cond_boundary_kernel_1), __POCHOIR_Shape__1__);
		Pointer_cond_boundary_kernel_1 = l_Pointer_cond_boundary_kernel_1;
	
		_Pointer_interior_kernel_0 = new __Pointer_interior_kernel_0__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_0), 1 >  * l_Pointer_interior_kernel_0 = NULL;
		l_Pointer_interior_kernel_0 = new Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_0), 1 > ((*_Pointer_interior_kernel_0), __POCHOIR_Shape__0__);
		Pointer_interior_kernel_0 = l_Pointer_interior_kernel_0;
	
		_Pointer_interior_kernel_1 = new __Pointer_interior_kernel_1__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_1), 1 >  * l_Pointer_interior_kernel_1 = NULL;
		l_Pointer_interior_kernel_1 = new Pochoir_Obase_Kernel < decltype(*_Pointer_interior_kernel_1), 1 > ((*_Pointer_interior_kernel_1), __POCHOIR_Shape__1__);
		Pointer_interior_kernel_1 = l_Pointer_interior_kernel_1;
	
		_Pointer_cond_interior_kernel_0 = new __Pointer_cond_interior_kernel_0__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_0), 1 >  * l_Pointer_cond_interior_kernel_0 = NULL;
		l_Pointer_cond_interior_kernel_0 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_0), 1 > ((*_Pointer_cond_interior_kernel_0), __POCHOIR_Shape__0__);
		Pointer_cond_interior_kernel_0 = l_Pointer_cond_interior_kernel_0;
	
		_Pointer_cond_interior_kernel_1 = new __Pointer_cond_interior_kernel_1__(_leap_frog, _a);
		Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_1), 1 >  * l_Pointer_cond_interior_kernel_1 = NULL;
		l_Pointer_cond_interior_kernel_1 = new Pochoir_Obase_Kernel < decltype(*_Pointer_cond_interior_kernel_1), 1 > ((*_Pointer_cond_interior_kernel_1), __POCHOIR_Shape__1__);
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
	int Register_Lambdas (Pochoir < 1 > & leap_frog) { 
		leap_frog.Register_Tile_Obase_Kernels(POCHOIR_Guard_0, 2, (*Pointer_interior_kernel_0), (*Pointer_cond_interior_kernel_0), (*Pointer_boundary_kernel_0), (*Pointer_cond_boundary_kernel_0));
		leap_frog.Register_Tile_Obase_Kernels(POCHOIR_Guard_1, 2, (*Pointer_interior_kernel_1), (*Pointer_cond_interior_kernel_1), (*Pointer_boundary_kernel_1), (*Pointer_cond_boundary_kernel_1));
	
		return 0;
	}
	
	extern "C" {
		void *__dso_handle = NULL;
	}
