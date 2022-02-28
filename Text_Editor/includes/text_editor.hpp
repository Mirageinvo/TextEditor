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
    bool has_word(const std::string &word) const;

  private:
    Dictionary *tables_;
    std::string cut_word(const std::string &tmp, size_t &it1, size_t &it2);
};

#endif // TEXT_EDITOR