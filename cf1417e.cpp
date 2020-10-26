/**
 * 参考：https://twitter.com/laycrs/status/1310266839017037827
 * ・むずい。
 * ・ビット、転倒数、座圧してBIT
 * ・上位ビットから貪欲に、その時いい方を選んでいけばいい。
 * 　こういう上位ビットから貪欲、みたいなの結構あるけど、今回のやつはそれでうまくいくの
 * 　なんか非自明だなぁ。下のビット切り替えた時に逆転されることないんだろうか、ってなる。
 * ・ビットのlogとBITのlogでlog2つ乗る30万なんだけどTLE。。
 * 　なんとなく、座圧が重い気がする。。
 */

#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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
#define list2d(name, N, M, type, init) vector<vector<type>> name(N, vector<type>(M, init))
const ll INF = LONG_LONG_MAX;
const ll MOD = 1000000007;

void print(ld out) { cout << fixed << setprecision(15) << out << '\n'; }
void print(double out) { cout << fixed << setprecision(15) << out << '\n'; }
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
// 数字なら'0'、アルファベットなら'a'みたいに使い分ける
// int toint(char c) { return c - '0'; }
// char tochar(int i) { return '0' + i; }

inline ll pow(int x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
inline ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

inline ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
inline ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }
pll divmod(ll a, ll b) { ll d = a / b; ll m = a % b; return {d, m}; }

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
};

typedef unordered_map<ll, int> mli;
typedef unordered_map<int, ll> mil;
pair<mli, mil> compress(unordered_set<ll> S) {
    mli zipped;
    mil unzipped;
    vector<ll> A(S.begin(), S.end());
    sort(A.begin(), A.end());
    rep(i, 0, A.size()) {
        zipped[A[i]] = i;
        unzipped[i] = A[i];
    }
    return mkp(zipped, unzipped);
}

ll N, K = 32;
vector<ll> A;

ll check(vector<ll> &A) {
    unordered_set<ll> S(A.begin(), A.end());
    auto cp = compress(S);
    auto zipped = cp.first;
    ll M = zipped.size();
    BIT<ll> bit(M);

    ll res = 0;
    rep(i, 0, N) {
        res += i - bit.sum(zipped[A[i]]);
        bit.add(zipped[A[i]], 1);
    }
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    rep(i, 0, N) cin >> A[i];

    ll cur = check(A);
    ll ans = 0;
    rrep(k, K-1, -1) {
        rep(i, 0, N) {
            A[i] ^= 1LL<<k;
        }
        ll tmp = check(A);
        // より良い値を取るなら、このビットを使う
        if (tmp < cur) {
            cur = tmp;
            ans |= 1LL<<k;
        // そうでないなら、ここは使わないとして状態を元に戻す
        } else {
            rep(i, 0, N) {
                A[i] ^= 1LL<<k;
            }
        }
    }
    print(mkp(cur, ans));
    return 0;
}
