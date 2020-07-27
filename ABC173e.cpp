/**
 * 参考：https://atcoder.jp/contests/abc173/submissions/15000305
 * ・むげんさんがlog累積和で解いてたのでC++に移植。
 * ・誤差怖いのは変わらないけど、long double使えばとりあえず通る。
 * ・log関数に渡す時にldにキャストするのと、負数MODを調整するのを気をつければあとはほぼpythonの移植。
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

template<typename T>
vector<T> accumulate(vector<T> &A) {
    int N = A.size();
    if (!N) return {};
    vector<T> res(N);
    res[0] = A[0];
    rep(i, 1, N) res[i] = res[i-1] + A[i];
    return res;
}

ll N, K, zero;
vector<ll> A, A1, A2;
vector<ld> B1, B2;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> K;
    A.resize(N);
    rep(i, 0, N) cin >> A[i];

    for (ll a : A) {
        if (a > 0) {
            A1.pb(a);
            // 戻り値がldのlog関数を呼び出すため、引数aはldにキャストして渡す
            B1.pb(log((ld)a));
        } else if (a < 0) {
            A2.pb(-a);
            B2.pb(log((ld)-a));
        } else {
            zero++;
        }
    }

    sort(A1.begin(), A1.end());
    sort(A2.begin(), A2.end());
    sort(B1.begin(), B1.end());
    sort(B2.begin(), B2.end());
    auto acc1 = accumulate(B1);
    auto acc2 = accumulate(B2);
    reverse(B1.begin(), B1.end());
    reverse(B2.begin(), B2.end());
    auto accrev1 = accumulate(B1);
    auto accrev2 = accumulate(B2);
    acc1.insert(acc1.begin(), 0);
    acc2.insert(acc2.begin(), 0);
    accrev1.insert(accrev1.begin(), 0);
    accrev2.insert(accrev2.begin(), 0);

    ld mx = -INF;
    ld mn = INF;
    pll idx1 = {-1, -1};
    pll idx2 = {-1, -1};
    ll j;
    ld sm;
    rep(i, 0, K+1) {
        j = K - i;
        if (B1.size() < i || B2.size() < j) {
            continue;
        }
        if (j % 2 == 0) {
            sm = accrev1[i] + accrev2[j];
            if (sm > mx) {
                mx = sm;
                idx1 = {i, j};
            }
        } else {
            sm = acc1[i] + acc2[j];
            if (sm < mn) {
                mn = sm;
                idx2 = {i, j};
            }
        }
    }

    ll ans, n, m;
    if (mx != -INF) {
        ans = 1;
        tie(n, m) = idx1;
        reverse(A1.begin(), A1.end());
        reverse(A2.begin(), A2.end());
        rep(i, 0, n) {
            ans *= A1[i];
            ans %= MOD;
        }
        rep(i, 0, m) {
            ans *= -A2[i];
            // C++は負数MODがダメなので調整入れる
            ans += MOD * MOD;
            ans %= MOD;
        }
        print(ans);
    } else if (zero) {
        print(0);
    } else {
        ans = 1;
        tie(n, m) = idx2;
        rep(i, 0, n) {
            ans *= A1[i];
            ans %= MOD;
        }
        rep(i, 0, m) {
            ans *= -A2[i];
            ans += MOD * MOD;
            ans %= MOD;
        }
        print(ans);
    }
    return 0;
}
