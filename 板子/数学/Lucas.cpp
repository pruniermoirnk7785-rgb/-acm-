#include <bits/stdc++.h>
using namespace std;
using ll=long long;
const int MAXN=1e5+5;
ll fact[MAXN],invFact[MAXN];

ll qpow(ll a,ll b, ll p) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}
void init(int p) {
    fact[0] = 1;
    for (int i = 1; i < p; i++) {
        fact[i] = fact[i-1] * i % p;
    }
    invFact[p-1] = qpow(fact[p-1], p - 2, p); // 费马小定理求逆元
    for (int i = p-2; i >= 0; i--) {
        invFact[i] = invFact[i+1] * (i+1) % p;
    }

}
ll C(ll n, ll m,ll p) {
    if (m < 0 || m > n) return 0;
    return fact[n] * invFact[m] % p * invFact[n-m] % p;
}
// Lucas定理：C(n, m) % p = C(n%p, m%p) * C(n/p, m/p) % p
ll lucas(ll n, ll m, ll p) {
    if (m == 0) return 1;
    return C(n % p, m % p, p) * lucas(n / p, m / p, p) % p;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        ll n,m,p;
        cin>>n>>m>>p;
        init(p);
        cout<<lucas(n+m,n,p)<<"\n";
    }
    return 0;
}