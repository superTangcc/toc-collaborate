#define STATEMENT_TYPES 1	// complete or individual statements
#define READ_FROM_TYPES 1	// read from array or variable
#define POINTER_TYPES 1		// fixed or moving pointers
#define NEIGHBOR_INDEX_TYPES 1	// single ptr per register block, plane, or pencil
#define FMA_INS_TYPES 1		// non-FMA or FMA like instructions
#define PREFETCH_INDEX_TYPES 1	// no prefetch, or prefetch for register block, leading planes, or leading pencils
#define PREFETCH_DISTANCES 1	// the distances ahead being prefetched
#define RB_SIZES 2		// the number of register block sizes

void (*stencil_per_thread[STATEMENT_TYPES][READ_FROM_TYPES][POINTER_TYPES][NEIGHBOR_INDEX_TYPES][FMA_INS_TYPES][PREFETCH_INDEX_TYPES][PREFETCH_DISTANCES][RB_SIZES])() =
{{{{{{{{	&stencil_per_thread_co_ar_fi_re_noFMA_no_0_1x1x1RB, 	&stencil_per_thread_co_ar_fi_re_noFMA_no_0_1x1x2RB}
}
}
}
}
}
}
};
