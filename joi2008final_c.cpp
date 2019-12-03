/**
 * ・蟻本演習3-2-3、自力AC！
 * ・あみだくじのグリッド。実装疲れた。
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<ll, int, int> tlii;
typedef pair<ll, ll> pll;
typedef pair<ll, int> pli;
typedef pair<int, int> pii;
typedef pair<pair<int, int>, ll> ppiil;
typedef vector<vector<ll>> vvl;
typedef vector<vector<int>> vvi;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define all(obj) (obj).begin(), (obj).end()
#define pb push_back
#define str to_string
#define mkp make_pair
#define mkt make_tuple
const ll INF = 1e18;
const ll MOD = 1e9 + 7;
void chmax(ll &a, ll b) { a = max(a, b); }
void chmin(ll &a, ll b) { a = min(a, b); }

template<typename T>
void print(T out) {
    cout << out << '\n';
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

int grid[1007][2007];
int N, H, W, M, K, a, b, h, w;
ll score, ans;
vector<ll> A, goals;
vvi B;
map<int, map<int, int>> keys;
queue<pii> que;
pii cur;

// あみだくじのルートを確認する
ll check(int start) {
    start++;
    start *= 2;
    start--;
    que.push(mkp(1, start));
    while (!que.empty()) {
        cur = que.front(); que.pop();
        h = cur.first, w = cur.second;
        if (h == H) {
            return A[(w+1)/2-1];
        }
        if (grid[h][w-1] == 1) {
            // 各横棒をどのルートが通ったのか覚えておく
            B[keys[h][w-1]].pb((start+1)/2-1);
            que.push(mkp(h+1, w-2));
        } else if (grid[h][w+1] == 1) {
            B[keys[h][w+1]].pb((start+1)/2-1);
            que.push(mkp(h+1, w+2));
        } else {
            que.push(mkp(h+1, w));
        }
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> M >> H >> K;
    A.resize(N);
    B.resize(M);
    goals.resize(N);
    W = N * 2;
    memset(grid, -1, sizeof(grid));
    // 縦棒
    rep(i, 1, H) {
        for (int j = 1; j < W; j += 2) {
            grid[i][j] = 0;
        }
    }
    rep(i, 0, N) cin >> A[i];
    // 横棒
    rep(i, 0, M) {
        cin >> a >> b;
        grid[b][a*2] = 1;
        // グリッド位置と横棒IDを紐付けるキー
        keys[b][a*2] = i;
    }

    // 横棒削除前の到着予定と得点
    rep(i, 0, N) {
        goals[i] = check(i);
    }
    score = 0;
    rep(i, 0, K) {
        score += goals[i];
    }
    
    // 横棒削除によりスワップするどちらかだけがK以内の場合を全部試す
    ans = score;
    rep(i, 0, M) {
        a = B[i][0], b = B[i][1];
        if (a < K && b >= K) {
            chmin(ans, score - goals[a] + goals[b]);
        }
        if (b < K && a >= K) {
            chmin(ans, score - goals[b] + goals[a]);
        }
    }
    print(ans);
    return 0;
}
