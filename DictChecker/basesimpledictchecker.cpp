#include "basesimpledictchecker.h"

#include <algorithm>
#include <functional>

BaseSimpleDictChecker::BaseSimpleDictChecker(const size_t num_edits):
        DictChecker(), num_edits{num_edits}
{}

void BaseSimpleDictChecker::setNumEdits(const size_t num_edits)
{
    this->num_edits = num_edits;
}

bool BaseSimpleDictChecker::candidatesCheck(
        const DictionaryPtr dictionary,
        DictMap& candidates,
        VectorStr& result) const
{
    if (candidates.size() > 0) {
        result.reserve(candidates.size());
        std::transform(candidates.cbegin(), candidates.cend(),
                       std::back_inserter(result),
                       std::bind(&DictMap::value_type::first,
                                 std::placeholders::_1));
        dictionary->sort(result);
        return true;
    } else {
        return false;
    }
}
