#include "simpledictionarynonearedits.h"
#include "dictutils.h"

#include <algorithm>

#include <boost/math/special_functions/sign.hpp>


SimpleDictionaryNoNearEdits::SimpleDictionaryNoNearEdits(
        const size_t num_edits, bool save_case):
    BaseSimpleDictChecker{num_edits}, save_case{save_case}
{}

std::vector<std::string> SimpleDictionaryNoNearEdits::correctionSuggestions(
        const DictionaryPtr dictionary,
        const std::string& word) const
{
    if (!DictUtils::isAllAlpha(word)){
        return VectorStr{};
    }

    VectorStr result;
    VectorStrPair edited_words, prev_edits, word_storage;
    DictMap candidates;

    if (dictionary->contain(word)) {
        return VectorStr{word};
    }

    std::vector<bool> case_mask;
    if (save_case) {
        case_mask = DictUtils::getCaseMask(word);
    }

    prev_edits.push_back(std::make_pair(DictUtils::toLowerCopy(word), std::vector<int>()));
    for (size_t iteration = 0; iteration < num_edits; iteration++) {
        for (const auto& word_v: prev_edits) {

            edits(dictionary, word_v, edited_words);
            known(dictionary, edited_words, candidates);

            moveTailToHeadEnd(word_storage, edited_words);
        }

        if (candidatesCheck(dictionary, candidates, result)) {
            if (save_case) {
                std::transform(result.begin(), result.end(), result.begin(),
                               [&case_mask](auto& v) {
                    return DictUtils::applyCaseMask(v, case_mask);
                });
            }
            return result;
        }

        prev_edits = std::move(word_storage);
    }

    return VectorStr{};
}

bool SimpleDictionaryNoNearEdits::allowedInsertions(
        const Mask& mask,
        const std::string::size_type idx,
        const int& corr_idx) const
{
    if (!mask.empty()) {
        auto it = std::find_if(mask.begin(), mask.end(),
                               [](const int& v) {
            return v > 0;
        });
        while (it != mask.end()) {
            if (std::abs((static_cast<int>(*it) - 1)
                         - static_cast<int>(idx) + corr_idx) <= 1) {
                return false;
            }

            it = std::find_if(++it, mask.end(),
                              [](const int& v) {
                return v > 0;
            });
        }
    }
    return true;
}

bool SimpleDictionaryNoNearEdits::allowedDeletions(
        const Mask& mask,
        const std::string::size_type idx,
        const int& corr_idx) const
{
    if (!mask.empty()) {
        auto it = std::find_if(mask.begin(), mask.end(),
                               [](const int& v) {
            return v < 0;
        });
        while (it != mask.end()) {
            if (std::abs((- static_cast<int>(*it) - 1)
                         - static_cast<int>(idx) + corr_idx) <= 1) {
                return false;
            }

            it = std::find_if(++it, mask.end(),
                              [](const int& v) {
                return v < 0;
            });
        }
    }
    return true;
}

SimpleDictionaryNoNearEdits::Mask
SimpleDictionaryNoNearEdits::getCorrectionsIdx(
        const std::string& word,
        const Mask& mask) const
{
    Mask corr_idx;
    corr_idx.resize(word.size() + 1, 0);
    if (!mask.empty()) {
        Mask mask_sorted{mask};

        std::sort(mask_sorted.begin(), mask_sorted.end(),
                  [](auto l, auto r) {
            return std::abs(l) < std::abs(r);
        });
        int sum = 0;
        for (int i = 0, j = 0; i < static_cast<int>(corr_idx.size());) {
            if (j != static_cast<int>(mask_sorted.size())) {
                if ((i+1) >= std::abs(mask_sorted.at(j))) {
                    sum += boost::math::sign(mask_sorted.at(j));
                    j++;
                    corr_idx.at(i) = sum;
                    continue;
                }
            }
            corr_idx.at(i) = sum;
            i++;
        }
    }
    return  corr_idx;
}

void SimpleDictionaryNoNearEdits::edits(
        const DictionaryPtr dictionary,
        const PairStrVec& word_pair,
        VectorStrPair& word_edits) const
{
    auto& word = word_pair.first;
    auto& mask = word_pair.second;

    auto corr_idx = getCorrectionsIdx(word, mask);

    for (std::string::size_type i = 0;i < word.size(); i++) {
        if (allowedDeletions(mask, i, corr_idx.at(i))) {
            auto new_mask = Mask(mask);
            new_mask.push_back(-static_cast<int>(i+1));
            word_edits.push_back(
                        std::make_pair(word.substr(0, i)
                                       + word.substr(i + 1),
                                       new_mask)); //deletions
        }
    }

    for (const auto& j: dictionary->getAlphabet()) {
        for (std::string::size_type i = 0;i < word.size() + 1;i++) {
          if (allowedInsertions(mask, i, corr_idx.at(i))) {
              auto new_mask = Mask(mask);
              new_mask.push_back(static_cast<int>(i+1));
              word_edits.push_back(
                          std::make_pair(word.substr(0, i) + j
                                         + word.substr(i),
                                         new_mask)); //insertion
          }
       }
    }
}

void SimpleDictionaryNoNearEdits::known(
        const DictionaryPtr dictionary,
        const VectorStrPair& words,
        DictMap& candidates) const
{
    for (unsigned int i = 0;i < words.size();i++) {
        auto& word = words.at(i).first;

        if (dictionary->contain(word)) {
            candidates[word]++;
        }
    }
}
