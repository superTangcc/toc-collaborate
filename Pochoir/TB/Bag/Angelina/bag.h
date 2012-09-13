/* #define NDEBUG */
#undef NDEBUG

#include <assert.h>

#ifndef NULL
#define NULL 0 
#endif

#define MAX_NUM_PENNANTS 64 
// #define MAX_NUM_PENNANTS 7

/* could have used bittwiddle trick */
#define MIN(x, y)  x < y ? x : y
#define MAX(x, y)  x > y ? x : y 


typedef struct Pennant_t {
    int elemt;
    struct Pennant_t *left;
    struct Pennant_t *right;
} Pennant;

typedef struct Bag_t {
    int next_avail_slot; // index for the next empty slot in pennants array
    Pennant * pennants[MAX_NUM_PENNANTS]; // stores pointers to pennants
} Bag;


Bag * create(); 
void destroy(Bag *bag); 
unsigned long long get_num_elemts(Bag *bag); 
int insert(Bag *bag, int elemt); 
int merge(Bag *b1, Bag *b2); 
void walk(Bag *bag); 

void check_content(Bag *bag, unsigned long long *array, int size); 
