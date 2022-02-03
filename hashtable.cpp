#include <iostream>
#include <algorithm>
#include "hashtable.h"

HashTable::HashTable() : data(new List*[DEFAULT_CAPACITY]()), capacity_(HashTable::DEFAULT_CAPACITY), size_(0){}

HashTable::~HashTable(){
    clear();
    delete[] data;
}

void HashTable::copy(const HashTable &b) {
    for (int i = 0; i < b.capacity_; i++) {
        if (b.data[i]) {
            for (List *tmp = b.data[i]; tmp; tmp = tmp->next) {
                add_list(tmp->key, tmp->value);
            }
        }
    }
}

HashTable::HashTable(const HashTable& b) : capacity_(b.capacity_), data(new List*[capacity_]()), size_(){
    copy(b);
}

HashTable& HashTable::operator=(const HashTable& b) {
    if (this != &b) {
        clear();
        capacity_ = b.capacity_;
        delete [] data;
        data = new List*[capacity_]();
        copy(b);
    }
    return *this;
}

unsigned long HashTable::hash_func( const Key& k) const {
    size_t len = k.length();
    unsigned res = 0;
    for (int i = 0; i < len; i++) {
        res += (res * PRIME) + k[i];
    }

    return res % capacity_;
}

// Return element with passed key or last element of list
HashTable::List* HashTable::find(const Key & k) const {
    unsigned long hash = hash_func(k);

    List* tmp = data[hash];
    List* prev;

    while (tmp != nullptr) {
        prev = tmp;
        if (tmp->key == k)
            return tmp;
        tmp = tmp->next;
    }

    return prev;
}

bool HashTable::erase(const Key& k){
    if (data[hash_func(k)] == nullptr)
        return false;

    List* tmp = find(k);

    if (tmp->key == k) {
        List* tmp_next = tmp->next;
        if (tmp_next != nullptr) {
            std::swap(tmp, tmp_next);
            tmp_next = nullptr;
            delete tmp_next;
            size_--;
            return true;
        }
        size_--;
        delete data[hash_func(k)];
        data[hash_func(k)] = nullptr;
        return true;
    }
    return false;
}

// Return element with passed key
// Add new element with passed key and value if element not find
HashTable::List* HashTable::add_list(const Key &k, const Value &v) {
    if (size_ >= capacity_ * 3 / 4)
        resize();

    unsigned long hash = hash_func(k);

    if (data[hash] == nullptr) {
        data[hash] = new List(k, v);
        size_++;
        return data[hash];
    }

    List *tmp = find(k);
    if (tmp->key != k) {
        tmp->next = new List(k, v);
        size_++;
        return tmp;
    }

    return tmp;
}

bool HashTable::insert(const Key& k, const Value& v){
    List* tmp = add_list(k, v);
    if (tmp->value != v) {
        tmp->value = v;
        return false;
    }

    return true;
}

Value& HashTable::operator[](const Key& k){
    return add_list(k, Value())->value;
}

void HashTable::swap(HashTable& b){
    std::swap(size_, b.size_);
    std::swap(capacity_, b.capacity_);
    std::swap(data, b.data);
}

void HashTable::clear(){
    for (int i = 0; i < capacity_; i++){
        if (data[i]) {
            while (data[i] != nullptr) {
                List* tmp = data[i]->next;
                delete data[i];
                data[i] = tmp;
            }
        }
    }
    size_ = 0;
}

bool HashTable::contains(const Key& k) const{
    if (!data[hash_func(k)])
        return false;

    List* g = find(k);

    if (g->key != k)
        return false;

    return true;
}

const Value& HashTable::at_const(const Key& k) const {
    unsigned long hash = hash_func(k);

    if (!data[hash])
        throw std::out_of_range("out_of_range");

    List* tmp = find(k);

    if (tmp->key != k)
        throw std::out_of_range("out_of_range");

    return tmp->value;
}

Value& HashTable::at(const Key& k){
    return const_cast<Value&>(at_const(k));
}

const Value& HashTable::at(const Key& k) const{
    return at_const(k);
}

size_t HashTable::size() const{
    return size_;
}

bool HashTable::empty() const{
    return size_ == 0;
}

void HashTable::resize() {
    /*HashTable other;
    std::swap(other, *this);
    delete[] data;
    capacity_ = capacity_ * 2;
    data = new List*[capacity_]();
    copy(other);*/
    List** other_data = new List*[capacity_ * 2]();
    std::swap(other_data, data);
    size_t other_capacity = capacity_;
    capacity_ *= 2;
    size_t other_size = size_;
    size_ = 0;
    List* tmp;

    for (int i = 0; i < other_capacity; ++i) {
        if (other_size == 0)
            break;

        if (!other_data[i])
            continue;

        while (other_data[i] != nullptr) {
            other_size--;
            add_list(other_data[i]->key, other_data[i]->value);
            tmp = other_data[i]->next;
            other_data[i]->next = nullptr;
            delete other_data[i];
            other_data[i] = tmp;
        }
    }
    delete [] other_data;
}

bool operator==(const HashTable& a, const HashTable& b){
    if (a.size() != b.size())
        return false;

    HashTable::List* a_list;
    HashTable::List* b_list;

    for (int i = 0; i < a.capacity_; ++i) {
        a_list = a.data[i];

        while (a_list != nullptr) {
            if (b.data[b.hash_func(a_list->key)] == nullptr)
                return false;

            b_list = b.find(a_list->key);

            if (b_list->key != a_list->key || a_list->value != b_list->value)
                return false;
            a_list = a_list->next;
        }
    }
    return true;
}

bool operator!=(const HashTable& a, const HashTable& b){
    return !(a == b);
}



