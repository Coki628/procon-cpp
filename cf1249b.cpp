/**
 * ・再帰が深くてpythonやられたやつ、こっちでAC。
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<ll, int, int> tlii;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef vector<vector<ll>> vvl;
typedef vector<vector<int>> vvi;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define all(obj) (obj).begin(), (obj).end()
#define pb push_back
#define str to_string
#define mkp make_pair
#define mkt make_tuple
// #define print(out) cout << (out) << endl
const ll INF = 1e18;
const ll MOD = 1e9 + 7;
void chmax(ll &a, ll b) { a = max(a, b); }
void chmin(ll &a, ll b) { a = min(a, b); }

template<typename Any>
void print(Any out) {
    cout << out << '\n';
}

template<typename T1, typename T2>
void print(pair<T1, T2> out) {
    cout << out.first << ' ' << out.second << '\n';
}

void print(vector<ll> A) {
    rep(i, 0, A.size()) {
        cout << A[i];
        cout << (i == A.size()-1 ? '\n' : ' ');
    }
}

void print(vector<int> A) {
    rep(i, 0, A.size()) {
        cout << A[i];
        cout << (i == A.size()-1 ? '\n' : ' ');
    }
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

int Q, N, nxt;
vector<int> A, ans;

int rec(int i, int org, int cnt) {
    nxt = A[i];
    if (nxt != org) {
        cnt = rec(nxt, org, cnt+1);
    }
    ans[i] = cnt;
    return cnt;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> Q;
    rep(_, 0, Q) {
        cin >> N;
        A.clear();
        A.resize(N);
        ans.clear();
        ans.resize(N, -1);
        rep(i, 0, N) {
            cin >> A[i];
            A[i]--;
        }
        rep(i, 0, N) {
            if (ans[i] == -1) {
                rec(i, i, 1);
            }
        }
        print(ans);
    }
    return 0;
}
