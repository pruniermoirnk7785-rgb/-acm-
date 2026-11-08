#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
//const int mod=998244353;
const int MAXN=1e7+5;

ll fact[MAXN],invFact[MAXN];

//快速幂
ll qpow(ll a,ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
// 求逆元：a^(p-2) mod p
ll inv(ll x) {
    return qpow(x, mod - 2);
}

// 分数取模：a/b mod p
ll fractionMod(ll a,ll b) {
    return a * inv(b) % mod;
}

// 预处理阶乘和逆元
void init(int n) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = fact[i-1] * i % mod;
    }
    invFact[n] = qpow(fact[n], mod - 2); // 费马小定理求逆元
    for (int i = n-1; i >= 0; i--) {
        invFact[i] = invFact[i+1] * (i+1) % mod;
    }

}
// 组合数 C(n, m) % mod n中取m个
ll C(int n, int m) {
    if (m < 0 || m > n) return 0;
    return fact[n] * invFact[m] % mod * invFact[n-m] % mod;
}
// 排列数 A(n, m) % mod n数排m个
ll P(int n, int m) {
    if (m < 0 || m > n) return 0;
    return fact[n] * invFact[n-m] % mod;
}

int main(){
ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
 int t;
 cin>>t;
 while(t--){
    ll n;
    cin>>n;
    ll ans=0;
    init(MAXN);
    if(n%2==1){
        ans=fractionMod(2,qpow(2,n));
    }
    else{
        ll fenzi=(2+C(n,n/2))%mod;
        ans=fractionMod(fenzi,qpow(2,n));
    }
    ans%=mod;
    cout<<ans<<"\n";
 }
}