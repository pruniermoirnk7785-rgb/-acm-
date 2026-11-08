#include <bits/stdc++.h>
using namespace std;
using ll=long long ;
struct BIT{
    int n;
    vector<ll> tree;
    BIT(int size):n(size),tree(size+1,0){}
    int lowbit(int x){
        return x&-x;
    }
    void add(int x,ll k){
        while(x<=n){
            tree[x]+=k;
            x+=lowbit(x);
        }
    }
    ll query(int x){
        ll sum=0;
        while(x>0){
            sum+=tree[x];
            x-=lowbit(x);
        }
        return sum;
    }
};
struct BIT_range{
    int n;
    BIT B1,B2;
    BIT_range(int size):n(size),B1(size),B2(size){}
    void rangeAdd(int l, int r, ll k) {
        B1.add(l,k);
        B1.add(r+1,-k);
        B2.add(l,k*(l-1));
        B2.add(r+1,-k*r);
    }
    ll presum(int x){
        return B1.query(x)*x-B2.query(x);
    }
    ll rangequery(int l,int r){
        return presum(r)-presum(l-1);
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,q;
    cin>>n>>q;
    BIT_range bit(n);
    for(int i=1;i<=n;i++){
        ll a;
        cin>>a;
        bit.rangeAdd(i,i,a);
    }
    while(q--){
        int op;
        cin>>op;
        if(op==1){
            int l,r,k;
            cin>>l>>r>>k;
            bit.rangeAdd(l,r,k);
        }
        else{
            int l,r;
            cin>>l>>r;
            cout<<bit.rangequery(l,r)<<endl;
        }
    }
    return 0;
}