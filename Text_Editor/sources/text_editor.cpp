#include "text_editor.hpp"

#include <thread>

TextEditor::TextEditor() : tables(new Dictionary[9])
{
    tables[0].set_word_size(1);
    tables[8].set_word_size(0);
    for (size_t i = 1; i < 8; ++i)
    {
        tables[i].set_word_size(i + 2);
    }
}

TextEditor::~TextEditor()
{
    delete[] tables;
}

void TextEditor::teach(const std::string &path)
{
    std::string tmp = "../texts/" + path;
    auto arr = new std::thread[9];
    for (size_t i = 0; i < 9; ++i)
    {
        arr[i] = std::thread(&Dictionary::add_words, &tables[i], std::ref(tmp));
    }
    for (size_t i = 0; i < 9; ++i)
    {
        arr[i].join();
    }
    delete[] arr;
}