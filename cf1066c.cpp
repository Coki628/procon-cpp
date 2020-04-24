/**
 * ・pypyTLEなのでこっちでAC。
 * ・区間加算BIT
 * ・絶対もっとすんなり賢く方法あるんだろうなー、って思いながらも
 * 　全体に1足す、を高速にしたかったので区間加算BITで殴った。
 * ・左に詰める時は全体のindexを1右にずらす。
 * ・これができたら後は各IDのindexを見るだけになる。
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

struct BIT2 {

    ll N;
    vector<ll> data0, data1;

    BIT2() {};

    BIT2(ll N) {
        resize(N);
    }

    void resize(ll n) {
        N = ++n;
        data0.resize(N);
        data1.resize(N);
    }

    void _add(vector<ll> &data, ll k, ll x) {
        k++;
        while (k < N) {
            data[k] += x;
            k += k & -k;
        }
    }

    ll _get(vector<ll> &data, ll k) {
        k++;
        ll s = 0;
        while (k) {
            s += data[k];
            k -= k & -k;
        }
        return s;
    }

    void add(ll l, ll r, ll x) {
        _add(data0, l, -x*(l-1));
        _add(data0, r, x*(r-1));
        _add(data1, l, x);
        _add(data1, r, -x);
    }

    void add(ll i, ll x) {
        add(i, i+1, x);
    }

    ll query(ll l, ll r) {
        return _get(data1, r-1) * (r-1) + _get(data0, r-1) - _get(data1, l-1) * (l-1) - _get(data0, l-1);
    }

    ll get(ll i) {
        return query(i, i+1);
    }

    void update(ll i, ll x) {
        add(i, i+1, x - get(i));
    }
};

const ll MAX = 1e5 * 2;
ll Q;
BIT2 bit(MAX+1);

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> Q;
    char lr;
    ll id, idx, ans;
    ll n = 0;
    rep(_, 0, Q) {
        cin >> lr;
        cin >> id;
        
        if (lr == '?') {
            idx = bit.get(id);
            ans = min(idx, n-idx-1);
            print(ans);
            continue;
        }
        if (lr == 'L') {
            bit.add(0, MAX+1, 1);
            bit.update(id, 0);
        } else {
            bit.update(id, n);
        }
        n++;
    }
    return 0;
}
