/**
 * ・pypy通らなかったのでこっちで。
 * ・行列累乗
 * ・計算量がクエリ1万*行列積で4^3*累乗に10^18のlogで10000*64*60くらい=約3800万。
 * 　まあループ深くなると重くなる傾向あるしなー。C++でAC0.8秒。
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
const ll MOD = 17;

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
char tochar(int i) { return '0' + i; }

inline ll pow(int x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
inline ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

inline ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
inline ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }

struct MatPow {

    vvl mat_dot(vvl A, vvl B) {
        ll n1 = A.size();
        ll n2 = A[0].size();
        ll m2 = B[0].size();
        vvl res(n1, vector<ll>(m2, 0));
        rep(i, 0, n1) {
            rep(j, 0, m2) {
                rep(k, 0, n2) {
                    res[i][j] = (res[i][j] + (A[i][k] * B[k][j]) % MOD) % MOD;
                }
            }
        }
        return res;
    }
    
    vvl mat_pow(vvl mat, ll k) {
        ll n = mat.size();
        vvl res(n, vector<ll>(n, 0));
        rep(i, 0, n) {
            res[i][i] = 1;
        }
        while (k > 0) {
            if (k & 1) {
                res = mat_dot(res, mat);
            }
            mat = mat_dot(mat, mat);
            k >>= 1;
        }
        return res;
    }

    vector<ll> solve(vvl mat, vvl init, ll K) {
        auto res = mat_pow(mat, K);
        res = mat_dot(res, init);
        ll n = mat.size();
        vector<ll> ret(n, 0);
        rep(i, 0, n) {
            ret[i] = res[i][0];
        }
    return ret;
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    vvl mat(4, vector<ll>(4, 0));
    rep(i, 0, 4) {
        mat[0][i] = 1;
    }
    rep(i, 0, 3) {
        mat[i+1][i] = 1;
    }
    vvl init(4, vector<ll>(1, 0));
    init[0][0] = 1;

    ll Q;
    cin >> Q;

    MatPow mp;
    ll n;
    rep(i, 0, Q) {
        cin >> n;
        if (n < 4) {
            print(0);
        } else if (n == 4) {
            print(1);
        } else {
            ll ans = mp.solve(mat, init, n-4)[0];
            print(ans);
        }
    }
    return 0;
}
