#include <gtest/gtest.h>

#include <array>

#include "../s21_array.h"

TEST(array_constructor, case1) {
  s21::array<int, 4> s21_arr_int;
  s21::array<double, 4> s21_arr_double;
  s21::array<std::string, 4> s21_arr_string;

  EXPECT_EQ(s21_arr_int.size(), 4U);
  EXPECT_EQ(s21_arr_double.size(), 4U);
  EXPECT_EQ(s21_arr_string.size(), 4U);
}

TEST(array_constructor, case2) {
  s21::array<int, 5> s21_arr_int{1, 4, 8, 9, 1};
  s21::array<double, 5> s21_arr_double{1.4, 4.8, 8.9, 9.1, 1.1};
  s21::array<std::string, 5> s21_arr_string{"Hello", ",", "world", "!", "!!"};

  EXPECT_EQ(s21_arr_int.size(), 5U);
  EXPECT_EQ(s21_arr_int[0], 1);

  EXPECT_EQ(s21_arr_double.size(), 5U);
  EXPECT_EQ(s21_arr_double[0], 1.4);

  EXPECT_EQ(s21_arr_string.size(), 5U);
  EXPECT_EQ(s21_arr_string[0], "Hello");
}

TEST(array_constructor, case3) {
  s21::array<int, 4> s21_arr_ref_int{1, 4, 8, 9};
  s21::array<int, 4> s21_arr_res_int(s21_arr_ref_int);

  s21::array<double, 4> s21_arr_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::array<double, 4> s21_arr_res_double(s21_arr_ref_double);

  s21::array<std::string, 4> s21_arr_ref_string{"Hello", ",", "world", "!"};
  s21::array<std::string, 4> s21_arr_res_string(s21_arr_ref_string);

  EXPECT_EQ(s21_arr_ref_int.size(), s21_arr_res_int.size());
  EXPECT_EQ(s21_arr_ref_int[0], s21_arr_res_int[0]);
  EXPECT_EQ(s21_arr_ref_int[1], s21_arr_res_int[1]);
  EXPECT_EQ(s21_arr_ref_int[2], s21_arr_res_int[2]);
  EXPECT_EQ(s21_arr_ref_int[3], s21_arr_res_int[3]);

  EXPECT_EQ(s21_arr_ref_double.size(), s21_arr_res_double.size());
  EXPECT_EQ(s21_arr_ref_double[0], s21_arr_res_double[0]);
  EXPECT_EQ(s21_arr_ref_double[1], s21_arr_res_double[1]);
  EXPECT_EQ(s21_arr_ref_double[2], s21_arr_res_double[2]);
  EXPECT_EQ(s21_arr_ref_double[3], s21_arr_res_double[3]);

  EXPECT_EQ(s21_arr_ref_string.size(), s21_arr_res_string.size());
  EXPECT_EQ(s21_arr_ref_string[0], s21_arr_res_string[0]);
  EXPECT_EQ(s21_arr_ref_string[1], s21_arr_res_string[1]);
  EXPECT_EQ(s21_arr_ref_string[2], s21_arr_res_string[2]);
  EXPECT_EQ(s21_arr_ref_string[3], s21_arr_res_string[3]);
}

