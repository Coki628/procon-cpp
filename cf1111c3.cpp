/**
 * 参考：https://codeforces.com/blog/entry/64989
 * 　　　submission:49485171
 * ・二分探索を公式に寄せた版
 * ・返されるiterの位置(ポインタ) - 開始位置でindexにする。
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

ll N, K, A, B;
ll aN[100000];
map<ll, ll> c;

ll rec(ll l, ll r) {

	ll mn = INF;
	ll baselen = r-l+1;
	// 二分探索で必要な値を取得
	auto iter1 = upper_bound(aN, aN+K, r)-aN;
	auto iter2 = lower_bound(aN, aN+K, l)-aN;
	ll avgs = iter1 - iter2;
	if (avgs == 0) {
		chmin(mn, A);
	} else {
		chmin(mn, B * avgs * baselen);
	}
	// 敵がいない時も、それ以上潜っても意味ない
	if (baselen >= 2 && avgs != 0) {
		chmin(mn, rec(l + baselen/2, r) + rec(l, r - baselen/2));
	}
	return mn;
}

int main() {
	cin >> N >> K >> A >> B;
	rep(i, 0, K) {
		cin >> aN[i];
	}
	sort(aN, aN+K);

	cout << rec(1, pow(2, N)) << endl;
	return 0;
}
