/**
 * ・これはTLE。
 * ・多分map使っててlogが乗ってるからだと思う。
 * ・計算量500^3/2=6000万くらい*logだからまあきついか。。
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

template<typename T1, typename T2>
void print(pair<T1, T2> out) {
    cout << out.first << ' ' << out.second << '\n';
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

int N, cnt, res, mx;
string S;
map<int, int> C;
pii ans;

// 最小値になった回数を返す
int check(string S) {
    cnt = 0;
    C.clear();
    for (char c : S) {
        if (c == '(') {
            cnt++;
        } else {
            cnt--;
        }
        C[cnt]++;
    }
    auto itr = C.begin();
    return itr->second;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    cin >> S;
    mx = 0;
    ans = {1, 1};
    if (count(all(S), '(') != count(all(S), ')')) {
        print(mx);
        print(ans);
        return 0;
    }

    rep(i, 0, N) {
        rep(j, i+1, N) {
            swap(S[i], S[j]);
            res = check(S);
            if (res > mx) {
                mx = res;
                ans = {i+1, j+1};
            }
            swap(S[i], S[j]);
        }
    }

    print(mx);
    print(ans);
    return 0;
}
