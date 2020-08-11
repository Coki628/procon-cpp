/**
 * ・終了後自力AC、D手こずってなければ間に合ったかもしれないけど。。
 * ・グラフ、DFS、木の走査、優先度付きキュー
 * ・まずは前処理。DFSで辺毎に通る葉の数を数える。
 * ・あとは優先度付きキューに各辺のコストを詰めれば貪欲にやれる。
 * ・でも時間内はサンプルでWA、直しきれず終了。。
 * ・キューに詰めるコストとして、現在の状態のコストを使ってしまっていたのが原因。
 * 　考えてみたらそこじゃない。必要なのは次に操作した時に減らせるコスト量。
 * ・そこを直したら無事AC。これRated参戦だったらかなり悔しかったなー。。
 * ・あとpriority_queueにclear()がなくて初期化どうするか悩んだんだけど、
 * 　ググったらそもそもclearさせる設計じゃないとかそんな感じみたい。なのでグローバルに置かない、
 * 　が正解っぽい。どうしてもclearしたかったらwhile (!que.empty()) que.pop();する。
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
const ll INF = LONG_LONG_MAX;
const ll MOD = 1000000007;

void print(ld out) { cout << fixed << setprecision(15) << out << '\n'; }
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
pll divmod(ll a, ll b) { ll d = a / b; ll m = a % b; return {d, m}; }

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }

ll N, K;
// edges[i].first := 辺iの1回分のコスト
// edges[i].second := 辺iを通る葉の数
vector<pll> edges;
map<pll, ll> edgetoi;
vvl nodes;

ll dfs(ll u, ll prev) {
    ll res = 0;
    for (ll v : nodes[u]) {
        if (v == prev) continue;
        res += dfs(v, u);
    }
    if (int(nodes[u].size() == 1)) {
        res++;
    }
    if (prev != -1) {
        if (prev < u) {
            swap(u, prev);
        }
        edges[edgetoi[{u, prev}]].second = res;
    }
    return res;
}

void solve() {
    edges.clear();
    edgetoi.clear();
    nodes.clear();

    cin >> N >> K;
    nodes.resize(N);
    edges.resize(N-1);
    ll a, b, c;
    rep(i, 0, N-1) {
        cin >> a >> b >> c;
        a--; b--;
        if (b < a) {
            swap(a, b);
        }
        nodes[a].pb(b);
        nodes[b].pb(a);
        edges[i] = {c, 0};
        edgetoi[{a, b}] = i;
    }

    // まずは普通のDFSで各辺にかかる葉の枚数を集めてくる
    dfs(0, -1);

    // que.top().first := 次に操作すると減らせるコスト量の最大値
    // que.top().second := 操作する辺のindex
    priority_queue<pll, vector<pll>> que;
    // cost[i] := 現在の辺iにかかっている総コスト
    vector<ll> cost(N-1);
    ll total = 0, nxt;
    rep(i, 0, N-1) {
        // 操作前の状態のコスト
        cost[i] = edges[i].first * edges[i].second;
        total += cost[i];
        // 次に操作した時に減らせるコスト
        nxt = ceil(edges[i].first, 2) * edges[i].second;
        que.push({nxt, i});
    }

    ll cnt = 0, cur, idx;
    while (!que.empty() && total > K) {
        // 減らせるコストが一番大きい辺を取得
        tie(cur, idx) = que.top(); que.pop();
        // 更新前のコストを合計から引く
        total -= cost[idx];
        // この辺を操作する
        edges[idx].first /= 2;
        // コストを更新して、合計に足す
        cost[idx] = edges[idx].first * edges[idx].second;
        total += cost[idx];
        // 次に操作した時に減らせるコストをキューに戻す
        nxt = ceil(edges[idx].first, 2) * edges[idx].second;
        que.push({nxt, idx});
        cnt++;
    }
    print(cnt);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while(T--) solve();

    return 0;
}
