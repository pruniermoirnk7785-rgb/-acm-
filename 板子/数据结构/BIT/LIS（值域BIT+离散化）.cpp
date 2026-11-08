#include <bits/stdc++.h>
using namespace std;
// 值域树状数组（前缀最大值）+ 离散化求 LIS
// 复杂度 O(n log n)，任意 int 值均可（含负数、重复、0）
struct BIT_max {
    int n;
    vector<int> tree;
    BIT_max(int sz) : n(sz), tree(sz + 1, 0) {}
    int lowbit(int x) { return x & -x; }
    // 前缀最大值更新：只能越改越大（LIS 的 dp 值单调不减，安全）
    void update(int pos, int val) {
        for (; pos <= n; pos += lowbit(pos)) {
            tree[pos] = max(tree[pos], val);
        }
    }
    // 查询 [1, pos] 的最大值
    int query(int pos) {
        int res = 0;
        for (; pos > 0; pos -= lowbit(pos)) {
            res = max(res, tree[pos]);
        }
        return res;
    }
};

// 离散化：返回 a 中每个元素在去重排序后的排名（1-based）
vector<int> compress(const vector<int>& a) {
    vector<int> id = a;
    sort(id.begin(), id.end());
    id.erase(unique(id.begin(), id.end()), id.end());
    vector<int> rk(a.size());
    for (int i = 0; i < (int)a.size(); i++) {
        rk[i] = lower_bound(id.begin(), id.end(), a[i]) - id.begin() + 1;
    }
    return rk;
}

// 最长上升子序列（严格递增）：query(rank-1)
int LIS(const vector<int>& a) {
    vector<int> rk = compress(a);
    BIT_max bit((int)rk.size());
    int ans = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        int best = bit.query(rk[i] - 1); // 严格小于 a[i] 的最大 dp
        bit.update(rk[i], best + 1);
        ans = max(ans, best + 1);
    }
    return ans;
}

// 最长不下降子序列（允许相等）：query(rank)
int LNDS(const vector<int>& a) {
    vector<int> rk = compress(a);
    BIT_max bit((int)rk.size());
    int ans = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        int best = bit.query(rk[i]); // 小于等于 a[i] 的最大 dp
        bit.update(rk[i], best + 1);
        ans = max(ans, best + 1);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cout << LIS(a) << '\n';
    return 0;
}