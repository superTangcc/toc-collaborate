#include "bag.h"
#include "stdio.h"
#include "stdlib.h"

Pennant * create_pennant(int elemt) {
    Pennant *res = (Pennant *) malloc(sizeof(Pennant));
    res->left = res->right = NULL;
    res->elemt = elemt;

    return res;
}

void destroy_pennant(Pennant *p) {
    if(p->left) 
         destroy_pennant(p->left);
    if(p->right) 
         destroy_pennant(p->right);

    free(p);
}

Pennant * combine(Pennant *p1, Pennant *p2) {
    p1->right = p2->left;
    p2->left = p1;

    return p2;
}

void walk_pennant(Pennant *p) {
    if(p->elemt) {
        printf("%d ", p->elemt);
    }
    if(p->left) 
         walk_pennant(p->left);
    if(p->right) 
         walk_pennant(p->right);
}


/* check content of the pennant and mark the array based on the value found.
 * Should put assert on to use this function. 
 * Given how we use the array indicies to specify the content, we can only 
 * insert non-negative intergers into the bag.
 */
void check_pennant_content(Pennant *p, unsigned long long *array, int size ) {
    assert(p->elemt < size);
    array[p->elemt]--;
    
    if(p->left) 
         check_pennant_content(p->left, array, size);
    if(p->right) 
         check_pennant_content(p->right, array, size);
}

/* returns the address of a newly created (empty) Bag */
Bag * create() {
    int i;

    Bag *res = (Bag *) malloc(sizeof(Bag));
    res->next_avail_slot = 0;
    for(i=0; i < MAX_NUM_PENNANTS; i++) {
        res->pennants[i] = NULL;
    }

    return res;
}

/* this is only used in this file */
static void empty(Bag *bag) {
    int i;

    bag->next_avail_slot = 0;
    for(i=0; i < MAX_NUM_PENNANTS; i++) {
        bag->pennants[i] = NULL;
    }
}

/* destroy a bag created using the create function above */
void destroy(Bag *bag) {
    int i;
    for(i=0; i < bag->next_avail_slot; i++) {
        if( bag->pennants[i] != NULL ) {
            destroy_pennant(bag->pennants[i]);
        }
    }
    free(bag);
}

unsigned long long get_num_elemts(Bag *bag) {
    unsigned int i = 0; 
    unsigned long long k = 1;
    unsigned long long size = 0;
    
    for(i=0; i < bag->next_avail_slot; i++) {
        if(bag->pennants[i]) {
            size += k;
        }
        k = k << 1;
    }
    return size;
}

/* Should put assert on to use this function */
void check_next_avail_slot(Bag *bag) {
    int i, j = 0;
    for(i=0; i < MAX_NUM_PENNANTS; i++) {
        if(bag->pennants[i]) {
            j = i+1;
        }
    }
    assert(j == bag->next_avail_slot);
}

/* insert elemt into the bag 
 * This function returns zero if insertion succeeds and returns 
 * nonzero otherwise.
 * If insert failed, the bag will be emptied.
 */
int insert(Bag *bag, int elemt) {
    int i = 0;
    Pennant *pennant = create_pennant(elemt);
    int boundary = MIN(bag->next_avail_slot, MAX_NUM_PENNANTS-1);

#ifndef NDEBUG
    unsigned long long old_count = get_num_elemts(bag);
#endif

    do {
        if( bag->pennants[i] == NULL ) {
            bag->pennants[i] = pennant;
            pennant = NULL;
        } else {
            pennant = combine(bag->pennants[i], pennant);
            bag->pennants[i] = NULL;
        } 
        i++;
    } while(pennant && i <= boundary); 

    if( i > bag->next_avail_slot ) {
        assert(i == bag->next_avail_slot+1);
        bag->next_avail_slot = i;
    }

    assert( pennant || get_num_elemts(bag) == old_count+1 );
    if( pennant ) { /* bag is full; reset it */
        empty(bag);
        return 1;
    } else { /* pennant must be NULL if inserted successfully */
        check_next_avail_slot(bag);
        return 0;
    }
}

