#include "simpledictchecker.h"


SimpleDictChecker::SimpleDictChecker(const size_t num_edits):
    BaseSimpleDictChecker(num_edits)
{}

std::vector<std::string> SimpleDictChecker::correctionSuggestions(
        const DictionaryPtr dictionary,
        const std::string& word) const
{
    VectorStr result, edited_words, prev_edits, word_storage;
    DictMap candidates;

    if (dictionary->contain(word)) {
        return VectorStr{word};
    }

    prev_edits.push_back(word);
    for (size_t iteration = 0; iteration < num_edits; iteration++) {
//      word_storage = VectorStr{}; // TODO std::optional<>
        for (const auto& word_v: prev_edits) {
//          edited_words = VectorStr{}; // TODO std::optional<>

            edits(dictionary, word_v, edited_words);
            known(dictionary, edited_words, candidates);

            moveTailToHeadEnd(word_storage, edited_words);
        }

        if (candidatesCheck(dictionary, candidates, result)) {
            return result;
        }

        prev_edits = std::move(word_storage);
    }

    return VectorStr{};
}

void SimpleDictChecker::edits(const DictionaryPtr dictionary,
                              const std::string& word,
                              VectorStr& word_edits) const
{
    for (std::string::size_type i = 0;i < word.size(); i++) {
        word_edits.push_back(word.substr(0, i)
                             + word.substr(i + 1)); //deletions
    }
    for (std::string::size_type i = 0;i < word.size() - 1;i++) {
        word_edits.push_back(word.substr(0, i)
                             + word[i + 1] + word[i]
                             + word.substr(i + 2)); //transposition
    }
    for (const auto& j: dictionary->getAlphabet()) {
        for (std::string::size_type i = 0;i < word.size(); i++) {
            word_edits.push_back(word.substr(0, i) + j
                                 + word.substr(i + 1)); //alterations
      }
        for (std::string::size_type i = 0;i < word.size() + 1;i++) {
             word_edits.push_back(word.substr(0, i) + j
                                  + word.substr(i)); //insertion
       }
    }
}

void SimpleDictChecker::known(const DictionaryPtr dictionary,
                              const VectorStr& words,
                              DictMap& candidates) const
{
    for (unsigned int i = 0;i < words.size();i++) {
        if (dictionary->contain(words[i])) {
            candidates[words[i]]++;
        }
    }
}

SimpleDictCheckerNoAlterNoTransp::SimpleDictCheckerNoAlterNoTransp(const size_t num_edits):
    SimpleDictChecker(num_edits)
{}


void SimpleDictCheckerNoAlterNoTransp::edits(
        const DictionaryPtr dictionary,
        const std::string& word,
        std::vector<std::string>& word_edits) const
{
    for (std::string::size_type i = 0;i < word.size(); i++) {
        word_edits.push_back(word.substr(0, i)
                             + word.substr(i + 1)); //deletions
    }
    for (const auto& j: dictionary->getAlphabet()) {
        for (std::string::size_type i = 0;i < word.size() + 1;i++) {
            word_edits.push_back(word.substr(0, i) + j
                                 + word.substr(i)); //insertion
        }
    }
}
