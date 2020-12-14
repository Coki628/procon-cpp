/**
 * ・しっかり自力AC！実装ちょっと重いよね。
 * ・蟻本演習4-2-1
 * ・ゲームDP、ミニマックス法
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

ll gridtoid(ll i, ll j, ll W) {
    return i*W+j;
}

pll idtogrid(ll id, ll W) {
    return divmod(id, W);
}

ll B[2][3], C[3][2];
ll H = 3, W = 3;

ll calc(string s) {
    ll res = 0;
    rep(j, 0, W) {
        rep(i, 0, H-1) {
            ll id1 = gridtoid(i, j, W);
            ll id2 = gridtoid(i+1, j, W);
            if (s[id1] == s[id2]) {
                res += B[i][j];
            }
        }
    }
    rep(i, 0, H) {
        rep(j, 0, W-1) {
            ll id1 = gridtoid(i, j, W);
            ll id2 = gridtoid(i, j+1, W);
            if (s[id1] == s[id2]) {
                res += C[i][j];
            }
        }
    }
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll total = 0;
    rep(i, 0, H-1) rep(j, 0, W) {
        cin >> B[i][j];
        total += B[i][j];
    }
    rep(i, 0, H) rep(j, 0, W-1) {
        cin >> C[i][j];
        total += C[i][j];
    }

    map<string, ll> memo;
    auto rec = [&](auto&& f, string s) -> ll {
        if (memo.count(s)) {
            return memo[s];
        }
        ll cnt = 0;
        rep(i, 0, H) {
            rep(j, 0, W) {
                ll id = gridtoid(i, j, W);
                if (s[id] != '*') cnt++;
            }
        }
        if (cnt == H*W) {
            return calc(s);
        }

        bool turn = cnt % 2;
        if (turn == 0) {
            ll res = 0;
            rep(i, 0, H) {
                rep(j, 0, W) {
                    ll id = gridtoid(i, j, W);
                    if (s[id] == '*') {
                        s[id] = 'o';
                        chmax(res, f(f, s));
                        s[id] = '*';
                    }
                }
            }
            memo[s] = res;
            return res;
        } else {
            ll res = INF;
            rep(i, 0, H) {
                rep(j, 0, W) {
                    ll id = gridtoid(i, j, W);
                    if (s[id] == '*') {
                        s[id] = 'x';
                        chmin(res, f(f, s));
                        s[id] = '*';
                    }
                }
            }
            memo[s] = res;
            return res;
        }
    };
    ll res = rec(rec, "*********");
    print(res);
    print(total-res);
    return 0;
}
