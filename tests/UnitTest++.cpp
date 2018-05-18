//
// Created by florian on 22.01.18.
//

#include "UnitTest++.h"
#ifndef _WIN32
inline void sigHandler(int sig) {
    std::cerr << "Signal " << sig << " received (" << strsignal(sig) << ")" << std::endl;
    signal(sig, sigHandler);

    longjmp(gBuffer, sig);
}
#endif

int main() {
#ifndef _WIN32
    for(int sig = 1;sig <= 15; sig++)
        signal(sig, sigHandler);
#endif
    int passed = 0;
    int tests = 0;
    for(std::function<bool()> &testFunc:getTests()) {
        if(testFunc())
            ++passed;
        ++tests;

        // Wait until all output is written
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // change terminal font color depending on percentage of failed tests
    int color;
    if(passed == tests)
        color = 32; // green
    else if(passed > tests/2.0f)
        color = 33; // yellow
    else
        color = 31; // red

    std::cout << "Test Results:\n\033[1;" << color << "m" << passed << "/" << tests << " tests passed\033[m" << std::endl;
    if(!failedTests.empty()) {
        std::cerr << "\nList of failed tests:";
        for(std::string &name:failedTests)  {
            std::cerr << '\n' << name;
        }
        std::cerr << std::endl;
    }

    return 0;
}
