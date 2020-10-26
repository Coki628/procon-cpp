/**
 * ・ここまで自力AC！
 * ・木の走査、DFS、ソートして貪欲
 * ・頂点ではなく辺に注目するやつ。
 * ・全ペアについて見た時の、各辺を通った回数が知りたくなる。
 * ・全体に対して等しく色々知りたくなる系なので全方位木DPを持ってきたくなるが、
 * 　辺に対して使ったことないしとりあえずやめ。
 * ・よくよく考察していくと、「そこより手前の頂点数 * そこより先の頂点数」で
 * 　その辺を通るペアの数になると分かった。
 * ・戻りがけで見ていけば、そこより先の頂点数は分かるけど、手前は分からないなぁ、、
 * 　ってなったけど、さらに考えると、それは単に全体-そこより先の〜、でいいじゃん、となる。
 * ・結果の回数に対しての値の割り振り方は、3^2+3^2より3^1+3^3のがでかいよな、ってな辺りから、
 * 　なるべく1箇所に寄せる、大きいところに全振りが最適だろう、となる。
 * ・1にするところは最小に、という条件があるので、素因数が足りない時は小さい方に1を追加、
 * 　余る時は大きいところに全部寄せ、とやった。
 * ・時間かかってしまったんだけど、みんな結構手早く通していてすごいなぁ、となった。
 * ・ちょっと改善。mapで辺番号の紐付けやってたけど、結局ソートしちゃうんだし、
 * 　どの辺の情報だったかは関係なかったので、普通にpush_backすればよかった。。
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

ll N, M;
vvl nodes;
vector<ll> A, C;

ll dfs(ll u, ll prev) {
    ll res = 0;
    for (ll v : nodes[u]) {
        if (v == prev) continue;
        res += dfs(v, u);
    }
    res++;
    if (prev != -1) {
        C.pb(res * (N-res));
    }
    return res;
}

void solve() {
    cin >> N;
    nodes.clear();
    A.clear();
    C.clear();
    nodes.resize(N);
    ll a, b;
    rep(i, 0, N-1) {
        cin >> a >> b;
        a--; b--;
        nodes[a].pb(b);
        nodes[b].pb(a);
    }
    cin >> M;
    A.resize(M);
    rep(i, 0, M) cin >> A[i];

    dfs(0, -1);
    sort(A.begin(), A.end());
    sort(C.begin(), C.end());
    ll ans = 0;
    if (M <= N-1) {
        reverse(A.begin(), A.end());
        reverse(C.begin(), C.end());
        while (A.size() < N-1) {
            A.pb(1);
        }
    } else {
        ll tmp;
        while (N-1 < A.size()) {
            tmp = A.back();
            A.pop_back();
            A[A.size()-1] *= tmp % MOD;
            A[A.size()-1] %= MOD;
        }
    }
    rep(i, 0, N-1) {
        ans = (ans + A[i]*C[i]%MOD) % MOD;
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
