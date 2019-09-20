/**
 * 参考：https://atcoder.jp/contests/dp/submissions/4122950
 * ・メモ化再帰
 * ・ゲーム木の探索
 * ・得点は引数に入れないし、メモにも入れない。mxとmnの戻り値で管理する。
 * ・再帰の900万
 * ・0.06秒くらいでAC
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define rep(i, a, b) for (ll i = (a); i < (b); i++)
#define all(obj) (obj).begin(), (obj).end()
const ll INF = 1e16;
void chmax(ll &a, ll b) { a = max(a, b); }
void chmin(ll &a, ll b) { a = min(a, b); }

ll aN[3000];
// メモ[左端位置][右端位置] = この局面からの結果
ll memo[3010][3010];
bool visited[3010][3010];

ll rec(int turn, int l, int r) {
	// 全部取り切ったので終了
	if (l > r) return 0;
	// 既に見た局面ならメモの内容を返す
	if (visited[l][r]) return memo[l][r];
	// 先手番
	if (!turn) {
		ll mx = -INF;
		chmax(mx, rec(1, l+1, r) + aN[l]);
		chmax(mx, rec(1, l, r-1) + aN[r]);
		// 訪問済にする
		visited[l][r] = true;
		// ここより深い所を探し終わったので結果をメモする
		return memo[l][r] = mx;
	// 後手番
	} else {
		ll mn = INF;
		chmin(mn, rec(0, l+1, r) - aN[l]);
		chmin(mn, rec(0, l, r-1) - aN[r]);
		visited[l][r] = true;
		return memo[l][r] = mn;
	}
}

int main() {
	int N;
	cin >> N;
	rep(i, 0, N) cin >> aN[i];
	cout << rec(0, 0, N-1) << endl;
	return 0;
}
