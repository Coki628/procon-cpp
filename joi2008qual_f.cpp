/**
 * 参考：https://comprolog.netlify.com/post/joi/2009qual6/
 * ・誤読で難しいこと考えてた。。N*Nが普通に1本の数列として見れる。
 * ・素直に3次元DPするとMLEするので2次元使い回しで。
 * ・計算量がM*N^2*S=2億9400万にもなるんだけど、C++はAC0.8秒。
 * ・添字としては、何番目の位置まで見て、ではなく、
 * 　何番目の値まで見て、を1次元目でindexにするとうまくいく。
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

ll N, M, S;
int dp[50][3007], nxt[50][3007];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> M >> S;
    
    ll NN = pow(N, 2);
    // dp[a][j][k] := 値aまで見て、位置jまで確定して、総和がkの時の通り数
    dp[0][0] = 1;
    rep(a, 1, M+1) {
        rep(j, 0, NN+1) {
            rep(k, 0, S+1) {
                nxt[j][k] += dp[j][k];
                if (j-1 >= 0 && k-a >= 0) {
                    nxt[j][k] += dp[j-1][k-a];
                }
                nxt[j][k] %= MOD;
            }
        }
		memcpy(dp, nxt, sizeof(nxt));
		memset(nxt, 0, sizeof(nxt));
    }
    ll ans = dp[NN][S];
    print(ans);
    return 0;
}
