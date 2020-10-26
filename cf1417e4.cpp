/**
 * 参考：https://codeforces.com/contest/1416/submission/94025253
 * ・やっとみんなのやろうとしてた方向性が分かった。
 * ・ビット、再帰探索、分割統治法
 * ・重要な考察として、上位ビットから見て行った時、あるビットが立ってるかどうかが異なる値同士は、
 * 　下位ビットをどう動かされようと大小関係が入れ替わらないということ。
 * 　つまりそのビットが異なるもの同士での転倒数は、そのビットによってのみ決まる。
 * ・このことから、そのビットが0のグループと1のグループに分けて、その各グループ内での
 * 　転倒数だけを再帰的に調べにいくことで、全体の計算量はlogが乗るだけで済む。
 * ・あと、各ビットについての結果は最終的にビット毎に合計で比較したいので、
 * 　戻り値に持たせるよりも、配列に記録しておいて、全部終わってから合計チェック、が具合がいい。
 * ・これらを踏まえて再帰を実装すれば、きれいにまとまる。
 * 　ビットであれば転倒数計算にlogも乗らないので、計算量は30万に再帰のlogひとつで、無事AC0.73秒。
 */

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ll, int> pli;
typedef pair<int, int> pii;
typedef pair<ll, ld> pld;
typedef pair<pii, int> ppiii;
typedef pair<pii, ll> ppiil;
typedef pair<pll, ll> pplll;
typedef pair<pli, int> pplii;
typedef vector<vector<ll>> vvl;
typedef vector<vector<int>> vvi;
typedef vector<vector<pll>> vvpll;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define pb push_back
#define tostr to_string
#define mkp make_pair
#define list2d(name, N, M, type, init) vector<vector<type>> name(N, vector<type>(M, init))
const ll INF = LONG_LONG_MAX;
const ll MOD = 1000000007;

void print(ld out) { cout << fixed << setprecision(15) << out << '\n'; }
void print(double out) { cout << fixed << setprecision(15) << out << '\n'; }
template<typename T> void print(T out) { cout << out << '\n'; }
template<typename T1, typename T2> void print(pair<T1, T2> out) { cout << out.first << ' ' << out.second << '\n'; }
template<typename T> void print(vector<T> A) { rep(i, 0, A.size()) { cout << A[i]; cout << (i == A.size()-1 ? '\n' : ' '); } }
template<typename T> void print(set<T> S) { vector<T> A(S.begin(), S.end()); print(A); }

template<typename T> inline bool chmax(T &x, T y) { return (y > x) ? x = y, true : false; }
template<typename T> inline bool chmin(T &x, T y) { return (y < x) ? x = y, true : false; }

ll sum(vector<ll> A) { ll res = 0; for (ll a: A) res += a; return res; }
ll max(vector<ll> A) { ll res = -INF; for (ll a: A) chmax(res, a); return res; }
ll min(vector<ll> A) { ll res = INF; for (ll a: A) chmin(res, a); return res; }

ll toint(string s) { ll res = 0; for (char c : s) { res *= 10; res += (c - '0'); } return res; }
// 数字なら'0'、アルファベットなら'a'みたいに使い分ける
// int toint(char c) { return c - '0'; }
// char tochar(int i) { return '0' + i; }

inline ll pow(int x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
inline ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

inline ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
inline ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }
pll divmod(ll a, ll b) { ll d = a / b; ll m = a % b; return {d, m}; }

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }

ll N, K = 32;
vector<ll> A;
list2d(table, 2, K, ll, 0);

// 転倒数カウント
ll check(vector<bool> &B) {
    ll one = 0, res = 0;
    for (bool b : B) {
        if (b) {
            one++;
        } else {
            res += one;
        }
    }
    return res;
}

void rec(vector<ll> &A, ll k) {
    if (k < 0 || A.size() == 0) return;

    // このビットが0のグループと1のグループに分ける
    vector<ll> A0, A1;
    // このビットだけにした数列と、それを反転させたもの
    vector<bool> B, Brev;

    for (ll a : A) {
        bool b = a>>k & 1;
        B.pb(b);
        Brev.pb(1-b);
        if (b) {
            A1.pb(a);
        } else {
            A0.pb(a);
        }
    }
    // table[0][k] := kビット目を反転させない時の転倒数、に追加
    table[0][k] += check(B);
    // table[1][k] := kビット目を反転させる時の転倒数、に追加
    table[1][k] += check(Brev);
    // グループ毎に下位ビットを見に行く
    rec(A0, k-1);
    rec(A1, k-1);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    rep(i, 0, N) cin >> A[i];

    rec(A, K-1);

    ll inv = 0, ans = 0;
    rep(k, 0, K) {
        if (table[0][k] <= table[1][k]) {
            inv += table[0][k];
        } else {
            inv += table[1][k];
            ans += 1<<k;
        }
    }
    print(mkp(inv, ans));
    return 0;
}
