/**
 * ・自力RE
 * ・2次元いもす、座標圧縮
 * ・座圧しても10000*10000くらいのグリッドになってるぽくて無理だった。。
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

// 座標圧縮
typedef map<ll, int> mli;
typedef map<int, ll> mil;
pair<mli, mil> compress(set<ll> S) {
    mli zipped;
    mil unzipped;
    vector<ll> A(btoe(S));
    sort(btoe(A));
    rep(i, 0, A.size()) {
        zipped[A[i]] = i;
        unzipped[i] = A[i];
    }
    return mkp(zipped, unzipped);
}

ll N, H, W;
vector<pair<pll, pll>> A;
set<ll> S1, S2;
short imos[5007][5007];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    cin >> W >> H;
    A.resize(N);
    rep(i, 0, N) cin >> A[i].first.second >> A[i].first.first >> A[i].second.second >> A[i].second.first;

    // 座標圧縮
    for (auto p : A) {
        S1.insert(p.first.first);
        S2.insert(p.first.second);
        S1.insert(p.second.first);
        S1.insert(p.second.first + 1);
        S2.insert(p.second.second);
        S2.insert(p.second.second + 1);
    }
    auto comp1 = compress(S1);
    auto comp2 = compress(S2);
    H = comp1.first.size();
    W = comp2.first.size();

    // 2次元いもす
    for (auto p : A) {
        imos[comp1.first[p.first.first]][comp2.first[p.first.second]]++;
        imos[comp1.first[p.second.first]+1][comp2.first[p.first.second]]--;
        imos[comp1.first[p.first.first]][comp2.first[p.second.second]+1]--;
        imos[comp1.first[p.second.first]+1][comp2.first[p.second.second]+1]++;
    }
    rep(i, 0, H) {
        rep(j, 0, W-1) {
            imos[i][j+1] += imos[i][j];
        }
    }
    rep(j, 0, W) {
        rep(i, 0, H-1) {
            imos[i+1][j] += imos[i][j];
        }
    }

    short mx = 0;
    rep(i, 0, H) {
        rep(j, 0, W) {
            chmax(mx, imos[i][j]);
        }
    }
    ll ans = 0;
    rep(i, 0, H) {
        rep(j, 0, W) {
            // 最大になる場所の大きさを調べていく
            if (imos[i][j] == mx) {
                int lh = comp1.second[i];
                int lw = comp2.second[j];
                int rh = comp1.second[i+1];
                int rw = comp2.second[j+1];
                int h = rh - lh;
                int w = rw - lw;
                ans += h * w;
            }
        }
    }
    print(mx);
    print(ans);
    return 0;
}
