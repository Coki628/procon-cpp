/**
 * ・貰うDP
 * ・メモリ節約のため、内ループ逆順で回して配列の添字1つ減らした。
 * ・色々あったけど何とかAC
 * ・これだとN回目の結果じゃないやつまで残るから、枚数合計がNと等しいか確認する必要があった。
 * ・基本この添字削るのは真下にも送る系じゃないと使わない方がいいかも。
 * 　今回はうまく最終回の値か判別する方法があったからいいけど。
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

	rep(i, 1, N) {
		for(ll j = 20000; j > 0; j--) {
			if (j-10 >= 0 && dp[j-10][0] != -1) {
				dp[j][0] = dp[j-10][0]+1;
				dp[j][1] = dp[j-10][1];
				dp[j][2] = dp[j-10][2];
			}
			if (j-5 >= 0 && dp[j-5][0] != -1) {
				dp[j][0] = dp[j-5][0];
				dp[j][1] = dp[j-5][1]+1;
				dp[j][2] = dp[j-5][2];
			}
			if (j-1 >= 0 && dp[j-1][0] != -1) {
				dp[j][0] = dp[j-1][0];
				dp[j][1] = dp[j-1][1];
				dp[j][2] = dp[j-1][2]+1;
			}
		}
	}
	if (dp[Y][0]+dp[Y][1]+dp[Y][2] != N) {
		cout << "-1 -1 -1" << endl;
	} else {
		cout << dp[Y][0] << " " << dp[Y][1] << " " << dp[Y][2] << endl;
	}
	return 0;
}
