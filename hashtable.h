#ifndef UNTITLED1_HASHTABLE_H
#define UNTITLED1_HASHTABLE_H

#include "value.h"

class HashTable {
public:
    HashTable();

    ~HashTable();

    //Copy other hashtable
    HashTable(const HashTable& b);

    // Return copy other hashtable
    HashTable& operator=(const HashTable& b);

    // Swap this and other hashtable
    void swap(HashTable& b);

    // Delete all elements from hashtable
    void clear();

    // Delete element with passed key
    // Return true if element is find else false
    bool erase(const Key& k);

    // Return true if element is find else false
    bool contains(const Key& k) const;

    // Add new element with passed key and value and return true
    // Chang value if element with passed key exist and return false
    bool insert(const Key& k, const Value& v);

    // Find element with passed key and return element value
    // Add new element with passed key if element not find
    Value& operator[](const Key& k);

    // Find element with passed key and return element value
    // Throw out_of_range if element not find
    Value& at(const Key& k);
    const Value& at(const Key& k) const;

    // Return number of table elements
    size_t size() const;

    // Return whether hashtable is empty
    bool empty() const;

    // Return result comparison two hashtable by keys and values
    friend bool operator==(const HashTable& a, const HashTable& b);
    friend bool operator!=(const HashTable& a, const HashTable& b);
private:
    struct List {
        List(Key  k,Value  v): key(std::move(k)), value(std::move(v)) {}

        Key key;
        Value value;
        List *next = nullptr;
    };

    const int PRIME = 7;
    const int DEFAULT_CAPACITY = 8;

    size_t capacity_;
    size_t size_;
    List **data;

    unsigned long hash_func(const Key& k) const;
    void resize();
    const Value& at_const(const Key& k) const;
    void copy(const HashTable& b);
    List* find(const Key & k) const;
    List* add_list(const Key& k, const Value& v);

};

#endif
