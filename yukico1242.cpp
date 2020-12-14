/**
 * ・自力AC！想定解とは違ったけど、青diff自力突破は嬉しい。
 * ・結局NGマスの周囲がどうなっているかだけが重要なので、そのマスが関係するNG6通りを全部チェック。
 * 　Nの範囲が広いけど、setで管理すればNGマスがある周辺だけをチェックして進められる。
 */

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using pii = pair<int, int>;
using vvl = vector<vector<ll>>;
using vvi = vector<vector<int>>;
using vvpll = vector<vector<pll>>;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define pb push_back
#define tostr to_string
#define ALL(A) A.begin(), A.end()
constexpr ll INF = LONG_LONG_MAX;
constexpr ll MOD = 1000000007;

template<typename T> vector<vector<T>> list2d(int N, int M, T init) { vector<vector<T>> res(N, vector<T>(M, init)); return res; }
template<typename T> vector<vector<vector<T>>> list3d(int N, int M, int L, T init) { vector<vector<vector<T>>> res(N, vector<vector<T>>(M, vector<T>(L, init))); return res; }

void print(ld out) { cout << fixed << setprecision(15) << out << '\n'; }
void print(double out) { cout << fixed << setprecision(15) << out << '\n'; }
template<typename T> void print(T out) { cout << out << '\n'; }
template<typename T1, typename T2> void print(pair<T1, T2> out) { cout << out.first << ' ' << out.second << '\n'; }
template<typename T> void print(vector<T> A) { rep(i, 0, A.size()) { cout << A[i]; cout << (i == A.size()-1 ? '\n' : ' '); } }
template<typename T> void print(set<T> S) { vector<T> A(S.begin(), S.end()); print(A); }

void Yes() { print("Yes"); }
void No() { print("No"); }
void YES() { print("YES"); }
void NO() { print("NO"); }

template<typename T> inline bool chmax(T &x, T y) { return (y > x) ? x = y, true : false; }
template<typename T> inline bool chmin(T &x, T y) { return (y < x) ? x = y, true : false; }

ll sum(vector<ll> A) { ll res = 0; for (ll a: A) res += a; return res; }
ll max(vector<ll> A) { ll res = -INF; for (ll a: A) chmax(res, a); return res; }
ll min(vector<ll> A) { ll res = INF; for (ll a: A) chmin(res, a); return res; }

ll toint(string s) { ll res = 0; for (char c : s) { res *= 10; res += (c - '0'); } return res; }
int toint(char num) { return num - '0'; }
char tochar(int num) { return '0' + num; }

inline ll pow(int x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
inline ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

inline ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
inline ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }
pll divmod(ll a, ll b) { ll d = a / b; ll m = a % b; return {d, m}; }

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N, K;
    cin >> N >> K;
    set<ll> S;
    rep(i, 0, K) {
        ll a;
        cin >> a;
        S.insert(a);
    }

    // 後ろから、NGマスを増やすシミュレーションをしていく
    auto itr = (S.rbegin());
    while (itr != S.rend()) {
        ll a = *itr;
        bool ok = false;
        // このマスを4として3もNGなら、0の位置はNG確定、を同じように6通りチェック
        if (S.count(a-1) and a-4 > 0) {
            S.insert(a-4);
        } else {
            ok = true;
        }
        if (S.count(a-3) and a-5 > 0) {
            S.insert(a-5);
        } else {
            ok = true;
        }
        if (S.count(a-5) and a-6 > 0) {
            S.insert(a-6);
        } else {
            ok = true;
        }
        if (S.count(a+1) and a-3 > 0) {
            S.insert(a-3);
        } else {
            ok = true;
        }
        if (S.count(a+3) and a-2 > 0) {
            S.insert(a-2);
        } else {
            ok = true;
        }
        if (S.count(a+5) and a-1 > 0) {
            S.insert(a-1);
        } else {
            ok = true;
        }
        // この手前6マスを全て潰してしまったら即NG終了
        if (!ok) {
            No();
            return 0;
        }
        itr++;
    }
    // マス1がNGになっているかで成否判定
    if (S.count(1)) {
        No();
    } else {
        Yes();
    }
    return 0;
}
