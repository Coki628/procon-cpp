/**
 * 参考：https://drken1215.hatenablog.com/entry/2020/11/29/210400
 * ・自力ならず。。
 * ・累積XOR、鳩の巣原理
 * ・前計算累積して愚直N^3すればよさそうなのは見えたけど、制約10万で全然無理。
 * ・と思ったら、実は100以上くらいは全部1操作で完了できるようだ。
 * 　というのも、今回の操作は最大ビットが同じ要素3つが並んでいると、
 * 　後ろ2つに操作することで必ず条件を達成できる。(最大ビットが消えて前が絶対でかくなるので)
 * ・元の数列は広義単調増加が保証されているので、制約のAの最大値10^9と照らし合わせると、
 * 　30ビットくらい*2より要素数が多いと、どうしたって3つ同じのが並ぶ場所が出てくる。(鳩の巣原理)
 * ・よって雑に考えてもN>100くらいあれば十分で、操作1回確定。
 * 　これより小さいやつは愚直N^3が通るので、やる。
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

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N;
    cin >> N;
    vector<ll> A(N);
    rep(i, 0, N) cin >> A[i];

    if (N > 100) {
        print(1);
        return 0;
    }

    vector<ll> acc(N+1);
    rep(i, 0, N) {
        acc[i+1] = acc[i] ^ A[i];
    }

    ll ans = INF;
    rep(i, 1, N) {
        rep(j, 0, i) {
            rep(k, i+1, N+1) {
                if ((acc[i]^acc[j]) > (acc[k]^acc[i])) {
                    chmin(ans, (i-j-1)+(k-i-1));
                }
            }
        }
    }
    if (ans == INF) {
        print(-1);
    } else {
        print(ans);
    }
    return 0;
}
