#include "parser.hpp"
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
// For more info on regex: https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Regular_expressions/Cheatsheet

void Parser::parseSpec(string const& specFile)
{
    std::ifstream file(specFile);
    string line;

	std::regex test_name_reg(R"(-\s*(\w+):\s*(\w+)\s*\((.*)\))");
	std::regex input_data_reg(R"(\s*input:\s*(.*))");
	std::regex output_regex(R"(\s*output:\s*(.*))");
    
    TestRequirement* currentReq = nullptr;

	while (std::getline(file, line))
	{
		std::smatch match;

		if (std::regex_search(line, match, test_name_reg))
		{
            _requirements.push_back({});
            currentReq = &_requirements.back();
            currentReq->testName = match[1];
			currentReq->returnType = match[2];

            std::stringstream ss(match[3]);
            string param;
            while (std::getline(ss, param, ',')) {
                param.erase(0, param.find_first_not_of(" "));
				currentReq->paramTypes.push_back(param);
            }
        }
		else if (currentReq && std::regex_search(line, match, input_data_reg))
		{
			currentReq->inputData = match[1];
		}
		else if (currentReq && std::regex_search(line, match, output_regex))
		{
			currentReq->expectedOutput = match[1];
		}
	}
}
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