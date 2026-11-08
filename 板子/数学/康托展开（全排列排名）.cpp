#include <bits/stdc++.h>
using namespace std;
using ll=long long ;
const int N=1e6+5;
const int mod=998244353;
//const int mod=1e9+7;
struct BIT{
    int n;
    vector<int> tree;
    BIT(int sz):n(sz),tree(sz+1,0){}
    void add(int i,int d){
        for(;i<=n;i+=i&-i) tree[i]+=d;
    }
    ll query(int i){
        ll sum=0;
        for(;i>0;i-=i&-i) sum+=tree[i];
        return sum;
    }
};
ll fact[N];
void init(){
    fact[0]=1;
    fact[1]=1;
    for(int i=2;i<=N-5;i++){
        fact[i]=fact[i-1]*i%mod;
    }
}
ll cantor(const vector<int> &p){
    int n=p.size();
    BIT bit(n);
    for(int i=1;i<=n;i++) bit.add(i,1);
    ll rank=0;
    for(int i=0;i<n;i++){
        int cur_i=bit.query(p[i]-1);
        rank=(rank+cur_i*fact[n-1-i])%mod;
        bit.add(p[i],-1);
    }
    return (rank+1)%mod;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin>>n;
    init();
    vector<int> a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    cout<<cantor(a);
    return 0;
}
