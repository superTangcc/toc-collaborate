#include "globals.h"
#include "grid.h"
#include "main.h"

/* If periodic boundary conditions are specified, the ghost cell region
   surrounding the real grid is enlarged according to the number of
   iterations to be performed.  These ghost cells are then updated only
   once, before any computation is performed.  Then, during each
   iteration, successively smaller grids are updated, until the final
   iteration includes only non-ghost cells.  This approach has extra
   computation, but only requires one ghost cell update. */
void update_ghost_cells() {
  int p_zzz, p_zzz_last, p_zzz_periodic;
  int i, j, k;
  int i_low, i_high, j_low, j_high, k_low, k_high;
  int i_low_periodic, i_high_periodic, j_low_periodic, j_high_periodic, k_low_periodic, k_high_periodic;
  int x_currentShellMin, x_currentShellMax, y_currentShellMin, y_currentShellMax, z_currentShellMin, z_currentShellMax;
  int depth;
  
  for (depth=0; depth < ghostCellDepth; depth++) {
    x_currentShellMin = x_realGridMin - depth * x_unitStride;
    x_currentShellMax = x_realGridMax + depth * x_unitStride;
    y_currentShellMin = y_realGridMin - depth * y_unitStride;
    y_currentShellMax = y_realGridMax + depth * y_unitStride;
    z_currentShellMin = z_realGridMin - depth;
    z_currentShellMax = z_realGridMax + depth;

    i_low = x_realGridMin + depth * x_unitStride;
    i_low_periodic = i_low + x_numRealCellsInGrid * x_unitStride;
    i_high = x_realGridMax - (depth+1) * x_unitStride;
    i_high_periodic = i_high - x_numRealCellsInGrid * x_unitStride;
    j_low = y_realGridMin + depth * y_unitStride;
    j_low_periodic = j_low + y_numRealCellsInGrid * y_unitStride;
    j_high = y_realGridMax - (depth+1) * y_unitStride;
    j_high_periodic = j_high - y_numRealCellsInGrid * y_unitStride;
    k_low = z_realGridMin + depth;
    k_low_periodic = k_low + z_numRealCellsInGrid;
    k_high = z_realGridMax - (depth+1);
    k_high_periodic = k_high - z_numRealCellsInGrid;

    // update lower yz-plane
    for (j=y_currentShellMin; j < y_currentShellMax; j += y_unitStride) {
      p_zzz_last = i_high+j+z_currentShellMax;
      p_zzz_periodic = i_high_periodic+j+z_currentShellMin;
      for (p_zzz = i_high+j+z_currentShellMin; p_zzz < p_zzz_last; p_zzz++) {
	A[p_zzz_periodic] = A[p_zzz];
	p_zzz_periodic++;
      }
    }
    
    // update upper yz-plane
    for (j=y_currentShellMin; j < y_currentShellMax; j += y_unitStride) {
      p_zzz_last = i_low+j+z_currentShellMax;
      p_zzz_periodic = i_low_periodic+j+z_currentShellMin;
      for (p_zzz = i_low+j+z_currentShellMin; p_zzz < p_zzz_last; p_zzz++) {
	A[p_zzz_periodic] = A[p_zzz];
	p_zzz_periodic++;
      }
    }
    
    // update lower xz-plane
    for (i=x_currentShellMin; i < x_currentShellMax; i += x_unitStride) {
      p_zzz_last = i+j_high+z_currentShellMax;
      p_zzz_periodic = i+j_high_periodic+z_currentShellMin;
      for (p_zzz = i+j_high+z_currentShellMin; p_zzz < p_zzz_last; p_zzz++) {
	A[p_zzz_periodic] = A[p_zzz];
	p_zzz_periodic++;
      }
    }
    
    // update upper xz-plane
    for (i=x_currentShellMin; i < x_currentShellMax; i += x_unitStride) {
      p_zzz_last = i+j_low+z_currentShellMax;
      p_zzz_periodic = i+j_low_periodic+z_currentShellMin;
      for (p_zzz = i+j_low+z_currentShellMin; p_zzz < p_zzz_last; p_zzz++) {
	A[p_zzz_periodic] = A[p_zzz];
	p_zzz_periodic++;
      }
    }
    
    // update lower xy-plane
    for (i=x_currentShellMin; i < x_currentShellMax; i += x_unitStride) {
      p_zzz_last = i+y_currentShellMax+k_high;
      p_zzz_periodic = i+y_currentShellMin+k_high_periodic;
      for (p_zzz = i+y_currentShellMin+k_high; p_zzz < p_zzz_last; p_zzz += y_unitStride) {
	A[p_zzz_periodic] = A[p_zzz];
	p_zzz_periodic += y_unitStride;
      }
    }
    
    // update upper xy-plane
    for (i=x_currentShellMin; i < x_currentShellMax; i += x_unitStride) {
      p_zzz_last = i+y_currentShellMax+k_low;
      p_zzz_periodic = i+y_currentShellMin+k_low_periodic;
      for (p_zzz = i+y_currentShellMin+k_low; p_zzz < p_zzz_last; p_zzz += y_unitStride) {
	A[p_zzz_periodic] = A[p_zzz];
	p_zzz_periodic += y_unitStride;
      }
    }

    // update z-pencils
    p_zzz_last = i_low+j_low+z_currentShellMax;
    p_zzz_periodic = i_low_periodic+j_low_periodic+z_currentShellMin;
    for (p_zzz = i_low+j_low+z_currentShellMin; p_zzz < p_zzz_last; p_zzz++) {
      A[p_zzz_periodic] = A[p_zzz];
      p_zzz_periodic++;
    }

    p_zzz_last = i_low+j_high+z_currentShellMax;
    p_zzz_periodic = i_low_periodic+j_high_periodic+z_currentShellMin;
    for (p_zzz = i_low+j_high+z_currentShellMin; p_zzz < p_zzz_last; p_zzz++) {
      A[p_zzz_periodic] = A[p_zzz];
      p_zzz_periodic++;
    }

    p_zzz_last = i_high+j_low+z_currentShellMax;
    p_zzz_periodic = i_high_periodic+j_low_periodic+z_currentShellMin;
    for (p_zzz = i_high+j_low+z_currentShellMin; p_zzz < p_zzz_last; p_zzz++) {
      A[p_zzz_periodic] = A[p_zzz];
      p_zzz_periodic++;
    }

    p_zzz_last = i_high+j_high+z_currentShellMax;
    p_zzz_periodic = i_high_periodic+j_high_periodic+z_currentShellMin;
    for (p_zzz = i_high+j_high+z_currentShellMin; p_zzz < p_zzz_last; p_zzz++) {
      A[p_zzz_periodic] = A[p_zzz];
      p_zzz_periodic++;
    }

    // update y-pencils
    p_zzz_last = i_low+y_currentShellMax+k_low;
    p_zzz_periodic = i_low_periodic+y_currentShellMin+k_low_periodic;
    for (p_zzz = i_low+y_currentShellMin+k_low; p_zzz < p_zzz_last; p_zzz += y_unitStride) {
      A[p_zzz_periodic] = A[p_zzz];
      p_zzz_periodic += y_unitStride;
    }

    p_zzz_last = i_low+y_currentShellMax+k_high;
    p_zzz_periodic = i_low_periodic+y_currentShellMin+k_high_periodic;
    for (p_zzz = i_low+y_currentShellMin+k_high; p_zzz < p_zzz_last; p_zzz += y_unitStride) {
      A[p_zzz_periodic] = A[p_zzz];
      p_zzz_periodic += y_unitStride;
    }

    p_zzz_last = i_high+y_currentShellMax+k_low;
    p_zzz_periodic = i_high_periodic+y_currentShellMin+k_low_periodic;
    for (p_zzz = i_high+y_currentShellMin+k_low; p_zzz < p_zzz_last; p_zzz += y_unitStride) {
      A[p_zzz_periodic] = A[p_zzz];
      p_zzz_periodic += y_unitStride;
    }

    p_zzz_last = i_high+y_currentShellMax+k_low;
    p_zzz_periodic = i_high_periodic+y_currentShellMin+k_high_periodic;
    for (p_zzz = i_high+y_currentShellMin+k_high; p_zzz < p_zzz_last; p_zzz += y_unitStride) {
      A[p_zzz_periodic] = A[p_zzz];
      p_zzz_periodic += y_unitStride;
    }

    // update x-pencils
    p_zzz_last = x_currentShellMax+j_low+k_low;
    p_zzz_periodic = x_currentShellMin+j_low_periodic+k_low_periodic;
    for (p_zzz = x_currentShellMin+j_low+k_low; p_zzz < p_zzz_last; p_zzz += x_unitStride) {
      A[p_zzz_periodic] = A[p_zzz];
      p_zzz_periodic += x_unitStride;
    }

    p_zzz_last = x_currentShellMax+j_low+k_high;
    p_zzz_periodic = x_currentShellMin+j_low_periodic+k_high_periodic;
    for (p_zzz = x_currentShellMin+j_low+k_high; p_zzz < p_zzz_last; p_zzz += x_unitStride) {
      A[p_zzz_periodic] = A[p_zzz];
      p_zzz_periodic += x_unitStride;
    }

    p_zzz_last = x_currentShellMax+j_high+k_low;
    p_zzz_periodic = x_currentShellMin+j_high_periodic+k_low_periodic;
    for (p_zzz = x_currentShellMin+j_high+k_low; p_zzz < p_zzz_last; p_zzz += x_unitStride) {
      A[p_zzz_periodic] = A[p_zzz];
      p_zzz_periodic += x_unitStride;
    }

    p_zzz_last = x_currentShellMax+j_high+k_high;
    p_zzz_periodic = x_currentShellMin+j_high_periodic+k_high_periodic;
    for (p_zzz = x_currentShellMin+j_high+k_high; p_zzz < p_zzz_last; p_zzz += x_unitStride) {
      A[p_zzz_periodic] = A[p_zzz];
      p_zzz_periodic += x_unitStride;
    }

    // update corners
    A[i_low_periodic+j_low_periodic+k_low_periodic] = A[i_low+j_low+k_low];
    A[i_low_periodic+j_low_periodic+k_high_periodic] = A[i_low+j_low+k_high];
    A[i_low_periodic+j_high_periodic+k_low_periodic] = A[i_low+j_high+k_low];
    A[i_low_periodic+j_high_periodic+k_high_periodic] = A[i_low+j_high+k_high];
    A[i_high_periodic+j_low_periodic+k_low_periodic] = A[i_high+j_low+k_low];
    A[i_high_periodic+j_low_periodic+k_high_periodic] = A[i_high+j_low+k_high];
    A[i_high_periodic+j_high_periodic+k_low_periodic] = A[i_high+j_high+k_low];
    A[i_high_periodic+j_high_periodic+k_high_periodic] = A[i_high+j_high+k_high];
  }
}
