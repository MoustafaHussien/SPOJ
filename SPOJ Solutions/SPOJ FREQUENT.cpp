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
		int best, pre, preNum, suf, sufNum;
	};
	node combine(node l, node r) {
		node n;
		//--------------update the best----------
		if (l.best >= r.best)
			n.best = l.best;
		if (l.best < r.best)
			n.best = r.best;
		if ((l.sufNum == r.preNum) && (l.suf + r.pre) > n.best)
			n.best = (l.suf + r.pre);
		//--------------update prefix--------------
		if (l.preNum == r.preNum)
			n.preNum = l.preNum, n.pre = (l.pre + r.pre);
		else
			n.preNum = l.preNum, n.pre = l.pre;
		//--------------update sufix---------------
		if (l.sufNum == r.sufNum)
			n.sufNum = l.sufNum, n.suf = (l.suf + r.suf);
		else
			n.sufNum = r.sufNum, n.suf = r.suf;
		//------------------------------------------
		return n;
	}

	node tree[600000];
	int values[600000];
	int i, j;
	void build(int node, int a, int b) {
		if (a > b)
			return; // Out of range
		if (a == b) { // Leaf node
			tree[node].preNum = tree[node].sufNum = values[a];
			tree[node].best = tree[node].pre = tree[node].suf = 1;
			return;
		}
		build(node * 2, a, (a + b) / 2);
		build(node * 2 + 1, 1 + (a + b) / 2, b);
		tree[node] = combine(tree[node * 2], tree[node * 2 + 1]);
	}
	node query(int v, int a, int b) {
		if (a > b || a > j || b < i) {
			node temp;
			temp.preNum = -1, temp.sufNum = -2;
			temp.best = temp.pre = temp.suf = -999999999;
//			cout << "here\n";
			return temp; // Out of range
		}
		if (a >= i && b <= j) // Current segment is totally within range [i, j]
			return tree[v];
		return combine(query(v * 2, a, (a + b) / 2),
				query(1 + (v * 2), 1 + (a + b) / 2, b));
	}
	void print(int i) {
		cout << "node " << i << " = ";
		cout << "[" << tree[i].best << " " << tree[i].preNum << " ";
		cout << tree[i].pre << " " << tree[i].sufNum << " ";
		cout << tree[i].suf << " ]" << endl;
	}
};
//----------------------------------------------------------------
int main(int argc, char **argv) {
//	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	int n, m, x;
	while (true) {
		scanf("%d", &n);
		if (n == 0)
			return 0;
		scanf("%d", &m);
		segment_tree *t = new segment_tree();
		for (int i = 1; i <= n; i++) {
			scanf("%d", &x);
			t->values[i] = x;
		}
		t->build(1, 1, n);
		int idx, val;
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &idx, &val);
			t->i = idx, t->j = val;
			printf("%d\n", t->query(1, 1, n).best);
		}
	}
	return 0;
}
