#include<bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define F first
#define S second
#define MOD 1000000007
#define len 50000005
#define ZERO 1e-9
using namespace std;
class segment_tree {
public:
	bitset<len> tree;
	int i, j;
	void build() {
		tree.set();
	}
	//1 10 1 5
	void update(int n, int s, int e, int q, int p) {
		if (s == q && e == p) {
			tree[n] = 0;
			return;
		}
		int left = n << 1;
		int right = left + 1;
		int mid = (s + e) >> 1;
		if (p <= mid) {
			update(left, s, mid, q, p);
		} else if (q > mid) {
			update(right, mid + 1, e, q, p);
		} else {
			update(left, s, mid, q, mid);
			update(right, mid + 1, e, mid + 1, p);
		}
		tree[n] = tree[n] && (tree[left] || tree[right]);
	}

	bool query(int v, int a, int b) {
		if (a > b || a > j || b < i) {
			return false;
		}
		if (!tree[v])
			return false;
		if (a >= i && b <= j) // Current segment is totally within range [i, j]
			return tree[v];
		int left = v << 1;
		int right = left + 1;
		int mid = (a + b) >> 1;
		return query(left, a, mid) || query(right, mid + 1, b);
	}
};

int main(int argc, char **argv) {
	int tc, n, a, b;
	int ans;
	cin >> tc;
	vector<pair<int, int> > v;
	segment_tree *t = new segment_tree();
	while (tc--) {
		v.clear(), ans = 0, t->build(), cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> a >> b;
			v.push_back(make_pair(a, b));
		}
		for (int i = n - 1; i > -1; i--) {
			t->i = v[i].first, t->j = v[i].second;
			if (t->query(1, 1, 10000000)) {
				ans++;
				t->update(1, 1, 10000000, v[i].first, v[i].second);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
