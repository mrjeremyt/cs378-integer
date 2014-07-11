#include <algorithm> // equal
#include <cstring>   // strcmp
#include <sstream>   // ostringstream
#include <stdexcept> // invalid_argument
#include <string>    // ==
#include <iostream>
#include <assert.h>

#include "Integer.h"

using namespace std;


int main()
{


    try {
        Integer<int>       x = 98765;
        const int          e =  9867;
        Integer<int>&      y = x.pow(e);
        assert(9867 == e);
        assert(0 == x);
        assert(&x == &y);
    }catch (std::invalid_argument& e) {
        assert(false);
    }

	return 0;
}

