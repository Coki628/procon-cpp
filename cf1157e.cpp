/**
 * ・自力AC！
 * ・multisetにぶたん
 * ・取りたい位置が変化するのをどうまとめようか悩んだけど、
 * 　最終的に2周作れば楽にいけるって判断でそれがうまくいった。
 * ・20万にlog2つ乗っても、なんとかAC1.5秒。
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
const ll INF = 1e18;
const ll MOD = 1e9 + 7;

void print(ld out) { cout << fixed << setprecision(12) << out << '\n'; }
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
int toint(char c) { return c - '0'; }

inline ll pow(int x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
inline ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

inline ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
inline ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }

ll bisearch_min(ll mn, ll mx, function<bool(ll)> func) {
    ll ok = mx;
    ll ng = mn;
    while (ng+1 < ok) {
        ll mid = (ok+ng) / 2;
        if (func(mid)) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    return ok;
}

ll N, offset;
vector<ll> A, B;
multiset<ll> S;

bool check(ll m) {
    auto itr1 = S.lower_bound(offset);
    auto itr2 = S.lower_bound(offset+m+1);
    return itr1 != itr2;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    B.resize(N);
    rep(i, 0, N) cin >> A[i];
    rep(i, 0, N) cin >> B[i];
    
    for (ll b: B) {
        S.insert(b);
        S.insert(b+N);
    }

    vector<ll> ans;
    ll res;
    rep(i, 0, N) {
        offset = N - A[i];
        res = bisearch_min(-1, N, check);
        ans.pb(res);
        S.erase(S.lower_bound((res+offset)%N));
        S.erase(S.lower_bound((res+offset)%N+N));
    }
    print(ans);
    return 0;
}
