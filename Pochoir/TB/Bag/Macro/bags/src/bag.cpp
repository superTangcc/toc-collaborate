/*
 * bag.cpp
 *
 *  Created on: 11/giu/2012
 *      Author: brix
 */

#include "bag.h"
#include <cmath>

/* Create an empty bag */
Bag::Bag() {
	size_ = 0;
}

/* Inserts a pennant in the bag */
void Bag::insert(Pennant* new_pennant) {
	int k = log2(new_pennant->size());
	if (k + 1 > pennants_.size()) {
		pennants_.insert(pennants_.end(), k - pennants_.size(), NULL);
		pennants_.insert(pennants_.end(), new_pennant);
	} else {
		Pennant* carry = new_pennant;
		unsigned long k = log2(new_pennant->size());
		while ((k < pennants_.size()) && (pennants_[k] != NULL)) {
				Pennant *tmp = new Pennant();
				carry = Pennant::merge(carry, pennants_[k], tmp);
				delete pennants_[k];
				pennants_[k] = NULL;
				k++;
		}
		if (k >= pennants_.size())
			pennants_.push_back(carry);
		else
		pennants_[k] = carry;
	}
	size_ += new_pennant->size();
}

/* Inserts a single element in the bag */
void Bag::insert(elem_t elem) {
	vector<elem_t> single(1, elem);
	insert(new Pennant(single));
}

/* Returns the number of elements in the bag */
unsigned long Bag::size() {
	return size_;
}

/* Walk through all the pennants in the bag
 */
string Bag::walk() {
	stringstream sstm;
	vector<Pennant*>::iterator itr;
	for (itr = pennants_.begin(); itr != pennants_.end(); itr++)
		if (*itr != NULL)
			sstm << (*itr)->walk();
	return sstm.str();
}

/* Merge another bag in the current bag
 */
void Bag::merge(Bag& bag2) {
	int n_min_pens = min(bag2.pennants_.size(), pennants_.size());
	if (bag2.pennants_.size() > pennants_.size()) { /* Store enough pennants */
		pennants_.insert(pennants_.end(), bag2.pennants_.size() - pennants_.size(), NULL);
	}
	Pennant* space = new Pennant();
	Pennant* result = NULL;
	Pennant* carry = NULL;
	for (int i = 0; i < n_min_pens; i++) {
		if (result) /* We may need a new pennant for the result of merge */
			space = new Pennant();
		carry = Pennant::carry(pennants_[i], bag2.pennants_[i], result);
		result = Pennant::merge(pennants_[i], bag2.pennants_[i], result, space);
		/* Carry of merge replaces the pennant at current position */
		pennants_[i] = carry;
	}
	if (result != NULL)
		if (n_min_pens == size_)
			pennants_.push_back(result);
		else
			pennants_[n_min_pens] = result;
	size_ += bag2.size();
}

/* Returns the pennants
 */
vector<Pennant*> Bag::pennants() {
	return pennants_;
}
