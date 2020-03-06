/**
 * ・半分全列挙
 * ・TLEだけどね。。
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

template<typename T>
map<T, ll> Counter(vector<T> A) {
    map<T, ll> res;
    for (T a : A) {
        res[a]++;
    }
    return res;
}

ll N, K;
vector<ll> A, A1, A2, P1, P2;
map<ll, ll> C;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> K;
    A.resize(N);
    rep(i, 0, N) cin >> A[i];
    // 総和0を平均KとするためにKを引く
    rep(i, 0, N) A[i] -= K;
    // 半分全列挙
    rep(i, 0, N/2) A1.pb(A[i]);
    rep(i, N/2, N) A2.pb(A[i]);
    
    // それぞれの全組み合わせ
    P1.pb(0);
    rep(S, 1, 1<<A1.size()) {
        ll p = 0;
        rep(i, 0, A1.size()) {
            if (S & (1<<i)) {
                p += A1[i];
            }
        }
        P1.pb(p);
    }
    P2.pb(0);
    rep(S, 1, 1<<A2.size()) {
        ll p = 0;
        rep(i, 0, A2.size()) {
            if (S & (1<<i)) {
                p += A2[i];
            }
        }
        P2.pb(p);
    }

    // 総和0になるペアの数を求める
    C = Counter(P2);
    ll ans = 0;
    for (ll p : P1) {
        ans += C[-p];
    }
    // どちらも1つも選ばない分の1を引く
    print(ans - 1);
    return 0;
}
