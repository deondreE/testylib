#include "parser.hpp"
#include <iostream>
#include <fstream>
#include <regex>

// For more info on regex: https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Regular_expressions/Cheatsheet
void Parser::scanHeader(string const& headerFile) 
{
    std::ifstream file(headerFile);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open header file at: " << headerFile << std::endl;
        return;
    }
    string line;
    
    std::regex namespace_reg(R"(namespace\s+(\w+))");
    std::regex class_reg(R"(class\s+(\w+))");
    std::regex spec_tag_reg(R"(\/\/\s*@test:\s*(\w+))");
    std::regex method_tag(R"((\w+)\s+(\w+)\((.*)\))");
    
    string currentNamespace = "";
    string currentClass = "";
    string pendingTag = "";
    
    while (std::getline(file, line)) 
    {
        std::smatch match;
    
        if (std::regex_search(line, match, namespace_reg)) 
        {
            currentNamespace = match[1];
        }
        
        if (std::regex_search(line, match, class_reg)) 
        {
            currentClass = match[1];
        }    
        
        if (std::regex_search(line, match, spec_tag_reg)) 
        {
            pendingTag = match[1];
            continue;
        }
        
        if (!pendingTag.empty() && std::regex_search(line, match, method_tag)) 
        {
            MethodRef ref;
            ref.tag = pendingTag;
            ref.returnType = match[1];
            ref.methodName = match[2];
            string fullClass = currentClass;   
            if (currentClass.empty()) {
                fullClass = currentNamespace + "::" + currentClass;
            } 
            ref.className = fullClass;
               
            _discoveredMethods.push_back(ref);
            pendingTag = "";
        } 
    }
}