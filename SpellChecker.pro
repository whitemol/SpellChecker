TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    SpellChecker/spellchecker.cpp \
    DictChecker/basesimpledictchecker.cpp \
    DictChecker/dictchecker.cpp \
    Dict/dictionary.cpp \
    DictChecker/simpledictionarynonearedits.cpp \
    Parser/simpleparser.cpp \
    Utils/dictutils.cpp \
    DictChecker/simpledictchecker.cpp \
    Dict/simplehashdict.cpp \
    IOModul/iomodul.cpp \
    Parser/parser.cpp \
    main.cpp

HEADERS += \
    SpellChecker/spellchecker.h \
    DictChecker/basesimpledictchecker.h \
    DictChecker/dictchecker.h \
    Dict/dictionary.h \
    DictChecker/simpledictionarynonearedits.h \
    Parser/simpleparser.h \
    Utils/dictutils.h \
    DictChecker/simpledictchecker.h \
    Dict/simplehashdict.h \
    IOModul/iomodul.h \
    Parser/parser.h

INCLUDEPATH += $$PWD/Dict
INCLUDEPATH += $$PWD/DictChecker
INCLUDEPATH += $$PWD/Utils
INCLUDEPATH += $$PWD/Parser
INCLUDEPATH += $$PWD/SpellChecker
INCLUDEPATH += $$PWD/IOModul
