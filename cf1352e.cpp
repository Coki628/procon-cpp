/**
 * ・終了後、(他のが終わった後で)15分くらいやって自力AC。
 * ・累積和
 * ・ありうる区間全てをキーとして持つとMLEする。(64MB制限)
 * 　予め数列Aの方に含まれる値をキーとして持って、区間全部見る時には確認だけするようにする。
 * 　これだと、キーはN^2ではなくN個程度持てばいい感じになるので無事AC。
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
typedef pair<pli, int> pplii;
typedef vector<vector<ll>> vvl;
typedef vector<vector<int>> vvi;
typedef vector<vector<pll>> vvpll;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define pb push_back
#define tostr to_string
#define mkp make_pair
const ll INF = 1e18;
const ll MOD = 1e9 + 7;

void print(ld out) { cout << fixed << setprecision(12) << out << '\n'; }
template<typename T> void print(T out) { cout << out << '\n'; }
template<typename T1, typename T2> void print(pair<T1, T2> out) { cout << out.first << ' ' << out.second << '\n'; }
template<typename T> void print(vector<T> A) { rep(i, 0, A.size()) { cout << A[i]; cout << (i == A.size()-1 ? '\n' : ' '); } }
template<typename T> void print(set<T> S) { vector<T> A(S.begin(), S.end()); print(A); }

template<typename T> inline bool chmax(T &x, T y) { return (y > x) ? x = y, true : false; }
template<typename T> inline bool chmin(T &x, T y) { return (y < x) ? x = y, true : false; }

ll sum(vector<ll> A) { ll res = 0; for (ll a: A) res += a; return res; }
ll max(vector<ll> A) { ll res = -INF; for (ll a: A) chmax(res, a); return res; }
ll min(vector<ll> A) { ll res = INF; for (ll a: A) chmin(res, a); return res; }

ll toint(string s) { ll res = 0; for (char c : s) { res *= 10; res += (c - '0'); } return res; }
int toint(char c) { return c - '0'; }
char tochar(int i) { return '0' + i; }

inline ll pow(int x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
inline ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

inline ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
inline ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }

template<typename T>
vector<T> accumulate(vector<T> A) {
    int N = A.size();
    vector<T> res(N);
    res[0] = A[0];
    rep(i, 1, N) res[i] = res[i-1] + A[i];
    return res;
}

ll N, Q;
vector<ll> A, acc;
unordered_set<ll> S, S2;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> Q;
    rep(_, 0, Q) {
        cin >> N;
        A.clear();
        acc.clear();
        S.clear();
        S2.clear();
        A.resize(N);
        rep(i, 0, N) cin >> A[i];
        rep(i, 0, N) S.insert(A[i]);

        acc = accumulate(A);
        acc.insert(acc.begin(), 0);
        rep(i, 0, N) {
            rep(j, i+2, N+1) {
                if (S.find(acc[j] - acc[i]) != S.end()) {
                    S2.insert(acc[j] - acc[i]);
                }
            }
        }

        ll ans = 0;
        rep(i, 0, N) {
            if (S2.find(A[i]) != S2.end()) {
                ans++;
            }
        }
        print(ans);
    }
    return 0;
}
