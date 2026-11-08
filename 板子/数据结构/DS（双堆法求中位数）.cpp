#include <bits/stdc++.h>
using namespace std;
using ll=long long ;
struct DS{
    multiset<int> q1,q2;
    ll sum1=0,sum2=0;
    void balance(){
        //q1最多比q2多1个
        while(q1.size()>q2.size()+1){
            int val=*q1.rbegin();
            q1.erase(--q1.end());
            q2.insert(val);
            sum1-=val;
            sum2+=val;
        }
        //q2不能比q1大
        while(q2.size()>q1.size()){
            int val=*q2.begin();
            q2.erase(q2.begin());
            q1.insert(val);
            sum1+=val;
            sum2-=val;
        }
        //保证q1的所有元素都小于等于q2的
        while(!q1.empty() and !q2.empty() and *q1.rbegin()>*q2.begin()){
            int big=*q1.rbegin();
            int small=*q2.begin();
            q1.erase(--q1.end());
            q2.erase(q2.begin());
            q1.insert(small);
            q2.insert(big);
            sum1+=(small-big);
            sum2+=(big-small);
        }
    }
    void add(int x){
        if(q1.empty()||x<=*q1.rbegin()){
            q1.insert(x);
            sum1+=x;
        }
        else{
            q2.insert(x);
            sum2+=x;
        }
        balance();
    }
    void del(int x){
        auto it=q1.find(x);
        if(it!=q1.end()){
            q1.erase(it);
            sum1-=x;
        }
        else{
            auto it2=q2.find(x);
            if(it2!=q2.end()){
                q2.erase(it2);
                sum2-=x;
            }
        }
        balance();
    }
    //查询中位数两倍
    ll query(){
        if(q1.empty()) return 0;
        if(q1.size()>q2.size()){
            return 2LL*(*q1.rbegin());
        }
        return 1LL*(*q1.rbegin()+*q2.begin());
    }
};
//todo：sum1和sum2只是记录了q1 q2的总和，目前还没有用
//可以用于求中位数附近k个数的和
//可以用于求所有小于中位数的数的和
//反正目前还没有写以后拓展用的