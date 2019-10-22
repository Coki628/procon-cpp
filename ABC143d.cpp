/**
 * ・愚直+枝刈り解法。
 * ・枝刈りなしだと普通にTLEで、枝刈りしてもまだ1ケースだけTLEで、
 * 　そこからa,bへの添字アクセスを外ループで取るようにしたらAC。
 * ・AC1.8秒。計算量はN^3/6=約13億-枝刈り分。これ通るC++やっぱやばい。
 * ・あまり望まれる解法じゃないだろうけど、これで通るなら参戦中枝刈り検討すればよかったな。。
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

template<typename Any>
void print(Any out) {
    cout << out << '\n';
}

void print(vector<ll> A) {
    rep(i, 0, A.size()) {
        cout << A[i];
        cout << (i == A.size()-1 ? '\n' : ' ');
    }
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

int N, a, b, c;
ll cnt;
vector<int> A;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    rep(i, 0, N) cin >> A[i];
    cnt = 0;
    sort(all(A));

    rep(i, 0, N) {
        a = A[i];
        rep(j, i+1, N) {
            b = A[j];
            rep(k, j+1, N) {
                c = A[k];
                // 枝刈り
                if (c >= a + b) break;
                if (a < b + c && b < c + a && c < a + b) {
                    cnt++;
                }
            }
        }
    }

    print(cnt);
    return 0;
}
