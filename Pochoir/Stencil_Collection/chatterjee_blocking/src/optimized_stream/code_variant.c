void select_code_variant(char *argv[]) {
  read_arrays_case = numReadArraysPerThread - 0;
  write_arrays_case = numWriteArraysPerThread - 0;
  write_type_case = atoi(argv[6]);
  load_type_case = atoi(argv[7]);
  loop_unroll_case = atoi(argv[8]);
  prefetch_distance_case = atoi(argv[9]);
}

void print_code_variant_parameters() {
  switch (write_type_case) {
    case 0: printf("write type (store=0, stream=1) = \n0,\n"); break;
    case 1: printf("write type (store=0, stream=1) = \n1,\n"); break;
  }
  switch (load_type_case) {
    case 0: printf("load type (implicit=0, explicit=1) = \n0,\n"); break;
    case 1: printf("load type (implicit=0, explicit=1) = \n1,\n"); break;
  }
  switch (loop_unroll_case) {
    case 0: printf("loop_unroll = \n1, case number, 0,\n"); break;
    case 1: printf("loop_unroll = \n2, case number, 1,\n"); break;
    case 2: printf("loop_unroll = \n3, case number, 2,\n"); break;
    case 3: printf("loop_unroll = \n4, case number, 3,\n"); break;
    case 4: printf("loop_unroll = \n5, case number, 4,\n"); break;
    case 5: printf("loop_unroll = \n6, case number, 5,\n"); break;
    case 6: printf("loop_unroll = \n7, case number, 6,\n"); break;
    case 7: printf("loop_unroll = \n8, case number, 7,\n"); break;
    case 8: printf("loop_unroll = \n9, case number, 8,\n"); break;
    case 9: printf("loop_unroll = \n10, case number, 9,\n"); break;
  }
  switch (prefetch_distance_case) {
    case 0: printf("prefetch distance = \n-1, case number, 0,\n"); break;
    case 1: printf("prefetch distance = \n0, case number, 1,\n"); break;
    case 2: printf("prefetch distance = \n32, case number, 2,\n"); break;
    case 3: printf("prefetch distance = \n64, case number, 3,\n"); break;
    case 4: printf("prefetch distance = \n128, case number, 4,\n"); break;
    case 5: printf("prefetch distance = \n256, case number, 5,\n"); break;
    case 6: printf("prefetch distance = \n512, case number, 6,\n"); break;
  }
  printf("\n");
}
