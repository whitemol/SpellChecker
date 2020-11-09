#include <dictutils.h>

#include <algorithm>

#include <boost/algorithm/string/case_conv.hpp>


namespace DictUtils
{

std::string toLowerCopy(const std::string& word)
{
    return boost::to_lower_copy(word);
}

bool isAllAlpha(const std::string& word) {
    return std::find_if(word.cbegin(), word.cend(),
                        [](char c) {
                            return !std::isalpha(c);
                        }) == word.cend();
}

std::vector<bool> getCaseMask(const std::string& word)
{
    std::vector<bool> result;
    result.resize(word.size(), false);

//    std::for_each(word.begin(), word.end(),
//                  [&, result, word](auto& ch) {
//         if (std::isupper(ch)) {
//             result[std::distance(word.cbegin(), ch)] = true;
//         }
//    });
    for (size_t i = 0; i < word.size(); ++i) {
        if (std::isupper(word[i])) {
            result[i] = true;
        }
    }
    return result;
}

std::string& applyCaseMask(std::string& word, std::vector<bool>& case_mask)
{
    if (!case_mask.empty() && !word.empty()) {
        if (case_mask.size() ==  word.size()) { // if size mismatch how apply?
            for (size_t i = 0; i < word.size(); ++i) {
                if (case_mask[i]) {
                    word[i] = std::toupper(word[i]);
                }
            }
        } else { // Save only first letter
            if (case_mask[0]) {
                word[0] = std::toupper(word[0]);
            }
        }
    }
    return word;
}

}
