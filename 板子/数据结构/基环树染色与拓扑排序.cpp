#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/**
 * 快速幂：计算 (base^exp) % mod
 */
long long qpow(long long base, long long exp) {
    long long res = 1;
    base %= 998244353;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % 998244353;
        base = (base * base) % 998244353;
        exp /= 2;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n + 1);
    vector<int> in_degree(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        in_degree[a[i]]++;
    }

    const int MOD = 998244353;
    const int M_MINUS_1 = 25; // 26个字母，m-1 = 25

    // 1. 拓扑排序：找出所有不在环上的点（树枝部分）
    queue<int> q;
    vector<bool> vis(n + 1, false);
    int tree_node_count = 0;

    for (int i = 1; i <= n; ++i) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = true;
        tree_node_count++;
        
        int v = a[u];
        in_degree[v]--;
        if (in_degree[v] == 0) {
            q.push(v);
        }
    }

    // 树枝部分的贡献：每个点有 (m-1) 种选法
    long long ans = qpow(M_MINUS_1, tree_node_count);

    // 2. 遍历剩下的点，寻找所有的环
    for (int i = 1; i <= n; ++i) {
        // 如果入度 > 0 且未被访问，说明它是环的一部分
        if (!vis[i] && in_degree[i] > 0) {
            int curr = i;
            int cycle_len = 0;
            
            // 统计环长
            while (!vis[curr]) {
                vis[curr] = true;
                cycle_len++;
                curr = a[curr];
            }

            /**
             * 长度为 k 的环染色方案数公式：
             * P = (m-1)^k + (-1)^k * (m-1)
             */
            long long term1 = qpow(M_MINUS_1, cycle_len);
            long long term2 = (cycle_len % 2 == 0) ? M_MINUS_1 : -M_MINUS_1;
            
            long long cycle_contribution = (term1 + term2 + MOD) % MOD;
            ans = (ans * cycle_contribution) % MOD;
        }
    }

    cout << ans << endl;

    return 0;
}