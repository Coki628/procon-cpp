// 一発全インクルード
#include <bits/stdc++.h>
using namespace std;

// どっちででもいいみたい
typedef long long ll;
using ll = long long;

// 高速化っぽい
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);

vector<int> A;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    // 降順ソート   
    sort(A.rbegin(), A.rend());
    // 最大値
    ll INF = LONG_LONG_MAX;
    cout << INF << endl;

    // 重複削除(案外めんどい)
    sort(A.begin(), A.end());
    A.erase(unique(A.begin(), A.end()), A.end());

    // 型が決まってれば、ペアもこれで入る
    pair<int, int> p;
    p = {2, 4};
    // mapもこんな感じ
    map<int, int> m;
    m = {{123, 12}, {32, 14}};
    int a, b;
    for (auto p : m) {
        // あとペア分解する時これでいける
        tie(a, b) = p;
    }
    // タプルでも。これ3要素以上の扱い楽になりそう
    tuple<int, int, int> tpl;
    int c;
    tpl = {1, 3, 4};
    tie(a, b, c) = tpl;

    // 累積和の先頭に0
    vector<ll> acc;
    acc.insert(acc.begin(), 0);

    // min,maxのラムダ
    // [](ll a, ll b) { return min(a, b); }
    // [](ll a, ll b) { return max(a, b); }
    // 大小比較関数
    // less_equal<ll>()
    // greater_equal<ll>()

    // vector -> set
    // unordered_set<ll> S(A.begin(), A.end());

    // c++17からはこう書ける
    vector<pair<ll, ll>> AB;
    for (auto &[a, b] : AB) {
    }

    // substrは右端じゃなくて文字数渡す。多すぎたらよしなに切ってくれるぽい。
    string s = "test";
    string t = s.substr(1, 10);
    cout << t << endl;

    // llでもldでも、その型の最大値が取れる
    ll mx = numeric_limits<ll>::max();

    // main内での再帰の書き方
    // auto dfs = [&](auto&& f, ll u, ll prev) -> void {
    //     for (auto v : nodes[u]) {
    //         if (v == prev) continue;
    //         f(f, v, u);
    //     }
    //     return;
    // };
    // dfs(dfs, 0, -1);

    // 3次元これでいけるみたいだ。
    ll N, M, L;
    vector N(M, vector(L, 0));

    return 0;
}
