#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "bag.h"


static int countit (int value __attribute__((__unused__)),
		    void *extra) {
    int *ep = (int*)extra;
    (*ep)++;
    return 0;
}

static int bag_count (BAG b) {
    int count=0;
    int r = bag_walk(b, countit, &count);
    assert(r==0);
    return count;
}

static void test0 (void) {
    BAG b = bag_create();
    assert(bag_count(b)==0);
    bag_destroy(b);
}

struct check_equals {
    bool *found;
    int  *ints;
    int   n;
};

static int checkit (int value, void *extra)
// Effect: extra is a check_equals structure. Return 0 iff value is one of the integers not found so far.
//   (In which case we set the corresponding found[i] boolean to be true, marking the object found0).
{
    struct check_equals *ce = (struct check_equals *)extra;
    for (int i=0; i<ce->n; i++) {
	if (!ce->found[i] && ce->ints[i]==value) {
	    ce->found[i]=true;
	    return 0;
	}
    }
    return 1; // notfound
}

static bool bag_content_equals(BAG b, int *ints, int n) {
    struct check_equals ce = {.found = calloc(n, sizeof(bool*)),
			      .ints  = ints,
			      .n     = n
    };
    for (int i=0; i<n; i++) ce.found[i]=false;
    int r = bag_walk(b, checkit, &ce);
    if (r==0) {
	// make sure everything was found
	for (int i=0; i<n; i++)
	    if (!ce.found[i]) {
		r=1;
		break;
	    }
    }
    free(ce.found);
    return r==0;
}

static void test1 (void) {
    BAG b = bag_create();
    b = bag_insert(b, 5);
    assert(bag_count(b)==1);
    int vals[] = {5};
    assert(bag_content_equals(b, vals, 1));
    bag_destroy(b);
}

static void test2 (void) {
    BAG b = bag_create();
    b = bag_insert(b, 2);
    b = bag_insert(b, 3);
    b = bag_insert(b, 5);
    b = bag_insert(b, 7);
    assert(bag_count(b)==4);
    int vals[] = {2,3,5,7};
    assert(bag_content_equals(b, vals, 4));
    bag_destroy(b);
}

static void test3 (void) {
    BAG a = bag_create();
    a = bag_insert(a, 1);
    BAG b = bag_create();
    a = bag_merge(a, b);
    assert(bag_count(a)==1);
    {
	int vals[] = {1};
	int nvals[] = {2};
	assert(bag_content_equals(a, vals, 1));
	assert(!bag_content_equals(a, nvals, 1));
    }

    BAG c = bag_create();
    c = bag_insert(c, 1);
    c = bag_insert(c, 1);
    c = bag_insert(c, 2);
    c = bag_insert(c, 3);
    assert(bag_count(c)==4);

    BAG d = bag_merge(a, c);
    assert(bag_count(d)==5);

    d = bag_insert(d, 4);
    d = bag_insert(d, 5);
    d = bag_insert(d, 6);
    BAG e = bag_create();
    e = bag_insert(e, 7);
    d = bag_merge(d, e);
    assert(bag_count(d)==9);
    bag_print(stdout, d);
    {
	int vals[] = {1,1,1,2,3,4,5,6,7};
	assert(bag_content_equals(d, vals, 9));
    }
    {
	for (int i=0; i<9; i++) {
	    int nvals[] = {1,1,1,2,3,4,5,6,7};
	    nvals[i]+=20;
	    assert(!bag_content_equals(d, nvals, 9));
	}
    }
    bag_destroy(d);
}

static void test4 (void)
// For each pair of bag sizes from 0 to 15 (there are 256 combinations), build a bag and merge them.
{
    int elements[32];
    for (int i=0; i<15; i++) {
	for (int j=0; j<15; j++) {
	    int nelts = 0;
	    BAG a = bag_create();
	    for (int ii=0; ii<i; ii++) {
		a = bag_insert(a, ii);
		elements[nelts++] = ii;
	    }
	    BAG b = bag_create();
	    for (int jj=0; jj<j; jj++) {
		b = bag_insert(b, 16+jj);
		elements[nelts++] = 16+jj;
	    }
	    BAG c = bag_merge(a, b);
	    assert(bag_count(c)==nelts);
	    assert(bag_content_equals(c, elements, nelts));
	    bag_destroy(c);
	}
    }
}

// According to gcov, we have 100% test coverage on the lines of bag.c
//  We have 96.3% of the branches taken both ways.  The remaining branch is in the assert that never fails in testin.
int main (int argc __attribute__((__unused__)), char *argv[] __attribute__((__unused__))) {
    for (int i=0; i<2; i++) {
	bag_set_testmode(i==0);
	test0();
	test1();
	test2();
	test3();
	test4();
    }
    return 0;
}
