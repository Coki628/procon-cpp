/**
 * ・すげー粘ってなんとか自力AC！
 * ・平面走査っぽいもの、イベントソート
 * ・内ループのmapをunordered_mapにしたらTLEがACになった。
 * ・確かに2重ループで既に5000^2だから、それにlog乗ったらきついか。
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

ll N, H, W, ah, aw, bh, bw, u, d, l, r, h;
vector<pair<pll, pll>> events;
unordered_map<ll, ll> row;
ll C[5007];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    cin >> W >> H;
    rep(i, 0, N) {
        cin >> aw >> ah >> bw >> bh;
        // 挿入
        events.pb(mkp(mkp(ah, 2), mkp(aw, bw)));
        // 削除
        events.pb(mkp(mkp(bh+1, 1), mkp(aw, bw)));
    }
    // Y座標順、同値は、削除→挿入、の順でソート
    sort(btoe(events), [](const pair<pll, pll> &e1, const pair<pll, pll> &e2) { 
        if (e1.first.first == e2.first.first) {
            return e1.first.second < e2.first.second;
        } else {
            return e1.first.first < e2.first.first;
        }
    });

    d = events[0].first.first;
    for (auto event : events) {
        u = event.first.first;
        h = u - d;
        // 高さが変わったところで、列毎に重なりを集計
        if (h != 0) {
            for (auto kv : row) {
                C[kv.second] += h;
            }
        }
        l = event.second.first;
        r = event.second.second;
        // 削除
        if (event.first.second == 1) {
            rep(i, l, r+1) {
                row[i]--;
            }
        // 挿入
        } else {
            rep(i, l, r+1) {
                row[i]++;
            }
        }
        d = u;
    }

    // 0ではない一番大きいところが答え
    ll ans = 0, mx = 0;
    rep(i, 0, 5007) {
        if (C[i] != 0) {
            mx = i;
            ans = C[i];
        }
    }
    print(mx);
    print(ans);
    return 0;
}
