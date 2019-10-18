/**
 * ・蟻本演習2-4-3
 * ・部分永続Union-Find
 * ・3つの解法の中で実装は一番軽い。
 * ・速度も同じくらい速い。AC0.1秒。
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
void chmax(int &a, int b) { a = max(a, b); }
void chmin(int &a, int b) { a = min(a, b); }

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

int N, M, Q, a, b, x, y, ans;
PartiallyPersistentUnionFind ppuf;

bool calc(int m) {
    // m回併合して、xとyが同じ集合に属しているかどうか
    return ppuf.is_same(m, x, y);
}

int main() {

    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> M;
    ppuf = PartiallyPersistentUnionFind(N);
    // 辺が追加された時系列iを辺のコストとする
    rep(i, 0, M) {
        cin >> a >> b;
        if (!ppuf.is_same(i, a, b)) {
            ppuf.merge(i+1, a, b);
        }
    }

    cin >> Q;
    rep(i, 0, Q) {
        cin >> x >> y;
        // 最後の状態で連結かどうか
        if (ppuf.is_same(M+1, x, y)) {
            // 連結した時間を二分探索
            ans = bisearch_min(-1, M+1, calc);
            print(ans);
        } else {
            print(-1);
        }
    }
}
