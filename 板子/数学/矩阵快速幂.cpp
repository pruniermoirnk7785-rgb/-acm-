#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int mod=998244353;
//const int mod=1e9+7;

// 矩阵类型：使用二维 vector，可根据需求修改为固定大小数组以提高性能
using Matrix = vector<vector<ll>>;

// 矩阵乘法：C = A * B
Matrix matMul(const Matrix& A, const Matrix& B) {
    int n = A.size();      // A的行数
    int m = A[0].size();   // A的列数 = B的行数
    int p = B[0].size();   // B的列数
    
    Matrix C(n, vector<ll>(p, 0));
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < m; k++) {
            if (A[i][k] == 0) continue; // 小优化：跳过零元素
            for (int j = 0; j < p; j++) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
            }
        }
    }
    return C;
}

// 矩阵快速幂：计算 base^k，结果对 mod 取模
Matrix matPow(Matrix base, ll power) {
    int n = base.size();
    // 初始化结果为单位矩阵 I
    Matrix res(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++) {
        res[i][i] = 1;
    }
    
    while (power > 0) {
        if (power & 1) {
            res = matMul(res, base);
        }
        base = matMul(base, base);
        power >>= 1;
    }
    return res;
}

// 示例：斐波那契数列 F(n) 用矩阵快速幂
// [ F(n)   ]   [1 1] ^ (n-1)   [F(1)]
// [ F(n-1) ] = [1 0]         * [F(0)]
ll fibonacci(ll n) {
    if (n <= 1) return n;
    Matrix base = {{1, 1}, {1, 0}};
    Matrix result = matPow(base, n - 1);
    // result[0][0] 就是 F(n)
    return result[0][0] % mod;
}

int main() {
    // 测试：求斐波那契第 10 项
    ll n = 100000;
    cout << "F(" << n << ") = " << fibonacci(n) << endl; // 输出 55
    return 0;
}
