#include "dictionary.hpp"

#include <cassert>
#include <fstream>

Dictionary::Dictionary(uint32_t word_size) : word_size_(word_size) {}

std::string Dictionary::make_word_(const std::string &tmp) {
    bool only_signs = true;
    std::string word;
    uint32_t it1 = 0;
    uint32_t it2 = 0;
    for (uint32_t i = 0; i < tmp.size(); ++i) {
        if ((static_cast<uint32_t>(tmp[i]) >= static_cast<uint32_t>('a') &&
             static_cast<uint32_t>(tmp[i]) <= static_cast<uint32_t>('z')) ||
            (static_cast<uint32_t>(tmp[i]) >= static_cast<uint32_t>('A') &&
             static_cast<uint32_t>(tmp[i]) <= static_cast<uint32_t>('Z'))) {
            only_signs = false;
            it1 = i;
            break;
        }
    }
    if (only_signs) {
        return "";
    }
    for (int i = static_cast<int>(tmp.size()) - 1; i >= 0; --i) {
        if ((static_cast<uint32_t>(tmp[static_cast<uint32_t>(i)]) >= static_cast<uint32_t>('a') &&
             static_cast<uint32_t>(tmp[static_cast<uint32_t>(i)]) <= static_cast<uint32_t>('z')) ||
            (static_cast<uint32_t>(tmp[static_cast<uint32_t>(i)]) >= static_cast<uint32_t>('A') &&
             static_cast<uint32_t>(tmp[static_cast<uint32_t>(i)]) <= static_cast<uint32_t>('Z'))) {
            it2 = static_cast<uint32_t>(i);
            break;
        }
    }
    for (uint32_t i = it1; i <= it2; ++i) {
        word += tmp[i];
    }
    return word.size() > 1U ? word : "";
}

void Dictionary::set_word_size(const uint32_t word_size) { word_size_ = word_size; }

uint32_t Dictionary::dist_lev(const std::string &word1, const std::string &word2) {
    std::vector<std::vector<uint32_t>> dp(word1.size() + 1,
                                          std::vector<uint32_t>(word2.size() + 1));
    for (uint32_t i = 0; i <= word1.size(); ++i) {
        dp[i][0] = i;
    }
    for (uint32_t i = 0; i <= word2.size(); ++i) {
        dp[0][i] = i;
    }
    for (uint32_t i = 1; i <= word1.size(); ++i) {
        for (uint32_t j = 1; j <= word2.size(); ++j) {
            dp[i][j] =
                std::min(dp[i][j - 1] + 1,
                         std::min(dp[i - 1][j] + 1,
                                  dp[i - 1][j - 1] + (word1[i - 1] == word2[j - 1] ? 0 : 1)));
        }
    }
    return dp[word1.size()][word2.size()];
}

void Dictionary::add_words(const std::string &path) {
    const size_t min_word_size = 1;
    const size_t max_word_size = 10;
    std::string tmp;
    std::string word;
    std::ifstream in;
    in.open(path);
    assert(in.is_open());
    if (in.is_open()) {
        while (!in.eof()) {
            in >> tmp;
            word = make_word_(tmp);
            if ((word.size() > min_word_size && word.size() < max_word_size && word.size() == word_size_) ||
                (word.size() >= max_word_size && word_size_ == 0)) {
                add(word);
            }
        }
        in.close();
    }
}

void Dictionary::get_best_word(std::string &ret, uint32_t &dist, uint32_t &freq,
                               const std::string &word) {
    uint32_t tmp;
    for (uint32_t i = 0; i < capacity_; ++i) {
        if (hash_table_f_[i].first != 0) {
            tmp = dist_lev(word, hash_table_f_[i].second);
            if (tmp < dist || (tmp == dist && hash_table_f_[i].first > freq)) {
                ret = hash_table_f_[i].second;
                dist = tmp;
                freq = hash_table_f_[i].first;
            }
        }
        if (hash_table_s_[i].first != 0) {
            tmp = dist_lev(word, hash_table_s_[i].second);
            if (tmp < dist || (tmp == dist && hash_table_s_[i].first > freq)) {
                ret = hash_table_s_[i].second;
                dist = tmp;
                freq = hash_table_s_[i].first;
            }
        }
    }
}