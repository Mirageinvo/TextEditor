#include "text_editor.hpp"

#include <thread>
#include <fstream>
#include <cassert>

TextEditor::TextEditor() : tables(new Dictionary[9])
{
    tables[8].set_word_size(0);
    for (size_t i = 0; i < 8; ++i)
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
    std::string tmp = "../texts_for_teaching/" + path;
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

bool TextEditor::has_word(const std::string& word) const {
    if (word.size() <= 1) {
        return false;
    }
    if (word.size() >= 10) {
        return tables[8].in_table(word);
    }
    return tables[word.size() - 2].in_table(word);
}

void TextEditor::fix_mist(const std::string& path) {
    std::string tmp_in = "../texts_for_fixing/" + path;
    std::string tmp_out = "../fixed_texts/" + path;
    std::ifstream in;
    std::ofstream out;
    in.open(tmp_in);
    out.open(tmp_out);
    assert(in.is_open());
    assert(out.is_open());
    out << "qwe";
    in.close();
    out.close();
}