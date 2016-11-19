#include<bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define F first
#define S second
#define MOD 1000000007
#define ZERO 1e-9
using namespace std;
//----------------------------------------------------------------
class segment_tree {
public:
	vector<int> tree; //number of on lights
	vector<bool> lazy;
	int n, i, j;
	void build() {
		for (int k = 0; k <= (4 * n); k++)
			tree.push_back(0), lazy.push_back(false);
	}

	void update(int node, int st, int en) {
		if (lazy[node]) {
			lazy[node] = false;
			tree[node] = en - st + 1 - tree[node];
			if (st != en) {
				lazy[node << 1] = !lazy[node << 1];
				lazy[1 + (node << 1)] = !lazy[1 + (node << 1)];
			}
		}
		if (i > en || j < st)
			return;
		if (i <= st && en <= j) {
			tree[node] = en - st + 1 - tree[node];
			if (st != en) {
				lazy[node << 1] = !lazy[node << 1];
				lazy[1 + (node << 1)] = !lazy[1 + (node << 1)];
			}
			return;
		}
		int mid = (st + en) / 2;
		update((node << 1), st, mid);
		update((node << 1) + 1, mid + 1, en);
		if (st != en)
			tree[node] = tree[node << 1] + tree[(node << 1) + 1];
	}
	int query(int node, int st, int en) {
		if (i > en || j < st)
			return 0;
		if (lazy[node]) {
			lazy[node] = false;
			tree[node] = en - st + 1 - tree[node];
			if (st != en) {
				lazy[node << 1] = !lazy[node << 1];
				lazy[(node << 1) + 1] = !lazy[(node << 1) + 1];
			}
		}
		if (i <= st && en <= j) {
			return tree[node];
		}
		int mid = (st + en) / 2;
		return query((node << 1), st, mid) + query((node << 1) + 1, mid + 1, en);
	}
};
//----------------------------------------------------------------
int main(int argc, char **argv) {
	freopen("input.txt", "r", stdin);
	int n, m, op, s, e;
	scanf("%d %d", &n, &m);
	segment_tree t;
	t.n = n;
	t.build();
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &op, &s, &e);
		t.i = s, t.j = e;
		if (op == 1) {
			printf("%d\n", t.query(1, 1, n));
		} else
			t.update(1, 1, n);
	}
	return 0;
}
