/**
 * ・自力AC！
 * ・最初ちょっと方針間違ったけど(三分探索して死亡)、ちゃんとすぐに修正できた。
 * ・ダイクストラはやるだけ。その後の各距離でのコスト計算は、小さい方から順番に進めれば、
 * 　最終的に線形時間で全部チェックできる。
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
vector<T> dijkstra(vector<vector<pair<ll, T>>> nodes, int src) {

    ll N = nodes.size();
    vector<T> res(N, INF);
    priority_queue<pair<T, ll>, vector<pair<T, ll>>, greater<pair<T, ll>>> que;
    res[src] = 0;
    que.push(mkp(0, src));

    while(!que.empty()) {
        pll p = que.top(); que.pop();
        ll dist = p.first;
        int cur = p.second;
        if (res[cur] < dist) {
            continue;
        }
        for (auto p: nodes[cur]) {
            ll nxt = p.first;
            T cost = p.second;
            if (res[cur] + cost < res[nxt]) {
                res[nxt] = res[cur] + cost;
                que.push(mkp(res[nxt], nxt));
            }
        }
    }
    return res;
}

ll N, M, C, dsm;
vvpll nodes, nodes2;
map<ll, vector<ll>> D;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> M >> C;
    nodes.resize(N);
    nodes2.resize(N);
    ll a, b, c;
    rep(i, 0, M) {
        cin >> a >> b >> c;
        a--; b--;
        nodes[a].pb(mkp(b, c));
        nodes[b].pb(mkp(a, c));
        // 各頂点、どの辺が繋がっているかも覚えておく
        nodes2[a].pb(mkp(c, i));
        nodes2[b].pb(mkp(c, i));
        dsm += c;
    }

    vector<ll> dist = dijkstra(nodes, 0);
    rep(i, 0, N) {
        // 頂点0からの距離毎にまとめておく
        D[dist[i]].pb(i);
    }
    vector<int> edgecnt(M, 2);
    ll ans = INF;
    // 距離が近い方から順番に見ていく
    for (auto p : D) {
        for (ll u : p.second) {
            for (auto p2 : nodes2[u]) {
                edgecnt[p2.second]--;
                // 2回出現したら、この辺はもう不要
                if (edgecnt[p2.second] == 0) {
                    dsm -= p2.first;
                }
            }
        }
        // この距離の頂点と繋がる辺を全てチェックしたら、コストを計算
        chmin(ans, C * p.first + dsm);
    }
    print(ans);
    return 0;
}
