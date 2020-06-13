// Wrong Answer.
// Cannot deal with two parens in parallel. e.g.
// ((1.2):(3.4.5))
// This bug cannot be fixed easily. Refactorize may be needed.

#include <algorithm>
#include <cstring>
#include <iostream>
#include <numeric>
#include <string>
#include <typeinfo>
#include <vector>

enum struct Relation { Horizental, Vertical };

struct Node {
    int w = 0;
    int h = 0;
    bool isBraced;
    Node() = default;
    void multiply(Relation r) {
        if (r == Relation::Horizental)
            w *= 3;
        else
            h *= 3;
    }
    virtual ~Node() {}
};

struct Branch : Node {
    Relation r;
    std::vector<Node*> child;
    ~Branch() {
        for (auto&& i : child) {
            delete i;
        }
    }
};

struct Leaf : Node {
    std::string content;
    Leaf(std::string content) : content{content} {
        w = content.size() + 2;
        h = 1;
    }
};

Leaf* parseLeaf() {
    char ch;
    std::string content;
    while (ch = std::cin.peek(), std::isdigit(ch)) {
        std::cin.get();
        content += ch;
    }
    return new Leaf(content);
}

Branch* parseBranch() {
    Branch* result = new Branch;
    char ch;
    bool bracing{false};
    while (ch = std::cin.peek()) {
        if (ch == '[') {
            std::cin.get();
            bracing = true;
            continue;
        }
        if (ch == ']') {
            std::cin.get();
            bracing = false;
            continue;
        }
        if (ch == '(') {
            std::cin.get();
            Branch* branch = parseBranch();
            branch->isBraced = bracing;
            result->child.push_back(branch);
            continue;
        }
        if (std::isdigit(ch)) {
            Leaf* leaf = parseLeaf();
            leaf->isBraced = bracing;
            result->child.push_back(leaf);
            continue;
        }
        if (ch == ':') {
            std::cin.get();
            result->r = Relation::Vertical;
            continue;
        }
        if (ch == '.') {
            std::cin.get();
            result->r = Relation::Horizental;
            continue;
        }
        if (ch == ')') {
            std::cin.get();
            for (auto&& i : result->child) {
                result->w = std::max(result->w, i->w);
                result->h = std::max(result->h, i->h);
            }
            for (auto&& i : result->child) {
                i->w = result->w;
                i->h = result->h;
                if (i->isBraced) {
                    i->multiply(result->r);
                }
            }
            if (result->r == Relation::Vertical) {
                result->h = std::accumulate(
                    result->child.begin(), result->child.end(), 0,
                    [](const int& a, Node* const& b) -> int { return a + b->h + 1; });
                result->h--;  // +1 in each part then -- to contain edges
            } else {
                result->w = std::accumulate(
                    result->child.begin(), result->child.end(), 0,
                    [](const int& a, Node* const& b) -> int { return a + b->w + 1; });
                result->w--;
            }
            return result;
        }
    }
    return nullptr;
}

char* map{nullptr};
int w{0};
inline char& at(int x, int y) {
    return map[(w + 2) * x + y];
}

void draw(const Node* node, char* map, int t, int l) {
    if (typeid(*node) == typeid(Leaf)) {
        auto leaf = dynamic_cast<const Leaf*>(node);
        at(t, l) = '+';
        at(t + leaf->h + 1, l) = '+';
        at(t, l + leaf->w + 1) = '+';
        at(t + leaf->h + 1, l + leaf->w + 1) = '+';
        for (int i{1}; i <= leaf->w; i++) {
            if (at(t, l + i) == ' ')
                at(t, l + i) = '-';
            if (at(t + leaf->h + 1, l + i) == ' ')
                at(t + leaf->h + 1, l + i) = '-';
        }
        for (int i{1}; i <= leaf->h; i++) {
            if (at(t + i, l) == ' ')
                at(t + i, l) = '|';
            if (at(t + i, l + leaf->w + 1) == ' ')
                at(t + i, l + leaf->w + 1) = '|';
        }
        for (int i{0}; i < leaf->content.size(); i++) {
            at(t + 1, l + 2 + i) = leaf->content.at(i);
        }
    } else {
        auto branch = dynamic_cast<const Branch*>(node);
        if (branch->r == Relation::Vertical) {
            int nt{t};
            for (auto&& i : branch->child) {
                draw(i, map, nt, l);
                nt += i->h + 1;
            }
        } else {
            int nl{l};
            for (auto&& i : branch->child) {
                draw(i, map, t, nl);
                nl += i->w + 1;
            }
        }
    }
}

int main() {
    Node* node{nullptr};
    if (std::isdigit(std::cin.peek())) {
        node = parseLeaf();
    } else {
        std::cin.get();
        node = parseBranch();
    }
    // std::freopen("a.txt", "w", stdout);

    w = node->w;
    map = new char[(node->h + 2) * (w + 2)];
    memset(map, ' ', (node->h + 2) * (w + 2));
    draw(node, map, 0, 0);
    for (int i{0}; i <= node->h + 1; i++) {
        for (int j{0}; j <= w + 1; j++) {
            std::cout << at(i, j);
        }
        std::cout << std::endl;
    }
    delete[] map;
    delete node;
}