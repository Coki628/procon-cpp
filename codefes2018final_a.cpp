/**
 * ・pythonでTLEしたやつ、試しにc++でも作ってみたけどやっぱTLEだね。
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define all(obj) (obj).begin(), (obj).end()
#define pb push_back
#define str to_string
const ll INF = 1e18;
const ll MOD = 1e9 + 7;
void chmax(ll &a, ll b) { a = max(a, b); }
void chmin(ll &a, ll b) { a = min(a, b); }

int main() {
	int N, M, a, b, l;
	cin >> N >> M;
    vector<vector<ll> > nodes1(N);
    vector<vector<ll> > nodes2(N);
    unordered_map<string, ll> graph;
    rep(i, 0, M) {
        cin >> a >> b >> l;
        nodes2[a-1].pb(b-1);
        nodes1[b-1].pb(a-1);
        graph[str(a-1)+","+str(b-1)] = l;
    }

    ll cnt = 0;
    rep(i, 0, N) for(int u: nodes1[i]) for(int v: nodes2[i]) {
        if (graph[str(u)+','+str(i)] + graph[str(i)+','+str(v)] == 2540) {
            cnt++;
        }
    }

	cout << cnt << endl;
	return 0;
}
