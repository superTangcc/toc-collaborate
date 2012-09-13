#define PARALLEL 1

#if PARALLEL
#include "tbb/parallel_for.h"
#include "tbb/parallel_invoke.h"
#include "tbb/blocked_range.h"
#include "tbb/task_scheduler_init.h"
#endif