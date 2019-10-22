/**
 * 参考：http://tsutaj.hatenablog.com/entry/2016/12/31/160154
 * ・蟻本演習2-5-3
 * ・最小全域木応用
 * ・問題は要約すると、全ての最小全域木に含まれるような辺を列挙するってこと。
 * ・pythonTLEで通らなかったのでC++に写経。
 * ・AC0.1秒。計算量は約N*M^2/2で6200万くらい。
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<ll, int, int> tlii;
typedef pair<ll, ll> pll;
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
// #define print(out) cout << (out) << endl
const ll INF = 1e18;
const ll MOD = 1e9 + 7;
void chmax(ll &a, ll b) { a = max(a, b); }
void chmin(ll &a, ll b) { a = min(a, b); }

template<typename Any>
void print(Any out) {
    cout << out << '\n';
}

template<typename T1, typename T2>
void print(pair<T1, T2> out) {
    cout << out.first << ' ' << out.second << '\n';
}

void print(vector<ll> A) {
    rep(i, 0, A.size()) {
        cout << A[i];
        cout << (i == A.size()-1 ? '\n' : ' ');
    }
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

    // 根の検索(グループ番号)
    int find(int x) {
        // 根ならその番号を返す
        if (par[x] == x) {
            return x;
        } else {
            // 走査していく過程で親を書き換える
            par[x] = find(par[x]);
            return par[x];
        }            
    }

    // 併合
    void merge(int a, int b) {
        // 根を探す
        int x = find(a);
        int y = find(b);
        // 木の高さを比較し、低いほうから高いほうに辺を張る
        if (rank[x] < rank[y]) {
            par[x] = y;
            size[y] += size[x];
        } else {
            par[y] = x;
            size[x] += size[y];
            // 木の高さが同じなら片方を1増やす
            if (rank[x] == rank[y]) {
                rank[x] += 1;
            }
        }
    }

    // 同じ集合に属するか判定
    bool is_same(int a, int b) {
        return find(a) == find(b);
    }

    // あるノードの属する集合のノード数
    int get_size(int x) {
        return size[find(x)];
    }

    // 集合の数
    int get_len() {
        set<int> res;
        rep(i, 0, n+1) {
            res.insert(find(i));
        }
        // グループ0の分を引いて返却
        return res.size() - 1;
    }
};

int N, M, a, b, c;
ll cost, mncost, ans;
vector<ppiil> edges;
UnionFind uf;
vector<int> ids, needs;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> M;
    edges.resize(M);
    rep(i, 0, M) {
        cin >> a >> b >> c;
        edges[i] = mkp(mkp(a, b), c);
    }

    // コストでソート
    sort(all(edges), [](const ppiil& e1, const ppiil& e2) { return e1.second < e2.second; });
    uf = UnionFind(N);
    cost = 0;
    rep(i, 0, M) {
        a = edges[i].first.first, b = edges[i].first.second, c = edges[i].second;
        if (!uf.is_same(a, b)) {
            uf.merge(a, b);
            cost += c;
            ids.pb(i);
        }
    }
    mncost = cost;

    for (int i : ids) {
        uf = UnionFind(N);
        cost = 0;
        rep(j, 0, M) {
            a = edges[j].first.first, b = edges[j].first.second, c = edges[j].second;
            // 辺iは使わない
            if (i == j) continue;
            if (!uf.is_same(a, b)) {
                uf.merge(a, b);
                cost += c;
            }
        }
        // 辺iなしで構築した時に、木にならなかったor最小コストにならなかったら、iは必須
        if (uf.get_len() != 1 || cost != mncost) {
            needs.pb(i);
        }
    }

    ans = 0;
    for (int i : needs) {
        ans += edges[i].second;
    }
    print({(ll)needs.size(), ans});
    return 0;
}
