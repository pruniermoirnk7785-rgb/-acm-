#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 外围声明（按题修改）：
const int N = 105;
const double eps = 1e-8;

// =====================================================================
// 高斯消元（异或方程组）· 片段（无 main）
// 说明：系数矩阵就是正常的高斯消元（选主元、换行、归一、消元），
//       只是这题答案（常数项）只有 0/1，所以答案部分用了异或来实现，
//       这只是本题的特殊形式，随时可以改成普通的加减消元。
// 返回值：0 唯一解（解在 a[i][n]）；1 无穷多解；2 无解。
// =====================================================================

ll n=105;
int a[N][N];
int num[105];
ll gauss(){
    ll c, r;
    for (c = 0, r = 0; c < n; c ++ )//c为列，r是遍历存在主元的行
    {
        ll t = r;//t是绝对值最大的那行，把他放到当前第r行
        for (int i = r; i < n; i ++ )    //找到绝对值最大的行 
            if (fabs(a[i][c]) > fabs(a[t][c]))
                t = i;
        if (fabs(a[t][c]) < eps) continue;
        swap(num[t],num[r]);
        for (int j = c; j < n + 1; j ++ )  swap(a[t][j], a[r][j]);    //将绝对值最大的一行换到最顶端
        for (int j = n; j >= c; j -- ) a[r][j] /= a[r][c];    //将当前行首位变成 1
        for (int i = 0; i < n ; i ++ )    //将下面列消成 0 
        {
            if(i==r) continue;
            if (fabs(a[i][c]) > eps)
            {
                for(int j=0;j<a[i][c];j++) num[i]^=num[r];
                for (int j = n; j >= c; j -- )
                {
                    a[i][j] -= a[r][j] * a[i][c];
                    a[i][j]=(a[i][j]+2)%2;
                }
                    
            }
                
        }
            
        r ++ ;
    }
    if (r < n){
        for (int i = r; i < n; i ++ )
            if (fabs(a[i][n]) > eps)
                return 2;
        return 1;
    }
    for (int i = n - 1; i >= 0; i -- )
        for (int j = i + 1; j < n; j ++ )
            a[i][n] -= a[i][j] * a[j][n];
    return 0;
}