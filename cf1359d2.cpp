/**
 * 参考：https://codeforces.com/contest/1359/submission/81768871
 * ・セグ木とか(実際はSparseTableとBITにしたけど)でうまくやる解
 * ・詳細はソース内コメント。この解法だとAの取りうる範囲が狭くなくても対応できるな。
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

struct SparseTable {

    const function<ll(ll, ll)> func;
    vvl dat;
    vector<ll> height;

    SparseTable(function<ll(ll, ll)> func) : func(func) {
    }

    SparseTable(vector<ll> A, function<ll(ll, ll)> func) : func(func) {
        build(A);
    }

    void build(vector<ll> A) {
        ll N = A.size();

        ll h = 0;
        while ((1<<h) <= N) {
            h++;
        }
        dat.resize(h);
        rep(i, 0, h) dat[i].resize(1<<h);
        height.resize(N+1);

        rep(i, 2, N+1) {
            height[i] = height[i>>1] + 1;
        }
        rep(i, 0, N) {
            dat[0][i] = A[i];
        }
        rep(i, 1, h) {
            rep(j, 0, N) {
                dat[i][j] = func(dat[i-1][j], dat[i-1][min(j+(1<<(i-1)), N-1)]);
            }
        }
    }

    ll get(ll l, ll r) {
        if (l >= r) throw exception();
        ll a = height[r-l];
        return func(dat[a][l], dat[a][r-(1<<a)]);
    }
};

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

    // [0, i]を合計する
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

    // 区間和の取得 [l, r)
    T query(int l, int r) {
        return sum(r-1) - sum(l-1);
    }

    T get(int i) {
        return query(i, i+1);
    }

    void update(int i, T x) {
        add(i, x - get(i));
    }

    // 区間[l, r]を左から右に向かってx番目の値がある位置
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

    // 区間[l, r]を右から左に向かってx番目の値がある位置
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

template<typename T>
vector<T> accumulate(vector<T> &A) {
    int N = A.size();
    vector<T> res(N);
    res[0] = A[0];
    rep(i, 1, N) res[i] = res[i-1] + A[i];
    return res;
}

ll N;
vector<ll> A, acc;
vector<pll> AI;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    AI.resize(N);
    rep(i, 0, N) {
        cin >> A[i];
        AI[i] = {A[i], i+1};
    }
    acc = accumulate(A);
    acc.insert(acc.begin(), 0);
    // 累積和をSparseTableに詰めて、左端最小と右端最大をすぐ取れるようにしておく
    SparseTable stmn(acc, [](ll a, ll b) { return min(a, b); });
    SparseTable stmx(acc, [](ll a, ll b) { return max(a, b); });
    // 確認済indexを管理するBIT
    BIT<ll> bit(N+2);
    bit.add(0, 1);
    bit.add(N+1, 1);

    sort(AI.rbegin(), AI.rend());
    ll a, idx, l, r, accl, accr, ans = -INF;
    // 値の大きい方から確認していく
    for (auto p : AI) {
        tie(a, idx) = p;
        // 今回の値より大きいものがない範囲を取る
        l = bit.bisearch_back(0, idx, 1);
        r = bit.bisearch_fore(idx, N+1, 1);
        // その範囲について、累積和から左端の最小と右端の最大を取る
        accl = stmn.get(l, idx);
        accr = stmx.get(idx, r);
        // 今回の値1つは最大値として引かれる
        chmax(ans, accr-accl-a);
        // 今回の値のindexを確認済とする
        bit.add(idx, 1);
    }
    print(ans);
    return 0;
}
