#ifndef SimpleMapDict_H
#define SimpleMapDict_H

#include "dictionary.h"

#include <map>
#include <unordered_map>

//! Simple realization of dictionary using map.
// TODO remove template class from header
template<typename T>
class SimpleMapDict: public Dictionary
{
public:

    SimpleMapDict();

    explicit SimpleMapDict(const std::string& alphabet);

    bool createDict(const std::vector<std::string>& words) final;

    void addWord(const std::string& word) final;

    bool contain(const std::string& word) const final;

    void sort(std::vector<std::string>& candidates) const final;

protected:

    using DictMap = T;

    DictMap dictionary;

};


using SimpleDictMap = SimpleMapDict<std::map<std::string, int>>;
using SimpleDictUMap = SimpleMapDict<std::unordered_map<std::string, int>>;

#endif // SimpleMapDict_H
