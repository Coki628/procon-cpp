/**
 * ・pypyTLEで状況が分からないのでこっちで作ったらWA。。
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
const ll MOD = 998244353;

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

ll N, Q, ans;
vector<ll> A;
vector<bool> S1, S2;

bool check1(ll x) {
    if (A[x-1] < A[x] && A[x] > A[x+1]) {
        S1[x] = 1;
        ans += A[x];
        return true;
    } else {
        return false;
    }
}

bool check2(ll x) {
    if (A[x-1] > A[x] && A[x] < A[x+1]) {
        S2[x] = 1;
        ans -= A[x];
        return true;
    } else {
        return false;
    }
}

void solve() {
    A.clear();
    S1.clear();
    S2.clear();

    cin >> N >> Q;
    N += 2;
    A.resize(N);
    S1.resize(N);
    S2.resize(N);
    rep(i, 1, N-1) cin >> A[i];

    ans = 0;
    rep(i, 1, N-1) {
        check1(i);
        check2(i);
    }

    print(ans);
    ll l, r;
    rep(_, 0, Q) {
        cin >> l >> r;

        if (S1[l]) {
            ans -= A[l];
            S1[l] = 0;
        }
        if (S1[r]) {
            ans -= A[r];
            S1[r] = 0;
        }
        if (S2[l]) {
            ans += A[l];
            S2[l] = 0;
        }
        if (S2[r]) {
            ans += A[r];
            S2[r] = 0;
        }

        swap(A[l], A[r]);

        bool resl1 = 0, resl2 = 0;
        if (check1(l)) {
            if (l-1 != 0 && !S2[l-1]) {
                check2(l-1);
            }
            if (l+1 != N-1 && !S2[l+1]) {
                resl2 = check2(l+1);
            }
        }
        if (check2(l)) {
            if (l-1 != 0 && !S1[l-1]) {
                check1(l-1);
            }
            if (l+1 != N-1 && !S1[l+1]) {
                resl1 = check1(l+1);
            }
        }
        if (check1(r)) {
            if (r-1 != 0 && !S2[r-1]) {
                check2(r-1);
            }
            if (r+1 != N-1 && !S2[r+1]) {
                check2(r+1);
            }
            if (resl1 && l+1 == r) {
                ans -= A[r];
            }
        }
        if (check2(r)) {
            if (r-1 != 0 && !S1[r-1]) {
                check1(r-1);
            }
            if (r+1 != N-1 && !S1[r+1]) {
                check1(r+1);
            }
            if (resl2 && l+1 == r) {
                ans += A[r];
            }
        }
        print(ans);
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while(T--) solve();

    return 0;
}
