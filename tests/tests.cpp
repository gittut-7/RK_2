// Copyright 2021 Davydov Nikolay davy.nikola@gmail.com

#include <gtest/gtest.h>
#include "cos.h"

TEST(TEST, COS){
    EXPECT_EQ(cos(1), cos_(1));
    EXPECT_EQ(cos(2), cos_(2));
    EXPECT_EQ(cos(3), cos_(3));
}
