#include <exception>
#include <iomanip>
#include <iostream>
#include <string>
#include <tuple>
#include <typeinfo>
#include <vector>

int lifetime[5] = {};

class Warrier {
public:
    virtual const int getLifeUnit() const {
        return 0;
    }
    virtual const char* getName() const {
        return "undefined";
    }
    virtual ~Warrier(){};
};

class Dragon : public Warrier {
public:
    const int getLifeUnit() const {
        return lifetime[0];
    }
    const char* getName() const {
        return "dragon";
    }
};
class Ninja : public Warrier {
public:
    const int getLifeUnit() const {
        return lifetime[1];
    }
    const char* getName() const {
        return "ninja";
    }
};
class Iceman : public Warrier {
public:
    const int getLifeUnit() const {
        return lifetime[2];
    }
    const char* getName() const {
        return "iceman";
    }
};
class Lion : public Warrier {
public:
    const int getLifeUnit() const {
        return lifetime[3];
    }
    const char* getName() const {
        return "lion";
    }
};
class Wolf : public Warrier {
public:
    const int getLifeUnit() const {
        return lifetime[4];
    }
    const char* getName() const {
        return "wolf";
    }
};

class Headquarter {
private:
    std::string name;
    std::vector<const Warrier*> warrierList;
    int lifeUnit;
    bool stopped;

public:
    Warrier* (*genCallback)(int);
    Headquarter(const std::string& name = "", int lifeUnit = 0, Warrier* (*callback)(int) = nullptr)
        : name(name), lifeUnit(lifeUnit), stopped(false), genCallback(callback) {}
    ~Headquarter() {
        for (auto i : warrierList) {
            delete i;
        }
    }
    const std::string& getName() const {
        return name;
    }
    inline int getLifeUnit() const {
        return lifeUnit;
    }
    int getNum() const {
        return warrierList.size();
    }
    inline bool isStop() const {
        return stopped;
    }
    void stop() {
        stopped = true;
    }
    
    /**
     * @brief Add a warrier to the headquarter.
     * 
     * @param warrier The warrier to be added.
     * @return int The total number of current type of warrier.
     */
    int addWarrier(const Warrier* warrier) {
        warrierList.push_back(warrier);
        lifeUnit -= warrier->getLifeUnit();
        int num = 0;
        for (auto i : warrierList) {
            if (typeid(*warrier) == typeid(*i))
                num++;
        }
        return num;
    }
};

Warrier* generateRed(int mod) {
    switch (mod) {
        case 0: return new Iceman;
        case 1: return new Lion;
        case 2: return new Wolf;
        case 3: return new Ninja;
        case 4: return new Dragon;
        default: return nullptr;
    }
}

Warrier* generateBlue(int mod) {
    switch (mod) {
        case 0: return new Lion;
        case 1: return new Dragon;
        case 2: return new Ninja;
        case 3: return new Iceman;
        case 4: return new Wolf;
        default: return nullptr;
    }
}

void execute(Headquarter& head, int& seq, const int time) {
    if (head.isStop())
        return;
    Warrier* next;
    int trytime = 0;
    while (next = head.genCallback(seq % 5), next->getLifeUnit() > head.getLifeUnit()) {
        delete next;
        trytime++;
        seq++;
        if (trytime == 5) {
            head.stop();
            std::cout << std::setw(3) << std::setfill('0') << time << ' ' << head.getName()
                      << " headquarter stops making warriors" << std::endl;
            return;
        }
    }
    int num = head.addWarrier(next);
    seq++;
    std::cout << std::setw(3) << std::setfill('0') << time << ' ' << head.getName() << ' '
              << next->getName() << ' ' << head.getNum() << " born with strength "
              << next->getLifeUnit() << ',' << num << ' ' << next->getName() << " in "
              << head.getName() << " headquarter" << std::endl;
}

int main() {
    int t;
    std::cin >> t;
    for (int j = 1; j <= t; j++) {
        int generalLifeUnit;
        std::cin >> generalLifeUnit;
        Headquarter red("red", generalLifeUnit, generateRed);
        Headquarter blue("blue", generalLifeUnit, generateBlue);
        for (auto& i : lifetime) {
            std::cin >> i;
        };
        int time = 0, redseq = 0, blueseq = 0;
        std::cout << "Case:" << j << std::endl;
        while (!red.isStop() || !blue.isStop()) {
            execute(red, redseq, time);
            execute(blue, blueseq, time);
            time++;
        }
    }
    return 0;
}