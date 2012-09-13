#define _CACHE_ALIGNMENT __attribute__ ((aligned (64)))

typedef struct barrier_tag {
  volatile uint8_t ThreadIsWaiting[MAX_THREADS] _CACHE_ALIGNMENT;
  double x[MAX_THREADS] _CACHE_ALIGNMENT;
  int WaitFor;
} barrier_t;

void barrier_init(barrier_t *barrier, int count);
void barrier_destroy(barrier_t *barrier);
void barrier_wait(barrier_t *barrier, int thread_id);
