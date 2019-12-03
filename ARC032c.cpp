/**
 * ・セグ木応用
 * ・これは結局C++でもTLE
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<ll, int, int> tlii;
typedef pair<ll, ll> pll;
typedef pair<ll, int> pli;
typedef pair<int, int> pii;
typedef pair<pair<int, int>, ll> ppiil;
typedef pair<pair<int, int>, int> ppiii;
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

typedef pair<int, vector<int>> pivi;
pivi compare(pivi a, pivi b) {
    // まず仕事数、同数なら内容の辞書順を比較する
    if (a.first > b.first) return a;
    if (a.first < b.first) return b;
    rep(i, 0, a.first) {
        if (a.second[i] < b.second[i]) return a;
        if (a.second[i] > b.second[i]) return b;
    }
    return a;
}

int N;
vector<ppiii> AB;
pivi intv;
// 独自の比較関数でセグ木を構築
SegmentTree<pivi> st(compare, intv);

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    AB.resize(N);
    set<ll> S;
    rep(i, 0, N) {
        cin >> AB[i].first.first >> AB[i].first.second;
        AB[i].second = i;
        S.insert(AB[i].first.first);
        S.insert(AB[i].first.second);
    }

    // 座標圧縮
    auto comp = compress(S);
    mli zipped = comp.first;
    rep(i, 0, N) {
        int a = AB[i].first.first;
        int b = AB[i].first.second;
        AB[i].first.first = zipped[a];
        AB[i].first.second = zipped[b];
    }
    st.resize(zipped.size());

    sort(btoe(AB));

    for (ppiii ab : AB) {
        int a = ab.first.first;
        int b = ab.first.second;
        int i = ab.second;
        // 時間aまでで最も良い状況を取ってくる
        pivi res = st.query(0, a+1);
        // 今回分を合わせて、時間bを更新
        res.first++;
        res.second.pb(i+1);
        pivi nxt = compare(st[b], res);
        st.update(b, nxt);
    }
    // 全時間帯から、最もうまくいった所を取ってくる
    pivi ans = st.all();
    print(ans.first);
    print(ans.second);
    return 0;
}
