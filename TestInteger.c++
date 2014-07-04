// --------------------------------
// projects/integer/TestInteger.c++
// Copyright (C) 2014
// Glenn P. Downing
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

/*
Google Test Libraries:
    % ls -al /usr/include/gtest/
    ...
    gtest.h
    ...

    % locate libgtest.a
    /usr/lib/libgtest.a

    % locate libpthread.a
    /usr/lib/x86_64-linux-gnu/libpthread.a
    /usr/lib32/libpthread.a

    % locate libgtest_main.a
    /usr/lib/libgtest_main.a

To compile the test:
    % g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Integer.c++ TestInteger.c++ -o TestInteger -lgtest -lgtest_main -lpthread

To run the test:
    % valgrind TestInteger

To obtain coverage of the test:
    % gcov-4.7 -b Integer.c++ TestInteger.c++
*/

// --------
// includes
// --------

#include <algorithm> // equal
#include <cstring>   // strcmp
#include <sstream>   // ostringstream
#include <stdexcept> // invalid_argument
#include <string>    // ==

#include "gtest/gtest.h"

#include "Integer.h"

// -----------
// TestInteger
// -----------

// -----------------
// shift_left_digits
// -----------------

TEST(Integer, shift_left_digits_1) {
    const int a[] = {2, 3, 4};
    const int b[] = {2, 3, 4, 0, 0};
          int x[10];
    const int* p = shift_left_digits(a, a + 3, 2, x);
    ASSERT_EQ(5, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, b));}

TEST(Integer, shift_left_digits_2) {
    const int a[] = {2};
    const int b[] = {2, 0, 0};
          int x[10];
    const int* p = shift_left_digits(a, a + 1, 2, x);
    ASSERT_EQ(3, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, b));}


TEST(Integer, shift_left_digits_3) {
    const int a[] = {2, 3, 4, 5, 6, 7};
    const int b[] = {2, 3, 4, 5, 6, 7, 0, 0, 0};
          int x[10];
    const int* p = shift_left_digits(a, a + 6, 3, x);
    ASSERT_EQ(9, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, b));}

// ------------------
// shift_right_digits
// ------------------

TEST(Integer, shift_right_digits_1) {
    const int a[] = {2, 3, 4};
    const int b[] = {2};
          int x[10];
    const int* p = shift_right_digits(a, a + 3, 2, x);
    ASSERT_EQ(1, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, b));}

TEST(Integer, shift_right_digits_2) {
    const int a[] = {2, 3, 4};
    const int b[] = {2, 3};
          int x[10];
    const int* p = shift_right_digits(a, a + 3, 1, x);
    ASSERT_EQ(2, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, b));}


TEST(Integer, shift_right_digits_3) {
    const int a[] = {2, 3, 4, 5, 6, 7, 8, 9};
    const int b[] = {2, 3, 4};
          int x[10];
    const int* p = shift_right_digits(a, a + 8, 5, x);
    ASSERT_EQ(3, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, b));}


// -----------
// plus_digits
// -----------

