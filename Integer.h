// --------------------------
// projects/integer/Integer.h
// Copyright (C) 2014
// Glenn P. Downing
// --------------------------

#ifndef Integer_h
#define Integer_h

// --------
// includes
// --------

#include <cassert>   // assert
#include <iostream>  // ostream
#include <stdexcept> // invalid_argument
#include <string>    // string
#include <vector>    // vector
#include <deque>     // deque

// -----------------
// shift_left_digits
// -----------------

/**
 * @param b an iterator to the beginning of an input  sequence (inclusive)
 * @param e an iterator to the end       of an input  sequence (exclusive)
 * @param x an iterator to the beginning of an output sequence (inclusive)
 * @return  an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the shift left of the input sequence into the output sequence
 * ([b, e) << n) => x
 */
template <typename II, typename OI>
OI shift_left_digits (II b, II e, int n, OI x) {
    while(b != e){*x++ = *b++;}
    while(n-- > 0){*x++ = 0;}
    return x;}

// ------------------
// shift_right_digits
// ------------------

/**
 * @param b an iterator to the beginning of an input  sequence (inclusive)
 * @param e an iterator to the end       of an input  sequence (exclusive)
 * @param x an iterator to the beginning of an output sequence (inclusive)
 * @return  an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the shift right of the input sequence into the output sequence
 * ([b, e) >> n) => x
 */
template <typename II, typename OI>
OI shift_right_digits (II b, II e, int n, OI x) {
    while(n-- > 0){ --e; }
    while(b != e){ *x++ = *b++; }
    return x;}

// -----------
// plus_digits
// -----------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the sum of the two input sequences into the output sequence
 * ([b1, e1) + [b2, e2)) => x
 */
template <typename II1, typename II2, typename OI>
OI plus_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
    bool overflow = false;
    std::deque<int> num1;
    std::deque<int> num2;
    std::deque<int> result;
    while(b1 != e1){num1.push_front(*b1++);}
    while(b2 != e2){num2.push_front(*b2++);}
    int bottom = std::min(num2.size(), num1.size());
    if((int)num1.size() == bottom){
        for(int i = num1.size()-1; i >= 0; i--){
            int to_insert = (num1[i] + num2[i]);
            if(overflow){
                overflow = false;
                to_insert += 1;
            }
            if(to_insert > 9){
                overflow = true;
                if(to_insert == 10){to_insert = 0;}
                else{to_insert = ceil(to_insert % 10);}
                result.push_front(to_insert);
            }else{ result.push_front(to_insert); }
        }
        if(num1.size() != num2.size()){

        }
    }else{
        for(int i = num2.size()-1; i >= 0; i--){
            int to_insert = (num1[i] + num2[i]);
            if(overflow){
                overflow = false;
                to_insert += 1;
            }
            if(to_insert > 9){
                overflow = true;
                if(to_insert == 10){to_insert = 0;}
                else{to_insert = ceil(to_insert % 10);}
                result.push_front(to_insert);
            }else{ result.push_front(to_insert); }
        }
        if(num1.size() != num2.size()){

        }
    }

    return x;}

// ------------
// minus_digits
// ------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the difference of the two input sequences into the output sequence
 * ([b1, e1) - [b2, e2)) => x
 */
template <typename II1, typename II2, typename OI>
OI minus_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
    // <your code>
    return x;}

// -----------------
// multiplies_digits
// -----------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the product of the two input sequences into the output sequence
 * ([b1, e1) * [b2, e2)) => x
 */
template <typename II1, typename II2, typename OI>
OI multiplies_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
    // <your code>
    return x;}

// --------------
// divides_digits
// --------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the division of the two input sequences into the output sequence
 * ([b1, e1) / [b2, e2)) => x
 */
template <typename II1, typename II2, typename OI>
OI divides_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
    // <your code>
    return x;}

// -------
// Integer
// -------

template < typename T, typename C = std::vector<T> >
class Integer {
    // -----------
    // operator ==
    // -----------

    /**
     * <your documentation>
     * uses the default == to confirm equality
     */
    friend bool operator == (const Integer& lhs, const Integer& rhs) {
        return lhs._x == rhs._x;}

    // -----------
    // operator !=
    // -----------

    /**
     * <your documentation>
     */
    friend bool operator != (const Integer& lhs, const Integer& rhs) {
        return !(lhs == rhs);}

    // ----------
    // operator <
    // ----------

    /**
     * <your documentation>
     */
    friend bool operator < (const Integer& lhs, const Integer& rhs) {
        // <your code>
        return false;}

    // -----------
    // operator <=
    // -----------

    /**
     * <your documentation>
     */
    friend bool operator <= (const Integer& lhs, const Integer& rhs) {
        return !(rhs < lhs);}

    // ----------
    // operator >
    // ----------

    /**
     * <your documentation>
     */
    friend bool operator > (const Integer& lhs, const Integer& rhs) {
        return (rhs < lhs);}

    // -----------
    // operator >=
    // -----------

