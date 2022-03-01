#ifndef TEXT_EDITOR
#define TEXT_EDITOR

#include "dictionary.hpp"

class TextEditor
{
  public:
    TextEditor();
    ~TextEditor();
    void teach(const std::string &path);
    void fix_mist(const std::string &path);
    size_t find_min_dist(const std::string& word);

  private:
    Dictionary *tables_;
    std::string cut_word_(const std::string &tmp, size_t &it1, size_t &it2);
    size_t dist_lev(const std::string& word1, const std::string& word2) const;
};

#endif // TEXT_EDITOR