TEST(Integer, plus_digits_1) {
    const int a[] = {2, 3, 4};
    const int b[] = {5, 6, 7};
    const int c[] = {8, 0, 1};
          int x[10];
    const int* p = plus_digits(a, a + 3, b, b + 3, x);
    ASSERT_EQ(3, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, plus_digits_2) {
    const int a[] = {1};
    const int b[] = {1};
    const int c[] = {2};
          int x[10];
    const int* p = plus_digits(a, a + 1, b, b + 1, x);
    ASSERT_EQ(1, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, plus_digits_3) {
    const int a[] = {9, 9, 8};
    const int b[] = {3};
    const int c[] = {1, 0, 0, 1};
          int x[10];
    const int* p = plus_digits(a, a + 3, b, b + 1, x);
    ASSERT_EQ(4, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, plus_digits_4) {
    const int a[] = {0};
    const int b[] = {1, 1};
    const int c[] = {1, 1};
          int x[10];
    const int* p = plus_digits(a, a+1, b, b + 2, x);
    ASSERT_EQ(2, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}
 
TEST(Integer, plus_digits_5) {
    const int a[] = {9, 9};
    const int b[] = {9, 9, 9};
    const int c[] = {1, 0, 9 ,8};
          int x[10];
    const int* p = plus_digits(a, a+2, b, b + 3, x);
    ASSERT_EQ(4, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}


// ------------
// minus_digits
// ------------

TEST(Integer, minus_digits_1) {
    const int a[] = {8, 0, 1};
    const int b[] = {5, 6, 7};
    const int c[] = {2, 3, 4};
          int x[10];
    const int* p = minus_digits(a, a + 3, b, b + 3, x);
    ASSERT_EQ(3, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, minus_digits_2) {
    const int a[] = {2};
    const int b[] = {1};
    const int c[] = {1};
          int x[10];
    const int* p = minus_digits(a, a + 1, b, b + 1, x);
    ASSERT_EQ(1, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, minus_digits_3) {
    const int a[] = {1, 0, 0, 0};
    const int b[] = {1};
    const int c[] = {9, 9, 9};
          int x[10];
    const int* p = minus_digits(a, a + 4, b, b + 1, x);
    ASSERT_EQ(3, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}


// -----------------
// multiplies_digits
// -----------------

TEST(Integer, multiplies_digits_1) {
    const int a[] = {2, 3, 4};
    const int b[] = {5, 6, 7};
    const int c[] = {1, 3, 2, 6, 7, 8};
          int x[10];
    const int* p = multiplies_digits(a, a + 3, b, b + 3, x);
    ASSERT_EQ(6, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, multiplies_digits_2) {
    const int a[] = {1};
    const int b[] = {2};
    const int c[] = {2};
          int x[10];
    const int* p = multiplies_digits(a, a + 1, b, b + 1, x);
    ASSERT_EQ(1, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, multiplies_digits_3) {
    const int a[] = {9};
    const int b[] = {9};
    const int c[] = {8, 1};
          int x[10];
    const int* p = multiplies_digits(a, a + 1, b, b + 1, x);
    ASSERT_EQ(2, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}    

// --------------
// divides_digits
// --------------

TEST(Integer, divides_digits_1) {
    const int a[] = {1, 3, 2, 6, 7, 8};
    const int b[] = {5, 6, 7};
    const int c[] = {2, 3, 4};
          int x[10];
    const int* p = divides_digits(a, a + 6, b, b + 3, x);
    ASSERT_EQ(3, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, divides_digits_2) {
    const int a[] = {1, 3, 2, 6, 7, 8};
    const int b[] = {5, 6, 7};
    const int c[] = {2, 3, 4};
          int x[10];
    const int* p = divides_digits(a, a + 6, b, b + 3, x);
    ASSERT_EQ(3, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, divides_digits_3) {
    const int a[] = {1, 3, 2, 6, 7, 8};
    const int b[] = {5, 6, 7};
    const int c[] = {2, 3, 4};
          int x[10];
    const int* p = divides_digits(a, a + 6, b, b + 3, x);
    ASSERT_EQ(3, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

// -----------
// constructor
// -----------

TEST(Integer, constructor_1) {
    try {
        const Integer<int> x("abc");
        ASSERT_TRUE(false);}
    catch (std::invalid_argument& e) {
        ASSERT_STREQ("Integer()", e.what());}}

TEST(Integer, constructor_2) {
    try {
        const Integer<int> x("2");}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, constructor_3) {
    try {
        const Integer<int> x(2);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

// ---
// abs
// ---

TEST(Integer, abs_1) {
    try {
        Integer<int>  x = -98765;
        Integer<int>& y = x.abs();
        ASSERT_EQ(98765, x);
        ASSERT_EQ(&x,    &y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, abs_2) {
    try {
        const Integer<int> x = -98765;
        const Integer<int> y = abs(x);
        ASSERT_EQ(-98765, x);
        ASSERT_EQ( 98765, y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, abs_3) {
    try {
        Integer<int>  x = 98765;
        Integer<int>& y = x.abs();
        ASSERT_EQ(98765, x);
        ASSERT_EQ(&x,    &y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, abs_4) {
    try {
        const Integer<int> x = 98765;
        const Integer<int> y = abs(x);
        ASSERT_EQ(-98765, x);
        ASSERT_EQ( 98765, y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

// --------
// equal_to
// --------

TEST(Integer, equal_to_1) {
    try {
        const Integer<int> x = 98765;
        const Integer<int> y = 98765;
        ASSERT_EQ(      x, y);
        ASSERT_EQ(      x, 98765);
        ASSERT_EQ(  98765, x);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, equal_to_2) {
    try {
        const Integer<int> x = 55;
        const Integer<int> y = 55;
        ASSERT_EQ(   x, y);
        ASSERT_EQ(   x, 55);
        ASSERT_EQ(  55, x);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

// --------
// negation
// --------

TEST(Integer, negation_1) {
    try {
        const Integer<int> x = 98765;
        const Integer<int> y = -x;
        ASSERT_EQ(-98765, y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, negation_2) {
    try {
        const Integer<int> x = -2;
        const Integer<int> y = -x;
        ASSERT_EQ(2, y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, negation_3) {
    try {
        const Integer<int> x = 55;
        const Integer<int> y = -x;
        ASSERT_EQ(-55, y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

// ------
// output
// ------

TEST(Integer, output_1) {
    try {
        const Integer<int> x = 98765;
        std::ostringstream out;
        out << x;
        ASSERT_EQ("98765", out.str());}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, output_2) {
    try {
        const Integer<int> x = -1;
        std::ostringstream out;
        out << x;
        ASSERT_EQ("-1", out.str());}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, output_3) {
    try {
        const Integer<int> x = 55;
        std::ostringstream out;
        out << x;
        ASSERT_EQ("55", out.str());}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

// ---
// pow
// ---

TEST(Integer, pow_1) {
    try {
        Integer<int>       x = 98765;
        const int          e =  9867;
        Integer<int>&      y = x.pow(e);
        ASSERT_EQ(9867,  e);
        ASSERT_EQ(   0,  x);
        ASSERT_EQ(  &x, &y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, pow_2) {
    try {
        const Integer<int> x = 98765;
        const int          e =  9867;
        const Integer<int> y = pow(x, e);
        ASSERT_EQ(98765, x);
        ASSERT_EQ( 9867, e);
        ASSERT_EQ(    0, y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, pow_3) {
    try {
        Integer<int>       x = 98765;
        const int          e = 1;
        Integer<int>&      y = x.pow(e);
        ASSERT_EQ(1,  e);
        ASSERT_EQ(   0,  x);
        ASSERT_EQ(  &x, &y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, pow_4) {
    try {
        const Integer<int> x = 98765;
        const int          e =  0;
        const Integer<int> y = pow(x, e);
        ASSERT_EQ(98765, x);
        ASSERT_EQ( 0, e);
        ASSERT_EQ(    0, y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}
