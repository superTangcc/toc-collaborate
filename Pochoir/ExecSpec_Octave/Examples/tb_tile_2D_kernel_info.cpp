/* known Guard ! */ auto __Default_Guard_3D__ = [&] (int t, int i, int j, int k) -> bool {
	return (true);
	
	
	};
	
	Pochoir_Guard <3> Default_Guard_3D(__Default_Guard_3D__); /* Known!!! */
	/* known Guard ! */ auto __Default_Guard_2D__ = [&] (int t, int i, int j) -> bool {
	return (true);
	
	
	};
	
	Pochoir_Guard <2> Default_Guard_2D(__Default_Guard_2D__); /* Known!!! */
	/* known Guard ! */ auto __Default_Guard_1D__ = [&] (int t, int i) -> bool {
	return (true);
	
	
	};
	
	Pochoir_Guard <1> Default_Guard_1D(__Default_Guard_1D__); /* Known!!! */
	
	/* Known */ Pochoir_Shape <1> oned_3pt [ ] = {{0, 0}, {-1, 0}, {-1, -1}, {-1, 1}};
	/* toggle: 2; slopes: [1] */
	
	/* Known */ Pochoir_Shape <1> shape_k0 [ ] = {{0, 0}, {-1, -1}, {-1, 0}, {-1, 1}};
	/* toggle: 2; slopes: [1] */
	
	/* Known */ Pochoir_Shape <1> shape_k1 [ ] = {{0, 0}, {-1, -1}, {-1, 0}, {-1, 1}};
	/* toggle: 2; slopes: [1] */
	
	/* Known */ Pochoir_Shape <1> shape_k2 [ ] = {{0, 0}, {-1, -1}, {-1, 0}, {-1, 1}};
	/* toggle: 2; slopes: [1] */
	
	/* Known */ Pochoir_Shape <1> shape_k3 [ ] = {{0, 0}, {-1, -1}, {-1, 0}, {-1, 1}};
	/* toggle: 2; slopes: [1] */
	
	/* Known*/ Pochoir_Array <double, 1> a ( 5500 ) ;

	/* Known*/ Pochoir_Array <double, 1> b ( 5500 ) ;

	/* Known */ Pochoir <1> leap_frog;

	a.Register_Boundary(Pochoir_Periodic_1D); /* Register_Boundary */
	/* Known */
	b.Register_Shape(oned_3pt);
	b.Register_Boundary(Pochoir_Periodic_1D); /* Register_Boundary */
	/* known Guard ! */ auto __guard_interior__ = [&] (int t, int i) -> bool {
	if ((t > 500 / 2 && i > 5500 / 2)) {
	{return (true);
	
	
	}
	} else {{return (false);
	
	
	}}
	
	};
	
	Pochoir_Guard <1> guard_interior(__guard_interior__); /* Known!!! */
	/* known Guard ! */ auto __guard_exterior__ = [&] (int t, int i) -> bool {
	if ((t > 500 / 2 && i > 5500 / 2)) {
	{return (false);
	
	
	}
	} else {{return (true);
	
	
	}}
	
	};
	
	Pochoir_Guard <1> guard_exterior(__guard_exterior__); /* Known!!! */
	/* known Kernel ! */ auto __k0__ = [&] (int t, int i) {
	a(t, i) = 0.1 * a(t - 1, i - 1) + 0.15 * a(t - 1, i) + 0.189 * a(t - 1, i + 1) + 0.8;
	
	};
	
	Pochoir_Kernel <1> k0(__k0__, shape_k0); /* KNOWN!!! */
	/* known Kernel ! */ auto __k1__ = [&] (int t, int i) {
	a(t, i) = 0.2 * a(t - 1, i - 1) + 0.25 * a(t - 1, i) + 0.281 * a(t - 1, i + 1) + 0.8;
	
	};
	
	Pochoir_Kernel <1> k1(__k1__, shape_k1); /* KNOWN!!! */
	/* known Kernel ! */ auto __k2__ = [&] (int t, int i) {
	a(t, i) = 0.3 * a(t - 1, i - 1) - 0.35 * a(t - 1, i) - 0.389 * a(t - 1, i + 1) - 0.8;
	
	};
	
	Pochoir_Kernel <1> k2(__k2__, shape_k2); /* KNOWN!!! */
	/* known Kernel ! */ auto __k3__ = [&] (int t, int i) {
	a(t, i) = 0.4 * a(t - 1, i - 1) - 0.45 * a(t - 1, i) - 0.489 * a(t - 1, i + 1) - 0.4;
	
	};
	
	Pochoir_Kernel <1> k3(__k3__, shape_k3); /* KNOWN!!! */
	
	Pochoir_Kernel <1> tile_2D_checkerboard[ 2 ][ 2 ] = {{k0, k1}, {k2, k3}}; /* Known! */
	/* k0[0,0]; k1[0,1]; k2[1,0]; k3[1,1] */
	leap_frog.Register_Tile_Kernels(Default_Guard_1D/* Known Guard */, tile_2D_checkerboard/* Known Tile */);
	leap_frog.Register_Array(a); /* Known Register Array */
	leap_frog.Gen_Plan(500); /* known */
	
	leap_frog.Run(ll_plan);
	
