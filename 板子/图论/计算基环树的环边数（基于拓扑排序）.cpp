#include <bits/stdc++.h>
using namespace std;
using ll=long long ;
struct NDtable
{
    int n;
    vector<vector<ll>> g;
    NDtable(int sz):n(sz),g(n+1){}
    void addEdge(int a,int b){
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int getCycleSize(){
        vector<int> deg(n+1,0);
        vector<bool> del(n+1,false);
        queue<int> q;
        for(int i=1;i<=n;i++){
            deg[i]=g[i].size();
            if(deg[i]==1) q.push(i);
        }
        while(!q.empty()){
            int u=q.front();
            q.pop();
            if(del[u]) continue;
            del[u]=true;
            for(int v:g[u]){
                if(!del[v]){
                    deg[v]--;
                    if(deg[v]==1) q.push(v);
                }
            }
        }
        int c=0;
        for(int i=1;i<=n;i++){
            if(!del[i]) c++;
        }
        return c;
    }
};
int main(){
    int n;
    cin>>n;
    NDtable ndtable(n);
    for(int i=1;i<=n;i++){
        int a,b;
        cin>>a>>b;
        ndtable.addEdge(a,b);
    }
    cout<<ndtable.getCycleSize()<<endl;
}
