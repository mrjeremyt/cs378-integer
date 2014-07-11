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
#include <algorithm> //for reasons
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
    int d = distance(b, e);
    if(d <= n){*x++ = 0; return x;}
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
    vector<int> num1; vector<int> num2; vector<int> result;
    while(b1 != e1){num1.push_back(*b1++);}
    while(b2 != e2){num2.push_back(*b2++);}
    result.resize(num1.size() + num2.size());

    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());

    for(int i = 0; i < (int)num1.size(); i++){
        int crry = 0; int k = i;
        for(int j = 0; j < (int)num2.size(); j++){
            int temp = (num1[i])*(num2[j]) + crry + result[k];
            crry = temp/10; result[k] = temp%10; k++;        }
        if(crry != 0){ result[k] = crry; }
    }

    auto it_Final = result.rbegin();
    while(*it_Final == 0 && it_Final != result.rend()){it_Final++;}
    if(it_Final == result.rend()){ *x++ = 0; return x;    }
    while(it_Final != result.rend()){ *x++ = *it_Final++; }
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
template <typename II1, typename II2, typename FI>
FI divides_digits (II1 b1, II1 e1, II2 b2, II2 e2, FI x) 
{
    vector<int> num1; vector<int> num2; vector<int> q;
    while(b1 != e1){num1.push_back(*b1++);}
    while(b2 != e2){num2.push_back(*b2++);}

    q.resize(num1.size() + num2.size());
    if (num1.size() < num2.size()){
        vector<int> temp = num1;
        num2 = temp;
        num1 = num2;}
    vector<int> dividend; dividend.push_back(1);
    int count = 0;
    while (num1.size() >= num2.size()){

        bool minus = true;
        if(num1.size() == num2.size()){
            auto ita = num1.begin();
            auto itb = num2.begin();
            for (; ita != num1.end(); ita++){
                if (*ita < *itb++){
                    minus = false;
                    break;
                }
            }
        }
        if (minus){
            auto v = minus_digits(num1.begin(), num1.end(), dividend.begin(), dividend.end(), q.begin());
            q.resize(distance(q.begin(), v));
            num1= q;
            count++;
        }
    }

    vector<int>result;
    while (count > 0)
    {
        result.push_back(count % 10); 
        count /= 10;
    }

    auto it = result.rbegin();
    while (*it == 0) it++;
    if (it == result.rend() + 1){
        *x++ = 0;
        return x;
    }
    for (auto k: result) *x++ = k;
    return x;
}

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
        if (lhs.positive != rhs.positive)
            return false;
        auto lhs_it = lhs._x.begin();
        auto rhs_it = rhs._x.begin();
        while (lhs_it != lhs._x.end() && rhs_it != rhs._x.end())
        {
            if (*lhs_it++ != *rhs_it++) return false;
        }
        if (lhs_it != lhs._x.end() || rhs_it != rhs._x.end()) return false;

        return true;
    }


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
        if(lhs._x.size() < rhs._x.size()){
            if(lhs.positive && !rhs.positive) return false;
            else return true;
        }
        else if(lhs._x.size() > rhs._x.size()){
            if(!lhs.positive) return true;
            else return false;
        }
        else if(!lhs.positive && rhs.positive) return true;
        else if(lhs.positive && !rhs.positive) return false;
        else{
            auto it_l_s = lhs._x.begin();
            auto it_l_e = lhs._x.end();
            auto it_r_s = rhs._x.begin();

            while (it_l_s != it_l_e){
                if (*it_l_s++ < *it_r_s++) return true;
            }
        }
        return false;
    }

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
        if (rhs.positive == false){ 
            if (!(rhs._x.size() == 1 && rhs._x.back() == 0)) lhs << "-";
        }

        auto it_s = rhs._x.begin();
        auto it_e = rhs._x.end();

        while (it_s != it_e) lhs << *it_s++;
        return lhs;
    }

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
            // I don't know what to do h
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

            unsigned tmp;
            if (value < 0) tmp = ~value + 1;
            else  tmp = value;

            deque<T> con;

            if (tmp == 0)
                con.push_front(0);
            else {
                while (tmp > 0)
                {
                    con.push_front(tmp % 10);
                    tmp /= 10;}
                }
            _x.resize(con.size());
            copy(con.begin(), con.end(), _x.begin());
        }

        /**
         * <your documentation>
         * @throws invalid_argument if value is not a valid representation of an Integer
         */
        explicit Integer (const std::string& value) {
            char *c;
            strtol(value.c_str(), &c, 10);

            if (*c != 0) throw std::invalid_argument("Integer()");

            positive = true;
            auto val_f = value.begin();
            auto val_b = value.end();

            if (*val_f == 45) //Negative
            {
                positive = false;
                val_f++;
            }
            while (val_f != val_b)
            {
                _x.push_back(*val_f++ - 48);
            }
        }

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
            Integer tmp = *this;

            if (!tmp.positive) tmp.positive = true;
            else tmp.positive = false;
            return tmp;
        }

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
            Integer tmp = 0;
            tmp._x.resize(this->_x.size() + rhs._x.size());
            auto v = plus_digits(this->_x.begin(), this->_x.end(), rhs._x.begin(), rhs._x.end(), tmp._x.begin());
            tmp._x.resize(distance(tmp._x.begin(), v));
            *this = tmp;
            return *this;
        }

        // -----------
        // operator -=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator -= (const Integer& rhs) {
            Integer tmp = 0;
            tmp._x.resize(this->_x.size() + rhs._x.size());
            auto v = minus_digits(this->_x.begin(), this->_x.end(), rhs._x.begin(), rhs._x.end(), tmp._x.begin());
            tmp._x.resize(distance(tmp._x.begin(), v));
            *this = tmp;
            return *this;
        }

        // -----------
        // operator *=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator *= (const Integer& rhs) {
            Integer tmp = 0;
            tmp._x.resize(this->_x.size() + rhs._x.size());
            auto v = multiplies_digits(this->_x.begin(), this->_x.end(), rhs._x.begin(), rhs._x.end(), tmp._x.begin());
            tmp._x.resize(distance(tmp._x.begin(), v));
            bool check = true;
            if(!this->positive && !tmp.positive) check = true;
            else if(!this->positive && tmp.positive) check = false;
            else if(this->positive && !tmp.positive) check = false;
            *this = tmp;
            if(!check) this->positive = false;
            return *this;
        }

        // -----------
        // operator /=
        // -----------

        /**
         * <your documentation>
         * @throws invalid_argument if (rhs == 0)
         */
        Integer& operator /= (const Integer& rhs) {
            if (rhs == 0) throw invalid_argument("Integer /=");

            Integer tmp = 0;
            tmp._x.resize(this->_x.size() + rhs._x.size());
            divides_digits(this->_x.begin(), this->_x.end(), rhs._x.begin(), rhs._x.end(), tmp._x.begin());
            *this = tmp;
            return *this;
        }

        // -----------
        // operator %=
        // -----------

        /**
         * <your documentation>
         * @throws invalid_argument if (rhs <= 0)
         */
        Integer& operator %= (const Integer& rhs) {
            Integer wtf = rhs;
            Integer why = 0;
            if (wtf._x <= why) throw invalid_argument("mod()");

            Integer tmp = 0;
            tmp._x.resize(this->_x.size() + wtf._x.size());
            divides_digits(this->_x.begin(), this->_x.end(), wtf._x.begin(), wtf._x.end(), tmp._x.begin());
            *this = tmp;
            return *this;
        }

        // ------------
        // operator <<=
        // ------------

        /**
         * <your documentation>
         */
        Integer& operator <<= (int n) {
            Integer tmp = 0;
            tmp._x.resize(this->_x.size() + n);
            shift_left_digits(this->_x.begin(), this->_x.end(), n, tmp._x.begin());
            *this = tmp;
            return *this;
        }

        // ------------
        // operator >>=
        // ------------

        /**
         * <your documentation>
         */
        Integer& operator >>= (int n) {
            Integer tmp = 0;
            shift_right_digits(this->_x.begin(), this->_x.end(), n, tmp._x.begin());
            *this = tmp;
            return *this;
        }

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
            if (((this == 0) && (e == 0)) || (e < 0))
                throw invalid_argument("Integer: power");

            Integer tmp = 1;
            while (e > 0){
                if (e % 2 == 1){
                    tmp *= *this;
                    e -= 1; 
                }else{
                *this *= *this;
                e /= 2;}
            }
            *this = tmp;
            return *this;
        }
};

#endif // Integer_h
