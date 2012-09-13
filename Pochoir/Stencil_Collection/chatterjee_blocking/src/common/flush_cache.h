#define FLUSH_CACHE_ARRAY_LENGTH 8388608
double FC[FLUSH_CACHE_ARRAY_LENGTH];

void init_flush_cache_array(void);
void flush_cache(void);
double flush_cache_checksum(void);
