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


ll gridtoid(ll i, ll j, ll W) {
    return i*W+j;
}


pll idtogrid(ll id, ll W) {
    return divmod(id, W);
}


// グリッドBFS
vvi bfs(vector<vector<char>> grid, vector<pii> src) {
    int H = grid.size();
    int W = grid[0].size();
    const vector<pii> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    vvi dist(H, vector<int>(W, INF));
    queue<pii> que;
    int h, w, dh, dw, h2, w2;
    for (auto p : src) {
        tie(h, w) = p;
        que.push(p);
        dist[h][w] = 0;
    }
    while (!que.empty()) {
        tie(h, w) = que.front(); que.pop();
        for (auto p : directions) {
            tie(dh, dw) = p;
            h2 = h + dh;
            w2 = w + dw;
            if (grid[h2][w2] == -1) {
                continue;
            }
            if (dist[h2][w2] != INF) {
                continue;
            }
            dist[h2][w2] = dist[h][w] + 1;
            que.push({h2, w2});
        }
    }
    return dist;
}


// グリッド転置
template<typename T>
void transpose(vector<vector<T>> &grid) {
    int H = grid.size();
    int W = grid[0].size();
    list2d(res, W, H, T, 0);
    rep(i, 0, H) {
        rep(j, 0, W) {
            res[j][i] = grid[i][j];
        }
    }
    swap(res, grid);
}
