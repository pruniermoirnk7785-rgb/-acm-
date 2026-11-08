#include <bits/stdc++.h>
using namespace std;
using ll=long long ;
const int mod=998244353;
const int G=3;//mod的原根
const int G_inv=332748118;
const int maxn=3e6+5;
ll a[maxn],b[maxn];
int rev[maxn];//二进制下要反转的位置

ll qpow(ll a, ll b){
    ll res=1;
    while(b){
        if(b&1) res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}
//f:系数矩阵，lim:变换长度，type:操作 1是正向-1是逆向
void ntt(ll *f,int lim,int type){
    for(int i=0;i<lim;i++){
        if(i<rev[i]) swap(f[i],f[rev[i]]);
    }
    for(int mid=1;mid<lim;mid<<=1){
        ll wn=qpow(type==1?G:G_inv,(mod-1)/(mid<<1));
        for(int j=0;j<lim;j+=(mid<<1)){
            ll w=1;
            for(int k=0;k<mid;k++){
                int x=f[j+k];
                int y=w*f[j+k+mid]%mod;
                f[j+k]=(x+y)%mod;
                f[j+k+mid]=(x-y+mod)%mod;
                w=w*wn%mod;
            }
        }
    }
    if(type==-1){
        ll inv_lim=qpow(lim,mod-2);
        for(int i=0;i<lim;i++){
            f[i]=f[i]*inv_lim%mod;
        }
    }
}
//l是2进制位数
void init(ll lim,ll l){
    for(int i=0;i<lim;i++){
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
    }
}
int main() {
    int n, m;
    cin >> n >> m;   // 多项式 A 有 n+1 项，B 有 m+1 项
    for (int i = 0; i <= n; i++) cin >> a[i];
    for (int i = 0; i <= m; i++) cin >> b[i];

    
    // 1. 求变换长度 lim = 2^l >= n+m+1
    int lim = 1, l = 0;
    while (lim < n + m + 1) {
        lim <<= 1;
        l++;
    }//lim必须是2的倍数

    // 2. 初始化 rev 数组
    init(lim, l);

    // 3. 把 A 和 B 补零到 lim 长度
    // （如果 a、b 是分开的数组，这里要保证长度一致）

    // 4. 正向 NTT
    ntt(a, lim, 1);
    ntt(b, lim, 1);

    // 5. 频域逐点相乘
    for (int i = 0; i < lim; i++) a[i] = a[i] * b[i] % mod;

    // 6. 逆 NTT
    ntt(a, lim, -1);

    // 7. a[0..n+m] 就是乘积的系数
    for (int i = 0; i <= n + m; i++) cout << a[i] << " ";
}