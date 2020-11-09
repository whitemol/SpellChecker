#ifndef DICTUTILS_H
#define DICTUTILS_H

#include <string>
#include <vector>

//! Some utils.
namespace DictUtils {

// Required check of isAllAlpha before
std::string toLowerCopy(const std::string& word);

bool isAllAlpha(const std::string& word);

std::vector<bool> getCaseMask(const std::string& word);

std::string& applyCaseMask(std::string& word, std::vector<bool>& case_mask);

}

#endif // DICTUTILS_H
