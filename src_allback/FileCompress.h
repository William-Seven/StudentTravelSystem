#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include "HuffmanTree.h"

#define _SIZE_ 1024
#define _FILE_NAME_SIZE_ 128

struct CodeInfo  // 定义CodeInfo结构体，用于存储每个字符的编码和频率
{
    CodeInfo()
        : code(), cnt(0) {}

    friend bool operator>(const CodeInfo& left, const CodeInfo& right) {
        return left.cnt > right.cnt;
    }

    friend bool operator!=(const CodeInfo& left, const CodeInfo& right) {
        return left.cnt != right.cnt;
    }

    friend CodeInfo operator+(const CodeInfo& left, const CodeInfo& right) {
        CodeInfo ret;
        ret.cnt = left.cnt + right.cnt;
        return ret;
    }

    unsigned char ch;  // 字符本身
    std::string code;  // 该字符的哈夫曼编码
    long long cnt;     // 该字符出现次数
};

class FileCompress  // 该类包含压缩和解压缩文件的方法
{
   public:  // 成员函数
    // 压缩
    void Compress(const std::string& FilePath);

    // 解压缩
    void UnCompress(const std::string& FilePath);

   private:  // 私有成员函数
    // 从文件路径中获取文件名
    void GetFileName(const std::string& FilePath, std::string& output);

    // 获取扩展名（后缀）
    void GetPostfixName(const std::string& FilePath, std::string& output);

    // 填充info信息，读取源文件并填充字符频率信息
    void FillInfo(FILE* src);

    // 填充编码信息，根据哈夫曼编码填充字符的编码
    void FillCode(const HuffmanTreeNode<CodeInfo>* pRoot);

    // 核心压缩函数
    void CompressCore(FILE* src, FILE* dst, const std::string& FilePath);

    // 保存编码信息至压缩文件首部
    void SaveCode(FILE* dst, const std::string& FilePath);

    // 从文件中获取一行元素
    void GetLine(FILE* src, unsigned char* buf, int size);

    // 从解压缩文件中获取头部编码信息
    void GetHead(FILE* src, std::string& Postfix);

    // 核心解压函数
    void UnCompressCore(FILE* input, FILE* output, HuffmanTreeNode<CodeInfo>* pRoot);

   private:
    CodeInfo info[256];
};
