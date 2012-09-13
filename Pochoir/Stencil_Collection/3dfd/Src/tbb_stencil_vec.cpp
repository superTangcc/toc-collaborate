#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <cilk.h>
#include "util_time.h"
#include "tbb/task_scheduler_init.h"
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"
#include "tbb/task.h"

using namespace tbb;

int nthreads = 1;
const int ds = 4;
int Nx = 100;
int Ny = 100;
int Nz = 20;
int T = 40;
static const int NPIECES = 2;
static const int dt_threshold = 3;
static const int dx_threshold = 1000;
static const int dyz_threshold = 3;

float **A;

float *B;
float coef[ds + 1];
float *vsq;

int N = 997;
int Nxy;
int sx2, sx3, sx4;
int sxy2, sxy3, sxy4;

void basecase(int t0, int t1, 
	      int x0, int dx0, int x1, int dx1,
	      int y0, int dy0, int y1, int dy1, 
	      int z0, int dz0, int z1, int dz1 )
{
  int _Nx = Nx;
  int Nxy = _Nx * Ny;
  int sx2 = _Nx * 2;
  int sx3 = _Nx * 3;
  int sx4 = _Nx * 4;
  int sxy2 = Nxy * 2;
  int sxy3 = Nxy * 3;
  int sxy4 = Nxy * 4;
  float c0 = coef[0], c1 = coef[1], c2 = coef[2], c3 = coef[3], c4 = coef[4];

  for(int t = t0; t < t1; ++t) {
    for(int z = z0; z < z1; ++z) {
      for(int y = y0; y < y1; ++y) {
	  float *A_cur = &A[t & 1][z * Nxy + y * _Nx];
	  float *A_next = &A[(t + 1) & 1][z * Nxy + y * _Nx];
	  float *vvv = &vsq[z * Nxy + y * _Nx];
#pragma ivdep
	for(int x = x0; x < x1; ++x) {
	  float div = c0 * A_cur[x] 
	    + c1 * ((A_cur[x + 1] + A_cur[x - 1])
		    + (A_cur[x + _Nx] + A_cur[x - _Nx])
		    + (A_cur[x + Nxy] + A_cur[x - Nxy]))
	    + c2 * ((A_cur[x + 2] + A_cur[x - 2])
		    + (A_cur[x + sx2] + A_cur[x - sx2])
		    + (A_cur[x + sxy2] + A_cur[x - sxy2]))
	    + c3 * ((A_cur[x + 3] + A_cur[x - 3])
		    + (A_cur[x + sx3] + A_cur[x - sx3])
		    + (A_cur[x + sxy3] + A_cur[x - sxy3]))
	    + c4 * ((A_cur[x + 4] + A_cur[x - 4])
		    + (A_cur[x + sx4] + A_cur[x - sx4])
		    + (A_cur[x + sxy4] + A_cur[x - sxy4]));
	  A_next[x] = 2 * A_cur[x] - A_next[x] + vvv[x] * div;
	}
      }
    }
    x0 += dx0; x1 += dx1;
    y0 += dy0; y1 += dy1;
    z0 += dz0; z1 += dz1;
  }
}

void basecase_loop(int t, 
                   int x0, int x1,
                   int y0, int y1, 
                   int z )
{
  int _Nx = Nx;
  int Nxy = _Nx * Ny;
  int sx2 = _Nx * 2;
  int sx3 = _Nx * 3;
  int sx4 = _Nx * 4;
  int sxy2 = Nxy * 2;
  int sxy3 = Nxy * 3;
  int sxy4 = Nxy * 4;
  float c0 = coef[0], c1 = coef[1], c2 = coef[2], c3 = coef[3], c4 = coef[4];

      for(int y = y0; y < y1; ++y) {
	  float *A_cur = &A[t & 1][z * Nxy + y * _Nx];
	  float *A_next = &A[(t + 1) & 1][z * Nxy + y * _Nx];
	  float *vvv = &vsq[z * Nxy + y * _Nx];
#pragma ivdep
	for(int x = x0; x < x1; ++x) {
	  float div = c0 * A_cur[x] 
	    + c1 * ((A_cur[x + 1] + A_cur[x - 1])
		    + (A_cur[x + _Nx] + A_cur[x - _Nx])
		    + (A_cur[x + Nxy] + A_cur[x - Nxy]))
	    + c2 * ((A_cur[x + 2] + A_cur[x - 2])
		    + (A_cur[x + sx2] + A_cur[x - sx2])
		    + (A_cur[x + sxy2] + A_cur[x - sxy2]))
	    + c3 * ((A_cur[x + 3] + A_cur[x - 3])
		    + (A_cur[x + sx3] + A_cur[x - sx3])
		    + (A_cur[x + sxy3] + A_cur[x - sxy3]))
	    + c4 * ((A_cur[x + 4] + A_cur[x - 4])
		    + (A_cur[x + sx4] + A_cur[x - sx4])
		    + (A_cur[x + sxy4] + A_cur[x - sxy4]));
	  A_next[x] = 2 * A_cur[x] - A_next[x] + vvv[x] * div;
	}
      }
}

