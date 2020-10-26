/**
 * 参考：https://twitter.com/laycrs/status/1298297994526126085
 * 　　　https://codeforces.com/contest/1400/submission/90960562
 * ・累積和
 * ・真ん中を固定するやつ。今回は4つあるので、中2つを決め打ち全探索して、
 * 　その手前と先にある個数を予め累積和で前計算しておく。
 * ・真ん中固定は結構典型であるので、この方針に行ければよかった。
 * 　やっぱり最近やった方針に頭が引っ張られるよね。。
 */

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

ll N;
vector<ll> A;

void solve() {
    A.clear();
    cin >> N;
    A.resize(N);
    list2d(acc1, N+1, N+1, ll, 0);
    list2d(acc2, N+1, N+1, ll, 0);
    rep(i, 0, N) cin >> A[i];

    rep(i, 0, N) {
        acc1[A[i]][i+1]++;
        acc2[A[i]][i]++;
    }
    rep(i, 0, N+1) {
        rep(j, 1, N+1) {
            acc1[i][j] += acc1[i][j-1];
        }
        rrep(j, N-1, -1) {
            acc2[i][j] += acc2[i][j+1];
        }
    }

    ll ans = 0;
    rep(j, 0, N) {
        rep(k, j+1, N) {
            ans += acc2[A[j]][k+1] * acc1[A[k]][j];
        }
    }
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while(T--) solve();

    return 0;
}
