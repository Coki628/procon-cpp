/**
 * 参考：各種ツイート
 * 　　　https://atcoder.jp/contests/abc175/editorial/53
 * ・自力ならず。
 * ・周期、サイクル
 * ・きつい。これ水diffは全人類やばいだろ。
 * ・まず場合分けとか周期の地獄をいくらか楽にするために必要な気づきがある。
 * ・今回のマスの移動先は順列なので、全てのマスはサイクルの中に含まれていて、
 * 　サイクルの外側にあって2度と戻ってこれない、みたいな場所はないと思っていい。(多分)
 * ・するとどこをスタートにするにせよ、1つずれても結果的に全部帳尻が合うので、
 * 　「そのマスでなく移動先のマスのスコアを足す」っていうめんどいのを
 * 　そのマスのスコアを足すと考えても大丈夫になる。
 * ・全てがサイクル内にあると分かったら、そのサイクルを配列にして
 * 　サイクル長でMOD取りしてもうまくいくので、普通の配列とループで処理できるようになった。
 * ・ここまで来ると、後は各サイクルについて、Kとサイクル長の関係と
 * 　1周回った時に増えるか増えないかで場合分けを丁寧に考えれば解ける。
 * ・同じサイクルについて、出発点が違うだけなのに毎回DFSするの絶対無駄だなぁって
 * 　思いながらやったけど、下手にサイクル毎にまとめて、とか考えたら余計頭壊れそうな気がしたので、
 * 　愚直にN箇所のスタート地点を全部やった。
 * ・N<=5000の2重ループってだけでもきつめなのに毎回再帰とか回したら絶対pypy死ぬと思って
 * 　最初からC++でやった。無事AC0.58秒。
 * ・ちなみに自力は周期だと脳が破壊されそうだったのでダブリングを考えた。結果、無理だったんだけど。
 * 　そっちで通してる人もいたけど、やり方みると周期よりきつい感じがしたのでこっちで通した。
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

ll N, K;
vector<ll> P, C, A;
bool visited[5007];

bool rec(ll cur) {
    if (visited[cur]) {
        return true;
    }
    visited[cur] = true;
    ll nxt = P[cur];
    if (rec(nxt)) {
        A.pb(cur);
        return true;
    }
    return false;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> K;
    P.resize(N);
    C.resize(N);
    rep(i, 0, N) {
        cin >> P[i];
        P[i]--;
    }
    rep(i, 0, N) cin >> C[i];

    ll M, cnt, mx, ans = -INF, d, m;
    rep(i, 0, N) {
        memset(visited, 0, sizeof(visited));
        A.clear();
        // DFSでサイクルの順序を保持した配列Aを作る
        rec(i);
        reverse(A.begin(), A.end());
        M = A.size();
        // 合計と最大値
        cnt = 0;
        mx = -INF;
        // Kがサイクル長以下
        if (K <= M) {
            // Kまで見るだけ
            rep(i, 0, K) {
                cnt += C[A[i]];
                chmax(mx, cnt);
            }
            chmax(ans, mx);
        // Kがサイクル長より大きい
        } else {
            // 最初の1周
            rep(i, 0, M) {
                cnt += C[A[i]];
                chmax(mx, cnt);
            }
            // 1周回って増えないなら最初だけでいい
            if (cnt <= 0) {
                chmax(ans, mx);
            // 増えるなら最後の1周+余りをやる
            } else {
                tie(d, m) = divmod(K, M);
                d--;
                cnt *= d;
                rep(i, 0, M+m) {
                    cnt += C[A[i%M]];
                    chmax(mx, cnt);
                }
            }
            chmax(ans, mx);
        }
    }
    print(ans);
    return 0;
}