int count = 0;
/* map the triple (t, x, y) into a unique long long */
static inline long long encode(int t, int x, int y, int z)
{
  return N * (N * (N * (long long)t + x) + y) + z;
}

static inline float &aref(int t, int x, int y, int z)
{
  return A[t & 1][Nxy * z + Nx * y + x];
}

static inline float &aref(int t, int s) {
  return A[t & 1][s];
}

static inline float &vsqref(int x, int y, int z)
{
  return vsq[Nxy * z + Nx * y + x];
}

static inline float &vsqref(int s)
{
  return vsq[s];
}

class ApplyStencilLoop {
	int my_t;
	int my_x0;
	int my_x1;
	int my_y0;
	int my_y1;

public:
	void operator() (const blocked_range<int>& r) const {
	  /*
	  int Nxy = Nx * Ny;
	  int sx2 = Nx * 2;
	  int sx3 = Nx * 3;
	  int sx4 = Nx * 4;
	  int sxy2 = Nxy * 2;
	  int sxy3 = Nxy * 3;
	  int sxy4 = Nxy * 4;
	  float c0 = coef[0], c1 = coef[1], c2 = coef[2], c3 = coef[3], c4 = coef[4];
	  */
	  for(int z = r.begin(); z != r.end(); ++z) {
	    basecase_loop(my_t, my_x0, my_x1, 
			  my_y0, my_y1, z);
	    /*
	      for(int y = my_y0; y < my_y1; ++y) {
		for(int x = my_x0; x < my_x1; ++x) {		
		  int s = z * Nxy + y * Nx + x;
		  float *A_cur = &A[my_t & 1][s];
		  float *A_next = &A[(my_t + 1) & 1][s];
		  float div = c0 * A_cur[0] 
			+ c1 * ((A_cur[0 + 1] + A_cur[0 - 1])
				+ (A_cur[0 + Nx] + A_cur[0 - Nx])
				+ (A_cur[0 + Nxy] + A_cur[0 - Nxy]))
			+ c2 * ((A_cur[0 + 2] + A_cur[0 - 2])
				+ (A_cur[0 + sx2] + A_cur[0 - sx2])
				+ (A_cur[0 + sxy2] + A_cur[0 - sxy2]))
			+ c3 * ((A_cur[0 + 3] + A_cur[0 - 3])
				+ (A_cur[0 + sx3] + A_cur[0 - sx3])
				+ (A_cur[0 + sxy3] + A_cur[0 - sxy3]))
			+ c4 * ((A_cur[0 + 4] + A_cur[0 - 4])
				+ (A_cur[0 + sx4] + A_cur[0 - sx4])
				+ (A_cur[0 + sxy4] + A_cur[0 - sxy4]));
		  A_next[0] = 2 * A_cur[0] - A_next[0] + vsq[s] * div;
		}
		  }
	    */
	  }

	}

	ApplyStencilLoop(int t, int x0, int x1, int y0, int y1) 
		: my_t(t), my_x0(x0), my_x1(x1), my_y0(y0), my_y1(y1){}
};

//Kernel:
//	Addition: 26
//  Multiplication: 7
void loop_opt3(int t0, int t1, 
	       int x0, int x1,
	       int y0, int y1,
	       int z0, int z1)
{
  for(int t = t0; t < t1; ++t) {
    parallel_for(blocked_range<int>(z0, z1), ApplyStencilLoop(t, x0, x1, y0, y1));
  }
}

