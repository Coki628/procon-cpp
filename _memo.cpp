// 一発全インクルード
#include <bits/stdc++.h>
using namespace std;

// どっちででもいいみたい
typedef long long ll;
using ll = long long;

// 高速化っぽい
#define fast  ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);

vector<int> A;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    // 降順ソート
    sort(A.rbegin(), A.rend());
    // 最大値
    ll INF = LONG_LONG_MAX;
    cout << INF << endl;

    return 0;
}
