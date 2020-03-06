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

class Warrier {
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
    Warrier(int number) : number(number) {}
    ~Warrier() {
        for (auto& i : armamentList) {
            delete i;
        }
    }
};

class Dragon : public Warrier {
public:
    Dragon(int number, float morale) : Warrier(number) {
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
class Ninja : public Warrier {
public:
    Ninja(int number) : Warrier(number) {
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
class Iceman : public Warrier {
public:
    Iceman(int number) : Warrier(number) {
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
class Lion : public Warrier {
public:
    Lion(int number, float loyalty) : Warrier(number) {
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
class Wolf : public Warrier {
public:
    Wolf(int number) : Warrier(number) {}
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

using WarrierDelegatePtr = Warrier* (*)(int, int, int);

class Headquarter {
private:
    std::string name;
    std::vector<const Warrier*> warrierList;
    int lifeUnit;
    bool stopped;

public:
    WarrierDelegatePtr genCallback;
    Headquarter(const std::string& name = "", int lifeUnit = 0,
                WarrierDelegatePtr callback = nullptr)
        : name(name), lifeUnit(lifeUnit), stopped(false), genCallback(callback) {}
    ~Headquarter() {
        for (auto& i : warrierList) {
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

Warrier* generateRed(int seq, int no, int lifeUnit) {
    switch (seq) {
        case 0: return new Iceman(no);
        case 1: return new Lion(no, lifeUnit - lifetime[3]);
        case 2: return new Wolf(no);
        case 3: return new Ninja(no);
        case 4: return new Dragon(no, 1.f * (lifeUnit - lifetime[0]) / lifetime[0]);
    }
    return nullptr;
}

Warrier* generateBlue(int seq, int no, int lifeUnit) {
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
    Warrier* next;
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
    int num = head.addWarrier(next);
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