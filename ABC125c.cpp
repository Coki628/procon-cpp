/**
 * ・蟻本演習3-3-4
 * ・平方分割
 * ・pypyTLEだったのでこっちでAC確認。
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

int gcd(int a, int b) {
    if (b==0) return a;
   	else return gcd(b, a%b);
}

ll N, D;
vector<ll> A, gcds;
vvl bucket;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    rep(i, 0, N) cin >> A[i];

    // 平方分割
    D = ceil(sqrt(N));
    bucket.resize(D);
    gcds.resize(D);
    rep(i, 0, N) bucket[i/D].pb(A[i]);
    // 各バケットで全体のGCDを予め取っておく
    rep(i, 0, D) {
        for (ll a : bucket[i]) {
            gcds[i] = gcd(gcds[i], a);
        }
    }

    ll ans = 0;
    rep(i, 0, D) {
        rep(j, 0, bucket[i].size()) {
            ll tmp = 0;
            // バケット内でa以外全ての要素とGCD
            rep(k, 0, bucket[i].size()) {
                if (j == k) continue;
                tmp = gcd(tmp, bucket[i][k]);
            }
            // aを含むバケット以外の全てのバケットとGCD
            rep(k, 0, D) {
                if (i == k) continue;
                tmp = gcd(tmp, gcds[k]);
            }
            ans = max(ans, tmp);
        }
    }
    print(ans);
    return 0;
}
