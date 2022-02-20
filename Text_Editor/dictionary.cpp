#include <fstream>
#include "dictionary.hpp"

Dictionary::Dictionary(size_t word_size) : word_size_(word_size) {};

void Dictionary::make_word_(const std::string& tmp, std::string& word) {
    bool is_digit = true;
    bool only_signs = true;
    size_t it1, it2;
    for (size_t i = 0; i < tmp.size(); ++i) {
        if (static_cast<int>(tmp[i]) < static_cast<int>('0') || static_cast<int>(tmp[i]) > static_cast<int>('9')) {
            is_digit = false;
            break;
        }
    }
    if (is_digit) {
        word = "";
        return;
    }
    for (size_t i = 0; i < tmp.size(); ++i) {
        if (static_cast<int>(tmp[i]) >= static_cast<int>('a') && static_cast<int>(tmp[i]) <= static_cast<int>('z') ||
            static_cast<int>(tmp[i]) >= static_cast<int>('A') && static_cast<int>(tmp[i]) <= static_cast<int>('Z')) {
            only_signs = false;
            it1 = i;
            break;
        }
    }
    if (only_signs) {
        word = "";
        return;
    }
    for (int i = static_cast<int>(tmp.size()) - 1; i >= 0; --i) {
        if (static_cast<int>(tmp[i]) >= static_cast<int>('a') && static_cast<int>(tmp[i]) <= static_cast<int>('z') ||
            static_cast<int>(tmp[i]) >= static_cast<int>('A') && static_cast<int>(tmp[i]) <= static_cast<int>('Z')) {
            it2 = i;
            break;
        }
    }
    for (size_t i = it1; i <= it2; ++i) {
        word += tmp[i];
    }
}

void Dictionary::add_words(const std::string& path) {
    std::string tmp, word;
    std::ifstream file(path);
    if (file.is_open()) {
        while (file.eof()) {
            file >> tmp;
            make_word_(tmp, word);
            if (word.size() == word_size_) {
                add(word);
            }
        }
    }
    file.close();
}