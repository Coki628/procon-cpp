/**
 * ・蟻本演習2-3-15
 * ・部分文字列DP、復元、辞書順系
 */

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

int H, W, N;
int grid[1003][1003];
int dp[1003][1003];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int i, j;
    cin >> H >> W >> N;
    rep(i, 0, H) rep(j, 0, W) {
        cin >> grid[i][j];
    }

    // dp[i][j] := (i, j)のマスをN回目の前までに何回通るか
    rep(i, 0, H+1) rep(j, 0, W+1) dp[i][j] = 0;
    dp[0][0] = N - 1;
    rep(i, 0, H) rep(j, 0, W) {
        // 通る回数が偶数なら半分ずつ
        if (dp[i][j] % 2 == 0) {
            dp[i+1][j] += dp[i][j] / 2;
            dp[i][j+1] += dp[i][j] / 2;
        } else {
            // 通る回数が奇数なら、元のグリッドの状態に応じて1回多く行く方が決まる
            if (grid[i][j] == 0) {
                dp[i+1][j] += dp[i][j] / 2 + 1;
                dp[i][j+1] += dp[i][j] / 2;
            } else {
                dp[i+1][j] += dp[i][j] / 2;
                dp[i][j+1] += dp[i][j] / 2 + 1;
            }
        }
    }

    // N-1回終了時の状態にグリッドを更新
    rep(i, 0, H) rep(j, 0, W) {
        grid[i][j] ^= dp[i][j];
        grid[i][j] &= 1;
    }

    // N回目の散歩をシミュレーション
    i = j = 0;
    while (i < H && j < W) {
        if (grid[i][j] == 0) {
            i++;
        } else {
            j++;
        }
    }
    print(str(i+1) + " " + str(j+1));
    return 0;
}
