#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// =====================================================================
// 线段树（离线扫描）· 查询完全包含区间 [L,R] 的线段最大长度
// ---------------------------------------------------------------------
// 问题模型：
//   有 n 条线段，第 i 条为 [l_i, r_i]，长度 = r_i - l_i + 1。
//   q 次询问：给定 [L, R]，求满足 l_i >= L 且 r_i <= R 的线段长度的
//   最大值（即完全被 [L,R] 包含的线段的最大长度），没有则为 0。
//
// 做法（离线 + 扫描线 + 线段树维护前缀最大值）：
//   1. 线段按左端点 l 降序排，询问按 L 降序排；
//   2. 依次处理每个询问：把满足 l >= 当前 L 的线段全部插入线段树
//      —— 线段树以下标 = 右端点 r 的离散化排名为位置，维护该位置上
//      的最大长度（同一 r 出现多条线段时取 max，即"单点取 max"）；
//   3. 查询 [1, get(R)] 的前缀最大值，即为同时满足 l >= L、r <= R
//      的线段最大长度。
//   正确性：扫描到询问 [L,R] 时树里恰好包含所有 l >= L 的线段，
//   再按 r <= R 取前缀 max，正好对应"完全包含"这一条件。
//
// 复杂度：O((n+q) log(n+q))；离散化同样 O((n+q) log(n+q))
// 注意：
//   - 右端点 r 来自线段和询问两边，必须一起离散化；
//   - tree 数组大小需 >= 4 * 离散化后点数（本模板取 4*maxn）；
//   - 无满足条件的线段时输出 0（query 的 res 初值为 0）。
// =====================================================================

const int maxn = 4e5 + 5;   // 线段 / 询问个数上限（按题修改，注意 tree 大小）

struct Node
{
    ll l, r, len;           // 线段左端点、右端点、长度
} a[maxn];
struct Q
{
    ll L, R, id;            // 询问左端点、右端点、编号（离线后按原序输出）
} q[maxn];

int tree[maxn << 2];        // 线段树：单点取 max、区间查前缀最大值
int ans[maxn];              // 答案按询问原顺序存放

// 向上合并：父节点 = 左右子节点的较大值
void pushup(int u)
{
    tree[u] = max(tree[u << 1], tree[u << 1 | 1]);
}

// 单点更新：把位置 p 的值更新为 max(tree[u], val)
void update(int u, int l, int r, int p, int val)
{
    if (l == r)
    {
        tree[u] = max(tree[u], val);
        return;
    }
    int mid = l + ((r - l) >> 1);
    if (p <= mid)
        update(u << 1, l, mid, p, val);
    else
        update(u << 1 | 1, mid + 1, r, p, val);
    pushup(u);
}

// 区间查询最大值（本模板只用到前缀 [1, qr]，写成通用区间查询）
ll query(int u, int l, int r, int ql, int qr)
{
    if (ql <= l and r <= qr)
    {
        return tree[u];
    }
    int mid = l + ((r - l) >> 1);
    ll res = 0;                             // 无满足条件的线段时返回 0
    if (ql <= mid)
        res = max(res, query(u << 1, l, mid, ql, qr));
    if (qr > mid)
        res = max(res, query(u << 1 | 1, mid + 1, r, ql, qr));
    return res;
}

// 线段按左端点降序
bool cmp1(const Node &a, const Node &b)
{
    return a.l > b.l;
}
// 询问按左端点降序
bool cmp2(const Q &a, const Q &b)
{
    return a.L > b.L;
}

void solve()
{
    int n, qq;
    cin >> n >> qq;
    vector<int> all;                        // 离散化数组：所有右端点 r + 询问右端点 R
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i].l >> a[i].r;
        a[i].len = a[i].r - a[i].l + 1;     // 线段长度
        all.push_back(a[i].r);
    }
    for (int i = 1; i <= qq; i++)
    {
        cin >> q[i].L >> q[i].R;
        q[i].id = i;                        // 记住原顺序，最后按 id 输出
        all.push_back(q[i].R);
    }
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());
    int sz = all.size();                    // 离散化后的值域大小
    // 值 x 的离散化排名（1-based）
    auto get = [&](int x)
    {
        return lower_bound(all.begin(), all.end(), x) - all.begin() + 1;
    };
    sort(a + 1, a + n + 1, cmp1);           // l 降序
    sort(q + 1, q + qq + 1, cmp2);          // L 降序
    memset(tree, 0, sizeof(tree));          // 清空线段树
    int ptr = 1;                            // 指向第一个未被插入的线段
    for (int i = 1; i <= qq; i++)
    {
        // 把左端点 >= 当前询问 L 的线段全部插入
        while (ptr <= n && a[ptr].l >= q[i].L)
        {
            int pos = get(a[ptr].r);        // 以右端点排名为位置
            update(1, 1, sz, pos, a[ptr].len);  // 该位置取 max 长度
            ptr++;
        }
        int pos = get(q[i].R);              // 询问右端点的排名
        ans[q[i].id] = query(1, 1, sz, 1, pos); // 前缀最大值 = 答案
    }
    for (int i = 1; i <= qq; i++)
    {
        cout << ans[i] << "\n";             // 按原顺序输出
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}