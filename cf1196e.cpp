/**
 * ・バチャ終了後だいたい自力AC。(テストケース見た。そこに手がかりはほぼなかったけど)
 * ・実装時間かかった。。
 * ・グリッドDFS、再帰
 * ・1方向に突き進めるだけ進んでから次に向かう、をしたかったので、
 * 　スタックだとうまくいかず、再帰のDFSでやるためにC++実装。
 * ・C++って関数内で関数定義できないのな。不便ー。。
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

inline ll pow(int x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
inline ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

inline ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
inline ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }

int popcount(ll S) { return __builtin_popcountll(S); }

ll B, W, Q;
const ll MAX = 1000000000;
vector<pll> directions = { mkp(1, 0), mkp(-1, 0), mkp(0, 1), mkp(0, -1) };

void rec(pll cur, ll &bcnt, ll &wcnt, unordered_map<ll, unordered_map<ll, bool>> &visited, vector<pll> &res) {
    for (pll nxt : directions) {
        ll h = nxt.first + cur.first;
        ll w = nxt.second + cur.second;
        bool is_blk = (h + w) % 2;
        if (h <= 0 || h > MAX || w <= 0 || w > MAX) continue;
        if (is_blk && bcnt == 0 || !is_blk && wcnt == 0) continue;
        if (visited[h][w]) continue;
        visited[h][w] = 1;
        if (is_blk) {
            bcnt--;
        } else {
            wcnt--;
        }
        res.pb(mkp(h, w));
        rec(mkp(h, w), bcnt, wcnt, visited, res);
    }
}

vector<pll> dfs(pll src, ll bcnt, ll wcnt) {
    ll h = src.first, w = src.second;
    vector<pll> res;
    unordered_map<ll, unordered_map<ll, bool>> visited;
    visited[h][w] = 1;
    res.pb(mkp(h, w));

    rec(src, bcnt, wcnt, visited, res);
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> Q;
    rep(_, 0, Q) {
        cin >> B >> W;
        vector<pll> res;
        if (B >= W) {
            res = dfs(mkp(MAX/2+1, MAX/2), B-1, W);
        } else {
            res = dfs(mkp(MAX/2, MAX/2), B, W-1);
        }
        if (res.size() < B + W) {
            print("NO");
        } else {
            print("YES");
            for (auto a : res) {
                print(a);
            }
        }
    }
    return 0;
}
