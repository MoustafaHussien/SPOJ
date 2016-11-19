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
		int zeros, ones, twos, lazy;
	};
	node combine(const node & left, const node & right) {
		node temp;
		temp.zeros = left.zeros + right.zeros;
		temp.ones = left.ones + right.ones;
		temp.twos = left.twos + right.twos;
		return temp;
	}
	node tree[600002];
	void pre(int n) {
		for (int i = 0; i <= (4 * n) + 2; i++)
			tree[i].lazy = 0;
	}
	void build(int ind, int segStart, int segEnd) {
		tree[ind].lazy = 0;
		if (segStart == segEnd) {
			tree[ind].zeros = 1;
			tree[ind].ones = tree[ind].twos = tree[ind].lazy = 0;
			return;
		}
		int left = ind << 1;
		int right = left + 1;
		int mid = (segStart + segEnd) / 2;
		build(left, segStart, mid);
		build(right, mid + 1, segEnd);
		tree[ind] = combine(tree[left], tree[right]);
	}

	void fix(int ind) {
		tree[ind].lazy %= 3;
		int a = tree[ind].zeros, b = tree[ind].ones, c = tree[ind].twos;
		if (tree[ind].lazy == 1)
			tree[ind].zeros = c, tree[ind].twos = b, tree[ind].ones = a;
		else if (tree[ind].lazy == 2)
			tree[ind].zeros = b, tree[ind].twos = a, tree[ind].ones = c;
		tree[ind << 1].lazy += tree[ind].lazy;
		tree[(ind << 1) + 1].lazy += tree[ind].lazy;
		tree[ind].lazy = 0;
	}

	void update(int ind, int segStart, int segEnd, int i, int j) {
		if (segStart == i && segEnd == j) {
			tree[ind].lazy += 1;
			fix(ind);
			return;
		}
		int left = ind << 1;
		int right = left + 1;
		int mid = (segStart + segEnd) >> 1;
		if (tree[ind].lazy != 0)
			fix(ind);
		if (j <= mid) {
			update(left, segStart, mid, i, j);
		} else if (i > mid) {
			update(right, mid + 1, segEnd, i, j);
		} else {
			update(left, segStart, mid, i, mid);
			update(right, mid + 1, segEnd, mid + 1, j);
		}
		fix(left);
		fix(right);
		tree[ind] = combine(tree[left], tree[right]);
	}

	int query(int ind, int segStart, int segEnd, int i, int j) {
		if (segStart == i && segEnd == j) {
			fix(ind);
			return tree[ind].zeros;
		}
		int left = ind << 1;
		int right = left + 1;
		int mid = (segStart + segEnd) >> 1;
		if (tree[ind].lazy != 0)
			fix(ind);
		if (j <= mid)
			return query(left, segStart, mid, i, j);
		if (i > mid)
			return query(right, mid + 1, segEnd, i, j);
		return query(left, segStart, mid, i, mid)
				+ query(right, mid + 1, segEnd, mid + 1, j);
	}
};

int main() {
	cin.sync_with_stdio(false);
	int n, q;
	freopen("input.txt", "r", stdin);
	scanf("%d%d", &n, &q);
	segment_tree *t = new segment_tree();
	t->pre(n);
	t->build(1, 1, n);
	int a, b, c;
	while (q--) {
		scanf("%d%d%d", &a, &b, &c);
		b += 1, c += 1;
		if (a == 0) {
			t->update(1, 1, n, b, c);
		} else {
			printf("%d\n", t->query(1, 1, n, b, c));
		}
	}
	return 0;
}
