/**
 * ・ABC164dの別解をこっちでも。
 * ・Pが最大10000まであるので、計算量最大20億でさすがにTLE。。
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
char tochar(int i) { return '0' + i; }

inline ll pow(int x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
inline ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

inline ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
inline ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }

ll dp0[2][10007], dp1[2][10007], dp2[2][10007];
ll N, P;
string S;
vector<ll> A;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> P;
    cin >> S;
    const ll mod = P;
    A.resize(N);
    rep(i, 0, N) A[i] = toint(S[i]);
    
    dp0[0][0] = 1;
    ll a, nxt, ans;
    rep(i, 0, N) {
        a = A[i];
        dp0[(i+1)&1][0] = dp0[i&1][0];
        dp1[(i+1)&1][a%mod] = dp0[i&1][0];
        // 1桁で終わる遷移を追加
        dp2[(i+1)&1][a%mod] = dp0[i&1][0];
        rep(j, 0, mod) {
            nxt = (j*10+a) % mod;
            dp1[(i+1)&1][nxt] += dp1[i&1][j];
            dp2[(i+1)&1][nxt] += dp1[i&1][j];
            dp2[(i+1)&1][j] += dp2[i&1][j];
        }
        memset(dp0[i&1], 0, sizeof(dp0[i&1]));
        memset(dp1[i&1], 0, sizeof(dp1[i&1]));
        memset(dp2[i&1], 0, sizeof(dp2[i&1]));
    }
    ans = dp2[N&1][0];
    print(ans);
    return 0;
}
