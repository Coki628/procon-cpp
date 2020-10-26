/**
 * ・自力AC！本日唯一の見せ場だった。。
 * ・前計算、二分探索
 * ・最近、ゆきこで近い考え方のやつをやってたのが良かった。(yukico800)
 * ・愚直だと4重ループになって、制約は2重ループまで許してる。
 * 　これは、前に来る2つペアの出現位置を取っておけば、後ろの2つペアを作った時、
 * 　その後ろ2つペアと組める前2つペアがいくつあるのか確認できる。
 * ・実装上は約3000^2/2=450万のループの内側で、mapとにぶたんでlog2つ乗ってるのでかなりきつめ。
 * 　AC0.98秒。(制約は2秒だったからギリではないけど)
 * ・各回のmapへのアクセスを3回やってたのを1回にしたらAC0.65秒。いいね。
 * ・ってやってたらハックされた。。。MLEって。。
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
map<pll, vector<ll>> D;

void solve() {
    A.clear();
    D.clear();
    cin >> N;
    A.resize(N);
    rep(i, 0, N) cin >> A[i];

    rep(i, 0, N) {
        rep(j, i+1, N) {
            D[{A[i], A[j]}].pb(j);
        }
    }
    for (auto &v : D) {
        sort(v.second.begin(), v.second.end());
    }
    ll ans = 0;
    rep(k, 0, N) {
        rep(l, k+1, N) {
            auto &v = D[{A[k], A[l]}];
            ll idx = lower_bound(v.begin(), v.end(), k) - v.begin();
            ans += idx;
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
