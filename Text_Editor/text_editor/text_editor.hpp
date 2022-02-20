#ifndef TEXT_EDITOR
#define TEXT_EDITOR

#include "../dictionary/dictionary.hpp"

class TextEditor {
public:
    TextEditor();
    ~TextEditor();
    void teach(const std::string& path);
private:
    Dictionary* tables;
};

#endif //TEXT_EDITOR