#include <algorithm>
#include <cmath>
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
        auto range = force.equal_range(va);
        std::pair<int, int> result;
        if (range.first == force.begin()) {
            result = *force.begin();
        } else {
            range.first--;
            if (range.second == force.end())
                result = *range.first;
            else
                result = range.second->first - va < va - range.first->first ? *range.second
                                                                            : *range.first;
        }
        std::printf("%d %d\n", id, result.second);
        force.insert(std::make_pair(va, id));
    }
}