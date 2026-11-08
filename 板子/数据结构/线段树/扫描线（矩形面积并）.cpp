#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
 * 扫描线 · 矩形面积并
 *
 * 题意：给定 n 个矩形 (x1,y1)-(x2,y2)，求它们的并集面积。
 *
 * 做法：
 *   1. 每个矩形拆成两条竖直边：下边 tag = +1，上边 tag = -1；
 *   2. 所有 x 坐标离散化，线段树的叶子 i 表示区间 [xs[i], xs[i+1])；
 *   3. 扫描线按 y 从小到大移动，线段树维护当前被覆盖的 x 总长度；
 *   4. 每扫过一段高度：ans += 覆盖长度 * (下一条扫描线 y - 当前 y)。
 *
 * 复杂度：O(n log n)。坐标可负，答案用 long long。
 * 注意：若坐标绝对值能到 1e18，面积可能超过 long long，需要 __int128。
 *
 * 对应题目：洛谷 P5490 【模板】扫描线 / 矩形面积并
 */

struct Node {
    ll y;      // 扫描线高度
    int l, r;  // 离散化后的 x 区间 [l, r)，叶子编号
    int tag;   // +1 进入矩形，-1 离开矩形
};

struct ScanLine {
    int n;              // 叶子个数 = 不同 x 坐标数 - 1
    vector<ll> xs;      // 离散化后的 x 坐标
    vector<int> cnt;    // 该节点区间被完整覆盖的次数
    vector<ll> len;     // 该节点区间内被覆盖的总长度

    explicit ScanLine(vector<ll> x) : xs(move(x)) {
        n = max(0, (int)xs.size() - 1);
        int cap = 4 * max(n, 1) + 5;
        cnt.assign(cap, 0);
        len.assign(cap, 0);
    }

    void pushup(int u, int l, int r) {
        if (cnt[u] > 0) {
            len[u] = xs[r + 1] - xs[l];    // 整段被覆盖
        } else if (l == r) {
            len[u] = 0;                    // 叶子且没有被完整覆盖
        } else {
            len[u] = len[u << 1] + len[u << 1 | 1];
        }
    }

    void modify(int u, int l, int r, int ql, int qr, int tag) {
        if (ql <= l && r <= qr) {
            cnt[u] += tag;
            pushup(u, l, r);
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid) modify(u << 1, l, mid, ql, qr, tag);
        if (qr > mid) modify(u << 1 | 1, mid + 1, r, ql, qr, tag);
        pushup(u, l, r);
    }

    // 覆盖离散化后的 x 区间 [l, r)
    void modify(int l, int r, int tag) {
        if (n == 0 || l >= r) return;
        modify(1, 0, n - 1, l, r - 1, tag);
    }

    ll covered() const { return n ? len[1] : 0; }
};

// 传入所有矩形 {x1, y1, x2, y2}，返回并集面积
ll UnionArea(vector<array<ll, 4>> rects) {
    vector<ll> xs;
    for (auto &a : rects) {
        if (a[0] > a[2]) swap(a[0], a[2]);
        if (a[1] > a[3]) swap(a[1], a[3]);
        if (a[0] == a[2] || a[1] == a[3]) continue;  // 退化矩形无面积
        xs.push_back(a[0]);
        xs.push_back(a[2]);
    }
    if (xs.empty()) return 0;

    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    vector<Node> Nodes;
    Nodes.reserve(rects.size() * 2);
    for (auto &a : rects) {
        if (a[0] == a[2] || a[1] == a[3]) continue;
        int l = lower_bound(xs.begin(), xs.end(), a[0]) - xs.begin();
        int r = lower_bound(xs.begin(), xs.end(), a[2]) - xs.begin();
        Nodes.push_back({a[1], l, r, +1});
        Nodes.push_back({a[3], l, r, -1});
    }

    sort(Nodes.begin(), Nodes.end(), [](const Node &A, const Node &B) {
        return A.y < B.y;
    });

    ScanLine seg(xs);
    ll ans = 0;
    for (int i = 0; i + 1 < (int)Nodes.size(); i++) {
        seg.modify(Nodes[i].l, Nodes[i].r, Nodes[i].tag);
        ans += seg.covered() * (Nodes[i + 1].y - Nodes[i].y);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<array<ll, 4>> rects(n);
    for (auto &a : rects) {
        cin >> a[0] >> a[1] >> a[2] >> a[3];
    }
    cout << UnionArea(rects) << '\n';
    return 0;
}