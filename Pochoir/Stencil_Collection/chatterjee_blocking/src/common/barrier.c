// SpMV barrier routines
//   Sam Williams (samw@cs.berkeley.edu)
//   University of California Berkeley
//   Lawrence Berkeley National Lab

void barrier_init(barrier_t *barrier, int count) {
  int i;
  barrier->WaitFor=count;
  for(i=0;i<MAX_THREADS;i++){
    barrier->ThreadIsWaiting[i]=(unsigned char)0;
    barrier->x[i]=2.0;
  }
  return;
}

void barrier_destroy(barrier_t *barrier) {
  // nothing was malloc'd
  return;
}

void barrier_wait(barrier_t *barrier, int thread_id) {
  int i;
  if (barrier->WaitFor == 1) return; // 1 thread waiting for itself

  barrier->ThreadIsWaiting[thread_id] = (unsigned char)1; // thread_id
  
  if (thread_id == 0) { // thread 0 is the master thread (it has sole write control on the barrier)
    int ThreadsWaiting = 0;
    while (ThreadsWaiting != barrier->WaitFor) { // not all threads are done
      ThreadsWaiting = 0;
      for (i=0;i<barrier->WaitFor; i++) {
	ThreadsWaiting+=barrier->ThreadIsWaiting[i]; // how many threads are done
      }
    }
    // master thread now resets all other threads (same way PPE does it on cell)
    for (i=0;i<barrier->WaitFor; i++) {
      barrier->ThreadIsWaiting[i]=0; // master thread now resets all other threads (same way PPE does it on cell)
    }
  }
  else { // other threads just wait for the master thread to release them
    while (barrier->ThreadIsWaiting[thread_id]) {
      barrier->x[thread_id]=1.0/barrier->x[thread_id];
    }
  }
  return;
}
