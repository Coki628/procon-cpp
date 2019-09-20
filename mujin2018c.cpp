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

vector<string> grid;
vector<vector<ll>> L,R,U,D;

int main() {
    int N,M;
    ll cnt,ans;
    string s;
    cin>>N>>M;
    grid.resize(N+2);
    grid[0]=string(M+2,'#');
    grid[N+1]=string(M+2,'#');
    rep(i,1,N+1) {
        cin>>s;
        grid[i]="#"+s+"#";
    }
    // 上下左右にいくつ進めるかを数えておく
    L.resize(N+2);
    rep(i,0,N+2) L[i].resize(M+2);
    rep(i,1,N+1) {
        cnt=0;
        rep(j,1,M+1) {
            if (grid[i][j]=='#') {
                L[i][j]=cnt=0;
            } else if (grid[i][j-1]=='.') {
                cnt+=1; 
                L[i][j]=cnt;
            }
        }
    }
    R.resize(N+2);
    rep(i,0,N+2) R[i].resize(M+2);
    rrep(i,N+1,0) {
        cnt=0;
        rrep(j,M+1,0) {
            if (grid[i][j]=='#') {
                R[i][j]=cnt=0;
            } else if (grid[i][j+1]=='.') {
                cnt+=1; 
                R[i][j]=cnt;
            }
        }
    }
    U.resize(N+2);
    rep(i,0,N+2) U[i].resize(M+2);
    rep(j,1,M+1) {
        cnt=0;
        rep(i,1,N+1) {
            if (grid[i][j]=='#') {
                U[i][j]=cnt=0;
            } else if (grid[i-1][j]=='.') {
                cnt+=1; 
                U[i][j]=cnt;
            }
        }
    }
    D.resize(N+2);
    rep(i,0,N+2) D[i].resize(M+2);
    rrep(j,M+1,0) {
        cnt=0;
        rrep(i,N+1,0) {
            if (grid[i][j]=='#') {
                D[i][j]=cnt=0;
            } else if (grid[i+1][j]=='.') {
                cnt+=1; 
                D[i][j]=cnt;
            }
        }
    }
    ans=0;
    rep(i,1,N+1) rep(j,1,M+1) {
        ans+=(U[i][j]+D[i][j])*(L[i][j]+R[i][j]);
    }
    cout << ans << endl;
    return 0;
}
