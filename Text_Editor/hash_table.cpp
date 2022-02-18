#ifndef TEXT_EDITOR_HASH_TABLE_IMPL
#define TEXT_EDITOR_HASH_TABLE_IMPL

#include <cmath>
#include "hash_table.hpp"

HashTable::HashTable() : num_of_added_f_(0), num_of_added_s_(0), capacity_(1000000) {
    hash_table_f_ = new std::pair<unsigned, std::string>[1000000];
    hash_table_s_ = new std::pair<unsigned, std::string>[1000000];
    for (size_t i = 0; i < 1000000; ++i) {
        hash_table_f_[i] = std::make_pair(0, "");
        hash_table_f_[i] = std::make_pair(0, "");
    }
}

HashTable::~HashTable() {
    delete[] hash_table_f_;
    delete[] hash_table_s_;
}

uint64_t HashTable::get_hash(std::string word, int type, uint64_t mod) {
    uint64_t hash = static_cast<int>(word[0]) >= static_cast<int>('a') ? static_cast<uint64_t>(word[0]) - static_cast<uint64_t>('a') :
                                                                                   static_cast<uint64_t>(word[0]) - static_cast<uint64_t>('A');
    uint64_t mult = (type == 1 ? 1697 : 3833);
    uint64_t p = mult;
    int word_type;
    if (static_cast<int>(word[0]) >= static_cast<int>('A') && static_cast<int>(word[0]) <= static_cast<int>('Z') && 
             static_cast<int>(word[word.size() - 1]) >= static_cast<int>('A') && static_cast<int>(word[word.size() - 1]) <= static_cast<int>('Z')) {
        word_type = 1;
    }
    else {
        word_type = 0;
    }

    if (word_type == 0) {
        for (size_t i = 1; i < word.size(); ++i) {
            hash = (hash + ((static_cast<uint64_t>(word[i]) - static_cast<uint64_t>('a')) * p)) % mod;
            p = (p * mult) % mod;
        }
    }
    else if (word_type == 1) {
        for (size_t i = 1; i < word.size(); ++i) {
            hash = (hash + ((static_cast<uint64_t>(word[i]) - static_cast<uint64_t>('A')) * p)) % mod;
            p = (p * mult) % mod;
        }
    }

    return hash;
}

void HashTable::hsh_resize() {
    capacity_ *= 2;
    num_of_added_f_ = 0;
    num_of_added_s_ = 0;
    auto* hash_table_f_nw = new std::pair<unsigned, std::string>[capacity_];
    auto* hash_table_s_nw = new std::pair<unsigned, std::string>[capacity_];
    for (size_t i = 0; i < capacity_; ++i) {
        hash_table_f_nw[i] = std::make_pair(0, "");
        hash_table_s_nw[i] = std::make_pair(0, "");
    }
    std::swap(hash_table_f_, hash_table_f_nw);
    std::swap(hash_table_s_, hash_table_s_nw);
    for (size_t i = 0; i * 2 < capacity_; ++i) {
        if (!hash_table_f_nw[i].second.empty()) {
            add(hash_table_f_nw[i].second, hash_table_f_nw[i].first);
        }
        if (!hash_table_s_nw[i].second.empty()) {
            add(hash_table_s_nw[i].second, hash_table_s_nw[i].first);
        }
    }
}

void HashTable::add(const std::string& word, unsigned number_of) {
    unsigned count = 0;
    uint64_t hsh;
    uint64_t hash1 = get_hash(word, 1, capacity_);
    uint64_t hash2 = get_hash(word, 2, capacity_);
    if (!hash_table_f_[hash1].second.empty() && hash_table_f_[hash1].second != word &&
        !hash_table_s_[hash2].second.empty() && hash_table_s_[hash2].second != word)
    {
        int table = 2;
        std::pair<unsigned, std::string> tmp = hash_table_f_[hash1];
        hash_table_f_[hash1].second = word;
        hash_table_f_[hash1].first = 1;
        while (true) {
            hsh = get_hash(tmp.second, table, capacity_);
            if (table == 1) {
                if (!hash_table_f_[hsh].second.empty()) {
                    std::swap(hash_table_f_[hsh], tmp);
                }
                else {
                    hash_table_f_[hsh] = tmp;
                    num_of_added_f_ += number_of;
                    break;
                }
            }
            else {
                if (!hash_table_s_[hsh].second.empty()) {
                    std::swap(hash_table_s_[hsh], tmp);
                }
                else {
                    hash_table_s_[hsh] = tmp;
                    num_of_added_s_ += number_of;
                    break;
                }
            }
            table = 3 - table;
            count++;
            if (count > static_cast<unsigned>(log(capacity_) / log(1.5))) { break; }
        }
    }
    else {
        if (hash_table_f_[hash1].second.empty()) {
            hash_table_f_[hash1].first = 1;
            hash_table_f_[hash1].second = word;
            num_of_added_f_++;
        }
        else if (hash_table_f_[hash1].second == word) {
            hash_table_f_[hash1].first++;
        }
        else if (hash_table_s_[hash2].second.empty()) {
            hash_table_s_[hash2].first = 1;
            hash_table_s_[hash2].second = word;
            num_of_added_s_++;
        }
        else if (hash_table_s_[hash2].second == word) {
            hash_table_s_[hash2].first++;
        }
    }

    if (static_cast<double>(num_of_added_f_) / static_cast<double>(capacity_) > 0.4 ||
        static_cast<double>(num_of_added_s_) / static_cast<double>(capacity_) > 0.4) {
            hsh_resize();
    }
}

#endif //TEXT_EDITOR_HASH_TABLE_IMPL