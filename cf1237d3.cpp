/**
 * ・セグ木上の二分探索確認用
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
#define btoe(obj) (obj).begin(), (obj).end()
#define pb push_back
#define str to_string
#define mkp make_pair
#define mkt make_tuple
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

    SegmentTree(const F f, const Monoid &M1) : f(f), M1(M1) {}

    void resize(int n) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.resize(2 * sz, M1);
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

    Monoid all() {
        return seg[1];
    }

    // 区間[l,r]で左からx番目の値がある位置
    ll bisearch_left(ll l, ll r, ll x) {
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
            return -1;
        }
    }

    // 区間[l,r]で右からx番目の値がある位置
    ll bisearch_right(ll l, ll r, ll x) {
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
            return -1;
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

int N, i;
vector<ll> A, dp, ans;
SegmentTree<ll> st1([](ll a, ll b) { return max(a, b); }, -INF);
SegmentTree<ll> st2([](ll a, ll b) { return min(a, b); }, INF);

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N, 0);
    rep(i, 0, N) cin >> A[i];
    dp.resize(N*3, INF);
    ans.resize(N, -1);
    st1.resize(N*3);
    st2.resize(N*3);

    if (min(A) >= max(A)/2.0) {
        print(ans);
        return 0;
    }

    rep(i, 0, N) {
        st1.set(i, A[i]);
        st1.set(i+N, A[i]);
        st1.set(i+N*2, A[i]);
        st2.set(i, A[i]);
        st2.set(i+N, A[i]);
        st2.set(i+N*2, A[i]);
    }
    st1.build();
    st2.build();

    rrep(i, N*3-1, -1) {
        // 区間内にA[i]より大きい値があるかどうか
        ll j = st1.bisearch_left(i, N*3, [i](ll m) { return st1.query(i, m+1) > A[i%N]; });
        // 区間内にA[i]/2より小さい値があるかどうか
        ll k = st2.bisearch_left(i, N*3, [i](ll m) { return st2.query(i, m+1) < A[i%N] / 2.0; });
        if (j < k) {
            // 自分より大きい値が先に来るなら、そこを参照する
            dp[i] = dp[j] + (j - i);
        } else if (j > k) {
            // 自分/2より小さい値が先に来るなら、自分が決める
            dp[i] = k - i;
        }
    }
    rep(i, 0, N) ans[i] = dp[i];
    print(ans);
    return 0;
}
