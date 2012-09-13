/*
 * test_bag.cpp
 *
 *  Created on: 12/giu/2012
 *      Author: brix
 */

#include "test_bag.h"

const unsigned long max_test_bag_size = 1e2;

void TestBag::SetUp() {
}

void TestBag::TearDown() {
}

TEST_F(TestBag, Constructor) {
	Bag* b = new Bag();
	EXPECT_NE((Bag*)NULL, b);
	EXPECT_EQ(0, b->size());
	delete b;
}

TEST_P(TestBag, InsertSinglePennant) {
	unsigned long size = 1 << GetParam();
	Bag* b = new Bag();
	vector<elem_t> x(size);
	Pennant p(x);
	b->insert(&p);
	EXPECT_EQ(size, b->size());
	vector<Pennant*> pens = b->pennants();
	for (int i = 0; i < pens.size() - 1; i++) {
		EXPECT_EQ((Pennant*)NULL, pens[i]);
	}
	delete b;
}

TEST_F(TestBag, InsertSingleRandomSizePennant) {
	const int num_tests = 100;
	for (int t = 0; t < num_tests; t++) {
		int size = 1 + (rand() % max_test_bag_size);
		Bag* b = new Bag();
		for (int i = 1; i <= size; i *= 2) {
			int psize = size & i;
			if (psize) {
				vector<elem_t> x(psize);
				Pennant* p = new Pennant(x);
				b->insert(p);
			}
		}
		EXPECT_EQ(size, b->size());
	}
}

TEST_F(TestBag, InsertElements) {
	unsigned long size = 1000;
	Bag* b = new Bag();
	for (int i = 0; i < size; i++)
		b->insert(i);
	EXPECT_EQ(size, b->size());
	vector<Pennant*> pens = b->pennants();
	for (int i = 0; i < pens.size() - 1; i++) {
		if (size & (1 << i))
			EXPECT_EQ((1 << i), pens[i]->size());
		else
			EXPECT_EQ((Pennant*)NULL, pens[i]);
	}
	delete b;
}

TEST_F(TestBag, MergeRandomBags) {
	int size1 = rand() % max_test_bag_size;
	int size2 = rand() % max_test_bag_size;
	Bag* b1 = new Bag();
	Bag* b2 = new Bag();
	for (int i = 1; i <= size1; i *= 2) {
		int psize = size1 & i;
		if (psize) {
			vector<elem_t> x(psize);
			Pennant* p = new Pennant(x);
			b1->insert(p);
		}
	}
	EXPECT_EQ(size1, b1->size());
	for (int i = 1; i <= size2; i *= 2) {
		int psize = size2 & i;
		if (psize) {
			vector<elem_t> x(psize);
			Pennant* p = new Pennant(x);
			b2->insert(p);
		}
	}
	EXPECT_EQ(size2, b2->size());
	b1->merge(*b2);
	EXPECT_EQ(size1 + size2, b1->size());
	vector<Pennant*> penns = b1->pennants();
	vector<Pennant*>::iterator itr;
	for (itr = penns.begin(); itr != penns.end(); itr++) {
		/* A pennant should either be NULL or have the correct size */
		EXPECT_TRUE((*itr == NULL) || ((*itr)->size() == 1<<(itr - penns.begin())));
	}
	delete b1;
	delete b2;
}

TEST_F(TestBag, SinglePennantWalk) {
	Bag* b = new Bag();
	vector<elem_t> x(big_size / 2);
	Pennant* p = new Pennant(x);
	b->insert(p);
	cout << b->walk() << endl;
	delete b;
	delete p;
}

TEST_F(TestBag, MultiPennantWalk) {
	Bag* b = new Bag();
	for (int i = 1; i < big_size; i *= 2) {
		vector<elem_t> x(i);
		Pennant* p = new Pennant(x);
		b->insert(p);
	}
	cout << b->walk() << endl;
	delete b;
}

INSTANTIATE_TEST_CASE_P(InsertSinglePennant, TestBag, testing::Range(0, 10));
