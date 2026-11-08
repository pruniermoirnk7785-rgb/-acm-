#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = 2e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    // 完全图的邻接矩阵（1-based）
    vector<vector<ll>> b(n + 1, vector<ll>(n + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> b[i][j];
        }
    }

    // Prim（O(n^2)），稠密图/完全图用邻接矩阵
    vector<ll> min_edge(n + 1, INF);
    vector<bool> tree(n + 1, 0);
    min_edge[1] = 0;
    ll ans = 0;
    ll u;
    for (int i = 0; i < n; i++) {
        u = -1;
        ll cur = INF;
        for (int v = 1; v < n + 1; v++) {
            if (!tree[v] && min_edge[v] < cur) {
                cur = min_edge[v];
                u = v;
            }
        }
        tree[u] = 1;
        ans += cur;
        for (int v = 1; v < n + 1; v++) {
            if (!tree[v] && b[u][v] < min_edge[v]) {
                min_edge[v] = b[u][v];
            }
        }
    }
    cout << ans << "\n";
    return 0;
}