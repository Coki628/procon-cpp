/**
 * ・pypyTLEしたのでこっちでAC。
 * 　でも結局その後pypyでもACしたんだけどね。
 * ・DP、復元、ビットの管理、貪欲
 * ・色々詳細はpythonの方のコメントで。
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

const vector<ll> B = {
    0b1110111, 0b0010010, 0b1011101, 0b1011011, 0b0111010, 0b1101011, 0b1101111, 0b1010010, 0b1111111, 0b1111011
};
ll N, K;
string s;
vector<ll> A;
ll dp[2007][2007];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> K;
    A.resize(N);
    rep(i, 0, N) {
        cin >> s;
        reverse(s.begin(), s.end());
        rep(j, 0, 7) {
            if (s[j] == '1') {
                A[i] |= 1 << j;
            }
        }
    }

    reverse(A.begin(), A.end());
    dp[0][0] = 1;
    ll ab, cnt;
    bool ng;
    rep(i, 0, N) {
        rep(j, 0, K+1) {
            if (!dp[i][j]) continue;
            cnt = 0;
            ng = false;
            rep(k, 0, 10) {
                ab = A[i] & B[k];
                cnt = popcount(B[k] ^ ab);
                ng = (A[i] ^ ab) > 0;
                if (!ng && j+cnt <= K) {
                    dp[i+1][j+cnt] |= 1 << k;
                }
            }
        }
    }

    if (!dp[N][K]) {
        print(-1);
        return 0;
    }

    cnt = K;
    string ans;
    ll num, need;
    rrep(i, N, 0) {
        rrep(j, 9, -1) {
            if ((dp[i][cnt]>>j) & 1) {
                num = j;
                break;
            }
        }
        ans += tochar(num);
        need = popcount(B[num]) - popcount(A[i-1]);
        cnt -= need;
    }
    print(ans);
    return 0;
}
