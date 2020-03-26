/**
 * ・自力AC
 * ・インタラクティブっぽいやつ。
 * ・毎回1個ずつ比較してると回数制限が間に合わないので、
 * 　再帰で毎回半分にしていく方針で行ったら無事ACした。
 */

#include <bits/stdc++.h>
#include "ramen.h"
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
typedef vector<vector<pll>> vvpll;
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

ll floor(ll a, ll b) {
    if (a < 0) {
        return (a-b+1)/b;
    } else {
        return a/b;
    }
}

ll ceil(ll a, ll b) {
    if (a >= 0) {
        return (a+b-1)/b;
    } else {
        return a/b;
    }
}

int rec1(vector<ll> &cur) {
    int N = cur.size();
    if (N == 1) {
        return cur[0];
    }
    vector<ll> lo;
    int res, j;
    for (int i = 0; i < N-1; i += 2) {
        j = i + 1;
        res = Compare(cur[i], cur[j]);
        if (res == -1) {
            lo.pb(cur[i]);
        } else {
            lo.pb(cur[j]);
        }
    }
    if (N % 2 == 1) {
       lo.pb(cur[N-1]);
    }
    return rec1(lo);
}

int rec2(vector<ll> &cur) {
    int N = cur.size();
    if (N == 1) {
        return cur[0];
    }
    vector<ll> hi;
    int res, j;
    for (int i = 0; i < N-1; i += 2) {
        j = i + 1;
        res = Compare(cur[i], cur[j]);
        if (res == 1) {
            hi.pb(cur[i]);
        } else {
            hi.pb(cur[j]);
        }
    }
    if (N % 2 == 1) {
        hi.pb(cur[N-1]);
    }
    return rec2(hi);
}

void Ramen(int N) {
    
    if (N == 1) {
        Answer(0, 0);
    }
    int res, j;
    vector<ll> lo, hi;
    for (int i = 0; i < N-1; i += 2) {
        j = i + 1;
        res = Compare(i, j);
        if (res == 1) {
            hi.pb(i);
            lo.pb(j);
        } else {
            lo.pb(i);
            hi.pb(j);
        }
    }
    if (N % 2 == 1) {
        res = Compare(N-1, j);
        if (res == 1) {
            hi.pb(N-1);
        } else {
            lo.pb(N-1);
        }
    }
    Answer(rec1(lo), rec2(hi));
}
