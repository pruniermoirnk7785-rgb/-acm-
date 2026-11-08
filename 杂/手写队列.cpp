#include<iostream>
using namespace std;
struct myqueue
{
    int q[100000];
    int head,tail;
    void init()
    {head=0;tail=-1;}
    int size()
    {return tail-head+1;}
    void push(int data) {q[++tail]=data;}
    int front(){return q[head];}
    void pop(){head++;}
} q;
int main()
{
    q.init();
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        q.push(i);
    }
    while(q.size()>0){
        for(int i=1;i<m;i++){
            q.push(q.front());
            q.pop();
        }
        cout<<q.front()<<" ";
        q.pop();
    }
    return 0;
}