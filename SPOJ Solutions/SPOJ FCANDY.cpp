#include <bits/stdc++.h>
using namespace std;
//spoj FCANDY
int n, num[200], calo[200], sum[200];
short dp[500000][200];
bool solve(int diff, int i) {
	if (diff > (300))
		return false;
	if (i == n - 1) {
		return dp[diff][n - 1] != -1;
	}
	if (dp[diff][i] != -1) {
		return dp[diff][i];
	}
	bool ans = false;
	for (int j = 0; j <= num[i]; j++) {
		int x = calo[i] * (num[i] - j);
		x = x - calo[i] * j;
		ans = ans | solve(abs(diff - x), i + 1) | solve(abs(diff + x), i + 1);
	}
	return (dp[diff][i] = ans);
}
int main(int argc, char **argv) {
//	freopen("input.txt", "r", stdin);
//	for (int aa = 0; aa < 7; aa++) {
	std::ios_base::sync_with_stdio(false);
	cin >> n;
//		cout<<n<<endl;
	for (int i = 0; i < n; i++) {
		cin >> num[i] >> calo[i];
	}

	memset(dp, -1, sizeof(dp));
	for (int i = 0; i < num[n - 1]; i++) {
		int c = calo[n - 1];
		int b = abs(((c * (num[n - 1] - i)) - c * i));
		if (b < 500000)
			dp[b][n - 1] = 1;
	}

	for (int i = 0; i <= 500; i++) {
		if (solve(i, 0)) {
			printf("%d\n", i);
			break;
		}
	}
//	}
	return 0;
}