/*
class COStencilTask: public tbb::task {
	int t0;
	int t1;
	int x0;
	int dx0;
	int x1;
	int dx1;
	int y0;
	int dy0;
	int y1;
	int dy1;
	int z0;
	int dz0;
	int z1;
	int dz1;

public:
	COStencilTask(int t0_, int t1_, 
	   int x0_, int dx0_, int x1_, int dx1_,
	   int y0_, int dy0_, int y1_, int dy1_, 
	   int z0_, int dz0_, int z1_, int dz1_) :
			t0(t0_), t1(t1_),
			x0(x0_), dx0(dx0_),  x1(x1_),dx1(dx1_),
			y0(y0_), dy0(dy0_), y1(y1_), dy1(dy1_),
			z0(z0_), dz0(dz0_), z1(z1_), dz1(dz1_) {}

	task* execute() {
	  int dt = t1 - t0, dx = x1 - x0, dy = y1 - y0, dz = z1 - z0;
	  int i;
	  tbb::task_list list1;
	  tbb::task_list list2;
	  int tcount = 1;
	  if (0 && dx >= dx_threshold && dx >= dy && dx >= dz &&
		  dt >= 1 && dx >= 2 * ds * dt * NPIECES) {
		int chunk = dx / NPIECES;

		for (i = 0; i < NPIECES - 1; ++i) {
		  tcount++;
		  list1.push_back(*new(allocate_child()) COStencilTask(
			  t0, t1, 
			  x0 + i * chunk, ds, x0 + (i+1) * chunk, -ds,
				   y0, dy0, y1, dy1,
				   z0, dz0, z1, dz1));
		}
		tcount++;
		list1.push_back(*new(allocate_child()) COStencilTask(t0, t1,
				 x0 + i * chunk, ds, x1, -ds,
				 y0, dy0, y1, dy1, 
				 z0, dz0, z1, dz1));
		set_ref_count(tcount);
		spawn_and_wait_for_all(list1);

		tcount = 1;
		tcount++;
		list2.push_back(*new(allocate_child()) COStencilTask(t0, t1, 
				 x0, dx0, x0, ds,
				 y0, dy0, y1, dy1, 
				 z0, dz0, z1, dz1));
		for (i = 1; i < NPIECES; ++i) {
			tcount++;
			list2.push_back(*new(allocate_child()) COStencilTask(t0, t1,
				   x0 + i * chunk, -ds, x0 + i * chunk, ds,
				   y0, dy0, y1, dy1, 
				   z0, dz0, z1, dz1));
		}
		tcount++;
		list2.push_back(*new(allocate_child()) COStencilTask(t0, t1, 
				 x1, -ds, x1, dx1,
				 y0, dy0, y1, dy1, 
				 z0, dz0, z1, dz1));
		set_ref_count(tcount);
		spawn_and_wait_for_all(list2);
	  } else if (dy >= dyz_threshold && dy >= dz && dt >= 1 && dy >= 2 * ds * dt * NPIECES) {
		int chunk = dy / NPIECES;
		tcount = 1;
		for (i = 0; i < NPIECES - 1; ++i) {
			tcount++;
			list1.push_back(*new(allocate_child()) COStencilTask(t0, t1,
				   x0, dx0, x1, dx1,
				   y0 + i * chunk, ds, y0 + (i+1) * chunk, -ds, 
				   z0, dz0, z1, dz1));
		}
		tcount++;
		list1.push_back(*new(allocate_child()) COStencilTask(t0, t1,
				 x0, dx0, x1, dx1,
				 y0 + i * chunk, ds, y1, -ds, 
				 z0, dz0, z1, dz1));
		set_ref_count(tcount);
		spawn_and_wait_for_all(list1);
		tcount = 1;
		tcount++;
		list2.push_back(*new(allocate_child()) COStencilTask(t0, t1, 
				 x0, dx0, x1, dx1,
				 y0, dy0, y0, ds, 
				 z0, dz0, z1, dz1));
		for (i = 1; i < NPIECES; ++i){
		  tcount++;
		  list2.push_back(*new(allocate_child()) COStencilTask(t0, t1,
				   x0, dx0, x1, dx1,
				   y0 + i * chunk, -ds, y0 + i * chunk, ds, 
				   z0, dz0, z1, dz1));
		}
		tcount++;
		list2.push_back(*new(allocate_child()) COStencilTask(t0, t1, 
				 x0, dx0, x1, dx1,
				 y1, -ds, y1, dy1, 
				 z0, dz0, z1, dz1));
		set_ref_count(tcount);
		spawn_and_wait_for_all(list2);
	  } else if (dz >= dyz_threshold && dt >= 1 && dz >= 2 * ds * dt * NPIECES) {
		int chunk = dz / NPIECES;
		tcount = 1;
		for (i = 0; i < NPIECES - 1; ++i) {
		    tcount++;
			list1.push_back(*new(allocate_child()) COStencilTask(t0, t1,
				   x0, dx0, x1, dx1,
				   y0, dy0, y1, dy1,
				   z0 + i * chunk, ds, z0 + (i+1) * chunk, -ds));
		}
		tcount++;
		list1.push_back(*new(allocate_child()) COStencilTask(t0, t1,
				 x0, dx0, x1, dx1,
				 y0, dy0, y1, dy1, 
				 z0 + i * chunk, ds, z1, -ds));
		set_ref_count(tcount);
		spawn_and_wait_for_all(list1);

		tcount = 1;
		tcount++;
		list2.push_back(*new(allocate_child()) COStencilTask(t0, t1, 
				 x0, dx0, x1, dx1,
				 y0, dy0, y1, dy1,
				 z0, dz0, z0, ds));
		for (i = 1; i < NPIECES; ++i){
		  tcount++;
			list2.push_back(*new(allocate_child()) COStencilTask(t0, t1,
				   x0, dx0, x1, dx1,
				   y0, dy0, y1, dy1,
				   z0 + i * chunk, -ds, z0 + i * chunk, ds));
		}
		tcount++;
		list2.push_back(*new(allocate_child()) COStencilTask(t0, t1, 
				 x0, dx0, x1, dx1,
				 y0, dy0, y1, dy1,
				 z1, -ds, z1, dz1));
		set_ref_count(tcount);
		spawn_and_wait_for_all(list2);
	  }  else if (dt > dt_threshold) {
		int halfdt = dt / 2;
		task* foo = new(allocate_child()) COStencilTask(t0, t0 + halfdt,
		  x0, dx0, x1, dx1,
		  y0, dy0, y1, dy1, 
		  z0, dz0, z1, dz1);
		foo->execute();
		//spawn(*foo);
		//set_ref_count(tcount);
		//printf("before wait for all 1 -- %d, %d, %d, %d\n", t0, t1, z0, z1);
		//wait_for_all();
		//printf("end wait for all 1 -- %d, %d, %d, %d\n", t0, t1, z0, z1);
		//tcount=1;
		//tcount++;
		foo = new(allocate_child()) COStencilTask(t0 + halfdt, t1, 
		  x0 + dx0 * halfdt, dx0, x1 + dx1 * halfdt, dx1,
		  y0 + dy0 * halfdt, dy0, y1 + dy1 * halfdt, dy1, 
		  z0 + dz0 * halfdt, dz0, z1 + dz1 * halfdt, dz1);
		foo->execute();
	  } else {
		basecase(t0, t1, 
			 x0, dx0, x1, dx1,
			 y0, dy0, y1, dy1,
			 z0, dz0, z1, dz1);
	  } 
	  return NULL;
	}
};
*/
/*
void my_set_ref_count(int i) {
	set_ref_count(i);
	printf("set ref count = %d\n", i);
}
*/

