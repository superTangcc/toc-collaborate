/*
 * bag.h
 *
 *  Created on: 2012-06-12
 *      Author: maryammehri
 */


#ifndef BAG_H_
#define BAG_H_
#include "pennant.h"

/* definition of a bag */
typedef struct Bag {
 Pennant *p;
 Bag *next;
} Bag;

Bag* CreateBag(int N);;
void WalkBag(Bag* b1);
void InsertBag(int p, Bag* pBag);
Bag* MergeBags(Bag * b1, Bag *b2);
void Free1Bag(Bag** b1);
void FreeBags(Bag** b1);

Bag* CreateBag(int N){ //create a bag of size N
	int i=1;
	Bag *root, *bag;

	root = (Bag *)malloc(sizeof(Bag));
	if (root == NULL) {
		printf("Malloc failed\n");
		return NULL;
	}
	root->next=NULL; root->p =NULL;
    bag=root;
	while (i!=N){
		bag->next = (Bag *)malloc(sizeof(Bag));
	    if (bag->next == NULL) {
		printf("Malloc failed\n");
		return NULL;
	    }
	    bag=bag->next;
	    bag->next=NULL; bag->p = NULL;
	    i++;
	}
	return root;
}


// insert an item to a bag

void insert2bag(Bag *bag, Pennant *p)
{
   int i=1;
   Bag *root = bag;

   while(i != p->k && bag->next != NULL){
	   bag = bag->next;
	   i++;
   }

   if (bag->next == NULL && i != p->k){
	   bag->next = CreateBag(p->k-i);
	   insert2bag (root, p);
   return ;
   }

   if(bag->p != NULL) {

	   p = mergePennants (bag->p, p);
	   bag->p=NULL;
	   insert2bag (root, p);
   }
   else
	   bag->p = p;

}

void walkBag(Bag *b){
    if (b == NULL) return;
    int i=1;
	while (b!=NULL){
	PrintPennant( b->p );
	b=b->next;
	printf ("pennant %d \n ", i);
	i++;
	}

}



Bag* MergeBags(Bag * b1, Bag *b2){
	int i=1;
	Pennant *Paux;
	Paux=NULL;
	Bag *root=b1;
	while (b1 != NULL && b2 != NULL){ // for now we consider the simpel case of bags of same size get merged
		merge3Pennants(&b1->p, &Paux, &b2->p);
		b1=b1->next; b2=b2->next;
		i++;
	}
	if (Paux != NULL) insert2bag(root, Paux);
	return root;

}

void FreeBags(Bag** b1){
	if(*b1==NULL) return;
	if((*b1)->next!=NULL)
	FreeBags(&((*b1)->next));
	Free1Bag(b1);
	}



void Free1Bag(Bag** b1){
	FreePennant(&((*b1)->p));
	free(*b1);
}


#endif 

