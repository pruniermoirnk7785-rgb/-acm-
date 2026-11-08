#include <bits/stdc++.h>
using namespace std;
// 计算 next 数组
void getNext(const string& pat, vector<int>& next) {
    int m = pat.size();
    next[0] = 0; // 第一个字符前后缀长度为0
    int j = 0;   // j 表示当前前缀的长度（也是正在比较的前缀指针）
    
    for (int i = 1; i < m; i++) {
        // 如果不匹配，回退 j
        while (j > 0 && pat[i] != pat[j]) {
            j = next[j - 1];
        }
        // 匹配成功，前缀长度+1
        if (pat[i] == pat[j]) {
            j++;
        }
        next[i] = j;
    }
}
int kmpSearch(const string& text, const string& pat) {
    int n = text.size(), m = pat.size();
    if (m == 0) return 0;
    
    vector<int> next(m);
    getNext(pat, next);
    
    int j = 0; // 模式串指针
    for (int i = 0; i < n; i++) {
        // 当前字符不匹配，回退 j
        while (j > 0 && text[i] != pat[j]) {
            j = next[j - 1];
        }
        if (text[i] == pat[j]) {
            j++;
        }
        // 找到完整匹配
        if (j == m) {
            return i - m + 1; // 返回起始下标（若只找第一次出现）
            // j = next[j - 1]; // 若需继续查找，回退 j
        }
    }
    return -1;
}