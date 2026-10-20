#include "spec_parser.hpp"
#include <stdexcept>

SpecToken SpecParser::peek()
{
    return _tokens[_pos];
}

// Returns the current token and moves to the next one.
SpecToken SpecParser::advance()
{
    return _tokens[++_pos];
}

void SpecParser::expect(SpecTokenType type, string msg)
{
    if (peek().type != type)
    {
        throw std::runtime_error(msg);
    }
    advance();
}

void SpecParser::parse_spec()
{
    while (peek().type != SpecTokenType::END_OF_FILE)
    {
        if (peek().type == SpecTokenType::DASH)
        {
            parse_test_entry();
        }
        else {
            advance();
        }
    }
}

void SpecParser::parse_test_entry()
{
    expect(SpecTokenType::DASH, "Expected '-' at start of test");
    string name = advance().value;
    expect(SpecTokenType::COLON, "Expected ':' after test name");

    // Parse Signature: int (int, int)
    string return_type = advance().value;
    expect(SpecTokenType::LPAREN, "Expected '('");
    vector<string> params = parse_parameters();
    expect(SpecTokenType::RPAREN, "Expected ')'");

    // Parse Indented Blocks
    expect(SpecTokenType::NEWLINE, "Expected newline");
    parse_data_block("input");
    parse_data_block("output");
}

vector<string> SpecParser::parse_parameters()
{
    vector<string> params;
    while (peek().type != SpecTokenType::RPAREN)
    {
        params.push_back(advance().value);
        if (peek().type == SpecTokenType::COMMA) {
            advance(); // Skip comma
        }
    }
    return params;
}

void SpecParser::parse_data_block(string blockName)
{
    expect(SpecTokenType::INDENT, "Expected indentation for " + blockName + " block");
    expect(SpecTokenType::IDENTIFIER, "Expected identifier for " + blockName + " block");
    expect(SpecTokenType::COLON, "Expected ':' after " + blockName + " block name");
    expect(SpecTokenType::NEWLINE, "Expected newline after " + blockName + " block header");
    while (peek().type == SpecTokenType::INDENT)
    {
        advance(); // Skip indentation
        if (peek().type == SpecTokenType::LITERAL) {
            advance(); // Capture literal data
        }
        expect(SpecTokenType::NEWLINE, "Expected newline after data entry in " + blockName + " block");
    }
}
