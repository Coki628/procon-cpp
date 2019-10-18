/**
 * ・蟻本演習2-4-3
 * ・並行二分探索
 * ・AC0.2秒。
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<ll, int, int> tlii;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
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
};

int N, M, Q, a, b, m;
vector<pii> edges;
vector<int> X, Y, OK, NG;
UnionFind uf;
vector<vector<int>> mid;
bool changed;

int main() {

    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> M;
    // 1回目の結合前を表す番兵
    edges.pb(mkp(0, 0));
    rep(i, 0, M) {
        cin >> a >> b;
        edges.pb(mkp(a, b));
    }
    cin >> Q;
    X.resize(Q);
    Y.resize(Q);
    rep(i, 0, Q) {
        cin >> X[i] >> Y[i];
    }

    OK.resize(Q, M+1);
    NG.resize(Q, -1);
    mid.resize(M+1);
    changed = true;
    while (changed) {
        changed = false;
        uf = UnionFind(N);
        rep(i, 0, M+1) mid[i].clear();

        // 各クエリiを、現在のOK,NG位置に応じたmに配置していく
        rep(i, 0, Q) {
            if (NG[i]+1 < OK[i]) {
                m = (OK[i]+NG[i]) / 2;
                mid[m].pb(i);
            }
        }

        rep(i, 0, M+1) {
            int a = edges[i].first;
            int b = edges[i].second;
            uf.merge(a, b);
            // i回結合後の状態で各クエリをOKとNGに振り分ける
            for (int m : mid[i]) {
                changed = true;
                if (uf.is_same(X[m], Y[m])) {
                    OK[m] = i;
                } else {
                    NG[m] = i;
                }
            }
        }
    }

    rep(i, 0, Q) {
        if (OK[i] > M) {
            print(-1);
        } else {
            print(OK[i]);
        }
    }
    return 0;
}
