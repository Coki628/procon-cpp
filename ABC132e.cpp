#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<ll, int, int> tlii;
typedef pair<ll, ll> pll;
typedef vector<vector<ll>> vvl;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define all(obj) (obj).begin(), (obj).end()
#define pb push_back
#define str to_string
#define mkp make_pair
#define mkt make_tuple
#define print(out) cout << (out) << endl
const ll INF = 1e18;
const ll MOD = 1e9 + 7;
void chmax(ll &a, ll b) { a = max(a, b); }
void chmin(ll &a, ll b) { a = min(a, b); }

int N, M;
vector<vector<ll>> nodes;
vector<vector<ll>> nodes2;
vector<pll> edges2;
bool visited[100007][4];

vector<ll> dijkstra(vector<vector<ll>> nodes, int src) {

    vector<ll> res(N, INF);
    res[src] = 0;
    priority_queue<pll, vector<pll>, greater<pll>> que;
    que.push(mkp(0, src));

    while(!que.empty()) {
        pll p = que.top(); que.pop();
        ll dist = p.first;
        int cur = p.second;

        for (ll nxt: nodes[cur]) {
            int cost = 1;
            if (res[cur] + cost < res[nxt]) {
                res[nxt] = res[cur] + cost;
                que.push(mkp(res[nxt], nxt));
            }
        }
    }
    return res;
}

void rec(ll org, ll u, int cnt) {

    if (visited[u][cnt]) return;
    visited[u][cnt] = true;

    if (cnt==3) {
        edges2.pb(mkp(org, u));
        return;
    }
    for (ll v: nodes[u]) {
        rec(org, v, cnt+1);
    }
    return;
}

int main() {
	ll a, b, c;
    int S, T;
	cin >> N >> M;
    nodes.resize(N);
    nodes2.resize(N);
    rep(i, 0, M) {
        cin >> a >> b;
        nodes[--a].pb(--b);
    }
    cin >> S >> T;
    --S;
    --T;

    rep(i, 0, N) {
        memset(visited, false, sizeof(visited));
        rec(i, i, 0);
    }
    for (pll edge: edges2) {
        int u = edge.first;
        int v = edge.second;
        nodes2[u].pb(v);
    }

    vector<ll> res = dijkstra(nodes2, S);

    ll ans = res[T];
    if (ans!=INF) {
        print(ans);
    } else {
        print(-1);
    }
    return 0;
}
