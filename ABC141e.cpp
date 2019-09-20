/**
 * ・二分探索
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

int N;
string S;

bool calc(ll m) {
    string a;
    string b;
    rep(i, 0, N-m*2+1) {
        a = S.substr(i, m);
        rep(j, i+m, N-m+1) {
            b = S.substr(j, m);
            if (a == b) {
                return true;
            }
        }
    }
    return false;
}

ll bisearch_max(ll mn, ll mx) {
    ll ok = mn;
    ll ng = mx;
    ll mid;
    while (ok+1 < ng) {
        mid = (ok+ng) / 2;
        if (calc(mid)) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    return ok;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    cin >> S;
    print(bisearch_max(0, N));
    return 0;
}
