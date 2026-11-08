#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define debug(x) cerr << #x << ": " << x << '\n';
#define ctz __builtin_ctzll         // 返回二进制表示中末尾连续0的个数
#define clz __builtin_clzll         // 返回二进驻表示中先导0的个数
#define count1 __builtin_popcountll // 返回二进制表示中1的个数
// 上面仨不是ll的时候记得调整
#define lowbit(x) ((x) & -(x))
using ll = long long;
using ull = unsigned long long;
using lll = __int128;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
constexpr int N = 5e4 + 10;
constexpr double EPS = 1e-8;
// constexpr int EPS = 0;
using T = long double;
constexpr T PI = 3.1415926535897932384l;
// constexpr ll MOD = 1e9 + 7;
constexpr ll MOD = 998244353;
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;
ll dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
ll dirr[8][2] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

class card // 注意看题目里是点数在前还是花色在前
{
    public:
        int suit, rank;
        card() {}
        card(const char *p) : card(string(p)) {}
        card(string S)
        {
            string T = "__23456789TJQKA";
            for (ll i = 0; i < T.size(); i++)
                if (T[i] == S[0])
                    rank = i;
            T = "_SHCD";
            for (ll i = 0; i < T.size(); i++)
                if (T[i] == S[1])
                    suit = i;
        }
        friend bool operator<(const card &a, const card &b)
        {
            return a.rank < b.rank;
        }
        friend bool operator==(const card &a, const card &b)
        {
            return a.rank == b.rank;
        }
        friend bool operator>(const card &a, const card &b)
        {
            return a.rank > b.rank;
        }
        friend bool operator!=(const card &a, const card &b)
        {
            return a.rank != b.rank;
        }
        friend auto &operator>>(istream &it, card &C) // 重载输出
        {
            string S;
            it >> S;
            C = card(S);
            return it;
        }
};
 
