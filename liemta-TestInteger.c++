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
    const int a[] = {2, 3, 4};
    const int b[] = {2, 3, 4, 0};
          int x[10];
    const int* p = shift_left_digits(a, a + 3, 1, x);
    ASSERT_EQ(4, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, b));}

TEST(Integer, shift_left_digits_3) {
    const int a[] = {2, 3, 4};
    const int b[] = {2, 3, 4, 0, 0, 0};
          int x[10];
    const int* p = shift_left_digits(a, a + 3, 3, x);
    ASSERT_EQ(6, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, b));
}

// TEST(Integer, shift_left_digits_4) {
//     const int a[] = {0};
//     const int b[] = {0};
//           int x[10];
//     const int* p = shift_left_digits(a, a + 1, 3, x);
//     ASSERT_EQ(1, p - x);
//     ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, b));
// }

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
    const int a[] = {2, 3, 4, 5};
    const int b[] = {2, 3};
          int x[10];
    const int* p = shift_right_digits(a, a + 4, 2, x);
    ASSERT_EQ(2, p - x);
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
    const int a[] = {2, 3, 4};
    const int b[] = {1, 1, 7, 0};
    const int c[] = {1, 4, 0, 4};
          int x[10];
    const int* p = plus_digits(a, a + 3, b, b + 4, x);
    ASSERT_EQ(4, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, plus_digits_3) {
    const int a[] = {9, 9, 9};
    const int b[] = {1};
    const int c[] = {1, 0, 0, 0};
          int x[10];
    const int* p = plus_digits(a, a + 3, b, b + 1, x);
    ASSERT_EQ(4, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}


TEST(Integer, plus_digits_4) {
    const int a[] = {9, 9, 9};
    const int b[] = {2};
    const int c[] = {1, 0, 0, 1};
          int x[10];
    const int* p = plus_digits(a, a + 3, b, b + 1, x);
    ASSERT_EQ(4, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, plus_digits_5) {
    const int a[] = {9, 9, 9};
    const int b[] = {0};
    const int c[] = {9, 9, 9};
          int x[10];
    const int* p = plus_digits(a, a + 3, b, b + 1, x);
    ASSERT_EQ(3, p - x);
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
    const int a[] = {8, 0, 0};
    const int b[] = {1, 9, 9};
    const int c[] = {6, 0, 1};
          int x[10];
    const int* p = minus_digits(a, a + 3, b, b + 3, x);
    ASSERT_EQ(3, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, minus_digits_3) {
    const int a[] = {9, 9, 9};
    const int b[] = {1, 1, 1};
    const int c[] = {8, 8, 8};
          int x[10];
    const int* p = minus_digits(a, a + 3, b, b + 3, x);
    ASSERT_EQ(3, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, minus_digits_4) {
    const int a[] = {1, 0, 0, 0};
    const int b[] = {1};
    const int c[] = {9, 9, 9};
          int x[10];
    const int* p = minus_digits(a, a + 4, b, b + 1, x);
    ASSERT_EQ(3, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, minus_digits_5) {
    const int a[] = {9, 9, 9};
    const int b[] = {1, 1, 1};
    const int c[] = {8, 8, 8};
          int x[10];
    const int* p = minus_digits(a, a + 3, b, b + 3, x);
    ASSERT_EQ(3, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, minus_digits_6) {
    const int a[] = {1, 0, 0, 0};
    const int b[] = {9, 9, 9};
    const int c[] = {1};
          int x[10];
    const int* p = minus_digits(a, a + 4, b, b + 3, x);
    ASSERT_EQ(1, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, minus_digits_7) {
    const int a[] = {9, 9, 9};
    const int b[] = {9, 9, 0};
    const int c[] = {9};
          int x[10];
    const int* p = minus_digits(a, a + 3, b, b + 3, x);
    ASSERT_EQ(1, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, minus_digits_8) {
    const int a[] = {1, 0, 0, 0};
    const int b[] = {1};
    const int c[] = {9, 9, 9};
          int x[10];
    const int* p = minus_digits(a, a + 4, b, b + 1, x);
    ASSERT_EQ(3, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, minus_digits_9) {
    const int a[] = {9, 9, 9};
    const int b[] = {9, 9, 9};
    const int c[] = {0};
          int x[10];
    const int* p = minus_digits(a, a + 3, b, b + 3, x);
    ASSERT_EQ(1, p - x);
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
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));
}

TEST(Integer, multiplies_digits_2) {
    const int a[] = {1, 0};
    const int b[] = {5, 6, 7};
    const int c[] = {5, 6, 7, 0};
          int x[10];
    const int* p = multiplies_digits(a, a + 2, b, b + 3, x);
    ASSERT_EQ(4, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));
}

TEST(Integer, multiplies_digits_3) {
    const int a[] = {2, 3, 4};
    const int b[] = {1};
    const int c[] = {2, 3, 4};
          int x[10];
    const int* p = multiplies_digits(a, a + 3, b, b + 1, x);
    ASSERT_EQ(3, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));
}

TEST(Integer, multiplies_digits_4) {
    const int a[] = {9, 9, 9, 9};
    const int b[] = {9, 9, 9, 9};
    const int c[] = {9, 9, 9, 8, 0, 0, 0, 1};
          int x[10];
    const int* p = multiplies_digits(a, a + 4, b, b + 4, x);
    ASSERT_EQ(8, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));
}

TEST(Integer, multiplies_digits_5) {
    const int a[] = {2, 3, 4};
    const int b[] = {0};
    const int c[] = {0};
          int x[10];
    const int* p = multiplies_digits(a, a + 3, b, b + 1, x);
    ASSERT_EQ(1, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));
}

TEST(Integer, multiplies_digits_6) {
    const int a[] = {0};
    const int b[] = {0};
    const int c[] = {0};
          int x[10];
    const int* p = multiplies_digits(a, a + 1, b, b + 1, x);
    ASSERT_EQ(1, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));
}
TEST(Integer, multiplies_digits_7) {
    const int a[] = {9, 8, 7, 6};
    const int b[] = {5, 4};
    const int c[] = {5, 3, 3, 3, 0, 4};
          int x[10];
    const int* p = multiplies_digits(a, a + 4, b, b + 2, x);
    ASSERT_EQ(6, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));
}

TEST(Integer, multiplies_digits_8) {
    const int a[] = {2, 3};
    const int b[] = {4, 5, 6, 7};
    const int c[] = {1, 0, 5, 0, 4, 1};
          int x[10];
    const int* p = multiplies_digits(a, a + 2, b, b + 4, x);
    ASSERT_EQ(6, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));
}

