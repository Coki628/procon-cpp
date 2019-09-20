#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define foreach(c, iter) for(auto iter=(c).begin(); iter!=(c).end(); iter++)
#define all(obj) (obj).begin(), (obj).end()
const ll INF = 1e18;
const ll MOD = 1e9 + 7;
void chmax(ll &a, ll b) { a = max(a, b); }
void chmin(ll &a, ll b) { a = min(a, b); }

unordered_map<string, ll> memo; 

int main() {
	memo[to_string(4321)+","+to_string(1234)] = 789;
	cout << memo["4442524321,12254525434"] << endl;
	cout << memo["4321,1234"] << endl;
	return 0;
}
