#ifndef TEXT_EDITOR_DICTIONARY
#define TEXT_EDITOR_DICTIONARY

#include "hash_table.hpp"

class Dictionary : public HashTable {
public:
    Dictionary(size_t word_size);
    void add_words(const std::string& path);
private:
    size_t word_size_;
    void make_word_(const std::string& tmp, std::string& word);
};








#endif //TEXT_EDITOR_DICTIONARY