TEST(Integer, multiplies_digits_9) {
    const int a[] = {9, 8, 7, 6};
    const int b[] = {0};
    const int c[] = {0};
          int x[10];
    const int* p = multiplies_digits(a, a + 4, b, b + 1, x);
    ASSERT_EQ(1, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));
}


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
    const int a[] = {2, 2, 2, 5};
    const int b[] = {8, 9};
    const int c[] = {2, 5};
          int x[10];
    const int* p = divides_digits(a, a + 4, b, b + 2, x);
    ASSERT_EQ(2, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, divides_digits_3) {
    const int a[] = {5, 6, 0, 8, 8};
    const int b[] = {4, 5, 6};
    const int c[] = {1, 2, 3};
          int x[10];
    const int* p = divides_digits(a, a + 5, b, b + 3, x);
    ASSERT_EQ(3, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, divides_digits_4) {
    const int a[] = {9, 9, 9, 9, 9};
    const int b[] = {9, 9};
    const int c[] = {1, 0, 1, 0};
          int x[10];
    const int* p = divides_digits(a, a + 5, b, b + 2, x);
    ASSERT_EQ(4, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, divides_digits_5) {
    const int a[] = {1, 3, 2};
    const int b[] = {5, 6, 7};
    const int c[] = {0};
          int x[10];
    const int* p = divides_digits(a, a + 3, b, b + 3, x);
    ASSERT_EQ(1, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, divides_digits_6) {
    const int a[] = {1, 3, 2, 6, 7, 8};
    const int b[] = {5, 0, 0};
    const int c[] = {2, 6, 5};
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
        ASSERT_STREQ("Integer::Integer()", e.what());}}

TEST(Integer, constructor_2) {
    try {
        const Integer<int> x("2");}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, constructor_3) {
    try {
        const Integer<int> x(2);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

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
        const Integer<int> x = 0;
        const Integer<int> y = abs(x);
        ASSERT_EQ(0, x);
        ASSERT_EQ(0, y);}
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
        const Integer<int> x = 2;
        const Integer<int> y = 2;
        ASSERT_EQ(      x, y);
        ASSERT_EQ(      x, 2);
        ASSERT_EQ(      2, x);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, equal_to_3) {
    try {
        const Integer<int> x = -98765;
        const Integer<int> y = -98765;
        ASSERT_EQ(      x, y);
        ASSERT_EQ(      x, -98765);
        ASSERT_EQ(  -98765, x);}
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
        const Integer<int> x = 0;
        const Integer<int> y = -x;
        ASSERT_EQ(0, y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, negation_3) {
    try {
        const Integer<int> x = -98765;
        const Integer<int> y = -x;
        ASSERT_EQ(98765, y);}
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
        const Integer<int> x ("9876578787836346345645");
        std::ostringstream out;
        out << x;
        ASSERT_EQ("9876578787836346345645", out.str());}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, output_3) {
    try {
        const Integer<int> x ("-9876578787836346345645");
        std::ostringstream out;
        out << x;
        ASSERT_EQ("-9876578787836346345645", out.str());}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, output_4) {
    try {
        const Integer<int> x = 98765;
        std::ostringstream out;
        out << x;
        ASSERT_EQ("98765", out.str());}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, output_5) {
    try {
        const Integer<int> x = -1;
        std::ostringstream out;
        out << x;
        ASSERT_EQ("-1", out.str());}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, output_6) {
    try {
        const Integer<int> x = 0;
        std::ostringstream out;
        out << x;
        ASSERT_EQ("0", out.str());}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

// ---
// pow
// ---

TEST(Integer, pow_1) {
    try {
        Integer<int>       x =  5;
        const int          e = 10;
        Integer<int>&      y = x.pow(e);
        ASSERT_EQ(9765625,          x);
        ASSERT_EQ(10,               e);
        ASSERT_EQ(9765625,          y);
        ASSERT_EQ(  &x, &y);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, pow_2) {
    try {
        const Integer<int> x =   5;
        const int          e =  11;
        const Integer<int> y = pow(x, e);
        ASSERT_EQ(5,            x);
        ASSERT_EQ(11,           e);
        ASSERT_EQ(48828125, y);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, pow_3) {
    try {
        const Integer<int> x = 5;
        const int          e = 0;
        const Integer<int> y = pow(x, e);
        ASSERT_EQ(5, x);
        ASSERT_EQ(0, e);
        ASSERT_EQ(1, y);}
    catch (std::invalid_argument& e)
    {
        ASSERT_TRUE(false);
    }   
}

TEST(Integer, pow_4) {
    try {
        Integer<int>       x = 2;
        const int          e = 8;
        ASSERT_EQ(8,  e);
        ASSERT_EQ(2,  x);
        Integer<int>&      y = x.pow(e);
        ASSERT_EQ(&x, &y);
        ASSERT_EQ(256, y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, pow_5) {
    try {
        const Integer<int> x = 2;
        const int          e = 15;
        const Integer<int> y = pow(x, e);
        ASSERT_EQ(2,  x);
        ASSERT_EQ(15, e);
        ASSERT_EQ(32768, y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, pow_6) {
    try {
        const Integer<int> x = 5;
        const int          e = 0;
        const Integer<int> y = pow(x, e);
        ASSERT_EQ(5, x);
        ASSERT_EQ(0, e);
        ASSERT_EQ(1, y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

// ---
// operator >>=
// ---

TEST(Integer, operator_left_shift) {
    try {
        Integer<int> x = 98765;
        Integer<int> y = 9876;
        ASSERT_EQ(98765,  x);
        x >>= 1;
        ASSERT_EQ(x, y);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}



// ----------
// operator <
// ----------

TEST(Integer, operator_less_than_1) {
    try {
        Integer<int> x = 5;
        Integer<int> y = 18;
        ASSERT_EQ(5,   x);
        ASSERT_EQ(18,  y);
        ASSERT_TRUE(x < y);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}


TEST(Integer, operator_less_than_2) {
    try {
        Integer<int> x = -5;
        Integer<int> y = -18;
        ASSERT_EQ(-5,   x);
        ASSERT_EQ(-18,  y);
        ASSERT_TRUE(y < x);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}


TEST(Integer, operator_less_than_3) {
    try {
        Integer<int> x = -5;
        Integer<int> y = 18;
        ASSERT_EQ(-5,   x);
        ASSERT_EQ(18,  y);
        ASSERT_TRUE(!(y < x));
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}


TEST(Integer, operator_less_than_4) {
    try {
        Integer<int> x = 5;
        Integer<int> y = -18;
        ASSERT_EQ(5,   x);
        ASSERT_EQ(-18,  y);
        ASSERT_TRUE(y < x);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}


TEST(Integer, operator_less_than_5) {
    try {
        Integer<int> x = 5;
        Integer<int> y = 5;
        ASSERT_EQ(5,   x);
        ASSERT_EQ(5,  y);
        ASSERT_TRUE(!(x < y));
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

// ---
// operator +=
// ---

TEST(Integer, operator_plus_equal_1) {
    try {
        Integer<int> x = 10;
        Integer<int> y = 4;
        ASSERT_EQ(10,  x);
        ASSERT_EQ(4,  y);
        x += y;
        ASSERT_EQ(14,  x);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, operator_plus_equal_2) {
    try {
        Integer<int> x = 25;
        Integer<int> y = 5;
        ASSERT_EQ(25,  x);
        ASSERT_EQ(5,    y);
        x += y;
        ASSERT_EQ(30, x);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, operator_plus_equal_3) {
    try {
        Integer<int> x = 5;
        Integer<int> y = 5;
        ASSERT_EQ(5,  x);
        ASSERT_EQ(5,  y);
        x += y;
        ASSERT_EQ(10, x);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, operator_plus_equal_4) {
    try {
        Integer<int> x = 1;
        Integer<int> y = 2;
        ASSERT_EQ(1,  x);
        ASSERT_EQ(2,    y);
        x += y;
        ASSERT_EQ(3, x);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

// ---
// operator -=
// ---

TEST(Integer, operator_minus_equal_1) {
    try {
        Integer<int> x = 10;
        Integer<int> y = 4;
        ASSERT_EQ(10,  x);
        ASSERT_EQ(4,  y);
        x -= y;
        ASSERT_EQ(6,  x);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, operator_minus_equal_2) {
    try {
        Integer<int> x = 25;
        Integer<int> y = 5;
        ASSERT_EQ(25,  x);
        ASSERT_EQ(5,    y);
        x -= y;
        ASSERT_EQ(20, x);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, operator_minus_equal_3) {
    try {
        Integer<int> x = 5;
        Integer<int> y = 5;
        ASSERT_EQ(5,  x);
        ASSERT_EQ(5,    y);
        x -= y;
        ASSERT_EQ(0, x);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

// ---
// operator *=
// ---

TEST(Integer, operator_multiply_equal_1) {
    try {
        Integer<int> x = 2;
        Integer<int> y = 3;
        ASSERT_EQ(2,  x);
        ASSERT_EQ(3,  y);
        x *= y;
        ASSERT_EQ(6,  x);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_multiply_equal_2) {
    try {
        Integer<int> x = -25;
        Integer<int> y = 5;
        ASSERT_EQ(-25,  x);
        ASSERT_EQ(5,    y);
        x *= y;
        ASSERT_EQ(-125, x);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_multiply_equal_3) {
    try {
        Integer<int> x = 1000;
        Integer<int> y = 0;
        ASSERT_EQ(1000,  x);
        ASSERT_EQ(0,    y);
        x *= y;
        ASSERT_EQ(0, x);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_multiply_equal_4)
{
    Integer<int> x("0"); 
    const Integer<int> y("-6521"); 
    x *= y;
    Integer<int> product("0");
    ASSERT_EQ(      x, product);
}

TEST(Integer, operator_multiply_equal_5) {
    Integer<int> x("-6521"); 
    const Integer<int> y("0"); 
    x *= y;
    Integer<int> product("0");
    ASSERT_EQ(      x, product);
}

// ---
// operator /=
// ---

TEST(Integer, operator_divides_equal_1) {
    try {
        Integer<int> x = 2;
        Integer<int> y = 3;
        ASSERT_EQ(2,  x);
        ASSERT_EQ(3,  y);
        x /= y;
        ASSERT_EQ(0,  x);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_divides_equal_2) {
    try {
        Integer<int> x = -25;
        Integer<int> y = 5;
        ASSERT_EQ(-25,  x);
        ASSERT_EQ(5,    y);
        x /= y;
        ASSERT_EQ(-5, x);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_divides_equal_3) {
    try {
        Integer<int> x = 25;
        Integer<int> y = -5;
        ASSERT_EQ(25,  x);
        ASSERT_EQ(-5,    y);
        x /= y;
        ASSERT_EQ(-5, x);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_divides_equal_4) {
    try {
        Integer<int> x = 0;
        Integer<int> y = 5;
        ASSERT_EQ(0,  x);
        ASSERT_EQ(5,    y);
        x /= y;
        ASSERT_EQ(0, x);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_divides_equal_5) {
    try {
        Integer<int> x = -25;
        Integer<int> y = -5;
        ASSERT_EQ(-25,  x);
        ASSERT_EQ(-5,    y);
        x /= y;
        ASSERT_EQ(5, x);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_divides_equal_6) {
    try {
        Integer<int> x = 11;
        Integer<int> y = 6;
        ASSERT_EQ(11,  x);
        ASSERT_EQ(6,    y);
        x /= y;
        ASSERT_EQ(1, x);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_divides_equal_7) {
    try {
        Integer<int> x = 11;
        Integer<int> y = 5;
        ASSERT_EQ(11,  x);
        ASSERT_EQ(5,    y);
        x /= y;
        ASSERT_EQ(2, x);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

// ---
// operator /=
// ---

TEST(Integer, operator_modulus_equal_1) {
    try {
        Integer<int> x = 2;
        Integer<int> y = 3;
        ASSERT_EQ(2,  x);
        ASSERT_EQ(3,  y);
        x %= y;
        ASSERT_EQ(2,  x);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_modulus_equal_2) {
    try {
        Integer<int> x = 25;
        Integer<int> y = 5;
        ASSERT_EQ(25,  x);
        ASSERT_EQ(5,    y);
        x %= y;
        ASSERT_EQ(0, x);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_modulus_equal_3) {
    try {
        Integer<int> x = 400;
        Integer<int> y = 250;
        ASSERT_EQ(400,  x);
        ASSERT_EQ(250,    y);
        x %= y;
        ASSERT_EQ(150, x);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_modulus_equal_4) {
    try {
        Integer<int> x = 3;
        Integer<int> y = 5;
        ASSERT_EQ(3,  x);
        ASSERT_EQ(5,    y);
        x %= y;
        ASSERT_EQ(3, x);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_modulus_equal_5) {
    try {
        Integer<int> x = -3;
        Integer<int> y = 5;
        ASSERT_EQ(-3,  x);
        ASSERT_EQ(5,    y);
        x %= y;
        ASSERT_EQ(-3, x);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

// ---
// operator ==
// ---

TEST(Integer, operator_equal_equal_1) {
    try {
        Integer<int> x = 2;
        Integer<int> y = 3;
        ASSERT_EQ(2,  x);
        ASSERT_EQ(3,  y);
        ASSERT_TRUE(!(x == y));
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_equal_equal_2) {
    try {
        Integer<int> x = 1000;
        Integer<int> y = 1000;
        ASSERT_EQ(1000,  x);
        ASSERT_EQ(1000,    y);
        ASSERT_TRUE(x == y);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_equal_equal_3) {
    try {
        Integer<int> x = -250;
        Integer<int> y = -250;
        ASSERT_EQ(-250,  x);
        ASSERT_EQ(-250,    y);
        ASSERT_TRUE(x == y);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_equal_equal_4) {
    try {
        Integer<int> x = 0;
        Integer<int> y = 0;
        ASSERT_EQ(0,  x);
        ASSERT_EQ(0,    y);
        ASSERT_TRUE(x == y);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

// ---
// operator ==
// ---

TEST(Integer, operator_not_equal_1) {
    try {
        Integer<int> x = 2;
        Integer<int> y = 3;
        ASSERT_EQ(2,  x);
        ASSERT_EQ(3,  y);
        ASSERT_TRUE(x != y);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_not_equal_2) {
    try {
        Integer<int> x = 1001;
        Integer<int> y = 1000;
        ASSERT_EQ(1001,  x);
        ASSERT_EQ(1000,    y);
        ASSERT_TRUE(x != y);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_not_equal_3) {
    try {
        Integer<int> x = -251;
        Integer<int> y = -250;
        ASSERT_EQ(-251,  x);
        ASSERT_EQ(-250,    y);
        ASSERT_TRUE(x != y);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_not_equal_4) {
    try {
        Integer<int> x = 0;
        Integer<int> y = 0;
        ASSERT_EQ(0,  x);
        ASSERT_EQ(0,    y);
        ASSERT_TRUE(!(x != y));
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

// ---
// operator <=
// ---

TEST(Integer, operator_less_than_equal_1) {
    try {
        Integer<int> x = 2;
        Integer<int> y = 3;
        ASSERT_EQ(2,  x);
        ASSERT_EQ(3,  y);
        ASSERT_TRUE(x <= y);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_less_than_equal_2) {
    try {
        Integer<int> x = 99;
        Integer<int> y = 1000;
        ASSERT_EQ(99,  x);
        ASSERT_EQ(1000,    y);
        ASSERT_TRUE(x <= y);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_less_than_equal_3) {
    try {
        Integer<int> x = 250;
        Integer<int> y = 250;
        ASSERT_EQ(250,  x);
        ASSERT_EQ(250,    y);
        ASSERT_TRUE(x <= y);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

// ---
// operator >
// ---

TEST(Integer, operator_greater_than_1) {
    try {
        Integer<int> x = 2;
        Integer<int> y = 3;
        ASSERT_EQ(2,  x);
        ASSERT_EQ(3,  y);
        ASSERT_TRUE(y > x);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_greater_than_2) {
    try {
        Integer<int> x = 99;
        Integer<int> y = 1000;
        ASSERT_EQ(99,  x);
        ASSERT_EQ(1000,    y);
        ASSERT_TRUE(y > x);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_greater_than_3) {
    try {
        Integer<int> x = 249;
        Integer<int> y = 250;
        ASSERT_EQ(249,  x);
        ASSERT_EQ(250,    y);
        ASSERT_TRUE(y > x);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

// ---
// operator >=
// ---

TEST(Integer, operator_greater_than_equal_1) {
    try {
        Integer<int> x = 2;
        Integer<int> y = 3;
        ASSERT_EQ(2,  x);
        ASSERT_EQ(3,  y);
        ASSERT_TRUE(y >= x);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_greater_than_equal_2) {
    try {
        Integer<int> x = 99;
        Integer<int> y = 1000;
        ASSERT_EQ(99,  x);
        ASSERT_EQ(1000,    y);
        ASSERT_TRUE(y >= x);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_greater_than_equal_3) {
    try {
        Integer<int> x = 250;
        Integer<int> y = 250;
        ASSERT_EQ(250,  x);
        ASSERT_EQ(250,    y);
        ASSERT_TRUE(y >= x);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

// ---
// operator +
// ---

TEST(Integer, operator_plus_1) {
    try {
        Integer<int> x = 2;
        Integer<int> y = 3;
        Integer<int> z = x + y;
        ASSERT_EQ(2,  x);
        ASSERT_EQ(3,  y);
        ASSERT_EQ(z, 5);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_plus_2) {
    try {
        Integer<int> x = 2;
        Integer<int> y = -3;
        Integer<int> z = x + y;
        ASSERT_EQ(2,  x);
        ASSERT_EQ(-3,  y);
        ASSERT_EQ(z, -1);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_plus_3) {
    try {
        Integer<int> x = -1;
        Integer<int> y = 2;
        Integer<int> z = x + y;
        ASSERT_EQ(-1,  x);
        ASSERT_EQ(2,  y);
        ASSERT_EQ(z, 1);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

// ---
// operator *
// ---

TEST(Integer, operator_multiply_1) {
    try {
        Integer<int> x = 2;
        Integer<int> y = 3;
        Integer<int> z = x * y;
        ASSERT_EQ(2,  x);
        ASSERT_EQ(3,  y);
        ASSERT_EQ(z, 6);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_multiply_2) {
    try {
        Integer<int> x = 2;
        Integer<int> y = -3;
        Integer<int> z = x * y;
        ASSERT_EQ(2,  x);
        ASSERT_EQ(-3,  y);
        ASSERT_EQ(z, -6);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_multiply_3) {
    try {
        Integer<int> x = -1;
        Integer<int> y = -2;
        Integer<int> z = x * y;
        ASSERT_EQ(-1,  x);
        ASSERT_EQ(-2,  y);
        ASSERT_EQ(z, 2);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

// ---
// operator /
// ---

TEST(Integer, operator_divides_1) {
    try {
        Integer<int> x = 2;
        Integer<int> y = 3;
        Integer<int> z = x / y;
        ASSERT_EQ(2,  x);
        ASSERT_EQ(3,  y);
        ASSERT_EQ(z, 0);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_divides_2) {
    try {
        Integer<int> x = 2;
        Integer<int> y = -3;
        Integer<int> z = x / y;
        ASSERT_EQ(2,  x);
        ASSERT_EQ(-3,  y);
        ASSERT_EQ(z, 0);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_divides_3) {
    try {
        Integer<int> x = -26;
        Integer<int> y = -13;
        Integer<int> z = x / y;
        ASSERT_EQ(-26,  x);
        ASSERT_EQ(-13,  y);
        ASSERT_EQ(z, 2);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

// ---
// operator %
// ---

TEST(Integer, operator_modulus_1) {
    try {
        Integer<int> x = 2;
        Integer<int> y = 3;
        Integer<int> z = x % y;
        ASSERT_EQ(2,  x);
        ASSERT_EQ(3,  y);
        ASSERT_EQ(z, 2);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_modulus_2) {
    try {
        // cout << "MOD TEST 2 mod -3 " << (2 % -3) << endl;
        // cout << "MOD TEST -2 mod 3 " << (-2 % 3) << endl;
        // cout << "MOD TEST -2 mod -3 " << (-2 % -3) << endl;
        Integer<int> x = -2;
        Integer<int> y = 3;
        Integer<int> z = x % y;
        ASSERT_EQ(-2,  x);
        ASSERT_EQ(3,  y);
        ASSERT_EQ(z, -2);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_modulus_3) {
    try {
        Integer<int> x = 0;
        Integer<int> y = 3;
        Integer<int> z = x % y;
        ASSERT_EQ(0,  x);
        ASSERT_EQ(3,  y);
        ASSERT_EQ(z, 0);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_modulus_4) {
    try {
        Integer<int> x = 100;
        Integer<int> y = 37;
        Integer<int> z = x % y;
        ASSERT_EQ(100,  x);
        ASSERT_EQ(37,  y);
        ASSERT_EQ(z, 26);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_modulus_5) {
    try {
        Integer<int> x = -100;
        Integer<int> y = 37;
        Integer<int> z = x % y;
        ASSERT_EQ(-100,  x);
        ASSERT_EQ(37,  y);
        ASSERT_EQ(z, -26);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

// ---
// operator >>
// ---

TEST(Integer, operator_right_shift_1) {
    try {
        Integer<int> x = 2;
        int y = 3;
        Integer<int> z = x >> y;
        ASSERT_EQ(2,  x);
        ASSERT_EQ(3,  y);
        ASSERT_EQ(z, 0);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_right_shift_2) {
    try {
        Integer<int> x = -2000000;
        int y = 6;
        Integer<int> z = x >> y;
        ASSERT_EQ(-2000000,  x);
        ASSERT_EQ(6,  y);
        ASSERT_EQ(z, -2);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_right_shift_3) {
    try {
        Integer<int> x = 0;
        int y = 1000000;
        Integer<int> z = x >> y;
        ASSERT_EQ(0,  x);
        ASSERT_EQ(1000000,  y);
        ASSERT_EQ(z, 0);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

// ---
// operator <<
// ---

TEST(Integer, operator_left_shift_1) {
    try {
        Integer<int> x = 2;
        int y = 3;
        Integer<int> z = x << y;
        ASSERT_EQ(2,  x);
        ASSERT_EQ(3,  y);
        ASSERT_EQ(z, 2000);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_left_shift_2) {
    try {
        Integer<int> x = -2;
        int y = 3;
        Integer<int> z = x << y;
        ASSERT_EQ(-2,  x);
        ASSERT_EQ(3,  y);
        ASSERT_EQ(z, -2000);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_left_shift_3) {
    try {
        Integer<int> x = 0;
        int y = 3;
        Integer<int> z = x << y;
        ASSERT_EQ(0,  x);
        ASSERT_EQ(3,  y);
        ASSERT_EQ(z, 0);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

// ---
// operator prefix ++
// ---

TEST(Integer, operator_prefix_increment_1) {
    try {
        Integer<int> x = 2;
        Integer<int> z = ++x;
        ASSERT_EQ(3,  x);
        ASSERT_EQ(z, 3);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, ooperator_prefix_increment_2) {
    try {
        Integer<int> x = 0;
        Integer<int> z = ++x;
        ASSERT_EQ(1,  x);
        ASSERT_EQ(z, 1);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_prefix_increment_3) {
    try {
        Integer<int> x = -10;
        Integer<int> z = ++x;
        ASSERT_EQ(-9,  x);
        ASSERT_EQ(z, -9);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

// ---
// operator postfix ++
// ---

TEST(Integer, operator_postfix_increment_1) {
    try {
        Integer<int> x = 2;
        Integer<int> z = x++;
        ASSERT_EQ(3,  x);
        ASSERT_EQ(z, 2);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_postfix_increment_2) {
    try {
        Integer<int> x = 0;
        Integer<int> z = x++;
        ASSERT_EQ(1,  x);
        ASSERT_EQ(z, 0);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_postfix_increment_3) {
    try {
        Integer<int> x = -10;
        Integer<int> z = x++;
        ASSERT_EQ(-9,  x);
        ASSERT_EQ(z, -10);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

// ---
// operator prefix --
// ---

TEST(Integer, operator_prefix_decrement_1) {
    try {
        Integer<int> x = 2;
        Integer<int> z = --x;
        ASSERT_EQ(1,  x);
        ASSERT_EQ(1,  z);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_prefix_decrement_2) {
    try {
        Integer<int> x = -2;
        Integer<int> z = --x;
        ASSERT_EQ(-3,  x);
        ASSERT_EQ(-3,  z);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_prefix_decrement_3) {
    try {
        Integer<int> x = 0;
        Integer<int> z = --x;
        ASSERT_EQ(-1,  x);
        ASSERT_EQ(-1,  z);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

// ---
// operator prefix --
// ---

TEST(Integer, operator_postfix_decrement_1) {
    try {
        Integer<int> x = -10;
        Integer<int> z = x--;
        ASSERT_EQ(-11,  x);
        ASSERT_EQ(z, -10);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_postfix_decrement_2) {
    try {
        Integer<int> x = -2;
        Integer<int> z = x--;
        ASSERT_EQ(-3,  x);
        ASSERT_EQ(-2,  z);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

TEST(Integer, operator_postfix_decrement_3) {
    try {
        Integer<int> x = 0;
        Integer<int> z = x--;
        ASSERT_EQ(-1,  x);
        ASSERT_EQ(0,  z);
    }
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);
    }
}

