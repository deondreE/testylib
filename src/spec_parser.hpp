#pragma once
#include "util.hpp"
#include <stdexcept>

enum class SpecTokenType
{
	DASH,
	COLON,
	LPAREN,
	RPAREN,
	COMMA,
	IDENTIFIER,
	LITERAL,
	INDENT,
	NEWLINE,
	END_OF_FILE
};

struct SpecToken
{
	SpecTokenType type;
	string value;
	int line;
};

class SpecParser {
    vector<SpecToken> _tokens;
    int _pos = 0;

    SpecToken peek();
    SpecToken advance();
    void expect(SpecTokenType type, string msg);
    void expect_word(string const& word);

    string parse_type();
    vector<string> parse_parameters();
    vector<string> parse_data_block(string block_name);
public:
    void parse_spec();
    void parse_test_entry();
    
};
