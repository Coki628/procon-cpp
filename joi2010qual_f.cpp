/**
 * 参考：https://nanikaka.hatenadiary.org/entry/20120412/1334175198
 * 　　　https://www.ioi-jp.org/joi/2010/2011-yo-prob_and_sol/2011-yo-t6/review/2011-yo-t6-review.html
 * ・蟻本演習3-4-3
 * ・bitDP、スライドbitDP
 * ・直前Mマスの全状態をビットに持たせる。
 * ・良い旗より悪い旗の方が数えやすいので、余事象で答えを求める。
 * ・計算量20^2*2^20=約4億はつらすぎる。当然pypyでもTLE。
 * ・C++でAC2.2秒(制約10秒)。やっぱすげぇ。
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<ll, int, int> tlii;
typedef pair<ll, ll> pll;
typedef pair<ll, int> pli;
typedef pair<int, int> pii;
typedef pair<pair<int, int>, ll> ppiil;
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
const ll MOD = pow(10, 5);
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

ll dp[2][1<<20], nxt[2][1<<20];
vector<string> grid;
ll qcnt, msk;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;
    grid.resize(N);
    rep(i, 0, N) cin >> grid[i];
    rep(i, 0, N) qcnt += count(btoe(grid[i]), '?');
    // Mビット全埋め(1ビットずらしの遷移に使う)
    msk = (1<<M) - 1;
    // dp[i][S] := 左隣の文字がJかどうかが(i=0or1)で、直前Mマスの状態がS(JOとなっているJ位置のビットを立てる)である通り数
    dp[0][0] = 1;
    rep(i, 0, N) {
        rep(j, 0, M) {
            // 直前Mマスの状態を全通り確認する
            memset(nxt, 0, sizeof(nxt));
            rep(S, 0, 1<<M) {
                if (dp[0][S] || dp[1][S]) {
                    if (grid[i][j] == '?') {
                        // Jを置く(左隣JフラグTrueに遷移)
                        nxt[1][(S<<1)&msk] += dp[0][S];
                        nxt[1][(S<<1)&msk] += dp[1][S];
                        // Oを置く(左隣JだったらJOが成立するのでビットを立てる)
                        nxt[0][(S<<1)&msk] += dp[0][S];
                        nxt[0][((S|1)<<1)&msk] += dp[1][S];
                        // 真上がJOのJ位置でなければ(右端は無条件OK)
                        if (!(S & (1<<(M-1))) || j == M-1) {
                            // Iを置く
                            nxt[0][(S<<1)&msk] += dp[0][S];
                            nxt[0][(S<<1)&msk] += dp[1][S];
                        }
                    } else if (grid[i][j] == 'J') {
                        nxt[1][(S<<1)&msk] += dp[0][S];
                        nxt[1][(S<<1)&msk] += dp[1][S];
                    } else if (grid[i][j] == 'O') {
                        nxt[0][(S<<1)&msk] += dp[0][S];
                        nxt[0][((S|1)<<1)&msk] += dp[1][S];
                    } else {
                        if (!(S & (1<<(M-1))) || j == M-1) {
                            nxt[0][(S<<1)&msk] += dp[0][S];
                            nxt[0][(S<<1)&msk] += dp[1][S];
                        }
                    }
                    nxt[0][(S<<1)&msk] %= MOD;
                    nxt[1][(S<<1)&msk] %= MOD;
                    nxt[0][((S|1)<<1)&msk] %= MOD;
                }
            }
            memcpy(dp, nxt, sizeof(dp));
        }
    }
    // 良い旗の総数 = 全通り - 悪い旗の総数
    ll sm = sum(dp[0], 1<<M) + sum(dp[1], 1<<M);
    sm %= MOD;
    print(((pow(3, qcnt, MOD) - sm)+MOD)%MOD);
    return 0;
}
