/**
 * ・終了後、色々やってみたけどWA。。
 * ・メモ化再帰
 * ・メモ化した。A,Bそれぞれ最後に詰めたのが何か、を持ったんだけど、これだとダメなんかなぁ。。
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
int toint(char c) { return c - '0'; }
char tochar(int i) { return '0' + i; }

inline ll pow(int x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
inline ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

inline ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
inline ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }

ll N;
vector<ll> P, A, B;
bool memo[4007][4007];

bool rec(ll i, ll j, ll k) {
    if (i < 0) {
        return true;
    }
    if (memo[j][k]) {
        return false;
    }
    if (A.size() <= N && B.back() > P[i]) {
        A.pb(P[i]);
        if (rec(i-1, i, k)) {
            return true;
        }
        A.pop_back();
    }
    if (B.size() <= N && A.back() > P[i]) {
        B.pb(P[i]);
        if (rec(i-1, j, i)) {
            return true;
        }
        B.pop_back();
    }
    memo[j][k] = 1;
    return false;
}

void solve() {
    cin >> N;
    A.clear();
    A.pb(INF);
    B.clear();
    B.pb(INF);
    P.clear();
    P.resize(N*2);
    rep(i, 0, N*2) cin >> P[i];
    rep(i, 0, N*2+1) rep(j, 0, N*2+1) memo[i][j] = 0; 

    if (rec(N*2-1, N*2, N*2)) {
        print("YES");
    } else {
        print("NO");
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    rep(_, 0, T) solve();

    return 0;
}
