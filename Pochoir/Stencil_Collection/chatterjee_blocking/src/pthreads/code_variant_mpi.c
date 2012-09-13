void select_code_variant(char *argv[]) {
  int32_t prefetch_index_type_param, prefetch_distance_param, rb_size_param;
  int32_t parameters_set = 0;
  int32_t job_num = 0;

  for (prefetch_index_type_param=0; prefetch_index_type_param < 1; prefetch_index_type_param++) {
    for (prefetch_distance_param=0; prefetch_distance_param < 1; prefetch_distance_param++) {
      for (rb_size_param=0; rb_size_param < 2; rb_size_param++) {
        if (my_proc_num == (job_num % num_procs)) {
          prefetch_index_type = prefetch_index_type_param;
          prefetch_distance = prefetch_distance_param;
          rb_size = rb_size_param;
          parameters_set = 1;
        }
        job_num++;
      }
    }
  }
  if (!parameters_set) {
    exit(EXIT_SUCCESS);
  }
//  prefetch_index_type = atoi(argv[11]);
//  prefetch_distance = atoi(argv[12]);
//  rb_size = atoi(argv[13]);
}

void print_code_variant_parameters() {
  switch (prefetch_index_type) {
    case 0: strcat(output_str, "prefetch index type (none=0, single prefetch per register block=1, per plane=2, per pencil=3) = 0; "); break;
  }
  switch (prefetch_distance) {
    case 0: strcat(output_str, "prefetch distance = 0, case number, 0; "); break;
  }
  switch (rb_size) {
    case 0: strcat(output_str, "register block size = 1, 1, 1, case number, 0;"); break;
    case 1: strcat(output_str, "register block size = 1, 1, 2, case number, 1;"); break;
  }
}
