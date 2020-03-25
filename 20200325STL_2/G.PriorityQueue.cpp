#include <cmath>
#include <iostream>
#include <set>

class PrimeFactor {
    int getPrimeSum(const int& a) const {
        auto isPrime = [](int x) {
            for (int i = 2; i <= std::sqrt(x); i++) {
                if (x % i == 0)
                    return false;
            }
            return true;
        };
        int sum = 0;
        for (int i = 2; i <= sqrt(a); i++) {
            if (a % i == 0) {
                int k = a / i;
                if (isPrime(i))
                    sum++;
                if (k != i && isPrime(k))
                    sum++;
            }
        }
        return sum;
    }

public:
    bool operator()(const int& a, const int& b) const {
        int suma = getPrimeSum(a);
        int sumb = getPrimeSum(b);
        return (suma == sumb) ? a < b : suma < sumb;
    }
};

int main() {
    std::set<int, PrimeFactor> s;
    int n;
    std::scanf("%d", &n);
    while (n--) {
        int m;
        for (int i = 0; i < 10; i++) {
            scanf("%d", &m);
            s.insert(m);
        }
        int min = *s.begin();
        int max = *s.rbegin();
        s.erase(max);
        s.erase(min);
        std::printf("%d %d\n", max, min);
    }
}