#ifndef IOCLASS_H
#define IOCLASS_H

#include <memory>

//! Base IO helper class
class IOModul
{
public:
    virtual std::string& getDict() const;
    virtual std::string& getText() const;
    virtual void output(const std::string& text) const = 0;

protected:

    IOModul();

    std::string dict;
    std::string text;
};

//! Realization of string input, stdout ouput IO helper class
class StringInStdOut: public IOModul
{
public:

    StringInStdOut();
    explicit StringInStdOut(std::string& text);

    void setText(const std::string& text);

    void output(const std::string& text) const override;
};

#endif // IOCLASS_H
