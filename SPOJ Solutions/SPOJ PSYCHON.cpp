#include <bits/stdc++.h>
using namespace std;
vector<int> primes;
void sieve() {
	bitset<3170> bs;
	bs.set();
	bs[0] = bs[1] = 0;
	for (int i = 2; i <= 3165; i++)
		if (bs[i]) {
			primes.push_back(i);
			for (int j = i * i; j <= 3165; j += i)
				bs[j] = 0;
		}
}

bool solve(long long n) {
	int even = 0, odd = 0;
	for (int i = 0; i < primes.size(); i++) {
		if (primes[i] * primes[i] > n)
			break;
		int cnt = 0;
		while (n % primes[i] == 0) {
			cnt++;
			n = n / primes[i];
		}
		if (cnt != 0) {
			if (cnt % 2 == 0)
				even++;
			else
				odd++;
		}
	}
	if (n != 1)
		odd++;
	return even > odd;
}
int main(int argc, char **argv) {
	sieve();
	int t, n;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		if (solve(n)) {
			printf("Psycho Number\n");
		} else {
			printf("Ordinary Number\n");
		}
	}
	return 0;
}
