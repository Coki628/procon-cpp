/**
 * 参考：https://img.atcoder.jp/arc092/editorial.pdf
 * 　　　https://www.youtube.com/watch?v=DqqPuIZvJTk
 * 　　　http://hyoga.hatenablog.com/entry/2018/03/21/231229
 * 　　　https://www.hamayanhamayan.com/entry/2018/03/18/090701
 * ・XORは繰り上がりがないのでビット毎に考えられる。
 * ・ビットが立つ範囲は決まっていて循環しているので、それに合わせて効率よくmodを取る。
 * ・ループを回すのはaNでも、二分探索でbNの値を効率よく調べられる。
 * ・O(29*N*2*logN*4)=2億3200万くらい。
 * ・2秒ちょっとでAC。すげぇな。
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long ll;
#define rep(i, a, b) for (ll i = (a); i < (b); i++)
#define all(obj) (obj).begin(), (obj).end()

int main() {
	ll N;
	ll ans = 0;
	cin >> N;
	vector<ll> A(N), B(N), B2(N);
	rep(i, 0, N) cin >> A[i];
	rep(i, 0, N) cin >> B[i];
	// 各ビットのループ
	rep(i, 0, 29) {
		ll T = pow(2, i);
		// 今回のビット用に2Tでmodを取ったbNを作る
		rep(j, 0, N) B2[j] = B[j] % (2*T);
		// 二分探索で範囲内の数を数えるのでソートしておく
		sort(all(B2));
		ll cnt = 0;
		// Aのループ
		rep(j, 0, N) {
			// Aも同じ位置でmodを取る
			ll a = A[j] % (2*T);
			// [T-a,2T-a)と[3T-a,4T-a)の範囲内にあるbの数を数える
			cnt += lower_bound(all(B2), 2*T-a) - lower_bound(all(B2), T-a);
			cnt += lower_bound(all(B2), 4*T-a) - lower_bound(all(B2), 3*T-a);
		}
		// XORなので、ビットの立っている場所が奇数個なら1
		if (cnt % 2 == 1) {
			ans += T;
		}
	}
	cout << ans << endl;
	return 0;
}
