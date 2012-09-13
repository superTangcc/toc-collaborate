//============================================================================
// Name        : main.cpp
// Author      : Marco Bressan
// Version     :
// Copyright   : 
// Description : Bags in C++, Ansi-style
//============================================================================

#include "bag.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sys/time.h>
using namespace std;

const int max_test_bag_size = 1e7;
const int num_tests = 10;

int main(int argc, char** argv) {
	struct timeval t0, t1;
	for (int t = 0; t < num_tests; t++) {
		int size1 = 1 + (rand() % max_test_bag_size);
		int size2 = 1 + (rand() % max_test_bag_size);
		cout << "size1 = " << size1 << ", size2 = " << size2 << endl;
		Bag* b1 = new Bag();
		Bag* b2 = new Bag();

		gettimeofday(&t0, NULL);
		for (int i = 1; i < size1; i *= 2) {
			int psize = size1 & i;
			if (psize) {
				vector<elem_t> x(psize);
				Pennant* p = new Pennant(x);
				b1->insert(p);
			}
		}
		gettimeofday(&t1, NULL);
		cout << "insert time 1 = ";
		cout << (t1.tv_sec + t1.tv_usec/1e6 - t0.tv_sec - t0.tv_usec/1e6) << endl;
		vector<Pennant*> penns = b1->pennants();
		vector<Pennant*>::iterator itr;

		gettimeofday(&t0, NULL);
		for (int i = 1; i < size2; i *= 2) {
			int psize = size2 & i;
			if (psize) {
				vector<elem_t> x(psize);
				Pennant* p = new Pennant(x);
				b2->insert(p);
			}
		}
		gettimeofday(&t1, NULL);
		cout << "insert time 2 = ";
		cout << (t1.tv_sec + t1.tv_usec/1e6 - t0.tv_sec - t0.tv_usec/1e6) << endl;
		penns = b2->pennants();

		gettimeofday(&t0, NULL);
		b1->merge(*b2);
		gettimeofday(&t1, NULL);
		cout << "merge time = ";
		cout << (t1.tv_sec + t1.tv_usec/1e6 - t0.tv_sec - t0.tv_usec/1e6) << endl;

		gettimeofday(&t0, NULL);
		string s = b1->walk();
		gettimeofday(&t1, NULL);
		if (s[0] > 128) cout << s[0] << endl;
		cout << "walk time = ";
		cout << (t1.tv_sec + t1.tv_usec/1e6 - t0.tv_sec - t0.tv_usec/1e6) << endl;
	}
}
