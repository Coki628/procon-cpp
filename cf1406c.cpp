/**
 * 参考：https://qiita.com/drken/items/4b4c3f1824339b090202
 * ・終了15分後、自力AC。。。
 * ・木の重心、木DP
 * ・重心の求め方はやったことなかったと思うけど、調べたら普通に木DPすればいいみたいでよかった。
 * ・なんだけど、辺の付け替えをどこにするかで思ったより手間取った。。
 * 　結局、2つある重心の片方から外して反対側に付ける、でよかった。
 * ・まあ敗因はこのCよりむしろBに手こずり過ぎたことなんだけどね。。。
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

ll N;
vvl nodes;
vector<ll> dp, cent;
set<pll> se;

void dfs(ll u, ll prev) {
    for (ll v : nodes[u]) {
        if (v == prev) continue;
        dfs(v, u);
        dp[u] += dp[v];
    }
    dp[u]++;
    bool iscent = true;
    for (ll v : nodes[u]) {
        if (v == prev) continue;
        if (dp[v] > N/2) {
            iscent = false;
            break;
        }
    }
    if (iscent && N-dp[u] <= N/2) {
        cent.pb(u);
    }
}

void solve() {
    nodes.clear();
    dp.clear();
    cent.clear();
    se.clear();

    cin >> N;
    nodes.resize(N);
    dp.resize(N);
    ll a, b;
    rep(i, 0, N-1) {
        cin >> a >> b;
        a--; b--;
        nodes[a].pb(b);
        nodes[b].pb(a);
        se.insert({a, b});
        se.insert({b, a});
    }

    dfs(0, -1);
    vector<pll> ans;
    if (cent.size() == 2) {
        rep(i, 0, N-1) {
            if (i == cent[0] || i == cent[1]) continue;
            if (se.count({cent[0], i}) && !se.count({cent[1], i})) {
                ans.pb({cent[0]+1, i+1});
                ans.pb({cent[1]+1, i+1});
                break;
            }
            if (se.count({cent[1], i}) && !se.count({cent[0], i})) {
                ans.pb({cent[1]+1, i+1});
                ans.pb({cent[0]+1, i+1});
                break;
            }
        }
    } else {
        ans.pb({cent[0]+1, nodes[cent[0]][0]+1});
        ans.pb({cent[0]+1, nodes[cent[0]][0]+1});
    }
    print(ans[0]);
    print(ans[1]);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while(T--) solve();

    return 0;
}
