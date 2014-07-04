#include "Integer.h"
#include <algorithm> // equal
#include <cstring>   // strcmp
#include <sstream>   // ostringstream
#include <stdexcept> // invalid_argument
#include <string>    // ==

using namespace std;

void test_1(){
    const int a[] = {2, 3, 4};
    const int b[] = {5, 6, 7};
    const int c[] = {8, 0, 1};
          int x[10];
    const int* p = plus_digits(a, a + 3, b, b + 3, x);
    cout << (p-x) << endl;
    //for(int i = 0; i < 10; i++){cout <<}
    //cout << endl;
}

void test_2(){
    const int a[] = {1};
    const int b[] = {1};
    const int c[] = {2};
          int x[10];
    const int* p = plus_digits(a, a + 1, b, b + 1, x);
    cout << (p-x) << endl;
}

void test_3(){
	const int a[] = {9, 9, 8};
    const int b[] = {3};
    const int c[] = {1, 0, 0, 1};
          int x[10];
    const int* p = plus_digits(a, a + 3, b, b + 1, x);
    cout << (p-x) << endl;
    for(auto c : x){ cout << c;}
    cout << endl;
}

int main()
{
	// test_1();
	// test_2();
	test_3();

    // for(int a, b = 0; a < 5; a++, b++){
            
    // }

	return 0;
}

