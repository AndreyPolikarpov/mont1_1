#include <gtest/gtest.h>

#include "lib.h"

TEST(VersionTest, HandlesVersionTest) {
  EXPECT_GT(version(), 0);
}
