
#include <INISerializer.h>
#include <fstream>
#include "UnitTest++.h"

static void checkINI(std::string filename, std::string content) {
    std::ifstream f(filename, std::ios_base::ate);
    ASSERT_TRUE(f.is_open(), "File not found!")

    char buff[static_cast<size_t>(f.tellg())+1];
    f.seekg(0, std::ios_base::beg);
    memset(buff, 0, sizeof(buff));
    f.read(buff, sizeof(buff));
    f.close();

    bool matches = strcmp(buff, content.data()) == 0;
    std::string s = "Content does not match, expected'" + content + "' got: '" + std::string(buff) + "'";
    ASSERT_TRUE(matches, s);
}

TEST(intTest) {
    INISerializer::INISerializer serializer;

    int i = std::numeric_limits<int>::max();
    serializer.registerVariable("test", "int", i);

    serializer.saveToFile("test.ini");

    checkINI("test.ini", "[test]\nint="+std::to_string(i)+"\n");
    return true;
}

TEST(charTest) {
    INISerializer::INISerializer serializer;

    char c = std::numeric_limits<char>::max();
    serializer.registerVariable("test", "char", c);

    serializer.saveToFile("test.ini");

    checkINI("test.ini", "[test]\nchar="+std::to_string(c)+"\n");
    return true;
}

TEST(shortTest) {
    INISerializer::INISerializer serializer;

    short i = std::numeric_limits<short>::max();
    serializer.registerVariable("test", "short", i);

    serializer.saveToFile("test.ini");

    checkINI("test.ini", "[test]\nshort="+std::to_string(i)+"\n");
    return true;
}

TEST(longTest) {
    INISerializer::INISerializer serializer;

    long i = std::numeric_limits<long>::max();
    serializer.registerVariable("test", "long", i);

    serializer.saveToFile("test.ini");

    checkINI("test.ini", "[test]\nlong="+std::to_string(i)+"\n");
    return true;
}

TEST(longlongTest) {
    INISerializer::INISerializer serializer;

    long long i = std::numeric_limits<long long>::max();
    serializer.registerVariable("test", "longlong", i);

    serializer.saveToFile("test.ini");

    checkINI("test.ini", "[test]\nlonglong="+std::to_string(i)+"\n");
    return true;
}

TEST(uintTest) {
    INISerializer::INISerializer serializer;

    unsigned int i = std::numeric_limits<unsigned int>::max();
    serializer.registerVariable("test", "uint", i);

    serializer.saveToFile("test.ini");

    checkINI("test.ini", "[test]\nuint="+std::to_string(i)+"\n");
    return true;
}

TEST(ucharTest) {
    INISerializer::INISerializer serializer;

    unsigned char c = std::numeric_limits<unsigned char>::max();
    serializer.registerVariable("test", "unsignedchar", c);

    serializer.saveToFile("test.ini");

    checkINI("test.ini", "[test]\nunsignedchar="+std::to_string(c)+"\n");
    return true;
}

TEST(ushortTest) {
    INISerializer::INISerializer serializer;

    unsigned short i = std::numeric_limits<unsigned short>::max();
    serializer.registerVariable("test", "ushort", i);

    serializer.saveToFile("test.ini");

    checkINI("test.ini", "[test]\nushort="+std::to_string(i)+"\n");
    return true;
}

TEST(ulongTest) {
    INISerializer::INISerializer serializer;

    unsigned long i = std::numeric_limits<unsigned long>::max();
    serializer.registerVariable("test", "ulong", i);

    serializer.saveToFile("test.ini");

    checkINI("test.ini", "[test]\nulong="+std::to_string(i)+"\n");
    return true;
}

TEST(ulonglongTest) {
    INISerializer::INISerializer serializer;

    unsigned long long i = std::numeric_limits<unsigned long long>::max();
    serializer.registerVariable("test", "ulonglong", i);

    serializer.saveToFile("test.ini");

    checkINI("test.ini", "[test]\nulonglong="+std::to_string(i)+"\n");
    return true;
}


TEST(floatTest) {
    INISerializer::INISerializer serializer;

    float f = std::numeric_limits<float>::max();
    serializer.registerVariable("test", "float", f);

    serializer.saveToFile("test.ini");

    checkINI("test.ini", "[test]\nfloat="+std::to_string(f)+"\n");
    return true;
}

TEST(doubleTest) {
    INISerializer::INISerializer serializer;

    double d = std::numeric_limits<double>::max();
    serializer.registerVariable("test", "double", d);

    serializer.saveToFile("test.ini");

    checkINI("test.ini", "[test]\ndouble="+std::to_string(d)+"\n");
    return true;
}

TEST(longdoubleTest) {
    INISerializer::INISerializer serializer;

    long double d = std::numeric_limits<long double>::max();
    serializer.registerVariable("test", "longdouble", d);

    serializer.saveToFile("test.ini");

    checkINI("test.ini", "[test]\nlongdouble="+std::to_string(d)+"\n");
    return true;
}

TEST(tupleTest) {
    INISerializer::INISerializer serializer;

    std::tuple<int, float, double, std::string> t {1, 0.0f, 3.1415, "test"};
    serializer.registerVariable("test", "tuple", t);

    serializer.saveToFile("test.ini");

    checkINI("test.ini", "[test]\ntuple={1,0.000000,3.141500,test}\n");
    return true;
}

TEST(arrayTest) {
    INISerializer::INISerializer serializer;

    std::array<int, 3> t {1, 2, 3};
    serializer.registerVariable("test", "array", t);

    serializer.saveToFile("test.ini");

    checkINI("test.ini", "[test]\narray={1,2,3}\n");
    return true;
}

TEST(pairTest) {
    INISerializer::INISerializer serializer;

    std::pair<int, float> t {1, 3.1415};
    serializer.registerVariable("test", "pair", t);

    serializer.saveToFile("test.ini");

    checkINI("test.ini", "[test]\npair={1,3.141500}\n");
    return true;
}

TEST(nestedTupleTest) {
    INISerializer::INISerializer serializer;

    std::tuple<std::tuple<int, char, unsigned int>, float, double, std::string> t {{1, -1, 255}, 0.0f, 3.1415, "test"};
    serializer.registerVariable("test", "tuple", t);

    serializer.saveToFile("test.ini");

    checkINI("test.ini", "[test]\ntuple={{1,-1,255},0.000000,3.141500,test}\n");
    return true;
}

TEST(nestedArrayTest) {
    INISerializer::INISerializer serializer;

    std::array<std::array<int, 2>, 3> t {1,1, 2,2, 3,3};
    serializer.registerVariable("test", "array", t);

    serializer.saveToFile("test.ini");

    checkINI("test.ini", "[test]\narray={{1,1},{2,2},{3,3}}\n");
    return true;
}

TEST(nestedPairTest) {
    INISerializer::INISerializer serializer;

    std::pair<std::pair<int, double>, float> t {{1, 0}, 3.1415};
    serializer.registerVariable("test", "pair", t);

    serializer.saveToFile("test.ini");

    checkINI("test.ini", "[test]\npair={{1,0.000000},3.141500}\n");
    return true;
}
