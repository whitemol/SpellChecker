#ifndef BASESIMPLEDICTCHECKER_H
#define BASESIMPLEDICTCHECKER_H

#include <dictchecker.h>

#include <map>

//! Base interface for checking word by the iteration.
//! In one iteration, assumptions are made about the word and checked for
//! its presence in the dictionary. The next iteration uses assumptions
//! from the previous one.
class BaseSimpleDictChecker: public DictChecker
{
public:

    //! Construct the object with setted iterarion count.
    explicit BaseSimpleDictChecker(const size_t num_edits = 2);

    //! Set the iterarion count.
    void setNumEdits(const size_t num_edits);

protected:

    using VectorStr = std::vector<std::string>;
    using DictMap = std::map<std::string, int>;

    size_t num_edits;

    template<typename T>
    void moveTailToHeadEnd(T& head, T& tail) const
    {
        head.insert(head.end(),
                    std::make_move_iterator(tail.begin()),
                    std::make_move_iterator(tail.end()));
    }

    //! Checking candidates and move them in result.
    //! If result empty return false.
    virtual bool candidatesCheck(const DictionaryPtr dictionary,
                                 DictMap& candidates,
                                 VectorStr& result) const;

};

#endif // BASESIMPLEDICTCHECKER_H
