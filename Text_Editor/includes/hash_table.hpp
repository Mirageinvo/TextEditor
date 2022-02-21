#ifndef TEXT_EDITOR_HASH_TABLE
#define TEXT_EDITOR_HASH_TABLE

#include <vector>
#include <string>

class HashTable {
public:
    explicit HashTable(size_t capacity = 500000);
    ~HashTable();
    void add(const std::string& word, unsigned number_of = 1);
    bool in_table(const std::string& word) const;

private:
    size_t capacity_;
    size_t num_of_added_f_;
    size_t num_of_added_s_;
    std::pair<unsigned, std::string>* hash_table_f_;
    std::pair<unsigned, std::string>* hash_table_s_;
    uint64_t get_hash_(std::string word, int type, uint64_t mod) const;
    void hsh_resize_();
};








#endif //TEXT_EDITOR_HASH_TABLE