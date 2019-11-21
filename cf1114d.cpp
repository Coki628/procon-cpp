/**
 * 参考：https://codeforces.com/blog/entry/65136
 * 　　　submission:49738197
 * ・区間DP
 * ・メモ化再帰
 * ・DPコンのスライムと一緒で、完成から戻してく方針でやれば、
 * 　開始位置を意識せずに最適が出せるみたいだ。
 * ・pythonがTLEだったからこっちでAC
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define foreach(c, iter) for(auto iter=(c).begin(); iter!=(c).end(); iter++)
#define all(obj) (obj).begin(), (obj).end()
const ll INF = 1e18;
const ll MOD = 1e9 + 7;
void chmax(ll &a, ll b) { a = max(a, b); }
void chmin(ll &a, ll b) { a = min(a, b); }

ll cN[5000];
vector<ll> cN2;
// メモ[左端位置][右端位置] = この局面からの最短ターン数
ll memo[5010][5010];
bool visited[5010][5010];

ll rec(int l, int r) {
	if (l == r) return 0;
	if (visited[l][r]) return memo[l][r];
	ll res = INF;
	if (cN2[l] == cN2[r]) {
		res = min(res, rec(l+1, r-1)+1);
	} else {
		res = min(res, rec(l+1, r)+1);
		res = min(res, rec(l, r-1)+1);
	}
	visited[l][r] = true;
	return memo[l][r] = res;
}

int main() {
	int N;
	cin >> N;
	rep(i, 0, N) cin >> cN[i];
	// 隣接して重複している値は不要なので削る
	cN2.push_back(cN[0]);
	rep(i, 1, N) {
		if (cN[i] != cN[i-1]) {
			cN2.push_back(cN[i]);
		}
	}
	cout << rec(0, cN2.size()-1) << endl;
	return 0;
}
