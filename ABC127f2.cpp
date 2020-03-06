/**
 * 参考：https://img.atcoder.jp/abc127/editorial.pdf
 * ・2つのmultisetで前半と後半を分けて管理させると、中央値が常に取り出せる。
 * ・反対側へ移す時の処理順でハマってた。。
 * ・あと、multisetの要素削除eraseでitrを引数にすれば単一要素削除になるけど、
 * 　要素を引数にすると、そのキーの要素全部消えるから注意。(考えたらそれはそう)
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<ll, int> pli;
typedef pair<int, int> pii;
typedef pair<pii, ll> ppiil;
typedef pair<pii, int> ppiii;
typedef vector<vector<ll>> vvl;
typedef vector<vector<int>> vvi;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define btoe(obj) (obj).begin(), (obj).end()
#define pb push_back
#define str to_string
#define mkp make_pair
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

template<typename T>
void print(set<T> S) {
    vector<T> A(btoe(S));
    print(A);
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

ll sum(ll A[], int len) {
    ll res = 0;
    rep(i, 0, len) res += A[i];
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

ll toint(string s) {
    ll res = 0;
    for (char c : s) {
        res *= 10;
        res += (c - '0');
    }
    return res;
}

int toint(char c) {
    return c - '0';
}

ll Q, tp, a, b, l, r, mid, asum, bsum, ln;
multiset<ll> S1, S2;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> Q;
    cin >> tp >> a >> b;

    mid = a;
    asum = 0;
    bsum = b;
    ln = 1;
    S1.insert(a);

    rep(_, 1, Q) {
        cin >> tp;
        if (tp == 1) {
            cin >> a >> b;
            bsum += b;
            l = *(--S1.end());
            r = *S2.begin();
            if (ln % 2 == 1) {
                asum += abs(a - l);
                if (a < mid) {
                    S1.insert(a);
                    // 今回の要素を入れてから、その中での最大値を大きい方へ移す
                    S2.insert(*(--S1.end()));
                    S1.erase(--S1.end());
                } else {
                    S2.insert(a);
                }
            } else {
                if (a < l) {
                    asum += abs(a - l);
                } else if (a > r) {
                    asum += abs(a - r);
                }
                if (a > mid) {
                    S2.insert(a);
                    // 今回の要素を入れてから、その中での最小値を小さい方へ移す
                    S1.insert(*S2.begin());
                    S2.erase(S2.begin());
                } else {
                    S1.insert(a);
                }
            }
            ln++;
            mid = *prev(S1.end());
        } else {
            print(mkp(mid, asum + bsum));
        }
    }
    return 0;
}