class COStencilTask: public tbb::task {
	int t0;
	int t1;
	int x0;
	int dx0;
	int x1;
	int dx1;
	int y0;
	int dy0;
	int y1;
	int dy1;
	int z0;
	int dz0;
	int z1;
	int dz1;

public:
	COStencilTask(int t0_, int t1_, 
	   int x0_, int dx0_, int x1_, int dx1_,
	   int y0_, int dy0_, int y1_, int dy1_, 
	   int z0_, int dz0_, int z1_, int dz1_) :
			t0(t0_), t1(t1_),
			x0(x0_), dx0(dx0_),  x1(x1_),dx1(dx1_),
			y0(y0_), dy0(dy0_), y1(y1_), dy1(dy1_),
			z0(z0_), dz0(dz0_), z1(z1_), dz1(dz1_) {}

	task* execute() {
	  int dt = t1 - t0, dx = x1 - x0, dy = y1 - y0, dz = z1 - z0;
	  int i;
	  task *foo;
	  //tbb::task_list list1;
	  //tbb::task_list list2;
	  //int  tcount = 1;
	  //printf("enter execute %d, %d, %d, %d, %d, %d\n", t0, t1, y0, y1, z0, z1);
	  if (0 && dx >= dx_threshold && dx >= dy && dx >= dz &&
		  dt >= 1 && dx >= 2 * ds * dt * NPIECES) {
		int chunk = dx / NPIECES;
		set_ref_count(NPIECES+1);
		for (i = 0; i < NPIECES - 1; ++i) {
		  //tcount++;
		  foo = new(allocate_child()) COStencilTask(
			  t0, t1, 
			  x0 + i * chunk, ds, x0 + (i+1) * chunk, -ds,
				   y0, dy0, y1, dy1,
				   z0, dz0, z1, dz1);
		  spawn(*foo);
		}
		//tcount++;
		foo = new(allocate_child()) COStencilTask(t0, t1,
				 x0 + i * chunk, ds, x1, -ds,
				 y0, dy0, y1, dy1, 
				 z0, dz0, z1, dz1);
		spawn(*foo);

		//spawn_and_wait_for_all(list1);
		wait_for_all();

		 //tcount = 1;
		//tcount++;
		set_ref_count(NPIECES+2);
		foo = new(allocate_child()) COStencilTask(t0, t1, 
				 x0, dx0, x0, ds,
				 y0, dy0, y1, dy1, 
				 z0, dz0, z1, dz1);
		spawn(*foo);
		for (i = 1; i < NPIECES; ++i) {
			//tcount++;
			foo = new(allocate_child()) COStencilTask(t0, t1,
				   x0 + i * chunk, -ds, x0 + i * chunk, ds,
				   y0, dy0, y1, dy1, 
				   z0, dz0, z1, dz1);
			spawn(*foo);
		}
		//tcount++;
		foo = new(allocate_child()) COStencilTask(t0, t1, 
				 x1, -ds, x1, dx1,
				 y0, dy0, y1, dy1, 
				 z0, dz0, z1, dz1);
		spawn(*foo);

		wait_for_all();
	  } else if (dy >= dyz_threshold && dy >= dz && dt >= 1 && dy >= 2 * ds * dt * NPIECES) {
		int chunk = dy / NPIECES;				
		 //tcount = 1;
		set_ref_count(NPIECES+1);
		for (i = 0; i < NPIECES - 1; ++i) {
			//tcount++;
			foo = new(allocate_child()) COStencilTask(t0, t1,
				   x0, dx0, x1, dx1,
				   y0 + i * chunk, ds, y0 + (i+1) * chunk, -ds, 
				   z0, dz0, z1, dz1);
			spawn(*foo);
		}

		//tcount++;
		foo = new(allocate_child()) COStencilTask(t0, t1,
				 x0, dx0, x1, dx1,
				 y0 + i * chunk, ds, y1, -ds, 
				 z0, dz0, z1, dz1);
		//set_ref_count(tcount);
		spawn(*foo);

		//printf("set ref count = %d, first phase\n", 5);
		wait_for_all();
		 //tcount = 1;
		//tcount++;
		set_ref_count(NPIECES+2);
		foo = new(allocate_child()) COStencilTask(t0, t1, 
				 x0, dx0, x1, dx1,
				 y0, dy0, y0, ds, 
				 z0, dz0, z1, dz1);
		spawn(*foo);
		for (i = 1; i < NPIECES; ++i){
		  //tcount++;
		  foo = new(allocate_child()) COStencilTask(t0, t1,
				   x0, dx0, x1, dx1,
				   y0 + i * chunk, -ds, y0 + i * chunk, ds, 
				   z0, dz0, z1, dz1);
		  spawn(*foo);
		}
		//tcount++;
		foo = new(allocate_child()) COStencilTask(t0, t1, 
				 x0, dx0, x1, dx1,
				 y1, -ds, y1, dy1, 
				 z0, dz0, z1, dz1);
		spawn(*foo);

		//printf("set ref count = %d, second phase\n", 6);
		wait_for_all();
	  } else if (dz >= dyz_threshold && dt >= 1 && dz >= 2 * ds * dt * NPIECES) {
		int chunk = dz / NPIECES;
				set_ref_count(NPIECES+1);
		 //tcount = 1;
		for (i = 0; i < NPIECES - 1; ++i) {
		    //tcount++;
			task* fooi = new(allocate_child()) COStencilTask(t0, t1,
				   x0, dx0, x1, dx1,
				   y0, dy0, y1, dy1,
				   z0 + i * chunk, ds, z0 + (i+1) * chunk, -ds);
			spawn(*fooi);
		}
		//tcount++;
		task* fooj = new(allocate_child()) COStencilTask(t0, t1,
				 x0, dx0, x1, dx1,
				 y0, dy0, y1, dy1, 
				 z0 + i * chunk, ds, z1, -ds);
		spawn(*fooj);

		 //printf("before wait for all z phase 1: %d, %d, %d, %d, %d, %d\n", t0, t1, y0, y1, z0, z1);
		wait_for_all();
		 //printf("after wait for all z phase 1: %d, %d, %d, %d, %d, %d\n", t0, t1, y0, y1, z0, z1);
		 //tcount = 1;
		//tcount++;
		 		set_ref_count(NPIECES+2);
		task *fook = new(allocate_child()) COStencilTask(t0, t1, 
				 x0, dx0, x1, dx1,
				 y0, dy0, y1, dy1,
				 z0, dz0, z0, ds);
		spawn(*fook);
		for (i = 1; i < NPIECES; ++i){
		  //tcount++;
			task *fool = new(allocate_child()) COStencilTask(t0, t1,
				   x0, dx0, x1, dx1,
				   y0, dy0, y1, dy1,
				   z0 + i * chunk, -ds, z0 + i * chunk, ds);
			spawn(*fool);
		}
		//tcount++;
		task *foom = new(allocate_child()) COStencilTask(t0, t1, 
				 x0, dx0, x1, dx1,
				 y0, dy0, y1, dy1,
				 z1, -ds, z1, dz1);
		spawn(*foom);

		 //printf("before wait for all z phase 2: %d, %d, %d, %d, %d, %d\n", t0, t1, y0, y1, z0, z1);
		wait_for_all();
		 //printf("after wait for all z phase 2: %d, %d, %d, %d, %d, %d\n", t0, t1, y0, y1, z0, z1);
	  }  else if (dt > dt_threshold) {
		int halfdt = dt / 2;
		//tcount=1;
		//tcount++;
		foo = new(allocate_child()) COStencilTask(t0, t0 + halfdt,
		  x0, dx0, x1, dx1,
		  y0, dy0, y1, dy1, 
		  z0, dz0, z1, dz1);
		foo->execute();
		//spawn(*foo);
		//set_ref_count(tcount);
		//printf("before wait for all 1 -- %d, %d, %d, %d\n", t0, t1, z0, z1);
		//wait_for_all();
		//printf("end wait for all 1 -- %d, %d, %d, %d\n", t0, t1, z0, z1);
		//tcount=1;
		//tcount++;
		foo = new(allocate_child()) COStencilTask(t0 + halfdt, t1, 
		  x0 + dx0 * halfdt, dx0, x1 + dx1 * halfdt, dx1,
		  y0 + dy0 * halfdt, dy0, y1 + dy1 * halfdt, dy1, 
		  z0 + dz0 * halfdt, dz0, z1 + dz1 * halfdt, dz1);
		foo->execute();
		//set_ref_count(tcount);
		//wait_for_all();
	  } else {
		basecase(t0, t1, 
			 x0, dx0, x1, dx1,
			 y0, dy0, y1, dy1,
			 z0, dz0, z1, dz1);
	  } 
	  //printf("exit execute %d, %d, %d, %d, %d, %d\n", t0, t1, y0, y1, z0, z1);
	  return NULL;
	}
};

