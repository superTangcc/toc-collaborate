/*
 * pennant.cpp
 *
 *  Created on: 11/giu/2012
 *      Author: brix
 */

#include "pennant.h"
#include <algorithm>

/* Creates an empty pennant */
Pennant::Pennant() {
	size_ = 0;
	content_ = NULL;
	subpen1 = NULL;
	subpen2 = NULL;
}

/* Creates and fills a pennant with the content of a vector
 * Assumes that the vector size is a power of two
 */
Pennant::Pennant(vector<elem_t>& content) {
	size_ = content.size();
	content_ = new vector<elem_t>(size_);
	content_->assign(content.begin(), content.end());
	subpen1 = NULL;
	subpen2 = NULL;
}

/* Merges two pennants and returns the result. The merge moves the elements only if
 * the resulting size is smaller than big_size, else it keeps pointers to the two
 * input pennants.
 */
Pennant* Pennant::merge(Pennant* p1, Pennant* p2, Pennant* result) {
	result->size_ = p1->size() + p2->size();
	if (result->size_ >= big_size) { /* just keep pointers to subpennants */
		result->subpen1 = p1;
		result->subpen2 = p2;
	} else { /* effectively merge the subpennants contents */
		result->content_ = new vector<elem_t>();
		result->content_->insert(result->content_->end(), p1->content_->begin(), p1->content_->end());
		result->content_->insert(result->content_->end(), p2->content_->begin(), p2->content_->end());
	}
	return result;
}

/* Merges three pennants and returns the result. Each pennant pointer must, for some k,
 * point to a pennant of size 1<<k or be NULL. The result is a pointer to a pennant
 * of size 1<<(k+1) if at least two pennants are not-NULL, and NULL otherwise.
 */
Pennant* Pennant::merge(Pennant* p1, Pennant* p2, Pennant* p3, Pennant* result) {
	int n_notnull = (p1 != NULL) + (p2 != NULL) + (p3 != NULL);
	if (n_notnull < 2) {
		return NULL;
	} else if (n_notnull == 2) {
		if (p1 == NULL)
			merge(p2, p3, result);
		else if (p2 == NULL)
			merge(p1, p3, result);
		else if (p3 == NULL)
			merge(p1, p2, result);
		return result;
	} else {
		merge(p1, p2, result);
		return result;
	}
}

/* Return the carry of merging three pennants. Each pennant pointer must, for some k,
 * point to a pennant of size 1<<k or be NULL. The result is a pointer to the last
 * pennant, if exactly one or exactly three of the input pennants are not-NULL, and
 * NULL otherwise.
 */
Pennant* Pennant::carry(Pennant* p1, Pennant* p2, Pennant* p3) {
	int n_notnull = (p1 != NULL) + (p2 != NULL) + (p3 != NULL);
	if (n_notnull == 1) {
		return max(max(p1, p2),p3);
	} else if (n_notnull == 3 ) {
		return p3;
	} else {
		return NULL;
	}
}

/* Walk through the pennant and print out the content
 */
string Pennant::walk() {
	stringstream sstm;
	if (content_ != NULL) {
		vector<elem_t>::iterator itr;
		for (itr = content_->begin(); itr != content_->end(); itr++)
			sstm << *itr << " ";
	} else {
		sstm << subpen1->walk();
		sstm << subpen2->walk();
	}
	return sstm.str();
}

/* Return the number of elements in the pennant
 */
unsigned long Pennant::size() {
	return size_;
}

/* Deletes the content.
 */
Pennant::~Pennant() {
	if (content_ != NULL)
		delete content_;
}
