/**
 * ・ちょっと思い当たる最適化を施してみたけどダメ。まだTLE。。
 * ・25ビット3300万*2はC++なら行けなくないような気がするんだけどなぁ。
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

int N, K;
vector<int> A, A1, A2;
int P1[33554440], P2[33554440], C0[2507], C1[2507];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> K;
    A.resize(N);
    rep(i, 0, N) cin >> A[i];
    // 総和0を平均KとするためにKを引く
    rep(i, 0, N) A[i] -= K;
    // 半分全列挙
    rep(i, 0, N/2) A1.pb(A[i]);
    rep(i, N/2, N) A2.pb(A[i]);
    
    // それぞれの全組み合わせ
    int N1 = A1.size();
    rep(S, 0, 1<<N1) {
        int p = 0;
        rep(i, 0, N1) {
            if (S>>i & 1) {
                p += A1[i];
            }
        }
        P1[S] = p;
    }
    int N2 = A2.size();
    rep(S, 0, 1<<N2) {
        int p = 0;
        rep(i, 0, N2) {
            if (S>>i & 1) {
                p += A2[i];
            }
        }
        P2[S] = p;
    }

    // 総和0になるペアの数を求める
    rep(i, 0, 1<<N2) {
        if (P2[i] <= 0) {
            C0[-P2[i]]++;
        } else {
            C1[P2[i]]++;
        }
    }
    ll ans = 0;
    rep(i, 0, 1<<N1) {
        if (P1[i] >= 0) {
            ans += C0[P1[i]];
        } else {
            ans += C1[-P1[i]];
        }
    }
    // どちらも1つも選ばない分の1を引く
    print(ans - 1);
    return 0;
}