/*

void walk3(int t0, int t1, 
	   int x0, int dx0, int x1, int dx1,
	   int y0, int dy0, int y1, int dy1, 
	   int z0, int dz0, int z1, int dz1 )
{
  int dt = t1 - t0, dx = x1 - x0, dy = y1 - y0, dz = z1 - z0;
  int i;

  if (dx >= dx_threshold && dx >= dy && dx >= dz &&
      dt >= 1 && dx >= 2 * ds * dt * NPIECES) {
    int chunk = dx / NPIECES;

    for (i = 0; i < NPIECES - 1; ++i)
      cilk_spawn walk3(t0, t1,
		       x0 + i * chunk, ds, x0 + (i+1) * chunk, -ds,
		       y0, dy0, y1, dy1,
		       z0, dz0, z1, dz1);
    cilk_spawn walk3(t0, t1,
		     x0 + i * chunk, ds, x1, -ds,
		     y0, dy0, y1, dy1, 
		     z0, dz0, z1, dz1);
    cilk_sync;
    cilk_spawn walk3(t0, t1, 
		     x0, dx0, x0, ds,
		     y0, dy0, y1, dy1, 
		     z0, dz0, z1, dz1);
    for (i = 1; i < NPIECES; ++i)
      cilk_spawn walk3(t0, t1,
		       x0 + i * chunk, -ds, x0 + i * chunk, ds,
		       y0, dy0, y1, dy1, 
		       z0, dz0, z1, dz1);
    cilk_spawn walk3(t0, t1, 
		     x1, -ds, x1, dx1,
		     y0, dy0, y1, dy1, 
		     z0, dz0, z1, dz1);
  } else if (dy >= dyz_threshold && dy >= dz && dt >= 1 && dy >= 2 * ds * dt * NPIECES) {
    int chunk = dy / NPIECES;

    for (i = 0; i < NPIECES - 1; ++i)
      cilk_spawn walk3(t0, t1,
		       x0, dx0, x1, dx1,
		       y0 + i * chunk, ds, y0 + (i+1) * chunk, -ds, 
		       z0, dz0, z1, dz1);
    cilk_spawn walk3(t0, t1,
		     x0, dx0, x1, dx1,
		     y0 + i * chunk, ds, y1, -ds, 
		     z0, dz0, z1, dz1);
    cilk_sync;
    cilk_spawn walk3(t0, t1, 
		     x0, dx0, x1, dx1,
		     y0, dy0, y0, ds, 
		     z0, dz0, z1, dz1);
    for (i = 1; i < NPIECES; ++i)
      cilk_spawn walk3(t0, t1,
		       x0, dx0, x1, dx1,
		       y0 + i * chunk, -ds, y0 + i * chunk, ds, 
		       z0, dz0, z1, dz1);
    cilk_spawn walk3(t0, t1, 
		     x0, dx0, x1, dx1,
		     y1, -ds, y1, dy1, 
		     z0, dz0, z1, dz1);
  } else if (dz >= dyz_threshold && dt >= 1 && dz >= 2 * ds * dt * NPIECES) {
    int chunk = dz / NPIECES;

    for (i = 0; i < NPIECES - 1; ++i)
      cilk_spawn walk3(t0, t1,
		       x0, dx0, x1, dx1,
		       y0, dy0, y1, dy1,
		       z0 + i * chunk, ds, z0 + (i+1) * chunk, -ds);
    cilk_spawn walk3(t0, t1,
		     x0, dx0, x1, dx1,
		     y0, dy0, y1, dy1, 
		     z0 + i * chunk, ds, z1, -ds);
    cilk_sync;
    cilk_spawn walk3(t0, t1, 
		     x0, dx0, x1, dx1,
		     y0, dy0, y1, dy1,
		     z0, dz0, z0, ds);
    for (i = 1; i < NPIECES; ++i)
      cilk_spawn walk3(t0, t1,
		       x0, dx0, x1, dx1,
		       y0, dy0, y1, dy1,
		       z0 + i * chunk, -ds, z0 + i * chunk, ds);
    cilk_spawn walk3(t0, t1, 
		     x0, dx0, x1, dx1,
		     y0, dy0, y1, dy1,
		     z1, -ds, z1, dz1);
  }  else if (dt > dt_threshold) {
    int halfdt = dt / 2;
    walk3(t0, t0 + halfdt,
	  x0, dx0, x1, dx1,
	  y0, dy0, y1, dy1, 
	  z0, dz0, z1, dz1);
    walk3(t0 + halfdt, t1, 
	  x0 + dx0 * halfdt, dx0, x1 + dx1 * halfdt, dx1,
	  y0 + dy0 * halfdt, dy0, y1 + dy1 * halfdt, dy1, 
	  z0 + dz0 * halfdt, dz0, z1 + dz1 * halfdt, dz1);
  } else {
    basecase(t0, t1, 
	     x0, dx0, x1, dx1,
	     y0, dy0, y1, dy1,
	     z0, dz0, z1, dz1);
  } 
}
*/
void init_variables() 
{
  Nxy = Nx * Ny;
  sx2 = Nx * 2;
  sx3 = Nx * 3;
  sx4 = Nx * 4;
  sxy2 = Nxy * 2;
  sxy3 = Nxy * 3;
  sxy4 = Nxy * 4;

  coef[4] = -1.0f / 560.0f;
  coef[3] = 8.0f/315;
  coef[2] = -0.2f;
  coef[1] = 1.6f;
  coef[0] = -1435.0f/504 * 3;

  count = 0;

  for (int z = 0; z < Nz; ++z)
    for (int y = 0; y < Ny; ++y) 
      for(int x = 0; x < Nx; ++x) {
	/* set initial values */
	/*
	  aref(0, x, y, z) = encode(0, x, y, z);
	  aref(1, x, y, z) = encode(-1, x, y, z); // set to invalid
	*/
	float r = abs((float)(x - Nx/2 + y - Ny/2 + z - Nz/2) / 30);
	r = max(1 - r, 0.0f) + 1;
	
	aref(0, x, y, z) = r;
	aref(1, x, y, z) = r;
	vsqref(x, y, z) = 0.001f;
      }

}

