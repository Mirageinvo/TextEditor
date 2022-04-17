#ifndef TEXT_EDITOR
#define TEXT_EDITOR

#include "dictionary.hpp"

class TextEditor final {
   public:
    TextEditor();
    ~TextEditor();
    void teach(const std::string &path);
    void fix_mist(const std::string &path);

   private:
    Dictionary *tables_;
    std::string find_best_word_(const std::string &word) const;
    std::string cut_word_(const std::string &tmp, uint32_t &it1, uint32_t &it2);
};

#endif  // TEXT_EDITOR