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
#include <math.h>

using namespace std;

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
    int count = 0;
    vector<int> num1;
    vector<int> num2;
    deque<int> result;
    while(b1 != e1){num1.push_back(*b1++);}
    while(b2 != e2){num2.push_back(*b2++);}
    int top = std::max(num2.size(), num1.size());
    if((int)num1.size() == top){
        auto min = num2.rbegin();
        for(int i = num1.size()-1; i >= 0; i--){
            if(count++ >= (int)num2.size()){
                int add = num1[i];
                if(overflow){
                    overflow = false;
                    add += 1;}
                if(add > 9){
                    overflow = true;
                    result.push_front(add % 10);
                }else{result.push_front(add);  }
            }else{
                int to_insert = (num1[i] + *min++);
                if(overflow){
                    overflow = false;
                    to_insert += 1;}
                if(to_insert > 9){
                    overflow = true;
                    to_insert = to_insert % 10;
                    result.push_front(to_insert);
                }else{ result.push_front(to_insert); }
            }
        }
    }else{
        auto min = num1.rbegin();
        for(int i = num2.size()-1; i >= 0; i--){
            if(count++ >= (int)num1.size()){
                int add = num2[i];
                if(overflow){
                    overflow = false;
                    add += 1;}
                if(add > 9){
                    overflow = true;
                    result.push_front(add % 10);
                }else{result.push_front(add);  }
            }else{
                int to_insert = (num2[i] + *min++);
                if(overflow){
                    overflow = false;
                    to_insert += 1;}
                if(to_insert > 9){
                    overflow = true;
                    to_insert = to_insert % 10;
                    result.push_front(to_insert);
                }else{ result.push_front(to_insert); }
            }
        }
    }
    if(overflow){result.push_front(1);}
    for(int i = 0; i < (int)result.size(); i++){*x++ = result[i];}
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
    bool carry = false;
    int count = 0;
    vector<int> num1;
    vector<int> num2;
    deque<int> result;
    while(b1 != e1){num1.push_back(*b1++);}
    while(b2 != e2){num2.push_back(*b2++);}
    assert(num1.size() >= num2.size());
    auto min = num2.rbegin();
    for(int i = num1.size()-1; i >= 0; i--){
        if(count++ >= (int)num2.size()){
            if(carry){ 
                int val = 1;
                if(num1[i] >= val){
                    result.push_front(num1[i] - val);
                    carry = false;
                }else{
                    result.push_front(10 - (val - num1[i]));
                    carry = true;
                }
            }else{ 
                result.push_front(num1[i]); 
            }
        }else{
            int val = *min++;
            if(carry){
                val += 1;
                if(num1[i] >= val){
                    result.push_front(num1[i] - val);
                    carry = false;
                }else{
                    result.push_front(10 - (val - num1[i]));
                    carry = true;
                }
            }else{
                if(num1[i] >= val){
                    result.push_front(num1[i] - val);
                    carry = false;
                }else{
                    result.push_front(10 - (val - num1[i]));
                    carry = true;
                }
            }
        }
    }

    auto begin = result.begin();
    while(*begin == 0){*begin++;}
    if(begin == result.end()){
        *x++ = 0; 
        return x;
    }

    if(result[0] == 0){ for(int i = 1; i < (int)result.size(); i++){*x++ = result[i];} }
    else{ for(int i = 0; i < (int)result.size(); i++){*x++ = result[i];} }
    // for(auto c:result){cout<<c;}
    // cout << endl;
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
    vector<int> num1;
    vector<int> num2;
    vector<int> result;
    size_t len1 = distance(b1, e1);
    size_t len2 = distance(b2, e2);
    result.reserve(b1_len + b2_len);
    while(b1 != e1){num1.push_back(*b1++);}
    while(b2 != e2){num2.push_back(*b2++);}

    int k = 0; 
    int count = 0;
    int temp;
    auto it1 = num1.rbegin();
    auto it2 = num2.rbegin();

    for(int i = 0; i < result.size(); i++){result[i] = 0;}

    for(int i = 0; i < num1.size(); i++){
        count = 0; k = i;
        for(int j = 0; j <  num2.size(); j++){
            temp = (*it1++) * (*it2++);
            temp += count + result[k];
            count = temp / 10;
            result[k] = temp % 10;
            k++
        }
        if(c!=0){ result[k] = c; k++; }
    }

    auto it_Final = result.rbegin();
    while(it_Final != result.rend();){ *x++ = *it_Final++; }

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
        auto lit = lhs._x.begin();
        auto rit = rhs._x.begin();
        while(lit != lhs._x.end() && rit != rhs._x.end()){
            if(*lit++ != *rit++)
                return false;
        }
        if(lit != lhs._x.end() || rit != rhs._x.end())
            return false;
        return true;}
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
        auto start = rhs._x.begin();
        while(start != rhs._x.end()){
            lhs << *start++;
        }
        return lhs;}

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
        int size;

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
            value < 0 ? positive = false : positive = true;
            int val = value;
            deque<int> myne;
            while(val != 0){
                myne.push_front(val % 10);
                val /= 10;
            }
            _x.resize(myne.size());
            copy(myne.begin(), myne.end(), _x.begin());
        }

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
            if(this->positive){
                this->positive = false;
            }else{ this->positive = true;}
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
