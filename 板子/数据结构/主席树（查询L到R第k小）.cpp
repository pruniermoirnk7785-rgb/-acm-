#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

struct PresidentTree {
    static constexpr int N = 2e5 + 10;
    int cntNodes, root[N];
    struct node {
        int l, r;
        int cnt;
    } tr[4 * N + 17 * N];
    void modify(int &u, int v, int l, int r, int x) {
        u = ++cntNodes;
        tr[u] = tr[v];
        tr[u].cnt++;
        if (l == r) return;
        int mid = (l + r) / 2;
        if (x <= mid)
            modify(tr[u].l, tr[v].l, l, mid, x);
        else
            modify(tr[u].r, tr[v].r, mid + 1, r, x);
    }
    int kth(int u, int v, int l, int r, int k) {
        if (l == r) return l;
        int res = tr[tr[v].l].cnt - tr[tr[u].l].cnt;
        int mid = (l + r) / 2;
        if (k <= res)
            return kth(tr[u].l, tr[v].l, l, mid, k);
        else
            return kth(tr[u].r, tr[v].r, mid + 1, r, k - res);
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,q;
    cin>>n>>q;
    vector<int> a(n+1);
    vector<int> nums; // 存离散化后的排名
    for(int i=1;i<=n;i++){
        cin>>a[i];
        nums.push_back(a[i]);
    }
    //离散化两步走
    sort(nums.begin(),nums.end());
    nums.erase(unique(nums.begin(),nums.end()),nums.end());

    PresidentTree pt;
    pt.cntNodes=0;//重置计数器

    int sz=nums.size();
    for(int i=1;i<=n;i++){
        
        int rank=lower_bound(nums.begin(),nums.end(),a[i])-nums.begin()+1;
        pt.modify(pt.root[i],pt.root[i-1],1,sz,rank);
    }
    while(q--){
        int L,R;
        cin>>L>>R;
        //以中位数为例子
        int len=R-L+1;
        int k=(len+1)/2;
        int rank=pt.kth(pt.root[L-1],pt.root[R],1,sz,k);
        cout<<nums[rank-1]<<endl;
    }
    return 0;
}