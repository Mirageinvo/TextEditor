#include "dictionary.hpp"

#include <cassert>
#include <fstream>

Dictionary::Dictionary(size_t word_size) : word_size_(word_size){};

std::string Dictionary::make_word_(const std::string &tmp)
{
    bool only_signs = true;
    std::string word = "";
    size_t it1 = 0, it2 = 0;
    for (size_t i = 0; i < tmp.size(); ++i)
    {
        if (static_cast<int>(tmp[i]) >= static_cast<int>('a') && static_cast<int>(tmp[i]) <= static_cast<int>('z') ||
            static_cast<int>(tmp[i]) >= static_cast<int>('A') && static_cast<int>(tmp[i]) <= static_cast<int>('Z'))
        {
            only_signs = false;
            it1 = i;
            break;
        }
    }
    if (only_signs)
    {
        return "";
    }
    for (int i = static_cast<int>(tmp.size()) - 1; i >= 0; --i)
    {
        if (static_cast<int>(tmp[i]) >= static_cast<int>('a') && static_cast<int>(tmp[i]) <= static_cast<int>('z') ||
            static_cast<int>(tmp[i]) >= static_cast<int>('A') && static_cast<int>(tmp[i]) <= static_cast<int>('Z'))
        {
            it2 = static_cast<size_t>(i);
            break;
        }
    }
    for (size_t i = it1; i <= it2; ++i)
    {
        word += tmp[i];
    }
    return word.size() > 1u ? word : "";
}

void Dictionary::set_word_size(const size_t word_size)
{
    word_size_ = word_size;
}

size_t Dictionary::dist_lev(const std::string &word1, const std::string &word2) const
{
    std::vector<std::vector<size_t>> dp(word1.size() + 1, std::vector<size_t>(word2.size() + 1));
    for (size_t i = 0; i <= word1.size(); ++i)
    {
        dp[i][0] = i;
    }
    for (size_t i = 0; i <= word2.size(); ++i)
    {
        dp[0][i] = i;
    }
    for (size_t i = 1; i <= word1.size(); ++i)
    {
        for (size_t j = 1; j <= word2.size(); ++j)
        {
            dp[i][j] = std::min(dp[i][j - 1] + 1,
                                std::min(dp[i - 1][j] + 1, dp[i - 1][j - 1] + (word1[i - 1] == word2[j - 1] ? 0 : 1)));
        }
    }
    return dp[word1.size()][word2.size()];
}

void Dictionary::add_words(const std::string &path)
{
    std::string tmp, word;
    std::ifstream in;
    in.open(path);
    assert(in.is_open());
    if (in.is_open())
    {
        while (!in.eof())
        {
            in >> tmp;
            word = make_word_(tmp);
            if ((word.size() > 1 && word.size() < 10 && word.size() == word_size_) ||
                (word.size() >= 10 && word_size_ == 0))
            {
                add(word);
            }
        }
        in.close();
    }
}

void Dictionary::get_best_word(std::string &ret, size_t &dist, size_t &freq, const std::string &word)
{
    size_t tmp;
    for (size_t i = 0; i < capacity_; ++i)
    {
        if (hash_table_f_[i].first != 0)
        {
            tmp = dist_lev(word, hash_table_f_[i].second);
            if (tmp < dist || (tmp == dist && hash_table_f_[i].first > freq))
            {
                ret = hash_table_f_[i].second;
                dist = tmp;
                freq = hash_table_f_[i].first;
            }
        }
        if (hash_table_s_[i].first != 0)
        {
            tmp = dist_lev(word, hash_table_s_[i].second);
            if (tmp < dist || (tmp == dist && hash_table_s_[i].first > freq))
            {
                ret = hash_table_s_[i].second;
                dist = tmp;
                freq = hash_table_s_[i].first;
            }
        }
    }
}