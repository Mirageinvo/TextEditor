#include "text_editor.hpp"

#include <cassert>
#include <fstream>
#include <iostream>
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
    std::string tmp = "../texts_for_teaching/" + path;
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

std::string TextEditor::cut_word(const std::string &tmp, size_t &it1, size_t &it2)
{
    bool only_signs = true;
    std::string word = "";
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

void TextEditor::fix_mist(const std::string &path)
{
    bool was_space, frst_word;
    std::string word, tmp, line;
    std::ifstream in;
    std::ofstream out;
    in.open("../texts_for_fixing/" + path);
    out.open("../fixed_texts/" + path);
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
                    if (i == line.size() - 1) {
                        tmp += line[i];
                    }
                    if (!frst_word)
                    {
                        out << " ";
                    }
                    frst_word = false;
                    if (!was_space)
                    {
                        word = cut_word(tmp, it1, it2);
                        if (word == "" || word.size() == 1) {
                            out << tmp;
                        }
                        else {
                            if ((word.size() > 1 && word.size() < 10 && tables_[word.size() - 2].in_table(word)) || (word.size() >= 10 && tables_[8].in_table(word))) {
                                out << tmp;
                            }
                            else {
                                //find the best word with Levenstein and replace
                                //std::cout << word << std::endl;//////////////

                                out << "#####";
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