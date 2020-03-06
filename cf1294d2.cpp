/**
 * ・セグ木で二分探索
 * ・log2つ乗るけど、これで自力AC。
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<ll, int> pli;
typedef pair<int, int> pii;
typedef pair<pii, ll> ppiil;
typedef pair<pii, int> ppiii;
typedef vector<vector<ll>> vvl;
typedef vector<vector<int>> vvi;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define btoe(obj) (obj).begin(), (obj).end()
#define pb push_back
#define str to_string
#define mkp make_pair
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

template<typename T>
void print(set<T> S) {
    vector<T> A(btoe(S));
    print(A);
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

ll sum(ll A[], int len) {
    ll res = 0;
    rep(i, 0, len) res += A[i];
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

ll toint(string s) {
    ll res = 0;
    for (char c : s) {
        res *= 10;
        res += (c - '0');
    }
    return res;
}

int toint(char c) {
    return c - '0';
}

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

ll Q, X, mn;
vector<ll> A, ans;
map<ll, ll> C;
SegmentTree<ll> st([](ll a, ll b) { return min(a, b); }, INF);

bool check(ll m) {
    return m <= mn;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> Q >> X;
    A.resize(Q);
    ans.resize(Q);
    st.resize(X);
    rep(i, 0, Q) cin >> A[i];

    reverse(btoe(A));
    rep(i, 0, Q) {
        A[i] %= X;
        C[A[i]]++;
    }
    mn = INF;
    rep(i, 0, X) {
        chmin(mn, C[i]);
        st.set(i, C[i]);
    }
    st.build();
    ll base = mn * X;
    ll add = st.bisearch_left(-1, X, [](ll m) {return st.query(0, m+1) == mn;});

    rep(i, 0, Q) {
        ans[i] = base + add;
        C[A[i]]--;
        st.update(A[i], st[A[i]] - 1);
        if (C[A[i]] < mn) {
            mn--;
            base -= X;
        }
        add = st.bisearch_left(-1, X, [](ll m) {return st.query(0, m+1) == mn;});
    }
    reverse(btoe(ans));
    rep(i, 0, Q) {
        print(ans[i]);
    }
    return 0;
}
