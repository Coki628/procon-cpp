
/**
 * ・ゲームDP、メモ化再帰
 * ・これはC++でもTLE。。
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

ll N, Z, W;
vector<ll> A;
ll memo[2007][2007][2];

ll rec(ll cur, ll prev, bool turn) {
    if (cur == N) {
        return abs(A[cur] - A[prev]);
    }
    if (memo[cur][prev][turn] != -1) {
        return memo[cur][prev][turn];
    }
    ll res = 0;
    if (!turn) {
        res = 0;
        rep(nxt, cur+1, N+1) {
            chmax(res, rec(nxt, cur, 1 - turn));
        }
    } else {
        res = INF;
        rep(nxt, cur+1, N+1) {
            chmin(res, rec(nxt, cur, 1 - turn));
        }
    }
    return memo[cur][prev][turn] = res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> Z >> W;
    A.resize(N+1);
    A[0] = W;
    memset(memo, -1, sizeof(memo));
    rep(i, 1, N+1) cin >> A[i]; 

    print(rec(0, 0, 0));
    return 0;
}
