/**
 * ・自力AC！
 * ・bitDP
 * ・想定解は考察して場合分けしてたけど、bitDPでも通った。
 * ・降順に向けられるのは1回だけなので、それ前かそれ後かで耳にする。
 * ・あとは昇順降順が分かるように直前を覚えながら、ありそうな順列のbitDPをやる。
 * ・最後に欲しい答えは最初の値がKの通り数なので、操作を配列の末尾からやる想定にして
 * 　(つまり降順昇順の関係を逆にして)処理を進める。
 * 　これで直前に使った値を最初の値とできるので答えが求まる。
 * ・20ビット*20*20=約4億2000万のループは明らかにpypyでも無理めなので最初からC++で。AC1.0秒。
 * ・ちなみに添字を次元が浅い方を手前にするの試してみたけど、あんま変わらなかった。
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

ll N, K;
ll dp0[1<<20][20], dp1[1<<20][20];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> K;
    K--;

    rep(i, 0, N) {
        dp0[1<<i][i] = 1;
    }
    rep(bit, 1, 1<<N) {
        rep(i, 0, N) {
            if (!(bit>>i & 1)) continue;
            rep(j, 0, N) {
                if (bit>>j & 1) continue;
                if (i > j) {
                    dp0[bit|(1<<j)][j] += dp0[bit][i];
                    dp1[bit|(1<<j)][j] += dp1[bit][i];
                }
                if (i < j) {
                    dp1[bit|(1<<j)][j] += dp0[bit][i];
                }
            }
        }
    }
    ll ans = dp1[(1<<N)-1][K];
    print(ans);
    return 0;
}
