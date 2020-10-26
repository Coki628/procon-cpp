/**
 * ・ハックからのメモリ改善。。なんとかAC。
 * ・llをintにしたり、キーをペアから2次元mapにしてみたり、unordered_mapにしてみたりvectorにしてみたり
 * 　色々試したけどダメで、結局、1度しか出現しなかったキーは実際使うことがないので、
 * 　1回目だけ普通の2次元vectorに保持、2回目以降が来たらmapにキーを追加する方針にしたら効いた。
 * ・でも時間も1.64秒でかなり遅くなったし、ちゃんと想定解っぽい方面に辿り着くべきだったな。。
 * ・今回分かったのは、キーが450万個くらいあるmapでvector(空でも)持つと256MBはMLEする。
 * 　なんならmapじゃなくて2次元vectorの下の3次元目に空vectorでも450万はダメ。ってことか。。
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
const ll INF = LONG_LONG_MAX;
const ll MOD = 1000000007;

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

ll N;
vector<ll> A;
map<pii, vector<int>> D;

void solve() {
    A.clear();
    D.clear();
    cin >> N;
    A.resize(N);
    list2d(visited, N+1, N+1, int, -1);
    rep(i, 0, N) cin >> A[i];

    rep(i, 0, N) {
        rep(j, i+1, N) {
            if (visited[A[i]][A[j]] == -1) {
                visited[A[i]][A[j]] = j;
            } else {
                D[{A[i], A[j]}].pb(j);
            }
        }
    }
    rep(i, 0, N+1) {
        rep(j, 0, N+1) {
            // 2回目以降が存在したら1回目も入れておく
            if (D.find({i, j}) != D.end()) {
                D[{i, j}].pb(visited[i][j]);
            }
        }
    }
    for (auto &v : D) {
        sort(v.second.begin(), v.second.end());
    }
    ll ans = 0;
    rep(k, 0, N) {
        rep(l, k+1, N) {
            // ここでも存在確認してから処理(直接やると全部のキーが生成されて結局やられる)
            if (D.find({A[k], A[l]}) != D.end()) {
                auto &v = D[{A[k], A[l]}];
                ll idx = lower_bound(v.begin(), v.end(), k) - v.begin();
                ans += idx;
            }
        }
    }
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while(T--) solve();

    return 0;
}
