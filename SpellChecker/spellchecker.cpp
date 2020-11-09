#include "spellchecker.h"

SpellChecker::SpellChecker(ParserPtr parcer,
                           DictionaryPtr dict,
                           DictCheckerPtr dictCheck):
    parser{parcer}, dict{dict}, dictCheck{dictCheck}
{}

bool SpellChecker::createDict(std::string& text) {
    auto words = parser->parse(text);
    if (dict->createDict(words))
        return true;
    else
        return false;
}

std::string SpellChecker::correctText(std::string& text) {
    auto words = parser->parse(text);

    for (auto& word: words) {
        auto word_offers = dictCheck->correctionSuggestions(dict, word);
        word = parser->packWord(word_offers, word);
    }
    return parser->packText(words);
}
