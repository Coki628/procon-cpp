/**
 * ・自力AC！
 * ・最短経路、ダイクストラ
 * ・多点スタートのダイクストラ初めて使ったけど、ちゃんと動いて良かった。
 * 　BFSでやったことあるのと同じ要領で、多分できるだろうとは思ったけど。
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
const ll MOD = 100000;
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
vector<T> dijkstra(vector<vector<pair<ll, T>>> nodes, vector<ll> src) {

    ll N = nodes.size();
    vector<T> res(N, INF);
    priority_queue<pair<T, ll>, vector<pair<T, ll>>, greater<pair<T, ll>>> que;
    // 多点スタート
    for (ll v : src) {
        res[v] = 0;
        que.push(mkp(0, v));
    }
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

ll N, M, K;
vvpll nodes;
vector<ll> src;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    cin >> N >> M >> K;
    nodes.resize(N);
    ll a, b, c;
    rep(i, 0, M) {
        cin >> a >> b >> c;
        a--; b--;
        nodes[a].pb(mkp(b, c));
        nodes[b].pb(mkp(a, c));
    }
    src.resize(K);
    rep(i, 0, K) {
        cin >> src[i];
        src[i]--;
    }

    // モールのある全ての町を始点にダイクストラ
    vector<ll> res = dijkstra(nodes, src);
    ll ans = 0;
    rep(u, 0, N) {
        for (pll p : nodes[u]) {
            // uからモールへの距離 + この辺の長さ + vからモールへの距離 の真ん中
            chmax(ans, ceil(res[u] + p.second + res[p.first], 2));
        }
    }
    print(ans);
    return 0;
}
