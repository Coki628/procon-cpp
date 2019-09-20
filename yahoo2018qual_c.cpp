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

// dp[n][msk] := n個売却して商品集合msk全てを購入した場合の最大価値(購入できないなら0)
// メビウス変換を行うことで以下のようになる
// dp[n][msk] := n個売却して購入可能商品がmskの場合の最大価値
vector<vector<ll>> dp,memo;
vector<ll> X,C,V;
int N;

ll rec(int n, int turn, int msk) {
    // メモ返却と終了条件
    if (memo[n][msk]!=-1) return memo[n][msk];
    if (n==N) return 0;

    ll ret;
    // 先手番(売却か購入)
    if (turn==0) {
        ret=0;
        // 売却
        chmax(ret, rec(n+1, 1, msk));
        // 購入(今の状況で得られる最大値はbitDPで前計算してある)
        chmax(ret, dp[n][msk]);
    // 後手番(破棄)
    } else {
        ret=INF;
        rep(i, 0, N) {
            // 1<<iビット目の商品がまだあったら破棄してみる
            if (msk&(1<<i)) {
                // 破棄(一番最小化できるものを使う)
                chmin(ret, rec(n, 0, msk-(1<<i)));
            }
        }
    }
    return memo[n][msk]=ret;
}

int main() {
    cin>>N;
    X.resize(N);
    C.resize(N);
    V.resize(N);
    dp.resize(N+1);
    rep(i, 0, N+1) dp[i].resize(1<<N);
    memo.resize(N+1);
    rep(i, 0, N+1) memo[i].resize(1<<N);
    rep(i, 0, N+1) rep(j, 0, 1<<N) memo[i][j]=-1;
    rep(i, 0, N) cin>>X[i];
    rep(i, 0, N) cin>>C[i];
    rep(i, 0, N) cin>>V[i];

    rep(n, 0, N+1) {
        // n個売却して円を獲得
        ll yen=0;
        rep(i, 0, n) yen+=X[i];
        // どの商品を購入するかをビットで全組み合わせ試す
        rep(msk, 0, 1<<N) {
            ll cost, val;
            cost=val=0;
            rep(i, 0, N) {
                // 1<<iビット目の商品を購入
                if (msk&(1<<i)) {
                    cost+=C[i];
                    val+=V[i];
                }
            }
            // 円が足りていればmskの全商品を購入する
            if (cost<=yen) {
                dp[n][msk]=val;
            } else {
                dp[n][msk]=0;
            }
        }
        // dp[n][msk]の部分集合とmaxを取る(メビウス変換：状態xの部分状態yを全列挙)
        rep(msk, 0, 1<<N) rep(i, 0, N) if (msk&(1<<i)) {
            chmax(dp[n][msk], dp[n][msk^(1<<i)]);
        }
    }
    cout<<rec(0, 0, (1<<N)-1)<<endl;
    return 0;
}
