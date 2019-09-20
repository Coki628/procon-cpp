/**
 * ・速度改善
 * ・check内のグリッドをグローバルで宣言(都度初期化しない) → すごい速くなった。
 * ・gridのvetcorを配列にしてみる。 → ほぼ変わらず。
 * ・bitカウントを速いやつに → ちょっと速くなった。
 * ・checkをグリッド作らないでビットのままやる。 → 結構速くなった。
 * ・2乗をpowしてllにキャストしてたのをビットシフトに → すごい速くなった。
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

int grid[5][5];
vector<pii> used(26, mkp(-1, -1));
// dp[i] := 集合iを埋まっているマス目として、その状態でのうまくいく通り数
int dp[1<<25];

bool check(ll bit, ll a) {
    int h = a / 5;
    int w = a % 5;
    // 縦位置の確認
    if (1 <= h && h <= 3) {
        // グリッドでのaから見た上下
        int u = (bit >> a-5) & 1;
        int d = (bit >> a+5) & 1;
        // 上下どちらかだけ埋まってたらNG
        if (u^d) return 0;
    }
    // 横位置の確認
    if (1 <= w && w <= 3) {
        // グリッドでのaから見た左右
        int l = (bit >> a-1) & 1;
        int r = (bit >> a+1) & 1;
        // 左右どちらかだけ埋まってたらNG
        if (l^r) return 0;
    }
    return 1;
}

int bit_cnt(ll i) {
    i = i - ((i >> 1) & 0x55555555);
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
    i = (i + (i >> 4)) & 0x0f0f0f0f;
    i = i + (i >> 8);
    i = i + (i >> 16);
    return i & 0x3f;
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

    dp[0] = 1;
    rep(bit, 0, (1<<25)-1) {
        // 0からは何も遷移しない
        if (dp[bit] == 0) continue;
        int cur = bit_cnt(bit) + 1;
        // 置く場所が決まっている時はその遷移だけ確認
        if (used[cur].first!=-1 && used[cur].second!=-1) {
            int nxt = used[cur].first*5 + used[cur].second;
            // nxtが既にbitに含まれている時はskip
            if ((bit>>nxt)&1) continue;
            dp[bit+(1<<nxt)] += dp[bit] * check(bit, nxt);
            dp[bit+(1<<nxt)] %= MOD;
        } else {
            // 決まっていない時は25箇所それぞれを試す
            rep(i, 0, 25) {
                // iが既にbitに含まれている時はskip
                if ((bit>>i)&1) continue;
                dp[bit+(1<<i)] += dp[bit] * check(bit, i);
                dp[bit+(1<<i)] %= MOD;
            }
        }
    }
    print(dp[(1<<25)-1]);
    return 0;
}
