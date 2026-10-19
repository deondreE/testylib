#pragma once

#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;

struct TestRequirement {
    string testName;
    string returnType;
    vector<string> paramTypes;
    string inputData;
    string expectedOutput;
};

struct MethodRef {
    string tag;
    string className;
    string methodName;
    string returnType;
    vector<string> argTypes;
};

class Parser 
{
    vector<MethodRef> _discoveredMethods;
	vector<TestRequirement> _requirements;
public:
    void parseSpec(string const& specFile);
    void scanHeader(string const& headerFile);
    
    void validateContract(); // Matches spec to header.
    
    vector<MethodRef> const& getDiscoveredMethods() const 
    {
        return _discoveredMethods;   
    }
    
    vector<TestRequirement> const& getRequirements() const
    {
        return _requirements;
    }
};