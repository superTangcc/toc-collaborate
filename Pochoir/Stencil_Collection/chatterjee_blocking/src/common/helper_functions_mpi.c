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
  char temp_str[20];
  int i;

  for (i=0; i < num_measurements; i++) {
    sprintf(temp_str, "%2.5f, ", (measurements[i]/counts_per_sec));
    strcat(output_str, temp_str);
  }
  strcat(output_str, "\n");
}

inline void print_max_timer_measurements(double *measurements, uint32_t num_threads, uint32_t num_measurements, double counts_per_sec) {
  double max_measurements[num_measurements];
  double thread_time, max_time;
  char temp_str[20];
  int32_t i, j;

  strcat(output_str, "Max time over all threads: ");

  for (i=0; i < num_measurements; i++) {
    max_time = measurements[i];
    for (j=1; j < num_threads; j++) {
      thread_time = measurements[j * NUM_TRIALS + i];
      if (thread_time > max_time) {
	max_time = thread_time;
      }
    }
    max_measurements[i] = max_time/counts_per_sec;
    sprintf(temp_str, "%2.5f, ", max_measurements[i]);
    strcat(output_str, temp_str);
  }

  strcat(output_str, "; Median: ");
  sprintf(temp_str, "%2.5f;", find_median(max_measurements, NUM_TRIALS));
  strcat(output_str, temp_str);
}

inline void print_bandwidth_measurements(double *measurements, uint32_t bytes_transferred, uint32_t num_threads, uint32_t num_measurements, double counts_per_sec) {
  double max_measurements[num_measurements];
  double thread_time, max_time;
  char temp_str[20];
  int32_t i, j;

  strcat(output_str, "Bandwidth measurements based on max time over all threads: ");

  for (i=0; i < num_measurements; i++) {
    max_time = measurements[i];
    for (j=1; j < num_threads; j++) {
      thread_time = measurements[j * NUM_TRIALS + i];
      if (thread_time > max_time) {
	max_time = thread_time;
      }
    }
    max_measurements[i] = (bytes_transferred/(max_time/counts_per_sec))/1.0e9;
    sprintf(temp_str, "%3.4f, ", max_measurements[i]);
    strcat(output_str, temp_str);
  }

  strcat(output_str, "; Median: ");
  sprintf(temp_str, "%3.4f;", find_median(max_measurements, NUM_TRIALS));
  strcat(output_str, temp_str);
}
