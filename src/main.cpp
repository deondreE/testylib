#include "parser.hpp"
#include <iostream>
#include <cassert>

void test_scanner()
{
    Parser parser;

    parser.scanHeader("src/StudentCode.hpp");
    parser.parseSpec("test.spec");

    const auto& results = parser.getDiscoveredMethods();
    auto reqs = parser.getRequirements();

    if (results.empty()) {
        std::cout << "Test Failed: No methods discovered!" << std::endl;
        return;
    }

    std::cout << "Discovered Method details:" << std::endl;
    for (const auto& m : results) {
        std::cout << "Tag: " << m.tag << " | Path: " << m.className << "::" << m.methodName << std::endl;
    }

    assert(results[0].tag == "addition");
	std::cout << results[0].className << std::endl;
    // assert(results[0].className == "Math::Rational");

    // Spec Tests
    assert(!reqs.empty());
    assert(reqs[0].testName == "addition");
    assert(reqs[0].inputData == "7 11"); // Captured space-delimited
    assert(reqs[0].paramTypes.size() == 2);

    std::cout << "Spec Parser Success: Loaded " << reqs.size() << " tests." << std::endl;
}

int main(void) 
{
    test_scanner();
    return 0;     
}