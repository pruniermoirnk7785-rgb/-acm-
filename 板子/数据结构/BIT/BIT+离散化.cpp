#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// 林月的树状数组板子，1-base
template<class Int>
struct BIT {
    vector<Int> a;
    int n;

    BIT() {}
    BIT(int n) { init(n); }

    void init(int n) {
        this->n = n;
        a.resize(n + 1);
    }

    // O(n) 建树：arr 下标从 0 开始，长度 n
    void build(const vector<Int>& arr) {
        n = (int)arr.size();
        a.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            a[i] += arr[i - 1];
            int j = i + (i & -i);
            if (j <= n) a[j] += a[i];
        }
    }

    void add(int x, Int k) {
        for (; x <= n; x += x & -x) {
            a[x] += k;
        }
    }
    void add(int x, int y, Int k) {
        add(x, k), add(y + 1, -k);
    }
    Int ask(int x) {
        Int ans = 0;
        for (; x; x -= x & -x) {
            ans += a[x];
        }
        return ans;
    }
    Int ask(int x, int y) {
        return ask(y) - ask(x - 1);
    }

    // 返回前缀和 >= k 的最小下标（值域第 k 小，k 从 1 开始）
    Int kth(int k) {
        Int ans = 0;
        for (int i = __lg(n); i >= 0; i--) {
            Int val = ans + (1 << i);
            if (val < n && a[val] < k) {
                k -= a[val];
                ans = val;
            }
        }
        return ans + 1;
    }

    // 值域第 k 大（k 从 1 开始）
    Int kthBig(int k) {
        return kth(ask(n) - k + 1);
    }
};

// 离散化：返回 v 中每个元素在去重排序后的排名（1-based）
template<class T>
vector<int> compress(const vector<T>& v) {
    vector<T> id = v;
    sort(id.begin(), id.end());
    id.erase(unique(id.begin(), id.end()), id.end());
    vector<int> rank(v.size());
    for (int i = 0; i < (int)v.size(); i++) {
        rank[i] = lower_bound(id.begin(), id.end(), v[i]) - id.begin() + 1;
    }
    return rank;
}

// 逆序对数量：a 中 i<j 且 a[i]>a[j] 的 (i,j) 对数
// 示例：inversionCount({3, 1, 4, 2}) = 3
ll inversionCount(const vector<ll>& a) {
    vector<int> rk = compress(a);
    int tot = *max_element(rk.begin(), rk.end());
    BIT<int> bit(tot);
    ll ans = 0;
    for (int i = (int)a.size() - 1; i >= 0; i--) {
        ans += bit.ask(rk[i] - 1); // 已扫过的、比 a[i] 小的个数
        bit.add(rk[i], 1);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<ll> nums;
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        nums.push_back(num);
    }
    vector<ll> pre(2 * n + 1, 0);
    for (int i = 1; i <= 2 * n; i++) {
        pre[i] = pre[i - 1] + nums[(i - 1) % n];
    }
    // 离散化：pre -> 排名（1-based）
    vector<int> rk = compress(pre);
    int tot = *max_element(rk.begin(), rk.end());

    BIT<int> bit(tot);
    for (int i = 1; i <= n; i++) {
        bit.add(rk[i], 1);
    }
    ll max = -10000000000000000;
    ll br = -1;
    for (int i = 0; i < n; i++) {
        int r = rk[i];
        ll score = n - bit.ask(r);
        if (score > max) {
            max = score;
            br = i;
        }
        if (i < n - 1) {
            bit.add(rk[i + 1], -1);
            bit.add(rk[i + n + 1], 1);
        }
    }
    cout << br << " " << max << endl;
    return 0;
    // let me ac
    // ac
}