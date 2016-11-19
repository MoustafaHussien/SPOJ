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
	struct node {
		long long sum, suf, pre, best;
	};
	node combine(node l, node r) {
		node temp;
		temp.sum = l.sum + r.sum;
		temp.suf = max(r.suf, r.sum + l.suf);
		temp.pre = max(l.pre, l.sum + r.pre);
		temp.best = max(l.best, max(r.best, r.pre + l.suf));
		return temp;
	}

	node tree[600000];
	int values[600000];
	int i, j;
	void build(int node, int a, int b) {
		if (a > b)
			return; // Out of range
		if (a == b) { // Leaf node
			tree[node].sum = tree[node].pre = values[a];
			tree[node].suf = tree[node].best = values[a];
			return;
		}
		build(node * 2, a, (a + b) / 2);
		build(node * 2 + 1, 1 + (a + b) / 2, b);
		tree[node] = combine(tree[node * 2], tree[node * 2 + 1]);
	}
	void update(int node, int a, int b, int idx, int val) {
		if (idx < a || idx > b || a > b)
			return;
		if (a == b) {
			tree[node].sum = tree[node].pre = val;
			tree[node].suf = tree[node].best = val;
			return;
		}
		update(node * 2, a, (a + b) / 2, idx, val);
		update(node * 2 + 1, (a + b) / 2 + 1, b, idx, val);
		tree[node] = combine(tree[node * 2], tree[node * 2 + 1]);
	}

	node query(int v, int a, int b) {
		if (a > b || a > j || b < i) {
			node temp;
			temp.pre = temp.suf = temp.sum = temp.best = -6000000000;
			return temp; // Out of range
		}
		if (a >= i && b <= j) // Current segment is totally within range [i, j]
			return tree[v];
		return combine(query(v * 2, a, (a + b) / 2),
				query(1 + (v * 2), 1 + (a + b) / 2, b));
	}
};
//----------------------------------------------------------------
int main(int argc, char **argv) {
	freopen("input.txt", "r", stdin);
	int n, x;
	cin >> n;
	segment_tree *t = new segment_tree();
	for (int i = 1; i <= n; i++) {
		cin >> x;
		t->values[i] = x;
	}
	t->build(1, 1, n);
	int m, idx, val, p;
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> p >> idx >> val;
		if (p == 0) {
			t->update(1, 1, n, idx, val);
		} else {
			t->i = idx, t->j = val;
			cout << t->query(1, 1, n).best << endl;
		}
	}
	return 0;
}
