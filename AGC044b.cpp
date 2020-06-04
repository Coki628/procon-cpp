/**
 * ・グリッド、01BFS
 * ・C++でも通らないや。。TLE。
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

int bfs01(vvi &dist, pii src) {
    int H = dist.size();
    int W = dist[0].size();
    vector<pii> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    vector<vector<bool>> visited(H, vector<bool>(W, 0));
    deque<tuple<int, int, int>> que;
    int h, w, dh, dw, h2, w2, cost;

    tie(h, w) = src;
    que.pb({0, h, w});
    visited[h][w] = 1;
    dist[h][w] = 0;
    while (!que.empty()) {
        tie(cost, h, w) = que.front(); que.pop_front();
        for (auto p : directions) {
            tie(dh, dw) = p;
            h2 = h + dh;
            w2 = w + dw;
            if (h2 < 0 || w2 < 0 || h2 >= H || w2 >= W) {
                tie(h, w) = src;
                dist[h][w] = cost;
                return cost;
            }
            if (visited[h2][w2]) {
                continue;
            }
            visited[h2][w2] = 1;
            if (dist[h2][w2] == -1) {
                que.push_front({cost, h2, w2});
            } else {
                que.pb({cost+1, h2, w2});
            }
        }
    }
}

ll N;
vector<ll> P;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    P.resize(N*N);
    vvi dist(N, vector<int>(N, -1));
    int p;
    rep(i, 0, N*N) {
        cin >> p;
        P[i] = --p;
    }

    ll ans = 0, h, w;
    reverse(P.begin(), P.end());
    for (auto p : P) {
        h = p / N;
        w = p % N;
        ans += bfs01(dist, {h, w});
    }
    print(ans);
    return 0;
}
