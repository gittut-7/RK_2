

#include <gtest/gtest.h>
#include "count.h"

TEST(TEST, COUNT){
   EXPECT_EQ(count_("irjr"), 4);
}
