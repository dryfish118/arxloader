#ifndef _GTEST_H_
#define _GTEST_H_

#include "arxmodule.h"

//
// ASSERT_* 系列的断言，当检查点失败时，退出当前函数
// EXPECT_* 系列的断言，当检查点失败时，继续往下执行。
//

#define EXPECT_EQ(val1, val2) \
  if (val1 != val2) \
  { \
    gDebuger->failure_eq(#val1, #val1); \
  }

#define EXPECT_NE(val1, val2) \
  if (val1 == val2) \
  { \
    gDebuger->failure_ne(#val1, #val1); \
  }

#define EXPECT_LE(val1, val2) \
  if (val1 > val2) \
  { \
    gDebuger->failure_le(#val1, #val1); \
  }

#define EXPECT_LT(val1, val2) \
  if (val1 >= val2) \
  { \
    gDebuger->failure_lt(#val1, #val1); \
  }

#define EXPECT_GE(val1, val2) \
  if (val1 < val2) \
  { \
    gDebuger->failure_ge(#val1, #val1); \
  }

#define EXPECT_GT(val1, val2) \
  if (val1 <= val2) \
  { \
    gDebuger->failure_gt(#val1, #val1); \
  }

# define ASSERT_EQ(val1, val2) \
  if (val1 != val2) \
  { \
    gDebuger->assert_eq(#val1, #val1); \
  }

# define ASSERT_NE(val1, val2) \
  if (val1 == val2) \
  { \
    gDebuger->assert_ne(#val1, #val1); \
  }

# define ASSERT_LE(val1, val2) \
  if (val1 > val2) \
  { \
    gDebuger->assert_le(#val1, #val1); \
  }

# define ASSERT_LT(val1, val2) \
  if (val1 >= val2) \
  { \
    gDebuger->assert_lt(#val1, #val1); \
  }

# define ASSERT_GE(val1, val2) \
  if (val1 < val2) \
  { \
    gDebuger->assert_ge(#val1, #val1); \
  }

# define ASSERT_GT(val1, val2) \
  if (val1 <= val2) \
  { \
    gDebuger->assert_gt(#val1, #val1); \
  }

#define EXPECT_STREQ(s1, s2) \
  if (AcString(s1) != s2) \
  { \
    gDebuger->failure_eq(#s1, #s2); \
  }

#define EXPECT_STRNE(s1, s2) \
  if (AcString(s1) == s2) \
  { \
    gDebuger->failure_ne(#s1, #s2); \
  }

#define EXPECT_STRCASEEQ(s1, s2) \
  if (AcString(s1).compareNoCase(s2) != 0) \
  { \
    gDebuger->failure_eq(#s1, #s2); \
  }

#define EXPECT_STRCASENE(s1, s2) \
  if (AcString(s1).compareNoCase(s2) == 0) \
  { \
    gDebuger->failure_ne(#s1, #s2); \
  }

#define ASSERT_STREQ(s1, s2) \
  if (AcString(s1) != s2) \
  { \
    gDebuger->assert_eq(#s1, #s2); \
  }

#define ASSERT_STRNE(s1, s2) \
  if (AcString(s1) == s2) \
  { \
    gDebuger->assert_ne(#s1, #s2); \
  }

#define ASSERT_STRCASEEQ(s1, s2) \
  if (AcString(s1).compareNoCase(s2) != 0) \
  { \
    gDebuger->assert_eq(#s1, #s2); \
  }

#define ASSERT_STRCASENE(s1, s2) \
  if (AcString(s1).compareNoCase(s2) == 0) \
  { \
    gDebuger->assert_ne(#s1, #s2); \
  }

#define EXPECT_DOUBLE_EQ(val1, val2) \
  if (val1 != val2) \
  { \
    gDebuger->failure_eq(#val1, #val2); \
  }

#define EXPECT_DOUBLE_NE(val1, val2) \
  if (val1 == val2) \
  { \
    gDebuger->failure_ne(#val1, #val2); \
  }

#define ASSERT_DOUBLE_EQ(val1, val2) \
  if (val1 != val2) \
  { \
    gDebuger->assert_ne(#val1, #val2); \
  }

#define ASSERT_DOUBLE_NE(val1, val2) \
  if (val1 == val2) \
  { \
    gDebuger->assert_ne(#val1, #val2); \
  }

// Defines a test.
//
//   TEST(FooTest, InitializesCorrectly) {
//     Foo foo;
//     EXPECT_TRUE(foo.StatusIsOK());
//   }

// #define GTEST_TEST(test_suite_name, test_name)             \
//   GTEST_TEST_(test_suite_name, test_name, ::testing::Test, \
//               ::testing::internal::GetTestTypeId())
// 
// #define TEST(test_suite_name, test_name) GTEST_TEST(test_suite_name, test_name)
// 
// #define TEST_F(test_fixture, test_name)\
//   GTEST_TEST_(test_fixture, test_name, test_fixture, \
//               ::testing::internal::GetTypeId<test_fixture>())

#endif  // _GTEST_H_
