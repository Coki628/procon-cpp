/**
 * ・試行錯誤の末AC。。
 * ・次の障害物の位置も保持するけど、訪問済の行と列の情報も持っておく。
 * ・後者は動的に変化するので、setに入れて二分探索、を繰り返す。
 * ・C++はset,mapでこれが出来るのは本当に強い。
 * ・細かい境界とか、行列どっちとか色々バグっててACするの大変だった。。
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
// #define print(out) cout << (out) << endl
const ll INF = 1e18;
const ll MOD = 1e9 + 7;
void chmax(ll &a, ll b) { a = max(a, b); }
void chmin(ll &a, ll b) { a = min(a, b); }

template<typename T>
void print(T out) {
    cout << out << '\n';
}

void print(vector<ll> A) {
    rep(i, 0, A.size()) {
        cout << A[i];
        cout << (i == A.size()-1 ? '\n' : ' ');
    }
}

template<typename T1, typename T2>
void print(pair<T1, T2> out) {
    cout << out.first << ' ' << out.second << '\n';
}

ll max(vector<ll> A) {
    ll res = -INF;
    for (ll a: A) chmax(res, a);
    return res;
}

ll min(vector<ll> A) {
    ll res = INF;
    for (ll a: A) chmin(res, a);
    return res;
}

ll max(ll A[], int len) {
    ll res = -INF;
    rep(i, 0, len) chmax(res, A[i]);
    return res;
}

ll min(ll A[], int len) {
    ll res = INF;
    rep(i, 0, len) chmin(res, A[i]);
    return res;
}

int r, c, idx, nxt1, nxt2, nxt;
ll H, W, K, cnt;
vvi rows, cols;
pii cur;
set<int> visitedr, visitedc;

bool right() {
    r = cur.first;
    c = cur.second;
    // 次の障害物の位置
    idx = lower_bound(all(rows[r]), c+1) - rows[r].begin();
    // その手前まで進める
    nxt1 = rows[r][idx] - 1;
    // 次の訪問済位置
    auto itr = visitedc.lower_bound(c+1);
    // その手前まで進める
    nxt2 = *itr - 1;
    // どちらか近い方
    nxt = min(nxt1, nxt2);
    // 動けなかったら終了
    if (nxt <= c) {
        return false;
    } else {
        cnt += nxt - c;
        cur.second = nxt;
        visitedr.insert(r);
        return true;
    }
}

bool down() {
    r = cur.first;
    c = cur.second;
    idx = lower_bound(all(cols[c]), r+1) - cols[c].begin();
    nxt1 = cols[c][idx] - 1;
    auto itr = visitedr.lower_bound(r+1);
    nxt2 = *itr - 1;
    nxt = min(nxt1, nxt2);
    if (nxt <= r) {
        return false;
    } else {
        cnt += nxt - r;
        cur.first = nxt;
        visitedc.insert(c);
        return true;
    }
}

bool left() {
    r = cur.first;
    c = cur.second;
    idx = upper_bound(all(rows[r]), c-1) - rows[r].begin() - 1;
    nxt1 = rows[r][idx] + 1;
    auto itr = prev(visitedc.upper_bound(c-1));
    nxt2 = *itr + 1;
    nxt = max(nxt1, nxt2);
    if (nxt >= c) {
        return false;
    } else {
        cnt += c - nxt;
        cur.second = nxt;
        visitedr.insert(r);
        return true;
    }
}

bool up() {
    r = cur.first;
    c = cur.second;
    idx = upper_bound(all(cols[c]), r-1) - cols[c].begin() - 1;
    nxt1 = cols[c][idx] + 1;
    auto itr = prev(visitedr.upper_bound(r-1));
    nxt2 = *itr + 1;
    nxt = max(nxt1, nxt2);
    if (nxt >= r) {
        return false;
    } else {
        cnt += r - nxt;
        cur.first = nxt;
        visitedc.insert(c);
        return true;
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> H >> W >> K;
    rows.resize(H);
    cols.resize(W);
    cur = mkp(0, 0);
    cnt = 1;
    rep(i, 0, K) {
        cin >> r >> c;
        r--;
        c--;
        // 障害物の座標を、行列毎に隣接リストっぽく持たせる
        rows[r].pb(c);
        cols[c].pb(r);
    }
    rep(i, 0, H) {
        // 前後に番兵を入れると、この後二分探索で管理がしやすい
        rows[i].pb(-1);
        rows[i].pb(W);
        sort(all(rows[i]));
    }
    rep(i, 0, W) {
        cols[i].pb(-1);
        cols[i].pb(H);
        sort(all(cols[i]));
    }
    visitedr.insert(-1);
    visitedr.insert(H);
    visitedc.insert(-1);
    visitedc.insert(W);

    // 最初に下に行く例外処理
    down();
    if (cnt == H*W-K) {
        print("Yes");
        return 0;
    } else {
        cur = mkp(0, 0);
        cnt = 1;
        visitedc.clear();
        visitedc.insert(-1);
        visitedc.insert(W);
    }

    // 普通に右から時計回りしていくシミュレーション
    while (true) {
        if (!right()) break;
        if (!down()) break;
        if (!left()) break;
        if (!up()) break;
    }

    // 踏破したマス数 == 全体 - 障害物 ならOK
    if (cnt == H*W-K) {
        print("Yes");
    } else {
        print("No");
    }
    return 0;
}
