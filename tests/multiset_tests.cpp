#include <gtest/gtest.h>

#include "../s21_multiset.h"

TEST(multiset, allcase) {
  s21::multiset<int> my_multiset;
  my_multiset.Insert(10);
  my_multiset.Insert(10);
  my_multiset.Insert(10);
  my_multiset.Insert(10);
  my_multiset.Insert(10);
  my_multiset.Insert(10);
  my_multiset.Insert(10);
  my_multiset.Insert(10);
  my_multiset.Insert(10);
  my_multiset.Insert(10);
  EXPECT_EQ(my_multiset.size(), 10U);
  auto it = my_multiset.begin();
  my_multiset.erase(it);
  EXPECT_EQ(my_multiset.size(), 9U);
  it = my_multiset.begin();
  EXPECT_EQ(*it, 10);
  my_multiset.erase(it);
  EXPECT_EQ(my_multiset.size(), 8U);
}
