#include <thread>
#include "text_editor.hpp"

TextEditor::TextEditor() : tables(new Dictionary[9]) {
    tables[0].set_word_size(1);
    tables[8].set_word_size(0);
    for (size_t i = 1; i < 8; ++i) {
        tables[i].set_word_size(i + 2);
    }
}

TextEditor::~TextEditor() {
    delete[] tables;
}

void TextEditor::teach(const std::string& path) {
    std::thread thrd1(&Dictionary::add_words, &tables[0], std::ref(path));
    std::thread thrd2(&Dictionary::add_words, &tables[1], std::ref(path));
    std::thread thrd3(&Dictionary::add_words, &tables[2], std::ref(path));
    std::thread thrd4(&Dictionary::add_words, &tables[3], std::ref(path));
    std::thread thrd5(&Dictionary::add_words, &tables[4], std::ref(path));
    std::thread thrd6(&Dictionary::add_words, &tables[5], std::ref(path));
    std::thread thrd7(&Dictionary::add_words, &tables[6], std::ref(path));
    std::thread thrd8(&Dictionary::add_words, &tables[7], std::ref(path));
    std::thread thrd9(&Dictionary::add_words, &tables[8], std::ref(path));

    thrd1.join();
    thrd2.join();
    thrd3.join();
    thrd4.join();
    thrd5.join();
    thrd6.join();
    thrd7.join();
    thrd8.join();
    thrd9.join();
}