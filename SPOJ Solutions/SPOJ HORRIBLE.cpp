#include<bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define F first
#define S second
#define MOD 1000000007
#define ZERO 1e-9
using namespace std;
using namespace std;
class segment_tree {
public:
	struct node {
		long long sum, lazy;
	};
	node t[500000];
	void build(int y) {
		for (int i = 0; i <= (4 * y); i++)
			t[i].sum = 0, t[i].lazy = 0;
	}
	void fix(int n, int s, int e) {
		t[n << 1].lazy += t[n].lazy;
		t[(n << 1) + 1].lazy += t[n].lazy;
		t[n].sum += t[n].lazy * (e - s + 1);
		t[n].lazy = 0;
	}
	void update(int n, int s, int e, int i, int j, int v) {
		if (s == i && e == j) {
			t[n].lazy += v;
			fix(n, s, e);
			return;
		}
		int left = n << 1;
		int right = left + 1;
		int mid = (s + e) >> 1;
		if (t[n].lazy != 0)
			fix(n, s, e);
		if (j <= mid) {
			update(left, s, mid, i, j, v);
		} else if (i > mid) {
			update(right, mid + 1, e, i, j, v);
		} else {
			update(left, s, mid, i, mid, v);
			update(right, mid + 1, e, mid + 1, j, v);
		}
		fix(left, s, mid);
		fix(right, mid + 1, e);
		t[n].sum = t[left].sum + t[right].sum;
	}
	long long query(int n, int s, int e, int i, int j) {
		if (s == i && e == j) {
			fix(n, s, e);
			return t[n].sum;
		}
		int left = n << 1;
		int right = left + 1;
		int mid = (s + e) >> 1;
		if (t[n].lazy != 0)
			fix(n, s, e);
		if (j <= mid)
			return query(left, s, mid, i, j);
		if (i > mid)
			return query(right, mid + 1, e, i, j);
		return query(left, s, mid, i, mid)
				+ query(right, mid + 1, e, mid + 1, j);
	}
};
int main() {
	int tc, n, c, s, q, p, v;
	scanf("%d", &tc);
	segment_tree *t = new segment_tree();
	while (tc--) {
		scanf("%d%d", &n, &c);
		t->build(n);
		for (int i = 0; i < c; i++) {
			scanf("%d%d%d", &s, &q, &p);
			if (s == 0) {
				scanf("%d", &v);
				t->update(1, 1, n, q, p, v);
			} else {
				printf("%lld\n", t->query(1, 1, n, q, p));
			}
		}
	}
	return 0;
}
