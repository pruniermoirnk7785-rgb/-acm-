#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define pb push_back
#define elif else if
const int mod=998244353;
//const int mod=1e9+7
const ll INF=2e18;
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define fi first
#define se second
#define p_q priority_queue
#define u_m unordered_map
#define endl "\n"
#define pi acos(-1)

// const int dx[4] = {-1, 1, 0, 0};
// const int dy[4] = {0, 0, -1, 1};
// const int dx[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
// const int dy[8] = {1, 1, 1, 0, -1, -1, -1, 0};
// const int dx[12] = {-1, 0, 1, 1, 1, 0, -1, -1, 0, 2, -2, 0};
// const int dy[12] = {1, 1, 1, 0, -1, -1, -1, 0, 2, 0, 0, -2};
const int N=6010;
int n,happy[N];
vector<int> g[N];
bool hasParent[N];
int dp[N][2];
void dfs(int u){
    dp[u][1]=happy[u];
    for(int v:g[u]){
        dfs(v);
        dp[u][1]+=dp[v][0];
        dp[u][0]+=max(dp[v][0],dp[v][1]);
    }
}

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>happy[i];
    for(int i=1;i<n;i++){
        int l,k;
        cin>>l>>k;
        g[k].push_back(l);
        hasParent[l]=true;
    }
    int root=1;
    while(hasParent[root]) root++;
    dfs(root);
    cout<<max(dp[root][0],dp[root][1]);
}
int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    int t=1;
    // cin>>t;
    while(t--){
        solve();
    }
    return 0;
}