#include <bits/stdc++.h>
using namespace std;

const int N = 1e7+5; // 筛的范围（最多3e7不然会MLE）
int primes[N], cnt;     // 质数表与质数个数
bool isComp[N];         // 合数标记（false表示质数）

void eulerSieve() {
    int n=N-5;
    for (int i = 2; i <= n; i++) {
        if (!isComp[i]) primes[cnt++] = i; // i是质数
        for (int j = 0; j < cnt && 1LL * i * primes[j] <= n; j++) {
            isComp[i * primes[j]] = true;
            if (i % primes[j] == 0) break;
        }
    }
}
//遍历使用cnt作为下标（for int i=0;i<cnt;i++)