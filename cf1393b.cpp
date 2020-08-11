/**
 * ・pypyTLEを移植。無事AC0.09秒。
 * ・indexセグ木の修正版も移植してverifyできた。
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ll, int> pli;
typedef pair<int, int> pii;
typedef pair<ll, ld> pld;
typedef pair<pii, int> ppiii;
typedef pair<pii, ll> ppiil;
typedef pair<pll, ll> pplll;
typedef pair<pli, int> pplii;
typedef vector<vector<ll>> vvl;
typedef vector<vector<int>> vvi;
typedef vector<vector<pll>> vvpll;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define pb push_back
#define tostr to_string
#define mkp make_pair
const ll INF = LONG_LONG_MAX;
const ll MOD = 1000000007;

void print(ld out) { cout << fixed << setprecision(15) << out << '\n'; }
template<typename T> void print(T out) { cout << out << '\n'; }
template<typename T1, typename T2> void print(pair<T1, T2> out) { cout << out.first << ' ' << out.second << '\n'; }
template<typename T> void print(vector<T> A) { rep(i, 0, A.size()) { cout << A[i]; cout << (i == A.size()-1 ? '\n' : ' '); } }
template<typename T> void print(set<T> S) { vector<T> A(S.begin(), S.end()); print(A); }

template<typename T> inline bool chmax(T &x, T y) { return (y > x) ? x = y, true : false; }
template<typename T> inline bool chmin(T &x, T y) { return (y < x) ? x = y, true : false; }

ll sum(vector<ll> A) { ll res = 0; for (ll a: A) res += a; return res; }
ll max(vector<ll> A) { ll res = -INF; for (ll a: A) chmax(res, a); return res; }
ll min(vector<ll> A) { ll res = INF; for (ll a: A) chmin(res, a); return res; }

ll toint(string s) { ll res = 0; for (char c : s) { res *= 10; res += (c - '0'); } return res; }
int toint(char c) { return c - '0'; }
char tochar(int i) { return '0' + i; }

inline ll pow(int x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
inline ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

inline ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
inline ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }
pll divmod(ll a, ll b) { ll d = a / b; ll m = a % b; return {d, m}; }

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }

template<typename Monoid>
struct SegmentTreeIndex {
    using F = function<Monoid(Monoid, Monoid)>;

    int sz;
    vector<pair<Monoid, int>> seg;

    const F f;
    const Monoid M1;

    pair<Monoid, int> compare(pair<Monoid, int> a, pair<Monoid, int> b) {
        if (a.first == b.first) {
            // 同値はindexが小さい方優先
            if (a.second <= b.second) {
                return a;
            } else {
                return b;
            }
        } else if (f(a.first, b.first) == a.first) {
            return a;
        } else {
            return b;
        }
    }

    SegmentTreeIndex(int n, const F f, const Monoid &M1) : f(f), M1(M1) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.assign(2 * sz, {M1, -1});
    }

    SegmentTreeIndex(const F f, const Monoid &M1) : f(f), M1(M1) {}

    void resize(int n) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.assign(2 * sz, {M1, -1});
    }

    void set(int k, const Monoid &x) {
        seg[k+sz] = {x, k};
    }

    void build() {
        for(int k = sz - 1; k > 0; k--) {
            seg[k] = compare(seg[2*k], seg[2*k+1]);            
        }
    }

    void update(int k, const Monoid &x) {
        k += sz;
        seg[k] = {x, k-sz};
        while(k >>= 1) {
            seg[k] = compare(seg[2*k], seg[2*k+1]);
        }
    }

    void add(int k, const Monoid &x) {
        update(k, seg[k+sz].first + x);
    }

    pair<Monoid, int> query(int a, int b) {
        Monoid L = M1, R = M1;
        for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
            if(a & 1) L = compare(L, seg[a++]);
            if(b & 1) R = compare(seg[--b], R);
        }
        return compare(L, R);
    }

    Monoid operator[](const int &k) const {
        return seg[k+sz].first;
    }

    pair<Monoid, int> all() {
        return seg[1];
    }
};

const ll MX = 100000;
SegmentTreeIndex<ll> seg(MX+1, [](ll a, ll b) { return max(a, b); }, 0);
ll N, Q;
vector<ll> C(MX+1);

void revert(vector<pii> &tmp) {
    for (auto p : tmp) {
        seg.add(p.first, p.second);
    }
}

bool check() {
    ll mx;
    int idx;
    vector<pii> tmp;
    tie(mx, idx) = seg.all();
    if (mx >= 4) {
        seg.update(idx, mx-4);
        tmp.pb({idx, 4});
        tie(mx, idx) = seg.all();
        if (mx >= 4) {
            revert(tmp);
            // 4, 4
            return true;
        } else if (mx >= 2) {
            seg.update(idx, mx-2);
            tmp.pb({idx, 2});
            tie(mx, idx) = seg.all();
            if (mx >= 2) {
                revert(tmp);
                // 4, 2, 2
                return true;
            } else {
                revert(tmp);
                // 4, 2, x
                return false;
            }
        } else {
            revert(tmp);
            // 4, x
            return false;
        }
    } else {
        // x
        return false;
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    ll a;
    rep(i, 0, N) {
        cin >> a;
        C[a]++;
    }
    rep(i, 1, MX+1) {
        seg.set(i, C[i]);
    }
    seg.build();

    cin >> Q;
    char op;
    ll x;
    rep(_, 0, Q) {
        cin >> op >> x;
        if (op == '+') {
            seg.add(x, 1);
        } else {
            seg.add(x, -1);
        }

        if (check()) {
            print("YES");
        } else {
            print("NO");
        }
    }
    return 0;
}
