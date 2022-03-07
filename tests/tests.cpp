#include <fstream>
#include "text_editor.hpp"
#include "gtest/gtest.h"

const size_t kItsF = 1e3;
const size_t kItsS = 1e2;

TEST(HashTable, InTableTest)
{
    HashTable tmp;
    std::string s;
    for (size_t i = 0; i < kItsF; ++i) {
        s += static_cast<char>(static_cast<unsigned>('a') + (i % 26));
        ASSERT_FALSE(tmp.in_table(s));
    }
}

TEST(HashTable, AddTest)
{
    HashTable tmp;
    std::string s;
    for (size_t i = 0; i < kItsF; ++i) {
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
    for (size_t i = 0; i < kItsS; ++i) {
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
    std::string s, ret, path = "../../texts_for_teaching/test_texts/1.txt";
    std::vector<std::string> arr;
    tmp.add_words(path);
    std::ifstream in;
    in.open(path);
    assert(in.is_open());
    if (in.is_open())
    {
        while (!in.eof()) {
            in >> s;
            arr.push_back(s);
        }
        in.close();
    }
    for (size_t i = 0; i < arr.size(); ++i) {
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
    std::string s, path = "test_texts/1.txt";
    std::vector<std::string> arr;
    tmp.teach(path);
    std::ifstream in;
    in.open("../../texts_for_teaching/" + path);
    assert(in.is_open());
    if (in.is_open())
    {
        while (!in.eof()) {
            in >> s;
            arr.push_back(s);
        }
        in.close();
    }
    for (const auto& word : arr) {
        s = "";
        for (size_t j = 0; j < word.size() - 2; ++j) {
            s += word[j];
        }
        ASSERT_TRUE(word == tmp.find_best_word(s));
    }
}












int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}