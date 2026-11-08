#include <bits/stdc++.h>
using namespace std;
using ll=long long ;
const int maxn=2e5+5;
struct  Node{
    ll xorsum;
};
Node tree[maxn<<2];
int a[maxn];
void init(Node &node,int val){
    node.xorsum=val;
}
Node pushup(const Node &L,const Node &R){
    Node M;
    M.xorsum=L.xorsum^R.xorsum;
    return M;
}
void build(int u,int l,int r){
    if(l==r){
        init(tree[u],a[l]);
        return ;
    }
    int mid=l+((r-l)>>1);
    build(u<<1,l,mid);
    build(u<<1|1,mid+1,r);
    tree[u]=pushup(tree[u<<1],tree[u<<1|1]);
}
void update(int u,int l,int r,int p,int val){
    if(l==r){
        init(tree[u],val);
        return ;
    }
    int mid=l+((r-l)>>1);
    if(p<=mid){
        update(u<<1,l,mid,p,val);
    }
    else{
        update(u<<1|1,mid+1,r,p,val);
    }
    tree[u]=pushup(tree[u<<1],tree[u<<1|1]);
}
Node query(int u,int l,int r,int ql,int qr){
    if(ql<=l and r<=qr){
        return tree[u];
    }
    int mid=l+((r-l)>>1);
    if (qr<=mid) return query(u<<1,l,mid,ql,qr);
    if(ql>mid) return query(u<<1|1,mid+1,r,ql,qr);
    return pushup(query(u<<1,l,mid,ql,qr),query(u<<1|1,mid+1,r,ql,qr));
}
void solve(){
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    build(1,1,n);
    while(q--){
        int op;
        cin>>op;
        if(op==1){
            int p,x;
            cin>>p>>x;
            update(1,1,n,p,x);
        }
        else{
            int l,r;
            cin>>l>>r;
            Node res=query(1,1,n,l,r);
            cout<<res.xorsum<<"\n";
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}