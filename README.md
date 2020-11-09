# General

A simple" library " for checking the spelling of words.

The main interface is the SpellChecker class. It is any combination of Parser, Dictionary, and DictChecker.

There is also an auxiliary IO Modul

## Dictionary

SimpleHashDict - Simple realization of dictionary using hash.

## DictChecker

SimpleDictChecker - Realization simple checking word by the iteration.

SimpleDictCheckerNoAlterNoTransp - Realization simple checking word by the iteration. Edits generates without alteration and transpose.

SimpleDictionaryNoNearEdits - Implementation Of BaseSimpleDictChecker. Based on the limitation of simultaneous deletions and insertions. And also without transpositions and alterations. It also has the ability to save the case of words.

## Parser

SimpleParser - Realization of simple splitter and concatenate word.

SimpleParserWithSavedSpaces - Realization of simple splitter and concatenate word with space saving.

## IOModul

StringInStdOut - Realization of string input, stdout ouput IO helper class.