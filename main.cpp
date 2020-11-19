#include <iostream>

#include <spellchecker.h>
#include <simplemapdict.h>
#include <simpledictchecker.h>
#include <simpledictionarynonearedits.h>
#include <simpleparser.h>
#include <iomodul.h>

// TODO: Using cmake, Unit test. Make it as lib.
//       Mb remove boost usage, or make it optional
//       Add namespace SpellChecker
//       Add const versions of SpellChecker
//       Add exceptions, All to namespace
//       Threadsave, thread pool
//       Trees dicts
//       Doxygen, time measuring

SpellCheckerPtr createSpellCheckerHashNoNearEdits()
{
    return std::make_shared<SpellChecker>
            (SpellChecker(std::make_shared<SimpleParserWithSavedSpaces>(),
                          std::make_shared<SimpleDictUMap>(),
                          std::make_shared<SimpleDictionaryNoNearEdits>()));
}

SpellCheckerPtr createSpellCheckerHashNoNearLowMemEdits()
{
    return std::make_shared<SpellChecker>
            (SpellChecker(std::make_shared<SimpleParserWithSavedSpaces>(),
                          std::make_shared<SimpleDictUMap>(),
                          std::make_shared<SimpleDictionaryNoNearEditsLowMem>()));
}

SpellCheckerPtr createSpellCheckerHashSimple()
{
    return std::make_shared<SpellChecker>
            (SpellChecker(std::make_shared<SimpleParser>(),
                          std::make_shared<SimpleDictUMap>(),
                          std::make_shared<SimpleDictChecker>()));
}

SpellCheckerPtr createSpellCheckerHashSimpleNoAlterNoTransp()
{
    return std::make_shared<SpellChecker>
            (SpellChecker(std::make_shared<SimpleParser>(),
                          std::make_shared<SimpleDictUMap>(),
                          std::make_shared<SimpleDictCheckerNoAlterNoTransp>()));
}

void testSpellChecker(StringInStdOut& io_modul,
                      SpellCheckerPtr checker,
                      const std::string& text)
{
    std::cout << std::endl << std::endl
              << "Example: "
              << std::endl << std::endl
              << text
              << std::endl ;
    io_modul.setText(text);
    checker->createDict(io_modul.getDict());
    std::cout << std::endl << std::endl
              << "Correction: "
              << std::endl << std::endl;
    io_modul.output(checker->correctText(io_modul.getText()));
}

int main()
{
    SpellCheckerPtr checker = createSpellCheckerHashNoNearEdits();
    StringInStdOut io_modul;

    testSpellChecker(io_modul, checker,
                     std::string("rain spain plain plaint pain main mainly\n"
                                 "the in on fall falls his was\n"
                                 "===\n"
                                 "hte rame in pain fells\n"
                                 "mainy oon teh lain\n"
                                 "was hints pliant\n"
                                 "==="));

    testSpellChecker(io_modul, checker,
                     std::string("rain spain plain plaint pain main mainly\n"
                                 "the in on fall falls his was\n"
                                 "===\n"
                                 " HTE  Rame in pain fells   "
                                 "   mainy Oon teh lain \n"
                                 " was hints pliant "
                                 "==="));

    SpellCheckerPtr checker_low_mem = createSpellCheckerHashNoNearLowMemEdits();
    testSpellChecker(io_modul, checker_low_mem,
                     std::string("rain qwerty"
                                 " spain plain plaint pain main mainly\n"
                                 "the in on fall falls his was\n"
                                 "===\n"
                                 " HTE  Rame in pain fells  qery "
                                 "   mainy Oon teh lain \n"
                                 " was hints pliant "
                                 "==="));

    testSpellChecker(io_modul, checker_low_mem,
                     std::string("rain qwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnm"
                                 " spain plain plaint pain main mainly\n"
                                 "the in on fall falls his was\n"
                                 "===\n"
                                 " HTE  Rame in pain fells  qwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcbn "
                                 "   mainy Oon teh lain \n"
                                 " was hints pliant "
                                 "==="));


    return 0;
}
