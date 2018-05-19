
#include <INISerializer.h>
#include <fstream>
#include "UnitTest++.h"

static void writeINI(std::string filename, std::string content) {
    std::ofstream f(filename);
    ASSERT_TRUE(f.is_open(), "Couldn't open file");
    f.write(content.data(), content.size());
}

TEST(intTestD) {
    writeINI("test.ini", "[test]\nint=15\n");
    INISerializer::INISerializer serializer;

    int i = 0;
    serializer.registerVariable("test", "int", i);

    serializer.loadFromFile("test.ini");
    ASSERT_EQU(i, 15, "Value does not equal");
    return true;
}

TEST(charTestD) {
    writeINI("test.ini", "[test]\nchar=15\n");
    INISerializer::INISerializer serializer;

    char c = 0;
    serializer.registerVariable("test", "char", c);

    serializer.loadFromFile("test.ini");
    ASSERT_EQU(c, 15, "Value does not equal");

    return true;
}

TEST(shortTestD) {
    writeINI("test.ini", "[test]\nshort=15\n");
    INISerializer::INISerializer serializer;

    short i = 0;
    serializer.registerVariable("test", "short", i);

    serializer.loadFromFile("test.ini");
    ASSERT_EQU(i, 15, "Value does not equal");

    return true;
}

TEST(longTestD) {
    writeINI("test.ini", "[test]\nlong=15\n");
    INISerializer::INISerializer serializer;

    long i = 0;
    serializer.registerVariable("test", "long", i);

    serializer.loadFromFile("test.ini");
    ASSERT_EQU(i, 15, "Value does not match");

    return true;
}

TEST(longlongTestD) {
    writeINI("test.ini", "[test]\nlonglong=15\n");
    INISerializer::INISerializer serializer;

    long long i = 0;
    serializer.registerVariable("test", "longlong", i);

    serializer.loadFromFile("test.ini");
    ASSERT_EQU(i, 15, "Value does not match");

    return true;
}

TEST(uintTestD) {
    writeINI("test.ini", "[test]\nuint=15\n");
    INISerializer::INISerializer serializer;

    unsigned int i = 0;
    serializer.registerVariable("test", "uint", i);

    serializer.loadFromFile("test.ini");
    ASSERT_EQU(i, 15, "Value does not match");

    return true;
}

TEST(ucharTestD) {
    writeINI("test.ini", "[test]\nunsigned char=15\n");
    INISerializer::INISerializer serializer;

    unsigned char c = 0;
    serializer.registerVariable("test", "unsigned char", c);

    serializer.loadFromFile("test.ini");
    ASSERT_EQU(c, 15, "Value does not match");

    return true;
}

TEST(ushortTestD) {
    writeINI("test.ini", "[test]\nushort=15\n");
    INISerializer::INISerializer serializer;

    unsigned short i = 0;
    serializer.registerVariable("test", "ushort", i);

    serializer.loadFromFile("test.ini");
    ASSERT_EQU(i, 15, "Value does not match");

    return true;
}

TEST(ulongTestD) {
    writeINI("test.ini", "[test]\nulong=15\n");
    INISerializer::INISerializer serializer;

    unsigned long i = 0;
    serializer.registerVariable("test", "ulong", i);

    serializer.loadFromFile("test.ini");
    ASSERT_EQU(i, 15, "Value does not match");

    return true;
}

TEST(ulonglongTestD) {
    writeINI("test.ini", "[test]\nulonglong=15\n");
    INISerializer::INISerializer serializer;

    unsigned long long i = 0;
    serializer.registerVariable("test", "ulonglong", i);

    serializer.loadFromFile("test.ini");
    ASSERT_EQU(i, 15, "Value does not match");

    return true;
}


