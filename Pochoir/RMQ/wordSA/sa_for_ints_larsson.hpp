/* Implementiert die SA-Konstruktion von Larsson/Sadakane. */
#ifndef _sa_for_ints_larsson_hpp_
#define _sa_for_ints_larsson_hpp_

#include <stdlib.h>
#include <iostream>
using namespace std;

/** 
 * Konstruiert ein SA nach der Methode von Larsson/Sadakane.
 * Funktioniert fuer Integer-Alpphabete.
*/
class SAforIntsLarsson {
public:
	virtual void construct(int* text, int length, int k, int* p);

protected:
	enum {
		BUCK = ~(~0u>>1),	/* high bit */
		MAXI = ~0u>>1,		/* biggest int */
	};

	void qsort2(int*, int*, int);
	int	 ssortit(int[], int[], int, int, int*, int);
	void vecswap2(int*, int*, int);
	int* med3(int*, int*, int*, int*);
	void inssort(int*, int*, int);
};

#endif
