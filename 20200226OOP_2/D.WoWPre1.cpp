#include <exception>
#include <iomanip>
#include <iostream>
#include <string>
#include <tuple>
#include <typeinfo>
#include <vector>

int lifetime[5] = {};

class Warrior {
public:
    virtual const int getLifeUnit() const {
        return 0;
    }
    virtual const char* getName() const {
        return "undefined";
    }
    virtual ~Warrior(){};
};

class Dragon : public Warrior {
public:
    const int getLifeUnit() const {
        return lifetime[0];
    }
    const char* getName() const {
        return "dragon";
    }
};
class Ninja : public Warrior {
public:
    const int getLifeUnit() const {
        return lifetime[1];
    }
    const char* getName() const {
        return "ninja";
    }
};
class Iceman : public Warrior {
public:
    const int getLifeUnit() const {
        return lifetime[2];
    }
    const char* getName() const {
        return "iceman";
    }
};
class Lion : public Warrior {
public:
    const int getLifeUnit() const {
        return lifetime[3];
    }
    const char* getName() const {
        return "lion";
    }
};
class Wolf : public Warrior {
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
    std::vector<const Warrior*> warriorList;
    int lifeUnit;
    bool stopped;

public:
    Warrior* (*genCallback)(int);
    Headquarter(const std::string& name = "", int lifeUnit = 0, Warrior* (*callback)(int) = nullptr)
        : name(name), lifeUnit(lifeUnit), stopped(false), genCallback(callback) {}
    ~Headquarter() {
        for (auto i : warriorList) {
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
        return warriorList.size();
    }
    inline bool isStop() const {
        return stopped;
    }
    void stop() {
        stopped = true;
    }
    
    /**
     * @brief Add a warrior to the headquarter.
     * 
     * @param warrior The warrior to be added.
     * @return int The total number of current type of warrior.
     */
    int addWarrior(const Warrior* warrior) {
        warriorList.push_back(warrior);
        lifeUnit -= warrior->getLifeUnit();
        int num = 0;
        for (auto i : warriorList) {
            if (typeid(*warrior) == typeid(*i))
                num++;
        }
        return num;
    }
};

Warrior* generateRed(int mod) {
    switch (mod) {
        case 0: return new Iceman;
        case 1: return new Lion;
        case 2: return new Wolf;
        case 3: return new Ninja;
        case 4: return new Dragon;
        default: return nullptr;
    }
}

Warrior* generateBlue(int mod) {
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
    Warrior* next;
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
    int num = head.addWarrior(next);
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