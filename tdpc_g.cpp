/**
 * ・蟻本演習2-3-13
 * ・グリッドDP
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<ll, int, int> tlii;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef vector<vector<ll>> vvl;
typedef vector<vector<int>> vvi;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define all(obj) (obj).begin(), (obj).end()
#define pb push_back
#define str to_string
#define mkp make_pair
#define mkt make_tuple
#define print(out) cout << (out) << endl
const ll INF = 1e18;
const ll MOD = 1e9 + 7;
void chmax(ll &a, ll b) { a = max(a, b); }
void chmin(ll &a, ll b) { a = min(a, b); }

int N, curi, i;
ll K, curk, k;
string S, ans;
ll nxt[1000001][26];
ll dp[1000001];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> S;
    cin >> K;
    N = S.size();

    // nxt[i][c] := i文字目以降で最初に文字cが登場するindex(存在しないときはN)
    rep(i, 0, N+1) rep(c, 0, 26) nxt[i][c] = N;
    rrep(i, N-1, -1) {
        rep(c, 0, 26) {
            nxt[i][c] = nxt[i+1][c];
        }
        // char => int のキャスト
        nxt[i][(int)(S[i]-'a')] = i;
    }

    // dp[i] := i文字目以降について部分文字列となる通り数
    rep(i, 0, N+1) dp[i] = 1;
    rrep(i, N-1, -1) {
        rep(c, 0, 26) {
            // 次の文字がない時
            if (nxt[i][c] == N) {
                continue;
            // 次の文字がある時
            } else {
                // 次回出現位置の次のindexから貰う
                dp[i] += dp[nxt[i][c]+1];
                // 数が大きくなりすぎないようにする(K+1以下が分かれば問題ない)
                chmin(dp[i], K+1);
            }
        }
    }

    // 全通り-空文字列 < K なら不可
    if (dp[0] - 1 < K) {
        print("Eel");
        return 0;
    }

    // 復元
    curi = curk = 0;
    ans = "";
    // ぴったりK通りに来るまで文字を追加していく
    while (curk != K) {
        rep(c, 0, 26) {
            // 文字cが次に出現する位置
            i = nxt[curi][c];
            // この文字はもうない
            if (i == N) continue;
            // 文字cから始まる部分文字列の通り数k(先頭はcで確定なので、+1した位置の通り数)
            k = dp[i+1];
            // K以上になるまでは該当位置のkを足していく
            if (curk + k < K) {
                curk += k;
                continue;
            } else {
                // int => char のキャスト
                ans += (char)('a' + c);
                // 文字cが増えた分1通り追加
                curk ++;
                // indexは今回のc出現位置の次に
                curi = i + 1;
                break;
            }
        }
    }
    print(ans);
    return 0;
}
