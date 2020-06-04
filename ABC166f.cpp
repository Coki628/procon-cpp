/**
 * 参考：https://www.hamayanhamayan.com/entry/2020/05/03/224516
 * ・別解。
 * ・枝狩り全探索、再帰探索、バックトラック
 * ・基本は数が少ない方を増やす方針で状態遷移させる。
 * 　ABC[cur1] == ABC[cur2] の時だけ2つの遷移になるが、枝刈りが十分に効いて高速に通る。
 * ・これだと確かに貪欲条件詰めなくてもいいから通しやすそうだけど、
 * 　これが最悪計算量が2^Nはないにしても、全然でかくならないのはなんか非自明だよなー。。
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

ll N;
vector<pll> S;
vector<ll> ABC(3);
vector<char> ans;

bool rec() {
    ll i = ans.size();
    if (i == N) return true;
    ll cur1 = S[i].first;
    ll cur2 = S[i].second;
    if (ABC[cur1] == 0 && ABC[cur2] == 0) return false;
    if (ABC[cur1] <= ABC[cur2]) {
        ans.pb(cur1+65);
        ABC[cur1]++;
        ABC[cur2]--;
        if (rec()) {
            return true;
        }
        ans.pop_back();
        ABC[cur1]--;
        ABC[cur2]++;
    } 
    if (ABC[cur1] >= ABC[cur2]) {
        ans.pb(cur2+65);
        ABC[cur2]++;
        ABC[cur1]--;
        if (rec()) {
            return true;
        }
        ans.pop_back();
        ABC[cur2]--;
        ABC[cur1]++;
    }
    return false;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> ABC[0] >> ABC[1] >> ABC[2];
    S.resize(N);
    string s;
    rep(i, 0, N) {
        cin >> s;
        S[i].first = s[0] - 65;
        S[i].second = s[1] - 65;
    }

    if (rec()) {
        print("Yes");
        rep(i, 0, N) print(ans[i]);
    } else {
        print("No");
    }
    return 0;
}
