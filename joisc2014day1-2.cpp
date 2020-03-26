/**
 * 参考：https://www.ioi-jp.org/camp/2015/2015-sp-tasks/2015-sp-d1-enjoi-review.pdf
 * ・自力ならず。。
 * ・累積和、再帰探索
 * ・実はある始点からの全区間の確認は再帰10回程度で済むので、100万箇所やっても大丈夫。
 * ・新しい知見として、C++はpowがすげー遅い。最初TLEして、
 * 　計算量1000万程度でそれはちょっとおかしいな、と思って調べてみて発覚。
 * ・そこを前計算なりしておいたら、1秒超→0.2秒まで変わった。
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

inline ll pow(int a, ll b) {
    ll res = 1;
    rep(_, 0, b) res *= a;
    return res;
}

ll K, N;
string S;
vector<ll> acc[3];
ll pow4[11];

ll rec(ll i, ll k) {
    if (k == -1) {
        return 1;
    }
    ll cnt = 0;
    ll l, r;
    rep(j, 0, 3) {
        l = i + pow4[k] * j;
        r = i + pow4[k] * (j+1);
        cnt += acc[j][r-1] - acc[j][l-1];
    }
    return cnt + rec(i+pow4[k]*3, k-1);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    rep(i, 0, 11) pow4[i] = pow(4, i);
    cin >> K;
    N = pow4[K];
    cin >> S;
    rep(i, 0, 3) acc[i].resize(N*2+1);
    rep(i, 0, N*2) {
        if (S[i%N] == 'J') {
            acc[0][i+1]++;
        } else if (S[i%N] == 'O') {
            acc[1][i+1]++;
        } else {
            acc[2][i+1]++;
        }
    }
    rep(i, 0, 3) {
        rep(j, 0, N*2) {
            acc[i][j+1] += acc[i][j];
        }
    }

    ll ans = 0;
    rep(i, 1, N+1) {
        chmax(ans, rec(i, K-1));
    }
    print(N - ans);
    return 0;
}
