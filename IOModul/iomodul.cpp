#include "iomodul.h"

#include <algorithm>
#include <iostream>

IOModul::IOModul()
{}

std::string& IOModul::getDict() const
{
    return const_cast<std::string&>(dict);
}
std::string& IOModul::getText() const
{
    return const_cast<std::string&>(text);
}

StringInStdOut::StringInStdOut():
    IOModul{}
{}

StringInStdOut::StringInStdOut(std::string& text):
    IOModul{}
{
    setText(text);
}

void StringInStdOut::setText(const std::string& text)
{
    this->dict.clear();
    this->text.clear();
    auto found_first = text.find("===");
    auto found_second = text.find("===", found_first+3);
    if (found_first != std::string::npos &&
        found_second != std::string::npos) {
        this->dict = text.substr(0, found_first);
        this->text = text.substr(found_first + 3, found_second - found_first - 3);
    } // TODO add info if smth go wrong
}

void StringInStdOut::output(const std::string& text) const
{
    std::cout << text << std::endl;
}

//void StringInStdOut::setText(std::string text)
//{
//    setText(std::ref(text));
//}

