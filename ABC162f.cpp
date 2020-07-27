/**
 * ・ちょっと思い立ったので試してみた。
 * ・メモ化再帰、枝刈り
 * ・この先が足りるかどうかを適切にチェックしていけば、取りうる状態数は多くない。
 * 　無理と確定したら枝刈りする。
 * ・公式解より直感的っぽいこの方針でも解けないかなーと思ってやってみた。。
 * ・さすがに多少は分岐があるからか、全探索はTLE。メモ化したらAC。
 * ・新たな知見として、unordered_mapはpairをキーにできない。mapはできるのにね。
 * 　(Boost使えばできるらしい)
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

ll N;
vector<ll> A;
map<pll, ll> memo[2];

ll rec(ll i, ll j, bool f) {
    if (memo[f].find({i, j}) != memo[f].end()) {
        return memo[f][{i, j}];
    }
    // 終了時
    if (i == N) {
        // ぴったりfloor(N, 2)ならOK
        if (j == N/2) {
            return 0;
        } else {
            return -INF;
        }
    }
    // この先で選べる最大数
    ll k = ceil(N-i, 2);
    // 今までに選んだ数と合わせて足りなければこの道はNG確定
    if (j+k < N/2) {
        return -INF;
    }
    ll res = -INF;
    chmax(res, rec(i+1, j, 0));
    if (!f) {
        chmax(res, rec(i+1, j+1, 1) + A[i]);
    }
    memo[f][{i, j}] = res;
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    rep(i, 0, N) cin >> A[i];

    ll ans = rec(0, 0, 0);
    print(ans);
    return 0;
}
