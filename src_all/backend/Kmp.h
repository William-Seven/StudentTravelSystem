#ifndef CLIONTEST_KMP_H
#define CLIONTEST_KMP_H

#include<iostream>
#include<string>

/*获取nextval[t.length()]数组*/
void get_nextval(std::string t, int nextval[]);

/*在字符串s中查找字符串t第一次出现的下标*/
bool kmp(std::string t, std::string s);
#endif //CLIONTEST_KMP_H
