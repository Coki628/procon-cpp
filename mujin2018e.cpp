#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define all(obj) (obj).begin(), (obj).end()
#define fi first
#define sc second
#define pb push_back
#define str to_string
const ll INF = 1e18;
const ll MOD = 1e9 + 7;
void chmax(ll &a, ll b) { a = max(a, b); }
void chmin(ll &a, ll b) { a = min(a, b); }

typedef tuple<ll,int,int> P;
vector<string> grid;
vector<vector<ll>> L,R,U,D;
unordered_map<char,vector<int>> prep;
// vector<direction> directions;
vector<tuple<int,int,char>> directions;
P start;
P goal;
ll memo[1010][1010];
bool visited[1010][1010];
int N,M,K;

// struct direction {
//     int h;
//     int w;
//     char k;
// };

ll dijkstra(P start) {
    priority_queue<P, vector<P>, greater<P>> que;
    // スタート位置
    que.push(start);
    memo[get<1>(start)][get<2>(start)]=0;

    while(!que.empty()) {
        P cur=que.top(); que.pop();
        ll cur_t=get<0>(cur);
        int cur_h=get<1>(cur);
        int cur_w=get<2>(cur);
        // 訪問済チェック
        if (visited[cur_h][cur_w]) continue;
        visited[cur_h][cur_w]=true;
        // 4方向見る
        for(tuple<int,int,char> dir: directions) {
            ll nxt_t=cur_t;
            int nxt_h=cur_h+get<0>(dir);
            int nxt_w=cur_w+get<1>(dir);
            char k=get<2>(dir);
            // 壁はスキップ
            if (grid[nxt_h][nxt_w]=='#') continue;
            // 現在時間+1+待ち時間を移動先に記録
            if (grid[nxt_h][nxt_w]=='.') {
                int stay=prep[k][cur_t%K];
                if (stay==-1) continue;
                ll dist=min(memo[cur_h][cur_w]+1+stay, memo[nxt_h][nxt_w]);
                if (!visited[nxt_h][nxt_w]) {
                    memo[nxt_h][nxt_w]=dist;
                    // 現在の経過時間をキューの優先度として、早い方から先に処理するようにする
                    nxt_t=dist;
                    que.push(make_tuple(nxt_t,nxt_h,nxt_w));
                }
            // # Gはキューに詰めないで記録のみ
            } else if (grid[nxt_h][nxt_w]=='G') {
                int stay=prep[k][cur_t%K];
                if (stay==-1) continue;
                ll dist=min(memo[cur_h][cur_w]+1+stay, memo[nxt_h][nxt_w]);
                memo[nxt_h][nxt_w]=dist;
            }
        }
    }
    // ゴール地点への最短時間を返却
    return memo[get<1>(goal)][get<2>(goal)];
}

int main() {
    int lcnt,rcnt,ucnt,dcnt;
    ll ans;
    string d,s;

    cin>>N>>M>>K;
    cin>>d;

    // あと何秒で特定の方向に動けるかを準備しておく
    prep['L'].resize(K);
    prep['R'].resize(K);
    prep['U'].resize(K);
    prep['D'].resize(K);
    lcnt=rcnt=ucnt=dcnt=0;
    // 循環するので*2から始めて逆順でやる
    rrep(i,K*2-1,-1) {
        if (d[i%K]=='L') lcnt=0;
        if (d[i%K]=='R') rcnt=0;
        if (d[i%K]=='U') ucnt=0;
        if (d[i%K]=='D') dcnt=0;
        if (i<K) {
            prep['L'][i]=lcnt;
            prep['R'][i]=rcnt;
            prep['U'][i]=ucnt;
            prep['D'][i]=dcnt;
        }
        lcnt++;
        rcnt++;
        ucnt++;
        dcnt++;
    }
    // 行ける方向だけ詰める
    if (d.find("L")!=-1) directions.pb(make_tuple(0,-1,'L'));
    if (d.find("R")!=-1) directions.pb(make_tuple(0,1,'R'));
    if (d.find("U")!=-1) directions.pb(make_tuple(-1,0,'U'));
    if (d.find("D")!=-1) directions.pb(make_tuple(1,0,'D'));
    // 一回り大きいグリッドを構築
    grid.resize(N+2);
    grid[0]=string(M+2,'#');
    grid[N+1]=string(M+2,'#');
    rep(i,1,N+1) {
        cin>>s;
        grid[i]="#"+s+"#";
    }
    rep(i,1,N+1) rep(j,1,M+1) {
        if (grid[i][j]=='S') start=make_tuple(0,i,j);
        if (grid[i][j]=='G') goal=make_tuple(INF,i,j);
    }
    // 移動時間メモ初期化
    rep(i,0,1010) rep(j,0,1010) {
        memo[i][j]=INF;
    }
    // ダイクストラでゴールへの最短時間を出す
    ans=dijkstra(start);
    if (ans==INF) {
        ans=-1;
    }
    cout<<ans<<endl;
    return 0;
}
