#include "sa_for_ints_larsson.hpp"

/* Implementiert die SA-Konstruktion von Larsson/Sadakane.
 * Alphabet must be in the range from 1 to k with no holes. 
 * String 'text' *must* be 0-terminated!
 * text:   text for which suffix array is to be constructed
 * length: length of text (including 0-termination)
 * k:      # of different symbols in text (incl. final '0')
 * p:      array of size length which holds SA afterwards
*/

void SAforIntsLarsson::construct(int* text, int length, int k, int* p) {
	int i, l;
	int c, cc, ncc, lab, cum, nbuck;
	int result = -1;
	int *al;
	int *pl;

	nbuck = 0;

	pl = p + length - k;
	al = text;
	memset(pl, -1, k*sizeof(int));

	for(i=0; i<length; i++) {		/* (1) link */
		l = text[i];
		al[i] = pl[l];
		pl[l] = i;
	}

	lab = 0;			/* (2) create p and label a */
	cum = 0;
	i = 0;
	for(c = 0; c < k; c++){	
		for(cc = pl[c]; cc != -1; cc = ncc){
			ncc = al[cc];
			al[cc] = lab;
			cum++;
			p[i++] = cc;
		}
		if(lab + 1 == cum) {
			i--;
		} else {
			p[i-1] |= BUCK;
			nbuck++;
		}
		lab = cum;
	}

	result = ssortit(text, p, length, 1, p+i, nbuck);
}

int SAforIntsLarsson::ssortit(int a[], int p[], int n, int h, int *pe, int nbuck)
{
#define succ(i, h) ((t=(i)+(h))>=n? t-n: t)
	int *s, *ss, *packing, *sorting;
	int v, sv, vv, packed, lab, t, i;

	for(; h < n && p < pe; h=2*h) {
		packing = p;
		nbuck = 0;

		for(sorting = p; sorting < pe; sorting = s){
			/*
			 * find length of stuff to sort
			 */
			lab = a[*sorting];
			for(s = sorting; ; s++) {
				sv = *s;
				v = a[succ(sv & ~BUCK, h)];
				if(v & BUCK)
					v = lab;
				a[sv & ~BUCK] = v | BUCK;
				if(sv & BUCK)
					break;
			}
			*s++ &= ~BUCK;
			nbuck++;

			qsort2(sorting, a, s - sorting);

			v = a[*sorting];
			a[*sorting] = lab;
			packed = 0;
			for(ss = sorting + 1; ss < s; ss++) {
				sv = *ss;
				vv = a[sv];
				if(vv == v) {
					*packing++ = ss[-1];
					packed++;
				} else {
					if(packed) {
						*packing++ = ss[-1] | BUCK;
					}
					lab += packed + 1;
					packed = 0;
					v = vv;
				}
				a[sv] = lab;
			}
			if(packed) {
				*packing++ = ss[-1] | BUCK;
			}
		}
		pe = packing;
	}

	/*
	 * reconstuct the permutation matrix
	 * return index of the entire string
	 */
	v = a[0];
	for(i = 0; i < n; i++)
		p[a[i]] = i;

	return v;
}

/*
 * qsort from Bentley and McIlroy, Software--Practice and Experience
   23 (1993) 1249-1265, specialized for sorting permutations based on
   successors
 */
void SAforIntsLarsson::vecswap2(int *a, int *b, int n)
{
	while (n-- > 0) {
        	int t = *a;
		*a++ = *b;
		*b++ = t;
	}
}

#define swap2(a, b) { t = *(a); *(a) = *(b); *(b) = t; }

int* SAforIntsLarsson::med3(int *a, int *b, int *c, int *asucc)
{
	int va, vb, vc;

	if ((va=asucc[*a]) == (vb=asucc[*b]))
		return a;
	if ((vc=asucc[*c]) == va || vc == vb)
		return c;	   
	return va < vb ?
		  (vb < vc ? b : (va < vc ? c : a))
		: (vb > vc ? b : (va < vc ? a : c));
}

void SAforIntsLarsson::inssort(int *a, int *asucc, int n)
{
	int *pi, *pj, t;

	for (pi = a + 1; --n > 0; pi++)
		for (pj = pi; pj > a; pj--) {
			if(asucc[pj[-1]] <= asucc[*pj])
				break;
			swap2(pj, pj-1);
		}
}

void SAforIntsLarsson::qsort2(int *a, int *asucc, int n)
{
	int d, r, partval;
	int *pa, *pb, *pc, *pd, *pl, *pm, *pn, t;

	if (n < 15) {
		inssort(a, asucc, n);
		return;
	}
	pl = a;
	pm = a + (n >> 1);
	pn = a + (n-1);
	if (n > 30) { /* On big arrays, pseudomedian of 9 */
		d = (n >> 3);
		pl = med3(pl, pl+d, pl+2*d, asucc);
		pm = med3(pm-d, pm, pm+d, asucc);
		pn = med3(pn-2*d, pn-d, pn, asucc);
	}
	pm = med3(pl, pm, pn, asucc);
	swap2(a, pm);
	partval = asucc[*a];
	pa = pb = a + 1;
	pc = pd = a + n-1;
	for (;;) {
		while (pb <= pc && (r = asucc[*pb]-partval) <= 0) {
			if (r == 0) {
				swap2(pa, pb);
				pa++;
			}
			pb++;
		}
		while (pb <= pc && (r = asucc[*pc]-partval) >= 0) {
			if (r == 0) {
				swap2(pc, pd);
				pd--;
			}
			pc--;
		}
		if (pb > pc)
			break;
		swap2(pb, pc);
		pb++;
		pc--;
	}
	pn = a + n;
	r = pa-a;
	if(pb-pa < r)
		r = pb-pa;
	vecswap2(a, pb-r, r);
	r = pn-pd-1;
	if(pd-pc < r)
		r = pd-pc;
	vecswap2(pb, pn-r, r);
	if ((r = pb-pa) > 1)
		qsort2(a, asucc, r);
	if ((r = pd-pc) > 1)
		qsort2(a + n-r, asucc, r);
}
