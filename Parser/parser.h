#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <vector>
#include <istream>
#include <sstream>
#include <iterator>
#include <numeric>

//! Base parser class.
class Parser
{
public:

    Parser();

    virtual std::vector<std::string> parse(std::string& text) = 0;
    virtual std::string packWord(std::vector<std::string>& words,
                                 std::string& word) = 0;
    virtual std::string packText(std::vector<std::string>& words) = 0;
};

using ParserPtr = std::shared_ptr<Parser>;

// TODO parcer with saving whitespaces

#endif // PARSER_H
