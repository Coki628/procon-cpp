/**
 * ・自力AC。予定外に時間かかったけど。。
 * ・分かった知見。C++の文字列処理、(多分)やり方によっては激遅。
 * ・100万ループの内側でstringの文字列結合4回と比較やってるだけで1秒間に合わなかった。
 * ・しょうがないからvector<char>に置き換えてやったらAC0.2秒。
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

ll H, W;
vector<string> grid;
bool good[1007][1007];
vector<char> emb(4);
vector<char> comp(4);

// 紋章との一致確認
bool check(ll h, ll w) {
    comp[0] = grid[h][w];
    comp[1] = grid[h][w+1];
    comp[2] = grid[h+1][w];
    comp[3] = grid[h+1][w+1];
    return comp == emb;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> H >> W;
    grid.resize(H+2);
    grid[0] = string(W+2, 'X');
    grid[H+1] = string(W+2, 'X');
    string tmp = "";
    rep(h, 1, H+1) {
        cin >> tmp;
        grid[h] = "X" + tmp + "X";
    }
    cin >> tmp;
    emb[0] = tmp[0];
    emb[1] = tmp[1];
    cin >> tmp;
    emb[2] = tmp[0];
    emb[3] = tmp[1];

    // まず初期状態をカウントしておく
    ll ans = 0;
    rep(i, 1, H) {
        rep(j, 1, W) {
            if (check(i, j)) {
                good[i][j] = true;
                ans++;
            }
        }
    }

    int mx = 0;
    rep(i, 1, H+1) {
        rep(j, 1, W+1) {
            for (char c : "JOI") {
                if (c == grid[i][j]) {
                    continue;
                }
                int cnt = 0;
                char tmp = grid[i][j];
                grid[i][j] = c;
                // 結局4箇所しか影響しないので、それぞれどうなるか確認する
                rep(k, -1, 1) {
                    rep(l, -1, 1) {
                        cnt -= good[i+k][j+l];
                        if (check(i+k, j+l)) {
                            cnt++;
                        }
                    }
                }
                chmax(mx, cnt);
                grid[i][j] = tmp;
            }
        }
    }
    ans += mx;
    print(ans);
    return 0;
}
