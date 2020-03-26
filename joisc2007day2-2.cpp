/**
 * ・自力AC！
 * ・二分探索、XY独立、にぶたん内でにぶたん
 * ・にぶたんで1番いいところだけ更新するDP(最新だけ持てばいいはずなので、多分DPにしなくてもいい)
 * ・log2つ付いて1秒はきついと思ったので最初からC++でやった。
 * ・DPの遷移どうするかちょっと手間取ったけど(これはもっと早くしたい)、無事一発AC。
 * ・20万にlog2つ付いて0.2秒はやっぱさすがのC++って感じだ。
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

// 条件を満たす最小値を見つける二分探索
ll bisearch_min(ll mn, ll mx, function<bool(ll)> func) {

    ll ok = mx;
    ll ng = mn;
    while (ng+1 < ok) {
        ll mid = (ok+ng) / 2;
        if (func(mid)) {
            // 下を探しに行く
            ok = mid;
        } else {
            // 上を探しに行く
            ng = mid;
        }
    }
    return ok;
}

ll N, M;
vector<ll> X, Y;
ll dp[200007];

// Dの幅をmとした時、全区間をカバーするのに必要な装置の数がN以内かどうか
bool check(ll m) {
    fill(dp, dp+M+7, INF);
    ll nxt = 0;
    // dp[i] := i番目の座標までをカバーするのに必要な装置の数
    dp[0] = 0;
    rep(i, 0, M) {
        if (dp[i] == INF) continue;
        // i~nxtまでは1台でカバーできる
        nxt = upper_bound(X.begin(), X.end(), X[i]+m) - X.begin() - 1;
        chmin(dp[nxt+1], dp[i] + 1);
    }
    ll res1 = dp[M];
    fill(dp, dp+M+7, INF);
    nxt = 0;
    dp[0] = 0;
    rep(i, 0, M) {
        if (dp[i] == INF) continue;
        nxt = upper_bound(Y.begin(), Y.end(), Y[i]+m) - Y.begin() - 1;
        chmin(dp[nxt+1], dp[i] + 1);
    }
    ll res2 = dp[M];
    // X,Y合わせた必要な数がN以内ならOK
    return res1 + res2 <= N;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> M;
    X.resize(M);
    Y.resize(M);
    rep(i, 0, M) cin >> X[i] >> Y[i];

    // X,Y独立にして、ソートしておく
    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());
    // Dの幅で二分探索
    ll res = bisearch_min(-1, pow(10, 9) + 7, check);
    print(res);
    return 0;
}
