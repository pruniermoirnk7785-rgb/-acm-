#include <bits/stdc++.h>
using namespace std;
int manacher(string &s){
    string t="#";
    for(char c:s){
        t+=c;
        t+="#";
    }
    int m=t.size();
    vector<int> p(m,0);
    int cent=0,maxr=0,maxlen=0;
    for(int i=0;i<m;i++){
        if(i<maxr){
            p[i]=min(p[2*cent-i],maxr-i);
        }
        int left=i-(p[i]+1);
        int right=i+(p[i]+1);
        while(left>=0 and right<m and t[left]==t[right]){
            p[i]++;
            left--;
            right++;
        }
        if(i+p[i]>maxr){
            cent=i;
            maxr=i+p[i];
        }
        maxlen=max(maxlen,p[i]);
    }
    return maxlen;
}
int main(){
    string s;
    cin>>s;
    cout<<manacher(s);
    return 0;
}