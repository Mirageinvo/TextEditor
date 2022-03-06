#include "text_editor.hpp"
#include "gtest/gtest.h"

TEST(TextEditor, Test)
{
    TextEditor tmp;
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}