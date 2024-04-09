// 文件说明：自实现哈希表结构

#ifndef MYHASHMAP_H
#define MYHASHMAP_H

#include <iostream>
#include <vector>
#include "Node.h"

// 自定义哈希节点类模板，用于存储键值对和指向下一个节点的指针
template <typename Key, typename Value>
class HashNode {
   public:
    Key key;         // 键
    Value value;     // 值
    HashNode* next;  // 指向下一个节点

    // 构造函数，初始化键值对和下一个节点的指针为nullptr
    HashNode(Key _key, Value _value)
        : key(_key), value(_value), next(nullptr) {}

    // 析构函数
    ~HashNode() {}
};

// 自定义哈希表类模板
template <typename Key, typename Value, typename HashFunc>
class HashMap {
   public:
    int size;                      // 哈希表大小
    HashFunc hash;                 // 哈希函数，用于计算键的哈希值
    HashNode<Key, Value>** table;  // 指向哈希节点指针数组的指针，实现键值对的存储
    Value valuenull;               // 查找失败时返回的默认值

    // 构造函数，传入哈希表的大小
    HashMap(int _size);
    // 析构函数，释放内存
    ~HashMap();

    // 插入操作：向哈希表中插入一个键值对
    bool insert(Key key, Value value);
    // 删除操作：从哈希表中删除指定键的节点
    bool del(Key& key);
    // 查找操作：根据键查找对应的值
    Value* find(Key& key);
    // 重载[]操作符：提供一种通过键访问值的便捷方式
    Value& operator[](Key& key);
    // 打印哈希表：遍历并打印哈希表中的所有键值对
    void print();
};

// 自定义哈希函数类模板
// template <typename Key>
class HashFunc {
   public:
    // 重载()操作符，用于计算键的哈希值
    int operator()(const int key) {
        return 3 * key + 1;
    }
};

#endif  // MYHASHMAP_H