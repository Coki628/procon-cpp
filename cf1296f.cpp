/**
 * ・python,pypyで5000ループ内で5000再帰は間に合わずTLE。
 * ・C++さすがのAC、0.7秒。
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<ll, int> pli;
typedef pair<int, int> pii;
typedef pair<pii, ll> ppiil;
typedef pair<pll, ll> pplll;
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

ll N, M, a, b, X, g, idx;
map<pll, ll> D, edges;
bool is_ok;
vvl nodes;
vector<ll> ans;
vector<pplll> Qs;

bool rec(ll u, ll prev) {
    if (u == X) {
        a = min(u, prev);
        b = max(u, prev);
        if (g >= D[mkp(a, b)]) {
            is_ok = true;
            D[mkp(a, b)] = g;
        }
        return true;
    }
    for (ll v : nodes[u]) {
        if (v == prev) {
            continue;
        }
        if (rec(v, u)) {
            a = min(u, prev);
            b = max(u, prev);
            if (a == -1) {
                return true;
            }
            if (g >= D[mkp(a, b)]) {
                is_ok = true;
                D[mkp(a, b)] = g;
            }
            return true;
        }
    }
    return false;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    nodes.resize(N);
    rep(i, 0, N-1) {
        cin >> a >> b;
        a--;
        b--;
        nodes[a].pb(b);
        nodes[b].pb(a);
        edges[mkp(min(a, b), max(a, b))] = i;
    }

    cin >> M;
    rep(i, 0, M) {
        cin >> a >> X >> g;
        a--;
        X--;
        Qs.pb(mkp(mkp(a, X), g));
    }
    for (pplll p : Qs) {
        a = p.first.first;
        X = p.first.second;
        g = p.second;
        rec(a, -1);
    }
    for (pplll p : Qs) {
        a = p.first.first;
        X = p.first.second;
        g = p.second;
        is_ok = false;
        rec(a, -1);
        if (!is_ok) {
            print(-1);
            return 0;
        }
    }

    ans.resize(N-1);
    rep(i, 0, N-1) ans[i] = pow(10, 6);
    for (auto kv : D) {
        idx = edges[kv.first];
        ans[idx] = kv.second;
    }
    print(ans);
    return 0;
}
