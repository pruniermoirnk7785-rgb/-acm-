#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; // n: 节点数, m: 边数
    cin >> n >> m;
    
    // 邻接表：ver[u] 存储从 u 出发的所有边 (v, w)
    vector<vector<pair<int, int>>> ver(n + 1);
    
    // 读入 m 条边
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        ver[u].emplace_back(v, w); // 有向图
        // 如果是无向图，加上下面这行：
        // ver[v].emplace_back(u, w);
    }
    
    // 距离数组，初始化为无穷大
    vector<long long> dis(n + 1, 1E18);
    
    // Dijkstra 算法
    auto dijkstra = [&](int s = 1) -> void {
        using PII = pair<long long, int>; // 注意：距离用 long long
        priority_queue<PII, vector<PII>, greater<PII>> q;
        
        dis[s] = 0;
        q.emplace(0, s);
        
        vector<int> vis(n + 1);
        
        while (!q.empty()) {
            int x = q.top().second;
            q.pop();
            
            if (vis[x]) continue;
            vis[x] = 1;
            
            for (auto [y, w] : ver[x]) {
                if (dis[y] > dis[x] + w) {
                    dis[y] = dis[x] + w;
                    q.emplace(dis[y], y);
                }
            }
        }
    };
    
    // 从节点 1 开始运行 Dijkstra
    dijkstra(1);
    
    // 输出结果
    for (int i = 1; i <= n; i++) {
        if (dis[i] == 1E18) {
            cout << "INF" << "\n"; // 不可达
        } else {
            cout << dis[i] << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    solve();
    
    return 0;
}