TEST(array_constructor, case4) {
  s21::array<int, 4> s21_arr_ref_int{1, 4, 8, 9};
  s21::array<int, 4> s21_arr_res_int = std::move(s21_arr_ref_int);

  s21::array<double, 4> s21_arr_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::array<double, 4> s21_arr_res_double = std::move(s21_arr_ref_double);

  s21::array<std::string, 4> s21_arr_ref_string{"Hello", ",", "world", "!"};
  s21::array<std::string, 4> s21_arr_res_string = std::move(s21_arr_ref_string);

  EXPECT_EQ(s21_arr_res_int.size(), 4U);
  EXPECT_EQ(s21_arr_res_int[0], 1);
  EXPECT_EQ(s21_arr_res_int[1], 4);
  EXPECT_EQ(s21_arr_res_int[2], 8);
  EXPECT_EQ(s21_arr_res_int[3], 9);

  EXPECT_EQ(s21_arr_res_double.size(), 4U);
  EXPECT_EQ(s21_arr_res_double[0], 1.4);
  EXPECT_EQ(s21_arr_res_double[1], 4.8);
  EXPECT_EQ(s21_arr_res_double[2], 8.9);
  EXPECT_EQ(s21_arr_res_double[3], 9.1);

  EXPECT_EQ(s21_arr_res_string.size(), 4U);
  EXPECT_EQ(s21_arr_res_string[0], "Hello");
  EXPECT_EQ(s21_arr_res_string[1], ",");
  EXPECT_EQ(s21_arr_res_string[2], "world");
  EXPECT_EQ(s21_arr_res_string[3], "!");
}

TEST(array_constructor, case6) {
  s21::array<int, 4> s21_arr_ref_int{1, 4, 8, 9};
  s21::array<int, 4> s21_arr_res_int;
  s21_arr_res_int = std::move(s21_arr_ref_int);

  s21::array<double, 4> s21_arr_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::array<double, 4> s21_arr_res_double;
  s21_arr_res_double = std::move(s21_arr_ref_double);

  s21::array<std::string, 4> s21_arr_ref_string{"Hello", ",", "world", "!"};
  s21::array<std::string, 4> s21_arr_res_string;
  s21_arr_res_string = std::move(s21_arr_ref_string);

  EXPECT_EQ(s21_arr_res_int.size(), 4U);
  EXPECT_EQ(s21_arr_res_int[0], 1);
  EXPECT_EQ(s21_arr_res_int[1], 4);
  EXPECT_EQ(s21_arr_res_int[2], 8);
  EXPECT_EQ(s21_arr_res_int[3], 9);

  EXPECT_EQ(s21_arr_res_double.size(), 4U);
  EXPECT_EQ(s21_arr_res_double[0], 1.4);
  EXPECT_EQ(s21_arr_res_double[1], 4.8);
  EXPECT_EQ(s21_arr_res_double[2], 8.9);
  EXPECT_EQ(s21_arr_res_double[3], 9.1);

  EXPECT_EQ(s21_arr_res_string.size(), 4U);
  EXPECT_EQ(s21_arr_res_string[0], "Hello");
  EXPECT_EQ(s21_arr_res_string[1], ",");
  EXPECT_EQ(s21_arr_res_string[2], "world");
  EXPECT_EQ(s21_arr_res_string[3], "!");
}

TEST(array_at, case1) {
  s21::array<int, 4> s21_arr_int{1, 4, 8, 9};
  s21::array<double, 4> s21_arr_double{1.4, 4.8, 8.9, 9.1};
  s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_arr_int.at(0), 1);
  EXPECT_EQ(s21_arr_double.at(0), 1.4);
  EXPECT_EQ(s21_arr_string.at(0), "Hello");
}

TEST(array_at, case2) {
  s21::array<int, 4> s21_arr_int{1, 4, 8, 9};
  s21::array<double, 4> s21_arr_double{1.4, 4.8, 8.9, 9.1};
  s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

  EXPECT_THROW(s21_arr_int.at(5), std::out_of_range);
  EXPECT_THROW(s21_arr_double.at(5), std::out_of_range);
  EXPECT_THROW(s21_arr_string.at(5), std::out_of_range);
}

TEST(array_at, case3) {
  s21::array<int, 0> s21_arr_int;
  s21::array<double, 0> s21_arr_double;
  s21::array<std::string, 0> s21_arr_string;

  EXPECT_THROW(s21_arr_int.at(5), std::out_of_range);
  EXPECT_THROW(s21_arr_double.at(5), std::out_of_range);
  EXPECT_THROW(s21_arr_string.at(5), std::out_of_range);
}

