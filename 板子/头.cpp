#include <bits/stdc++.h>
using namespace std;

using ll=long long;
using ull=unsigned long long;
using i128=__int128;
using ld=long double;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using pil=pair<int,ll>;

const ll mod=998244353;
//const ll mod=1e9+7;
const ll INF=(ll)2e18;
const double eps=1e-8;
const double PI=acos(-1);
const ll LLMIN=LLONG_MIN;   // -9223372036854775808
const ll LLMAX=LLONG_MAX;   //  9223372036854775807

#define pb push_back
#define elif else if
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define fi first
#define se second
#define pq priority_queue
#define um unordered_map
#define us unordered_set
#define endl "\n"                   //交互题注释掉

#define debug(x) cerr << #x << ": " << x << '\n';

template <typename T>
void printEl(const T&x){
    cerr<<x;
}
template <typename A,typename B>
void printEl(const pair<A,B>&p){
    cerr<<'('<<p.first<<','<<p.second<<')';
}
template <typename C>
void printC(const C&c,const string&sep=" ") {
    int i=0;
    for (auto&x:c) {
        printEl(x);
        cerr<<(++i==c.size()?"\n":sep);
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

//以下是pbds库，按需开启
#include <bits/extc++.h>
using namespace __gnu_pbds;
#define gpum gp_hash_table //注意没有cend cbegin emplace
#define ccum cc_hash_table //时间复杂度1.5-4倍，空间复杂度8倍，一般没人用
using ordered_set= tree<
    int, // key类型
    null_type, //映射类型，填null_type表示这是set
    std::less<int>, //比较函数
    rb_tree_tag, //底层使用红黑树，一般用这个
    tree_order_statistics_node_update //启用按排名查询,不启用是null_node_update（默认）
>;
//目前感觉就这俩货有用

void solve(){
    
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