#include <bits/stdc++.h>
using namespace std;
// int / unsigned int 使用函数不带后缀
// long / unsigned long 带l
// long long / unsigned long long 带ll
// 1. 查找 "1" 的位置
long long x;
int ctz=__builtin_ctzll(x);   // 返回末尾连续0的个数（从低位开始数）
int clz=__builtin_clzll(x);   // 返回开头连续0的个数（从高位开始数）
int ffs=__builtin_ffsll(x);   // 返回最低位'1'的位置（从1开始计数），x=0时返回0
int hbp=63-clz;               // 返回最高位'1'的位置（从1开始计数）
// 2. 统计 "1" 的个数
int popcount=__builtin_popcountll(x);   // 返回二进制中1的总数
int parity=__builtin_parityll(x);     // 返回1的个数的奇偶性（1=奇数个，0=偶数个）
// 3. 字节序操作
// __builtin_bswap64(x);   // 64位字节序反转（高低位互换）
// __builtin_bswap32(x);   // 32位字节序反转
// __builtin_bswap16(x);   // 16位字节序反转
// 4. 按位反转
// __builtin_bitreverse64(x)   // 按位反转（GCC 12+ 支持）
// __builtin_bitreverse32(x)   // 32位按位反转
// __builtin_bitreverse16(x)   // 16位按位反转