/**
 * ・なんとか自力AC！
 * ・貪欲考察頑張る。公式解とはちょっと違う方法？
 * ・後ろからやる。すると、その時点でその位置を0にできない時は、
 * 　それ以上前を操作してもその位置が動かせないのでNG。
 * ・で、どういう時に0にできるかを考えると、A[i] == iだったらよさそうだけど、これだけじゃダメ。
 * 　実はA[i]がmod iで0だったらいくら多くてもOK。というのも、後ろから消していってる途中で、
 * 　あるA[i]がiちょうどになったら、その時にA[i]を1回空にすればよく、
 * 　そう考えると最終的に0になるには、mod iで0だったらOKと分かる。
 * ・都度A[i]を空にする操作を陽に行うと遅いので、後ろからの値がどのくらい積まれるかは
 * 　管理しておいて、自分の番になったらまとめて処理する感じ。
 * ・これで最初までやりきれればOKだし、途中で0にならないところがあったらNG。
 * ・自分より前にA[i]/iずつ足す操作は工夫すればもっとうまくやれそうだったけど、
 * 　そこに思考リソース割きたくなかったし区間加算BITで殴った。
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

template<typename T> vector<vector<T>> list2d(int N, int M, T init) {
    vector<vector<T>> res(N, vector<T>(M, init));
    return res;
}
template<typename T> vector<vector<vector<T>>> list3d(int N, int M, int L, T init) {
    vector<vector<vector<T>>> res(N, vector<vector<T>>(M, vector<T>(L, init)));
    return res;
}

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

// 区間加算BIT(区間加算・区間和取得)
template<typename T>
struct BIT2 {

    ll N;
    vector<T> data0, data1;

    BIT2() {};

    BIT2(int N) {
        resize(N);
    }

    void resize(int n) {
        // 添字0が使えないので、内部的には全て1-indexedとして扱う
        N = ++n;
        data0.resize(N);
        data1.resize(N);
    }

    void _add(vector<T> &data, int k, T x) {
        k++;
        while (k < N) {
            data[k] += x;
            k += k & -k;
        }
    }

    T _get(vector<T> &data, int k) {
        k++;
        T s = 0;
        while (k) {
            s += data[k];
            k -= k & -k;
        }
        return s;
    }

    // 区間[l,r)に値xを加算
    void add(int l, int r, T x) {
        _add(data0, l, -x*(l-1));
        _add(data0, r, x*(r-1));
        _add(data1, l, x);
        _add(data1, r, -x);
    }

    // 1点加算
    void add(int i, T x) {
        add(i, i+1, x);
    }

    // 区間[l,r)の和を取得
    T query(int l, int r) {
        return _get(data1, r-1) * (r-1) + _get(data0, r-1) - _get(data1, l-1) * (l-1) - _get(data0, l-1);
    }

    // 1点取得
    T get(int i) {
        return query(i, i+1);
    }

    // 1点更新
    void update(int i, T x) {
        add(i, i+1, x - get(i));
    }

    T operator[](int i) {
        return get(i);
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N;
    cin >> N;
    BIT2<ll> bit(N+1);
    rep(i, 1, N+1) {
        ll a;
        cin >> a;
        bit.add(i, a);
    }

    rrep(i, N, 1) {
        if (bit[i] == 0) continue;
        if (bit[i] % i == 0) {
            bit.add(0, i, bit[i] / i);
            bit.update(i, 0);
        } else {
            No();
            return 0;
        }
    }    
    Yes();
    return 0;
}