class game
{
    public:
        ll level;
        vector<card> peo;
        ll a, b, c, d, e, u, v, w, x, y;
        game() {}
        bool Rk10()
        {
            sort(peo.begin(), peo.end());
            reverse(peo.begin(), peo.end());
            a = peo[0].rank, b = peo[1].rank, c = peo[2].rank, d = peo[3].rank, e = peo[4].rank;
            u = peo[0].suit, v = peo[1].suit, w = peo[2].suit, x = peo[3].suit, y = peo[4].suit;
            if (u != v || v != w || w != x || x != y)
                return 0;
            if (a == 14 && b == 13 && c == 12 && d == 11 && e == 10)
                return 1;
            return 0;
        }
        bool Dif() // 处理 A 的问题
        {
            a = peo[0].rank, b = peo[1].rank, c = peo[2].rank, d = peo[3].rank, e = peo[4].rank;
            u = peo[0].suit, v = peo[1].suit, w = peo[2].suit, x = peo[3].suit, y = peo[4].suit;
            if (a != 14 || b != 5 || c != 4 || d != 3 || e != 2)
                return 0;
            vector<card> peo2 = {peo[1], peo[2], peo[3], peo[4], peo[0]};
            peo = peo2;
            return 1;
        }
        bool Rk9()
        {
            sort(peo.begin(), peo.end());
            reverse(peo.begin(), peo.end());
            a = peo[0].rank, b = peo[1].rank, c = peo[2].rank, d = peo[3].rank, e = peo[4].rank;
            u = peo[0].suit, v = peo[1].suit, w = peo[2].suit, x = peo[3].suit, y = peo[4].suit;
            if (u != v || v != w || w != x || x != y)
                return 0;
            if (Dif())
                return 1;
            if (a == b + 1 && b == c + 1 && c == d + 1 && d == e + 1)
                return 1;
            return 0;
        }
        bool Rk8()
        {
            sort(peo.begin(), peo.end());
            a = peo[0].rank, b = peo[1].rank, c = peo[2].rank, d = peo[3].rank, e = peo[4].rank;
            u = peo[0].suit, v = peo[1].suit, w = peo[2].suit, x = peo[3].suit, y = peo[4].suit;
            if (a == b && b == c && c == d)
                return 1;
            if (b == c && c == d && d == e)
            {
                reverse(peo.begin(), peo.end());
                return 1;
            }
            return 0;
        }
        bool Rk7()
        {
            sort(peo.begin(), peo.end());
            a = peo[0].rank, b = peo[1].rank, c = peo[2].rank, d = peo[3].rank, e = peo[4].rank;
            u = peo[0].suit, v = peo[1].suit, w = peo[2].suit, x = peo[3].suit, y = peo[4].suit;
            if (a == b && b == c && d == e)
                return 1;
            if (a == b && c == d && d == e)
            {
                reverse(peo.begin(), peo.end());
                return 1;
            }
            return 0;
        }
        bool Rk6()
        {
            sort(peo.begin(), peo.end());
            reverse(peo.begin(), peo.end());
            a = peo[0].rank, b = peo[1].rank, c = peo[2].rank, d = peo[3].rank, e = peo[4].rank;
            u = peo[0].suit, v = peo[1].suit, w = peo[2].suit, x = peo[3].suit, y = peo[4].suit;
            if (u != v || v != w || w != x || x != y)
                return 0;
            return 1;
        }
        bool Rk5()
        {
            sort(peo.begin(), peo.end());
            reverse(peo.begin(), peo.end());
            a = peo[0].rank, b = peo[1].rank, c = peo[2].rank, d = peo[3].rank, e = peo[4].rank;
            u = peo[0].suit, v = peo[1].suit, w = peo[2].suit, x = peo[3].suit, y = peo[4].suit;
            if (Dif())
                return 1;
            if (a == b + 1 && b == c + 1 && c == d + 1 && d == e + 1)
                return 1;
            return 0;
        }
        bool Rk4()
        {
            sort(peo.begin(), peo.end());
            reverse(peo.begin(), peo.end());
            a = peo[0].rank, b = peo[1].rank, c = peo[2].rank, d = peo[3].rank, e = peo[4].rank;
            u = peo[0].suit, v = peo[1].suit, w = peo[2].suit, x = peo[3].suit, y = peo[4].suit;
            if (a == b && b == c)
                return 1;
            if (b == c && c == d)
            {
                swap(peo[3], peo[0]);
                return 1;
            }
            if (c == d && d == e)
            {
                swap(peo[3], peo[0]);
                swap(peo[4], peo[1]);
                return 1;
            }
            return 0;
        }
        bool Rk3()
        {
            sort(peo.begin(), peo.end());
            reverse(peo.begin(), peo.end());
            a = peo[0].rank, b = peo[1].rank, c = peo[2].rank, d = peo[3].rank, e = peo[4].rank;
            u = peo[0].suit, v = peo[1].suit, w = peo[2].suit, x = peo[3].suit, y = peo[4].suit;
            if (a == b && c == d)
                return 1;
            if (a == b && e == d)
            {
                swap(peo[2], peo[4]);
                return 1;
            }
            if (c == b && d == e)
            {
                swap(peo[2], peo[0]);
                swap(peo[4], peo[2]);
                return 1;
            }
            return 0;
        }
        bool Rk2()
        {
            sort(peo.begin(), peo.end());
            reverse(peo.begin(), peo.end());
            a = peo[0].rank, b = peo[1].rank, c = peo[2].rank, d = peo[3].rank, e = peo[4].rank;
            u = peo[0].suit, v = peo[1].suit, w = peo[2].suit, x = peo[3].suit, y = peo[4].suit;
            vector<card> peo2;
            if (a == b)
                return 1;
            if (b == c)
            {
                peo2 = {peo[1], peo[2], peo[0], peo[3], peo[4]};
                peo = peo2;
                return 1;
            }
            if (c == d)
            {
                peo2 = {peo[2], peo[3], peo[0], peo[1], peo[4]};
                peo = peo2;
                return 1;
            }
            if (d == e)
            {
                peo2 = {peo[3], peo[4], peo[0], peo[1], peo[2]};
                peo = peo2;
                return 1;
            }
            return 0;
        }
        bool Rk1()
        {
            sort(peo.begin(), peo.end());
            reverse(peo.begin(), peo.end());
            return 1;
        }
        game(vector<card> New_peo)
        {
            peo = New_peo;
            if (Rk10())
                level = 10;
            else if (Rk9())
                level = 9;
            else if (Rk8())
                level = 8;
            else if (Rk7())
                level = 7;
            else if (Rk6())
                level = 6;
            else if (Rk5())
                level = 5;
            else if (Rk4())
                level = 4;
            else if (Rk3())
                level = 3;
            else if (Rk2())
                level = 2;
            else if (Rk1())
                level = 1;
        }
        friend bool operator<(const game &a, const game &b)
        {
            if (a.level != b.level)
                return a.level < b.level;
            for (ll i = 0; i < 5; i++)
            {
                if (a.peo[i] != b.peo[i])
                    return a.peo[i] < b.peo[i];
            }
            return 0;
        }
        friend bool operator==(const game &a, const game &b)
        {
            if (a.level != b.level)
                return 0;
            for (ll i = 0; i < 5; i++)
            {
                if (a.peo[i] != b.peo[i])
                    return 0;
            }
            return 1;
        }
        friend bool operator!=(const game &a, const game &b)
        {
            return !(a == b);
        }
        friend bool operator>(const game &a, const game &b)
        {
            return !(a == b || a < b);
        }
};

void LiangBaiKai()
{

}

void Aiden()
{
    card c1, c2;
    cin >> c1 >> c2;
    cout << (c1 > c2) << endl;
    vector<card> hand1 = {"TS", "JS", "QS", "KS", "AS"};
    vector<card> hand2 = {"8H", "8D", "8C", "9S", "9H"};
    game g1(hand1), g2(hand2);
    if (g1 < g2)
        cout << "g2赢了" << endl;
    else if (g1 > g2)
        cout << "g1赢了" << endl;
    else
        cout << "平局" << endl;
}   

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    LiangBaiKai();
    int _ = 1;
    //cin >> _;
    while (_--)
        Aiden();
    return 0;
}
