#include "text_editor.hpp"
#include "gtest/gtest.h"
#include <fstream>

const size_t kItsF = 1e3;
const size_t kItsS = 1e2;

TEST(HashTable, InTableTest)
{
    HashTable tmp;
    std::string s;
    for (size_t i = 0; i < kItsF; ++i)
    {
        s += static_cast<char>(static_cast<unsigned>('a') + (i % 26));
        ASSERT_FALSE(tmp.in_table(s));
    }
}

TEST(HashTable, AddTest)
{
    HashTable tmp;
    std::string s;
    for (size_t i = 0; i < kItsF; ++i)
    {
        s += static_cast<char>(static_cast<unsigned>('a') + (i % 26));
        tmp.add(s);
        ASSERT_TRUE(tmp.in_table(s));
    }
}

TEST(Dictionary, GetBestWordTest)
{
    Dictionary tmp;
    size_t dist, freq;
    std::string s, ret;
    for (size_t i = 0; i < kItsS; ++i)
    {
        dist = 1e9;
        freq = 0;
        s += static_cast<char>(static_cast<unsigned>('a') + (i % 26));
        tmp.add(s);
        ASSERT_TRUE(tmp.in_table(s));
        tmp.get_best_word(ret, dist, freq, s);
        ASSERT_TRUE(s == ret);
    }
}

TEST(Dictionary, AddWordsTest)
{
    Dictionary tmp;
    size_t dist, freq;
    std::string s, ret, path = "../../texts_for_teaching/test_text/0.txt";
    std::vector<std::string> arr;
    tmp.add_words(path);
    std::ifstream in;
    in.open(path);
    ASSERT_TRUE(in.is_open());
    if (in.is_open())
    {
        while (!in.eof())
        {
            in >> s;
            arr.push_back(s);
        }
        in.close();
    }
    for (size_t i = 0; i < arr.size(); ++i)
    {
        dist = 1e9;
        freq = 0;
        ASSERT_TRUE(tmp.in_table(s));
        tmp.get_best_word(ret, dist, freq, s);
        ASSERT_TRUE(s == ret);
    }
}

TEST(TextEditor, FindBestWordTest)
{
    TextEditor tmp;
    std::string s, path = "test_text/0.txt";
    std::vector<std::string> arr;
    tmp.teach(path);
    std::ifstream in;
    in.open("../../texts_for_teaching/" + path);
    ASSERT_TRUE(in.is_open());
    if (in.is_open())
    {
        while (!in.eof())
        {
            in >> s;
            arr.push_back(s);
        }
        in.close();
    }
    for (const auto &word : arr)
    {
        s = "";
        for (size_t j = 0; j < word.size() - 2; ++j)
        {
            s += word[j];
        }
        ASSERT_TRUE(word == tmp.find_best_word(s));
    }
}

TEST(TextEditor, EndToEndTestFirst)
{
    TextEditor tmp;
    std::string sf, ss;
    tmp.teach("LoR.txt");
    tmp.teach("LoR_1.txt");
    tmp.teach("LoR_2.txt");
    tmp.teach("LoR_3.txt");
    tmp.teach("Onegin.txt");
    tmp.fix_mist("test_texts/1.txt");
    std::ifstream in, in_ans;
    in.open("../../fixed_texts/test_texts/1.txt");
    in_ans.open("../../fixed_texts/test_texts/1_ans.txt");
    assert(in.is_open());
    assert(in_ans.is_open());
    if (in.is_open() && in_ans.is_open())
    {
        while (!in.eof() && !in_ans.eof())
        {
            std::getline(in, sf);
            std::getline(in_ans, ss);
            ASSERT_TRUE(sf == ss);
        }
        ASSERT_TRUE(in.eof() && in_ans.eof());
        in.close();
        in_ans.close();
    }
    ASSERT_TRUE(remove("../../fixed_texts/test_texts/1.txt") == 0);
}

TEST(TextEditor, EndToEndTestSecond)
{
    TextEditor tmp;
    std::string sf, ss;
    tmp.teach("LoR.txt");
    tmp.teach("LoR_1.txt");
    tmp.teach("LoR_2.txt");
    tmp.teach("LoR_3.txt");
    tmp.teach("Onegin.txt");
    tmp.fix_mist("test_texts/2.txt");
    std::ifstream in, in_ans;
    in.open("../../fixed_texts/test_texts/2.txt");
    in_ans.open("../../fixed_texts/test_texts/2_ans.txt");
    assert(in.is_open());
    assert(in_ans.is_open());
    if (in.is_open() && in_ans.is_open())
    {
        while (!in.eof() && !in_ans.eof())
        {
            std::getline(in, sf);
            std::getline(in_ans, ss);
            ASSERT_TRUE(sf == ss);
        }
        ASSERT_TRUE(in.eof() && in_ans.eof());
        in.close();
        in_ans.close();
    }
    ASSERT_TRUE(remove("../../fixed_texts/test_texts/2.txt") == 0);
}

TEST(TextEditor, EndToEndTestThird)
{
    TextEditor tmp;
    std::string sf, ss;
    tmp.teach("LoR.txt");
    tmp.teach("LoR_1.txt");
    tmp.teach("LoR_2.txt");
    tmp.teach("LoR_3.txt");
    tmp.teach("Onegin.txt");
    tmp.fix_mist("test_texts/3.txt");
    std::ifstream in, in_ans;
    in.open("../../fixed_texts/test_texts/3.txt");
    in_ans.open("../../fixed_texts/test_texts/3_ans.txt");
    assert(in.is_open());
    assert(in_ans.is_open());
    if (in.is_open() && in_ans.is_open())
    {
        while (!in.eof() && !in_ans.eof())
        {
            std::getline(in, sf);
            std::getline(in_ans, ss);
            ASSERT_TRUE(sf == ss);
        }
        ASSERT_TRUE(in.eof() && in_ans.eof());
        in.close();
        in_ans.close();
    }
    ASSERT_TRUE(remove("../../fixed_texts/test_texts/3.txt") == 0);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}