#include "simpleparser.h"

#include <algorithm>


SimpleParser::SimpleParser():
    Parser{}
{}

std::vector<std::string> SimpleParser::parse(std::string& text)
{
    std::istringstream iss(text);
    return std::vector<std::string>(
                std::make_move_iterator(std::istream_iterator<std::string>{iss}),
                std::make_move_iterator(std::istream_iterator<std::string>()));
}

std::string SimpleParser::packWord(std::vector<std::string>& words,
                     std::string& word)
{
    std::string result;
    if (words.empty()) {
        result = "{ " + word + "? }";
    } else if (words.size() == 1) {
        result = words.at(0);
    } else {
        result = "{" + concatWithSpace(words) + " }";
    }
    return result;
}

std::string SimpleParser::packText(std::vector<std::string>& words)
{
    return concatWithSpace(words);
}


std::string SimpleParser::concatWithSpace(std::vector<std::string>& words) const
{
    return std::accumulate(words.begin(), words.end(), std::string{},
                           [](std::string &s,
                              const std::string &piece) -> decltype(auto) {
        return s += ' ' + piece;
    });
}

std::vector<std::string> SimpleParserWithSavedSpaces::parse(
        std::string& text)
{
    saved_spaces.clear();
    std::vector<std::string> result;

    std::string word = "";
    std::string space = "";

    if (!isspace(*text.cbegin())) {
        saved_spaces.push_back("");
    }

    for (auto ch : text)
    {
        if (std::isspace(ch)) {
            if (!word.empty()) {
                result.push_back(word);
            }
            space += ch;
            word = "";
        } else {
            if (!space.empty()) {
                saved_spaces.push_back(space);
            }
            space = "";
            word += ch;
        }
    }
    if (!word.empty()) {
        result.push_back(word);
    }
    if (!space.empty()) {
        saved_spaces.push_back(space);
    }

    if (!isspace(*(text.cend()-1))) {
        saved_spaces.push_back("");
    }
    return result;
}

std::string SimpleParserWithSavedSpaces::packText(
        std::vector<std::string>& words)
{
    std::string result;
    if ((words.size() + 1) == saved_spaces.size()) {
        for (size_t i = 0, j = 0; i < words.size(); ++i, ++j) {
            result += saved_spaces.at(i);
            result += words.at(i);
        }
    } else { // if smth go wrond
        // TODO: add info about it
        return concatWithSpace(words);
    }
    return result + *saved_spaces.end();
}
