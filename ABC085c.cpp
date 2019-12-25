/**
 * ・配るDP
 * ・配列要素確保しすぎてMLE…。
 * ・時間計算量2000*2万*3=1億2000万はダメみたいだ。
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define rep(i, a, b) for (ll i = (a); i < (b); i++)
#define all(obj) (obj).begin(), (obj).end()
const ll INF = 1e16;
const ll MOD = 1e9 + 7;
void chmax(ll &a, ll b) { a = max(a, b); }
void chmin(ll &a, ll b) { a = min(a, b); }

ll dp[2001][20020][3];

int main() {
	int N, Y;
	cin >> N >> Y;
	Y /= 1000;
	memset(dp, -1, sizeof(dp));
	dp[1][1][0] = 0;
	dp[1][1][1] = 0;
	dp[1][1][2] = 1;
	dp[1][5][0] = 0;
	dp[1][5][1] = 1;
	dp[1][5][2] = 0;
	dp[1][10][0] = 1;
	dp[1][10][1] = 0;
	dp[1][10][2] = 0;

	rep(i, 1, N) {
		rep(j, 0, 20000) {
			if (j > Y || j + 10*(N-i) < Y) continue;
			if (dp[i][j][0] != -1) {
				dp[i+1][j+1][0] = dp[i][j][0];
				dp[i+1][j+1][1] = dp[i][j][1];
				dp[i+1][j+1][2] = dp[i][j][2]+1;
				dp[i+1][j+5][0] = dp[i][j][0];
				dp[i+1][j+5][1] = dp[i][j][1]+1;
				dp[i+1][j+5][2] = dp[i][j][2];
				dp[i+1][j+10][0] = dp[i][j][0]+1;
				dp[i+1][j+10][1] = dp[i][j][1];
				dp[i+1][j+10][2] = dp[i][j][2];
			}
		}
	}
	cout << dp[N][Y][0] << " " << dp[N][Y][1] << " " << dp[N][Y][2] << endl;
	return 0;
}
