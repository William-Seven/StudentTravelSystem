// My哈希表方法实现

#include "MyHashMap.h"

// 哈希表构造函数
template <typename Key, typename Value, typename HashFunc>
HashMap<Key, Value, HashFunc>::HashMap(int _size)
    : size(_size), hash() {
    table = new HashNode<Key, Value>*[_size];
    for (int i = 0; i < _size; i++) {
        table[i] = nullptr;  // 初始化哈希表中的每个槽位为空
    }
}

// 哈希表析构函数
template <typename Key, typename Value, typename HashFunc>
HashMap<Key, Value, HashFunc>::~HashMap() {
    for (int i = 0; i < size; i++) {
        HashNode<Key, Value>* cur = table[i];
        while (cur != nullptr) {
            HashNode<Key, Value>* temp = cur;
            cur = cur->next;
            delete temp;  // 释放节点占用的内存
        }
    }
    delete[] table;  // 释放存储节点指针的数组
}

// 插入函数
template <typename Key, typename Value, typename HashFunc>
bool HashMap<Key, Value, HashFunc>::insert(Key key, Value value) {
    int index = hash(key) % size;
    HashNode<Key, Value>* newnode = new HashNode<Key, Value>(key, value);
    newnode->next = table[index];
    table[index] = newnode;
    return true;
}

// 删除函数
template <typename Key, typename Value, typename HashFunc>
bool HashMap<Key, Value, HashFunc>::del(Key& key) {
    int index = hash(key) % size;
    HashNode<Key, Value>* cur = table[index];
    HashNode<Key, Value>* pre = nullptr;
    while (cur != nullptr) {
        if (cur->key == key) {
            if (pre != nullptr) {
                pre->next = cur->next;
            } else {
                table[index] = cur->next;
            }
            delete cur;
            return true;
        }
        pre = cur;
        cur = cur->next;
    }
    return false;
}

// 查找函数
template <typename Key, typename Value, typename HashFunc>
Value* HashMap<Key, Value, HashFunc>::find(Key& key) {
    int index = hash(key) % size;
    HashNode<Key, Value>* cur = table[index];
    while (cur != nullptr) {
        if (cur->key == key)
            return &(cur->value);
        cur = cur->next;
    }
    // std::cout << "Key not found!" << std::endl;
    return nullptr;
}

template <typename Key, typename Value, typename HashFunc>
Value& HashMap<Key, Value, HashFunc>::operator[](Key& key) {
    return *(find(key));
}

template <typename Key, typename Value, typename HashFunc>
void HashMap<Key, Value, HashFunc>::print() {
    for (int i = 0; i < size; i++) {
        HashNode<Key, Value>* cur = table[i];
        std::cout << "Slot[" << i << "]: ";
        while (cur != nullptr) {
            std::cout << "(" << cur->key << ", " << cur->value << ") -> ";
            cur = cur->next;
        }
        std::cout << "NULL" << std::endl;
    }
}

// template class HashFunc<int>;
template class HashMap<int, Node*, HashFunc>;
template class HashMap<int, double, HashFunc>;
template class HashMap<int, bool, HashFunc>;
template class HashMap<int, int, HashFunc>;
