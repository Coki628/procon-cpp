/**
 * 参考：https://scrapbox.io/ganariya/JOI2008%E6%98%A5%E5%90%88%E5%AE%BF_P6_%E3%80%8CNile.Com%E3%80%8D_(copy)
 * ・自力ならず。。
 * ・遷移を工夫して計算量を減らすDP
 * ・まともに全部遷移させようとするとNの3000かかってしまうが、
 * 　実際は予め前回までの最小を取っておくことで1つにまとまる。
 * ・後はもう、違う店を選ぶ or 同じ店を選ぶ の2択なので最終的に遷移は定数に収まる。
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

ll N, D;
vvl DN;
ll dp[370][3007][3];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> D;
    DN.resize(D);
    rep(i, 0, D) {
        DN[i].resize(N);
        rep(j, 0, N) {
            cin >> DN[i][j];
        }
    }

    // dp[i][j][k] := i日目まで見て、直前に買った店がjで、k回連続状態での最小コスト
    rep(i, 0, D+1) rep(j, 0, N) rep(k, 0, 3) dp[i][j][k] = INF;
    dp[0][0][0] = 0;
    rep(i, 0, D) {
        // 前日までの値で最も良いものを調べておく
        ll minv = INF;
        rep(j, 0, N) {
            rep(k, 0, 3) {
                chmin(minv, dp[i][j][k]);
            }
        }

        rep(j, 0, N) {
            // 違う店で買う遷移
            chmin(dp[i+1][j][0], minv + DN[i][j]);
            // 初回は前回と同じ店はないのでこの先はスキップ
            if (i == 0) {
                continue;
            }
            // 同じ店で買う遷移(2回目)
            chmin(dp[i+1][j][1], dp[i][j][0] + DN[i][j] * 9 / 10);
            // 同じ店で買う遷移(3回目)
            chmin(dp[i+1][j][2], dp[i][j][1] + DN[i][j] * 7 / 10);
            // 同じ店で買う遷移(それ以降)
            chmin(dp[i+1][j][2], dp[i][j][2] + DN[i][j] * 7 / 10);
        }
    }

    ll ans = INF;
    rep(j, 0, N) {
        rep(k, 0, 3) {
            chmin(ans, dp[D][j][k]);
        }
    }
    print(ans);
    return 0;
}
