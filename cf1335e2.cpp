/**
 * 参考：https://twitter.com/pazzle1230/status/1249738896579035136
 * 　　　https://codeforces.com/contest/1335/submission/76551239
 * 　　　https://twitter.com/titia_til/status/1249739414537830403
 * ・計算量的にpypyでもきついだろー、とこっちで。
 * ・種類毎に累積和、左端決め打ちで右端を二分探索、枝刈り
 * ・似たような発想はちょっと考えたけど、内側のbを決めるループを合わせると、
 * 　計算量が200*20万*200で死ぬと思ってやらなかった。。
 * ・実際そのままじゃ無理なんだけど、その左端と同じ数を取れる最大の右端、を取りに行く前に、
 * 　左端が変わっても取れる数が同じだった場合、出てくる右端は同じだし左端は狭まってるしで何も得をしない。
 * 　このことを踏まえると、前回と同じ数だった左端はやる必要がない。
 * ・1つめと2つめのループを入れ替えて、その枝刈りをやったら無事AC0.7秒。
 * ・計算量は20万*200=4000万に枝刈りしたlogと200が乗る。やっぱ速いね。
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

typedef unordered_map<ll, int> mli;
typedef unordered_map<int, ll> mil;
pair<mli, mil> compress(unordered_set<ll> S) {
    mli zipped;
    mil unzipped;
    vector<ll> A(S.begin(), S.end());
    sort(A.begin(), A.end());
    rep(i, 0, A.size()) {
        zipped[A[i]] = i;
        unzipped[i] = A[i];
    }
    return mkp(zipped, unzipped);
}

template<typename T>
vector<T> accumulate(vector<T> A) {
	int N = A.size();
	vector<T> res(N);
	res[0] = A[0];
	rep(i, 1, N) res[i] = res[i-1] + A[i];
	return res;
}

ll bisearch_max(ll mn, ll mx, function<bool(ll)> func) {
    ll ok = mn;
    ll ng = mx;
    while (ok+1 < ng) {
        ll mid = (ok+ng) / 2;
        if (func(mid)) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    return ok;
}

ll N, Q;
vector<ll> A;
vvi acc;
unordered_set<ll> S;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> Q;
    rep(_, 0, Q) {
        cin >> N;
        A.resize(N+1);
        S.clear();
        rep(i, 1, N+1) {
            cin >> A[i];
            A[i]--;
            S.insert(A[i]);
        }

        auto cp = compress(S);
        ll M = cp.first.size();
        rep(i, 1, N+1) A[i] = cp.first[A[i]];

        acc.clear();
        acc.resize(M);
        rep(a, 0, M) acc[a].resize(N+1);
        rep(i, 1, N+1) acc[A[i]][i] = 1;
        rep(a, 0, M) acc[a] = accumulate(acc[a]);

        int ans = 0;
        int prevx = -1;
        int x, y, r;
        rep(a, 0, M) {
            rep(l, 0, N+1) {
                x = acc[a][l];
                if (x == prevx) continue;
                prevx = x;
                r = bisearch_max(-1, N+1, [a, x](ll m) { return acc[a][N] - acc[a][m] >= x; });
                if (l > r) break;
                y = 0;
                rep(b, 0, M) {
                    chmax(y, acc[b][r] - acc[b][l]);
                }
                chmax(ans, x*2 + y);
            }
        }
        print(ans);
    }
    return 0;
}
