/**
 * 参考：https://codeforces.com/blog/entry/64989
 * ・方針はだいたい合ってた。問題は以下。
 * ・この再帰、同じ所通らないからメモ要らなかった…。
 * ・その範囲に敵が0人だったらそれ以上潜らなくていいを考慮できなかった。
 * ・でもメモ消すまでREだったのは何でだろう…。
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

ll A, B;
ll aN[100000];
map<ll, ll> c;

ll rec(ll l, ll r) {

	ll mn = INF;
	ll baselen = r-l+1;
	// 二分探索で必要な値を取得
	auto iter1 = next(c.upper_bound(r), -1);
	auto iter2 = next(c.lower_bound(l), -1);
	ll avgs = iter1->second - iter2->second;
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
	ll N, K;
	cin >> N >> K >> A >> B;
	rep(i, 0, K) {
		cin >> aN[i];
		c[aN[i]]++;
	}
	c[0] = 0;
	c[INF] = 0;
	// 累積和
	foreach(c, iter) {
		if (iter != c.end()) {
			auto nxt = next(iter, 1);
			nxt->second += iter->second;
		}
	}
	cout << rec(1, pow(2, N)) << endl;
	return 0;
}
