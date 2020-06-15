// copied but tle

#include <algorithm>
#include <cstdio>
#include <cstring>
const int maxn = 300;
int n, m, p, k, T[maxn], U[maxn], V[maxn], X[maxn], Y[maxn], Z[maxn];
struct Node {
    int size, v;
} P[30000];
int A[100002], B[100002], tot = 0;
void devide(int x) {
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
void devide2(int x) {
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
    int t;
    scanf("%d", &t);
    while (t--) {
        k = 50000;
        memset(T, 0, sizeof(T));
        memset(U, 0, sizeof(U));
        memset(V, 0, sizeof(V));
        memset(X, 0, sizeof(X));
        memset(Y, 0, sizeof(Y));
        memset(Z, 0, sizeof(Z));
        memset(P, 0, sizeof(P));
        memset(A, 0, sizeof(A));
        memset(B, 0, sizeof(B));
        scanf("%d%d%d", &n, &m, &p);
        for (int i = 1; i <= n; i++)
            scanf("%d%d%d", &T[i], &U[i], &V[i]);
        for (int i = 1; i <= m; i++)
            scanf("%d%d%d", &X[i], &Y[i], &Z[i]);
        for (int i = 1; i <= n; i++)
            devide(i);
        for (int i = 1; i <= tot; i++) {
            for (int V = 100000; V >= P[i].size; V--) {
                A[V] = std::max(A[V], A[V - P[i].size] + P[i].v);
            }
        }
        int ans1;
        for (int i = 1; i <= 100000; i++) {
            if (A[i] >= p) {
                ans1 = i;
                // printf("%d\n", i);
                break;
            }
        }
        tot = 0;
        for (int i = 1; i <= m; i++)
            devide2(i);
        for (int i = 1; i <= tot; i++) {
            for (int V = 100000; V >= P[i].size; V--) {
                B[V] = std::max(B[V], B[V - P[i].size] + P[i].v);
            }
        }
        for (int i = 1; i <= k; i++) {
            if (B[i] >= ans1) {
                printf("%d\n", i);
                goto next;
            }
        }
        puts("FAIL");
    next:;
    }
    return 0;
}