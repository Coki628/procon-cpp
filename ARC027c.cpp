/**
 * ・自力AC
 * ・pypyで枝刈りまでしてもTLEだったのでこっちで。
 * ・計算量600*300*600=1億800万、AC0.1秒。強い。。
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

int X, Y, N, M;
vector<pll> TH;
// dp[i][j][k] := i個目のトッピングまで見て、スペシャルチケットj枚、通常チケットk枚を使った時の、嬉しさの最大値
ll dp[2][307][607];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> X >> Y >> N;
    M = X + Y;
    TH.resize(N);
    rep(i, 0, N) cin >> TH[i].first >> TH[i].second;

    rep(i, 0, N) {
        int cur = i % 2;
        int nxt = (i+1) % 2;
        ll t = TH[i].first;
        ll h = TH[i].second;
        rep(j, 0, X+1) {
            rep(k, 0, M+1) {
                // 枝刈り
                if (j+k > M) break;
                chmax(dp[nxt][j][k], dp[cur][j][k]);
                if (j+1 <= X && k+t-1 <= M) {
                    // スペシャルチケットは常に1枚だけ使うとする
                    chmax(dp[nxt][j+1][k+t-1], dp[cur][j][k]+h);
                }
            }
        }
    }

    ll ans = 0;
    rep(j, 0, X+1) {
        rep(k, 0, M+1) {
            if (j+k > M) break;
            // 両チケットの和がM以内なら、通常チケットで数えた分をスペシャルチケットで代替できるので答えとして使える
            chmax(ans, dp[N%2][j][k]);
        }
    }
    print(ans);
    return 0;
}
