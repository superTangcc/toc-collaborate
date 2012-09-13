/*
 * pennant.h
 *
 *  Created on: 11/giu/2012
 *      Author: brix
 */

#ifndef PENNANT_H_
#define PENNANT_H_

#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

typedef int elem_t;
const unsigned long big_size = 128;

class Pennant {
protected:
	vector<elem_t>* content_;
	Pennant* subpen1;
	Pennant* subpen2;
	unsigned long size_;
public:
	Pennant();
	Pennant(vector<elem_t>& content);
	~Pennant();
	static Pennant* merge(Pennant* pennant1, Pennant* pennant2, Pennant* result);
	static Pennant* merge(Pennant* pennant1, Pennant* pennant2, Pennant* pennant3, Pennant* result);
	static Pennant* carry(Pennant* pennant1, Pennant* pennant2, Pennant* pennant3);
	string walk();
	unsigned long size();
};


#endif /* PENNANT_H_ */
