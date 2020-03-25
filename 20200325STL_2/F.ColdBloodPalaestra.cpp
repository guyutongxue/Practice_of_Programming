#include <algorithm>
#include <iostream>
#include <map>

std::map<int, int> force;
int main() {
    force.insert(std::make_pair(1000000000, 1));
    int n;
    std::scanf("%d", &n);
    while (n--) {
        int id, va;
        std::scanf("%d%d", &id, &va);

        auto it = force.lower_bound(va);
        if (it == force.end())
            it--;
        int result = it->second;
        int sub = std::abs(it->first - va);
        if (it != force.begin()) {
            it--;
            if (sub == abs(it->first - va) ? it->second < result : std::abs(it->first - va) < sub)
                result = it->second;
        }
        std::printf("%d %d\n", id, result);
        it = force.find(va);
        // only update the value when id is lower
        if (it == force.end() || it->second > id)
            force[va] = id;
    }
    return 0;
}