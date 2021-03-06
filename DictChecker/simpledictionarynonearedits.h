#ifndef SIMPLEDICTIONARYNONEAREDITS_H
#define SIMPLEDICTIONARYNONEAREDITS_H

#include "basesimpledictchecker.h"

//! Implementation Of BaseSimpleDictChecker. Based on the limitation of
//! simultaneous deletions and insertions. And also without transpositions
//! and alterations. It also has the ability to save the case of words.
class SimpleDictionaryNoNearEdits: public BaseSimpleDictChecker
{
public:

     //! See BaseSimpleDictChecker::BaseSimpleDictChecker
     //! It also have possibility to disable saving case.
    explicit SimpleDictionaryNoNearEdits(const size_t num_edits = 2,
                                         const bool save_case = true);

    //! See DictChecker::correctionSuggestions
    std::vector<std::string> correctionSuggestions(
            const DictionaryPtr dictionary,
            const std::string& word) const override;

protected:

    // vector<int> contatin +(idx+1) for insertions and -(idx+1) for deletions
    using Mask = std::vector<int>;
    using PairStrVec = std::pair<std::string, Mask>;
    using VectorStrPair = std::vector<PairStrVec>;

    bool save_case;

    //! Checks whether insertion is possible
    virtual bool allowedInsertions(const Mask& mask,
                                   const std::string::size_type idx,
                                   const int& corr_idx) const;

    //! Checks whether deletion is possible
    virtual bool allowedDeletions(const Mask& mask,
                                  const std::string::size_type idx,
                                  const int& corr_idx) const;

    //! Build correction vector for rigth checking in
    //! allowedInsertions and allowedDeletions
    virtual Mask getCorrectionsIdx(const std::string& word,
                                   const Mask& mask) const;

    //! Generate edits of word with checking of
    //! allowedInsertions and allowedDeletions
    virtual void edits(const DictionaryPtr dictionary,
                       const PairStrVec& word_pair,
                       VectorStrPair& word_edits) const;

    //! Check edits of word
    virtual void known(const DictionaryPtr dictionary,
                       const VectorStrPair& words,
                       DictMap& candidates) const;
};

#endif // SIMPLEDICTIONARYNONEAREDITS_H
