/**
 * 参考：https://codeforces.com/blog/entry/52318
 * ・蟻本演習4-2-5
 * ・Nim応用、木上のゲーム
 * ・むずい。Nimに帰着させる。
 * ・葉からの距離の偶奇が1のところは、動かされたら同じ動きして無効にさせられる。
 * 　偶奇が0のところをNimの山とみなして勝敗を考えられる。
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

    ll N;
    cin >> N;
    vvl nodes(N);
    vector<ll> A(N);
    rep(i, 0, N) cin >> A[i];
    rep(v, 1, N) {
        ll u;
        cin >> u;
        u--;
        nodes[u].pb(v);
    }

    // 葉からの距離の偶奇で、頂点をNimの山(blue)と無効な場所(red)に分ける
    vector<ll> blue, red;
    auto dfs = [&](auto&& f, ll u, ll prev) -> bool {
        if (nodes[u].size() == 0) {
            blue.pb(u);
            return true;
        }
        bool res;
        for (ll v : nodes[u]) {
            if (v == prev) continue;
            res = !f(f, v, u);
        }
        if (res) {
            blue.pb(u);
        } else {
            red.pb(u);
        }
        return res;
    };
    dfs(dfs, 0, -1);

    ll nim = 0;
    for (ll u : blue) {
        nim ^= A[u];
    }
    ll M = blue.size();
    ll L = red.size();
    map<ll, ll> C;
    for (ll u : red) {
        C[A[u]]++;
    }
    ll ans = 0;
    for (ll u : blue) {
        // 交換することでNimのXORを0にできるペア
        // (元々Nimが0の時に同値で交換するのもここに含まれる)
        ans += C[A[u]^nim];
    }
    if (!nim) {
        // 元々Nimが0の場合はblue同士、red同士の頂点は全て交換できる
        ans += M*(M-1)/2 + L*(L-1)/2;
    }
    print(ans);
    return 0;
}
