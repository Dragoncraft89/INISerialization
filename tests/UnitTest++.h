#include <string>
#ifndef _WIN32
#include <csignal>
#include <csetjmp>
#include <string.h>
#endif

#include <iostream>
#include <stdexcept>
#include <vector>
#include <chrono>
#include <thread>
#include <functional>

#ifndef UNIT_TESTPLUSPLUS_H
#define UNIT_TESTPLUSPLUS_H
template<bool f()>
bool test();

template<typename T>
inline std::string as_string(T t) {
    return std::to_string(t);
}

template<>
inline std::string as_string<std::string>(std::string s) {
    return "\"" + s + "\"";
}

template<>
inline std::string as_string<const char*>(const char *c) {
    return std::string(c);
}


#define ASSERT_EQU(x, y, msg) { auto tmp_x = x; auto tmp_y = y; if(tmp_x != tmp_y) throw std::runtime_error(as_string(tmp_x) + " != " + as_string(tmp_y) + " (" + __func__ + " on line: " + std::to_string(__LINE__) + "), message: " + as_string(msg)); }
#define ASSERT_TRUE(x, msg) { auto tmp_x = x; if(!tmp_x) throw std::runtime_error("Expected true, got: " + as_string(tmp_x) + " (" + __func__ + " on line: " + std::to_string(__LINE__) + "), message: " + as_string(msg)); }
#define ASSERT_FALSE(x, msg) { auto tmp_x = x; if(tmp_x) throw std::runtime_error("Expected false, got: " + as_string(tmp_x) + " (" + __func__ + " on line: " + std::to_string(__LINE__) + "), message: " + as_string(msg)); }
#define TEST(name) bool name(); \
    template<> inline std::string getName<name>() { return #name; } \
    StaticInitHelper __init_##name##__(test<name>); \
    bool name()

template<bool ()>
inline std::string getName();

static std::vector<std::string> failedTests;
static jmp_buf gBuffer;
template<bool f()>
inline bool test() {
    std::string name = getName<f>();
    std::cout << "Testing \'" << name << "\'" << std::endl;
    try {
        int sig;
        if((sig = setjmp(gBuffer)) == 0) {
            bool succ = f();

            if(succ) {
                std::cout << "\033[1;32mTest \'" << name << "\' executed succesfully\033[m\n" << std::endl;
            } else {
                std::cerr << "Test \'" << name << "\' failed\n" << std::endl;
                failedTests.push_back(name);
            }

            return succ;
        } else {
            throw sig;
        }
    } catch(const std::runtime_error &e) {
        std::cerr << "Test \'" << name << "\' failed with exception\n" << e.what() << '\n' << std::endl;
    } catch(const int &sig) {
        std::cerr << "Test \'" << name << "\' failed with signal " << sig << '\n' << std::endl;
    } catch(...) {
        std::cerr << "Test \'" << name << "\' failed with unknown reason\n" << std::endl;
    }

    return false;
}

inline std::vector<std::function<bool()>> &getTests() {
    static std::vector<std::function<bool()>> testFunctions;
    return testFunctions;
}

class StaticInitHelper {
public:
    StaticInitHelper(bool f()) {
        getTests().push_back(f);
    }
};
#endif
