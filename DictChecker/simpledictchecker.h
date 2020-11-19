#ifndef SIMPLEDICTCHECKER_H
#define SIMPLEDICTCHECKER_H

#include "basesimpledictchecker.h"

//! Realization simple checking word by the iteration.
class SimpleDictChecker: public BaseSimpleDictChecker
{
public:

    //! See BaseSimpleDictChecker::BaseSimpleDictChecker
    explicit SimpleDictChecker(const size_t num_edits = 2);

    // TODO add lo_lower and save Upper and lower case
    //! See DictChecker::correctionSuggestions
    std::vector<std::string> correctionSuggestions(
            const DictionaryPtr dictionary,
            const std::string& word) const override;

protected:

    //! Generate edits of word
    virtual void edits(const DictionaryPtr dictionary,
                       const std::string& word,
                       ListStr& word_edits) const;

    //! Check edits of word
    virtual void known(const DictionaryPtr dictionary,
                       const ListStr& words,
                       DictMap& candidates) const;

};


//! Realization simple checking word by the iteration.
//! Edits generates without alteration and transpose.
class SimpleDictCheckerNoAlterNoTransp : public SimpleDictChecker
{
public:

    explicit SimpleDictCheckerNoAlterNoTransp(const size_t num_edits = 2);

    virtual void edits(const DictionaryPtr dictionary,
                       const std::string& word,
                       std::list<std::string>& word_edits) const override;
};

#endif // SIMPLEDICTCHECKER_H
