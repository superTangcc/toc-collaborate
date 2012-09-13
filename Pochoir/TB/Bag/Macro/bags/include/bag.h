/*
 * bag.h
 *
 *  Created on: 11/giu/2012
 *      Author: brix
 */

#ifndef BAG_H_
#define BAG_H_

#include "pennant.h"
#include <vector>
#include <sstream>
using namespace std;

class Bag {
protected:
	vector<Pennant*> pennants_;
	unsigned long size_;
public:
	Bag();
	void insert(elem_t element);
	void insert(Pennant* pennant);
	void merge(Bag& bag2);
	string walk();
	unsigned long size();
	vector<Pennant*> pennants();
};


#endif /* BAG_H_ */
