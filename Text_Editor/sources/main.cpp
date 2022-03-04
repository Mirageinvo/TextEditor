#include <iostream>

#include "text_editor.hpp"

int main()
{
    TextEditor el;
    el.teach("Onegin.txt");
    el.fix_mist("test.txt");
    return 0;
}