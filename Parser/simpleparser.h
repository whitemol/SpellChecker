#ifndef SIMPLEPARSER_H
#define SIMPLEPARSER_H

#include <parser.h>

//! Realization of simple splitter and concatenate word
class SimpleParser : public Parser
{
public:

    SimpleParser();

    std::vector<std::string> parse(std::string& text) override;

    std::string packWord(std::vector<std::string>& words,
                         std::string& word) override;

    std::string packText(std::vector<std::string>& words) override;

protected:

    std::string concatWithSpace(std::vector<std::string>& words) const;
};

//! Realization of simple splitter and concatenate word with space saving.
class SimpleParserWithSavedSpaces : public SimpleParser
{
public:

    std::vector<std::string> parse(std::string& text) override;

    // Must be call only after parse
    std::string packText(std::vector<std::string>& words) override;

protected:

    std::vector<std::string> saved_spaces;
};

#endif // SIMPLEPARSER_H
