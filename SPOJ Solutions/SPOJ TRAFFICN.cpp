#include<bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define F first
#define S second
#define MOD 1000000007
#define ZERO 1e-9
using namespace std;
struct n {
	int i, d;bool b;
	n(int x, int c, bool flag) {
		i = x, d = c, b = flag;
	}
	bool operator <(const n &s) const {
		return d > s.d;
	}
};
int s, dist[11000][2];
vector<vector<pair<int, int> > > v1(10100), v2(10100);
void dijkstra() {
	priority_queue<n> q;
	dist[s][0] = dist[s][1] = 0;
	n t(s, 0, 0);
	q.push(t);
	while (!q.empty()) {
		n a = q.top();
		q.pop();
		if (a.d == dist[a.i][a.b]) {
			for (int i = 0; i < (int) v1[a.i].size(); i++) {
				if (dist[v1[a.i][i].first][a.b] > a.d + v1[a.i][i].second) {
					dist[v1[a.i][i].first][a.b] = a.d + v1[a.i][i].second;
					n x(v1[a.i][i].first, dist[v1[a.i][i].first][a.b], a.b);
					q.push(x);
				}
			}
			if (a.b == false) {
				for (int i = 0; i < (int) v2[a.i].size(); i++) {
					if (dist[v2[a.i][i].first][1] > a.d + v2[a.i][i].second) {
						dist[v2[a.i][i].first][1] = a.d + v2[a.i][i].second;
						n x(v2[a.i][i].first, dist[v2[a.i][i].first][1], true);
						q.push(x);
					}
				}
			}
		}
	}
}
int main(int argc, char **argv) {
	int tc, n, m, k, t, d, c, l;
	scanf("%d", &tc);
	while (tc--) {
		memset(dist, 127, sizeof(dist));
		scanf("%d%d%d%d%d", &n, &m, &k, &s, &t);
		for (int i = 0; i <= n; i++) {
			v1[i].clear();
			v2[i].clear();
		}
		for (int i = 0; i < m; i++) {
			scanf("%d%d%d", &d, &c, &l);
			v1[d].push_back(make_pair(c, l));
		}
		for (int i = 0; i < k; i++) {
			scanf("%d%d%d", &d, &c, &l);
			v2[d].push_back(make_pair(c, l));
			v2[c].push_back(make_pair(d, l));
		}
		dijkstra();
		int ans = min(dist[t][0], dist[t][1]);
		if (ans == dist[10100][0])
			printf("-1\n");
		else
			printf("%d\n", ans);
	}
	return 0;
}
