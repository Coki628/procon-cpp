/**
 * ・さくっと自力AC
 * ・グリッド、その先に出てくる数を前計算しといて後でO(1)で使うやつ。
 * ・900万のグリッドがpypyでも間に合わなくてこっちでAC0.2秒。
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
// void chmax(ll &a, ll b) { a = max(a, b); }
// void chmin(ll &a, ll b) { a = min(a, b); }
template<typename T> inline bool chmax(T &x, T y) {return (y > x) ? x = y, true : false;}
template<typename T> inline bool chmin(T &x, T y) {return (y < x) ? x = y, true : false;}

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
vector<string> grid;
ll cnto[3007][3007], cnti[3007][3007];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> H >> W;
    grid.resize(H);
    rep(i, 0, H) cin >> grid[i];

    // あるマスから先にあるOとIの数を前計算しておく
    rep(i, 0, H) {
        rrep(j, W-1, 0) {
            cnto[i][j-1] = cnto[i][j] + (grid[i][j] == 'O');
        }
    }
    rep(j, 0, W) {
        rrep(i, H-1, 0) {
            cnti[i-1][j] = cnti[i][j] + (grid[i][j] == 'I');
        }
    }

    ll ans = 0;
    rep(i, 0, H) {
        rep(j, 0, W) {
            // Jを見つけたら、前計算したO,Iと組み合わせる数を数える
            if (grid[i][j] == 'J') {
                ans += cnto[i][j] * cnti[i][j];
            }
        }
    }
    print(ans);
    return 0;
}