void copy_A_to_B() {
  long total = Nx * Ny * Nz;
  B = new float[total];
  for(int i = 0; i < total; i++) {
    B[i] = A[T&1][i];
  }
}

void verify_A_and_B() {
  long total = Nx * Ny * Nz;
  for(int i = 0; i < total; i++) {
    if(B[i] != A[T&1][i]) {
      printf("%f != %f at index %d\n", A[T&1][i], B[i], i);
      return;
    }
  }
  printf("All checked out, A = B\n");
}

void print_summary(char *header, double interval) {
  /* print timing information */
  long total = (long)Nx * Ny * Nz;
//  int n_worker = cilk::current_worker_count();
  int n_worker = nthreads;
  printf("++++++++++++++++++++ %s ++++++++++++++++++++++\n", header);
  printf("first non-zero numbers\n");
  for(int i = 0; i < total; i++) {
    if(A[T%2][i] != 0) {
      printf("%d: %f\n", i, A[T%2][i]);
      break;
    }
  }
	
  long mul = (long)(Nx - 8) * (Ny  - 8) * (Nz - 8) * T;
  double perf = mul / (interval * 1e6);
  printf("time: %f\n", interval);
  printf("Perf: %f Mcells/sec (%f M-FAdd/s, %f M-FMul/s)\n", 
	 perf, 
	 perf * 26, 
	 perf * 7);
  printf("Perf per worker: %f Mcells/sec (%f M-FAdd/s, %f M-FMul/s)\n\n", 
	 perf / n_worker, 
	 perf * 26 / n_worker, 
	 perf * 7 / n_worker);
  //printf("count = %d\n\n", count);		
}

