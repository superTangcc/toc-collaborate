/*
 * pennant.h
 *
 *  Created on: 2012-06-12
 *      Author: maryammehri
 */

#ifndef PENNANT_H_
#define PENNANT_H_





/* definition of a pennant */
typedef struct pennant {
 int k;
 int item;
 pennant *left;
 pennant *right;
} Pennant;

Pennant* Createpennant(int N);
void insertitem (Pennant *p, int k);
void PrintPennant( Pennant *root );
Pennant* mergePennants(Pennant* p1, Pennant* p2);
void merge3Pennants(Pennant* p1, Pennant* p2, Pennant* p3);


Pennant* Createpennant(int N){ //create a bag of degree N

	Pennant *root= (Pennant *) malloc (sizeof (Pennant));
	root->right=NULL; root->item = N+1; root->k=N;  //the root of pennant

	root->left= (Pennant *) malloc (sizeof (Pennant));
	Pennant *p = root->left;
	p->left=NULL; p->right=NULL; p->item = N; p->k=N;  //the only child of root

	if (N>1) {
		insertitem (p, p->k-1);
	}
	return root;
}

void insertitem (Pennant *p, int k){
	p->left = (Pennant *) malloc (sizeof (Pennant));
	p->right = (Pennant *) malloc (sizeof (Pennant));
	p->left->k = k;
	p->right->k = k;
	p->right->item = k;
	p->left->item = k;
	if ( k == 1) return;
	insertitem (p->left, k-1);
	insertitem (p->right,k-1);
	return;
}


void PrintPennant( Pennant *root ) {

   if ( root != NULL ) {  // (Otherwise, there's nothing to print.)
	   PrintPennant( root->left );    // Print items in left subtree.
      printf (" %d  ", root->item);     // Print the root item.
      PrintPennant( root->right );   // Print items in right subtree.
   }
}


Pennant* mergePennants(Pennant* p1, Pennant* p2){
	Pennant* RightC = p2->left;
	p2->left = p1;
	p1->right = RightC;
	p2->k= p2->k+1;
	p2->item= p2->item+1;
    return p2;
}

void merge3Pennants(Pennant** p1, Pennant** p2, Pennant** p3 ){
	switch ((*p1 != NULL)*4 + (*p2 != NULL)*2 + (*p3 != NULL )*1)
	{
	case 0:
		*p1=NULL; *p2=NULL; *p3 ==NULL; break;
	case 4:
		*p2=NULL;break;
	case 2:
	    *p1=*p2; *p2=NULL;break;
	case 1:
		*p1=*p3; *p2=NULL;break;
	case 6:
		*p2=mergePennants(*p1,*p2);*p1=NULL;break;
	case 5:
		*p2=mergePennants(*p1,*p3);*p1=NULL;break;
	case 3:
		*p2=mergePennants(*p2,*p3);*p1=NULL;break;
	case 7:
		*p2=mergePennants(*p2,*p3);break;

	}

}

void FreePennant(Pennant** p){
 if(*p == NULL) return;
 FreePennant(&((*p)->left));
 FreePennant(&((*p)->right));
 free(*p);
}

#endif /* PENNANT_H_ */

