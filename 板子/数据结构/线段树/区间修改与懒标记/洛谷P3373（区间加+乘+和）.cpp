#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5 + 5;

int n, m;
ll mod;
ll a[maxn];

struct Node {
    ll sum;   // 区间和 (已对 mod 取模)
    ll mul;   // 乘法懒标记, 初始为 1
    ll add;   // 加法懒标记, 初始为 0
};
Node tree[maxn << 2];

// 对整个节点区间 (u, l, r) 一次性乘 k
void apply_mul(int u, ll k) {
    k %= mod;
    tree[u].sum = tree[u].sum * k % mod;
    tree[u].mul = tree[u].mul * k % mod;
    tree[u].add = tree[u].add * k % mod;   // 关键: 以前攒下的加法也要一起乘
}

// 对整个节点区间 (u, l, r) 一次性加 k
void apply_add(int u, int l, int r, ll k) {
    k %= mod;
    tree[u].sum = (tree[u].sum + k * (r - l + 1)) % mod;
    tree[u].add = (tree[u].add + k) % mod;
}

void pushup(int u) {
    tree[u].sum = (tree[u << 1].sum + tree[u << 1 | 1].sum) % mod;
}

void pushdown(int u, int l, int r) {
    if (tree[u].mul == 1 && tree[u].add == 0) return;
    int mid = l + ((r - l) >> 1);
    // 顺序很重要: 先下传乘法, 再下传加法
    apply_mul(u << 1, tree[u].mul);
    apply_mul(u << 1 | 1, tree[u].mul);
    apply_add(u << 1, l, mid, tree[u].add);
    apply_add(u << 1 | 1, mid + 1, r, tree[u].add);
    tree[u].mul = 1;
    tree[u].add = 0;
}

void build(int u, int l, int r) {
    tree[u].mul = 1;
    tree[u].add = 0;
    if (l == r) {
        tree[u].sum = a[l] % mod;
        return;
    }
    int mid = l + ((r - l) >> 1);
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

// 区间乘法
void update_mul(int u, int l, int r, int ql, int qr, ll k) {
    if (ql <= l && r <= qr) {
        apply_mul(u, k);
        return;
    }
    pushdown(u, l, r);
    int mid = l + ((r - l) >> 1);
    if (ql <= mid) update_mul(u << 1, l, mid, ql, qr, k);
    if (qr > mid) update_mul(u << 1 | 1, mid + 1, r, ql, qr, k);
    pushup(u);
}

// 区间加法
void update_add(int u, int l, int r, int ql, int qr, ll k) {
    if (ql <= l && r <= qr) {
        apply_add(u, l, r, k);
        return;
    }
    pushdown(u, l, r);
    int mid = l + ((r - l) >> 1);
    if (ql <= mid) update_add(u << 1, l, mid, ql, qr, k);
    if (qr > mid) update_add(u << 1 | 1, mid + 1, r, ql, qr, k);
    pushup(u);
}

// 区间求和
ll query(int u, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[u].sum;
    pushdown(u, l, r);
    int mid = l + ((r - l) >> 1);
    ll res = 0;
    if (ql <= mid) res = (res + query(u << 1, l, mid, ql, qr)) % mod;
    if (qr > mid) res = (res + query(u << 1 | 1, mid + 1, r, ql, qr)) % mod;
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> mod;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);
    while (m--) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1) {
            ll k; cin >> k;
            update_mul(1, 1, n, l, r, k);
        } else if (op == 2) {
            ll k; cin >> k;
            update_add(1, 1, n, l, r, k);
        } else {
            cout << query(1, 1, n, l, r) % mod << "\n";
        }
    }
    return 0;
}