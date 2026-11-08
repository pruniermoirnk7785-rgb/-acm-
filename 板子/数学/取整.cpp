#include <bits/stdc++.h>
using namespace std;
enum class RoundMode { FLOOR, CEIL };

int divide(int a, int b, RoundMode mode) {
    if (b == 0) throw invalid_argument("除数不能为0");
    
    // 统一分母为正数，调整分子符号
    if (b < 0) {
        a = -a;
        b = -b;
    }
    
    int q = a / b;           // 整数除法（向零取整）
    int r = a % b;           // 余数，符号与 a 相同
    
    if (mode == RoundMode::FLOOR) {
        // 下取整：当结果为负且有余数时，需要减1
        if (r != 0 && a < 0) q--;
    } else { // CEIL
        // 上取整：当结果为正且有余数，或者为负但余数不为0时
        if (r != 0 && a > 0) q++;
        // 注意：a为负时，整数除法已经向零取整，上取整需要保持
        // 但若余数不为0，实际上 ceil(-1.3) = -1，而 q = -1，已经正确
    }
    
    return q;
}


int main() {
    // 下取整
    cout << divide(5, 2, RoundMode::FLOOR) << endl;   // 2
    cout << divide(-5, 2, RoundMode::FLOOR) << endl;  // -3
    cout << divide(5, -2, RoundMode::FLOOR) << endl;  // -3
    
    // 上取整
    cout << divide(5, 2, RoundMode::CEIL) << endl;    // 3
    cout << divide(-5, 2, RoundMode::CEIL) << endl;   // -2
    cout << divide(5, -2, RoundMode::CEIL) << endl;   // -2
    
    return 0;
}