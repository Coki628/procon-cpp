/**
 * ・pypyTLEだったやつ、こっちでAC！でも1.5秒。。
 * ・mapとsetがソート済で使えるのpython使いからすると羨ましいよなー。
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

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int N, Q;
    ll s, t, x, d;
    bool flag;
    map<ll, vector<pair<ll, bool>>> A;
    set<ll> D, S;
    map<ll, ll> B, C;

    cin >> N >> Q;
    rep(i, 0, N) {
        cin >> s >> t >> x;
        // 全ての工事を同じ時系列に持ってくる
        S.insert(s-x);
        S.insert(t-x);
        A[s-x].pb(mkp(x, 0));
        A[t-x].pb(mkp(x, 1));
    }
    rep(i, 0, Q) {
        cin >> d;
        D.insert(d);
        S.insert(d);
    }
    // 人か工事のある箇所だけ見る
    for (ll key: S) {
        // 工事の状態に変化のある時
        if (A.find(key) != A.end()) {
            for (auto p: A[key]) {
                x = p.first;
                flag = p.second;
                // 工事の本来の開始時期毎に値を増減させる
                if (flag == false) {
                    C[x] ++;
                } else {
                    C[x] --;
                }
                if (C[x] == 0) {
                    C.erase(x);
                }
            }
        }
        // 人が出発する時
        if (D.find(key) != D.end()) {
            // この時点で存在する工事の最も早いものを使いたいので、先頭位置を取得
            auto itr = C.begin();
            if (itr != C.end()) {
                B[key] = itr->first;
            } else {
                // 工事が1つもなければその人は止まらない
                B[key] = -1;
            }
        }
    }
    for (ll x: D) {
        print(B[x]);
    }
    return 0;
}
