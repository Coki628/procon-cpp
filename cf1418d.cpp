/**
 * 参考：誰かのツイート
 * ・自力ならず？
 * ・まず読解が大変だった。ようは2回でゴミを掃ききる、
 * 　つまり二筆書きで区間の点を全部網羅するのが目標。
 * ・このためには、区間長で最大になるものを常に見れるようにしておけば、
 * 　全体 - 最大の区間長 でクエリに対応できる。
 * ・ツイートで、各区間の長さを管理、みたいな話を聞いたら解けた。
 * ・setで今存在する座標位置、multisetで各区間の長さを管理する。
 * ・後は適宜番兵を入れておいて、クエリを進めながら最大長さを常に取れるようにする。
 * ・注意点としては、番兵のINFは普段のINFだとオーバーフローがあるので適当に小さめに。
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
#define list2d(name, N, M, type, init) vector<vector<type>> name(N, vector<type>(M, init))
const ll INF = 1000000000000000;
const ll MOD = 1000000007;

void print(ld out) { cout << fixed << setprecision(15) << out << '\n'; }
void print(double out) { cout << fixed << setprecision(15) << out << '\n'; }
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
// 数字なら'0'、アルファベットなら'a'みたいに使い分ける
// int toint(char c) { return c - '0'; }
// char tochar(int i) { return '0' + i; }

inline ll pow(int x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
inline ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

inline ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
inline ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }
pll divmod(ll a, ll b) { ll d = a / b; ll m = a % b; return {d, m}; }

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }

ll N, Q;
vector<ll> P;
// se[i] := 座標iが今あるかどうか
set<ll> se;
// se[i] := 区間長iがあるかどうか(複数)
multiset<ll> se2;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> Q;
    P.resize(N);
    rep(i, 0, N) {
        cin >> P[i];
        se.insert(P[i]);
    }
    ll ans = max(P) - min(P);
    P.pb(-INF);
    P.pb(INF);
    se.insert(-INF);
    se.insert(INF);

    sort(P.begin(), P.end());
    rep(i, 0, N+1) {
        se2.insert(P[i+1]-P[i]);
    }
    se2.insert(0);
    se2.insert(0);

    // 最大の区間長を引く
    ans -= *next(se2.rbegin(), 2);
    print(ans);
    bool t;
    ll x, l, r;
    rep(i, 0, Q) {
        cin >> t >> x;

        if (t) {
            se.insert(x);
            l = x - *prev(se.find(x));
            r = *next(se.find(x)) - x;
            se2.erase(se2.find(l+r));
            se2.insert(l);
            se2.insert(r);
        } else {
            l = x - *prev(se.find(x));
            r = *next(se.find(x)) - x;
            se.erase(x);
            se2.insert(l+r);
            se2.erase(se2.find(l));
            se2.erase(se2.find(r));
        }
        // 何もない時は(max - min)できないので例外処理
        if (se.size() == 2) {
            print(0);
        } else {
            // 全体の長さ(max - min) - 最大の区間長
            ans = *next(se.rbegin()) - *next(se.begin()) - *next(se2.rbegin(), 2);
            print(ans);
        }
    }
    return 0;
}
