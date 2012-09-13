/*
 * test_pennant.h
 *
 *  Created on: 11/giu/2012
 *      Author: brix
 */

#ifndef TEST_PENNANT_H_
#define TEST_PENNANT_H_

#include "gtest/gtest.h"

#include "pennant.h"

class TestPennant: public ::testing::TestWithParam<int> {
public:
	void SetUp();
	void TearDown();
};

#endif /* TEST_PENNANT_H_ */
