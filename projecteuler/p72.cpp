#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

/* 
Reference: https://brilliant.org/wiki/eulers-totient-function/

The number of RDFs (reduced proper fractions) for d is equal to phi(d) (Euler's Totient Function).
Hence, the size of the set of RDFs for d <= 1e6 is 
    
    total = 0
    for d in [2, 1e6]:
        total += phi(d)

To improve the algorithm, we can use DP by making use of these properties

    phi on prime numbers (use prime sieving to generate):
        phi(p) = p - 1, where p is a prime number

    Multiplicativity:
        if a and b are coprime => phi(a * b) = phi(a) * phi(b)
        otherwise => phi(a * b) = phi(a) * phi(b) * d / phi(d), where d = gcd(a, b)
*/

// Euclidean algorithm
ull gcd(ull a, ull b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Sieve of Eratosthenes
vector<bool> sieve(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = false;
    is_prime[1] = false;
    for (int i = 2; i <= n; i++) {
        if (!is_prime[i]) continue;
        for (int j = 2 * i; j <= n; j += i) {
            is_prime[j] = false;
        }
    }
    return is_prime;
}

int totient(int n, vector<bool> &is_prime, vector<int> &totient_arr) {
    if (totient_arr[n] != 0) return totient_arr[n];
    if (is_prime[n]) {
        totient_arr[n] = n - 1;
        return n - 1;
    }

    for (int d = 2; d * d <= n; d++) {
        if (n % d == 0) {
            // Multiplicativity
            int a = totient(n / d, is_prime, totient_arr);
            int b = totient(d, is_prime, totient_arr);
            int x = gcd (n / d, d);

            if (x == 1) totient_arr[n] = a * b;
            else totient_arr[n] = a * b * x / totient(x, is_prime, totient_arr);

            return totient_arr[n]; 
        }
    }

    return 0;
}

int main() {
    const int N = 1e6;
    vector<bool> is_prime = sieve(N);

    // Store for DP
    vector<int> totient_arr(N + 1, 0);

    ull ans = 0;
    for (int i = 2; i <= N; i++) {
        ans += totient(i, is_prime, totient_arr);
    }
    cout << ans << endl;

    return 0;
}