/* merge two bags together
 * The first bag will be returned with updated content, and the second
 * bag will be destroyed (memory freed). 
 * This function returns zero if merge succeeds and returns nonzero
 * otherwise.
 *
 * The merge can fail if the number of elements exceed the size the bag
 * can handle.  In which case, the first bag is emptied, and
 * the second bag is freed.
 */
int merge(Bag *b1, Bag *b2) {
    Pennant *carry = NULL;
    int i, mask = 0;
    int boundary = MAX(b1->next_avail_slot, b2->next_avail_slot);
    boundary = MIN(boundary, MAX_NUM_PENNANTS-1);
    
#ifndef NDEBUG
    unsigned long long count1 = get_num_elemts(b1);
    unsigned long long count2 = get_num_elemts(b2);
#endif

    for(i=0; i <= boundary; i++) {
        mask = 0;
        if(b1->pennants[i]) 
            mask |= 0x4;
        if(b2->pennants[i]) 
            mask |= 0x2;
        if(carry) 
            mask |= 0x1;
        
        /* implicitly, the sum for this round goes into b1->pennants[i] */
        switch(mask) {
            case 0: 
                break;
            case 1:
                b1->pennants[i] = carry;
                carry = NULL;
                break;
            case 2:
                b1->pennants[i] = b2->pennants[i];
                b2->pennants[i] = NULL;
                break;
            case 3:
                carry = combine(b2->pennants[i], carry);
                b2->pennants[i] = NULL;
                break;
            case 4:
                break;
            case 5:
                carry = combine(b1->pennants[i], carry);
                b1->pennants[i] = NULL;
                break;
            case 6:
                carry = combine(b1->pennants[i], b2->pennants[i]);
                b1->pennants[i] = b2->pennants[i] = NULL;
                break;
            case 7:
                carry = combine(b2->pennants[i], carry);
                b2->pennants[i] = NULL;
                break;
            default: assert(0); /* should never reach here */
        } 
    } 

    if(carry) { /* merge failed; reset the bag and return error */
        assert(i == MAX_NUM_PENNANTS);
        /* free the second bag */
        destroy(b2);
        empty(b1);
        return 1; 

    } else { /* merge succeeded; free the second bag */

        switch(mask) {
            case 0: /* the previous slot be filled based on how to
                       calculate our boundary */
                b1->next_avail_slot = boundary;
                assert(b1->pennants[boundary-1] != NULL);
                break;
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
                b1->next_avail_slot = boundary + 1;
                assert(b1->pennants[boundary] != NULL);
                break;
            default: 
                assert(0); /* can't happen */
        }
        
#ifndef NDEBUG
        for(i=0; i < MAX_NUM_PENNANTS; i++) {
            assert(b2->pennants[i] == NULL);
        }
        destroy(b2);
        check_next_avail_slot(b1);
        assert(get_num_elemts(b1) == count1 + count2); 
#endif
    }

    return 0;
}

void walk(Bag *bag) {
    int i;
    for(i=0; i < bag->next_avail_slot; i++) {
        if(bag->pennants[i]) {
            walk_pennant(bag->pennants[i]);
            printf("\n");
        }
    }
    printf("Done walking the bag.\n");
}

/* check content of the bag based on the array
 * If the bag content is correct, it should contain array[i] number of 
 * element with value i. 
 * Should put assert on to use this function. 
 * Given how we use the array indicies to specify the content, we can only 
 * insert non-negative intergers into the bag.
 */
void check_content(Bag *bag, unsigned long long *array, int size) {
    int i;

    for(i=0; i < bag->next_avail_slot; i++) {
        if(bag->pennants[i]) {
            check_pennant_content(bag->pennants[i], array, size);
        }
    }

    for(i=0; i < size; i++) {
if(array[i] != 0)
printf("array[%d] = %llu.\n", i, array[i]);
        assert(array[i] == 0);
    }
}

