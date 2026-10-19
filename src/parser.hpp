#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

using std::string;
using std::vector;

template <typename ClassType, typename ReturnType, typename... Args>
using MethodPtr = ReturnType (ClassType::*)(Args...);

using TestRegistry = std::unordered_map<string, std::function<void()>>;

class Parser {
public:
    static TestRegistry& getRegistry() {
        static TestRegistry instance;
        return instance;
    }
    
    void runAllTests() {
        for (auto const& [name, testFunc] : getRegistry()) {
            testFunc();
        }
    }
};

#define REGISTER_TEST(TagName, Class, Ret, Method, ...) \
    struct Reg_##TagName { \
        Reg_##TagName() { \
            Parser::getRegistry()[#TagName] = []() { \
                Class obj; \
                auto ptr = &Class::Method; \
                (obj.*ptr)(__VA_ARGS__); \
            }; \
        } \
    } global_##TagName;
        