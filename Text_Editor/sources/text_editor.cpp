#include "text_editor.hpp"

#include <cassert>
#include <fstream>
#include <thread>

TextEditor::TextEditor() : tables_(new Dictionary[9])
{
    tables_[8].set_word_size(0);
    for (size_t i = 0; i < 8; ++i)
    {
        tables_[i].set_word_size(i + 2);
    }
}

TextEditor::~TextEditor()
{
    delete[] tables_;
}

void TextEditor::teach(const std::string &path)
{
    std::string tmp = "../../texts_for_teaching/" + path;
    auto arr = new std::thread[9];
    for (size_t i = 0; i < 9; ++i)
    {
        arr[i] = std::thread(&Dictionary::add_words, &tables_[i], std::ref(tmp));
    }
    for (size_t i = 0; i < 9; ++i)
    {
        arr[i].join();
    }
    delete[] arr;
}

std::string TextEditor::find_best_word(const std::string &word) const
{
    size_t dist = 1e9, freq = 0;
    std::string ret;
    if (word.size() == 2)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            tables_[j].get_best_word(ret, dist, freq, word);
        }
    }
    else if (word.size() == 3)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            tables_[j].get_best_word(ret, dist, freq, word);
        }
    }
    else if (word.size() == 9)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            tables_[j + 5].get_best_word(ret, dist, freq, word);
        }
    }
    else if (word.size() == 10)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            tables_[j + 6].get_best_word(ret, dist, freq, word);
        }
    }
    else if (word.size() == 11)
    {
        for (size_t j = 0; j < 2; ++j)
        {
            tables_[j + 7].get_best_word(ret, dist, freq, word);
        }
    }
    else if (word.size() >= 12)
    {
        tables_[8].get_best_word(ret, dist, freq, word);
    }
    else
    {
        for (size_t j = 0; j < 5; ++j)
        {
            tables_[j + word.size() - 4].get_best_word(ret, dist, freq, word);
        }
    }
    return ret;
}

std::string TextEditor::cut_word_(const std::string &tmp, size_t &it1, size_t &it2)
{
    bool only_signs = true;
    std::string word = "";
    for (size_t i = 0; i < tmp.size(); ++i)
    {
        if ((static_cast<unsigned>(tmp[i]) >= static_cast<unsigned>('a') &&
             static_cast<unsigned>(tmp[i]) <= static_cast<unsigned>('z')) ||
            (static_cast<unsigned>(tmp[i]) >= static_cast<unsigned>('A') &&
             static_cast<unsigned>(tmp[i]) <= static_cast<unsigned>('Z')))
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
        if ((static_cast<int>(tmp[static_cast<size_t>(i)]) >= static_cast<int>('a') &&
             static_cast<int>(tmp[static_cast<size_t>(i)]) <= static_cast<int>('z')) ||
            (static_cast<int>(tmp[static_cast<size_t>(i)]) >= static_cast<int>('A') &&
             static_cast<int>(tmp[static_cast<size_t>(i)]) <= static_cast<int>('Z')))
        {
            it2 = static_cast<size_t>(i);
            break;
        }
    }
    for (size_t i = it1; i <= it2; ++i)
    {
        word += tmp[i];
    }
    return word.size() > 1u ? word : "";
}

void TextEditor::fix_mist(const std::string &path)
{
    bool was_space, frst_word;
    std::string word, tmp, line;
    std::ifstream in;
    std::ofstream out;
    in.open("../../texts_for_fixing/" + path);
    out.open("../../fixed_texts/" + path);
    assert(in.is_open());
    assert(out.is_open());
    size_t it1, it2;
    if (in.is_open() && out.is_open())
    {
        while (!in.eof())
        {
            std::getline(in, line);
            tmp = "";
            was_space = true;
            frst_word = true;
            for (size_t i = 0; i < line.size(); ++i)
            {
                if (line[i] == ' ' || i == line.size() - 1)
                {
                    if (i == line.size() - 1)
                    {
                        tmp += line[i];
                    }
                    if (!frst_word)
                    {
                        out << " ";
                    }
                    frst_word = false;
                    if (!was_space)
                    {
                        word = cut_word_(tmp, it1, it2);
                        if (word == "" || word.size() == 1)
                        {
                            out << tmp;
                        }
                        else
                        {
                            if ((word.size() > 1 && word.size() < 10 && tables_[word.size() - 2].in_table(word)) ||
                                (word.size() >= 10 && tables_[8].in_table(word)))
                            {
                                out << tmp;
                            }
                            else
                            {
                                for (size_t p = 0; p < it1; ++p)
                                {
                                    out << tmp[p];
                                }
                                out << find_best_word(word);
                                for (size_t p = it2 + 1; p < tmp.size(); ++p)
                                {
                                    out << tmp[p];
                                }
                            }
                        }
                        tmp = "";
                        was_space = true;
                        frst_word = false;
                    }
                }
                else
                {
                    was_space = false;
                    tmp += line[i];
                }
            }
            out << std::endl;
        }
    }
    in.close();
    out.close();
}