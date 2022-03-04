#ifndef TEXT_EDITOR_DICTIONARY
#define TEXT_EDITOR_DICTIONARY

#include "hash_table.hpp"

class Dictionary : public HashTable
{
  public:
    explicit Dictionary(size_t word_size = 0);
    void add_words(const std::string &path);
    void set_word_size(const size_t word_size);
    void get_best_word(std::string &ret, size_t &dist, size_t &freq, const std::string &word);

  private:
    size_t word_size_;
    std::string make_word_(const std::string &tmp);
    size_t dist_lev(const std::string &word1, const std::string &word2) const;
};

#endif // TEXT_EDITOR_DICTIONARY