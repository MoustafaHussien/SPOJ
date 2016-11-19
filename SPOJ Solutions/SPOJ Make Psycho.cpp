#include <map>
#include <stdio.h>
#include <vector>
#include <string.h>
using namespace std;
map<int, bool> m;
int n, k, z;
void load() {
	m[4] = 1, m[9] = 1, m[16] = 1, m[25] = 1, m[36] = 1, m[49] = 1, m[64] = 1, m[81] =
			1, m[100] = 1, m[121] = 1, m[144] = 1, m[169] = 1, m[180] = 1, m[196] =
			1, m[225] = 1, m[252] = 1, m[256] = 1, m[289] = 1, m[300] = 1, m[324] =
			1, m[361] = 1, m[396] = 1, m[400] = 1, m[441] = 1, m[450] = 1, m[468] =
			1, m[484] = 1, m[529] = 1, m[576] = 1, m[588] = 1, m[612] = 1, m[625] =
			1, m[676] = 1, m[684] = 1, m[700] = 1, m[720] = 1, m[729] = 1, m[784] =
			1, m[828] = 1, m[841] = 1, m[882] = 1, m[900] = 1, m[961] = 1, m[980] =
			1, m[1008] = 1, m[1024] = 1, m[1044] = 1, m[1089] = 1, m[1100] = 1;
}

int main() {
	load();
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &k);
		int j, sum = 0;
		int v[102];
		z = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &j);
			if (m[j]) {
				v[z] = j;
				z++;
				sum += j;
			}
		}
		bool ans[sum + 10];
		for (int i = 0; i < sum + 10; i++) {
			ans[i] = false;
		}
		ans[0] = true;
		for (int i = 0; i < z; i++) {
			for (int h = sum; h >= v[i]; h--) {
				ans[h] |= ans[h - v[i]];
			}
		}
		if (k > sum)
			printf("No\n");
		else if (ans[k])
			printf("Yes\n");
		else
			printf("No\n");
	}

	return 0;
}
