#include <exception>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <typeinfo>
#include <vector>

int lifetime[5] = {};

class Armament {
public:
    float data;
    virtual const char* getName() const = 0;
};

// ENHANCE ARMAMENT!!!
class Sword : public Armament {
public:
    const char* getName() const override {
        return "sword";
    }
};

class Bomb : public Armament {
public:
    const char* getName() const override {
        return "bomb";
    }
};

class Arrow : public Armament {
public:
    const char* getName() const override {
        return "arrow";
    }
};

Armament* generateArmament(int);

class Warrior {
private:
    int number;

protected:
    float morale;
    int loyalty;
    std::vector<Armament*> armamentList;

public:
    virtual const int getLifeUnit() const = 0;
    virtual const char* getName() const = 0;
    virtual const std::string getBornLog() const = 0;
    const int getNumber() {
        return number;
    }
    Warrior(int number) : number(number) {}
    ~Warrior() {
        for (auto& i : armamentList) {
            delete i;
        }
    }
};

class Dragon : public Warrior {
public:
    Dragon(int number, float morale) : Warrior(number) {
        armamentList.push_back(generateArmament(number % 3));
        this->morale = morale;
    }
    const int getLifeUnit() const override {
        return lifetime[0];
    }
    const char* getName() const override {
        return "dragon";
    }
    const std::string getBornLog() const override {
        std::stringstream ss;
        ss << "It has a " << armamentList[0]->getName() << ",and it's morale is " << std::fixed
           << std::setprecision(2) << morale << "\n";
        return ss.str();
    }
};
class Ninja : public Warrior {
public:
    Ninja(int number) : Warrior(number) {
        armamentList.push_back(generateArmament(number % 3));
        armamentList.push_back(generateArmament((number + 1) % 3));
    }
    const int getLifeUnit() const override {
        return lifetime[1];
    }
    const char* getName() const override {
        return "ninja";
    }
    const std::string getBornLog() const override {
        std::stringstream ss;
        ss << "It has a " << armamentList[0]->getName() << " and a " << armamentList[1]->getName()
           << "\n";
        return ss.str();
    }
};
class Iceman : public Warrior {
public:
    Iceman(int number) : Warrior(number) {
        armamentList.push_back(generateArmament(number % 3));
    }
    const int getLifeUnit() const override {
        return lifetime[2];
    }
    const char* getName() const override {
        return "iceman";
    }
    const std::string getBornLog() const override {
        std::stringstream ss;
        ss << "It has a " << armamentList[0]->getName() << "\n";
        return ss.str();
    }
};
class Lion : public Warrior {
public:
    Lion(int number, float loyalty) : Warrior(number) {
        this->loyalty = loyalty;
    }
    const int getLifeUnit() const override {
        return lifetime[3];
    }
    const char* getName() const override {
        return "lion";
    }
    const std::string getBornLog() const override {
        std::stringstream ss;
        ss << "It's loyalty is " << loyalty << "\n";
        return ss.str();
    }
};
class Wolf : public Warrior {
public:
    Wolf(int number) : Warrior(number) {}
    const int getLifeUnit() const override {
        return lifetime[4];
    }
    const char* getName() const override {
        return "wolf";
    }
    const std::string getBornLog() const override {
        return "";
    }
};

using WarriorDelegatePtr = Warrior* (*)(int, int, int);

class Headquarter {
private:
    std::string name;
    std::vector<const Warrior*> warriorList;
    int lifeUnit;
    bool stopped;

public:
    WarriorDelegatePtr genCallback;
    Headquarter(const std::string& name = "", int lifeUnit = 0,
                WarriorDelegatePtr callback = nullptr)
        : name(name), lifeUnit(lifeUnit), stopped(false), genCallback(callback) {}
    ~Headquarter() {
        for (auto& i : warriorList) {
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

Warrior* generateRed(int seq, int no, int lifeUnit) {
    switch (seq) {
        case 0: return new Iceman(no);
        case 1: return new Lion(no, lifeUnit - lifetime[3]);
        case 2: return new Wolf(no);
        case 3: return new Ninja(no);
        case 4: return new Dragon(no, 1.f * (lifeUnit - lifetime[0]) / lifetime[0]);
    }
    return nullptr;
}

Warrior* generateBlue(int seq, int no, int lifeUnit) {
    switch (seq) {
        case 0: return new Lion(no, lifeUnit - lifetime[3]);
        case 1: return new Dragon(no, 1.f * (lifeUnit - lifetime[0]) / lifetime[0]);
        case 2: return new Ninja(no);
        case 3: return new Iceman(no);
        case 4: return new Wolf(no);
    }
    return nullptr;
}

Armament* generateArmament(int no) {
    switch (no) {
        case 0: return new Sword();
        case 1: return new Bomb();
        case 2: return new Arrow();
    }
    return nullptr;
}

void execute(Headquarter& head, int& seq, const int time) {
    if (head.isStop())
        return;
    Warrior* next;
    int trytime = 0;
    while (next = head.genCallback(seq % 5, head.getNum() + 1, head.getLifeUnit()),
           next->getLifeUnit() > head.getLifeUnit()) {
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
    std::cout << next->getBornLog();
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