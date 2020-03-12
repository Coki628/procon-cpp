/**
 * ・セグ木をSparse TableにしたらTLE→AC0.2秒。
 * ・区間最大、最小を取りながらDPする。
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

struct SparseTable {

    const function<ll(ll, ll)> func;
    vvl dat;
    vector<ll> height;

    SparseTable(function<ll(ll, ll)> func) : func(func) {
    }

    SparseTable(vector<ll> A, function<ll(ll, ll)> func) : func(func) {
        build(A);
    }

    void build(vector<ll> A) {
        ll N = A.size();

        ll h = 0;
        while ((1<<h) < N) {
            h++;
        }
        dat.resize(h);
        rep(i, 0, h) dat[i].resize(1<<h);
        height.resize(N+1);

        rep(i, 2, N+1) {
            height[i] = height[i>>1] + 1;
        }
        rep(i, 0, N) {
            dat[0][i] = A[i];
        }
        rep(i, 1, h) {
            rep(j, 0, N) {
                dat[i][j] = func(dat[i-1][j], dat[i-1][min(j+(1<<(i-1)), N-1)]);
            }
        }
    }

    // 区間[l,r)でのmin,maxを取得
    ll get(ll l, ll r) {
        if (l >= r) throw exception();
        ll a = height[r-l];
        return func(dat[a][l], dat[a][r-(1<<a)]);
    }
};

ll N, M, K;
vector<ll> A;
ll dp[20007];
SparseTable stmx([](ll a, ll b) { return max(a, b); });
SparseTable stmn([](ll a, ll b) { return min(a, b); });

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> M >> K;
    A.resize(N);
    rep(i, 0, N) cin >> A[i];
    // 任意の区間での最大、最小をO(1)で出せるようにしておく
    stmx.build(A);
    stmn.build(A);
    rep(i, 0, N+1) dp[i] = INF;

    // dp[i] := オレンジをi個目まで詰めた時の最小コスト
    dp[0] = 0;
    rep(i, 0, N) {
        rep(j, i+1, N+1) {
            int s = j - i;
            if (s > M) {
                break;
            }
            ll mx = stmx.get(i, j);
            ll mn = stmn.get(i, j);
            // i個済の状態からs個詰める遷移
            chmin(dp[j], dp[i] + (K + s * (mx - mn)));
        }
    }
    ll ans = dp[N];
    print(ans);
    return 0;
}
