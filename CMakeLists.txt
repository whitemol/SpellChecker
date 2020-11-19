cmake_minimum_required(VERSION 3.10)

project(SpellChecker VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    SpellChecker/spellchecker.cpp
    DictChecker/basesimpledictchecker.cpp
    DictChecker/dictchecker.cpp
    Dict/dictionary.cpp
    DictChecker/simpledictionarynonearedits.cpp
    Parser/simpleparser.cpp
    Utils/dictutils.cpp
    DictChecker/simpledictchecker.cpp
    Dict/simplemapdict.cpp
    IOModul/iomodul.cpp
    Parser/parser.cpp
    main.cpp
    )

add_executable(SpellChecker ${SOURCES})

target_include_directories(SpellChecker PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}"
                           "${PROJECT_SOURCE_DIR}/SpellChecker"
                           "${PROJECT_SOURCE_DIR}/Dict"
                           "${PROJECT_SOURCE_DIR}/DictChecker"
                           "${PROJECT_SOURCE_DIR}/Parser"
                           "${PROJECT_SOURCE_DIR}/Utils"
                           "${PROJECT_SOURCE_DIR}/IOModul"
                           )
