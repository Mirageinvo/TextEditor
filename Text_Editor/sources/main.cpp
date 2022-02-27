#include <iostream>

#include "text_editor.hpp"

int main()
{
    TextEditor el;
    el.teach("LoR_1.txt");
    el.fix_mist("test.txt");
    std::cout << "Good!!!" << std::endl;
    return 0;
}