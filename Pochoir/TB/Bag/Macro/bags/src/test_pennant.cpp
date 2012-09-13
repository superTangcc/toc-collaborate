/*
 * test_pennant.cpp
 *
 *  Created on: 11/giu/2012
 *      Author: brix
 */

#include "test_pennant.h"

void TestPennant::SetUp() {
}

void TestPennant::TearDown() {
}

TEST_F(TestPennant, Constructor) {
	Pennant* p = new Pennant();
	EXPECT_NE((Pennant*)NULL, p);
	EXPECT_EQ(0, p->size());
	delete p;
}

/* Test merging two pennants */
TEST_P(TestPennant, MergeTwoPennants) {
	const unsigned long size = 1 << GetParam();
	vector<elem_t> x1(size);
	x1.assign(size, 1);
	vector<elem_t> x2(size);
	x2.assign(size, 2);
	Pennant p1(x1);
	Pennant p2(x2);
	Pennant p3;
	Pennant::merge(&p1, &p2, &p3);
	EXPECT_EQ(size * 2, p3.size());
//	p3.walk();
}

/* Test merging two pennants, then destroying them and check the result */
TEST_P(TestPennant, MergeDestroy) {
	const unsigned long size = 1 << GetParam();
	vector<elem_t> x1(size);
	vector<elem_t> x2(size);
	Pennant* p1 = new Pennant(x1);
	Pennant* p2 = new Pennant(x2);
	Pennant* p3 = new Pennant();
	Pennant::merge(p1, p2, p3);
	delete p1;
	delete p2;
	EXPECT_EQ(size * 2, p3->size());
//	p3->walk();
}

/* Test merging 3 not-NULL Pennants */
TEST_P(TestPennant, MergeThreePennants3) {
	const unsigned long size = 1 << GetParam();
	vector<elem_t> x1(size);
	x1.assign(size, 1);
	vector<elem_t> x2(size);
	x2.assign(size, 2);
	vector<elem_t> x3(size);
	x3.assign(size, 3);
	Pennant p1(x1);
	Pennant p2(x2);
	Pennant p3(x3);
	Pennant space;
	Pennant *result = Pennant::merge(&p1, &p2, &p3, &space);
	EXPECT_EQ(&space, result);
	EXPECT_EQ(size * 2, result->size());
	Pennant *carry = Pennant::carry(&p1, &p2, &p3);
	EXPECT_EQ(&p3, carry);
	EXPECT_EQ(size, carry->size());
}

/* Test merging 1 NULL + 2 not-NULL Pennants */
TEST_P(TestPennant, MergeThreePennants2) {
	const unsigned long size = 1 << GetParam();
	vector<elem_t> x1(size);
	x1.assign(size, 1);
	vector<elem_t> x2(size);
	x2.assign(size, 2);
	Pennant* v_p[4];
	v_p[0] = NULL;
	v_p[1] = new Pennant(x1);
	v_p[2] = new Pennant(x2);
	for (int i = 0; i < 3; i++) {
		Pennant space;
		Pennant *result = Pennant::merge(v_p[0], v_p[1], v_p[2], &space);
		EXPECT_EQ(&space, result);
		EXPECT_EQ(size * 2, result->size());
		Pennant *carry = Pennant::carry(v_p[0], v_p[1], v_p[2]);
		EXPECT_EQ(NULL, carry);
		/* Change position of the NULL element */
		v_p[i] = v_p[i+1];
		v_p[i+1] = NULL;
	}
}

/* Test merging 1 NULL + 2 not-NULL Pennants */
TEST_P(TestPennant, MergeThreePennants1) {
	const unsigned long size = 1 << GetParam();
	vector<elem_t> x1(size);
	x1.assign(size, 1);
	Pennant* v_p[4];
	v_p[0] = new Pennant(x1);
	v_p[1] = NULL;
	v_p[2] = NULL;
	for (int i = 0; i < 3; i++) {
		Pennant space;
		Pennant *result = Pennant::merge(v_p[0], v_p[1], v_p[2], &space);
		EXPECT_EQ(NULL, result);
		Pennant *carry = Pennant::carry(v_p[0], v_p[1], v_p[2]);
		EXPECT_EQ(v_p[i], carry);
		EXPECT_EQ(size, carry->size());
		/* Change position of the not-NULL element */
		v_p[i+1] = v_p[i];
		v_p[i] = NULL;
	}
}

/* Test merging 1 NULL + 2 not-NULL Pennants */
TEST_P(TestPennant, MergeThreePennants0) {
	const unsigned long size = 1 << GetParam();
	Pennant space;
	Pennant *result = Pennant::merge(NULL, NULL, NULL, &space);
	EXPECT_EQ(NULL, result);
	Pennant *carry = Pennant::carry(NULL, NULL, NULL);
	EXPECT_EQ(NULL, carry);
}

TEST_F(TestPennant, SmallPennantWalk) {
	vector<elem_t> x(big_size / 2);
	Pennant* p = new Pennant(x);
	string s = p->walk();
	cout << s << endl;
	delete p;
}

TEST_F(TestPennant, BigPennantWalk) {
	vector<elem_t> x(big_size / 2);
	Pennant* p1 = new Pennant(x);
	Pennant* p2 = new Pennant(x);
	Pennant* p3 = new Pennant();
	Pennant::merge(p1, p2, p3);
	string s = p3->walk();
	cout << s << endl;
	delete p1;
	delete p2;
	delete p3;
}


INSTANTIATE_TEST_CASE_P(Merge, TestPennant, testing::Range(0, 10));
