#include <gtest/gtest.h>
#include <money.h>

class MoenyTest : public ::testing::Test {
 public:
  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

TEST_F(MoenyTest, testMultiplication) {
    Dollar five(5);
    five.times(2);
    EXPECT_EQ(10, five.amount_);
}
