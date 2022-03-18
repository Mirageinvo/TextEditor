#include "text_editor.hpp"

int main()
{
    TextEditor el;
    el.teach("LoR.txt");
    el.teach("LoR_1.txt");
    el.teach("LoR_2.txt");
    el.teach("LoR_3.txt");
    el.teach("Onegin.txt");

    el.fix_mist("test.txt");
    return 0;
}