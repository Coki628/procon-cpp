/**
 * ・自力AC！
 * ・二分探索、ループを工夫
 * ・Aにできる操作「順番は変えないけど好きな場所から除ける」は、連続しない部分列、
 * 　Bにできる操作「順番は変えず、前後からのみ除ける」は、連続した部分列、と考えられる。
 * ・外側のループでBのどの範囲を使うかを固定して、内側でBの各文字とAの文字が一致するかを
 * 　並行してindexを進めながら判定していく、とすると、この判定処理はO(M(N+M))でできる。
 * ・何文字ならいけるか、は単調性があるので、試す文字数を二分探索できる。
 * ・両方合わせてO(M(N+M)logmin(N,M))、5000のN,Mなのでこれはpypyでも厳しいかと思って最初からC++でやってAC0.2秒。
 * ・判定処理ゴチャゴチャしてるからどうかなーと思ったけど、
 * 　サンプルだけ合わせて、ほぼノーデバッグでぶん投げて一発で通ったから嬉しい。
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
typedef vector<vector<ll>> vvl;
typedef vector<vector<int>> vvi;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define btoe(obj) (obj).begin(), (obj).end()
#define pb push_back
#define str to_string
#define mkp make_pair
const ll INF = 1e18;
const ll MOD = 1e9 + 7;
// void chmax(ll &a, ll b) { a = max(a, b); }
// void chmin(ll &a, ll b) { a = min(a, b); }
template<typename T> inline bool chmax(T &x, T y) {return (y > x) ? x = y, true : false;}
template<typename T> inline bool chmin(T &x, T y) {return (y < x) ? x = y, true : false;}

template<typename T>
void print(T out) {
    cout << out << '\n';
}

void print(ld out) {
    cout << fixed << setprecision(12) << out << '\n';
}

template<typename T1, typename T2>
void print(pair<T1, T2> out) {
    cout << out.first << ' ' << out.second << '\n';
}

template<typename T>
void print(vector<T> A) {
    rep(i, 0, A.size()) {
        cout << A[i];
        cout << (i == A.size()-1 ? '\n' : ' ');
    }
}

template<typename T>
void print(set<T> S) {
    vector<T> A(btoe(S));
    print(A);
}

ll sum(vector<ll> A) {
    ll res = 0;
    for (ll a: A) res += a;
    return res;
}

ll max(vector<ll> A) {
    ll res = -INF;
    for (ll a: A) chmax(res, a);
    return res;
}

ll min(vector<ll> A) {
    ll res = INF;
    for (ll a: A) chmin(res, a);
    return res;
}

ll sum(ll A[], int len) {
    ll res = 0;
    rep(i, 0, len) res += A[i];
    return res;
}

ll max(ll A[], int len) {
    ll res = -INF;
    rep(i, 0, len) chmax(res, A[i]);
    return res;
}

ll min(ll A[], int len) {
    ll res = INF;
    rep(i, 0, len) chmin(res, A[i]);
    return res;
}

ll toint(string s) {
    ll res = 0;
    for (char c : s) {
        res *= 10;
        res += (c - '0');
    }
    return res;
}

int toint(char c) {
    return c - '0';
}

ll pow(ll x, ll n, int mod) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) {
            res = (res * x) % mod;
        }
        x = (x * x) % mod;
        n >>= 1;
    }
    return res;
}

// 条件を満たす最大値を見つける二分探索
ll bisearch_max(ll mn, ll mx, function<bool(ll)> func) {

    ll ok = mn;
    ll ng = mx;
    while (ok+1 < ng) {
        ll mid = (ok+ng) / 2;
        if (func(mid)) {
            // 上を探しに行く
            ok = mid;
        } else {
            // 下を探しに行く
            ng = mid;
        }
    }
    return ok;
}

ll N, M;
vector<ll> A, B;

// m枚の山を作れるか
bool check(ll m) {
    // Bの何枚目から使うかのループ
    rep(i, 0, M-m+1) {
        // Bのi~i+m枚目について、Aに一致するカードがあるか見ていく
        ll k = 0;
        bool ok = true;
        rep(j, i, i+m) {
            // Aに一致するカードが見つかるまでAのindex(k)を進める
            while (k < N && B[j] != A[k]) {
                k++;
            }
            // 見つかったら、次回以降のためにその次にしておく
            k++;
            // Aが最後まで行って見つからなかったらこの回はNG
            if (k > N) {
                ok = false;
                break;
            }
        }
        // この回でうまくいったらOK、ダメならBの開始位置iを進めて繰り返す
        if (ok) {
            return true;
        }
    }
    // 最後まで見てダメならこの枚数は無理
    return false;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> M;
    A.resize(N);
    B.resize(M);
    rep(i, 0, N) cin >> A[i];
    rep(i, 0, M) cin >> B[i];

    ll res = bisearch_max(0, min(N, M)+1, check);
    print(res);
    return 0;
}
