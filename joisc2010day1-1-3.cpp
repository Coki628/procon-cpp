/**
 * 参考：http://h0rnet.hatenablog.com/entry/2016/03/15/JOI_11_Day1_Banner_%28_DP_%29
 * ・自力ならず。。
 * ・内ループを1つ外すために、色パターンの出現数を前計算しておく。
 * ・それでも計算量は400^3/2*8=2億5600万くらいある。AC0.5秒はさすがC++。
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

ll H, W;
int grid[407][407];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> H >> W;
    rep(i, 0, H) {
        rep(j, 0, W) {
            cin >> grid[i][j];
        }
    }

    ll ans = 0;
    vector<int> C(1<<3);
    int a, b, bit;
    int has3 = (1<<3) - 1;
    rep(i, 0, H) {
        rep(j, i+1, H) {
            // C[i] := 行i,jを使う時の、各列での色パターンの出現数を集計
            rep(bit, 0, 1<<3) C[bit] = 0;
            rep(k, 0, W) {
                a = grid[i][k];
                b = grid[j][k];
                bit = (1<<a) | (1<<b);
                C[bit]++;
            }
            rep(k, 0, W) {
                a = grid[i][k];
                b = grid[j][k];
                bit = (1<<a) | (1<<b);
                rep(bit2, 0, 1<<3) {
                    // 今回使う列(bit)と合わせて3色揃うようなパターン(bit2)であれば、その出現数を答えに足す
                    if ((bit | bit2) == has3) {
                        ans += C[bit2];
                    }
                }
            }
        }
    }
    // 2重に数えているので/2する
    print(ans / 2);
    return 0;
}
