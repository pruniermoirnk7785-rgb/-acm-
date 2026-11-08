#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 自动取模整数类：所有运算后自动取模，无需手动写 % mod
// 用法：mint a, b; 支持 + - * / 幂、输入输出、比较
// 要求 mod 为质数（除法用费马小定理求逆元）
template<int MOD>
struct Mint {
    int v;

    // 构造：负数、大数自动归入 [0, MOD)
    Mint(ll x = 0) { v = (x % MOD + MOD) % MOD; }

    friend istream& operator>>(istream& is, Mint& a) { ll x; is >> x; a = Mint(x); return is; }
    friend ostream& operator<<(ostream& os, const Mint& a) { return os << a.v; }

    // 快速幂 a^b
    Mint qpow(ll b) const {
        Mint a = *this, res = 1;
        while (b) {
            if (b & 1) res *= a;
            a *= a;
            b >>= 1;
        }
        return res;
    }

    // 逆元 a^(mod-2)，要求 a 不为 0
    Mint inv() const { return qpow(MOD - 2); }

    // 取负
    Mint operator-() const { return Mint(-v); }

    Mint& operator+=(const Mint& b) {
        if ((v += b.v) >= MOD) v -= MOD;
        return *this;
    }
    Mint& operator-=(const Mint& b) {
        if ((v -= b.v) < 0) v += MOD;
        return *this;
    }
    Mint& operator*=(const Mint& b) {
        v = (ll)v * b.v % MOD;
        return *this;
    }
    Mint& operator/=(const Mint& b) { return *this *= b.inv(); }

    friend Mint operator+(Mint a, const Mint& b) { return a += b; }
    friend Mint operator-(Mint a, const Mint& b) { return a -= b; }
    friend Mint operator*(Mint a, const Mint& b) { return a *= b; }
    friend Mint operator/(Mint a, const Mint& b) { return a /= b; }

    friend bool operator==(const Mint& a, const Mint& b) { return a.v == b.v; }
    friend bool operator!=(const Mint& a, const Mint& b) { return a.v != b.v; }

    static int mod() { return MOD; }
};

// 两种常用模数，需要哪个就打开哪个（默认 998244353）
using mint = Mint<998244353>;
// using mint = Mint<1000000007>;  // 1e9+7

// ---- 分数取模 ----
// 直接写 a / b 即可：自动求逆元并取模，a、b 为负也会自动归正
// 例：mint ans = (mint)a / b;  // 等价于原来的 fractionMod(a, b)

// ---- 排列组合 ----
// initFact(n) 预处理 0..n 的阶乘和阶乘逆元，之后 O(1) 求 C(n,m)、P(n,m)
// n 记得按题目最大需要调整；n = 1e7 时约需 80MB 内存
vector<mint> fact, invFact;

void initFact(int n) {
    fact.resize(n + 1);
    invFact.resize(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i;
    invFact[n] = fact[n].inv();  // 费马小定理求逆元
    for (int i = n - 1; i >= 0; i--) invFact[i] = invFact[i + 1] * (i + 1);
}

// 组合数 C(n, m)：n 中取 m 个
mint C(int n, int m) {
    if (m < 0 || m > n) return 0;
    return fact[n] * invFact[m] * invFact[n - m];
}

// 排列数 P(n, m)：n 个里排 m 个
mint P(int n, int m) {
    if (m < 0 || m > n) return 0;
    return fact[n] * invFact[n - m];
}

int main() {
    // 例 1（第一版示例）：手写 mint 阶乘数组，直接除法算 C(10,5)
    mint fact[11];
    fact[0] = 1;
    for (int i = 1; i <= 10; i++) fact[i] = fact[i - 1] * i;
    mint C105 = fact[10] / (fact[5] * fact[5]);
    cout << C105 << endl;  // 252

    // 例 2（第一版示例）：负数自动归正、除法自动求逆
    mint a = -3, b = 4;
    cout << a / b << endl;  // -3/4：998244353 下为 748683264，1e9+7 下为 250000001

    // 例 3（第一版示例）：直接读入输出
    // mint x; cin >> x; cout << x << endl;

    // 例 4（集成的排列组合）：initFact 预处理后 O(1) 求 C(n,m)、P(n,m)
    initFact(10);
    cout << C(10, 5) << endl;  // 252
    cout << P(10, 3) << endl;  // 720
    return 0;
}
