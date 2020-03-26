/**
 * ・自力AC！
 * ・整数のグラフ、ワーシャルフロイド、ダイクストラ応用
 * ・整数の各値を頂点としてグラフを構築するやつ。(ABC077Dを思い出した)
 * ・計算量は、前にいた数字として0~9を添字に追加しているので、(最初これなかったらWAした)
 * 　10万*10=100万頂点のダイクストラって感じになる。
 * ・python,pypyはTLEしたのでこっちでAC0.5秒。
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
#define btoe(obj) (obj).begin(), (obj).end()
#define pb push_back
#define str to_string
#define mkp make_pair
const ll INF = 1e18;
const ll MOD = 1e9 + 7;
template<typename T> inline bool chmax(T &x, T y) { return (y > x) ? x = y, true : false; }
template<typename T> inline bool chmin(T &x, T y) { return (y < x) ? x = y, true : false; }

template<typename T>
void print(T out) {
    cout << out << '\n';
}

void print(ld out) {
    cout << fixed << setprecision(12) << out << '\n';
}

template<typename T1, typename T2>
void print(pair<T1, T2> out) {
    cout << out.first << ' ' << out.second << '\n';
}

template<typename T>
void print(vector<T> A) {
    rep(i, 0, A.size()) {
        cout << A[i];
        cout << (i == A.size()-1 ? '\n' : ' ');
    }
}

template<typename T>
void print(set<T> S) {
    vector<T> A(btoe(S));
    print(A);
}

ll sum(vector<ll> A) {
    ll res = 0;
    for (ll a: A) res += a;
    return res;
}

ll max(vector<ll> A) {
    ll res = -INF;
    for (ll a: A) chmax(res, a);
    return res;
}

ll min(vector<ll> A) {
    ll res = INF;
    for (ll a: A) chmin(res, a);
    return res;
}

ll sum(ll A[], int len) {
    ll res = 0;
    rep(i, 0, len) res += A[i];
    return res;
}

ll max(ll A[], int len) {
    ll res = -INF;
    rep(i, 0, len) chmax(res, A[i]);
    return res;
}

ll min(ll A[], int len) {
    ll res = INF;
    rep(i, 0, len) chmin(res, A[i]);
    return res;
}

ll toint(string s) {
    ll res = 0;
    for (char c : s) {
        res *= 10;
        res += (c - '0');
    }
    return res;
}

int toint(char c) {
    return c - '0';
}

inline ll pow(int a, ll b) {
    ll res = 1;
    rep(_, 0, b) res *= a;
    return res;
}

ll pow(ll x, ll n, int mod) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) {
            res = (res * x) % mod;
        }
        x = (x * x) % mod;
        n >>= 1;
    }
    return res;
}

ll floor(ll a, ll b) {
    if (a < 0) {
        return (a-b+1)/b;
    } else {
        return a/b;
    }
}

ll ceil(ll a, ll b) {
    if (a >= 0) {
        return (a+b-1)/b;
    } else {
        return a/b;
    }
}

template<typename T>
vector<vector<T>> warshall_floyd(vector<vector<T>> G) {
    ll N = G.size();
    rep(i, 0, N) G[i][i] = 0;
    rep(k, 0, N) {
        rep(i, 0, N) {
            rep(j, 0, N) {
                chmin(G[i][j], G[i][k] + G[k][j]);
            }
        }
    }
    rep(i, 0, N) {
        if (G[i][i] < 0) {
            return {};
        }
    }
    return G;
}

ll M, R;
vvl wf;
vvpll nodes;

template<typename T>
vvl dijkstra(vector<vector<pair<ll, T>>> nodes, int src) {

    ll N = nodes.size();
    // res[i][j] := 今いるキーがiで、入力した数値がjの時の最小コスト
    vvl res(10, vector<ll>(N, INF));
    priority_queue<pplii, vector<pplii>, greater<pplii>> que;
    res[0][src] = 1;
    que.push(mkp(mkp(0, src), 0));

    pplii p;
    ll dist, cost;
    int cur, nxt, a;
    while(!que.empty()) {
        p = que.top(); que.pop();
        dist = p.first.first;
        cur = p.first.second;
        a = p.second;
        if (res[a][cur] < dist) {
            continue;
        }
        // 0~9のキーを押す
        rep(nxta, 0, 10) {
            nxt = (cur*10 + nxta) % M;
            cost = wf[a][nxta] + 1;
            if (dist + cost < res[nxta][nxt]) {
                res[nxta][nxt] = dist + cost;
                que.push(mkp(mkp(dist+cost, nxt), nxta));
            }
        }
    }
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> M >> R;

    // 各キー間の移動距離を前計算
    vvl G(10, vector<ll>(10, INF));
    G[0][1] = G[1][0] = 1;
    G[1][2] = G[2][1] = G[1][4] = G[4][1] = 1;
    G[2][3] = G[3][2] = G[2][5] = G[5][2] = 1;
    G[3][6] = G[6][3] = 1;
    G[4][7] = G[7][4] = G[4][5] = G[5][4] = 1;
    G[5][8] = G[8][5] = G[5][6] = G[6][5] = 1;
    G[6][9] = G[9][6] = 1;
    G[7][8] = G[8][7] = 1;
    G[8][9] = G[9][8] = 1;
    wf = warshall_floyd(G);

    nodes.resize(M);
    vvl res = dijkstra(nodes, 0);
    ll ans = INF;
    rep(i, 0, 10) {
        chmin(ans, res[i][R]);
    }
    print(ans);
    return 0;
}
