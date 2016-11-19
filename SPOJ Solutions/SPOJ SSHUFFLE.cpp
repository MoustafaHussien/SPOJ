#include<bits/stdc++.h>
using namespace std;
string s1, s2, s3;
long long dp[60][60][60];
long long solve(int i, int j, int k) {
	if (k == (int) s3.size())
		return 1;
	if (i == (int) s1.size() && j == (int) s2.size())
		return 0;
	if (dp[i][j][k] != -1)
		return dp[i][j][k];
	long long ret;
	ret = 0;
	for (int x = i; x < (int) s1.size(); ++x)
		if (s1[x] == s3[k])
			ret += solve(x + 1, j, k + 1);
	for (int x = j; x < (int) s2.size(); ++x)
		if (s2[x] == s3[k])
			ret += solve(i, x + 1, k + 1);
	return dp[i][j][k] = ret;
}
int main() {
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	while (t--) {
		cin >> s1 >> s2 >> s3;
		memset(dp, -1, sizeof dp);
		cout << solve(0, 0, 0) << endl;
	}
}
