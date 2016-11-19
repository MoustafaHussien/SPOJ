#include <bits/stdc++.h>
using namespace std;
int n, m;
struct ingredent {
	int x, y, sm, pm, sv, pv;
	// X, 10 <= X <= 100, the amount of the ingredient needed in one serving;
	//  Y, 1 <= Y <= 100, the amount of the ingredient already available in the kitchen;
	//  SM, 1 <= SM < 100, the size of the smaller package at the store;
	// PM, 10 <= PM < 100, the price of the smaller package;
	// SV, SM < SV <= 100, the size of the larger package; and
	// PV, PM < PV <= 100, the price of the larger package
};
vector<ingredent> a;
int getcost(int i, int num) {
	int need = (num * a[i].x) - a[i].y;	//needed amount
	int mymin = 9999999;
	//j is num of small ones used till now
	for (int j = 0; j <= ceil((need * 1.0) / (a[i].sm * 1.0)); j++) {
		int cost = j * a[i].pm;
		if (j * a[i].sm < need) {
			cost += ceil(((need - (j * a[i].sm)) * 1.0 / a[i].sv * 1.0))
					* a[i].pv;
		}
		mymin = min(mymin, cost);
	}
	return mymin;
}

bool can(int num) {
	int temp = m;
	for (int i = 0; i < n; i++) {
		int x = getcost(i, num);
		if (x > temp)
			return false;
		temp -= x;
	}
	return true;
}

int binarySearchTheAnswer() {
	int lo = 0, hi = 100000, mid = 0, ans = 0;
	while (hi - lo > 1) {
		mid = (lo + hi) / 2;
		if (can(mid)) {
			ans = mid;
			lo = mid;
		} else
			hi = mid;
	}
	return ans;
}

int main(int argc, char **argv) {
	ios_base::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		ingredent t;
		cin >> t.x >> t.y >> t.sm >> t.pm >> t.sv >> t.pv;
		a.push_back(t);
	}
	cout << binarySearchTheAnswer() << endl;
	return 0;
}
