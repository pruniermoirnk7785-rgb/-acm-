#include <bits/stdc++.h>
using namespace std;

// =====================================================================
// 高斯消元（实数方程组）· 行最简形式（RREF）
// ---------------------------------------------------------------------
// 求解 n 元线性方程组（普通加减消元，浮点）：
//   a[i][0]*x0 + a[i][1]*x1 + ... + a[i][n-1]*x_{n-1} = a[i][n]
// 输入：n 个方程 n 个未知数，增广矩阵 a[0..n-1][0..n]
// 返回值：
//   0 —— 唯一解：解存回 a[i][n]，即 x_i = a[i][n]
//   1 —— 无穷多解（秩 r < n，存在自由变量）
//   2 —— 无解（消元后出现 0 = 非0 的矛盾行）
//
// 与"只消下方行"的普通消元的区别：把主元列从【所有】行消掉，
// 最终得到行最简形式（RREF），满秩时解直接在对角线上。
// 主元按绝对值最大选取，数值稳定性更好。
// 复杂度：O(n^3)
// 注意：判 0 用 eps；n 是方程数 = 变量数，非方阵需改循环边界。
// =====================================================================

const int N = 105;          // 方程/变量个数上限（按题修改）
const double eps = 1e-8;    // 判 0 阈值

int n;                      // 变量个数 = 方程个数
double a[N][N];             // 增广矩阵：前 n 列是系数，第 n 列是常数项

// 返回 0 唯一解 / 1 无穷多解 / 2 无解
int gauss()
{
    int r = 0;                                  // 当前主元行号（同时是秩）
    for (int c = 0; c < n; c++)                 // 枚举主元列
    {
        int t = r;
        for (int i = r; i < n; i++)             // 选绝对值最大的行做主元（数值稳定）
            if (fabs(a[i][c]) > fabs(a[t][c]))
                t = i;
        if (fabs(a[t][c]) < eps) continue;      // 该列全 0：自由变量列，跳过
        for (int j = c; j <= n; j++)
            swap(a[t][j], a[r][j]);             // 主元行换到第 r 行
        for (int j = n; j >= c; j--)
            a[r][j] /= a[r][c];                 // 主元归一化为 1
        for (int i = 0; i < n; i++)             // 把主元列从【所有】行消掉（RREF）
        {
            if (i == r) continue;
            if (fabs(a[i][c]) > eps)
            {
                double k = a[i][c];             // 消元系数
                for (int j = c; j <= n; j++)
                    a[i][j] -= k * a[r][j];     // 普通加减消元：行 i -= k * 行 r
            }
        }
        r++;                                    // 处理完一个主元，秩 +1
    }
    if (r < n)                                  // 秩不足：检查是否矛盾
    {
        for (int i = r; i < n; i++)
            if (fabs(a[i][n]) > eps)
                return 2;                       // 存在 0 = 非0，无解
        return 1;                               // 有自由变量，无穷多解
    }
    return 0;                                   // 满秩：RREF 下解已在 a[i][n]（对角线上）
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    // 示例输入：
    // 3
    // 1 1 1 6
    // 1 3 2 13
    // 2 1 2 9
    // 解得 x0=2, x1=3, x2=1
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= n; j++)
            cin >> a[i][j];                     // 读增广矩阵（含常数项）
    int res = gauss();
    if (res == 2)
    {
        cout << "无解\n";
    }
    else if (res == 1)
    {
        cout << "无穷多解\n";
    }
    else
    {
        cout << fixed << setprecision(6);
        for (int i = 0; i < n; i++)
            cout << "x" << i << " = " << a[i][n] << '\n';   // 唯一解
    }
    return 0;
}