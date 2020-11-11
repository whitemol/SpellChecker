#include "simplehashdict.h"
#include "dictutils.h"

#include <algorithm>


SimpleHashDict::SimpleHashDict():
    Dictionary()
{}

SimpleHashDict::SimpleHashDict(const std::string& alphabet):
    Dictionary(alphabet)
{}

bool SimpleHashDict::createDict(const std::vector<std::string>& words)
{
    for (const auto& word: words) {
        addWord(word);
    }
    return true;
}

void SimpleHashDict::addWord(const std::string& word)
{
    if (DictUtils::isAllAlpha(word)) {
        dictionary[DictUtils::toLowerCopy(word)]++;
    }
}

bool SimpleHashDict::contain(const std::string& word) const
{
    return dictionary.find(word) != dictionary.end();
}

void SimpleHashDict::sort(std::vector<std::string>& candidates) const
{
    std::sort(candidates.begin(), candidates.end(),
              [this](auto& l, auto& r) {
        return dictionary.at(l) > dictionary.at(r);
    });
}
