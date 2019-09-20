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

int N, M, K;
vector<vector<pll>> nodes;
vector<pll> XY;

vvl dijkstra(vector<vector<pll>> nodes, int src) {
    // 2次元vectorをINFで初期化
    vvl res(K*2, vector<ll>(N, INF));

    res[0][src] = 0;
    priority_queue<tlii, vector<tlii>, greater<tlii>> que;
    que.push(mkt(0, 0, src));

    while(!que.empty()) {
        tlii tpl = que.top(); que.pop();
        ll dist = get<0>(tpl);
        int k = get<1>(tpl);
        int cur = get<2>(tpl);
        ll x = XY[cur].first;
        ll y = XY[cur].second;

        for (auto node: nodes[cur]) {
            ll nxt = node.first;
            ll cost = node.second;
            if (res[k][cur] + cost < res[k][nxt]) {
                res[k][nxt] = res[k][cur] + cost;
                que.push(mkt(res[k][nxt], k, nxt));
            }
            // 花を買う分のK方向の移動をする辺を追加する
            int idx = 0;
            while (x!=0 && k+idx*x<K) {
                idx++;
                ll nxtk = k+idx*x;
                ll cost2 = cost+idx*y;
                if (res[k][cur] + cost2 < res[nxtk][nxt]) {
                    res[nxtk][nxt] = res[k][cur] + cost2;
                    que.push(mkt(res[nxtk][nxt], nxtk, nxt));
                }
            }
        }
    }
    return res;
}

int main() {
	ll a, b, c;
	cin >> N >> M >> K;
    nodes.resize(N);
    rep(i, 0, M) {
        cin >> a >> b >> c;
        nodes[a-1].pb(mkp(b-1, c));
        nodes[b-1].pb(mkp(a-1, c));
    }
    // 最後の頂点はK方向だけの遷移をさせたいので自己ループを追加しておく
    nodes[N-1].pb(mkp(N-1, 0));

    rep(i, 0, N) {
        ll x, y;
        cin >> x >> y;
        XY.pb(mkp(x, y));
    }

    vvl res = dijkstra(nodes, 0);

    ll ans = INF;
    // 花をK本以上買った頂点Nから最小値を取る
    rep(k, K, K*2) {
        chmin(ans, res[k][N-1]);
    }
    if (ans!=INF) {
        print(ans);
    } else {
        print(-1);
    }
    return 0;
}
