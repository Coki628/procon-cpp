/**
 * ・pypyでも3秒TLEしたのでこっちで。
 * ・グリッドBFS、座標圧縮応用
 * ・無事AC1.0秒。
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

vector<vector<bool>> bfs(vector<vector<char>> grid, vector<pii> src) {
    int H = grid.size();
    int W = grid[0].size();
    vector<pii> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    vector<vector<bool>> visited(H, vector<bool>(W, 0));
    queue<pii> que;
    int h, w, dh, dw, h2, w2;
    for (auto p : src) {
        tie(h, w) = p;
        que.push(p);
        visited[h][w] = 1;
    }
    while (!que.empty()) {
        tie(h, w) = que.front(); que.pop();
        for (auto p : directions) {
            tie(dh, dw) = p;
            h2 = h + dh;
            w2 = w + dw;
            // 外壁まで行ったら即終了
            if (grid[h2][w2] == -1) {
                return {};
            }
            if (grid[h2][w2] == 1) {
                continue;
            }
            if (visited[h2][w2]) {
                continue;
            }
            visited[h2][w2] = 1;
            que.push({h2, w2});
        }
    }
    return visited;
}

ll N, M;
vector<tuple<ll, ll, ll>> vert, horz;
unordered_set<ll> S1, S2;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> M;
    S1.insert(0);
    S2.insert(0);
    ll h, h1, h2, w, w1, w2;
    rep(i, 0, N) {
        cin >> h1 >> h2 >> w;
        vert.pb({h1, h2, w});
        S1.insert(h1);
        S1.insert(h2);
        S2.insert(w);
    }
    rep(i, 0, M) {
        cin >> h >> w1 >> w2;
        horz.pb({h, w1, w2});
        S1.insert(h);
        S2.insert(w1);
        S2.insert(w2);
    }

    mli zph, zpw;
    mil unzph, unzpw;
    tie(zph, unzph) = compress(S1);
    tie(zpw, unzpw) = compress(S2);
    // グリッドの壁配置は全部2倍して考える
    ll H = zph.size() * 2;
    ll W = zpw.size() * 2;

    vector<vector<char>> grid(H, vector<char>(W, -1));
    rep(i, 1, H-1) rep(j, 1, W-1) grid[i][j] = 0;
    rep(i, 0, N) {
        tie(h1, h2, w) = vert[i];
        w = zpw[w] * 2;
        rep(h, zph[h1]*2, zph[h2]*2+1) {
            grid[h][w] = 1;
        }
    }
    rep(i, 0, M) {
        tie(h, w1, w2) = horz[i];
        h = zph[h] * 2;
        rep(w, zpw[w1]*2, zpw[w2]*2+1) {
            grid[h][w] = 1;
        }
    }

    auto visited = bfs(grid, {{zph[0]*2, zpw[0]*2}});
    if (visited.empty()) {
        print("INF");
        return 0;
    }

    ll ans = 0, hln, wln;
    // 対象は奇数マスだけ
    for (int i=1; i<H-1; i+=2) {
        for (int j=1; j<W-1; j+=2) {
            if (visited[i][j]) {
                hln = unzph[i/2+1] - unzph[i/2];
                wln = unzpw[j/2+1] - unzpw[j/2];
                ans += hln * wln;
            }
        }
    }
    print(ans);
    return 0;
}
