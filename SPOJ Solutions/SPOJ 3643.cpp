//============================================================================
// Name        : SPOJ.cpp
// Author      : moustafa
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <queue>
#include <tuple>
#include <math.h>
using namespace std;
int n, m, k, a, b, c, d;
int dist[2][10010];
vector<vector<pair<int, int> > > city[2];
vector<tuple<int, int, int> > roads;
class CompareDist {
public:
	bool operator()(pair<int, int> n1, pair<int, int> n2) {

		if (n1.second > n2.second)
			return true;
		else
			return false;

	}
};

void dijkstra(int n, int s) {
	priority_queue<pair<int, int>, vector<pair<int, int> >, CompareDist> pq;
	pq.push(make_pair(s, 0));
	dist[n][s] = 0;
	while (!pq.empty()) {
		pair<int, int> u;
		u = pq.top();
		pq.pop();
		if (u.second != dist[n][u.first])
			continue;

		vector<pair<int, int> > e;
		e = city[n][u.first];
		for (int i = 0; i < e.size(); i++) {
			pair<int, int> v = e[i];
			if (dist[n][u.first] + v.second < dist[n][v.first]) {
				dist[n][v.first] = dist[n][u.first] + v.second;
				pq.push(make_pair(v.first, dist[n][v.first]));
			}
		}
	}
}

int main() {
	int tc, s, t;
	scanf("%d", &tc);
	for (int i = 0; i < 10110; i++) {
		vector<pair<int, int> > temp;
		city[0].push_back(temp);
		city[1].push_back(temp);
	}
	while (tc--) {
		scanf("%d %d %d %d %d", &n, &m, &k, &s, &t);
		for (int i = 0; i < (n + 2) && i < (k + 2); i++) {
			city[i].clear();
			roads.clear();
		}
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &a, &b, &c);
			city[0][a].push_back(make_pair(b, c));
			city[1][b].push_back(make_pair(a, c));
		}
		memset(dist, 127, sizeof(dist));
		for (int j = 0; j < k; j++) {
			scanf("%d %d %d", &a, &b, &c);
			tuple<int, int, int> x;
			get<0>(x) = a;
			get<1>(x) = b;
			get<2>(x) = c;
			roads.push_back(x);
		}
		dijkstra(0, s);
		dijkstra(1, t);
		int x, y;
		int ans = 2139062140;
		for (int i = 0; i < k; i++) {
			y = 2139062140;
			x = 2139062140;
			if (dist[0][get<0>(roads[i])] < dist[0][10009]
					&& dist[1][get<1>(roads[i])] < dist[0][10009]) {
				x = dist[0][get<0>(roads[i])] + get<2>(roads[i])
						+ dist[1][get<1>(roads[i])];
			}
			if (dist[1][get<0>(roads[i])] < dist[0][10009]
					&& dist[1][get<1>(roads[i])] < dist[0][10009]) {
				y = dist[0][get<1>(roads[i])] + get<2>(roads[i])
						+ dist[1][get<0>(roads[i])];
			}

			ans = min(ans, min(x, y));
		}
		if (ans == 2139062140) {
			printf("-1\n");
		} else {
			printf("%d\n", ans);
		}
	}
	return 0;
}

