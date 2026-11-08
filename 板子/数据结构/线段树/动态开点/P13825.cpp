#include <bits/stdc++.h>
using namespace std;
using ll=unsigned long long ;
const int maxn=(1e5+10)*64;
struct  Node{
    ll sum;
    ll lazy;
    int lc,rc;//左右儿子
};
Node tree[maxn];
int tot=0;//建了几个点
int newNode(){
    tot++;
    tree[tot]={0,0,0,0};
    return tot;
}

ll baseSum(int l,int r){
    return (ll)(l+r)*(r-l+1)/2;
}

void add(int u,ll len, ll v){
    tree[u].sum+=v*len;
    tree[u].lazy+=v;
}

void pushup(int u){
    tree[u].sum=tree[tree[u].lc].sum+tree[tree[u].rc].sum;
}

void pushdown(int u,int l,int r){
    if(l==r || tree[u].lazy==0) return ;
    int mid=l+((r-l)>>1);
    if(!tree[u].lc) tree[u].lc=newNode();
    if(!tree[u].rc) tree[u].rc=newNode();
    add(tree[u].lc,mid-l+1,tree[u].lazy);
    add(tree[u].rc,r-mid,tree[u].lazy);
    tree[u].lazy=0;
}

void update(int &u,int l,int r,int ql,int qr,ll val){
    if(!u) u=newNode();
    if(ql<=l and r<=qr){
        add(u,r-l+1,val);
        return ;
    }
    pushdown(u,l,r);
    int mid=l+((r-l)>>1);
    if(ql<=mid) update(tree[u].lc,l,mid,ql,qr,val);
    if(qr>mid) update(tree[u].rc,mid+1,r,ql,qr,val);
    pushup(u);
}
ll query(int u,int l,int r,int ql,int qr){
    if(!u) return 0;
    if(ql<=l and r<=qr){
        return tree[u].sum;
    }
    pushdown(u,l,r);
    int mid=l+((r-l)>>1);
    ll res=0;
    if (ql<=mid) res+=query(tree[u].lc,l,mid,ql,qr);
    if(qr>mid) res+=query(tree[u].rc,mid+1,r,ql,qr);
    return res;
}
void solve(){
    int n,q;
    cin>>n>>q;
    int root=0;
    while(q--){
        int op;
        cin>>op;
        if(op==1){
            ll l,r,x;
            cin>>l>>r>>x;
            update(root,1,n,l,r,x);
        }
        else{
            int l,r;
            cin>>l>>r;
            cout<<baseSum(l,r)+query(root,1,n,l,r)<<"\n";
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
