/**
 * ・グリッドDP
 * ・pypyTLEなのでこっちで。
 * ・計算量80^3*160=8200万くらいで、AC0.2秒。
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<ll, int> pli;
typedef pair<int, int> pii;
typedef pair<pii, ll> ppiil;
typedef pair<pii, int> ppiii;
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

ll grid1[87][87], grid2[87][87], grid[87][87];
// dp[i][j][k] := グリッド(i, j)に数値kで到達可能かどうか
bool dp[87][87][13007];
const ll MAXV = 80 * 160;
int H, W;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> H >> W;
    rep(i, 0, H) rep(j, 0, W) cin >> grid1[i][j];
    rep(i, 0, H) rep(j, 0, W) cin >> grid2[i][j];
    rep(i, 0, H) {
        rep(j, 0, W) {
            grid[i+1][j+1] = abs(grid1[i][j]-grid2[i][j]);
        }
    }

    int v = grid[1][1];
    dp[1][1][v] = 1;
    rep(i, 1, H+1) {
        rep(j, 1, W+1) {
            v = grid[i][j];
            rep(k, 0, MAXV+1) {
                // 上からの遷移
                dp[i][j][k] |= dp[i-1][j][abs(k-v)];
                if (k+v <= MAXV) {
                    dp[i][j][k] |= dp[i-1][j][k+v];
                }
                // 左からの遷移
                dp[i][j][k] |= dp[i][j-1][abs(k-v)];
                if (k+v <= MAXV) {
                    dp[i][j][k] |= dp[i][j-1][k+v];
                }
            }
        }
    }
    ll ans = INF;
    rep(k, 0, MAXV+1) {
        if (dp[H][W][k]) {
            chmin(ans, k);
        }
    }
    print(ans);
    return 0;
}
