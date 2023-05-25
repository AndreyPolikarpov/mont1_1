#include <gtest/gtest.h>

#include "lib.h"

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

TEST(VersionTest, HandlesVersionTest) {
  std::vector<int> zero{0};
  EXPECT_EQ(split("", '.'), zero);

  std::vector<int> elef{11};
  EXPECT_EQ(split("11", '.'), elef);

  std::vector<int> test{0,0,0};
  EXPECT_EQ(split("..", '.'), test);

  test={11,0};
  EXPECT_EQ(split("11.", '.'), test);

  test={0,11};
  EXPECT_EQ(split(".11", '.'), test);

  test={11,22};
  EXPECT_EQ(split("11.22", '.'), test);
}
