#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 扩展欧几里得：求 ax + by = gcd(a, b) 的一组整数解 (x, y)，返回 gcd
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

// 求 a 在模 m 下的逆元（要求 gcd(a, m) = 1）
ll inv(ll a, ll m) {
    ll x, y;
    exgcd(a, m, x, y);
    return (x % m + m) % m;
}

// 解线性同余方程 ax ≡ c (mod m)：有解返回 true，x 存最小非负特解
bool solveMod(ll a, ll c, ll m, ll &x) {
    ll g, y;
    g = exgcd(a, m, x, y);
    if (c % g) return false;          // 裴蜀定理：g 必须整除 c
    ll m2 = m / g;
    x = (c / g) % m2 * x % m2;        // ax ≡ c (mod m/g) 的特解
    x = (x % m + m) % m;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    // exgcd：6x + 15y = gcd(6,15) = 3，一组解 x=-2, y=1
    ll x, y, g = exgcd(6, 15, x, y);
    cout << "gcd(6,15)=" << g << " x=" << x << " y=" << y << '\n';

    // 模逆元：3 在模 11 下的逆元
    cout << "inv(3,11)=" << inv(3, 11) << '\n';     // 4

    // 解 2x ≡ 3 (mod 5)，特解 x=4
    if (solveMod(2, 3, 5, x)) cout << "2x=3(mod5) x=" << x << '\n';
    // 无解例子：2x ≡ 3 (mod 4)
    if (!solveMod(2, 3, 4, x)) cout << "2x=3(mod4) 无解\n";
    return 0;
}