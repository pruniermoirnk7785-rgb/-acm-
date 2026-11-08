#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 数据规模: n 最大 1e9, 操作数 q 最大 1e5, 且初始 a[i] = i
// 树里只维护"额外加的值 delta"(初始全是 0, 所以没建过的点就是 0)
// 真正的答案 = delta 的区间和 + 初始等差数列 a[i]=i 的区间和
//
// 动态开点: 节点用到了才建 (++tot), 所以每个节点要存左右儿子的下标
// 下标 0 表示"空", 数组是全局变量, tr[0] 的 sum/lazy 自动为 0
struct Node {
    ll sum;     // delta 的区间和
    ll lazy;    // 加法懒标记
    int lc, rc; // 左右儿子下标, 0 表示还没建出来
};

// log2(1e9) ≈ 30, 每个操作最坏大约新开 2*log2(n) 个点
// 节点上限取 q * (2*31) 左右, 不够就把系数调大
const int MAXNODE = (100000 + 10) * 64;
Node tr[MAXNODE];
int tot = 0; // 当前一共建了几个点 (从 1 开始)

int newNode() {
    ++tot;
    tr[tot] = {0, 0, 0, 0};
    return tot;
}

// 初始 a[i] = i 时, 区间 [l, r] 的和 (等差数列)
ll baseSum(int l, int r) {
    return (ll)(l + r) * (r - l + 1) / 2;
}

void addTag(int u, ll len, ll v) {
    tr[u].sum += v * len;
    tr[u].lazy += v;
}

void pushup(int u) {
    // 没建出来的儿子是下标 0, tr[0].sum 恒为 0, 直接加即可
    tr[u].sum = tr[tr[u].lc].sum + tr[tr[u].rc].sum;
}

void pushdown(int u, int l, int r) {
    if (l == r || tr[u].lazy == 0) return;
    int mid = l + ((r - l) >> 1);
    if (!tr[u].lc) tr[u].lc = newNode();
    if (!tr[u].rc) tr[u].rc = newNode();
    addTag(tr[u].lc, mid - l + 1, tr[u].lazy);
    addTag(tr[u].rc, r - mid, tr[u].lazy);
    tr[u].lazy = 0;
}

// u 传引用: 第一次访问这个点时把它建出来
void update(int &u, int l, int r, int ql, int qr, ll v) {
    if (!u) u = newNode();
    if (ql <= l && r <= qr) {
        addTag(u, r - l + 1, v);
        return;
    }
    pushdown(u, l, r);
    int mid = l + ((r - l) >> 1);
    if (ql <= mid) update(tr[u].lc, l, mid, ql, qr, v);
    if (qr > mid) update(tr[u].rc, mid + 1, r, ql, qr, v);
    pushup(u);
}

// 只查询 delta(额外加的部分), 初值部分在 main 里用 baseSum 补上
ll query(int u, int l, int r, int ql, int qr) {
    if (!u) return 0;
    if (ql <= l && r <= qr) return tr[u].sum;
    pushdown(u, l, r);
    int mid = l + ((r - l) >> 1);
    ll res = 0;
    if (ql <= mid) res += query(tr[u].lc, l, mid, ql, qr);
    if (qr > mid) res += query(tr[u].rc, mid + 1, r, ql, qr);
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q; // n 最大 1e9, 初始 a[i] = i
    cin >> n >> q;

    int root = 0;
    while (q--) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1) { // 区间加 v
            ll v;
            cin >> v;
            update(root, 1, n, l, r, v);
        } else {       // 区间求和: delta + 初始 i 的和
            cout << baseSum(l, r) + query(root, 1, n, l, r) << "\n";
        }
    }
    return 0;
}