/**
 * ・しっかり自力AC！
 * ・グリッドダイクストラ
 * ・通行料金を使ったor使ってないのフラグを持たせて、後は普通にダイクストラする。
 * ・500*500=25万グリッドならまだpypyでも間に合うかと思ったらダメだった。。C++で無事AC0.17秒。
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

// グリッドダイクストラ(H*Wグリッド, 始点{h, w}) 
using P = tuple<ll, bool, int, int>;
vector<vector<vector<ll>>> dijkstra(vvl grid, pll src) {

    int H = grid.size();
    int W = grid[0].size();
    auto res = list3d(2, H, W, INF);
    auto [sh, sw] = src;
    const vector<pii> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    priority_queue<P, vector<P>, greater<P>> que;
    que.push({0, 0, sh, sw});
    res[0][sh][sw] = 0;

    while (!que.empty()) {
        auto [dist, used, h, w] = que.top(); que.pop();
        if (res[used][h][w] < dist) {
            continue;
        }
        for (auto [dh, dw] : directions) {
            int nh = h + dh;
            int nw = w + dw;
            if (grid[nh][nw] == -1) {
                continue;
            }
            ll cost = grid[nh][nw];
            if (dist + cost < res[used][nh][nw]) {
                res[used][nh][nw] = dist + cost;
                que.push({dist+cost, used, nh, nw});
            }
            if (cost > 1 and !used) {
                cost = 1;
                if (dist + cost < res[1][nh][nw]) {
                    res[1][nh][nw] = dist + cost;
                    que.push({dist+cost, 1, nh, nw});
                }
            }
        }
    }
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N, M;
    cin >> N >> M;
    auto grid = list2d(N+2, N+2, 1LL);
    rep(i, 0, N+2) {
        grid[i][0] = -1;
        grid[i][N+1] = -1;
        grid[0][i] = -1;
        grid[N+1][i] = -1;
    }
    rep(i, 0, M) {
        ll h, w, c;
        cin >> h >> w >> c;
        grid[h][w] += c;
    }

    auto res = dijkstra(grid, {1, 1});
    ll ans = min(res[0][N][N], res[1][N][N]);
    print(ans);
    return 0;
}
