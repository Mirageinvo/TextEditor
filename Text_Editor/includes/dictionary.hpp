#ifndef TEXT_EDITOR_DICTIONARY
#define TEXT_EDITOR_DICTIONARY

#include "hash_table.hpp"

class Dictionary : public HashTable
{
  public:
    explicit Dictionary(size_t word_size = 0);
    void add_words(const std::string &path);
    void set_word_size(const size_t word_size);

  private:
    size_t word_size_;
    std::string make_word_(const std::string& tmp);
};

#endif // TEXT_EDITOR_DICTIONARY