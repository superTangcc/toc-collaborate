#include <time.h>

struct timespec timer_ApplicationStartTime;
int timer_initialized = 0;

void timer_init(void);
double timer_time(void);
