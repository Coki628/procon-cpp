#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<ll, int, int> tlii;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef vector<vector<ll>> vvl;
typedef vector<vector<int>> vvi;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define all(obj) (obj).begin(), (obj).end()
#define pb push_back
#define str to_string
#define mkp make_pair
#define mkt make_tuple
#define print(out) cout << (out) << endl
const ll INF = 1e18;
const ll MOD = 1e9 + 7;
void chmax(ll &a, ll b) { a = max(a, b); }
void chmin(ll &a, ll b) { a = min(a, b); }

int grid[5][5];
vector<pii> used(26, mkp(-1, -1));
// dp[i] := 集合iを埋まっているマス目として、その状態でのうまくいく通り数
int dp[1<<25];
// 都度初期化が重かったぽいのでグローバルに置いた
// vvi grid2(7, vector<int>(7, -1));
int grid2[7][7];

bool check(ll bit, ll a) {

    int cnt, h, w;
    cnt = h = w = 0;
    rep(i, 1, 6) rep(j, 1, 6) {
        if (cnt==a) {
            h = i;
            w = j;
        }
        grid2[i][j] = (bit>>cnt) & 1;
        cnt++;
    }
    // 縦方向のチェック
    if (grid2[h-1][w]!=-1 && grid2[h+1][w]!=-1
            && (grid2[h-1][w]==1 ^ grid2[h+1][w]==1)) {
        return 0;
    }
    // 横方向のチェック
    if (grid2[h][w-1]!=-1 && grid2[h][w+1]!=-1
            && (grid2[h][w-1]==1 ^ grid2[h][w+1]==1)) {
        return 0;
    }
    return 1;
}

int bit_cnt(ll bit) {
    int res = 0;
    rep(i, 0, 25) {
        res += (bit>>i) & 1;
    }
    return res;
}

int main() {

    rep(i, 0, 5) rep(j, 0, 5) {
        cin >> grid[i][j];
    }
    rep(i, 0, 5) rep(j, 0, 5) {
        if (grid[i][j]!=0) {
            used[grid[i][j]] = mkp(i, j);
        }
    }
    rep(i, 0, 7) rep(j, 0, 7) grid2[i][j] = -1;

    dp[0] = 1;
    rep(bit, 0, 1<<25) {
        // 0からは何も遷移しない
        if (dp[bit] == 0) continue;
        int cur = bit_cnt(bit) + 1;
        // 置く場所が決まっている時はその遷移だけ確認
        if (used[cur].first!=-1 && used[cur].second!=-1) {
            int nxt = used[cur].first*5 + used[cur].second;
            // nxtが既にbitに含まれている時はskip
            if ((bit>>nxt)&1) continue;
            dp[bit+ll(pow(2, nxt))] += dp[bit] * check(bit, nxt);
            dp[bit+ll(pow(2, nxt))] %= MOD;
        } else {
            // 決まっていない時は25箇所それぞれを試す
            rep(i, 0, 25) {
                // iが既にbitに含まれている時はskip
                if ((bit>>i)&1) continue;
                dp[bit+ll(pow(2, i))] += dp[bit] * check(bit, i);
                dp[bit+ll(pow(2, i))] %= MOD;
            }
        }
    }
    print(dp[(1<<25)-1]);
    return 0;
}
