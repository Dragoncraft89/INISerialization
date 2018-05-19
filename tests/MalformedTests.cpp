#include <INISerializer.h>
#include <fstream>
#include "UnitTest++.h"

static void writeINI(std::string filename, std::string content) {
    std::ofstream f(filename);
    ASSERT_TRUE(f.is_open(), "Couldn't open file");
    f.write(content.data(), content.size());
}

TEST(MalformedINITests) {
    try {
        writeINI("test.ini", "[section=5");
        INISerializer::INISerializer s;
        s.loadFromFile("test.ini");
        ERROR("\"[section=5\" parsed as valid INI");
        return false;
    } catch(std::runtime_error &e) {
    }

    try {
        writeINI("test.ini", "[section]]");
        INISerializer::INISerializer s;
        s.loadFromFile("test.ini");
        ERROR("\"[section]]\" parsed as valid INI");
        return false;
    } catch(std::runtime_error &e) {
    }

    try {
        writeINI("test.ini", "[section]key");
        INISerializer::INISerializer s;
        int key;
        s.registerVariable("section", "key", key);
        s.loadFromFile("test.ini");
        ERROR("\"[section]key\" parsed as valid INI");
        return false;
    } catch(std::runtime_error &e) {
    }

    try {
        writeINI("test.ini", "[section]key=5");
        INISerializer::INISerializer s;
        int key;
        s.registerVariable("section", "key", key);
        s.loadFromFile("test.ini");
        ERROR("\"[section]key=5\" parsed as valid INI");
        return false;
    } catch(std::runtime_error &e) {
    }

    try {
        writeINI("test.ini", "[section]\nkey");
        INISerializer::INISerializer s;
        int key;
        s.registerVariable("section", "key", key);
        s.loadFromFile("test.ini");
        ERROR("\"[section]\nkey\" parsed as valid INI");
        return false;
    } catch(std::runtime_error &e) {
    }

    return true;
}

TEST(missingEntryTest) {
    try {
        writeINI("test.ini", "[section]\nkey=5");
        INISerializer::INISerializer s;
        int i = 0;
        s.registerVariable("section", "test", i);
        s.loadFromFile("test.ini");
        ERROR("Deserialization of \"[section]\nkey=5\" completed without error");
        return false;
    } catch(std::runtime_error &e) {
    }
    return true;
}

TEST(missingSectionTest) {
    try {
        writeINI("test.ini", "[section]\nkey=5");
        INISerializer::INISerializer s;
        s.loadFromFile("test.ini");
        ERROR("Deserialization of \"[section]\nkey=5\" completed without error");
        return false;
    } catch(std::runtime_error &e) {
    }
    return true;
}

TEST(malformedTupleTest) {
    try {
        writeINI("test.ini", "[section]\nkey={1,2,3,4,5}");
        INISerializer::INISerializer s;
        std::tuple<float, int, std::string> key;
        s.registerVariable("section", "key", key);
        s.loadFromFile("test.ini");
        ERROR("Deserialization with tuple value mismatch completed without error");
        return false;
    } catch(std::runtime_error &e) {
    }

    try {
        writeINI("test.ini", "[section]\nkey={1,2");
        INISerializer::INISerializer s;
        std::tuple<int, int> key;
        s.registerVariable("section", "key", key);
        s.loadFromFile("test.ini");
        ERROR("Deserialization with unbalanced curly brackets completed without error");
        return false;
    } catch(std::runtime_error &e) {
    }

    return true;
}

TEST(malformedPairTest) {
    try {
        writeINI("test.ini", "[section]\nkey={1,2.0}");
        INISerializer::INISerializer s;
        std::pair<float, int> key;
        s.registerVariable("section", "key", key);
        s.loadFromFile("test.ini");
        ERROR("Deserialization with pair value mismatch completed without error");
        return false;
    } catch(std::runtime_error &e) {
    }

    try {
        writeINI("test.ini", "[section]\nkey={1,2");
        INISerializer::INISerializer s;
        std::pair<int, int> key;
        s.registerVariable("section", "key", key);
        s.loadFromFile("test.ini");
        ERROR("Deserialization with unbalanced curly brackets completed without error");
        return false;
    } catch(std::runtime_error &e) {
    }

    return true;
}

TEST(malformedArrayTest) {
    try {
        writeINI("test.ini", "[section]\nkey={1,2.0,3,4,5}");
        INISerializer::INISerializer s;
        std::array<int, 5> key;
        s.registerVariable("section", "key", key);
        s.loadFromFile("test.ini");
        ERROR("Deserialization with array value mismatch completed without error");
        return false;
    } catch(std::runtime_error &e) {
    }

    try {
        writeINI("test.ini", "[section]\nkey={1,2,3,4,5}");
        INISerializer::INISerializer s;
        std::array<float, 4> key;
        s.registerVariable("section", "key", key);
        s.loadFromFile("test.ini");
        ERROR("Deserialization with array size mismatch completed without error");
        return false;
    } catch(std::runtime_error &e) {
    }

    try {
        writeINI("test.ini", "[section]\nkey={1,2");
        INISerializer::INISerializer s;
        std::array<int, 2> key;
        s.registerVariable("section", "key", key);
        s.loadFromFile("test.ini");
        ERROR("Deserialization with unbalanced curly brackets completed without error");
        return false;
    } catch(std::runtime_error &e) {
    }

    return true;
}
