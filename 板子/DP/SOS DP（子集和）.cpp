#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ============ SOS DP（子集和）模板 ============
// sos[mask] = Σ_{sub ⊆ mask} f[sub]，即每个 mask 的所有子集的 f 之和
// 复杂度 O(n * 2^n)
// 超集和变体：sup[mask] = Σ_{sup ⊇ mask} f[sup]
//   for (int i = 0; i < n; i++)
//     for (int mask = 0; mask < (1 << n); mask++)
//       if (!(mask >> i & 1)) sup[mask] += sup[mask | (1 << i)];
const int MAXB = 12;   // 二进制位数上限，按题目修改
int f[1 << MAXB];      // 输入：每个 mask 的初始值（频次/权值）
int sos[1 << MAXB];    // 输出：子集和

void sosDP(int n) {
    for (int m = 0; m < (1 << n); m++) {
        sos[m] = f[m];
    }
    for (int i = 0; i < n; i++) {
        for (int m = 0; m < (1 << n); m++) {
            if (m >> i & 1) {
                sos[m] += sos[m ^ (1 << i)];
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int mm = 0;
        for (int j = 0; j < m; j++) {
            if (s[j] == '1') {
                mm |= (1 << j);
            }
        }
        a[i] = mm;
        f[mm]++;
    }
    sosDP(m);
    ll cant = 0;
    int all = (1 << m) - 1;
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
            cant += n - 1;
        } else {
            int d = all ^ a[i];
            cant += sos[d];
        }
    }
    ll ans = 1LL * n * (n - 1) / 2 - cant / 2;
    cout << ans << '\n';
    return 0;
}