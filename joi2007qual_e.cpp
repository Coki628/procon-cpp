/**
 * ・蟻本演習3-2-4
 * ・反転(ライツアウト)、ビット演算
 * ・これは行列勘違いしてるやつなのでTLE。
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<ll, int, int> tlii;
typedef pair<ll, ll> pll;
typedef pair<ll, int> pli;
typedef pair<int, int> pii;
typedef pair<pair<int, int>, ll> ppiil;
typedef vector<vector<ll>> vvl;
typedef vector<vector<int>> vvi;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define all(obj) (obj).begin(), (obj).end()
#define pb push_back
#define str to_string
#define mkp make_pair
#define mkt make_tuple
const ll INF = 1e18;
const ll MOD = 1e9 + 7;
void chmax(ll &a, ll b) { a = max(a, b); }
void chmin(ll &a, ll b) { a = min(a, b); }

template<typename T>
void print(T out) {
    cout << out << '\n';
}

template<typename T1, typename T2>
void print(pair<T1, T2> out) {
    cout << out.first << ' ' << out.second << '\n';
}

template<typename T>
void print(vector<T> A) {
    rep(i, 0, A.size()) {
        cout << A[i];
        cout << (i == A.size()-1 ? '\n' : ' ');
    }
}

ll sum(vector<ll> A) {
    ll res = 0;
    for (ll a: A) res += a;
    return res;
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

ll bit_count(ll i) {
    i = i - ((i >> 1) & 0x55555555);
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
    i = (i + (i >> 4)) & 0x0f0f0f0f;
    i = i + (i >> 8);
    i = i + (i >> 16);
    return i & 0x3f;
}

int R, C;
ll org, change, cnt, ans, sm;
vector<ll> grid;
vector<int> tmp;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> R >> C;
    tmp.resize(C);
    grid.resize(R-1);
    rep(i, 0, C) cin >> tmp[i];
    reverse(all(tmp));
    rep(i, 0, C) {
        if (tmp[i]) {
            org += 1 << i;
        }
    }
    // 各行をビットで持つ
    rep(i, 0, R-1) {
        rep(j, 0, C) {
            cin >> tmp[j];
        }
        reverse(all(tmp));
        rep(j, 0, C) {
            if (tmp[j]) {
                grid[i] += 1 << j;
            }
        }
    }

    ans = 0;
    // 1行目を全通り試す
    rep(row1, 0, 1<<C) {
        cnt = bit_count(row1);
        // 行は単体で自由に切り替えられるので、反転と比較して大きい方を使う
        sm = max(cnt, C-cnt);
        change = org ^ row1;
        rep(i, 0, R-1) {
            // 決め打ちした1行目と同じ変更を、他の行にも適用する
            cnt = bit_count(grid[i] ^ change);
            sm += max(cnt, C-cnt);
        }
        ans = max(ans, sm);
    }

    print(ans);
    return 0;
}
