#include <bits/stdc++.h>
using namespace std;

using ll=long long;
using ull=unsigned long long;
using lll=__int128;
using ld=long double;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using pil=pair<int,ll>;
using tlll=tuple<ll,ll,ll>;

const ll mod=998244353;
//const ll mod=1e9+7
const ll INF=2e18;
const double eps=1e-8;

#define pb push_back
#define elif else if
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define fi first
#define se second
#define p_q priority_queue
#define u_m unordered_map
#define u_s unordered_set
#define endl "\n"
#define pi acos(-1)

#define debug(x) cerr << #x << ": " << x << '\n';
template <typename C>
void printC(const C&c,const string&sep=" ") {
    int i=0;
    for (auto&x:c) {
        cout<<x<<(++i==c.size()?"\n":sep);
    }
}

#define ctz __builtin_ctzll         // 返回二进制表示中末尾连续0的个数
#define clz __builtin_clzll         // 返回二进驻表示中先导0的个数
#define count1 __builtin_popcountll // 返回二进制表示中1的个数
// 上面仨不是ll的时候记得调整

// const int dx[4] = {-1, 1, 0, 0};
// const int dy[4] = {0, 0, -1, 1};
// const int dx[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
// const int dy[8] = {1, 1, 1, 0, -1, -1, -1, 0};
// const int dx[12] = {-1, 0, 1, 1, 1, 0, -1, -1, 0, 2, -2, 0};
// const int dy[12] = {1, 1, 1, 0, -1, -1, -1, 0, 2, 0, 0, -2};
const int maxn=2e5+5;
struct  Node{
    ll cnt;
    int lc,rc;
    int lazy;
    bool rev;
};
Node tree[maxn<<2];
int a[maxn];
void init(Node &node,int val){
    node.cnt=0;
    node.lc=node.rc=val;
    node.lazy=-1;
    node.rev=false;
}
Node pushup(const Node &L,const Node &R){
    Node M;
    M.cnt=L.cnt+R.cnt;
    if(L.rc!=R.lc) M.cnt++;
    M.lc=L.lc;
    M.rc=R.rc;
    M.lazy=-1;
    M.rev=false;
    return M;
}
void apply(int u,int l,int r,int val){
    tree[u].cnt=0;
    tree[u].lc=tree[u].rc=val;
    tree[u].lazy=val;
    tree[u].rev=false;
}
void reverse(int u,int l,int r){
    tree[u].lc^=1;
    tree[u].rc^=1;
    if(tree[u].lazy!=-1){
        tree[u].lazy^=1;
    }
    else{
        tree[u].rev=!tree[u].rev;
    }
}
void pushdown(int u,int l,int r){
    if (l==r) return;
    int mid=l+((r-l)>>1);
    if(tree[u].lazy!=-1){
        apply(u<<1,l,mid,tree[u].lazy);
        apply(u<<1|1,mid+1,r,tree[u].lazy);
        tree[u].lazy=-1;
    }
    if(tree[u].rev){
        reverse(u<<1,l,mid);
        reverse(u<<1|1,mid+1,r);
        tree[u].rev=false;
    }
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
void update1(int u,int l,int r,int ql,int qr,int val){
    if(ql<=l and r<=qr){
        apply(u,l,r,val);
        return ;
    }
    pushdown(u,l,r);
    int mid=l+((r-l)>>1);
    if(ql<=mid){
        update1(u<<1,l,mid,ql,qr,val);
    }
    if(qr>mid){
        update1(u<<1|1,mid+1,r,ql,qr,val);
    }
    tree[u]=pushup(tree[u<<1],tree[u<<1|1]);
}
void update2(int u,int l,int r,int ql,int qr){
    if(ql<=l and r<=qr){
        reverse(u,l,r);
        return ;
    }
    pushdown(u,l,r);
    int mid=l+((r-l)>>1);
    if(ql<=mid){
        update2(u<<1,l,mid,ql,qr);
    }
    if(qr>mid){
        update2(u<<1|1,mid+1,r,ql,qr);
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
    memset(tree,0,sizeof(tree));
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
            int l,r,x;
            cin>>l>>r>>x;
            update1(1,1,n,l,r,x);
        }
        elif(op==2){
            int l,r;
            cin>>l>>r;
            update2(1,1,n,l,r);
        }
        else{
            int l,r;
            cin>>l>>r;
            cout<<query(1,1,n,l,r).cnt<<endl;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int t=1;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}