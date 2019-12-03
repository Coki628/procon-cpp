/**
 * ・なんとか自力AC
 * ・渾身の5次元DP
 * ・絶対もっとすっきり解く解法があると思いながらもこれしか見つからなかった。
 * ・1億2000万はpypyでも無理な計算量と思って、最初からC++で書いた。AC0.3秒。
 * ・地味にC++の型変換でハマった。土壇場で-'0'って書き方を思い出せたのは良かったけど。
 * ・charもstringも迷わず数値化できるようにライブラリ化しておいた。
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
const ll MOD = 1e9 + 7;
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

int N;
string S;
bool dp[30007][4][10][10][10];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    cin >> S;

    // dp[i][j][k][l][m] := 左からi番目まで見て、今j桁決まっていて、数字klmが可能か
    dp[0][0][0][0][0] = 1;
    rep(i, 0, N) {
        int a = toint(S[i]);
        rep(j, 0, 4) {
            rep(k, 0, 10) {
                rep(l, 0, 10) {
                    rep(m, 0, 10) {
                        // i番目を使わない
                        dp[i+1][j][k][l][m] |= dp[i][j][k][l][m];
                        // i番目を左から1桁目として使う
                        if (j == 0) dp[i+1][j+1][a][l][m] |= dp[i][j][k][l][m];
                        // 2桁目として使う
                        if (j == 1) dp[i+1][j+1][k][a][m] |= dp[i][j][k][l][m];
                        // 3桁目として使う
                        if (j == 2) dp[i+1][j+1][k][l][a] |= dp[i][j][k][l][m];
                    }
                }
            }
        }
    }
    ll ans = 0;
    // N個全部見て3桁使い終わった状態で、0〜999から可能な数を数える
    rep(k, 0, 10) {
        rep(l, 0, 10) {
            rep(m, 0, 10) {
                ans += dp[N][3][k][l][m];
            }
        }
    }
    print(ans);
    return 0;
}
