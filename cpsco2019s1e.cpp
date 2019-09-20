/**
 * 参考：https://img.atcoder.jp/cpsco2019-s1/editorial.pdf
 * ・とりあえず解説だけ見て自力実装、WA。
 * ・まあイテレータの挙動とか勉強にはなったからOK。
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
    ll a, l, r, x, cnt, ans;
    set<ll> st;

    cin >> N >> Q;
    rep(i, 0, N) {
        cin >> a;
        auto res = st.insert(a);
        // 既にaが入っていたら削除(xorは重複したら消えるから)
        if (!res.second) st.erase(res.first);
    }

    ll A[Q];
    rep(i, 0, Q) {
        cin >> l >> r >> x;
        cnt = 0;
        ans = 0;
        auto res = st.insert(l);
        // lが入っていなかったら、数えたくないので先に帳尻を合わせておく
        if (res.second) {
            cnt--;
            ans ^= l;
        }
        res = st.insert(r);
        if (res.second) {
            cnt--;
            ans ^= r;
        }
        // lとrのイテレータを取得(開区間なのでrは1つ進める)
        auto s = st.find(l);
        auto t = st.find(r);
        t = next(t);
        // 該当区間の要素を全て削除しながら、カウントとxorを取っていく
        for (auto itr=s; itr!=t;) {
            // *itrでイテレータが差す値
            ans ^= *itr;
            cnt++;
            // 戻り値が次要素のイテレータ
            itr = st.erase(itr);
        }
        // 削除した要素数が奇数個なら、xを追加
        if (cnt%2 == 1) st.insert(x);
        A[i] = ans;
    }
    // 各xorの結果を出力
    rep(i, 0, Q) print(A[i]);
    return 0;
}
