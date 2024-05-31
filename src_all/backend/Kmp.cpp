//
// Created by SevenGrass on 2024/5/20.
//
#include "Kmp.h"

void get_nextval(std::string t, int nextval[]) {
    int j = 0, k = -1;
    int t_len = t.length();
    nextval[0] = -1;
    while (j < t_len)
        if (k == -1 || t[j] == t[k]) {
            j++;
            k++;
            if (t[j] != t[k])
                nextval[j] = k;
            else
                nextval[j] = nextval[k];
        } else
            k = nextval[k];
}

bool kmp(std::string t, std::string s) {
    if (t == "-1")
        return 1;
    int line_limit;
    line_limit = t.length();
    int nextval[line_limit];
    int i = 0, j = 0;
    int s_len = s.length(), t_len = t.length();
    get_nextval(t, nextval);
    while (i < s_len && j < t_len)
        if (j == -1 || s[i] == t[j]) {
            i++;
            j++;
        } else
            j = nextval[j];
    if (j >= t_len)
        return true;
    else
        return false;
}