#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

// =====================================================================
// 线性基（异或空间）· 求最大异或和 / 求最小异或和 / 判断能否表示
// ---------------------------------------------------------------------
// 原理：
//   把 n 个数看成 GF(2) 上的二进制向量，对它们做高斯消元，得到一组
//   "主元位"（最高位）互不相同的基 b[i]，其中 b[i] 的最高位恰为 i。
//   于是这 n 个数的所有子集异或和，与这组基的所有子集异或和完全相同。
//   （消元时只做异或，不做加减，因此必定能在 GF(2) 上完成）
//
// 三个查询：
//   1) 最大异或和：从高位到低位贪心，若 res ^ b[i] 比 res 大就异或上。
//   2) 最小异或和：取非空子集的最小值。若插入过程中有数被消成 0，
//      说明 rank < n，存在异或和为 0 的组合，答案是 0；
//      否则答案是主元位最低的那个基向量 b[p]
//      （任何包含更高主元位基向量的子集，值都 >= 2^{p+1} > b[p]）。
//   3) 能否表示 x：从高位到低位用基把 x 的 1 消掉，能消成 0 就可以。
//
// 复杂度：单次插入 / 查询 O(MAXB)，建整组 O(n · MAXB)，空间 O(MAXB)。
//
// 使用注意：
//   * 本模板按"非负整数"设计，值域 0 .. 2^63-1。
//     若需要 unsigned 全 64 位，把 MAXB 改成 64 即可。
//     负数（补码）的最高位语义不同，不要直接当无符号数喂进来。
//   * 求"第 k 小异或和"需要先把基化成行最简形式（消掉高位对低位的干扰），
//     再按 k 的二进制位从低位往高位组合，本文件未包含，按需再加。
//   * 数组里有重复元素 / 有 0 元素都能正常处理（只会让 zero 变成 true）。
// =====================================================================

constexpr int MAXB = 63;   // 值域 [0, 2^63)

struct XorBasis {
    ull b[MAXB] = {};   // b[i]：主元位（最高位）为 i 的基向量，0 表示该位没有基
    int cnt = 0;        // 秩：基向量个数
    bool zero = false;  // 是否存在"若干个数异或和 == 0"的组合（等价于 rank < 元素个数）

    void clear() {
        fill(b, b + MAXB, 0ULL);
        cnt = 0;
        zero = false;
    }

    // 插入一个数 x。返回 false 表示 x 已被现有基线性表示（秩没增加）
    bool insert(ull x) {
        for (int i = MAXB - 1; i >= 0; i--) {
            if (!(x >> i & 1)) continue;      // 该位为 0，跳过
            if (!b[i]) {                      // 该主元位还没占 -> 作为新基存入
                b[i] = x;
                cnt++;
                return true;
            }
            x ^= b[i];                        // 用已有基消掉这一位，继续往下
        }
        zero = true;                          // 被消成 0：存在异或和为 0 的非空组合
        return false;
    }

    // 子集异或和的最大值（空集异或和为 0，一般取至少一个数；全 0 时返回 0）
    ull queryMax() const {
        ull res = 0;
        for (int i = MAXB - 1; i >= 0; i--)
            if ((res ^ b[i]) > res) res ^= b[i];   // 这一位能变 1 就变 1
        return res;
    }

    // 非空子集异或和的最小值
    ull queryMin() const {
        if (zero) return 0;                       // 能异或出 0
        for (int i = 0; i < MAXB; i++)
            if (b[i]) return b[i];                // 主元位最低的基向量即最小非零值
        return 0;                                 // 基为空（一个数都没插入）
    }

    // x 能否由这组数异或得到
    bool canRepresent(ull x) const {
        for (int i = MAXB - 1; i >= 0; i--) {
            if (!(x >> i & 1)) continue;
            if (!b[i]) return false;              // 这一位没有基向量能消 -> 表示不出来
            x ^= b[i];
        }
        return true;                              // x 被完全消成 0
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    // 示例：n 个数，求最大 / 最小异或和；再询问 q 个数能否被表示
    int n;
    cin >> n;
    XorBasis lb;
    for (int i = 0; i < n; i++) {
        long long v;
        cin >> v;
        lb.insert((ull)v);                        // 非负；负数请先确认题意
    }

    cout << "max = " << lb.queryMax() << '\n';
    cout << "min = " << lb.queryMin() << '\n';
    cout << "rank = " << lb.cnt << '\n';

    int q;
    cin >> q;
    while (q--) {
        long long x;
        cin >> x;
        cout << (lb.canRepresent((ull)x) ? "YES" : "NO") << '\n';
    }
    return 0;
}
