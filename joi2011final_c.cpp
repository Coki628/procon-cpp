/**
 * ・結構すんなり自力AC！
 * ・割と典型なナップザック系2次元DP
 * ・気をつける点としては遷移の時花火の時間と被ると遷移できないことと、
 * 　毎回その時間までの最大値から遷移させたいので累積max取りながらやるってくらい。
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

ll N, T, S;
vector<pll> AB;
ll dp[3007][3007];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> T >> S;
    AB.resize(N);
    rep(i, 0, N) cin >> AB[i].first >> AB[i].second;

    // dp[i][j] := i番目の夜店まで見て、時刻j時点での楽しさの最大値
    dp[0][0] = 0;
    rep(i, 0, N) {
        ll a = AB[i].first;
        ll b = AB[i].second;
        rep(j, 0, T+1) {
            // この店で遊ばない
            chmax(dp[i+1][j], dp[i][j]);
            // この店で遊ぶ
            if (j+b <= T && (S <= j || j+b <= S)) {
                chmax(dp[i+1][j+b], dp[i][j] + a);
            }
        }
        // 待ち時間を考慮して累積maxを取っておく
        rep(j, 0, T) {
            chmax(dp[i+1][j+1], dp[i+1][j]);
        }
    }
    ll ans = dp[N][T];
    print(ans);
    return 0;
}
