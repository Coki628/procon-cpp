/**
 * 参考：https://codeforces.com/blog/entry/66586
 * ・自力ならず。
 * ・setをうまく使う。
 * ・C++のsetなら、追加と削除に加えて、ある位置から順番に前後に進むこともできる。
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

ll N, K;
vector<pll> A;
set<ll> S;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> K;
    A.resize(N);
    ll a;
    rep(i, 0, N) {
        cin >> a;
        S.insert(i);
        A[i] = mkp(a, i);
    }
    sort(A.rbegin(), A.rend());

    ll idx, cnt;
    int turn = 0;
    string ans(N, '0');
    vector<ll> tmp;
    rep(i, 0, N) {
        idx = A[i].second;
        auto itr = S.find(idx);
        // このidx位置がもう使われていたらスキップ
        if (itr == S.end()) continue;
        ans[idx] = tochar(turn + 1);
        tmp.clear();
        // 今回使った要素を覚えておく
        tmp.pb(idx);
        // 要素をK個先まで使う
        auto itr2 = itr;
        cnt = 1;
        while (cnt <= K) {
            itr2++;
            if (itr2 == S.end()) break;
            idx = *itr2;
            ans[idx] = tochar(turn + 1);
            tmp.pb(idx);
            cnt++;  
        }
        // 要素をK個前まで使う
        itr2 = itr;
        cnt = 1;
        while (cnt <= K) {
            if (itr2 == S.begin()) break;
            itr2--;
            idx = *itr2;
            ans[idx] = tochar(turn + 1);
            tmp.pb(idx);
            cnt++;
        }
        // 使った要素をsetから削除
        for (ll idx : tmp) S.erase(idx);
        turn = 1 - turn;
    }
    print(ans);
    return 0;
}
