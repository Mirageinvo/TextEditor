#ifndef TEXT_EDITOR_HASH_TABLE
#define TEXT_EDITOR_HASH_TABLE

#include <vector>
#include <string>

class HashTable {
public:
    HashTable();
    ~HashTable();

    void add(const std::string& word, unsigned number_of = 1);

private:
    size_t num_of_added_f_;
    size_t num_of_added_s_;
    size_t capacity_;
    std::pair<unsigned, std::string>* hash_table_f_;
    std::pair<unsigned, std::string>* hash_table_s_;
    uint64_t get_hash(std::string word, int type, uint64_t mod);
    void hsh_resize();
};








#endif //TEXT_EDITOR_HASH_TABLE