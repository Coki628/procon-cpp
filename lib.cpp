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
#define btoe(obj) (obj).begin(), (obj).end()
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


// ここから関数

template<typename T>
map<T, ll> Counter(vector<T> A) {
    map<T, ll> res;
    for (T a : A) {
        res[a]++;
    }
    return res;
}

// 条件を満たす最小値を見つける二分探索
ll bisearch_min(ll mn, ll mx, function<bool(ll)> func) {

    ll ok = mx;
    ll ng = mn;
    while (ng+1 < ok) {
        ll mid = (ok+ng) / 2;
        if (func(mid)) {
            // 下を探しに行く
            ok = mid;
        } else {
            // 上を探しに行く
            ng = mid;
        }
    }
    return ok;
}

// 条件を満たす最大値を見つける二分探索
ll bisearch_max(ll mn, ll mx, function<bool(ll)> func) {

    ll ok = mn;
    ll ng = mx;
    while (ok+1 < ng) {
        ll mid = (ok+ng) / 2;
        if (func(mid)) {
            // 上を探しに行く
            ok = mid;
        } else {
            // 下を探しに行く
            ng = mid;
        }
    }
    return ok;
}

// 座標圧縮
typedef map<ll, int> mli;
typedef map<int, ll> mil;
pair<mli, mil> compress(set<ll> S) {
    mli zipped;
    mil unzipped;
    vector<ll> A(btoe(S));
    sort(btoe(A));
    rep(i, 0, A.size()) {
        zipped[A[i]] = i;
        unzipped[i] = A[i];
    }
    return mkp(zipped, unzipped);
}

// ダイクストラ(重み付き、テンプレートで小数コストも対応)
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


// ここからクラス

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
    int get_size() {
        set<int> res;
        rep(i, 0, n+1) {
            res.insert(find(i));
        }
        // グループ0の分を引いて返却
        return res.size() - 1;
    }
};


struct PartiallyPersistentUnionFind {

    int n;
    vector<int> par, last;

    PartiallyPersistentUnionFind(int n) : n(n) {
        // xが根のときはxを含むグループのサイズ(の-1倍)、そうでないときは親ノード
        par.resize(n+1, -1);
        // 最後に「根」ではなくなった瞬間の時刻
        last.resize(n+1, -1);
    }

    PartiallyPersistentUnionFind() {}

    // 根の検索(グループ番号)
    int find(int t, int x) {
        // 根ならその番号を返す
        if (last[x] == -1 || t < last[x]) {
            return x;
        } else {
            return find(t, par[x]);
        }
    }

    // 併合
    bool merge(int t, int a, int b) {
        // 根を探す
        int x = find(t, a);
        int y = find(t, b);
        if (x == y) {
            return false;
        }
        // 要素数の少ない方を付け替える(マージテク)
        if (par[x] > par[y]) {
            swap(x, y);
        }
        // xにyを付ける
        par[x] += par[y];
        par[y] = x;
        last[y] = t;
        return true;
    }

    // 同じ集合に属するか判定
    bool is_same(int t, int a, int b) {
        return find(t, a) == find(t, b);
    }
};


template<typename Monoid>
struct SegmentTree {
    using F = function<Monoid(Monoid, Monoid)>;
    
    int sz;
    vector<Monoid> seg;
    
    const F f;
    const Monoid M1;
    
