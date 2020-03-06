/**
 * ・100万グリッドの2次元累積和で、制約0.5秒と64MB。
 * ・絶対pythonTLE,pypyMLEだと思ったから、最初からC++で書いてAC。
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

ll H, W, Q, lh, lw, rh, rw, ansj, anso, ansi;
vector<string> grid;
vector<ll> ans(3);
ll accj[1007][1007], acco[1007][1007], acci[1007][1007];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> H >> W;
    cin >> Q;
    grid.resize(H);
    rep(i, 0, H) cin >> grid[i];

    rep(i, 0, H) {
        rep(j, 0, W) {
            // 3種類別々に2次元累積和を作る
            if (grid[i][j] == 'J') {
                accj[i+1][j+1] = 1;
            } else if (grid[i][j] == 'O') {
                acco[i+1][j+1] = 1;
            } else {
                acci[i+1][j+1] = 1;
            }
        }
    }
    rep(i, 0, H+1) {
        rep(j, 0, W) {
            accj[i][j+1] += accj[i][j];
            acco[i][j+1] += acco[i][j];
            acci[i][j+1] += acci[i][j];
        }
    }
    rep(j, 0, W+1) {
        rep(i, 0, H) {
            accj[i+1][j] += accj[i][j];
            acco[i+1][j] += acco[i][j];
            acci[i+1][j] += acci[i][j];
        }
    }

    rep(i, 0, Q) {
        cin >> lh >> lw >> rh >> rw;
        
        ans[0] = accj[rh][rw] - accj[rh][lw-1] - accj[lh-1][rw] + accj[lh-1][lw-1];
        ans[1] = acco[rh][rw] - acco[rh][lw-1] - acco[lh-1][rw] + acco[lh-1][lw-1];
        ans[2] = acci[rh][rw] - acci[rh][lw-1] - acci[lh-1][rw] + acci[lh-1][lw-1];
        print(ans);
    }
    return 0;
}
