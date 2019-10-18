/**
 * 参考：https://img.atcoder.jp/iroha2019-day1/editorial-G.pdf
 * 　　　https://atcoder.jp/contests/iroha2019-day1/submissions/5713292
 * ・いわゆる普通のminmax系DP(2次元+内ループ)
 * ・これは貰うDP実装
 * ・内ループをセグメント木(RMaxQ)にした。
 * ・やっぱC++だと速い。
 */

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
    
    void set(int k, const Monoid &x) {
        seg[k + sz] = x;
    }
    
    void build() {
        for(int k = sz - 1; k > 0; k--) {
            seg[k] = f(seg[2 * k + 0], seg[2 * k + 1]);
        }
    }

      void update(int k, const Monoid &x) {
        k += sz;
        seg[k] = x;
        while(k >>= 1) {
            seg[k] = f(seg[2 * k + 0], seg[2 * k + 1]);
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
        return seg[k + sz];
    }
};

// dp[i][j] := i回目をj日目に使った状態(2次元目をセグ木で構築)
vector<SegmentTree<ll>> dp;
vector<ll> A;

int main() {
    int N,M,K;
    cin >> N >> M >> K;
    A.resize(N+1, 0);
    rep(i, 1, N+1) cin >> A[i];
    rep(i, 0, M+1) {
        SegmentTree<ll> st(N+1, [](ll a, ll b) { return max(a, b); }, -INF);
        dp.pb(st);
    }
    dp[0].update(0, 0);

    rep(i, 1, M+1) rep(j, 1, N+1) {
        // 区間maxをセグ木から取得
        ll mx = dp[i-1].query(max(j-K, 0LL), j);
        if (mx!=-INF) mx+=A[j];
        dp[i].update(j, mx);
    }
    // M回終わって、あとK日で終わりまで行ければOK
    ll ans = dp[M].query(N+1-K, N+1);
    if (ans!=-INF) {
        print(ans);
    } else {
        print(-1);
    }
    return 0;
}
