/**
 * 参考：https://kyopro-friends.hatenablog.com/entry/2019/01/12/231106
 * ・自力ならず。
 * ・bitDP応用
 * ・最善のグループの分け方を決めるために、自身の部分集合の区切り方を全て確認する。
 * 　(ちょうど区間DPで全ての切り方を見る時と同じ感じ)
 * ・この実装だと計算量が2^16*2^16/2=21億くらいなんだけど、
 * 　C++はAC1.6秒。強い。。
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
#define btoe(obj) (obj).begin(), (obj).end()
#define pb push_back
#define str to_string
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

ll N;
ll G[16][16];
ll dp[1<<16];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    rep(i, 0, N) rep(j, 0, N) cin >> G[i][j];
    
    // dp[S] := 集合Sのグループ分けを決めた時の最大値
    rep(S, 1, 1<<N) {
        // 集合S全てを同じグループとした場合を計算
        rep(i, 0, N) {
            rep(j, i+1, N) {
                if (S & (1<<i) && S & (1<<j)) {
                    dp[S] += G[i][j];
                }
            }
        }
        // 集合Sの部分集合の区切り方から、一番いいものを取る
        rep(T, 1, S) {
            if ((S | T) == S) {
                chmax(dp[S], dp[T] + dp[S^T]);
            }
        }
    }
    ll ans = dp[(1<<N)-1];
    print(ans);
    return 0;
}
