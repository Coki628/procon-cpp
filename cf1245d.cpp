/**
 * ・200万辺に最小全域木
 * ・pypyTLEをさすがのAC0.3秒。
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<ll, int, int> tlii;
typedef pair<ll, ll> pll;
typedef pair<ll, int> pli;
typedef pair<int, int> pii;
typedef pair<pair<int, int>, ll> ppiil;
typedef vector<vector<ll>> vvl;
typedef vector<vector<int>> vvi;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define all(obj) (obj).begin(), (obj).end()
#define pb push_back
#define str to_string
#define mkp make_pair
#define mkt make_tuple
const ll INF = 1e18;
const ll MOD = 1e9 + 7;
void chmax(ll &a, ll b) { a = max(a, b); }
void chmin(ll &a, ll b) { a = min(a, b); }

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

struct UnionFind {

    int n;
    vector<int> par, rank, size;

    UnionFind(int n) : n(n) {
        par.resize(n+1);
        rank.resize(n+1);
        size.resize(n+1, 1);
        rep(i, 0, n+1) par[i] = i;
    }

    UnionFind() {}

    int find(int x) {
        if (par[x] == x) {
            return x;
        } else {
            par[x] = find(par[x]);
            return par[x];
        }            
    }

    void merge(int a, int b) {
        int x = find(a);
        int y = find(b);
        if (rank[x] < rank[y]) {
            par[x] = y;
            size[y] += size[x];
        } else {
            par[y] = x;
            size[x] += size[y];
            if (rank[x] == rank[y]) {
                rank[x] += 1;
            }
        }
    }

    bool is_same(int a, int b) {
        return find(a) == find(b);
    }

    int get_size(int x) {
        return size[find(x)];
    }

    int get_size() {
        set<int> res;
        rep(i, 0, n+1) {
            res.insert(find(i));
        }
        return res.size() - 1;
    }
};

int N;
ll total;
vector<pii> edges, cities;
vector<ll> C, K, stations;
vector<ppiil> edges2;
UnionFind uf;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    edges.resize(N);
    C.resize(N);
    K.resize(N);
    uf = UnionFind(N+1);
    rep(i, 0, N) {
        cin >> edges[i].first >> edges[i].second;
    }
    rep(i, 0, N) cin >> C[i];
    rep(i, 0, N) cin >> K[i];

    // 各頂点から大元の発電所への辺
    rep(i, 0, N) {
        edges2.pb(mkp(mkp(i, N), C[i]));
    }
    // 各頂点同士の辺
    rep(i, 0, N) {
        int x1 = edges[i].first, y1 = edges[i].second;
        ll c1 = C[i], k1 = K[i];
        rep(j, i+1, N) {
            int x2 = edges[j].first, y2 = edges[j].second;
            ll c2 = C[j], k2 = K[j];
            ll dist = abs(x1-x2) + abs(y1-y2);
            edges2.pb(mkp(mkp(i, j), dist * (k1+k2)));
        }
    }
    sort(all(edges2), [](const ppiil& e1, ppiil& e2) { return e1.second < e2.second; });

    total = 0;
    for (ppiil edge : edges2) {
        int a = edge.first.first, b = edge.first.second;
        ll c = edge.second;
        if (!uf.is_same(a, b)) {
            uf.merge(a, b);
            total += c;
            if (b == N) {
                stations.pb(a+1);
            } else {
                cities.pb(mkp(a+1, b+1));
            }
        }
        if (uf.get_size(N) == N+1) {
            break;
        }
    }

    print(total);
    print(stations.size());
    sort(all(stations));
    print(stations);
    print(cities.size());
    for (pii edge : cities) {
        print(edge);
    }
    return 0;
}
