/**
 * ・pypyTLEでC++移植。でもこれもTLE。。
 * ・優先度付きキュー、C++のはデフォだと降順に並ぶ。
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

ll N, M, Q;
vector<ll> A, B, B2;
vector<pll> A2;
priority_queue<pll, vector<pll>> que;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> Q;
    rep(_, 0, Q) {

        cin >> N >> M;
        A.resize(N);
        rep(i, 0, N) cin >> A[i];
        B.resize(M);
        rep(i, 0, M) cin >> B[i];
        B2.resize(N+1);
        rep(i, 0, N+1) B2[i] = INF;
        rep(i, 0, M) B2[B[i]] = i + 1;
        A2.resize(N);
        rep(i, 0, N) {
            ll order = B2[A[i]];
            A2[i] = mkp(order, A[i]);
        }
        reverse(btoe(A2));
        ll cnt = 0;
        for (ll b : B) {
            while (1) {
                pll a = A2.back(); A2.pop_back();
                cnt++;
                if (a.second == b) {
                    break;
                }
                que.push(a);
            }
            while (!que.empty()) {
                pll a = que.top(); que.pop();
                A2.push_back(a);
                cnt++;
            }
        }
        print(cnt);
    }
    return 0;
}
