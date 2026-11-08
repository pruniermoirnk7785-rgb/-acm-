#include <bits/stdc++.h>
using namespace std;
using ll=long long ;
int main(){
    cout<<"5^9="<<(5^9)<<endl;
    cout<<"5*9="<<((5+9)-(5^9))<<endl;
    ll ans=0;
    for(int k=1;k<=63;k++){
        ans+=((k+45)-(k^45));
    }
    cout<<ans<<endl;
}