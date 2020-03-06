
/**
 * ・平面走査、平衡二分探索木、イベントソート
 * ・解説は螺旋本が詳しい。
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
// void chmax(ll &a, ll b) { a = max(a, b); }
// void chmin(ll &a, ll b) { a = min(a, b); }
template<typename T> inline bool chmax(T &x, T y) {return (y > x) ? x = y, true : false;}
template<typename T> inline bool chmin(T &x, T y) {return (y < x) ? x = y, true : false;}

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

ll N, ax, ay, bx, by, ans;
set<ll> S;
vector<pair<pll, pll>> events;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    rep(i, 0, N) {
        cin >> ax >> ay >> bx >> by;
        if (ax == bx) {
            // 向き補正
            if (by < ay) swap(ay, by);
            // 挿入：(y座標(始点), フラグ), (x座標(どっちでもいい), x座標(どっちでもいい)))
            events.pb(mkp(mkp(ay, 1), mkp(ax, bx)));
            // 削除：(y座標(終点), フラグ), (x座標(どっちでもいい), x座標(どっちでもいい)))
            events.pb(mkp(mkp(by, 3), mkp(ax, bx)));

        } else {
            // 向き補正
            if (bx < ax) swap(ax, bx);
            // カウント：(y座標(どっちでもいい), フラグ), (x座標(始点), x座標(終点)))
            events.pb(mkp(mkp(ay, 2), mkp(ax, bx)));
        }
    }
    // Y座標順、同値は、挿入→カウント→削除、の順でソート
    sort(btoe(events), [](const pair<pll, pll> &e1, const pair<pll, pll> &e2) { 
        if (e1.first.first == e2.first.first) {
            return e1.first.second < e2.first.second;
        } else {
            return e1.first.first < e2.first.first;
        }
    });

    S.insert(INF);
    ans = 0;
    for (auto event : events) {
        // 挿入
        if (event.first.second == 1) {
            S.insert(event.second.first);
        // カウント
        } else if (event.first.second == 2) {
            auto itr1 = S.lower_bound(event.second.first);
            auto itr2 = S.upper_bound(event.second.second);
            ans += distance(itr1, itr2);
        // 削除
        } else {
            S.erase(event.second.first);
        }
    }
    print(ans);
    return 0;
}
