#ifndef TEXT_EDITOR_HASH_TABLE
#define TEXT_EDITOR_HASH_TABLE

#include <string>
#include <vector>

template <typename T>
class HashTable {
   public:
    explicit HashTable(uint32_t capacity = initialSize_);
    ~HashTable();
    void add(const T& word, uint32_t number_of = numOf_);
    bool in_table(const T& word) const;

   private:
    static const uint32_t numOf_ = 1;
    static const uint32_t initialSize_ = 500000;
    uint32_t capacity_;
    std::pair<uint32_t, T>* hash_table_;
    uint32_t num_of_added_;
    uint64_t get_hash_(std::string word, int type, uint64_t mod) const;
    void hsh_resize_();
};

template <>
class HashTable<std::string> {
   public:
    explicit HashTable(uint32_t capacity = initialSize_);
    ~HashTable();
    void add(const std::string& word, uint32_t number_of = numOf_);
    bool in_table(const std::string& word) const;

   protected:
    uint32_t capacity_;
    std::pair<uint32_t, std::string>* hash_table_f_;
    std::pair<uint32_t, std::string>* hash_table_s_;

   private:
    static const uint32_t numOf_ = 1;
    static const uint32_t initialSize_ = 500000;
    uint32_t num_of_added_f_;
    uint32_t num_of_added_s_;
    uint64_t get_hash_(std::string word, int type, uint64_t mod) const;
    void hsh_resize_();
};

#endif  // TEXT_EDITOR_HASH_TABLE