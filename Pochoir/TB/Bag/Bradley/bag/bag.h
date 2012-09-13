// Note: I use Liskov-style specifications of the abstractions I implement.

// Overview: Implement the BAG data structure described in bag.pdf

typedef struct bag *BAG;

BAG bag_create(void);
// Effect: Create and return an empty bag.

BAG bag_insert(BAG b, int i);
// Effect: Add i to b, returning the new bag.  The old bag b is no longer valid.  Free any memory that was used by the old bag, but not by the new bag.

BAG bag_merge(BAG, BAG);
// Effect: Given two bags, merge them to make a new bag.  The old bags are no longer valid.  Free any memory that was used by the old bag, but not by the new bag.

int bag_walk(BAG, int (*f)(int value, void *extra), void *extra);
// Effect: Apply f(e,extra) to every element e of the bag until either f has been applied to all the elements
//   of f, or f returns nonzero.   If f always returns zero, then bag_walk returns zero.  If f ever returns
//   nonzero, then bag_walk returns that value.
// Requires: The BAG must not be modified or destroyed by f.
// Rationale: The problem calls for printing, but that can be done by doing a bag_walk with a print function.
// Rationale: I implement CLU-style iterators using higher-order functions, rather than monkeying around with Java-style iterators and generators, 
//   which are a kludge.  I'd rather pay for the void* object to act as the closure to the downward function argument.

void bag_destroy(BAG);
// Effect: Free any memory used by the BAG.

void bag_check (BAG a);
// Effect: This is a helper function for testing.  Call this function to make sure that the bag looks OK.

void bag_set_testmode(bool do_testmode);
// Effect: This is a helper function.  Call this with true to run slower but check results with, for example,
//   bag_check, frequently.

void bag_print (FILE *f, BAG b);
// Effect: Print the contents of b in set notation.  For example if the bag includes 1, 3 and 1, you get  
//    "{1, 3, 1}\n"
// sent to f, possibly in some other order.
