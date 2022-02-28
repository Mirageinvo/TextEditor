#include "dictionary.hpp"

#include <cassert>
#include <fstream>

Dictionary::Dictionary(size_t word_size) : word_size_(word_size){};

std::string Dictionary::make_word_(const std::string &tmp)
{
    bool only_signs = true;
    std::string word = "";
    size_t it1 = 0, it2 = 0;
    for (size_t i = 0; i < tmp.size(); ++i)
    {
        if (static_cast<int>(tmp[i]) >= static_cast<int>('a') && static_cast<int>(tmp[i]) <= static_cast<int>('z') ||
            static_cast<int>(tmp[i]) >= static_cast<int>('A') && static_cast<int>(tmp[i]) <= static_cast<int>('Z'))
        {
            only_signs = false;
            it1 = i;
            break;
        }
    }
    if (only_signs)
    {
        return "";
    }
    for (int i = static_cast<int>(tmp.size()) - 1; i >= 0; --i)
    {
        if (static_cast<int>(tmp[i]) >= static_cast<int>('a') && static_cast<int>(tmp[i]) <= static_cast<int>('z') ||
            static_cast<int>(tmp[i]) >= static_cast<int>('A') && static_cast<int>(tmp[i]) <= static_cast<int>('Z'))
        {
            it2 = static_cast<size_t>(i);
            break;
        }
    }
    for (size_t i = it1; i <= it2; ++i)
    {
        if (tmp[i] != '\'' && tmp[i] != '-' &&
            (static_cast<int>(tmp[i]) < static_cast<int>('a') || static_cast<int>(tmp[i]) > static_cast<int>('z')) &&
            (static_cast<int>(tmp[i]) < static_cast<int>('A') || static_cast<int>(tmp[i]) > static_cast<int>('Z')))
        {
            return "";
        }
        word += tmp[i];
    }
    return word.size() > 1u ? word : "";
}

void Dictionary::set_word_size(const size_t word_size)
{
    word_size_ = word_size;
}

void Dictionary::add_words(const std::string &path)
{
    std::string tmp, word;
    std::ifstream in;
    in.open(path);
    assert(in.is_open());
    if (in.is_open())
    {
        while (!in.eof())
        {
            in >> tmp;
            word = make_word_(tmp);
            if ((word.size() > 1 && word.size() < 10 && word.size() == word_size_) ||
                (word.size() >= 10 && word_size_ == 0))
            {
                add(word);
            }
        }
        in.close();
    }
}