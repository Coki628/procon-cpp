/**
 * 参考：https://img.atcoder.jp/tokiomarine2020/editorial.pdf
 * ・自力ならず。まあこれはしょうがない。
 * ・グラフ、二分木、木上でナップザック、ビット全探索
 * ・想定解からして計算量1億と大変なやつなので最初からC++で。
 * ・根に近い方半分はDFSして前からナップザック。
 * ・葉に近い方半分はクエリの都度、ビット全探索。
 * ・どっちも10万*500=5000万くらいなので、合わせて1億。攻めてる。。
 * ・出てくる変数が多くてゴチャゴチャするけど、自分が高得点取れるとしたら
 * 　こういう実装頑張れ系だと思うので、しっかり解けるようにしていきたい。
 * ・最初、MLE対策でDP配列をintにする以外はいつも通りllでやったらAC2.8秒。(制約3秒)
 * ・今回10億を超える心配は基本的にない(はず)なので、全部intにしたら2.4秒。
 * 　やっぱり計算量厳しいところではこの辺も大きく関係してくるなー。
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

int N, Q;
const int M = 1<<9;
const int MAXW = 100000;
vector<int> V, W, par;
vvi nodes;
int dp[M+1][MAXW+1];

void dfs(int u, int prev, int depth) {
    // DPで見る深さは9まで
    if (depth == 9) return;
    // 木上でやること以外は普通のナップザックと同じ
    rep(w, 0, MAXW+1) {
        chmax(dp[u+1][w], dp[prev+1][w]);
        if (w+W[u] <= MAXW) {
            chmax(dp[u+1][w+W[u]], dp[prev+1][w] + V[u]);
        }
    }
    for (int v : nodes[u]) {
        if (prev == v) continue;
        dfs(v, u, depth+1);
    }
    return;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    V.resize(N);
    W.resize(N);
    par.resize(N);
    nodes.resize(N);
    rep(i, 0, N) cin >> V[i] >> W[i];

    int v;
    par[0] = -1;
    rep(u, 2, N+1) {
        v = u / 2;
        nodes[u-1].pb(v-1);
        nodes[v-1].pb(u-1);
        par[u-1] = v - 1;
    }
    dfs(0, -1, 0);

    cin >> Q;
    int x, L, cur, ans, bitln, w;
    vector<int> li;
    rep(_, 0, Q) {
        cin >> x >> L;
        x--;

        li.clear();
        cur = x;
        // 今回見る頂点xを根まで遡る
        while (cur != -1) {
            li.pb(cur);
            cur = par[cur];
        }
        // 深さが9以内ならDPした結果を出力
        if (li.size() <= 9) {
            ans = dp[x+1][L];
            print(ans);
        // 9を超えるならビット全探索する
        } else {
            ans = 0;
            bitln = li.size() - 9;
            rep(bit, 0, 1<<bitln) {
                v = w = 0;
                rep(i, 0, bitln) {
                    // ビットが立っていたら頂点li[i]は使う
                    if (bit>>i & 1) {
                        v += V[li[i]];
                        w += W[li[i]];
                    }
                }
                // この時点で重さLオーバーならスキップ
                if (w > L) continue;
                // OKなら、DPとビット全探索の結果を合わせる
                chmax(ans, v + dp[li[bitln]+1][L-w]);
            }
            print(ans);
        }
    }
    return 0;
}