    /**
     * <your documentation>
     */
    friend bool operator >= (const Integer& lhs, const Integer& rhs) {
        return !(lhs < rhs);}

    // ----------
    // operator +
    // ----------

    /**
     * <your documentation>
     */
    friend Integer operator + (Integer lhs, const Integer& rhs) {
        return lhs += rhs;}

    // ----------
    // operator -
    // ----------

    /**
     * <your documentation>
     */
    friend Integer operator - (Integer lhs, const Integer& rhs) {
        return lhs -= rhs;}

    // ----------
    // operator *
    // ----------

    /**
     * <your documentation>
     */
    friend Integer operator * (Integer lhs, const Integer& rhs) {
        return lhs *= rhs;}

    // ----------
    // operator /
    // ----------

    /**
     * <your documentation>
     * @throws invalid_argument if (rhs == 0)
     */
    friend Integer operator / (Integer lhs, const Integer& rhs) {
        return lhs /= rhs;}

    // ----------
    // operator %
    // ----------

    /**
     * <your documentation>
     * @throws invalid_argument if (rhs <= 0)
     */
    friend Integer operator % (Integer lhs, const Integer& rhs) {
        return lhs %= rhs;}

    // -----------
    // operator <<
    // -----------

    /**
     * <your documentation>
     * @throws invalid_argument if (rhs < 0)
     */
    friend Integer operator << (Integer lhs, int rhs) {
        return lhs <<= rhs;}

    // -----------
    // operator >>
    // -----------

    /**
     * <your documentation>
     * @throws invalid_argument if (rhs < 0)
     */
    friend Integer operator >> (Integer lhs, int rhs) {
        return lhs >>= rhs;}

    // -----------
    // operator <<
    // -----------

    /**
     * <your documentation>
     */
    friend std::ostream& operator << (std::ostream& lhs, const Integer& rhs) {
        // <your code>
        return lhs << "0";}

    // ---
    // abs
    // ---

    /**
     * absolute value
     * <your documentation>
     */
    friend Integer abs (Integer x) {
        return x.abs();}

    // ---
    // pow
    // ---

    /**
     * power
     * <your documentation>
     * @throws invalid_argument if ((x == 0) && (e == 0)) || (e < 0)
     */
    friend Integer pow (Integer x, int e) {
        return x.pow(e);}

    private:
        // ----
        // data
        // ----

        C _x; // the backing container
        // <your data>
        bool positive;

    private:
        // -----
        // valid
        // -----

        bool valid () const { // class invariant
            // <your code>
            return true;}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * <your documentation>
         */
        Integer (int value) {
            // <your code>
            assert(valid());}

        /**
         * <your documentation>
         * @throws invalid_argument if value is not a valid representation of an Integer
         */
        explicit Integer (const std::string& value) {
            // <your code>
            if (!valid())
                throw std::invalid_argument("Integer::Integer()");}

        // Default copy, destructor, and copy assignment.
        // Integer (const Integer&);
        // ~Integer ();
        // Integer& operator = (const Integer&);

        // ----------
        // operator -
        // ----------

        /**
         * <your documentation>
         */
        Integer operator - () const {
            // <your code>
            return Integer(0);}

        // -----------
        // operator ++
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator ++ () {
            *this += 1;
            return *this;}

        /**
         * <your documentation>
         */
        Integer operator ++ (int) {
            Integer x = *this;
            ++(*this);
            return x;}

        // -----------
        // operator --
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator -- () {
            *this -= 1;
            return *this;}

        /**
         * <your documentation>
         */
        Integer operator -- (int) {
            Integer x = *this;
            --(*this);
            return x;}

        // -----------
        // operator +=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator += (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator -=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator -= (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator *=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator *= (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator /=
        // -----------

        /**
         * <your documentation>
         * @throws invalid_argument if (rhs == 0)
         */
        Integer& operator /= (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator %=
        // -----------

        /**
         * <your documentation>
         * @throws invalid_argument if (rhs <= 0)
         */
        Integer& operator %= (const Integer& rhs) {
            // <your code>
            return *this;}

        // ------------
        // operator <<=
        // ------------

        /**
         * <your documentation>
         */
        Integer& operator <<= (int n) {
            // <your code>
            return *this;}

        // ------------
        // operator >>=
        // ------------

        /**
         * <your documentation>
         */
        Integer& operator >>= (int n) {
            // <your code>
            return *this;}

        // ---
        // abs
        // ---

        /**
         * absolute value
         * <your documentation>
         */
        Integer& abs () {
            // <your code>
            return *this;}

        // ---
        // pow
        // ---

        /**
         * power
         * <your documentation>
         * @throws invalid_argument if ((this == 0) && (e == 0)) or (e < 0)
         */
        Integer& pow (int e) {
            if(((this == 0) && (e == 0)) || (e < 0))
                throw std::invalid_argument("Invalid Argument to the call.");

            return *this;}};

#endif // Integer_h
