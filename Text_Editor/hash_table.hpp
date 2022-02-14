#ifndef TEXT_EDITOR_HASH_TABLE
#define TEXT_EDITOR_HASH_TABLE

#include <vector>
#include <string>

class HashTable {
public:
    HashTable();
    ~HashTable() {};

    void add(std::string word);

private:
    size_t num_of_added_f_;
    size_t num_of_added_s_;
    double fill_factor_f_;
    double fill_factor_s_;
    std::vector<std::pair<int, std::string>> hash_table_f_;
    std::vector<std::pair<int, std::string>> hash_table_s_;
    unsigned long long get_hash(std::string word, int type);
    void hsh_resize();
};








#endif //TEXT_EDITOR_HASH_TABLE