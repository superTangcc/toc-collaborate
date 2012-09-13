/*
 * main.cpp
 *
 *  Created on: 2012-06-12
 *      Author: maryammehri
 */

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>

#include "bag.h"
#include "pennant.h"


int testInsert();
int testCreate();
int testInsert2array();
int testmerge();
int testmerge2();
int testmerge3();
int main() {
int i;

int j;

printf (" \n \n A pennant K has an item number K for its root, the children are numbered in a decreasing order, children in the same level have the same number \n ");

	printf ("\n ********************* \n ");
	testCreate(); //test create
	printf ("\n ********************* \n ");
	testInsert(); //insert to a NULL bag
	printf ("\n ********************* \n ");
	testInsert2array(); //insert to a general bag
	printf ("\n ********************* \n ");
	testmerge(); //merge
	printf ("\n ********************* \n ");
	testmerge2(); //merge
	printf ("\n ********************* \n ");
	testmerge3(); //merge

}

int testCreate(){
 int N=4;
 printf ("\n Create a bag of size %d with all NULLs \n ", N);
 Bag *b1 = CreateBag(N);
 walkBag(b1);  //print the bag
}


int testInsert(){
 int N=4;
 printf ("\n Create a full Bag (A bag with no Nulls) of size %d \n ", N);
 Bag *b1 = CreateBag(N);
 for(int i=1;i<N+1;i++){
  insert2bag(b1, Createpennant(i));
 }
 walkBag(b1);  //print the bag

}

int testInsert2array(){
 int N=4;
 printf ("\n Create a bag with every other element as NULL %d \n ", N);
 Bag *b1 = CreateBag(N);
 for(int i=1;i<N+1;i++){
  if (i%2 ==0) insert2bag(b1, Createpennant(i));
 }
 walkBag(b1);
 int k=1;
 printf ("\n Inserting a %d level pennant to the bag \n ", k);
 insert2bag(b1, Createpennant(k));
 walkBag(b1);  //print the bag
 k=2;
 printf ("\n Inserting a %d level pennant to the bag \n ", k);
 insert2bag(b1, Createpennant(k));
 walkBag(b1);  //print the bag
}
int testmerge(){
 int N=4;
 printf ("\n Create a bag with even elements as NULL %d \n ", N);
 Bag *b1 = CreateBag(N);
 for(int i=1;i<N+1;i++){
  if (i%2 == 0) insert2bag(b1, Createpennant(i));
 }
 walkBag(b1);

 N=4;
 printf ("\n Create a bag with odd element as NULL %d \n ", N);
 Bag *b2 = CreateBag(N);
 for(int i=1;i<N+1;i++){
  if (i%2 !=0) insert2bag(b2, Createpennant(i));
 }
 walkBag(b2);

 printf ("\n ****merging**** \n ");
 walkBag(MergeBags(b1,b2));
}

int testmerge2(){

 int N=4;
 printf ("\n one full bag %d \n ", N);
 Bag *b1 = CreateBag(N);
 for(int i=1;i<N+1;i++){
  insert2bag(b1, Createpennant(i));
  }
  walkBag(b1);

  printf ("\n Create a bag with odd elements as NULL %d \n ", N);
  Bag *b2 = CreateBag(N);
   for(int i=1;i<N+1;i++){
    if (i%2 !=0) insert2bag(b2, Createpennant(i));
   }
   walkBag(b2);

  printf ("\n ****merging**** \n ");
  walkBag(MergeBags(b1,b2));


}


int testmerge3(){
 int N=4;
 printf ("\n Create a bag with even elements as NULL %d \n ", N);
 Bag *b1 = CreateBag(N);
 for(int i=1;i<N+1;i++){
  if (i%2 == 0) insert2bag(b1, Createpennant(i));
 }
 walkBag(b1);

 N=4;
 printf ("\n Create a bag with even element as NULL %d \n ", N);
 Bag *b2 = CreateBag(N);
 for(int i=1;i<N+1;i++){
  if (i%2 !=0) insert2bag(b2, Createpennant(i));
 }
 walkBag(b2);

 printf ("\n ****merging**** \n ");
 walkBag(MergeBags(b1,b2));
}




