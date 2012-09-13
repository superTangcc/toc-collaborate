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
	
	/* Known */ Pochoir_Shape <2> heat_shape_2D [ ] = {{0, 0, 0}, {-1, 1, 0}, {-1, 0, 0}, {-1, -1, 0}, {-1, 0, -1}, {-1, 0, 1}};
	/* toggle: 2; slopes: [1,1] */
	
	/* Known */ Pochoir <2> heat_2D;

	
	/* Known*/ Pochoir_Array <double, 2> a ( 2000, 2000 ) , b ( 2000, 2000 ) ;
a.Register_Boundary(periodic_2D); /* Register_Boundary */
	/* Known */
	b.Register_Shape(heat_shape_2D);
	b.Register_Boundary(periodic_2D); /* Register_Boundary */
	/* known Kernel ! */ auto __heat_2D_fn__ = [&] (int t, int i, int j) {
	a(t, i, j) = 0.125 * (a(t - 1, i + 1, j) - 2.0 * a(t - 1, i, j) + a(t - 1, i - 1, j)) + 0.125 * (a(t - 1, i, j + 1) - 2.0 * a(t - 1, i, j) + a(t - 1, i, j - 1)) + a(t - 1, i, j);
	
	};
	
	Pochoir_Kernel <2> heat_2D_fn(__heat_2D_fn__, heat_shape_2D); /* KNOWN!!! */
	heat_2D.Register_Tile_Kernels(Default_Guard_2D/* Known Guard */, heat_2D_fn);
	heat_2D.Register_Array(a); /* Known Register Array */
	heat_2D.Gen_Plan(200); /* known */
	
	heat_2D.Run(l_plan);
	
