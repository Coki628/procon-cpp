/**
 * ・自力WA
 * ・メモ化再帰
 * ・正解は逆からBFS、だった。pypyでAC。
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

int N;
vector<ll> A, ans;
ll memo[200007];
int visited[200007];

ll rec(ll cur) {
    if (memo[cur] != -1) {
        return memo[cur];
    }
    if (visited[cur] >= 2) {
        return INF;
    }
    visited[cur] += 1;
    ll res = INF;
    if (cur + A[cur] < N) {
        if (A[cur]%2 != (A[cur+A[cur]])%2) {
            memo[cur] = 1;
            return 1;
        } else {
            chmin(res, rec(cur+A[cur]) + 1);
        }
    }
    if (cur - A[cur] >= 0) {
        if (A[cur]%2 != (A[cur-A[cur]])%2) {
            memo[cur] = 1;
            return 1;
        } else {
            chmin(res, rec(cur-A[cur]) + 1);
        }
    }
    memo[cur] = res;
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    ans.resize(N);
    memset(memo, -1, sizeof(memo));
    rep(i, 0, N) cin >> --A[i];

    rep(i, 0, N) {
        rec(i);
    }
    rep(i, 0, N) {
        if (memo[i] < INF) {
            ans[i] = memo[i];
        } else {
            ans[i] = -1;
        }
    }
    print(ans);
    return 0;
}
