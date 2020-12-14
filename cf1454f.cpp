/**
 * ・なんとか自力AC。でもなんとなく解法ネタバレは食らってたので微妙。。時間かかったし。
 * ・区間系、セグ木上の二分探索
 * ・セグ木にぶたんをふんだんに使う。2点固定する必要があるので、とりあえず左の点を固定して、
 * 　うまくいく右の点があるかをチェック、を全部のiに対してやる。
 * ・左の点を固定すると、求めるべきぴったりにするxは定まる。その点より右側で、
 * 　区間最小と最大がxぴったりになるのを求めるために、未満と以下両方でにぶたんして
 * 　その差分を取る、みたいなことをやる。
 * ・これで最小最大それぞれのxぴったりになる範囲が分かるので、これがうまく重なっていて、
 * 　未満=以下だった時はそれがxぴったりなのかをチェックして、ここまで来れたらOKにする。
 * ・右の点の位置は、それぞれの区間の右端のうち小さい方にした。
 * 　どっちの区間のが前にあるか分からなくても、多分ここなら確実に重なってる、はず。。
 * ・pypyTLEでC++で無事AC0.90秒。やっぱセグ木にぶたんするとまあまあ重いな。。
 * 　特にこどふぉ環境だと厳しめに感じる。。
 * ・にぶたんの比較関数を毎回生成してるっぽいのが重いのかなーって先に作っておいたけどほぼ変わらず。
 * ・いやーでも解法なんとなく聞いてたにも関わらず時間かかり過ぎた。
 * 　これじゃEより優先してこっちに取り組んでたとしても時間内には解けなかった可能性が高いな。。
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

template<typename Monoid>
struct SegTree {
    using F = function<Monoid(Monoid, Monoid)>;
    
    int sz;
    vector<Monoid> seg;
    
    const F f;
    const Monoid M1;
    
    SegTree(int n, const F f, const Monoid &M1) : f(f), M1(M1) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.assign(2 * sz, M1);
    }

    SegTree(const F f, const Monoid &M1) : f(f), M1(M1) {}

    void resize(int n) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.resize(2 * sz, M1);
    }

    void clear() {
        seg.clear();
    }
    
    void set(int k, const Monoid &x) {
        seg[k+sz] = x;
    }
    
    void build() {
        for(int k = sz - 1; k > 0; k--) {
            seg[k] = f(seg[2*k], seg[2*k+1]);
        }
    }

    void update(int k, const Monoid &x) {
        k += sz;
        seg[k] = x;
        while(k >>= 1) {
            seg[k] = f(seg[2*k], seg[2*k+1]);
        }
    }
 
    Monoid query(int a, int b) {
        Monoid L = M1, R = M1;
        for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
            if(a & 1) L = f(L, seg[a++]);
            if(b & 1) R = f(seg[--b], R);
        }
        return f(L, R);
    }

    Monoid operator[](const int &k) const {
        return seg[k+sz];
    }

    Monoid all() {
        return seg[1];
    }

    // 区間[l,r]で左から最初にxに対して比較の条件を満たすような値が出現する位置
    template<typename G> ll bisearch_fore(ll l, ll r, ll x, const G &compare) {
        ll ok = r + 1;
        ll ng = l - 1;
        while (ng+1 < ok) {
            ll mid = (ok+ng) / 2;
            if (compare(query(l, mid+1), x)) {
                ok = mid;
            } else {
                ng = mid;
            }
        }
        if (ok != r + 1) {
            return ok;
        } else {
            return -1;
        }
    }

    // 区間[l,r]で右から最初にxに対して比較の条件を満たすような値が出現する位置
    template<typename G> ll bisearch_back(ll l, ll r, ll x, const G &compare) {
        ll ok = l - 1;
        ll ng = r + 1;
        while (ok+1 < ng) {
            ll mid = (ok+ng) / 2;
            if (compare(query(mid, r+1), x)) {
                ok = mid;
            } else {
                ng = mid;
            }
        }
        if (ok != l - 1) {
            return ok;
        } else {
            return -1;
        }
    }
};

auto le = less_equal<ll>();
auto lt = less<ll>();
auto gt = greater<ll>();
auto ge = greater_equal<ll>();

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    rep(i, 0, N) cin >> A[i];

    SegTree<ll> segmx(N, [](ll a, ll b) { return max(a, b); }, -INF);
    SegTree<ll> segmn(N, [](ll a, ll b) { return min(a, b); }, INF);
    rep(i, 0, N) {
        segmx.set(i, A[i]);
        segmn.set(i, A[i]);
    }
    segmx.build();
    segmn.build();

    vector<ll> ans(3);
    bool ok = false;
    rep(i, 1, N-1) {
        // i以降で前から区間minがxちょうどになる区間
        ll x = segmx.query(0, i);
        ll l1 = segmn.bisearch_fore(i, N-1, x, le);
        ll r1 = segmn.bisearch_fore(i, N-1, x, lt);
        if (r1 == -1) {
            r1 = N - 1;
        }

        // i以降で後ろから区間maxがxちょうどになる区間
        ll l2 = segmx.bisearch_back(i, N-1, x, gt);
        ll r2 = segmx.bisearch_back(i, N-1, x, ge);
        if (l2 == -1) {
            l2 = 0;
        }
        if (r2 == -1) {
            r2 = 0;
        }

        // 2つの区間が重なってない
        if (r1 <= l2 or l1 >= r2) continue;
        // 区間が0の時はxぴったりかチェック
        if (l1 == r1 and A[l1] != x) continue;
        if (l2 == r2 and A[l2] != x) continue;
        ll j = min(r1, r2);
        print("YES");
        ans[0] = i;
        ans[1] = j - i;
        ans[2] = N - j;
        print(ans);
        ok = true;
        break;
    }
    if (!ok) {
        print("NO");
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while(T--) solve();

    return 0;
}
