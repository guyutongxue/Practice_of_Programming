#include<cstdio>
#include<cstring>
#include<set>
using namespace std;

multiset<int> s;
int a[5000 + 5];

int main() {
	int n, T, k;
	scanf("%d", &T);
	while (T--) {
		s.clear();
		scanf("%d", &n);
		for (int i = 0; i < n; i ++) {
			scanf("%d", a + i);
			s.insert(a[i]);
		}
		bool flag = false;
		scanf("%d", &k);
		for (int i = 0; i < n; i ++) {
			for (int j = i + 1; j < n; j ++) {
				int target = k - a[i] - a[j], min_count = 1;
                s.erase(s.find(a[i]));
                s.erase(s.find(a[j]));
                auto r = s.find(target);
                flag = r != s.end();
                s.insert(a[i]);
                s.insert(a[j]);
                if(flag) break;
}
			if (flag) break;
		}
		puts(flag? "Yes": "No");
	}
}