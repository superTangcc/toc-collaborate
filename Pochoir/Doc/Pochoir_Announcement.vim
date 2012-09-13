Dear xxxx,

The MIT Pochoir stencil compiler 1.0, as described in the attached
paper which will appear in the 2011 ACM Symposium on Parallelism in
Algorithms and Architectures (SPAA), has been released.  A stencil
computation repeatedly updates each point in a multidimensional grid
as a function of the point's nearby neighbors.  The Pochoir software
provides a simple specification language for stencil computations and
typically provides a 10-100 times performance boost over a serial loop
nest on a 12-core multicore processor.  Pochoir does not require you to
understand anything about parallel programming to avail yourself of the
performance advantage of multicore processors.

If you have stencil computations written in C/C++ and running on
a multicore processor under Linux, we invite you to try Pochoir.
The software is free (Gnu Public License).  Please email us at
pochoir@csail.mit.edu, and we will send you a tarball with the software.
You will also need the latest Intel C++ compiler (available with
C++ Composer XE 2011 for Linux), since Pochoir uses the Cilk Plus
multithreading extensions.

As documented in the attached paper, we have tested the Pochoir compiler
on a wide range of benchmarks, including heat equation, Conway's game of
life, finite-difference wave equation, lattice Boltzmann method (LBM),
RNA secondary structure prediction (RNA), pairwise sequence alignment
(PSA), longest common subsequence (LCS), and American put stock option
pricing (APOP).  The Pochoir specification language supports stencil
computations on any rectangular multidimensional grid up to 8 dimensions,
and it allows general periodic and nonperiodic boundaries to be specified,
including Dirichlet and Neumann boundary conditions.

Whether you personally are interested in Pochoir or not, if you know of
other researchers who perform stencil computations and wish to take full
advantage of multicore processors, I request that you please forward
this announcement to them.

Best!

-Pochoir Team
