/**
 * 参考：https://jupiro.hatenablog.com/entry/2020/11/25/013726
 * ・自力ならず。木にする方針はよかったけど、やり方がよくなかった。閉路の辺切って木のパス数えて、
 * 　それ付けた時いくつくらいパス増えるか、みたいにやろうとしたけど、うまくいかなかった。
 * ・なもりグラフ
 * ・木より1本辺が多いグラフ。サイクルを検出、そこに含まれる頂点を列挙して、
 * 　その各頂点を根とした部分木について木の走査をやるとよしなにやれる。
 * 　今回の場合は部分木の頂点数を数える。
 * ・パス数について、部分木の頂点同士は普通に木のパスなので全てのペアに1本ずつでN*(N-1)/2になって、
 * 　その部分木と部分木の外の頂点については全部*全部なんだけど、ここは右回りと左回りがあるから*2になる。
 * 　で、今回は往復のパスを同一のみなす設定なのでここは結局/2する。
 */

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using pii = pair<int, int>;
using vvl = vector<vector<ll>>;
using vvi = vector<vector<int>>;
using vvpll = vector<vector<pll>>;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define pb push_back
#define tostr to_string
constexpr ll INF = LONG_LONG_MAX;
constexpr ll MOD = 1000000007;

template<typename T> vector<vector<T>> list2d(int N, int M, T init) {
    vector<vector<T>> res(N, vector<T>(M, init));
    return res;
}
template<typename T> vector<vector<vector<T>>> list3d(int N, int M, int L, T init) {
    vector<vector<vector<T>>> res(N, vector<vector<T>>(M, vector<T>(L, init)));
    return res;
}

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
int toint(char num) { return num - '0'; }
char tochar(int num) { return '0' + num; }

inline ll pow(int x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
inline ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

inline ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
inline ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }
pll divmod(ll a, ll b) { ll d = a / b; ll m = a % b; return {d, m}; }

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }

void solve() {
    ll N;
    cin >> N;
    vector<set<ll>> nodes(N);
    rep(i, 0, N) {
        ll u, v;
        cin >> u >> v;
        u-- ; v--;
        nodes[u].insert(v);
        nodes[v].insert(u);
    }

    // 閉路の辺を検出
    vector<bool> visited(N);
    pll edge;
    auto dfs = [&](auto&& f, ll u, ll prev) -> void {
        if (visited[u]) {
            edge = {prev, u};
            return;
        }
        visited[u] = true;
        for (auto v : nodes[u]) {
            if (v == prev) continue;
            f(f, v, u);
        }
        return;
    };
    dfs(dfs, 0, -1);

    ll x, y;
    tie(x, y) = edge;
    nodes[x].erase(y);
    nodes[y].erase(x);

    // サイクルの位置を特定
    vector<ll> V;
    auto dfs2 = [&](auto&& f, ll u, ll prev, ll w) -> bool {
        if (u == w) {
            V.pb(u);
            return true;
        }
        for (auto v : nodes[u]) {
            if (v == prev) continue;
            if (f(f, v, u, w)) {
                V.pb(u);
                return true;
            }
        }
        return false;
    };
    dfs2(dfs2, x, -1, y);

    // サイクルの部分木の頂点数を数える
    auto dfs3 = [&](auto&& f, ll u, ll prev, ll l, ll r) -> ll {
        ll res = 0;
        for (auto v : nodes[u]) {
            // この部分木から出ていく頂点には行かない
            if (v == prev or v == l or v == r) continue;
            res += f(f, v, u, l, r);
        }
        res++;
        return res;
    };
    ll M = V.size();
    ll ans = 0;
    rep(i, 0, M) {
        ll res = dfs3(dfs3, V[i], -1, V[(i+M-1)%M], V[(i+1)%M]);
        // 部分木の頂点同士でのパス数
        ans += res*(res-1) / 2;
        // 部分木外の頂点とのパス数(右回り左回りで*2、往復を同一とみなすので/2で結局そのまま)
        ans += res*(N-res);
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
