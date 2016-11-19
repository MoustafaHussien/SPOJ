#include<bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define F first
#define S second
#define MOD 1000000007
#define ZERO 1e-9
#define MAX 5000000
using namespace std;
int g[153][153], n;
int ans[153][153][153];
vector<int> p;
void floyd() {
	memset(ans, 127, sizeof(ans));
	for (int i = 0; i <= 151; i++)
		for (int j = 0; j <= 151; j++)
			ans[i][j][0] = g[i][j];
	for (int k = 0; k < (int) p.size(); k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) {
				g[i][j] = min(g[i][j], g[i][p[k]] + g[p[k]][j]);
				ans[i][j][k + 1] = min(ans[i][j][k + 1], g[i][j]);
			}
}
void fill() {
	memset(g, 1, sizeof(g));
	for (int i = 0; i < 151; i++){
		g[i][i] = 0;
	}
}
int main() {
//	freopen("input.txt", "r", stdin);
	int tc, a, count, k, s, t;
	scanf("%d", &tc);
	for (int m = 1; m <= tc; m++) {
		scanf("%d", &n);
		fill();
		for (int i = 1; i < n; i++) {
			count = i + 1;
			while (count <= n) {
				scanf("%d", &a);
				if (a != -1) {
					g[i][count] = g[count][i] = a;
				}
				count++;
			}
		}
		scanf("%d", &s);
		p.clear();
		for (int i = 1; i <= s; i++) {
			scanf("%d", &a);
			p.push_back(a);
		}
		floyd();
		scanf("%d", &a);
		printf("Case %d:", m);
		for (int i = 1; i <= a; i++) {
			scanf("%d %d %d", &k, &s, &t);
			if (ans[s][t][k] != g[152][152])
				printf(" %d", ans[s][t][k]);
			else
				printf(" -1");
		}
		printf("\n");
	}
	return 0;
}
