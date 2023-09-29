/**
 * This source file may be used to verify that ascii23.dll
 * can be built and linked with successfully.
 */

#include <iostream>

#define ASCII23_USE_SHARED_LIB
// included twice to test that this doesn't break anything
#include <ascii23.h>
#include <ascii23.h>

int main() {
    if(ascii::is_whitespace_char(' ')) {
        std::cout << "Test ok\n";
        return 0;
    }
    else {
        std::cout << "Test error\n";
        return 1;
    }
}
