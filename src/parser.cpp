#include "parser.hpp"

#include <string>
#include <vector>
#include <unordered_map>
using std::string;
using std::vector;

struct MethodRef {
	string className;
	string methodName;
	string returnType;

};