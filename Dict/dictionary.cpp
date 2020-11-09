#include "dictionary.h"

Dictionary::Dictionary(const std::string alphabet):
    alphabet{alphabet}
{}

const std::string& Dictionary::getAlphabet() const
{
    return alphabet;
}
