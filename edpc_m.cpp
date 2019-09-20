/**
 * 参考：https://kyopro-friends.hatenablog.com/entry/2019/01/12/231035
 * ・数え上げDP
 * ・累積和で高速化
 * ・計算量O(N*K*2)=2000万
 * ・0.09秒くらいでAC。速っ…。
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

ll aN[100000];
// dp[この子までの範囲で][飴を配る総数] = 場合の数
ll dp[110][10010];

int main() {
	int N, K;
	cin >> N >> K;
	rep(i, 0, N) cin >> aN[i];
	// 0番目まで(誰もいない)の範囲で0個配る場合の数は1通り
	dp[0][0] = 1;

	rep(i, 0, N) {
		ll sm[K+2];
		// 今回送るi行について累積和を取る
		rep(j, 1, K+2) {
			sm[j] = (sm[j-1] + dp[i][j-1]) % MOD;
		}
		rep(j, 0, K+1) {
			// iが送る予定の長さに応じた区間和を取る
			// ここは +MOD が入る
			dp[i+1][j] = (sm[j+1] - sm[max(j-aN[i], ll(0))] + MOD) % MOD;
		}
	}
	cout << dp[N][K] << endl;
	return 0;
}
