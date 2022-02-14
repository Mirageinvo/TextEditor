#ifndef TEXT_EDITOR_HASH_TABLE_IMPL
#define TEXT_EDITOR_HASH_TABLE_IMPL

#include "hash_table.hpp"

HashTable::HashTable() : num_of_added_f_(0), num_of_added_s_(0), fill_factor_f_(0.0), fill_factor_s_(0.0) {
    hash_table_f_.resize(500000, {0, ""});
    hash_table_s_.resize(500000, {0, ""});
}

unsigned long long HashTable::get_hash(std::string word, int type) {
    unsigned long long hash = static_cast<int>(word[0]) >= static_cast<int>('a') ? static_cast<unsigned long long>(word[0]) - static_cast<unsigned long long>('a') :
                                                                                   static_cast<unsigned long long>(word[0]) - static_cast<unsigned long long>('A');
    unsigned long long mult = (type == 1 ? 1697 : 3833);
    unsigned long long p = mult;
    unsigned long long mod = hash_table_f_.size();
    int word_type;
    if (static_cast<int>(word[0]) >= static_cast<int>('a') && static_cast<int>(word[0]) <= static_cast<int>('z')) {
        word_type = 0;
    }
    else if (static_cast<int>(word[0]) >= static_cast<int>('A') && static_cast<int>(word[0]) <= static_cast<int>('Z') && 
             static_cast<int>(word[word.size() - 1]) >= static_cast<int>('A') && static_cast<int>(word[word.size() - 1]) <= static_cast<int>('Z')) {
        word_type = 1;
    }
    else {
        word_type = 0;
    }

    if (word_type == 0) {
        for (size_t i = 1; i < word.size(); ++i) {
            hash = (hash + ((static_cast<unsigned long long>(word[i]) - static_cast<unsigned long long>('a')) * p)) % mod;
            p = (p * mult) % mod;
        }
    }
    else if (word_type == 1) {
        for (size_t i = 1; i < word.size(); ++i) {
            hash = (hash + ((static_cast<unsigned long long>(word[i]) - static_cast<unsigned long long>('A')) * p)) % mod;
            p = (p * mult) % mod;
        }
    }

    return hash;
}

void HashTable::add(std::string word) {
    unsigned long long hash1 = get_hash(word, 1);
    if (hash_table_f_[hash1].second == "") {
        hash_table_f_[hash1].first == 1;
        hash_table_f_[hash1].second == word;
        //check fill factor!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }
    else if (hash_table_f_[hash1].second == word) {
        hash_table_f_[hash1].first++;
        //check fill factor!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }
    else {
        
    }
}

#endif //TEXT_EDITOR_HASH_TABLE_IMPL