/**
 * 参考：https://twitter.com/armeria_betrue/status/1271852367265148929
 * ・自力ならず。
 * ・グラフ、2部グラフ、閉路検出
 * ・小さい閉路がない時、2部グラフに塗り上げるのは分かったけど、
 * 　最小閉路をどう検出すればいいか分からなかった。
 * ・アルメリアさんの解法が賢くて、頂点をK個までしか見なければ、
 * 　その中で閉路があればK以内だし、なければそこまでの集合は2部グラフなので、
 * 　どっちにしても答えを出せるというもの。これだとより小さい閉路は求める必要がない。
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

ll N, M, K, cntk;
vvl nodes;
vector<bool> color, visited;
vector<ll> cycle;

bool dfs(ll u, ll prev, bool c) {
    if (visited[u]) {
        return true;
    }
    if (cntk >= K) {
        return false;
    }
    cntk++;
    color[u] = c;
    visited[u] = true;
    for (ll v : nodes[u]) {
        if (v == prev) continue;
        if (dfs(v, u, 1-c)) {
            cycle.pb(u+1);
            return true;
        }
    }
    return false;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> M >> K;
    nodes.resize(N);
    color.resize(N);
    visited.resize(N);
    ll a, b;
    rep(i, 0, M) {
        cin >> a >> b;
        a--; b--;
        nodes[a].pb(b);
        nodes[b].pb(a);
    }
    cntk = 0;
    if (dfs(0, -1, 0)) {
        print(2);
        print(cycle.size());
        print(cycle);
    } else {
        print(1);
        vector<ll> ans1, ans2;
        rep(i, 0, N) {
            if (visited[i]) {
                if (color[i]) {
                    ans1.pb(i+1);
                } else {
                    ans2.pb(i+1);
                }
            }
        }
        vector<ll> ans;
        if (ans1.size() >= ans2.size()) {
            rep(i, 0, ceil(K, 2)) ans.pb(ans1[i]);
        } else {
            rep(i, 0, ceil(K, 2)) ans.pb(ans2[i]);
        }
        print(ans);
    }
    return 0;
}
