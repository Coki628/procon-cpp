/**
 * 参考：https://tenka1-2016-qualb.contest.atcoder.jp/data/other/tenka1-2016-qualb/editorial.pdf
 * ・メモ化再帰
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <utility>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>
using namespace std;

typedef long long ll;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define all(obj) (obj).begin(), (obj).end()
#define fi first
#define sc second
#define pb push_back
#define str to_string
const ll INF = 1e18;
const ll MOD = 1e9 + 7;
void chmax(ll &a, ll b) { a = max(a, b); }
void chmin(ll &a, ll b) { a = min(a, b); }

int N;
string S;
// memo[現在位置][ここまでの(と)の差]][最後の操作位置]
ll memo[110][110][110];

ll rec(int cur, int gap, int last) {

    if (gap<0) return INF;
    if (memo[cur][gap][last]!=-1) return memo[cur][gap][last];
    if (cur==N) {
        if (gap==0) return last;
        else return INF;
    }

    ll res=INF;
    if (S[cur]=='(') {
        chmin(res, rec(cur+1, gap-1, cur)+1);
        chmin(res, rec(cur+1, gap+1, last));
    } else {
        chmin(res, rec(cur+1, gap+1, cur)+1);
        chmin(res, rec(cur+1, gap-1, last));
    }

    return memo[cur][gap][last]=res;
}

int main() {
	cin >> S;
    N=S.size();
    rep(i, 0, 110) rep(j, 0, 110) rep(k, 0, 110) {
        memo[i][j][k]=-1;
    }
	cout << rec(0, 0, 0) << endl;
	return 0;
}
