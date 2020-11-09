#ifndef SIMPLEHASHDICT_H
#define SIMPLEHASHDICT_H

#include "dictionary.h"

#include <map>

//! Simple realization of dictionary using hash.
class SimpleHashDict: public Dictionary
{
public:

    SimpleHashDict();

    explicit SimpleHashDict(const std::string& alphabet);

    bool createDict(const std::vector<std::string>& words) final;

    void addWord(const std::string& word) final;

    bool contain(const std::string& word) const final;

    void sort(std::vector<std::string>& candidates) const final;

protected:

    using DictMap = std::map<std::string, int>;

    DictMap dictionary;

};

#endif // SIMPLEHASHDICT_H
