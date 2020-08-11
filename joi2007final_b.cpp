/**
 * ・ロリハの動作確認
 * ・まあTLEなんだけどね。手元で試したらなんか答えずれるし、どうなんだろー。。
 */

#pragma GCC optimize("Ofast")
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

struct RollingHash {

    const ll BASE = 1234;
    const ll MASK30 = (1LL << 30) - 1;
    const ll MASK31 = (1LL << 31) - 1;
    const ll MASK61 = (1LL << 61) - 1;
    const ll MOD = (1LL << 61) - 1;
    const ll POSITIVIZER = MOD * 4;
    ll n;
    vector<ll> hash, pow;

    // 文字列Sの部分文字列のハッシュを構築する：O(N) 
    RollingHash(string S) {
        n = S.size();
        hash.assign(n+1, 0);
        pow.assign(n+1, 1);

        rep(i, 0, n) {
            hash[i+1] = calc_mod(mul(hash[i], BASE) + S[i]);
            pow[i+1] = calc_mod(mul(pow[i], BASE));
        }
    }

    // x mod 2^61-1 を返す
    ll calc_mod(ll x) {
        ll xu = x >> 61;
        ll xd = x & MASK61;
        x = xu + xd;
        if (x >= MOD) {
            x -= MASK61;
        }
        return x;
    }

    // a*b mod 2^61-1 を返す
    ll mul(ll a, ll b) {
        ll au = a >> 31;
        ll ad = a & MASK31;
        ll bu = b >> 31;
        ll bd = b & MASK31;
        ll mid = ad * bu + au * bd;
        ll midu = mid >> 30;
        ll midd = mid & MASK30;
        return calc_mod(au * bu * 2 + midu + (midd << 31) + ad * bd);
    }

    // S[l,r)のハッシュ値を返す：O(1)
    ll get_hash(ll l, ll r) {
        return calc_mod(hash[r] + POSITIVIZER - mul(hash[l], pow[r - l]));
    }

    // ハッシュ値h1と長さlen2のハッシュ値h2を結合する：O(1)
    ll merge(ll h1, ll h2, ll len2) {
        return calc_mod(mul(h1, pow[len2]) + h2);
    }

    // S[l1:r2]とS[l2:r2]の最長共通接頭辞(Longest Common Prefix)の長さを求める：O(log|string|)
    ll get_lcp(ll l1, ll r1, ll l2, ll r2) {
        ll ng = min(r1 - l1, r2 - l2) + 1;
        ll ok = 0;
        while (abs(ok - ng) > 1) {
            ll mid = (ok + ng) / 2;
            if (get_hash(l1, l1 + mid) == get_hash(l2, l2 + mid)) {
                ok = mid;
            } else {
                ng = mid;
            }
        }
        return ok;
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    string S, T;
    ll N, M, NM;
    cin >> S;
    N = S.size();
    cin >> T;
    M = T.size();
    NM = N + M;

    RollingHash rh(S+T);
    ll ans = 0;
    rep(i, 0, N) {
        rep(j, N, NM) {
            chmax(ans, rh.get_lcp(i, N, j, NM));
        }
    }
    print(ans);
    return 0;
}