TEST(floatTestD) {
    writeINI("test.ini", "[test]\nfloat=3.141500\n");
    INISerializer::INISerializer serializer;

    float f = 0;
    serializer.registerVariable("test", "float", f);

    serializer.loadFromFile("test.ini");
    ASSERT_EQU(f, 3.1415f, "Value does not match");

    return true;
}

TEST(doubleTestD) {
    writeINI("test.ini", "[test]\ndouble=42.000000\n");
    INISerializer::INISerializer serializer;

    double d = 0;
    serializer.registerVariable("test", "double", d);

    serializer.loadFromFile("test.ini");
    ASSERT_EQU(d, 42, "Value does not match");

    return true;
}

TEST(longdoubleTestD) {
    writeINI("test.ini", "[test]\nlongdouble=3.1415\n");
    INISerializer::INISerializer serializer;

    long double d = 0;
    serializer.registerVariable("test", "longdouble", d);

    serializer.loadFromFile("test.ini");
    ASSERT_EQU(d, 3.1415l, "Value does not match");

    return true;
}

TEST(tupleTestD) {
    writeINI("test.ini", "[test]\ntuple={1,0.000000,3.141500,test}\n");
    INISerializer::INISerializer serializer;

    std::tuple<int, float, double, std::string> t {-1, -1, -1, ""};
    std::tuple<int, float, double, std::string> expected{1, 0, 3.1415, "test"};
    serializer.registerVariable("test", "tuple", t);

    serializer.loadFromFile("test.ini");
    ASSERT_EQU(t, expected, "Value does not match");

    return true;
}

TEST(arrayTestD) {
    writeINI("test.ini", "[test]\narray={1,2,3}\n");
    INISerializer::INISerializer serializer;

    std::array<int, 3> t {0, 0, 0};
    std::array<int, 3> expected {1, 2, 3};
    serializer.registerVariable("test", "array", t);

    serializer.loadFromFile("test.ini");
    ASSERT_EQU(t, expected, "Value does not match");

    return true;
}

TEST(pairTestD) {
    writeINI("test.ini", "[test]\npair={1,3.141500}\n");
    INISerializer::INISerializer serializer;

    std::pair<int, float> t {1, 3.1415};
    std::pair<int, float> expected{1, 3.1415};
    serializer.registerVariable("test", "pair", t);

    serializer.loadFromFile("test.ini");
    ASSERT_EQU(t, expected, "Value does not match");

    return true;
}
TEST(nestedTupleTestD) {
    writeINI("test.ini", "[test]\ntuple={{1,-1,255},0.000000,3.141500,test}\n");
    INISerializer::INISerializer serializer;

    std::tuple<std::tuple<int, char, unsigned int>, float, double, std::string> expected {{1, -1, 255}, 0.0f, 3.1415, "test"};
    std::tuple<std::tuple<int, char, unsigned int>, float, double, std::string> t;
    serializer.registerVariable("test", "tuple", t);

    serializer.loadFromFile("test.ini");
    ASSERT_EQU(t, expected, "Value does not match");

    return true;
}

TEST(nestedArrayTestD) {
    writeINI("test.ini", "[test]\narray={{1,1},{2,2},{3,3}}\n");
    INISerializer::INISerializer serializer;

    std::array<std::array<int, 2>, 3> expected {1,1, 2,2, 3,3};
    std::array<std::array<int, 2>, 3> t;
    serializer.registerVariable("test", "array", t);

    serializer.loadFromFile("test.ini");
    ASSERT_EQU(t, expected, "Value does not match")

    return true;
}

TEST(nestedPairTestD) {
    writeINI("test.ini", "[test]\npair={{1,0.000000},3.141500}\n");
    INISerializer::INISerializer serializer;

    std::pair<std::pair<int, double>, float> expected {{1, 0}, 3.1415};
    std::pair<std::pair<int, double>, float> t;
    serializer.registerVariable("test", "pair", t);

    serializer.loadFromFile("test.ini");

    ASSERT_EQU(t, expected, "Value does not match");

    return true;
}
