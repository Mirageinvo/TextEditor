#include <iostream>

#include "text_editor.hpp"

int main()
{
    TextEditor el;
    el.teach("LoR_1.txt");
    std::cout << "Good_1!!!" << std::endl;
    el.fix_mist("test.txt");
    std::cout << "Good_2!!!" << std::endl;
    return 0;
}