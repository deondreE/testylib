#include "parser.hpp"
#include <iostream>
#include <cassert>

void test_scanner()
{
    Parser parser;

    parser.scanHeader("src/StudentCode.hpp");

    const auto& results = parser.getDiscoveredMethods();

    if (results.empty()) {
        std::cout << "Test Failed: No methods discovered!" << std::endl;
        return;
    }

    std::cout << "Discovered Method details:" << std::endl;
    for (const auto& m : results) {
        std::cout << "Tag: " << m.tag << " | Path: " << m.className << "::" << m.methodName << std::endl;
    }

    assert(results[0].tag == "addition");
    assert(results[0].className == "Math::Rational");
}

int main(void) 
{
    test_scanner();
    return 0;     
}