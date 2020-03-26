/**
 * ・自力WA。。
 * ・小さい方から貪欲にやったけど無理だった。。
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

inline ll pow(int a, ll b) {
    ll res = 1;
    rep(_, 0, b) res *= a;
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

ll N, M;
vector<pll> VS;
vector<ll> C, A, A2, L;
multimap<ll, ll> D;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> M;
    VS.resize(N);
    A.resize(M);
    rep(i, 0, M) A[i] = INF;
    rep(i, 0, N) cin >> VS[i].second >> VS[i].first;
    ll c;
    rep(i, 0, M) {
        cin >> c;
        D.insert(mkp(c, 0));
    }
    ll i = 0;
    for (auto &p : D) {
        p.second = i;
        i++;
    }

    sort(VS.begin(), VS.end());
    for (auto p : VS) {
        auto itr = D.lower_bound(p.second);
        if (itr == D.end()) {
            continue;
        }
        auto p2 = *itr;
        A[p2.second] = p.first;
        D.erase(itr);
    }
    for (ll a : A) {
        if (a != INF) {
            A2.pb(a);
        }
    }

    if (!A2.size()) {
        print(0);
        return 0;
    }
    // 広義LIS
    ll M2 = A2.size();
    L.pb(A2[0]);
    rep(i, 1, M2) {
        if (A2[i] >= L.back()) {
            L.pb(A2[i]);
        } else {
            ll idx = upper_bound(L.begin(), L.end(), A2[i]) - L.begin();
            L[idx] = A2[i];
        }
    }
    ll ans = L.size();
    print(ans);
    return 0;
}
