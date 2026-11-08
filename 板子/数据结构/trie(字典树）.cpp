#include <bits/stdc++.h>
using namespace std;

// ===== 数组版 01 Trie 板子 =====
// 只存 0/1：nxt 开 [2]；若存小写字母，改成 [26] 并把 b = c - 'a'
// 节点数上限 ≈ 字符串总长度 + 1，按数据范围估（如 q * |s| 的最大值）

const int MAXN = 4000005;

int nxt[MAXN][2];
int cnt[MAXN]; // 经过该节点的字符串个数（该前缀按多重集计的出现次数）
int tot = 0;   // 根节点编号为 0，nxt 数组默认全 0 表示空儿子

// 插入字符串 s
void insert(const string& s) {
    int u = 0;
    for (char c : s) {
        int b = c - '0';
        if (!nxt[u][b]) nxt[u][b] = ++tot;
        u = nxt[u][b];
        cnt[u]++;
    }
}

// 删除字符串 s（题目保证集合中存在，节点必然已建好）
void erase(const string& s) {
    int u = 0;
    for (char c : s) {
        int b = c - '0';
        u = nxt[u][b];
        cnt[u]--;
    }
}

// s 作为前缀在集合中出现了多少次（不存在返回 0）
int count_prefix(const string& s) {
    int u = 0;
    for (char c : s) {
        int b = c - '0';
        u = nxt[u][b];
        if (!u) return 0; // 走到空节点，说明该前缀不存在
    }
    return cnt[u];
}

// 判断 s 是否是某个已存在字符串的前缀
bool exist_prefix(const string& s) { return count_prefix(s) > 0; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // 题目 E 的用法：每个节点 cnt>0 即对应一个不同的非空前缀，
    // 插入/删除时维护 ans：cnt 0->1 时 ans++，1->0 时 ans--
    return 0;
}
