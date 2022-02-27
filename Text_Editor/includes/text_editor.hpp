#ifndef TEXT_EDITOR
#define TEXT_EDITOR

#include "dictionary.hpp"

class TextEditor
{
  public:
    TextEditor();
    ~TextEditor();
    void teach(const std::string &path);
    void fix_mist(const std::string& path);
    bool has_word(const std::string& word) const;

  private:
    Dictionary *tables;
};

#endif // TEXT_EDITOR