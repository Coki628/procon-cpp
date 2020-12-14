/**
 * ・間に合わなかった。終了15分後くらいに仕上がって、システス終わって投げたら無事AC。。
 * ・再帰探索
 * ・全体を半分ずつに割っていく操作の性質上、全部愚直に見てもせいぜいlog回くらいだろうとなる。
 * 　こういうのは再帰で書くとすんなりできる、と思ったところで確か残り15分くらいしかなくて、
 * 　詰め切るの無理そうだけど頑張って書こう、ってやったらやっぱり間に合わなかった。。
 * ・ちょっと色々整理した版。
 * 　和を求めるパートを前に持ってきた方がスッキリだった。
 * 　あと目的の位置探すのはにぶたんしてたけど、log回くらいしかやらないんだから線形かけていいよね。
 * 　コードはupper_boundのがスッキリだけど、こっちのが考えなくても書けそうだし、
 * 　時間なかったんだし、こっちでよかったね。
 */

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using pii = pair<int, int>;
using vvl = vector<vector<ll>>;
using vvi = vector<vector<int>>;
using vvpll = vector<vector<pll>>;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define pb push_back
#define tostr to_string
#define ALL(A) A.begin(), A.end()
constexpr ll INF = LONG_LONG_MAX;
constexpr ll MOD = 1000000007;

template<typename T> vector<vector<T>> list2d(int N, int M, T init) { vector<vector<T>> res(N, vector<T>(M, init)); return res; }
template<typename T> vector<vector<vector<T>>> list3d(int N, int M, int L, T init) { vector<vector<vector<T>>> res(N, vector<vector<T>>(M, vector<T>(L, init))); return res; }

void print(ld out) { cout << fixed << setprecision(15) << out << '\n'; }
void print(double out) { cout << fixed << setprecision(15) << out << '\n'; }
template<typename T> void print(T out) { cout << out << '\n'; }
template<typename T1, typename T2> void print(pair<T1, T2> out) { cout << out.first << ' ' << out.second << '\n'; }
template<typename T> void print(vector<T> A) { rep(i, 0, A.size()) { cout << A[i]; cout << (i == A.size()-1 ? '\n' : ' '); } }
template<typename T> void print(set<T> S) { vector<T> A(S.begin(), S.end()); print(A); }

void Yes() { print("Yes"); }
void No() { print("No"); }
void YES() { print("YES"); }
void NO() { print("NO"); }

template<typename T> inline bool chmax(T &x, T y) { return (y > x) ? x = y, true : false; }
template<typename T> inline bool chmin(T &x, T y) { return (y < x) ? x = y, true : false; }

ll sum(vector<ll> A) { ll res = 0; for (ll a: A) res += a; return res; }
ll max(vector<ll> A) { ll res = -INF; for (ll a: A) chmax(res, a); return res; }
ll min(vector<ll> A) { ll res = INF; for (ll a: A) chmin(res, a); return res; }

ll toint(string s) { ll res = 0; for (char c : s) { res *= 10; res += (c - '0'); } return res; }
int toint(char num) { return num - '0'; }
char tochar(int num) { return '0' + num; }

inline ll pow(int x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
inline ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

inline ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
inline ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }
pll divmod(ll a, ll b) { ll d = a / b; ll m = a % b; return {d, m}; }

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }

void solve() {
    ll N, Q;
    cin >> N >> Q;
    vector<ll> A(N);
    rep(i, 0, N) cin >> A[i];

    sort(ALL(A));
    set<ll> se;
    auto rec = [&](auto&& f, ll l, ll r) -> void {
        ll sm = 0;
        rep(i, l, r) {
            sm += A[i];
        }
        se.insert(sm);

        ll mid = (A[l]+A[r-1]) / 2;
        ll mi = r;
        rep(i, l, r) {
            if (A[i] > mid) {
                mi = i;
                break;
            }
        }
        // ll mi = upper_bound(ALL(A), mid) - A.begin();
        if (mi != r) {
            f(f, l, mi);
            f(f, mi, r);
        }
    };
    rec(rec, 0, N);

    rep(_, 0, Q) {
        ll q;
        cin >> q;
        if (se.count(q)) {
            Yes();
        } else {
            No();
        }
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while(T--) solve();

    return 0;
}
