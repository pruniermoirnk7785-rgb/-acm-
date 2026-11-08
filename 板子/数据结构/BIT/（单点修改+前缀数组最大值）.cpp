#include <bits/stdc++.h>
using namespace std;
struct BIT_with_premax
{
   int n;
   vector<int> tree;
   BIT_with_premax(int sz){
        n=sz;
        tree.assign(n+2,0);
   }
   int lowbit(int x){
    return x&-x;
   }
   void update(int pos,int val){
    while(pos<=n){
        tree[pos]=max(tree[pos],val);
        pos+=lowbit(pos);
    }
   }
   int query(int pos){
    int res=0;
    while(pos>0){
        res=max(res,tree[pos]);
        pos-=lowbit(pos);
    }
    return res;
   }
};
int main(){
    int n;
    cin>>n;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    BIT_with_premax bit(n);
    int mx=0;
    for(int i=1;i<=n;i++){
        int best=bit.query(a[i]-1);
        int nval=best+1;
        bit.update(a[i],nval);
    }
    int ans=bit.query(n);
    cout<<ans<<endl;
    return 0;
}