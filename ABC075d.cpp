
/**
 * ・pypyTLEのためこっちでAC
 * ・20億^2で10^18を超えるので19乗、llのオーバーフローが心配だったけど、
 * 　とりあえず手元でもAtCoder環境でもちゃんと動いた。
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
const ll INF = 1e19;
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

ll N, K;
vector<pll> XY;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> K;
    XY.resize(N);
    rep(i, 0, N) cin >> XY[i].first >> XY[i].second; 

    ll ans = INF;
    // 4点組み合わせ全部試す
    rep(i, 0, N) {
        ll x1 = XY[i].first;
        ll y1 = XY[i].second;
        rep(j, i, N) {
            ll x2 = XY[j].first;
            ll y2 = XY[j].second;
            rep(k, j, N) {
                ll x3 = XY[k].first;
                ll y3 = XY[k].second;
                rep(l, k, N) {
                    ll x4 = XY[l].first;
                    ll y4 = XY[l].second;
                    ll xl = min({x1, x2, x3, x4});
                    ll xr = max({x1, x2, x3, x4});
                    ll yl = min({y1, y2, y3, y4});
                    ll yr = max({y1, y2, y3, y4});
                    // 4点の内側にいくつ点があるか数える
                    ll cnt = 0;
                    for (pll xy : XY) {
                        ll x5 = xy.first;
                        ll y5 = xy.second;
                        if (xl <= x5 && x5 <= xr && yl <= y5 && y5 <= yr) {
                            cnt++;
                        }
                    }
                    if (cnt >= K) {
                        chmin(ans, (xr-xl) * (yr-yl));
                    }
                }
            }
        }
    }
    print(ans);
    return 0;
}
