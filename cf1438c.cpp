/**
 * ・自力AC！
 * ・2-SAT
 * ・それぞれのマスについて、「+1するかどうか」をtrue/falseとして、
 * 　隣り合うマスとの関係性でNGなところに辺を張る。この時、2-satのルールに従って
 * 　「AかつBがNG」なところに「!Aまたは!B」な辺を張る形にする。
 * ・今回は成否ではなく、答えの一例を構築する必要があるので、
 * 　ts.answer()を呼ぶ。なんだけど、最初全く答えが出ない。。
 * 　で、ソースよく確認したら、ts.satisfiable()を呼ばないと、答えの構築もされないのね。。
 * ・さて、無事ACしたはいいが、みんなの話聞いたらこれもギャグだったそう。
 * 　市松模様に偶奇で分ければどこも被らない。言われたら確かにーーー、ってなる。
 * 　今日BもCもそんなんだったな。。
 */

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
#define list2d(name, N, M, type, init) vector<vector<type>> name(N, vector<type>(M, init))
constexpr ll INF = LONG_LONG_MAX;
constexpr ll MOD = 1000000007;

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

#ifndef ATCODER_INTERNAL_SCC_HPP
#define ATCODER_INTERNAL_SCC_HPP 1
#include <algorithm>
#include <utility>
#include <vector>
namespace atcoder {
namespace internal {
template <class E> struct csr {
    std::vector<int> start;
    std::vector<E> elist;
    csr(int n, const std::vector<std::pair<int, E>>& edges)
        : start(n + 1), elist(edges.size()) {
        for (auto e : edges) {
            start[e.first + 1]++;
        }
        for (int i = 1; i <= n; i++) {
            start[i] += start[i - 1];
        }
        auto counter = start;
        for (auto e : edges) {
            elist[counter[e.first]++] = e.second;
        }
    }
};
// Reference:
// R. Tarjan,
// Depth-First Search and Linear Graph Algorithms
struct scc_graph {
  public:
    scc_graph(int n) : _n(n) {}
    int num_vertices() { return _n; }
    void add_edge(int from, int to) { edges.push_back({from, {to}}); }
    // @return pair of (# of scc, scc id)
    std::pair<int, std::vector<int>> scc_ids() {
        auto g = csr<edge>(_n, edges);
        int now_ord = 0, group_num = 0;
        std::vector<int> visited, low(_n), ord(_n, -1), ids(_n);
        visited.reserve(_n);
        auto dfs = [&](auto self, int v) -> void {
            low[v] = ord[v] = now_ord++;
            visited.push_back(v);
            for (int i = g.start[v]; i < g.start[v + 1]; i++) {
                auto to = g.elist[i].to;
                if (ord[to] == -1) {
                    self(self, to);
                    low[v] = std::min(low[v], low[to]);
                } else {
                    low[v] = std::min(low[v], ord[to]);
                }
            }
            if (low[v] == ord[v]) {
                while (true) {
                    int u = visited.back();
                    visited.pop_back();
                    ord[u] = _n;
                    ids[u] = group_num;
                    if (u == v) break;
                }
                group_num++;
            }
        };
        for (int i = 0; i < _n; i++) {
            if (ord[i] == -1) dfs(dfs, i);
        }
        for (auto& x : ids) {
            x = group_num - 1 - x;
        }
        return {group_num, ids};
    }
    std::vector<std::vector<int>> scc() {
        auto ids = scc_ids();
        int group_num = ids.first;
        std::vector<int> counts(group_num);
        for (auto x : ids.second) counts[x]++;
        std::vector<std::vector<int>> groups(ids.first);
        for (int i = 0; i < group_num; i++) {
            groups[i].reserve(counts[i]);
        }
        for (int i = 0; i < _n; i++) {
            groups[ids.second[i]].push_back(i);
        }
        return groups;
    }
  private:
    int _n;
    struct edge {
        int to;
    };
    std::vector<std::pair<int, edge>> edges;
};
}  // namespace internal
}  // namespace atcoder
#endif  // ATCODER_INTERNAL_SCC_HPP
#ifndef ATCODER_TWOSAT_HPP
#define ATCODER_TWOSAT_HPP 1
#include <cassert>
#include <vector>
namespace atcoder {
// Reference:
// B. Aspvall, M. Plass, and R. Tarjan,
// A Linear-Time Algorithm for Testing the Truth of Certain Quantified Boolean
// Formulas
struct two_sat {
  public:
    two_sat() : _n(0), scc(0) {}
    two_sat(int n) : _n(n), _answer(n), scc(2 * n) {}
    void add_clause(int i, bool f, int j, bool g) {
        assert(0 <= i && i < _n);
        assert(0 <= j && j < _n);
        scc.add_edge(2 * i + (f ? 0 : 1), 2 * j + (g ? 1 : 0));
        scc.add_edge(2 * j + (g ? 0 : 1), 2 * i + (f ? 1 : 0));
    }
    bool satisfiable() {
        auto id = scc.scc_ids().second;
        for (int i = 0; i < _n; i++) {
            if (id[2 * i] == id[2 * i + 1]) return false;
            _answer[i] = id[2 * i] < id[2 * i + 1];
        }
        return true;
    }
    std::vector<bool> answer() { return _answer; }
  private:
    int _n;
    std::vector<bool> _answer;
    internal::scc_graph scc;
};
}  // namespace atcoder
#endif  // ATCODER_TWOSAT_HPP
using namespace atcoder;

ll gridtoid(ll i, ll j, ll M) {
    return i*M+j;
}

pll idtogrid(ll id, ll M) {
    return divmod(id, M);
}

void solve() {
    ll N, M;
    cin >> N >> M;

    list2d(grid, N, M, ll, 0);
    rep(i, 0, N) rep(j, 0, M) cin >> grid[i][j];

    // ts[i] := iマス目を+1するか
    two_sat ts(N*M);
    ll i, j;
    rep(h, 0, N) {
        rep(w, 0, M) {
            i = gridtoid(h, w, M);
            if (h != N-1) {
                j = gridtoid(h+1, w, M);
                if (grid[h][w] == grid[h+1][w]) {
                    ts.add_clause(i, true, j, true);
                    ts.add_clause(i, false, j, false);
                }
                if (grid[h][w]+1 == grid[h+1][w]) {
                    ts.add_clause(i, false, j, true);
                }
                if (grid[h][w] == grid[h+1][w]+1) {
                    ts.add_clause(i, true, j, false);
                }
            }
            if (w != M-1) {
                j = gridtoid(h, w+1, M);
                if (grid[h][w] == grid[h][w+1]) {
                    ts.add_clause(i, true, j, true);
                    ts.add_clause(i, false, j, false);
                }
                if (grid[h][w]+1 == grid[h][w+1]) {
                    ts.add_clause(i, false, j, true);
                }
                if (grid[h][w] == grid[h][w+1]+1) {
                    ts.add_clause(i, true, j, false);
                }
            }
        }
    }

    ts.satisfiable();
    vector<bool> res = ts.answer();
    list2d(ans, N, M, ll, 0);
    rep(h, 0, N) {
        rep(w, 0, M) {
            i = gridtoid(h, w, M);
            if (res[i]) {
                ans[h][w] = grid[h][w] + 1;
            } else {
                ans[h][w] = grid[h][w];
            }
        }
    }
    rep(i, 0, N) {
        print(ans[i]);
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while(T--) solve();

    return 0;
}
