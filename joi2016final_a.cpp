/**
 * ・なんとか自力AC
 * ・区間加算と1点取得
 * ・と思ったけど、解説見たら区間加算しないでもよかった。。
 * 　差分のとこだけ更新してれば後はいらないのね。。
 * ・ちなみに20万数列に20万クエリでlog付いてもAC0.2秒。やっぱ速いよね。
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
template<typename T> inline bool chmax(T &x, T y) { return (y > x) ? x = y, true : false; }
template<typename T> inline bool chmin(T &x, T y) { return (y < x) ? x = y, true : false; }

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

// 区間加算BIT(区間加算・区間合計取得)
struct BIT2 {

    ll N;
    vector<ll> data0, data1;

    BIT2() {};

    BIT2(ll N) {
        resize(N);
    }

    void resize(ll n) {
        // 添字0が使えないので、内部的には全て1-indexedとして扱う
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

    // 区間[l,r)に値xを追加 
    void add(ll l, ll r, ll x) {
        _add(data0, l, -x*(l-1));
        _add(data0, r, x*(r-1));
        _add(data1, l, x);
        _add(data1, r, -x);
    }

    // 1点更新
    void add(ll i, ll x) {
        add(i, i+1, x);
    }

    // 区間[l,r)の和を取得
    ll query(ll l, ll r) {
        return _get(data1, r-1) * (r-1) + _get(data0, r-1) - _get(data1, l-1) * (l-1) - _get(data0, l-1);
    }

    // 1点取得
    ll get(ll i) {
        return query(i, i+1);
    }
};

ll N, Q, S, T;
vector<ll> A, diff;
BIT2 bit;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> Q >> S >> T;
    N++;
    A.resize(N);
    diff.resize(N-1);
    rep(i, 0, N) cin >> A[i];
    bit.resize(N);
    rep(i, 0, N) bit.add(i, A[i]);

    // 初期状態と各位置の差分を確認
    ll cur = 0;
    rep(i, 0, N-1) {
        diff[i] = A[i+1] - A[i];
        if (diff[i] >= 0) {
            cur += -diff[i] * S;
        } else {
            cur += -diff[i] * T;
        }
    }

    ll l, r, x, nxdiff;
    rep(_, 0, Q) {
        cin >> l >> r >> x;

        // 区間加算
        bit.add(l, r+1, x);
        // 左端について次の差分
        nxdiff = bit.get(l) - bit.get(l-1);
        if (nxdiff >= 0) {
            cur += -nxdiff * S;
        } else {
            cur += -nxdiff * T;
        }
        if (diff[l-1] >= 0) {
            cur += diff[l-1] * S;
        } else {
            cur += diff[l-1] * T;
        }
        diff[l-1] = nxdiff;
        // 末尾なら右端はなし
        if (r < N-1) {
            // 右端について次の差分
            nxdiff = bit.get(r+1) - bit.get(r);
            if (nxdiff >= 0) {
                cur += -nxdiff * S;
            } else {
                cur += -nxdiff * T;
            }
            if (diff[r] >= 0) {
                cur += diff[r] * S;
            } else {
                cur += diff[r] * T;
            }
            diff[r] = nxdiff;
        }
        print(cur);
    }
    return 0;
}
