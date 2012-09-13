// Representation: We represent a BAG as either
//   NULL for an empty bag
//   Or:
//     a penant containing K items and a BAG containing only penants of size greater than K.
//     We can think of this as a linked list of penants, where the next item in the list is another bag.

#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "bag.h"


// use an assert function instead of a macro so hat we can don't get false positives from gcov branch coverage.
#define USING_GCOV
#ifdef USING_GCOV
static void assertf(bool b) { assert(b); }
#define Assert(a) assertf(a);
#else
#define Assert(a) assert(a)
#endif

bool testmode = false;
void bag_set_testmode(bool do_testmode) {
    testmode = do_testmode;
}

typedef struct treenode *TREENODE;

struct bag {
    int      pennant_size;
    TREENODE pennant;
    BAG      next;
};
    
struct treenode {
    TREENODE children[2];
    int      value;
};

BAG bag_create(void)
// Implements: bag_create as specified in bag.h.
{
    return 0; // return NULL, the empty bag.
}

static int treenode_walk (TREENODE pennant, int (*f)(int value, void *extra), void *extra)
// Helper function.
// Effect: Apply f to the elements in a penant.  Return 0 if f always returns 0, otherwise quit as soon as
//   f returns nonzero, returning that value.
{
    if (!pennant) return 0;
    {
	int r = f(pennant->value, extra);
	if (r) return r;
    }
    for (int i=0; i<2; i++) {
	int r = treenode_walk(pennant->children[i], f, extra);
	if (r) return r;
    }
    return 0;
}

int bag_walk(BAG b, int (*f)(int value, void *extra), void *extra) {
    if (!b) return 0;
    int r = treenode_walk(b->pennant, f, extra);
    if (r) return r;
    return bag_walk(b->next, f, extra);
}

struct printstate {
    int n_printed;
    FILE *f;
};

static int printit (int value, void *extra) {
    struct printstate *p = extra;
    if (p->n_printed>0) {
	printf(", ");
    }
    p->n_printed++;
    fprintf(p->f, "%d", value);
    return 0;
}

void bag_print (FILE *f, BAG b) {
    struct printstate p = {0,f};
    printf("{");
    bag_walk(b, printit, &p);
    printf("}\n");
}

static void treenode_destroy(TREENODE t) {
    if (t) {
	treenode_destroy(t->children[0]);
	treenode_destroy(t->children[1]);
	free(t);
    }
}

void bag_destroy(BAG b) {
    if (b) {
	bag_destroy(b->next);
	treenode_destroy(b->pennant);
	free(b);
    }
}

static TREENODE merge_pennants (TREENODE a, TREENODE b)
// Helper function.
// Effect: merge_pennants is a helper function.  It merges two pennants into one, returning a new one.  The old treenodes are no longer valid.
//  This merge runs in O(1) time.
// Modifies: a and b (they are destroyed).
// Requires: The two treenodes are the same size, which must be a power of two.
// Implemenation note: The merge of pennants is described in bag.pdf.
{
    TREENODE bchild = b->children[0];
    b->children[0] = a;
    a->children[1] = bchild;
    return b;
}


BAG bag_insert(BAG b, int i)
// Implements: bag_insert as specified in bag.h.
{
    TREENODE t= malloc(sizeof(*t));
    t->children[0] = t->children[1] = NULL;
    t->value = i;
    BAG a = malloc(sizeof(*a));
    a->pennant_size = 1;
    a->pennant = t;
    a->next = NULL;
    BAG result = bag_merge(a, b);
    if (testmode) bag_check(result);
    return result;
}

static BAG bag_merge_3 (BAG a, BAG b, BAG c)
// Helper function
// Requires: Bag a has exactly one pennant.  The pennants of bags b and c are all at least as big as a's.
// Effect: 
//   Merge a, b, and c together.
//   Destroys a, b, and c.
{
    if (b==NULL && c==NULL) return a;
    if (b==NULL) return bag_merge(a, c);
    if (c==NULL) return bag_merge(a, b);
    if (b->pennant_size == c->pennant_size) {
	a->next = bag_merge(b, c); // We know that b and c's pennants are bigger, so merging them will not produce a pennant of the saem size as a.
	return a;
    } else if (b->pennant_size > c->pennant_size) {
	BAG tmp=b;
	b=c;
	c=tmp;
    }
    // Fall through.
    Assert(b->pennant_size < c->pennant_size);
    if (a->pennant_size < b->pennant_size) {
	a->next = bag_merge(b,c); // a is smaller than b and c.
	return a;
    } else {
	a->pennant_size *= 2;
	a->pennant = merge_pennants(a->pennant, b->pennant);
	BAG result = bag_merge_3(a, b->next, c);
	free(b);
	return result;
    }
}
	

BAG bag_merge (BAG a, BAG b) 
// Implements: bag_merge as specified in bag.h.
{
    if (a==NULL) return b;
    if (b==NULL) return a;
    if (a->pennant_size < b->pennant_size) {
	a->next = bag_merge(a->next, b);
	return a;
    }
    if (a->pennant_size > b->pennant_size) {
	b->next = bag_merge(a, b->next);
	return b;
    }
    BAG newbag = malloc(sizeof(*newbag));
    newbag->pennant_size = a->pennant_size*2;
    newbag->pennant      = merge_pennants(a->pennant, b->pennant);
    newbag->next         = NULL;
    BAG result = bag_merge_3(newbag,
			     a->next,
			     b->next);
    free(a);
    free(b);
    if (testmode) bag_check(result);
    return result;
}

static void check_tree (TREENODE t, int size) {
    if (size==1) {
	Assert(t->children[0]==NULL);
	Assert(t->children[1]==NULL);
    } else {
	check_tree(t->children[0], size/2);
	check_tree(t->children[1], size/2);
    }
}

void bag_check (BAG a)
// Effect: Helper function to make sure that the bag is OK.
//  Check the representation invariants.
//   1) the pennants are strictly increasing in size.
//   2) each pennant is a power of two in size.
{
    if (a) {
	int psize = a->pennant_size;
	Assert(psize>=1);
	Assert(0==((psize-1) & psize)); // check that psize is a power of two.
	Assert(a->pennant->children[1]==NULL);
	if (psize==1) {
	    Assert(a->pennant->children[0]==NULL);
	} else {
	    check_tree(a->pennant->children[0], psize-1);
	}
	if (a->next) {
	    Assert(psize < a->next->pennant_size);
	    bag_check(a->next);
	}
    }
}
