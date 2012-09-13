/*
 * test_bag.h
 *
 *  Created on: 12/giu/2012
 *      Author: brix
 */

#ifndef TEST_BAG_H_
#define TEST_BAG_H_

#include "gtest/gtest.h"

#include "bag.h"

class TestBag: public ::testing::TestWithParam<int> {
public:
	void SetUp();
	void TearDown();
};

#endif /* TEST_BAG_H_ */
