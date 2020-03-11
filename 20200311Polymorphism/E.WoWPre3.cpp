#include <exception>
#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>

namespace WoW {

int initialLife[5] = {};

class Armament {
public:
    float force;
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
private:
    bool used = false;
public:
    bool isUsed() {
        return used;
    }
    const char* getName() const override {
        return "arrow";
    }
};

Armament* generateArmament(int);
class Headquarter;

class Warrier {
private:
    int number;
    int life;
    int force;
    const Headquarter* owner;

protected:
    std::vector<Armament*> armamentList;

public:
    virtual const int getLife() const = 0;
    virtual const char* getName() const = 0;
    virtual const std::string getBornLog() const = 0;
    const int getNumber() {
        return number;
    }
    Warrier(int number, const Headquarter* owner) : number(number), owner(owner) {}
    ~Warrier() {
        for (auto& i : armamentList) {
            delete i;
        }
    }
};

class Dragon : public Warrier {
private:
    float morale;

public:
    Dragon(int number, const Headquarter* owner, float morale)
        : Warrier(number, owner), morale(morale) {
        armamentList.push_back(generateArmament(number % 3));
    }
    const int getLife() const override {
        return initialLife[0];
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
    Ninja(int number, const Headquarter* owner) : Warrier(number, owner) {
        armamentList.push_back(generateArmament(number % 3));
        armamentList.push_back(generateArmament((number + 1) % 3));
    }
    const int getLife() const override {
        return initialLife[1];
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
    Iceman(int number, const Headquarter* owner) : Warrier(number, owner) {
        armamentList.push_back(generateArmament(number % 3));
    }
    const int getLife() const override {
        return initialLife[2];
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
private:
    int loyalty;

public:
    Lion(int number, const Headquarter* owner, float loyalty)
        : Warrier(number, owner), loyalty(loyalty) {}
    const int getLife() const override {
        return initialLife[3];
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
    Wolf(int number, const Headquarter* owner) : Warrier(number, owner) {}
    const int getLife() const override {
        return initialLife[4];
    }
    const char* getName() const override {
        return "wolf";
    }
    const std::string getBornLog() const override {
        return "";
    }
};

class Headquarter {
public:
    class WarrierGenerator {
    public:
        const std::function<Warrier*(int, int, const Headquarter*, int)> generateFunction;
        template <typename T>
        WarrierGenerator(const T& function) : generateFunction(function) {}
        Warrier* operator()(int seq, const Headquarter* owner) const;
        ~WarrierGenerator() {}
    };

private:
    std::string name;
    std::vector<const Warrier*> warrierList;
    int life;
    bool stopped;
    const WarrierGenerator warrierGenerator;

public:
    const static WarrierGenerator redGenerator;
    const static WarrierGenerator blueGenerator;
    Headquarter(const std::string& name, int life, const WarrierGenerator warrierGenerator)
        : name(name), life(life), stopped(false), warrierGenerator(warrierGenerator) {}
    ~Headquarter() {
        for (auto& i : warrierList) {
            delete i;
        }
    }
    const std::string& getName() const {
        return name;
    }
    inline int getLife() const {
        return life;
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
    int addWarrier(const Warrier* warrier);

    void generateWarrier(int& seq, const int time);
};

Warrier* Headquarter::WarrierGenerator::operator()(int seq, const Headquarter* owner) const {
    return generateFunction(seq, owner->getNum() + 1, owner, owner->life);
}

const Headquarter::WarrierGenerator Headquarter::redGenerator =
    [](int seq, int no, const Headquarter* owner, int life) -> Warrier* {
    switch (seq) {
        case 0: return new Iceman(no, owner);
        case 1: return new Lion(no, owner, life - initialLife[3]);
        case 2: return new Wolf(no, owner);
        case 3: return new Ninja(no, owner);
        case 4: return new Dragon(no, owner, 1.f * (life - initialLife[0]) / initialLife[0]);
    }
    return nullptr;
};

const Headquarter::WarrierGenerator Headquarter::blueGenerator =
    [](int seq, int no, const Headquarter* owner, int life) -> Warrier* {
    switch (seq) {
        case 0: return new Lion(no, owner, life - initialLife[3]);
        case 1: return new Dragon(no, owner, 1.f * (life - initialLife[0]) / initialLife[0]);
        case 2: return new Ninja(no, owner);
        case 3: return new Iceman(no, owner);
        case 4: return new Wolf(no, owner);
    }
    return nullptr;
};

int Headquarter::addWarrier(const Warrier* warrier) {
    warrierList.push_back(warrier);
    life -= warrier->getLife();
    int num = 0;
    for (auto i : warrierList) {
        if (typeid(*warrier) == typeid(*i))
            num++;
    }
    return num;
}

void Headquarter::generateWarrier(int& seq, const int time) {
    if (stopped)
        return;
    Warrier* next;
    int trytime = 0;
    while (next = warrierGenerator(seq % 5, this), next->getLife() > life) {
        delete next;
        trytime++;
        seq++;
        if (trytime == 5) {
            stop();
            std::cout << std::setw(3) << std::setfill('0') << time << ' ' << name
                      << " headquarter stops making warriors" << std::endl;
            return;
        }
    }
    int num = addWarrier(next);
    seq++;
    std::cout << std::setw(3) << std::setfill('0') << time << ' ' << name << ' ' << next->getName()
              << ' ' << getNum() << " born with strength " << next->getLife() << ',' << num
              << ' ' << next->getName() << " in " << name << " headquarter" << std::endl;
    std::cout << next->getBornLog();
}

inline Armament* generateArmament(int no) {
    switch (no) {
        case 0: return new Sword();
        case 1: return new Bomb();
        case 2: return new Arrow();
    }
    return nullptr;
}

}  // namespace WoW

int main() {
    int t;
    std::cin >> t;
    for (int j = 1; j <= t; j++) {
        int generalLife;
        std::cin >> generalLife;
        WoW::Headquarter red("red", generalLife, WoW::Headquarter::redGenerator);
        WoW::Headquarter blue("blue", generalLife, WoW::Headquarter::blueGenerator);
        for (auto& i : WoW::initialLife) {
            std::cin >> i;
        };
        int time = 0, redseq = 0, blueseq = 0;
        std::cout << "Case:" << j << std::endl;
        while (!red.isStop() || !blue.isStop()) {
            red.generateWarrier(redseq, time);
            blue.generateWarrier(blueseq, time);
            time++;
        }
    }
    return 0;
}