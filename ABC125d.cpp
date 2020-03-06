/**
 * ・速解き特訓ABC周回
 * ・3重ループを2重+logに落とす。
 * ・にぶたん内でにぶたん
 * ・100万にlog2つ乗ってpypyでもつらすぎるのでこっちで。
 * ・惜しくも自力ACならず。。
 * ・同値がたくさんある時、出力をKより多く出してた。
 * ・それだけ直したら無事AC1.2秒。
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

// 条件を満たす最大値を見つける二分探索
ll bisearch_max(ll mn, ll mx, function<bool(ll)> func) {

    ll ok = mn;
    ll ng = mx;
    while (ok+1 < ng) {
        ll mid = (ok+ng) / 2;
        if (func(mid)) {
            // 上を探しに行く
            ok = mid;
        } else {
            // 下を探しに行く
            ng = mid;
        }
    }
    return ok;
}

ll X, Y, Z, K;
vector<ll> A, B, C, ans;

// K個以上の3つ組が達成できるような最大の値mを探す
bool check(ll m) {
    ll sm = 0;
    for (ll a : A) {
        for (ll b : B) {
            ll cnt = Z - (lower_bound(btoe(C), m-a-b) - C.begin());
            sm += cnt;
        }
    }
    return sm >= K;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> X >> Y >> Z >> K;
    A.resize(X);
    B.resize(Y);
    C.resize(Z);
    rep(i, 0, X) cin >> A[i];
    rep(i, 0, Y) cin >> B[i];
    rep(i, 0, Z) cin >> C[i];
    sort(btoe(C));

    ll res = bisearch_max(0, INF, check);

    for (ll a : A) {
        for (ll b : B) {
            ll idx = lower_bound(btoe(C), res-a-b) - C.begin();
            rrep(i, Z-1, idx-1) {
                ll c = C[i];
                ans.pb(a+b+c);
            }
        }
    }
    sort(btoe(ans));
    reverse(btoe(ans));
    // K個まで出力
    rep(i, 0, K) print(ans[i]);
    return 0;
}
