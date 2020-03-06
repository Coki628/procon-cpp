/**
 * ・蟻本演習2-6-6
 * ・繰り返し二乗法
 * ・定数倍高速化してAC。
 * ・ループを半分にして、vectorのresizeを配列静的確保にした。
 * ・計算量P^2=1億を0.5秒弱。この問題制約0.5秒でギリギリだけどね。
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<ll, int, int> tlii;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef vector<vector<ll>> vvl;
typedef vector<vector<int>> vvi;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define all(obj) (obj).begin(), (obj).end()
#define pb push_back
#define str to_string
#define mkp make_pair
#define mkt make_tuple
// #define print(out) cout << (out) << endl
const ll INF = 1e18;
const ll MOD = 1e9 + 7;
void chmax(ll &a, ll b) { a = max(a, b); }
void chmin(ll &a, ll b) { a = min(a, b); }

template<typename Any>
void print(Any out) {
    cout << out << '\n';
}

template<typename T1, typename T2>
void print(pair<T1, T2> out) {
    cout << out.first << ' ' << out.second << '\n';
}

void print(vector<ll> A) {
    rep(i, 0, A.size()) {
        cout << A[i];
        cout << (i == A.size()-1 ? '\n' : ' ');
    }
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

ll pow(ll x, ll n, int mod) {
    // 繰り返し二乗法
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

int P, N, z;
ll ans;
ll cnts[10007];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> P;
    cin >> N;

    rep(i, 0, P) {
        // 0..Pについて、i^N が mod P でいくつになるかを集計しておく
        cnts[pow(i, N, P)]++;
    }

    ans = 0;
    rep(x, 0, P) {
        rep(y, x+1, P) {
            // x,yが決まればzも定まる
            z = (x+y) % P;
            // x+y と y+x の分で *2
            ans += cnts[x] * cnts[y] * cnts[z] * 2;
        }
        // x==y の分
        z = (x+x) % P;
        ans += cnts[x] * cnts[x] * cnts[z];
    }
    print(ans);
    return 0;
}
