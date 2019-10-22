/**
 * 参考：http://www.utpc.jp/2013/slides/F.pdf
 * 　　　http://kmjp.hatenablog.jp/entry/2014/04/04/1000
 * 　　　https://competitive12.blogspot.com/2019/07/utpc-2013-f.html
 * ・蟻本演習2-5-3
 * ・最小全域木応用
 * ・必要な辺だけを使いながら何回もクラスカルする。
 * ・実装バグらせまくって大変だった。最終的にだいたい内容はkmjpさんの写経。。
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

int N, M, Q, a, b, p, q, proot, qroot, nxtroot;
ll c, cost;
vector<ppiil> edges;
vector<vector<ppiil>>nxtedges;
vector<int> nodes1, nodes2;
UnionFind uf, uf2;
vvl G;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> M;
    G.resize(N);
    uf = UnionFind(N);
    nxtedges.resize(N);
    rep(i, 0, N) G[i].resize(N, INF);
    rep(i, 0, M) {
        cin >> a >> b >> c;
        G[a][b] = c;
        G[b][a] = c;
    }

    cin >> Q;
    rep(i, 0, Q) {
        cin >> p >> q;
        proot = uf.find(p);
        qroot = uf.find(q);
        edges.clear();
        // 前回の併合で使った辺(今回併合するグループのものだけ)
        for (ppiil edge : nxtedges[proot]) edges.pb(edge);
        for (ppiil edge : nxtedges[qroot]) edges.pb(edge);

        // 今回の併合で新たに使う辺を準備
        nodes1.clear();
        nodes2.clear();
        rep(i, 0, N) {
            // pのいるグループとqのいるグループの頂点だけを集める
            if (uf.find(i) == proot) nodes1.pb(i);
            if (uf.find(i) == qroot) nodes2.pb(i);
        }
        for (int a : nodes1) {
            for (int b : nodes2) {
                // pのいるグループからqのいるグループに出ている辺
                if (G[a][b] != INF) {
                    edges.pb(mkp(mkp(a, b), G[a][b]));
                }
            }
        }

        // 今回の併合での次の根を決める
        uf.merge(p, q);
        nxtroot = uf.find(p);
        nxtedges[nxtroot].clear();

        // コストでソート
        sort(all(edges), [](const ppiil& e1, const ppiil& e2) { return e1.second < e2.second; });
        uf2 = UnionFind(N);
        cost = 0;
        for (ppiil edge : edges) {
            a = edge.first.first, b = edge.first.second, c = edge.second;
            if (!uf2.is_same(a, b)) {
                uf2.merge(a, b);
                cost += c;
                // 次以降使う予定の辺はグループ毎に取っておく
                nxtedges[nxtroot].pb(edge);
            }
        }

        // 今回のクラスカルで実際に付けられた辺の数と、想定される全域木の辺の数の一致を確認
        if (nxtedges[nxtroot].size() == uf.get_size(nxtroot) - 1) {
            print(cost);
        } else {
            print("IMPOSSIBLE");
        }
    }
    return 0;
}
