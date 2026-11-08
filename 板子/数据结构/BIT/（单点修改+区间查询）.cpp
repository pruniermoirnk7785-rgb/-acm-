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
    ll rangequery(int l,int r){
        if(l>r) return 0;
        return query(r)-query(l-1);
    }
};
int main(){
    int n,q;
    cin>>n>>q;
    BIT bit(n);
    for(int i=1;i<=n;i++){
        ll a;
        cin>>a;
        bit.add(i,a);
    }
    while(q--){
        int op;
        cin>>op;
        if(op==1){
            int i,k;
            cin>>i>>k;
            bit.add(i,k);
        }
        else{
            int l,r;
            cin>>l>>r;
            cout<<bit.rangequery(l,r)<<endl;
        }
    }
    return 0;
}