TEST(array_square_braces, case1) {
  s21::array<int, 4> s21_arr_int{1, 4, 8, 9};
  s21::array<double, 4> s21_arr_double{1.4, 4.8, 8.9, 9.1};
  s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_arr_int[1], 4);
  EXPECT_EQ(s21_arr_double[1], 4.8);
  EXPECT_EQ(s21_arr_string[0], "Hello");
}

TEST(array_front, case1) {
  s21::array<int, 4> s21_arr_int{1, 4, 8, 9};
  s21::array<double, 4> s21_arr_double{1.4, 4.8, 8.9, 9.1};
  s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_arr_int.front(), 1);
  EXPECT_EQ(s21_arr_double.front(), 1.4);
  EXPECT_EQ(s21_arr_string.front(), "Hello");
}

TEST(array_back, case1) {
  s21::array<int, 4> s21_arr_int{1, 4, 8, 9};
  s21::array<double, 4> s21_arr_double{1.4, 4.8, 8.9, 9.1};
  s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_arr_int.back(), 9);
  EXPECT_EQ(s21_arr_double.back(), 9.1);
  EXPECT_EQ(s21_arr_string.back(), "!");
}

TEST(array_data, case1) {
  s21::array<int, 4> s21_arr_int{1, 4, 8, 9};
  s21::array<double, 4> s21_arr_double{1.4, 4.8, 8.9, 9.1};
  s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_arr_int.data(), &s21_arr_int[0]);
  EXPECT_EQ(s21_arr_double.data(), &s21_arr_double[0]);
  EXPECT_EQ(s21_arr_string.data(), &s21_arr_string[0]);
}

TEST(array_begin, case1) {
  s21::array<int, 4> s21_arr_int{1, 4, 8, 9};
  s21::array<double, 4> s21_arr_double{1.4, 4.8, 8.9, 9.1};
  s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_arr_int.begin(), &s21_arr_int[0]);
  EXPECT_EQ(s21_arr_double.begin(), &s21_arr_double[0]);
  EXPECT_EQ(s21_arr_string.begin(), &s21_arr_string[0]);
}

TEST(array_end, case1) {
  s21::array<int, 4> s21_arr_int{1, 4, 8, 9};
  s21::array<double, 4> s21_arr_double{1.4, 4.8, 8.9, 9.1};
  s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_arr_int.end(), &s21_arr_int[0] + 4);
  EXPECT_EQ(s21_arr_double.end(), &s21_arr_double[0] + 4);
  EXPECT_EQ(s21_arr_string.end(), &s21_arr_string[0] + 4);
}

TEST(array_empty, case1) {
  s21::array<int, 4> s21_arr_int{1, 4, 8, 9};
  s21::array<double, 4> s21_arr_double{1.4, 4.8, 8.9, 9.1};
  s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_arr_int.empty(), 0);
  EXPECT_EQ(s21_arr_double.empty(), 0);
  EXPECT_EQ(s21_arr_string.empty(), 0);
}

TEST(array_empty, case2) {
  s21::array<int, 0> s21_arr_int;
  s21::array<double, 0> s21_arr_double;
  s21::array<std::string, 0> s21_arr_string;

  EXPECT_EQ(s21_arr_int.empty(), 1);
  EXPECT_EQ(s21_arr_double.empty(), 1);
  EXPECT_EQ(s21_arr_string.empty(), 1);
}

TEST(array_size, case1) {
  s21::array<int, 4> s21_arr_int{1, 4, 8, 9};
  s21::array<double, 4> s21_arr_double{1.4, 4.8, 8.9, 9.1};
  s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_arr_int.size(), 4U);
  EXPECT_EQ(s21_arr_double.size(), 4U);
  EXPECT_EQ(s21_arr_string.size(), 4U);
}

