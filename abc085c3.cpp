/**
 * ・配るDP
 * ・メモリ節約のため、1つ前の情報を保持しながらやった。
 * ・色々あったけど何とかAC
 * ・N回目より前の情報はいらないので、都度初期化しながらやる。
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

ll dp[20020][3];
ll prv[20020][3];

int main() {
	int N, Y;
	cin >> N >> Y;
	Y /= 1000;
	memset(dp, -1, sizeof(dp));
	dp[1][0] = 0;
	dp[1][1] = 0;
	dp[1][2] = 1;
	dp[5][0] = 0;
	dp[5][1] = 1;
	dp[5][2] = 0;
	dp[10][0] = 1;
	dp[10][1] = 0;
	dp[10][2] = 0;
	memcpy(prv, dp, sizeof(dp));
	memset(dp, -1, sizeof(dp));

	rep(i, 1, N) {
		rep(j, 0, 20000) {
			if (j > Y || j + 10*(N-i) < Y) continue;
			if (prv[j][0] != -1 || prv[j][1] != -1 || prv[j][2] != -1) {
				dp[j+1][0] = prv[j][0];
				dp[j+1][1] = prv[j][1];
				dp[j+1][2] = prv[j][2]+1;
				dp[j+5][0] = prv[j][0];
				dp[j+5][1] = prv[j][1]+1;
				dp[j+5][2] = prv[j][2];
				dp[j+10][0] = prv[j][0]+1;
				dp[j+10][1] = prv[j][1];
				dp[j+10][2] = prv[j][2];
			}
		}
		memcpy(prv, dp, sizeof(dp));
		memset(dp, -1, sizeof(dp));
	}
	cout << prv[Y][0] << " " << prv[Y][1] << " " << prv[Y][2] << endl;
	return 0;
}
