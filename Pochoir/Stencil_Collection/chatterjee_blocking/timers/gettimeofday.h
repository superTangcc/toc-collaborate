#include <sys/time.h>

struct timeval timer_ApplicationStartTime;
int timer_initialized = 0;

void timer_init(void);
double timer_time(void);
