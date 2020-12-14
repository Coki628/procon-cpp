/**
 * 参考：https://ferin-tech.hatenablog.com/entry/2019/11/29/AOJ2376_DisconnectedGame
 * 　　　https://drken1215.hatenablog.com/entry/2020/10/16/055000
 * ・蟻本演習4-2-1
 * ・ゲームDP、グラフ
 * ・むずい。解説熟読してやっと理解できるくらいのやつ。
 * ・連結成分が1つになる時に決着が着くので、連結成分数に注目する。
 * 　ある2つの連結成分が併合する時、含まれる頂点数の偶奇だけ管理していれば、
 * 　連結成分数の変化も、頂点数の偶奇の変化も分かる。
 * ・同じ連結成分内で辺を繋ぐ場合は、結局それがなくなるまでお互いにやり合う形になってしまうので、
 * 　偶奇だけ管理すればいい。
 * ・これで頂点や辺の状態を直接全て管理しなくてよくなり、
 * 　・含まれる頂点数が偶数個の連結成分の数
 * 　・含まれる頂点数が奇数個の連結成分の数
 * 　・同じ連結成分内で繋げる残りの辺の総数の偶奇
 * 　だけを状態として持ってDPを進められる。
 * ・状態変化の詳細はソース内コメントにて。
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
#define ALL(A) A.begin(), A.end()
constexpr ll INF = LONG_LONG_MAX;
constexpr ll MOD = 1000000007;

template<typename T> vector<vector<T>> list2d(int N, int M, T init) { vector<vector<T>> res(N, vector<T>(M, init)); return res; }
template<typename T> vector<vector<vector<T>>> list3d(int N, int M, int L, T init) { vector<vector<vector<T>>> res(N, vector<vector<T>>(M, vector<T>(L, init))); return res; }

void print(ld out) { cout << fixed << setprecision(15) << out << '\n'; }
void print(double out) { cout << fixed << setprecision(15) << out << '\n'; }
template<typename T> void print(T out) { cout << out << '\n'; }
template<typename T1, typename T2> void print(pair<T1, T2> out) { cout << out.first << ' ' << out.second << '\n'; }
template<typename T> void print(vector<T> A) { rep(i, 0, A.size()) { cout << A[i]; cout << (i == A.size()-1 ? '\n' : ' '); } }
template<typename T> void print(set<T> S) { vector<T> A(S.begin(), S.end()); print(A); }

void Yes() { print("Yes"); }
void No() { print("No"); }
void YES() { print("YES"); }
void NO() { print("NO"); }

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

struct UnionFind {

    int n, groupcnt;
    vector<int> par, rank, size;

    UnionFind(int n) : n(n) {
        par.resize(n);
        rank.resize(n);
        size.resize(n, 1);
        rep(i, 0, n) par[i] = i;
        groupcnt = n;
    }

    UnionFind() {}

    void resize(int _n) {
        n = _n;
        par.resize(n);
        rank.resize(n);
        size.resize(n, 1);
        rep(i, 0, n) par[i] = i;
        groupcnt = n;
    }

    // 根の検索(グループ番号)
    int find(int x) {
        if (par[x] == x) {
            return x;
        } else {
            par[x] = find(par[x]);
            return par[x];
        }            
    }

    // 併合
    void merge(int a, int b) {
        int x = find(a);
        int y = find(b);
        if (x == y) return;
        groupcnt--;
        if (rank[x] < rank[y]) {
            par[x] = y;
            size[y] += size[x];
        } else {
            par[y] = x;
            size[x] += size[y];
            if (rank[x] == rank[y]) {
                rank[x] += 1;
            }
        }
    }

    // 同じ集合に属するか判定
    bool is_same(int a, int b) {
        return find(a) == find(b);
    }

    // あるノードの属する集合のノード数
    int get_size(int x) {
        return size[find(x)];
    }

    // 集合の数
    int get_size() {
        return groupcnt;
    }

    // 全ての根を取得
    set<int> get_roots() {
        set<int> res;
        rep(i, 0, n) res.insert(find(i));
        return res;
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N;
    cin >> N;
    vector<string> grid(N);
    rep(i, 0, N) cin >> grid[i];

    ll M = 0;
    UnionFind uf(N);
    rep(i, 0, N) {
        rep(j, i+1, N) {
            if (grid[i][j] == 'Y') {
                M++;
                uf.merge(i, j);
            }
        }
    }
    // 含まれる頂点数が偶数個・奇数個の連結成分の数
    ll evencnt = 0, oddcnt = 0;
    // 同じ連結成分内で繋げる残りの辺の総数
    ll K = 0;
    for (auto root : uf.get_roots()) {
        ll sz = uf.get_size(root);
        if (sz % 2 == 0) {
            evencnt++;
        } else {
            oddcnt++;
        }
        K += sz*(sz-1)/2;
    }
    K -= M;

    auto memo = list3d(2, N+1, N+1, -1);
    auto rec = [&](auto&& f, bool k, ll ev, ll od) -> bool {
        if (memo[k][ev][od] != -1) {
            return memo[k][ev][od];
        }
        // 残る連結成分が2つなら終了へ
        if (ev+od == 2) {
            // 同じ成分内の辺が奇数個ならここは勝ち
            if (k) {
                return true;
            } else {
                return false;
            }
        }
        bool res = true;
        // 偶*偶 or 偶*奇 の連結成分を繋ぐ
        // 連結成分数は、偶+偶=偶、偶+奇=奇でいずれも偶が-1、
        // 成分内の辺数は偶*偶-1=奇、偶*奇-1=奇なのでいずれも変化する
        if (ev+od >= 2 and ev) {
            res &= f(f, !k, ev-1, od);
        }
        // 奇*奇 の連結成分を繋ぐ
        // 連結成分数は、奇+奇=偶なので偶が+1、奇が-2
        // 成分内の辺数は奇*奇-1=偶なので変化しない
        if (od >= 2 and od) {
            res &= f(f, k, ev+1, od-2);
        }
        // 同じ成分内の辺を繋ぐ
        if (k) {
            res &= f(f, !k, ev, od);
        }
        memo[k][ev][od] = !res;
        return !res;
    };

    if (rec(rec, K%2, evencnt, oddcnt)) {
        print("Taro");
    } else {
        print("Hanako");
    }
    return 0;
}
