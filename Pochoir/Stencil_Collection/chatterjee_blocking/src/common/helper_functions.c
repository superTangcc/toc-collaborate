double find_median(double *measurements, uint32_t num_measurements) {
  double median, temp;
  uint32_t i, j, min_idx;

  // sort the array first
  for (i=0; i < num_measurements; i++) {
    min_idx = i;
    for (j=(i+1); j < num_measurements; j++) {
      if (measurements[j] < measurements[min_idx]) {
	min_idx = j;
      }
    }
    temp = measurements[i];
    measurements[i] = measurements[min_idx];
    measurements[min_idx] = temp;
  }

  if ((num_measurements % 2) == 1) {
    median = measurements[num_measurements/2];
  }
  else {
    median = (measurements[num_measurements/2 - 1] + measurements[num_measurements/2])/2.0;
  }

  return median;
}

inline void print_timer_measurements(double *measurements, uint32_t num_measurements, double counts_per_sec) {
  uint32_t i;

  for (i=0; i < num_measurements; i++) {
    printf("%2.5f, ", (measurements[i]/counts_per_sec));
  }
  printf("\n");
}

inline void print_max_timer_measurements(double *measurements, uint32_t num_threads, uint32_t num_measurements, double counts_per_sec) {
  double max_measurements[num_measurements];
  double thread_time, max_time;
  int32_t i, j;

  printf("Max time over all threads:\n");

  for (i=0; i < num_measurements; i++) {
    max_time = measurements[i];
    for (j=1; j < num_threads; j++) {
      thread_time = measurements[j * NUM_TRIALS + i];
      if (thread_time > max_time) {
	max_time = thread_time;
      }
    }
    max_measurements[i] = max_time/counts_per_sec;
    printf("%2.5f, ", max_measurements[i]);
    fflush(stdout);
  }

  printf("\nMedian Time: %2.5f\n", find_median(max_measurements, NUM_TRIALS));
  fflush(stdout);
}

inline void print_bandwidth_measurements(double *measurements, uint32_t bytes_transferred, uint32_t num_threads, uint32_t num_measurements, double counts_per_sec) {
  double max_measurements[num_measurements];
  double thread_time, max_time;
  int32_t i, j;

  printf("Bandwidth measurements based on max time over all threads:\n");

  for (i=0; i < num_measurements; i++) {
    max_time = measurements[i];
    for (j=1; j < num_threads; j++) {
      thread_time = measurements[j * NUM_TRIALS + i];
      if (thread_time > max_time) {
	max_time = thread_time;
      }
    }
    max_measurements[i] = (bytes_transferred/(max_time/counts_per_sec))/1.0e9;
    printf("%3.4f, ", max_measurements[i]);
    fflush(stdout);
  }

  printf("\nMedian Bandwidth: %3.4f\n", find_median(max_measurements, NUM_TRIALS));
  fflush(stdout);
}
