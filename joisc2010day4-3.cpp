/**
 * ・自力AC！
 * ・二分探索、にぶたん内で判定が色々ゴチャゴチャする系
 * ・ちょっと時間かかったけど、正しく実装できて良かった。
 * ・10万にlog2つ乗るから(制約1秒だし)、最初からC++でやった。AC0.1秒。
 * ・2秒あればpypy行けそうだけど、1秒は厳しいかなーって感じ。(試してないけど)
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

ll K, N, M, times;
vector<ll> A, tmp, ans1, ans2, org;

// 合格ボーダーGを探す
bool checkg(ll m) {
    int cnt = 0;
    rrep(i, K-1, -1) {
        // m点以上獲得している人をカウント
        if (tmp[i] >= m) {
            cnt++;
        } else {
            break;
        }
    }
    // 全体の1/12以上かどうか
    return cnt >= K / 12.0;
}

// m番目の人が金メダル確実かどうか
bool check1(ll m) {
    rep(i, 0, K) tmp[i] = A[i];
    rep(i, 0, K) {
        // m番目の人以外に最大得点を与える
        if (i == m) continue;
        tmp[i] += 100 * times;
    }
    ll a = tmp[m];
    sort(btoe(tmp));
    ll g = bisearch_max(0, INF, checkg);
    return a >= g;
}

// m番目の人が金メダルを取る可能性があるかどうか
bool check2(ll m) {
    rep(i, 0, K) tmp[i] = A[i];
    // m番目の人だけに最大得点を与える
    tmp[m] += 100 * times;
    ll a = tmp[m];
    sort(btoe(tmp));
    ll g = bisearch_max(0, INF, checkg);
    return a >= g;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> K >> N >> M;
    A.resize(K);
    tmp.resize(K);
    org.resize(K);
    times = N - M;
    rep(i, 0, K) {
        cin >> A[i]; 
        org[i] = A[i];
    }
    sort(btoe(A));
    reverse(btoe(A));

    int idx = bisearch_max(-1, K, check1);
    if (idx != -1) {
        ll border = A[idx];
        rep(i, 0, K) {
            // 元の並びを使ってボーダー以上を集める
            if (org[i] >= border) {
                ans1.pb(i+1);
            }
        }
    }

    idx = bisearch_max(-1, K, check2);
    if (idx != - 1) {
        ll border = A[idx];
        rep(i, 0, K) {
            if (org[i] >= border) {
                ans2.pb(i+1);
            }
        }
    }

    for (ll a : ans1) {
        print(a);
    }
    print("--------");
    for (ll a : ans2) {
        print(a);
    }
    return 0;
}
