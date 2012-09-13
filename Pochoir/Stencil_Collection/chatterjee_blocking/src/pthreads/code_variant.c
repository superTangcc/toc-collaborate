void select_code_variant(char *argv[]) {
  statement_type = atoi(argv[13]);
  read_from_type = atoi(argv[14]);
  pointer_type = atoi(argv[15]);
  neighbor_index_type = atoi(argv[16]);
  fma_ins_type = atoi(argv[17]);
  prefetch_index_type = atoi(argv[18]);
  prefetch_distance = atoi(argv[19]);
  rb_size = atoi(argv[20]);
}

void print_code_variant_parameters() {
  switch (statement_type) {
    case 0: printf("statement type (complete=0, individual=1) = \n0,\n"); break;
  }
  switch (read_from_type) {
    case 0: printf("read from type (array=0, variable=1) = \n0,\n"); break;
  }
  switch (pointer_type) {
    case 0: printf("pointer type (fixed=0, moving=1) = \n0,\n"); break;
  }
  switch (neighbor_index_type) {
    case 0: printf("neighbor index type (single ptr per register block=0, per plane=1, per pencil=2) = \n0,\n"); break;
  }
  switch (fma_ins_type) {
    case 0: printf("FMA instruction type (not FMA-like=0, FMA-like=1) = \n0,\n"); break;
  }
  switch (prefetch_index_type) {
    case 0: printf("prefetch index type (none=0, single prefetch per register block=1, per plane=2, per pencil=3) = \n0,\n"); break;
  }
  switch (prefetch_distance) {
    case 0: printf("prefetch distance = \n0, case number, 0,\n"); break;
  }
  switch (rb_size) {
    case 0: printf("register block size = \n1, 1, 1, case number, 0,\n"); break;
    case 1: printf("register block size = \n1, 1, 2, case number, 1,\n"); break;
  }
  printf("\n");
}
