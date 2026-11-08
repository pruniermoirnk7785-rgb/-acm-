#include <bits/stdc++.h>
using namespace std;
using ll=long long ;
const int maxn=2e5+5;
struct  Node{
    ll sum;
    ll lazy;
};
Node tree[maxn<<2];
ll a[maxn];
void init(Node &node,ll val){
    node.sum=val;
    node.lazy=0;
}
Node pushup(const Node &L,const Node &R){
    Node M;
    M.sum=L.sum+R.sum;
    M.lazy=0;
    return M;
}
void pushdown(int u,int l,int r){
    if(tree[u].lazy==0) return ;
    int mid=l+((r-l)>>1);
    tree[u<<1].sum+=tree[u].lazy*(mid-l+1);
    tree[u<<1].lazy+=tree[u].lazy;
    tree[u<<1|1].sum+=tree[u].lazy*(r-mid);
    tree[u<<1|1].lazy+=tree[u].lazy;
    tree[u].lazy=0;
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
void update(int u,int l,int r,int ql,int qr,ll val){
    if(ql<=l and r<=qr){
        tree[u].sum+=1LL*val*(r-l+1);
        tree[u].lazy+=val;
        return ;
    }
    pushdown(u,l,r);
    int mid=l+((r-l)>>1);
    if(ql<=mid){
        update(u<<1,l,mid,ql,qr,val);
    }
    if(qr>mid){
        update(u<<1|1,mid+1,r,ql,qr,val);
    }
    tree[u]=pushup(tree[u<<1],tree[u<<1|1]);
}
Node query(int u,int l,int r,int ql,int qr){
    if(ql<=l and r<=qr){
        return tree[u];
    }
    pushdown(u,l,r);
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
            ll l,r,x;
            cin>>l>>r>>x;
            update(1,1,n,l,r,x);
        }
        else{
            int l,r;
            cin>>l>>r;
            Node res=query(1,1,n,l,r);
            cout<<res.sum<<"\n";
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t=1;
    // cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
