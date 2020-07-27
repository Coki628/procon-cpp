/**
 * ・青diff600点自力AC！嬉しい。
 * ・(連続でない)部分文字列
 * ・一見、全体に対する前計算が必要そうな量にも見えるが、各クエリにO(N)かけていい。
 * 　以下、各クエリ内での処理。
 * ・先に後ろから「あるDからx文字以内にあるMの数」を前計算しておくと、
 * 　前から見て行った時に、あるDが使えなくなった時にDMペアが何個使えなくなるか、
 * 　がすぐに分かるようになる。
 * ・あとはD,M,Cの出現に従って、Dの数,DMの数,DMCの数を加減させていけばいい。
 * ・多分、logを落とすためなんだろうけど制約がきつい。(100万のN*75クエリ)
 * 　pypyTLEでこっちで書き直してAC0.96秒。
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

void print(ld out) { cout << fixed << setprecision(15) << out << '\n'; }
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

ll N, Q, q;
string S;

ll f(ll x) {
    // DM[i] := 位置iにあるDからx文字以内にあるMの数
    vector<ll> DM(N);
    ll mcnt = 0;
    rrep(i, N-1, -1) {
        if (i+x < N) {
            if (S[i+x] == 'M') {
                mcnt--;
            }
        }
        if (S[i] == 'M') {
            mcnt++;
        } else if (S[i] == 'D') {
            DM[i] = mcnt;
        }
    }

    ll dcnt = 0, dmcnt = 0, dmccnt = 0;
    rep(i, 0, N) {
        if (i-x >= 0) {
            if (S[i-x] == 'D') {
                dcnt--;
                dmcnt -= DM[i-x];
            }
        }
        if (S[i] == 'D') {
            dcnt++;
        } else if (S[i] == 'M') {
            dmcnt += dcnt;
        } else if (S[i] == 'C') {
            dmccnt += dmcnt;
        }
    }
    return dmccnt;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    cin >> S;
    cin >> Q;
    rep(_, 0, Q) {
        cin >> q;
        ll ans = f(q);
        print(ans);
    }
    return 0;
}
