#ifndef SPELLCHECKER_H
#define SPELLCHECKER_H

#include "dictionary.h"
#include "dictchecker.h"
#include "parser.h"
#include "iomodul.h"

#include <functional>

class SpellChecker;
using SpellCheckerPtr = std::shared_ptr<SpellChecker>;

//! Head helper class for spell checking.
//! The parser, dictionary, and dictionary checker is used here.
class SpellChecker
{

protected:

    ParserPtr parser;
    DictionaryPtr dict;
    DictCheckerPtr dictCheck;

public:

    explicit SpellChecker(ParserPtr parcer,
                          DictionaryPtr dict,
                          DictCheckerPtr dictCheck);

    //! Interface to create dictionary
    bool createDict(std::string& text);

//    bool loadDict(const std::string& filename) = 0;
//    bool saveDict(const std::string& filename) const = 0;

    //! Interface to spell checking.
    std::string correctText(std::string& text);
};

#endif // SPELLCHECKER_H
