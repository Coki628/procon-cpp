/**
 * 参考：https://www.ioi-jp.org/joi/2017/2018-ho/2018-ho-t2-review.pdf
 * 　　　https://www.ioi-jp.org/joi/2017/2018-ho/2018-ho-t2-sample.cpp
 * ・自力ならず。。
 * ・式変形
 * ・部分点のO(N^2)解法までは公式と同じ方針が出てたけど、そこまで。
 * ・S - (max(A) - min(A)) について、Aでソート済の列を考えると、
 * 　ある区間[i, j]について、Sは累積和にすると、区間和で Sj - Si-1 とできる。
 * 　Aはそのまま最小最大が左端と右端なので Aj - Ai になる。
 * 　まとめると、 (Sj - Si-1) - (Aj - Ai) これを式変形して (Sj - Aj) - (Si-1 - Ai)
 * 　ここまで来ると、i, jが独立になるので、左端となるiの最小をすぐに見つけられる。
 * ・実際の動きはソース内コメントも参照。
 * ・計算量は50万のNにソートのlog、これが1秒だとpypyでも通らなかった。。
 * ・C++でAC0.2秒。さすが。
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
typedef vector<vector<ll>> vvl;
typedef vector<vector<int>> vvi;
typedef vector<vector<pll>> vvpll;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define btoe(obj) (obj).begin(), (obj).end()
#define pb push_back
#define str to_string
#define mkp make_pair
const ll INF = 1e18;
const ll MOD = 1e9 + 7;
template<typename T> inline bool chmax(T &x, T y) { return (y > x) ? x = y, true : false; }
template<typename T> inline bool chmin(T &x, T y) { return (y < x) ? x = y, true : false; }

template<typename T>
void print(T out) {
    cout << out << '\n';
}

void print(ld out) {
    cout << fixed << setprecision(12) << out << '\n';
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

inline ll pow(int a, ll b) {
    ll res = 1;
    rep(_, 0, b) res *= a;
    return res;
}

ll pow(ll x, ll n, int mod) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) {
            res = (res * x) % mod;
        }
        x = (x * x) % mod;
        n >>= 1;
    }
    return res;
}

ll floor(ll a, ll b) {
    if (a < 0) {
        return (a-b+1)/b;
    } else {
        return a/b;
    }
}

ll ceil(ll a, ll b) {
    if (a >= 0) {
        return (a+b-1)/b;
    } else {
        return a/b;
    }
}

ll N;
vector<pll> AB;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    AB.resize(N);
    rep(i, 0, N) cin >> AB[i].first >> AB[i].second;
    sort(AB.begin(), AB.end());

    ll ans = 0, mn = 0, acc = 0;
    for (auto p : AB) {
        // min(min(Si-1 - Ai), Sj-1 - Aj) ：左端の最小値を更新
        chmin(mn, acc - p.first);
        // Sj = Sj-1 + Bj ：Bの累積和を更新
        acc += p.second;
        // (Sj - Aj) - min(Si-1 - Ai) ：答えの最大値を更新
        chmax(ans, (acc - p.first) - mn);
    }
    print(ans);
    return 0;
}
