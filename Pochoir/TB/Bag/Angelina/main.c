#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bag.h"

#define NUM_TESTS 15

static void test_empty() {
    Bag *bag = create();
    walk(bag);
    assert(get_num_elemts(bag) == 0); 
    destroy(bag);
    printf("Done testing empty.\n");
}

static void test_one() {
    Bag *bag = create();
    insert(bag, 1);
    walk(bag);
    assert(get_num_elemts(bag) == 1); 
    destroy(bag);
    printf("Done testing one elemt.\n");
}

/* should set the MAX_NUM_PENNANTS to something small to use this test */
#if MAX_NUM_PENNANTS <= 10
static void test_insert_full() {

    int err;
    unsigned long long i, j, k=1;
    unsigned long long array[MAX_NUM_PENNANTS];

    Bag *bag = create();

    for(i=0; i < MAX_NUM_PENNANTS; i++) {
        for(j=0; j < k; j++) {
            err = insert(bag, i);
            assert(err == 0);
        }
        array[i] = k;
        k = k << 1;
    }
    // walk(bag);
    check_content(bag, array, MAX_NUM_PENNANTS);
    err = insert(bag, 0);
    assert(err == 1);
    destroy(bag);

    printf("Done testing insert full.\n");
}

static void test_merge_full() {

    int err;
    int i, j, k = 1;
    Bag *b1 = create(), *b2 = create();
    
    // populate the two bags accordingly
    for(i=0; i < MAX_NUM_PENNANTS; i++) {
        for(j=0; j < k; j++) {
            err = insert(b1, i);
            assert(err == 0);
        } 
        for(j=0; j < k; j++) {
            err = insert(b2, i);
            assert(err == 0);
        } 
        k = k << 1;
    }

    err = merge(b1, b2);
    assert(err == 1); 

    destroy(b1);

    printf("Done testing merge full.\n");
}
#endif


static void test_merge_helper(int *a1, int *a2, int range) {

    int i, j; 
    unsigned long long k = 1;
    unsigned long long res[range]; // what the content should be after the merge
    int err;
    Bag *b1 = create(), *b2 = create();
    
    assert(range < MAX_NUM_PENNANTS);

    /* populate the two bags accordingly */
    for(i=0; i < range; i++) {
        if(a1[i]) {
            for(j=0; j < k; j++) {
                err = insert(b1, i);
                assert(err == 0);
            } 
        }
        if(a2[i]) {
            for(j=0; j < k; j++) {
                err = insert(b2, i);
                assert(err == 0);
            } 
        }
        res[i] = (a1[i] + a2[i]) * k;
        k = k << 1;
    }

    err = merge(b1, b2);
    assert(err == 0); 

    check_content(b1, res, range);
    printf("Num of elemts in the final bag: %llu.\n", get_num_elemts(b1)); 

    destroy(b1);
}

static void test_merge_all_cases() {
    /* these bit patterns represent which slots in the bag's pennants array
     * should be filled in order to test every switch cases in the merge
     * function */
    int a1[11] = {0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1};
    int a2[11] = {0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1};
    
    test_merge_helper(a1, a2, 11);

    printf("Done testing merge all cases.\n");
}

static void test_merge_large_set() {
        
    int a1[25] = {1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 
                  1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
                  1, 0, 1, 1, 1};
    int a2[25] = {0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 
                  0, 0, 1, 1, 0, 1, 0, 0, 0, 1,
                  0, 0, 0, 1, 0};

    printf("Start testing merge large set.\n");

    test_merge_helper(a1, a2, 25);

    printf("Done testing merge large set.\n");
}

/* generate a test case that merge two bags with
 * `range' number of slots filled in its penannt array 
 */
static void test_merge_random(int range) {
        
    int i;
    int a1[range];
    int a2[range];

    printf("Start testing merge random with range %d.\n", range);
    assert(range < MAX_NUM_PENNANTS);

    for(i=0; i < range; i++) {
        a1[i] = rand() & 0x1;
        a2[i] = rand() & 0x1;
    }

    test_merge_helper(a1, a2, range);

    printf("Done testing merge random.\n");
}

int main(int argc, char *argv[]) {
    
    int i;
    unsigned int seed = (unsigned int) time(0);

    test_empty();
    test_one();
    // should set the MAX_NUM_PENNANTS to something small to use this test
#if MAX_NUM_PENNANTS <= 10
    test_insert_full();
    test_merge_full();
#endif

    test_merge_all_cases();

    printf("Generate random test cases using seed %u.\n", seed);
    srand(seed);
    
    for(i=1; i <= NUM_TESTS; i++) {
        test_merge_random(i);
    }
    
    test_merge_large_set();

    return 0;
}



