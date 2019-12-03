/**
 * ・indexセグ木の検証用にC++版も作成。
 * ・pypy1.6秒ACだったところを0.4秒AC。やっぱ安心感あるー。
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<ll, int, int> tlii;
typedef pair<ll, ll> pll;
typedef pair<ll, int> pli;
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

int N, K, l, r, segcnt, idx;
const int MAX = 200007;
vvi LRs;
vector<int> R, ans;
set<int> removed;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> K;
    LRs.resize(MAX);
    R.resize(N+1);
    rep(i, 0, N) {
        cin >> l >> r;
        // いもすっぽい始点終点の追加を、隣接リストっぽくやってindexを保持する
        LRs[l].pb(i+1);
        // 終点位置は負数で保持することで、始点と区別できる
        LRs[r+1].pb(-(i+1));
        R[i+1] = r;
    }

    // index毎に、終点位置を保持するセグ木
    SegmentTreeIndex<ll> sti([](ll a, ll b) { return max(a, b); }, -INF);
    sti.resize(N+1);
    segcnt = 0;
    rep(i, 1, MAX) {
        // この地点での始点と終点の操作
        for (int idx : LRs[i]) {
            // 始点
            if (idx > 0) {
                sti.update(idx, R[idx]);
                segcnt++;
            // 終点
            } else {
                idx = abs(idx);
                // 既に削除されていないかチェック
                if (removed.find(idx) == removed.end()) {
                    sti.update(idx, -INF);
                    segcnt--;
                }
            }
        }
        // 区間数がKを超えている場合、削除をやる
        while (segcnt > K) {
            // 現在残っている区間の中で、最も終点位置が大きいもののindex
            idx = sti.query(0, N+1).second;
            sti.update(idx, -INF);
            ans.pb(idx);
            removed.insert(idx);
            segcnt--;
        }
    }

    print(ans.size());
    print(ans);
    return 0;
}
