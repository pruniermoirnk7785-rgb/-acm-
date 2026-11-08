#include <bits/stdc++.h>
using namespace std;

// 并查集：路径压缩 + 按大小合并，均摊 O(α(n)) 近似 O(1)
struct DSU {
    vector<int> fa, sz; // fa[i] 父亲，sz[i] 仅对根有意义（集合大小）
    int cnt;            // 当前连通块个数

    DSU(int n = 0) { init(n); }

    void init(int n) {
        fa.resize(n + 1);
        sz.assign(n + 1, 1);
        cnt = n;
        for (int i = 1; i <= n; i++) fa[i] = i;
    }

    int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

    // 合并 x, y 所在集合，返回是否真的合并了（原本不在同一集合）
    bool unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (sz[x] < sz[y]) swap(x, y); // 小的并到大的上
        fa[y] = x;
        sz[x] += sz[y];
        cnt--;
        return true;
    }

    bool same(int x, int y) { return find(x) == find(y); }
    int size(int x) { return sz[find(x)]; }
};

// 扩展：带权并查集（维护到根的距离/差值），例题：POJ 1182 食物链
// struct WeightedDSU {
//     vector<int> fa, w; // w[x]：x 到 fa[x] 的权值（按题目定义维护）
//     int find(int x) {
//         if (fa[x] == x) return x;
//         int root = find(fa[x]);
//         w[x] += w[fa[x]]; // 先累加父亲，再更新自己（顺序不能反）
//         return fa[x] = root;
//     }
//     // 合并时按题意推导 w 的转移式
// };

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    // 示例：n 个点 m 次操作，1 x y 查询是否连通，0 x y 合并
    int n, m;
    cin >> n >> m;
    DSU dsu(n);
    while (m--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1) {
            cout << (dsu.same(x, y) ? "YES" : "NO") << '\n';
        } else {
            dsu.unite(x, y);
        }
    }
    return 0;
}
