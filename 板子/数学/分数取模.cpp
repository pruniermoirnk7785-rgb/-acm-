#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;

// 快速幂（底数自动归正，支持负数）
ll qpow(ll a, ll b) {
    a = (a % mod + mod) % mod;
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

// 求逆元：a^(p-2) mod p（要求 x 与 mod 互质）
ll inv(ll x) {
    return qpow(x, mod - 2);
}

// 分数取模：a/b mod p（a、b 均可为负，结果恒为非负）
ll fractionMod(ll a, ll b) {
    a = (a % mod + mod) % mod;
    return a * inv(b) % mod;
}

int main() {
    // 计算 1/2 mod 1e9+7
    cout << fractionMod(1, 2) << endl;   // 500000004
    // 负数：-1/2 mod 1e9+7 = 500000003
    cout << fractionMod(-1, 2) << endl;
    // 计算 3/4 mod 1e9+7
    cout << fractionMod(3, 4) << endl;   // 750000006
    // 负数：-3/4 mod 1e9+7 = 250000001
    cout << fractionMod(-3, 4) << endl;
    return 0;
}