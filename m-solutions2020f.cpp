/**
 * 参考：https://img.atcoder.jp/m-solutions2020/editorial.pdf
 * ・自力ならず。
 * ・3^Nの全列挙(再帰探索)、前計算
 * ・重要な考察として、集落のある場所以外に路線を引くのは無駄ということ。
 * 　これはなんとなく1次元の時の中央値の感覚でそうなんじゃないかって気はしたものの、
 * 　全然確証は持てず。結果的に、2次元でもこれが通用するみたい。
 * ・で、ここが分かったら、ある集落の場所に路線を
 * 　横に引く、縦に引く、引かないの3通りを全列挙で試せる。
 * ・3通り全列挙はビットっぽくやるのだるそうだったので再帰でやった。
 * ・N箇所について出揃ったところで、check関数で値を確認。
 * 　ここでN^2かけるとさすがにC++でも無理めなので前計算しておく。具体的には、
 * 　prevx[S][i] := 集合Sの場所について縦(横)線を入れた時の、集落iへの最短距離
 * 　みたいなやつを縦横両方について事前に押さえておく。
 * ・前計算しても計算量が3^N*N=2億1500万くらいあるので、迷わずC++で。無事AC1.06秒。(制約3秒)
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
ll prevx[1<<15][15];
ll prevy[1<<15][15];
vvl XY;
vector<ll> ans;

void check(vector<ll> &li) {
    ll k = 0;
    ll S1 = 0, S2 = 0;
    rep(i, 0, N) {
        // 縦線を入れる
        if (li[i] == 1) {
            S1 |= 1LL<<i;
            k++;
        // 横線を入れる
        } else if (li[i] == 2) {
            S2 |= 1LL<<i;
            k++;
        }
    }
    ll cnt = 0;
    rep(i, 0, N) {
        // 前計算の値を使って、縦横近い方を取る
        cnt += min(prevx[S1][i], prevy[S2][i]) * XY[i][2];
    }
    // k本線を引いた場合の答えに使う
    chmin(ans[k], cnt);
    return;
}

void rec(vector<ll> &li) {
    // N個の集落全てについて3通りどうするか決まったら、値がどうなるか確認
    if ((int)li.size() == N) {
        check(li);
        return;
    }
    // 集落iの場所に路線を横に引く、縦に引く、引かないの3通りを全部やる
    rep(i, 0, 3) {
        li.pb(i);
        rec(li);
        li.pop_back();
    }
    return;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    XY.resize(N);
    ans.assign(N+1, INF);
    ll x, y, p;
    rep(i, 0, N) {
        cin >> x >> y >> p;
        XY[i] = {x, y, p};
    }

    // prevx[S][i] := 集合Sの場所について縦線を入れた時の、集落iへの最短距離
    // prevy[S][i] := 集合Sの場所について横線を入れた時の、集落iへの最短距離
    rep(S, 0, 1<<N) {
        rep(i, 0, N) {   
            prevx[S][i] = abs(XY[i][0]);
            prevy[S][i] = abs(XY[i][1]);
        }
    }
    rep(S, 0, 1<<N) {
        rep(i, 0, N) {
            rep(j, 0, N) {
                // 集落jが集合に含まれていたら、集落iとの距離を確認
                if (S>>j & 1) {
                    chmin(prevx[S][i], abs(XY[i][0] - XY[j][0]));
                    chmin(prevy[S][i], abs(XY[i][1] - XY[j][1]));
                }
            }
        }
    }

    vector<ll> li;
    rec(li);
    rep(i, 0, N+1) {
        print(ans[i]);
    }
    return 0;
}
