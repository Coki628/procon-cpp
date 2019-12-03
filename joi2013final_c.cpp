/**
 * ・蟻本演習3-1-3、自力AC！
 * ・二分探索、最小値の最大化(最大値の最小化)
 * ・にぶたん内でにぶたん系
 * ・計算量はNlogNlogmax(A)=10万*30*17くらい=5100万
 * ・C++さすがの0.3秒AC。
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<ll, int, int> tlii;
typedef pair<ll, ll> pll;
typedef pair<ll, int> pli;
typedef pair<int, int> pii;
typedef pair<pair<int, int>, ll> ppiil;
typedef vector<vector<ll>> vvl;
typedef vector<vector<int>> vvi;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define all(obj) (obj).begin(), (obj).end()
#define pb push_back
#define str to_string
#define mkp make_pair
#define mkt make_tuple
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

int N, i, idx1, idx2;
ll total, offset, a1, a2, ans, res;
vector<ll> A, acc;

ll check(ll m) {
    // 1つ目の切れ込み
    auto itr1 = lower_bound(next(acc.begin(), i), next(acc.begin(), i+N), m+offset);
    a1 = *itr1 - offset;
    // 2つ目の切れ込み
    auto itr2 = lower_bound(next(acc.begin(), i), next(acc.begin(), i+N), m+a1+offset);
    a2 = *itr2 - offset;
    // 最後のピースのサイズがm以上あればOK
    return total - a2 >= m;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    rep(i, 0, N) cin >> A[i];
    // 累積和を2周分作る
    acc.resize(N*2);
    acc[0] = A[0];
    rep(i, 1, N*2) acc[i] = acc[i-1] + A[i%N];
    total = sum(A);
    offset = 0;
    ans = 0;

    rep(i, 0, N) {
        ::i = i;
        res = bisearch_max(0, total/2, check);
        chmax(ans, res);
        offset += A[i];
    }

    print(ans);
    return 0;
}
