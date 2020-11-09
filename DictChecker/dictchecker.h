#ifndef DICTCHECKER_H
#define DICTCHECKER_H

#include <dictionary.h>


class DictChecker;
using DictCheckerPtr = std::shared_ptr<DictChecker>;

//! Simple interface for checking word in dictionary.
class DictChecker
{
public:

    DictChecker();
//    virtual std::string correct(DictionaryPtr dictionary,
//                                std::string& word) = 0;

    //! Get the correction suggestions with priority ordering.
    virtual std::vector<std::string> correctionSuggestions(
            const DictionaryPtr dictionary,
            const std::string& word) const = 0;

};

#endif // DICTCHECKER_H
