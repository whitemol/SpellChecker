#include "simplemapdict.h"
#include "dictutils.h"

#include <algorithm>

template<typename T>
SimpleMapDict<T>::SimpleMapDict():
    Dictionary()
{}

template<typename T>
SimpleMapDict<T>::SimpleMapDict(const std::string& alphabet):
    Dictionary(alphabet)
{}

template<typename T>
bool SimpleMapDict<T>::createDict(const std::vector<std::string>& words)
{
    for (const auto& word: words) {
        addWord(word);
    }
    return true;
}

template<typename T>
void SimpleMapDict<T>::addWord(const std::string& word)
{
    if (DictUtils::isAllAlpha(word)) {
        dictionary[DictUtils::toLowerCopy(word)]++;
    }
}

template<typename T>
bool SimpleMapDict<T>::contain(const std::string& word) const
{
    return dictionary.find(word) != dictionary.end();
}

template<typename T>
void SimpleMapDict<T>::sort(std::vector<std::string>& candidates) const
{
    std::sort(candidates.begin(), candidates.end(),
              [this](auto& l, auto& r) {
        return dictionary.at(l) > dictionary.at(r);
    });
}

template class SimpleMapDict<std::map<std::string, int>>;
template class SimpleMapDict<std::unordered_map<std::string, int>>;