TEST(array_size, case2) {
  s21::array<int, 0> s21_arr_int;
  s21::array<double, 0> s21_arr_double;
  s21::array<std::string, 0> s21_arr_string;

  EXPECT_EQ(s21_arr_int.size(), 0U);
  EXPECT_EQ(s21_arr_double.size(), 0U);
  EXPECT_EQ(s21_arr_string.size(), 0U);
}

TEST(array_max_size, case1) {
  s21::array<int, 4> s21_arr_int{1, 4, 8, 9};
  std::array<int, 4> std_arr_int{1, 4, 8, 9};

  s21::array<double, 4> s21_arr_double{1.4, 4.8, 8.9, 9.1};
  std::array<double, 4> std_arr_double{1.4, 4.8, 8.9, 9.1};

  s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};
  std::array<std::string, 4> std_arr_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_arr_int.max_size(), std_arr_int.max_size());
  EXPECT_EQ(s21_arr_double.max_size(), std_arr_double.max_size());
  EXPECT_EQ(s21_arr_string.max_size(), std_arr_string.max_size());
}

TEST(array_swap, case1) {
  s21::array<int, 4> s21_arr_ref_int{1, 4, 8, 9};
  s21::array<int, 4> s21_arr_res_int{21, 21, 21, 21};

  s21::array<double, 4> s21_arr_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::array<double, 4> s21_arr_res_double{21.0, 21.0, 21.0, 21.0};

  s21::array<std::string, 4> s21_arr_ref_string{"Hello", ",", "world", "!"};
  s21::array<std::string, 4> s21_arr_res_string{"21", "21", "21", "21"};

  s21_arr_ref_int.swap(s21_arr_res_int);
  s21_arr_ref_double.swap(s21_arr_res_double);
  s21_arr_ref_string.swap(s21_arr_res_string);

  EXPECT_EQ(s21_arr_ref_int[3], 21);
  EXPECT_EQ(s21_arr_res_int[0], 1);
  EXPECT_EQ(s21_arr_res_int[1], 4);
  EXPECT_EQ(s21_arr_res_int[2], 8);
  EXPECT_EQ(s21_arr_res_int[3], 9);

  EXPECT_EQ(s21_arr_ref_double[3], 21.0);
  EXPECT_EQ(s21_arr_res_double[0], 1.4);
  EXPECT_EQ(s21_arr_res_double[1], 4.8);
  EXPECT_EQ(s21_arr_res_double[2], 8.9);
  EXPECT_EQ(s21_arr_res_double[3], 9.1);

  EXPECT_EQ(s21_arr_ref_string[3], "21");
  EXPECT_EQ(s21_arr_res_string[0], "Hello");
  EXPECT_EQ(s21_arr_res_string[1], ",");
  EXPECT_EQ(s21_arr_res_string[2], "world");
  EXPECT_EQ(s21_arr_res_string[3], "!");
}

TEST(array_fill, case1) {
  s21::array<int, 4> s21_arr_int{1, 4, 8, 9};
  s21::array<double, 4> s21_arr_double{1.4, 4.8, 8.9, 9.1};
  s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

  s21_arr_int.fill(21);
  s21_arr_double.fill(21.0);
  s21_arr_string.fill("21");

  EXPECT_EQ(s21_arr_int[0], 21);
  EXPECT_EQ(s21_arr_int[1], 21);
  EXPECT_EQ(s21_arr_int[2], 21);
  EXPECT_EQ(s21_arr_int[3], 21);

  EXPECT_EQ(s21_arr_double[0], 21.0);
  EXPECT_EQ(s21_arr_double[1], 21.0);
  EXPECT_EQ(s21_arr_double[2], 21.0);
  EXPECT_EQ(s21_arr_double[3], 21.0);

  EXPECT_EQ(s21_arr_string[0], "21");
  EXPECT_EQ(s21_arr_string[1], "21");
  EXPECT_EQ(s21_arr_string[2], "21");
  EXPECT_EQ(s21_arr_string[3], "21");
}
