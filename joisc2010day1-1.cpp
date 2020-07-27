/**
 * ・自力WA。。
 * ・どのみちTLEなんだけど、内ループを集合管理。
 * ・TLEは分かるんだけど、WAはなんでか分からん。どこがバグってんだろ。。
 * →分かった。bitsetの使い方間違ってた。1<<iとかじゃなくて.set(i)ってする。これでTLE。
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
vector<bitset<407>> J, O, I;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> H >> W;
    J.resize(H);
    O.resize(H);
    I.resize(H);
    rep(i, 0, H) {
        rep(j, 0, W) {
            cin >> grid[i][j];
            if (grid[i][j] == 0) {
                J[i].set(j);
            } else if (grid[i][j] == 1) {
                O[i].set(j);
            } else {
                I[i].set(j);
            }
        }
    }

    bitset<407> bit1, bit2, bit;
    ll ans = 0;
    rep(i, 0, H) {
        rep(j, i+1, H) {
            rep(k, 0, W) {
                int a = grid[i][k];
                int b = grid[j][k];
                if (a == 0 && b == 0) {
                    bit1 = O[i] & I[j];
                    bit2 = O[j] & I[i];
                } else if (a == 1 && b == 1) {
                    bit1 = J[i] & I[j];
                    bit2 = J[j] & I[i];
                } else if (a == 2 && b == 2) {
                    bit1 = J[i] & O[j];
                    bit2 = J[j] & O[i];
                } else if (a == 0 && b == 1 || a == 1 && b == 0) {
                    bit1 = I[i];
                    bit2 = I[j];
                } else if (a == 0 && b == 2 || a == 2 && b == 0) {
                    bit1 = O[i];
                    bit2 = O[j];
                } else if (a == 1 && b == 2 || a == 2 && b == 1) {
                    bit1 = J[i];
                    bit2 = J[j];
                }
                bit = bit1 | bit2;
                bit >>= k + 1;
                ans += bit.count();
            }
        }
    }
    print(ans);
    return 0;
}