void print_y() {
  FILE *fout = fopen("y_points.txt", "w");
  int z = Nz/2;
  int x = Nx/2;
  for(int y = 0; y < Ny; y++) {
    fprintf(fout, "%f\n", aref(T, x, y, z));
  }
  fclose(fout);
  printf("Done writing output\n");
}

void dotest()
{
  //initialization
  A = new float*[2];
  A[0] = new float[Nx * Ny * Nz];
  A[1] = new float[Nx * Ny * Nz];
  vsq = new float[Nx * Ny * Nz];

  double start;
  double stop;
	
  ///////////////////////////////////////////////                                                                      
  
  init_variables();
  start = getseconds();
  
  loop_opt3(0, T,
            ds, Nx - ds, 
            ds, Ny - ds,
            ds, Nz - ds);
  
  //basecase(0, T,
  //	    ds, 0, Nx - ds, 0, 
  //	    ds, 0, Ny - ds, 0, 
  //	    ds, 0, Nz - ds, 0);
  stop = getseconds(); 
  //copy_A_to_B();
  print_summary("base", stop - start);
  
  ///////////////////////////////////////////////
  
  init_variables();
  // verify_A_and_B();
  start = getseconds();
  COStencilTask& a = *new(tbb::task::allocate_root()) 
	  COStencilTask(0, T,
	    ds, 0, Nx - ds, 0, 
		ds, 0, Ny - ds, 0, 
		ds, 0, Nz - ds, 0);
	  
  tbb::task::spawn_root_and_wait(a);
  stop = getseconds();
  print_summary("walk3", stop - start);
  
  // verify_A_and_B();
  //print_y();

  delete[] A;
  delete[] vsq;
}

int main(int argc, char *argv[])
{

  if (argc > 3) {
    Nx = atoi(argv[1]);
    Ny = atoi(argv[2]);
    Nz = atoi(argv[3]);
  }
	
  if (argc > 4)
    T = atoi(argv[4]);

  if (argc > 5)
    nthreads = atoi(argv[5]);

  task_scheduler_init init(nthreads);
  /*    
	if (argc > 5)
	ds = atoi(argv[5]);

	if (ds < 1)
	ds = 1;
  */

  printf("Order-%d 3D-Stencil (%d points) with space %dx%dx%d and time %d\n", 
	 ds, ds*2*3+1, Nx, Ny, Nz, T);

  dotest();
  return 0;
}
