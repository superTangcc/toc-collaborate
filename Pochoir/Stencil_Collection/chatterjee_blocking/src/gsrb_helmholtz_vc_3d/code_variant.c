void select_code_variant(char *argv[]) {
  prefetch_index_type = atoi(argv[13]);
  prefetch_distance = atoi(argv[14]);
  rb_size = atoi(argv[15]);
}

void print_code_variant_parameters() {
  switch (prefetch_index_type) {
    case 0: printf("prefetch index type (none=0, single prefetch per register block=1, per plane=2, per pencil=3) = \n0,\n"); break;
    case 1: printf("prefetch index type (none=0, single prefetch per register block=1, per plane=2, per pencil=3) = \n1,\n"); break;
    case 2: printf("prefetch index type (none=0, single prefetch per register block=1, per plane=2, per pencil=3) = \n2,\n"); break;
    case 3: printf("prefetch index type (none=0, single prefetch per register block=1, per plane=2, per pencil=3) = \n3,\n"); break;
  }
  switch (prefetch_distance) {
    case 0: printf("prefetch distance = \n0, case number, 0,\n"); break;
    case 1: printf("prefetch distance = \n32, case number, 1,\n"); break;
    case 2: printf("prefetch distance = \n64, case number, 2,\n"); break;
    case 3: printf("prefetch distance = \n128, case number, 3,\n"); break;
    case 4: printf("prefetch distance = \n256, case number, 4,\n"); break;
    case 5: printf("prefetch distance = \n512, case number, 5,\n"); break;
  }
  switch (rb_size) {
    case 0: printf("register block size = \n2, 2, 2, case number, 0,\n"); break;
    case 1: printf("register block size = \n2, 2, 4, case number, 1,\n"); break;
    case 2: printf("register block size = \n2, 2, 8, case number, 2,\n"); break;
    case 3: printf("register block size = \n2, 4, 2, case number, 3,\n"); break;
    case 4: printf("register block size = \n2, 4, 4, case number, 4,\n"); break;
    case 5: printf("register block size = \n4, 2, 2, case number, 5,\n"); break;
    case 6: printf("register block size = \n4, 2, 4, case number, 6,\n"); break;
    case 7: printf("register block size = \n4, 4, 2, case number, 7,\n"); break;
    case 8: printf("register block size = \n4, 4, 4, case number, 8,\n"); break;
  }
  printf("\n");
}
