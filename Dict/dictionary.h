#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <memory>
#include <vector>
#include <string>

// TODO: add check for alphabet and given word
// TODO: add string type, for supporting custom and another string

class Dictionary;
using DictionaryPtr = std::shared_ptr<Dictionary>;

//! Simple interface for Dictionary.
class Dictionary
{
public:
    //! Construct the base object with alphabet.
    explicit Dictionary(
            const std::string alphabet = "abcdefghijklmnopqrstuvwxyz");
//    Dictionary(std::vector<std::string> words);

    //! Create dict from given words.
    virtual bool createDict(const std::vector<std::string>& words) = 0;

//    virtual bool loadDict(const std::string& filename) = 0;

//    virtual bool saveDict(const std::string& filename) const = 0;

    //! Add given word to dictionary.
    virtual void addWord(const std::string& word) = 0;

    //! Check word in dictionary.
    virtual bool contain(const std::string& word) const = 0;

    //! Sort the candidates by priority (from higth to low).
    //! Candidates must be in dictionary.
    virtual void sort(std::vector<std::string>& candidates) const = 0;

    //! Get alphabet.
    const std::string& getAlphabet() const;

protected:

    std::string alphabet;
};

#endif // DICTIONARY_H
