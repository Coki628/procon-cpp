/**
 * ・2次元累積和
 * ・125^4のループは*1/4=約6100万になっててもつらくてpypyでもTLE。。
 * ・C++でさすがのAC0.1秒。
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
void chmax(ll &a, ll b) { a = max(a, b); }
void chmin(ll &a, ll b) { a = min(a, b); }

void print(ld out) {
    cout << fixed << setprecision(12) << out << '\n';
}

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

ll H, W, K, V, ans, land, square, price;
ll grid[129][129];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> H >> W >> K >> V;
    rep(i, 0, H) rep(j, 0, W) cin >> grid[i+1][j+1];

    rep(i, 0, H+1) rep(j, 0, W) grid[i][j+1] += grid[i][j];
    rep(j, 0, W+1) rep(i, 0, H) grid[i+1][j] += grid[i][j];

    ans = 0;
    rep(h1, 1, H+1) {
        rep(w1, 1, W+1) {
            rep(h2, h1, H+1) {
                rep(w2, w1, W+1) {
                    land = grid[h2][w2] - grid[h1-1][w2] - grid[h2][w1-1] + grid[h1-1][w1-1];
                    square = (h2-h1+1) * (w2-w1+1);
                    price = land + square * K;
                    if (price <= V) {
                        chmax(ans, square);
                    }
                }
            }
        }
    }
    print(ans);
    return 0;
}
