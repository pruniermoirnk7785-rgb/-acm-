#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// =====================================================================
// 带权线性基（bitset 掩码 + 值域异或）· 判断异或和是否唯一确定
// ---------------------------------------------------------------------
// 适用场景：
//   给定若干条"等式约束"，形如：xor_{j in mask} x_j = val
//   （mask 是变量集合的 bitset，val 是该集合的异或和）
//   多次询问：xor_{j in qmask} x_j 是否被唯一确定？
//             唯一确定则输出该异或和，否则输出 -1。
//
// 原题背景：
//   若干条链，每条链有一个长度 L 和 SG 值 S；已知某些"链长集合"的
//   SG 异或和，询问任意"链长集合"的 SG 异或和能否由已知条件唯一推出。
//   （L <= 100，因此用 bitset<128> 表示链长集合）
//
// 原理：
//   把每个等式看成 GF(2) 上的行向量 (mask | val)，对 mask 部分做线性基
//   （高斯消元）。消元时 val 必须跟随 mask 做完全相同的行操作（同步异或），
//   这样基向量本身就携带了"该行组合对应的右端值"。
//   基向量之间线性无关，所以若某个 qmask 能被基向量组合出来，组合系数唯一，
//   对应的 val 异或和也唯一，它就是答案；组合不出来（消不到 0）则返回 -1。
//
// 复杂度：插入 / 查询均为 O(MAXB^2 / 64)（bitset 按机器字并行运算，实际接近 O(MAXB)）
// 使用注意：MAXB 按变量个数上限修改；变量下标从 0 开始（输入时减 1）。
// =====================================================================

constexpr int MAXB = 128;   // 变量个数上限（原题 L<=100，128 留余量）

struct Node {
    bitset<MAXB> mask;      // 基向量的掩码部分：由哪些变量组成
    ll val;                 // 基向量的值部分：该组合对应的异或和
};

Node basis[MAXB];           // basis[i]：主元位（最高位）为 i 的基向量
bool has[MAXB];             // has[i]：主元位为 i 的基向量是否存在

// 插入一条等式：xor_{j in mask} x_j = val
void ins(bitset<MAXB> mask, ll val) {
    for (int i = MAXB - 1; i >= 0; i--) {   // 从高到低逐位消元
        if (!mask.test(i)) continue;        // 当前位为 0，跳过
        if (!has[i]) {                      // 该位还没有基向量 -> 作为新基存入
            basis[i] = {mask, val};
            has[i] = true;
            return;
        }
        mask ^= basis[i].mask;              // 用主元位为 i 的基向量消去当前最高位
        val ^= basis[i].val;                // 值部分必须同步异或（保持行操作一致）
    }
    // mask 被消成 0：说明该等式是已有等式的线性组合，不增加秩，直接丢弃
}

// 询问：xor_{j in mask} x_j 是否唯一确定？
// 唯一确定 -> 返回该异或和；无法确定 -> 返回 -1
ll query(bitset<MAXB> mask) {
    ll res = 0;
    for (int i = MAXB - 1; i >= 0; i--) {
        if (!mask.test(i)) continue;
        if (!has[i]) return -1;             // 该位没有基向量 -> 不在张成空间内，无法确定
        mask ^= basis[i].mask;              // 消去当前最高位
        res ^= basis[i].val;                // 累加对应的值
    }
    // mask 已消成 0：表示组合唯一，res 即为唯一确定的异或和
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--) {
        fill(has, has + MAXB, false);       // 清空线性基（basis 无需清，has 决定是否有效）
        int K;
        cin >> K;                           // K：已知等式的个数
        while (K--) {
            int C;
            ll S;
            cin >> C >> S;                  // C：集合中变量的个数；S：该集合的异或和（用 ll 读防溢出）
            bitset<MAXB> mask;
            for (int j = 0; j < C; j++) {
                int L;
                cin >> L;
                mask.flip(L - 1);           // 变量下标从 0 开始；同一变量出现两次自动抵消（异或）
            }
            ins(mask, S);                   // 插入等式
        }
        int Q;
        cin >> Q;                           // Q：询问次数
        while (Q--) {
            int D;
            cin >> D;                       // D：询问集合中变量的个数
            bitset<MAXB> mask;
            for (int j = 0; j < D; j++) {
                int R;
                cin >> R;
                mask.flip(R - 1);           // 构造询问集合
            }
            cout << query(mask) << '\n';    // 唯一确定输出异或和，否则 -1
        }
    }
    return 0;
}