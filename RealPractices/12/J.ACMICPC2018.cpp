// copied but wa

#include <algorithm>
#include <cstdio>
#include <cstring>
const int maxn = 300;
int n, m, p, k, T[maxn], U[maxn], V[maxn], X[maxn], Y[maxn], Z[maxn];
struct Node {
    int size, v;
} P[30000];
int A[100002], B[100002], tot = 0;
inline void devide(int x) {
    int l = 1;
    while (l <= V[x]) {
        P[++tot].size = U[x] * l;
        P[tot].v = T[x] * l;
        V[x] -= l;
        l <<= 1;
    }
    if (V[x]) {
        P[++tot].size = U[x] * V[x];
        P[tot].v = T[x] * V[x];
    }
    return;
}
inline void devide2(int x) {
    int l = 1;
    while (l <= Z[x]) {
        P[++tot].size = Y[x] * l;
        P[tot].v = X[x] * l;
        Z[x] -= l;
        l <<= 1;
    }
    if (Z[x]) {
        P[++tot].size = Y[x] * Z[x];
        P[tot].v = X[x] * Z[x];
    }
    return;
}
int main() {
    freopen("z.in", "r", stdin);
    freopen("z.out", "w", stdout);
    scanf("%d%d%d%d", &n, &m, &p, &k);
    for (register int i = 1; i <= n; i++)
        scanf("%d%d%d", &T[i], &U[i], &V[i]);
    for (register int i = 1; i <= m; i++)
        scanf("%d%d%d", &X[i], &Y[i], &Z[i]);
    for (register int i = 1; i <= n; i++)
        devide(i);
    for (register int i = 1; i <= tot; i++) {
        for (register int V = 100000; V >= P[i].size; V--) {
            A[V] = std::max(A[V], A[V - P[i].size] + P[i].v);
        }
    }
    int ans1;
    for (register int i = 1; i <= 100000; i++) {
        if (A[i] >= p) {
            ans1 = i;
            printf("%d\n", i);
            break;
        }
    }
    tot = 0;
    for (register int i = 1; i <= m; i++)
        devide2(i);
    for (register int i = 1; i <= tot; i++) {
        for (register int V = 100000; V >= P[i].size; V--) {
            B[V] = std::max(B[V], B[V - P[i].size] + P[i].v);
        }
    }
    for (register int i = 1; i <= k; i++) {
        if (B[i] >= ans1) {
            printf("%d\n", i);
            return 0;
        }
    }
    puts("FAIL");
    return 0;
}