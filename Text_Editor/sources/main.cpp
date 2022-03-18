#include "text_editor.hpp"
#include <iostream>

int main()
{
    std::string filename;
    TextEditor el;
    el.teach("LoR.txt");
    el.teach("LoR_1.txt");
    el.teach("LoR_2.txt");
    el.teach("LoR_3.txt");
    el.teach("Onegin.txt");

    std::cout << "Insert name of the file: ";
    std::cin >> filename;
    try
    {
        el.fix_mist(filename);
    }
    catch (int i)
    {
        std::cout << "Unknown filename" << std::endl;
    }
    return 0;
}