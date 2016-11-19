#include<bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define F first
#define S second
long long MOD = 1000000007;
#define ZERO 1e-9
using namespace std;
#define MAX_N 9000000
char t[MAX_N], p[MAX_N];
int b[MAX_N], n, m;
void kmppreprocess() {
	int i = 0, j = -1;
	b[0] = -1;
	while (i < m) {
		while (j >= 0 && p[i] != p[j])
			j = b[j];
		i++, j++;
		b[i] = j;
	}
}
void kmpSearch() {
	kmppreprocess();
	int i = 0, j = 0;
	while (i < n) {
		while (j >= 0 && t[i] != p[j])
			j = b[j];
		i++;
		j++;
		if (j == m) {
			printf("%d\n", i - j);
			j = b[j];
		}
	}
}
int main(int argc, char **argv) {
	bool line = 0;
//	freopen("input.txt", "r", stdin);
	while (scanf("%d", &m) != EOF) {
		scanf("%s", p);
		scanf("%s", t);
		n = strlen(t);
		if (line)
			printf("\n");
		line = 1;
		kmpSearch();
	}
	return 0;
}
