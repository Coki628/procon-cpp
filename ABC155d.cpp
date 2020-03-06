/**
 * 参考：https://atcoder.jp/contests/abc155/submissions/10145450
 * ・計算量つらいのでpythonから移植。
 * ・C++の負の除算の切り捨て方向でハマった。
 * ・pythonだと切り捨ては負の方向に丸めるのに対して、C++は0の方向に丸める。
 * ・実用的には前者の方が使い勝手がいいので、よしなに正してくれる関数を拝借。(fromアルメリアさん)
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
void chmax(ll &a, ll b) { a = max(a, b); }
void chmin(ll &a, ll b) { a = min(a, b); }

void print(ld out) {
    cout << fixed << setprecision(12) << out << '\n';
}

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

vector<ll> A, A1, A1b, A2, A3;
ll N, K, N1, N2, N3, res, cnt0;

// x以下の数がK個以上かどうか
bool check(ll x) {
    res = 0;
    // + * +
    rep(i, 0, N3) {
        // 式変形： a * b <= x → b <= floor(x, a)
        // 重複カウントを避けるため、indexを調整
        res += max(upper_bound(btoe(A3), floor(x, A3[i])) - A3.begin() - (i+1), 0LL);
    }
    // - * -
    rep(i, 0, N1) {
        res += max(upper_bound(btoe(A1b), floor(x, A1b[i])) - A1b.begin() - (i+1), 0LL);
    }
    // - * +
    rep(i, 0, N3) {
        res += upper_bound(btoe(A1), floor(x, A3[i])) - A1.begin();
    }
    // 0 * -, 0 * +, 0 * 0
    cnt0 = N2*N1 + N2*N3 + N2*(N2-1)/2;
    if (x >= 0) {
        res += cnt0;
    }
    return res >= K;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> K;
    A.resize(N);
    rep(i, 0, N) cin >> A[i];

    // -, 0, + をそれぞれ別配列に分ける
    sort(btoe(A));
    for (ll a : A) {
        if (a < 0) {
            A1.pb(a);
            A1b.pb(-a);
        } else if (a == 0) {
            A2.pb(a);
        } else {
            A3.pb(a);
        }
    }
    reverse(btoe(A1b));
    N1 = A1.size();
    N2 = A2.size();
    N3 = A3.size();

    print(bisearch_min(-INF, INF, check));
    return 0;
}
