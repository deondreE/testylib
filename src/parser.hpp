#pragma once

#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;

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
public:
    void parseSpec(string const& specFile);
    void scanHeader(string const& headerFile);
    
    vector<MethodRef> const& getDiscoveredMethods() const 
    {
        return _discoveredMethods;   
    }
};

        