    SegmentTree(int n, const F f, const Monoid &M1) : f(f), M1(M1) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.assign(2 * sz, M1);
    }

    SegmentTree(const F f, const Monoid &M1) : f(f), M1(M1) {}

    void resize(int n) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.resize(2 * sz, M1);
    }
    
    void set(int k, const Monoid &x) {
        seg[k+sz] = x;
    }
    
    void build() {
        for(int k = sz - 1; k > 0; k--) {
            seg[k] = f(seg[2*k], seg[2*k+1]);
        }
    }

    void update(int k, const Monoid &x) {
        k += sz;
        seg[k] = x;
        while(k >>= 1) {
            seg[k] = f(seg[2*k], seg[2*k+1]);
        }
    }
 
    Monoid query(int a, int b) {
        Monoid L = M1, R = M1;
        for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
            if(a & 1) L = f(L, seg[a++]);
            if(b & 1) R = f(seg[--b], R);
        }
        return f(L, R);
    }

    Monoid operator[](const int &k) const {
        return seg[k+sz];
    }

    Monoid all() {
        return seg[1];
    }

    // 区間[l,r]で左からx番目の値がある位置
    ll bisearch_fore(ll l, ll r, ll x) {
        ll ok = r + 1;
        ll ng = l - 1;
        while (ng+1 < ok) {
            ll mid = (ok+ng) / 2;
            if (query(l, mid+1) >= x) {
                ok = mid;
            } else {
                ng = mid;
            }
        }
        if (ok != r + 1) {
            return ok;
        } else {
            return INF;
        }
    }

    // 区間[l,r]で右からx番目の値がある位置
    ll bisearch_back(ll l, ll r, ll x) {
        ll ok = l - 1;
        ll ng = r + 1;
        while (ok+1 < ng) {
            ll mid = (ok+ng) / 2;
            if (query(mid, r+1) >= x) {
                ok = mid;
            } else {
                ng = mid;
            }
        }
        if (ok != l - 1) {
            return ok;
        } else {
            return -INF;
        }
    }

    // 左から見て、条件を満たす値が最初に出現する位置
    ll bisearch_left(ll l, ll r, function<bool(ll)> func) {
        ll ok = r;
        ll ng = l;
        while (ng+1 < ok) {
            ll mid = (ok+ng) / 2;
            if (func(mid)) {
                ok = mid;
            } else {
                ng = mid;
            }
        }
        return ok;
    }
};


template<typename Monoid>
struct SegmentTreeIndex {
    using F = function<Monoid(Monoid, Monoid)>;
    
    int sz;
    vector<Monoid> seg;
    vector<int> index;
    
    const F f;
    const Monoid M1;
    
    SegmentTreeIndex(int n, const F f, const Monoid &M1) : f(f), M1(M1) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.assign(2 * sz, M1);
        index.assign(2 * sz, -1);
        // 1段目(最下段)の初期化
        rep(i, 0, sz) index[i+sz] = i;
        // 2段目以降の初期化(全部左の子の値に更新)
        rrep(i, sz-1, -1) index[i] = index[i*2];
    }

    SegmentTreeIndex(const F f, const Monoid &M1) : f(f), M1(M1) {}

    void resize(int n) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.assign(2 * sz, M1);
        index.assign(2 * sz, -1);
        // 1段目(最下段)の初期化
        rep(i, 0, sz) index[i+sz] = i;
        // 2段目以降の初期化(全部左の子の値に更新)
        rrep(i, sz-1, -1) index[i] = index[i*2];
    }
    
    void set(int k, const Monoid &x) {
        seg[k+sz] = x;
        index[k+sz] = k;
    }
    
    void build() {
        for(int k = sz - 1; k > 0; k--) {
            // 左の子の値を優先して更新
            if (f(seg[2*k], seg[2*k+1]) == seg[2*k]) {
                seg[k] = seg[2*k];
                index[k] = index[2*k];
            } else {
                seg[k] = seg[2*k+1];
                index[k] = index[2*k+1];
            }
            
        }
    }

    void update(int k, const Monoid &x) {
        k += sz;
        seg[k] = x;
        while(k >>= 1) {
            // 左の子の値を優先して更新
            if (f(seg[2*k], seg[2*k+1]) == seg[2*k]) {
                seg[k] = seg[2*k];
                index[k] = index[2*k];
            } else {
                seg[k] = seg[2*k+1];
                index[k] = index[2*k+1];
            }
        }
    }
 
    pair<Monoid, int> query(int a, int b) {
        pair<Monoid, int> L = mkp(M1, -1), R = mkp(M1, -1);
        for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
            if (a & 1) {
                if (f(seg[a], L.first) == seg[a]) {
                    L.first = seg[a];
                    L.second = index[a];
                }
                a++;
            }
            if (b & 1) {
                b--;
                if (f(R.first, seg[b]) != R.first) {
                    R.first = seg[b];
                    R.second = index[b];
                }
            }
        }
        // 左との一致を優先する
        if (f(L.first, R.first) == L.first) {
            return L;
        } else {
            return R;
        }
    }

    Monoid operator[](const int &k) const {
        return seg[k+sz];
    }
};
