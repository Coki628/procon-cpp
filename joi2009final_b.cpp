/**
 * 参考：https://comprolog.netlify.com/post/joi/2010final2/
 * ・自力ならず。。
 * ・ナップザック系で、フラグ付の3次元DP
 * ・添字をどう割り当てるかが見抜きづらい。DPちょっと考えたけど、
 * 　切る箇所が10000箇所もあったら遷移多すぎて死ぬ、、で終わった。
 * ・正解は、i箇所目の切れ目まで考えて、をindexにする。そうすると、
 * 　各遷移が切るor切らないの二択のみになるので、うまくDPを進められる。
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
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define btoe(obj) (obj).begin(), (obj).end()    
#define pb push_back
#define str to_string
#define mkp make_pair
const ll INF = 1e18;
const ll MOD = 100000;
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

ll N;
vector<ll> A;
ll dp[2][5007][2];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    A[N-1] = 0;
    rep(i, 0, N-1) cin >> A[i];

    // dp[i][j][k] := 左からi番目の切れ目まで見て、Aがj個のブロックを得ていて、直前がAorB(k=0,1)の状態の最小コスト
    rep(i, 0, 2) rep(j, 0, N/2+1) rep(k, 0, 2) dp[i][j][k] = INF;
    dp[0][0][0] = dp[0][0][1] = 0;
    rep(i, 0, N) {
        ll a = A[i];
        rep(j, 0, N/2+1) {
            // この位置を切らない
            chmin(dp[(i+1)&1][j+1][0], dp[i&1][j][0]);
            chmin(dp[(i+1)&1][j][1], dp[i&1][j][1]);
            // この位置を切る
            chmin(dp[(i+1)&1][j][0], dp[i&1][j][1] + a);
            chmin(dp[(i+1)&1][j+1][1], dp[i&1][j][0] + a);
            // 遷移元を初期化
            dp[i&1][j][0] = dp[i&1][j][1] = INF;
        }
    }
    ll ans = min(dp[N&1][N/2][0], dp[N&1][N/2][1]);
    print(ans);
    return 0;
}
