/**
 * ・600点自力AC！(pypyTLEでこっちでAC)
 * ・幾何と見せかけてグラフに帰着。
 * ・各円を頂点とみなして、全円間で距離取って辺としてつなぐ。
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
typedef vector<vector<double>> vvd;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define btoe(obj) (obj).begin(), (obj).end()
#define pb push_back
#define str to_string
#define mkp make_pair
const ll INF = 1e18;
const ll MOD = 1e9 + 7;
void chmax(ll &a, ll b) { a = max(a, b); }
void chmin(ll &a, ll b) { a = min(a, b); }

void print(ld out) {
    cout << fixed << setprecision(12) << out << '\n';
}

template<typename T>
void print(T out) {
    cout << out << '\n';
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

template<typename T>
vector<T> dijkstra(int N, vector<vector<pair<ll, T>>> nodes, int src) {

    vector<T> res(N, INF);
    res[src] = 0;
    priority_queue<pair<T, ll>, vector<pair<T, ll>>, greater<pair<T, ll>>> que;
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

ll sx, sy, tx, ty, N, x, y, r, x1, _y1, r1, x2, y2, r2;
ld dist, cost;
vector<pplll> XYR;
vector<vector<pld>> nodes;
vector<ld> res;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> sx >> sy >> tx >> ty;
    cin >> N;
    rep(i, 0, N) {
        cin >> x >> y >> r;
        XYR.pb(mkp(mkp(x, y), r));
    }
    // 始点と終点も半径0の円とする
    XYR.pb(mkp(mkp(sx, sy), 0));
    XYR.pb(mkp(mkp(tx, ty), 0));
    N += 2;

    // 各円を頂点としたグラフとみなす
    nodes.resize(N);
    rep(i, 0, N) {
        x1 = XYR[i].first.first;
        _y1 = XYR[i].first.second;
        r1 = XYR[i].second;
        rep(j, i+1, N) {
            x2 = XYR[j].first.first;
            y2 = XYR[j].first.second;
            r2 = XYR[j].second;
            dist = hypot(x1 - x2, _y1 - y2);
            // 2円間の距離(重なっていれば0)
            cost = max(dist - (r1+r2), ld(0));
            nodes[i].pb(mkp(j, cost));
            nodes[j].pb(mkp(i, cost));
        }
    }

    res = dijkstra(N, nodes, N-2);
    print(res[N-1]);
    return 0;
}
