/**
 * ・pypyでもTLEなのでこっちでAC0.2秒。
 * ・ゲームDP、メモ化再帰
 * ・円状なのでNでmod取って周期にする以外は割と普通。
 * ・こういうl,rの区間動かしてくタイプのゲームDPはEDPC-LでもpypyTLEしたので、まあしょうがないか。
 * ・計算量自体は2000のNだから400万(ターン偶奇考えても800万)程度なんだけどね。再帰弱いからね。
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

ll N, res;
vector<ll> A;
ll memo[2007][2007][2];

// ゲームDP、メモ化再帰
ll rec(ll l, ll r, ll turn) {
    if (turn == N) {
        return 0;
    }
    if (memo[l][r][turn&1] != -1) {
        return memo[l][r][turn&1];
    }
    // 自分の手番は両方試す
    if ((turn&1) == 0) {
        res = max(rec((l-1+N)%N, r, turn+1) + A[(l-1+N)%N], rec(l, (r+1)%N, turn+1) + A[(r+1)%N]);
    // 相手の手番は必ず大きい方を取る
    } else {
        if (A[(l-1+N)%N] >= A[(r+1)%N]) {
            res = rec((l-1+N)%N, r, turn+1);
        } else {
            res = rec(l, (r+1)%N, turn+1);
        }
    }
    return memo[l][r][turn&1] = res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    rep(i, 0, N) cin >> A[i];
    rep(i, 0, N) rep(j, 0, N) rep(k, 0, 2) memo[i][j][k] = - 1;

    ll ans = 0;
    rep(i, 0, N) {
        // 最初の1つを全箇所試す
        chmax(ans, rec(i, i, 1) + A[i]);
    }
    print(ans);
    return 0;
}
