#ifndef TEXT_EDITOR_DICTIONARY
#define TEXT_EDITOR_DICTIONARY

#include "hash_table.hpp"

class Dictionary final : public HashTable<std::string> {
   public:
    explicit Dictionary(uint32_t word_size = 0);
    void add_words(const std::string &path);
    void set_word_size(const uint32_t word_size);
    void get_best_word(std::string &ret, uint32_t &dist, uint32_t &freq, const std::string &word);
    static uint32_t dist_lev(const std::string &word1, const std::string &word2);

   private:
    uint32_t word_size_;
    static std::string make_word_(const std::string &tmp);
};

#endif  // TEXT_EDITOR_DICTIONARY