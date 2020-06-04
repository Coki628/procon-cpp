
/**
 * ・終了後自力AC。
 * ・BIT上の二分探索
 * ・セグ木で代用できるしいいやって作ってなかったBITを使うことになった。
 * 　ちゃんとBITも移植しておくんだったな。。
 * ・やってることはセグ木版と全く同じ。速度が違う。
 * ・100万にlog2つ乗っても、AC0.9秒。BITのlogが軽いってのはマジなんだなー。
 * ・ちなみにやっぱりメモリもこっちのが軽くて、12→8MBになった。
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
const ll INF = 1e18;
const ll MOD = 1e9 + 7;

void print(ld out) { cout << fixed << setprecision(12) << out << '\n'; }
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

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }

template<typename T>
struct BIT {

    int sz;
    vector<T> tree;

    BIT(int n) {
        // 0-indexed
        n++;
        sz = 1;
        while (sz < n) {
            sz *= 2;
        }
        tree.resize(sz);
    }

    T sum(int i) {
        T s = 0;
        i++;
        while (i > 0) {
            s += tree[i-1];
            i -= i & -i;
        }
        return s;
    }

    void add(int i, T x) {
        i++;
        while (i <= sz) {
            tree[i-1] += x;
            i += i & -i;
        }
    }

    T query(int l, int r) {
        return sum(r-1) - sum(l-1);
    }

    T get(int i) {
        return query(i, i+1);
    }

    void update(int i, T x) {
        add(i, x - get(i));
    }

    ll bisearch_fore(int l, int r, ll x) {
        ll l_sm = sum(l-1);
        int ok = r + 1;
        int ng = l - 1;
        while (ng+1 < ok) {
            int mid = (ok+ng) / 2;
            if (sum(mid) - l_sm >= x) {
                ok = mid;
            } else {
                ng = mid;
            }
        }
        if (ok != r+1) {
            return ok;
        } else {
            return INF;
        }
    }

    ll bisearch_back(int l, int r, ll x) {
        ll r_sm = sum(r);
        int ok = l - 1;
        int ng = r + 1;
        while (ok+1 < ng) {
            int mid = (ok+ng) / 2;
            if (r_sm - sum(mid-1) >= x) {
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
};

ll N, Q;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> Q;
    int a;
    BIT<int> bit(N+1);
    rep(i, 0, N) {
        cin >> a;
        bit.add(a, 1);
    }
    int idx;
    rep(i, 0, Q) {
        cin >> a;
        if (a > 0) {
            bit.add(a, 1);
        }
        if (a < 0) {
            a = abs(a);
            idx = bit.bisearch_fore(0, N, a);
            bit.add(idx, -1);
        }
    }
    int ans = 0;
    rep(i, 0, N+1) {
        if (bit.get(i) > 0) {
            ans = i;
            break;
        }
    }
    print(ans);
    return 0;
}
