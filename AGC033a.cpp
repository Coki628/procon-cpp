/**
 * ・グリッドのBFS
 * ・pypyでも通らなかったからこっちで通した。
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
#include <cstring>
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

typedef tuple<int,int,int> P;
vector<string> grid;
vector<vector<ll>> L,R,U,D;
unordered_map<char,vector<int>> prep;
queue<P> que;
vector<tuple<int,int>> directions;
ll memo[1010][1010];
bool visited[1010][1010];

int main() {
    int H,W;
    ll ans;
    string s;
    memset(memo, -1, sizeof(memo));
    cin>>H>>W;
    // 四方に一回り大きいグリッドを作る
    grid.resize(H+2);
    grid[0]=string(W+2,'*');
    grid[H+1]=string(W+2,'*');
    rep(i,1,H+1) {
        cin>>s;
        grid[i]="*"+s+"*";
    }
    rep(i,1, H+1) rep(j,1, W+1) {
        if (grid[i][j]=='#') {
            que.push(make_tuple(i, j, 0));
        }
    }
    // 4方向の設定
    directions.pb(make_tuple(0, -1));
    directions.pb(make_tuple(0, 1));
    directions.pb(make_tuple(-1, 0));
    directions.pb(make_tuple(1, 0));

    while(!que.empty()) {
        P cur=que.front(); que.pop();
        int cur_h=get<0>(cur);
        int cur_w=get<1>(cur);
        int cost=get<2>(cur);
        // 訪問済チェック
        if (visited[cur_h][cur_w]) continue;
        visited[cur_h][cur_w]=true;
        memo[cur_h][cur_w]=cost;
        // 4方向見る
        for(tuple<int,int> dir: directions) {
            int nxt_h=cur_h+get<0>(dir);
            int nxt_w=cur_w+get<1>(dir);
            // 壁、黒はスキップ
            if (grid[nxt_h][nxt_w]=='*' || grid[nxt_h][nxt_w]=='#') continue;
            // 白を埋める
            if (grid[nxt_h][nxt_w]=='.') {
                grid[nxt_h][nxt_w]='#';
                que.push(make_tuple(nxt_h, nxt_w, cost+1));
            }
        }
    }
    ans=0;
    rep(i,1, H+1) rep(j,1, W+1) {
        chmax(ans, memo[i][j]);
    }
    cout<<ans<<endl;
    return 0;
}
