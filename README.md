# INISerialization

A Small C++ Library for (de)serialization to INI-Files

Examples:
```C++
#include <INISerializer.h>
void serialization() {
  INISerializer::INISerializer s;
  
  std::tuple<int, float, std::string> tuple {1, 3.1415, "Hello, world!"};
  s.registerVariable("sectionName", "keyName", tuple);
  
  s.saveToFile("configuration.ini");
}

void deserialization() {
  INISerializer::INISerializer s;
  
  std::tuple<int, float, std::string> tuple;
  s.registerVariable("sectionName", "keyName", tuple);
  
  s.loadFromFile("configuration.ini");
  std::cout << "{" << std::get<0>(tuple) << ", " << std::get<1>(tuple) << ", " << std::get<2>(tuple) << "};
}

int main(int argc, char *argv[]) {
  serialization();
  deserialization();
}
```
