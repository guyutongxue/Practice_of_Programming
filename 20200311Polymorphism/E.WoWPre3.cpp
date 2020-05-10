#include <algorithm>
#include <cassert>
#include <exception>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>

/**
 * @brief 魔兽世界命名空间。
 * 此命名空间存放全部声明。
 */
namespace WoW {

/**
 * @brief 武士的初始生命值。
 *
 */
int initialLife[5] = {};

/**
 * @brief 武士的初始武力值。
 *
 */
int initialForce[5] = {};

/**
 * @brief Lion 的忠诚度衰减参数。
 *
 */
int lionDecrease;

/**
 * @brief 需要输出的时间段。
 * 仅在此时间内的事件需要输出，以分钟为单位。
 */
int timeLimit;

/**
 * @brief 标记游戏是否结束。
 *
 */
bool isOver;

/**
 * @brief 标记输出的类型，用以决定分钟数。
 * 使用枚举值来标记分钟。
 */
enum class BroadcastType : int {
    WarriorBorn = 0,        /**< 武士被生成 */
    LionEscape = 5,         /**< Lion 逃跑 */
    WarriorMarch = 10,      /**< 武士前进 */
    WolfGetArmament = 35,   /**< Wolf 抢夺武器 */
    Battle = 40,            /**< 武士战斗 */
    HeadquarterReport = 50, /**< 司令部报告 */
    WarriorReport = 55      /**< 武士报告 */
};

/**
 * @brief 处理事件广播的静态类。
 * 所有事件的报告都将由此类中静态函数处理。
 */
class Broadcast {
private:
    static std::stringstream ss;
    template <typename T, typename... Us>
    static void generateContent(T content, Us... pack) {
        ss << content;
        generateContent(pack...);
    }
    template <typename T>
    static void generateContent(T content) {
        ss << content;
    }

public:
    /**
     * @brief 至今所过去的小时数。
     *
     */
    static int hour;

    /**
     * @brief 将事件的内容输出。
     *
     * @tparam Ts 所有的输出内容。
     * @param type 输出事件的类型。
     * @param contents 按照顺序将输出内容以参数形式传入。
     */
    template <typename... Ts>
    static void output(BroadcastType type, Ts... contents) {
        // reset stringstream
        ss.str("");
        ss.clear();
        generateContent(contents...);
        // 倘若已经超过时间限制，就不再输出
        if (hour * 60 + int(type) > timeLimit)
            isOver = true;
        else
            std::cout << std::setw(3) << std::setfill('0') << hour << ':' << std::setw(2)
                      << int(type) << ' ' << ss.str() << std::endl;
    }

    // 不允许声明 Broadcast 的任何对象
    virtual ~Broadcast() = 0;
};

// Broadcast 静态成员初始化
int Broadcast::hour = 0;
std::stringstream Broadcast::ss;

class Warrior;

/**
 * @brief 武器类。
 * 所有武器共同的属性、方法记录于此。
 */
class Armament {
private:
protected:
    /**
     * @brief 武器编号。
     *
     */
    const int number;

    /**
     * @brief 武器是否可用。
     * 若不可用（如 Bomb 和 Arrow 使用次数耗尽），则设置为 false。
     */
    bool available = true;

public:
    Armament(int number) : number(number) {}
    bool isAvailable() {
        return available;
    }
    int getNumber() {
        return number;
    }
    virtual int getForce(int) const = 0;

    /**
     * @brief 用于武器排序的运算符重载。
     * 在 Wolf 抢武器、战斗之前会进行排序。
     * @param rhs 右侧操作数。
     * @return true 左侧操作数应优先使用。
     * @return false 右侧操作数应优先使用
     */
    virtual bool operator<(const Armament& rhs) const {
        return number == rhs.number ?: number < rhs.number;
    }

    /**
     * @brief 使用武器攻击。
     *
     * @param force 使用者武力值。
     * @param enemy 被攻击对象。
     * @return int 对使用者的伤害。
     */
    virtual int attack(int force, Warrior* enemy) = 0;

    /**
     * @brief 获取武士名称。
     * 此函数通过多态实现不同武士的不同输出。
     * @return const char* 武士名称的 C 风格常量字符串。
     */
    virtual const char* getName() const = 0;
};

// ENHANCE ARMAMENT!!!
/**
 * @brief Sword 武器类。
 * 没有什么特殊的。
 */
class Sword : public Armament {
public:
    using Armament::Armament;
    int attack(int, Warrior*) override;
    int getForce(int warriorForce) const override {
        return warriorForce / 5;
    }
    const char* getName() const override {
        return "sword";
    }
};

/**
 * @brief Bomb 武器类。
 * 用一次就废弃，且会对自身造成伤害。
 */
class Bomb : public Armament {
public:
    using Armament::Armament;
    int attack(int, Warrior*) override;
    int getForce(int warriorForce) const override {
        return warriorForce * 2 / 5;
    }
    const char* getName() const override {
        return "bomb";
    }
};

/**
 * @brief Arrow 武器类。
 * 可以使用两次。
 */
class Arrow : public Armament {
private:
    /**
     * @brief 标记此 Arrow 是否使用过。
     * 参与武器类的排序。
     */
    bool used = false;

public:
    using Armament::Armament;
    bool isUsed() {
        return used;
    }
    int attack(int, Warrior*) override;
    int getForce(int warriorForce) const override {
        return warriorForce * 3 / 10;
    }

    /**
     * @brief 覆盖基类的运算符重载。
     * 若同为 Arrow 比较，则已使用过的排在前面。
     * @param rhs 右侧操作数。
     * @return true 左侧操作数优先使用。
     * @return false 右侧操作数优先使用。
     */
    bool operator<(const Armament& rhs) const override {
        // 若右侧操作数也是 Arrow
        const Arrow* arrow = dynamic_cast<const Arrow*>(&rhs);
        if (arrow) {
            return !used && arrow->used;
        }
        return Armament::operator<(rhs);
    }
    const char* getName() const override {
        return "arrow";
    }
};

class Headquarter;

/**
 * @brief 武士类。
 * 所有武士的共同属性、方法记录于此。
 */
class Warrior {
private:
    /**
     * @brief 武士编号。
     *
     */
    int number;

protected:
    /**
     * @brief 武士生命值，即 element。
     * 会因受到自身或对方的伤害而降低。
     */
    int life;

    /**
     * @brief 是否会遭受到自己的武器伤害。
     * 若不会被自己的 Bomb 伤害，则标记为 true。
     */
    bool isProtected = false;

    // 保留属性，来自上一次题目
    // const int force;

    /**
     * @brief 武士所拥有的武器列表。
     *
     */
    std::vector<Armament*> armamentList;

public:
    /**
     * @brief 当前武士所归属的司令部。
     *
     */
    Headquarter* owner;
    const int getLife() const {
        return life;
    }

    /**
     * @brief 获取武士是否死亡。
     * 若武士生命值不大于 0，则已死亡。
     * @return true 武士已死亡。
     * @return false 武士未死亡。
     */
    bool isDied() const {
        return life <= 0;
    }

    /**
     * @brief 判断该武士能否对战斗局面造成改变。
     * 只有当武器列表内仅存在 sword 且 sword 的武力值为 0 时，
     * 再怎样攻击也不会发生双方及双方武器的数据变化。
     *
     * 此处的逻辑应当优化：不能依靠武器自身的属性来判断
     * 是否停战。可以用哈希值来确定是否发生变化。
     * @return true 该武士已经不能对双方造成改变。
     * @return false 该武士仍然可以对双方造成改变。
     */
    bool canChange() const {
        if (armamentList.empty())
            return true;
        for (auto& i : armamentList) {
            if (typeid(*i) != typeid(Sword))
                return false;
            if (i->getForce(getForce()) > 0)
                return false;
        }
        return true;
    }

    /**
     * @brief 武士受到伤害。
     *
     * @param force 伤害大小。
     */
    void loseLife(int force) {
        life -= force;
    }
    virtual const int getForce() const = 0;
    virtual const char* getName() const = 0;
    virtual const std::string getBornLog() const = 0;
    const int getNumber() const {
        return number;
    }
    Warrior(int number, Headquarter* owner) : number(number), owner(owner) {}

    /**
     * @brief 对武士的全部拥有武器进行排序。
     *
     */
    void sortArmaments() {
        std::sort(armamentList.begin(), armamentList.end(),
                  [](Armament* a, Armament* b) -> bool { return *a < *b; });
    }

    /**
     * @brief 回应 Wolf 的武器抢夺请求。
     * 将自身的优先武器传出。
     * @param maximum 所能传出的武器数量最大值。
     * @return std::vector<Armament*> 传出的武器列表。
     */
    virtual std::vector<Armament*> responseArmaments(int maximum) {
        sortArmaments();
        Armament* first = armamentList.front();
        std::vector<Armament*> result;
        auto i = armamentList.begin();
        int num = 0;
        // 当达到最大值或者列表为空时停止传出
        while (num <= maximum && !armamentList.empty() && typeid(**i) == typeid(*first)) {
            result.push_back(*i);
            num++;
            armamentList.erase(i);
            i = armamentList.begin();
        }
        return result;
    }

    /**
     * @brief 武士攻击敌人。
     *
     * @param enemy 敌人。
     */
    virtual void attack(Warrior* enemy) {
        // 若没有武器，则不攻击
        if (armamentList.size() == 0)
            return;
        // 取出最优先的武器进行攻击
        Armament* selected = armamentList.front();
        // 仅当可受到自身伤害时才会损失生命值
        if (!isProtected)
            life -= selected->attack(getForce(), enemy);
        else
            selected->attack(getForce(), enemy);
        armamentList.erase(armamentList.begin());
        // 如果武器还可用，将其置入尾部；否则释放
        if (selected->isAvailable())
            armamentList.push_back(selected);
        else
            delete selected;
    }

    /**
     * @brief 武士获得战利品，即对方武器。
     *
     * @param enemy 已经死亡的敌人。
     */
    void getTrophy(Warrior* enemy) {
        // 调试：检测对方是否已死亡
        // assert(enemy->isDied());

        // 直接将对方的武器列表插入尾部
        armamentList.insert(armamentList.end(), enemy->armamentList.begin(),
                            enemy->armamentList.end());
        // 必须清除对方列表，否则武器指针会被误 delete
        enemy->armamentList.clear();
        // 去除多余武器
        if (armamentList.size() > 10) {
            for (auto i = armamentList.begin() + 10; i != armamentList.end(); ++i)
                delete *i;
            armamentList.erase(armamentList.begin() + 10, armamentList.end());
        }
    }

    /**
     * @brief 获取武士所持有的武器详情。
     * 在输出武士报告时被调用。
     * @return std::string 字符串格式的武器详情。
     */
    std::string getArmamentDetail() {
        std::stringstream ss;
        int swordCnt = 0, bombCnt = 0, arrowCnt = 0;
        for (auto& i : armamentList) {
            if (typeid(*i) == typeid(Sword))
                swordCnt++;
            if (typeid(*i) == typeid(Bomb))
                bombCnt++;
            if (typeid(*i) == typeid(Arrow))
                arrowCnt++;
        }
        ss << swordCnt << " sword " << bombCnt << " bomb " << arrowCnt << " arrow ";
        return ss.str();
    }

    /**
     * @brief 武士析构函数。
     * 需要释放所有所持有的武器。
     */
    ~Warrior() {
        for (auto& i : armamentList) {
            delete i;
        }
    }
};

/**
 * @brief 生成武士所持有的初始武器。
 *
 * @param no 武器编号。
 * @return Armament* 生成的武器指针。
 */
inline Armament* generateArmament(int no) {
    switch (no) {
        case 0: return new Sword(no);
        case 1: return new Bomb(no);
        case 2: return new Arrow(no);
    }
    return nullptr;
}

/**
 * @brief Dragon 武士类。
 * 在战斗中存活会欢呼。
 */
class Dragon : public Warrior {
private:
    // 保留属性，来自上一道题目。
    float morale;

public:
    Dragon(int number, Headquarter* owner, float morale) : Warrior(number, owner), morale(morale) {
        life = initialLife[0];
        armamentList.push_back(generateArmament(number % 3));
    }
    const int getForce() const override {
        return initialForce[0];
    }
    const char* getName() const override {
        return "dragon";
    }
    const std::string getBornLog() const override {
        // std::stringstream ss;
        // ss << "\nIts morale is " << std::fixed << std::setprecision(2) << morale;
        return "";
    }
};

/**
 * @brief Ninja 武士类。
 * 初始持有两把武器，且不会被自己伤害。
 */
class Ninja : public Warrior {
public:
    Ninja(int number, Headquarter* owner) : Warrior(number, owner) {
        life = initialLife[1];
        armamentList.push_back(generateArmament(number % 3));
        armamentList.push_back(generateArmament((number + 1) % 3));
        isProtected = true;
    }
    const int getForce() const override {
        return initialForce[1];
    }
    const char* getName() const override {
        return "ninja";
    }
    const std::string getBornLog() const override {
        return "";
    }
};

/**
 * @brief Iceman 武士类。
 * 前进会损失生命值。
 */
class Iceman : public Warrior {
public:
    Iceman(int number, Headquarter* owner) : Warrior(number, owner) {
        life = initialLife[2];
        armamentList.push_back(generateArmament(number % 3));
    }
    const int getForce() const override {
        return initialForce[2];
    }
    const char* getName() const override {
        return "iceman";
    }

    /**
     * @brief Iceman 损失生命值。
     * 每前进一步损失自身生命值的 [1/10]。
     */
    void stepDecrease() {
        life -= (life / 10);
    }
    const std::string getBornLog() const override {
        return "";
    }
};

/**
 * @brief Lion 武士类。
 * 当忠诚度不足时会逃跑。
 */
class Lion : public Warrior {
private:
    /**
     * @brief 忠诚度。
     *
     */
    int loyalty;

public:
    Lion(int number, Headquarter* owner, float loyalty) : Warrior(number, owner), loyalty(loyalty) {
        life = initialLife[3];
        armamentList.push_back(generateArmament(number % 3));
    }

    const int getForce() const override {
        return initialForce[3];
    }

    const char* getName() const override {
        return "lion";
    }

    /**
     * @brief Lion 是否应当逃跑。
     * 当忠诚度不大于零时，应当逃跑。
     * @return true 应当逃跑。
     * @return false 不逃跑。
     */
    bool isEscaping() const {
        return loyalty <= 0;
    }

    /**
     * @brief Lion 损失忠诚度。
     *
     */
    void decreaseLoyalty() {
        loyalty -= lionDecrease;
    }

    /**
     * @brief Lion 的出生详述信息。
     * 对于 Lion，出生时需要详述。
     * @return const std::string 详述信息。
     */
    const std::string getBornLog() const override {
        std::stringstream ss;
        ss << "\nIts loyalty is " << loyalty;
        return ss.str();
    }
};

/**
 * @brief Wolf 武士类。
 * 战斗开始前会抢夺对方武器。
 */
class Wolf : public Warrior {
public:
    Wolf(int number, Headquarter* owner) : Warrior(number, owner) {
        life = initialLife[4];
    }

    /**
     * @brief 抢武器请求的回应的覆盖。
     * 若对方 Wolf 想抢武器，则不传出任何武器。
     * @return std::vector<Armament*> 恒为空。
     */
    std::vector<Armament*> responseArmaments(int) override {
        return std::vector<Armament*>();
    }

    /**
     * @brief 向对方发出抢武器的请求。
     * 从敌人列表中抢夺武器，并将武器信息输出。
     * @param enemy 对方敌人。
     * @return const std::string 抢到的武器信息。
     */
    const std::string requestArmaments(Warrior* enemy) {
        std::vector<Armament*> capture = enemy->responseArmaments(10 - armamentList.size());
        for (auto& i : capture) {
            armamentList.push_back(i);
        }
        // 若没抢到（对方无武器或者为 Wolf），则输出空字符串
        if (capture.size() == 0)
            return "";
        std::stringstream ss;
        ss << capture.size() << ' ' << capture.front()->getName();
        return ss.str();
    }

    const int getForce() const override {
        return initialForce[4];
    }

    const char* getName() const override {
        return "wolf";
    }

    const std::string getBornLog() const override {
        return "";
    }
};

/**
 * @brief 司令部类。
 * 管理司令部所管辖的全部武士。
 */
class Headquarter {
public:
    /**
     * @brief 武士生成器类。
     * 通过此类生成武士。
     */
    class WarriorGenerator {
    public:
        /**
         * @brief 武士生成函数对象。
         * 确定以如何顺序生成武士。
         */
        const std::function<Warrior*(int, Headquarter*, int)> generateFunction;

        /**
         * @brief 武士生成器构造函数。
         * 使用函数对象（可为 Lambda 表达式）构造一个生成器。
         * 这个函数应接收 @c int, @c Headquarter*, @c int 三个参数，
         * 分别为要生成的武士编号、司令部指针和司令部的生命元数量。
         * 返回一个 @c Warrior* 为生成的武士。
         * @tparam T 函数对象类。
         * @param function 函数对象。
         */
        template <typename T>
        WarriorGenerator(const T& function) : generateFunction(function) {}

        /**
         * @brief 执行武士生成过程。
         * 直接通过仿函数的形式生成武士。
         * @param headquarter 要生成武士的司令部。
         * @return Warrior* 生成得到的武士。
         */
        Warrior* operator()(Headquarter* headquarter) const;
        ~WarriorGenerator() {}
    };

private:
    /**
     * @brief 司令部名称。
     * 为 @c "red" 或 @c "blue" 。
     */
    std::string name;

    /**
     * @brief 武士列表。
     * 以 武士编号 - 武士指针 的映射方式存储。
     */
    std::map<int, Warrior*> warriorList;

    /**
     * @brief 司令部所拥有的生命元个数。
     *
     */
    int life;

    /**
     * @brief 司令部即将生成的武士编号。
     *
     */
    int nextWarriorNumber = 1;

    /**
     * @brief 标记司令部是否应停止生成武士。
     *
     */
    bool stopped = false;

    /**
     * @brief 本司令部所使用的武士生成器。
     *
     */
    const WarriorGenerator warriorGenerator;

    /**
     * @brief 向该司令部添加一名武士。
     *
     * @param warrior 要被添加的武士。
     * @return int （弃用：当前同类型武士个数）
     */
    int addWarrior(Warrior* warrior);

public:
    /**
     * @brief 红方所用的武士生成器。
     *
     */
    const static WarriorGenerator redGenerator;

    /**
     * @brief 蓝方所用的武士生成器。
     *
     */
    const static WarriorGenerator blueGenerator;
    Headquarter(const std::string& name, int life, const WarriorGenerator warriorGenerator)
        : name(name), life(life), warriorGenerator(warriorGenerator) {}

    /**
     * @brief 司令部的析构函数。
     * 需要释放所有武士。此过程也会释放武士所拥有的全部武器。
     */
    ~Headquarter() {
        for (auto& i : warriorList) {
            delete i.second;
        }
    }
    const std::string& getName() const {
        return name;
    }
    inline int getLife() const {
        return life;
    }

    /**
     * @brief 获取当前司令部所拥有的武士个数。
     *
     * @return int 武士个数。
     */
    int getNum() const {
        return warriorList.size();
    }

    /**
     * @brief 从该司令部中移走一名武士。
     * 同时命令该武士消亡。
     * @param number 要移走的武士编号。
     */
    void removeWarrior(int number);

    /**
     * @brief 令该司令部生成下一名武士。
     * 若生成符合规则，则添加到武士列表。
     * @return Warrior*
     */
    Warrior* generateWarrior();

    /**
     * @brief 检查本司令部的逃跑 Lion。
     * 若有，则令它们消亡。
     */
    void checkEscapedLion();

    /**
     * @brief 输出本司令部的报告。
     *
     */
    void printInfo() const {
        Broadcast::output(BroadcastType::HeadquarterReport, life, " elements in ", name,
                          " headquarter");
    }
};

int Sword::attack(int force, Warrior* enemy) {
    enemy->loseLife(getForce(force));
    return 0;
}

int Bomb::attack(int force, Warrior* enemy) {
    enemy->loseLife(getForce(force));
    available = false;
    return getForce(force) / 2;
}

int Arrow::attack(int force, Warrior* enemy) {
    if (used) {
        enemy->loseLife(getForce(force));
        available = false;
    } else {
        enemy->loseLife(getForce(force));
        used = true;
    }
    return 0;
}

Warrior* Headquarter::WarriorGenerator::operator()(Headquarter* owner) const {
    return generateFunction(owner->nextWarriorNumber, owner, owner->life);
}

const Headquarter::WarriorGenerator Headquarter::redGenerator = [](int no, Headquarter* owner,
                                                                   int life) -> Warrior* {
    switch (no % 5) {
        case 1: return new Iceman(no, owner);
        case 2: return new Lion(no, owner, life - initialLife[3]);
        case 3: return new Wolf(no, owner);
        case 4: return new Ninja(no, owner);
        case 0: return new Dragon(no, owner, 1.f * (life - initialLife[0]) / initialLife[0]);
    }
    return nullptr;
};

const Headquarter::WarriorGenerator Headquarter::blueGenerator = [](int no, Headquarter* owner,
                                                                    int life) -> Warrior* {
    switch (no % 5) {
        case 1: return new Lion(no, owner, life - initialLife[3]);
        case 2: return new Dragon(no, owner, 1.f * (life - initialLife[0]) / initialLife[0]);
        case 3: return new Ninja(no, owner);
        case 4: return new Iceman(no, owner);
        case 0: return new Wolf(no, owner);
    }
    return nullptr;
};

int Headquarter::addWarrior(Warrior* warrior) {
    warriorList.insert(std::pair<int, Warrior*>(nextWarriorNumber, warrior));
    nextWarriorNumber++;
    life -= warrior->getLife();
    // 废弃代码，来自第一题
    // int num = 0;
    // for (auto i : warriorList) {
    //     if (typeid(*warrior) == typeid(*(i.second)))
    //         num++;
    // }
    // return num;
    return 0;
}

void Headquarter::removeWarrior(int number) {
    warriorList.erase(number);
}

Warrior* Headquarter::generateWarrior() {
    if (stopped)
        return nullptr;
    // 尝试生成下一个武士
    Warrior* next = warriorGenerator(this);
    // 若无法生成（生命元不足），则令其消亡
    if (next->getLife() > life) {
        delete next;
        // 此题要求不再生成
        stopped = true;
        return nullptr;
    }
    addWarrior(next);
    Broadcast::output(BroadcastType::WarriorBorn, name, ' ', next->getName(), ' ',
                      next->getNumber(), " born", next->getBornLog());
    return next;
}

void Headquarter::checkEscapedLion() {
    // 无法边删除元素边检测（因为删除元素的同时迭代器在发生变化），
    // 因此不断重复检测直至无法删除
    bool found = true;
    while (found) {
        found = false;
        for (auto i = warriorList.begin(); i != warriorList.end(); ++i) {
            // 若为 Lion 且应当逃跑，则移出列表并令其消亡
            if (typeid(*(i->second)) == typeid(Lion) &&
                dynamic_cast<Lion*>(i->second)->isEscaping()) {
                Broadcast::output(BroadcastType::LionEscape, name, " lion ", i->first, " ran away");
                warriorList.erase(i);
                found = true;
                break;
            }
        }
    }
}

/**
 * @brief 城市类。
 * 处理城市中发生的所有事件。
 */
class City {
private:
    /**
     * @brief 城市编号。
     *
     */
    int number;

    /**
     * @brief 该城市所停留的红色武士。
     * 若不存在，则为空。
     */
    Warrior* redWarrior = nullptr;

    /**
     * @brief 该城市所停留的蓝色武士。
     * 若不存在，则为空。
     */
    Warrior* blueWarrior = nullptr;

    /**
     * @brief 处理战斗的结果。
     * 对于胜利者，获得战利品；对于失败者，令其消亡。
     * @param winner 胜利者。
     * @param loser 失败者。
     */
    void dealWithResult(Warrior* winner, Warrior* loser) {
        winner->getTrophy(loser);
        // 将其移出所在司令部，然后令其消亡
        loser->owner->removeWarrior(loser->getNumber());
        delete loser;
        // 若 Dragon 获胜，则欢呼
        if (typeid(*winner) == typeid(Dragon)) {
            Broadcast::output(BroadcastType::Battle, winner->owner->getName(), " dragon ",
                              winner->getNumber(), " yelled in city ", number);
        }
    }

    /**
     * @brief 判断战斗是否结束。
     * 当局面不再变化或者双方存在死亡战斗结束。
     * @return true 战斗已结束。
     * @return false 战斗需继续。
     */
    bool checkResult() {
        if (redWarrior->isDied() && blueWarrior->isDied()) {
            // 若双方皆死亡
            Broadcast::output(BroadcastType::Battle, "both red ", redWarrior->getName(), ' ',
                              redWarrior->getNumber(), " and blue ", blueWarrior->getName(), ' ',
                              blueWarrior->getNumber(), " died in city ", number);
            redWarrior->owner->removeWarrior(redWarrior->getNumber());
            delete redWarrior;
            redWarrior = nullptr;
            blueWarrior->owner->removeWarrior(blueWarrior->getNumber());
            delete blueWarrior;
            blueWarrior = nullptr;
            return true;
        } else if (redWarrior->isDied()) {
            // 若红方死亡
            Broadcast::output(BroadcastType::Battle, "blue ", blueWarrior->getName(), ' ',
                              blueWarrior->getNumber(), " killed red ", redWarrior->getName(), ' ',
                              redWarrior->getNumber(), " in city ", number, " remaining ",
                              blueWarrior->getLife(), " elements");
            dealWithResult(blueWarrior, redWarrior);
            redWarrior = nullptr;
            return true;
        } else if (blueWarrior->isDied()) {
            // 若蓝方死亡
            Broadcast::output(BroadcastType::Battle, "red ", redWarrior->getName(), ' ',
                              redWarrior->getNumber(), " killed blue ", blueWarrior->getName(), ' ',
                              blueWarrior->getNumber(), " in city ", number, " remaining ",
                              redWarrior->getLife(), " elements");
            dealWithResult(redWarrior, blueWarrior);
            blueWarrior = nullptr;
            return true;
        } else if (redWarrior->canChange() && blueWarrior->canChange()) {
            // 若局面不再发生变化
            Broadcast::output(BroadcastType::Battle, "both red ", redWarrior->getName(), ' ',
                              redWarrior->getNumber(), " and blue ", blueWarrior->getName(), ' ',
                              blueWarrior->getNumber(), " were alive in city ", number);
            // 若存在 Dragon，则仍要欢呼
            if (typeid(*redWarrior) == typeid(Dragon)) {
                Broadcast::output(BroadcastType::Battle, redWarrior->owner->getName(), " dragon ",
                                  redWarrior->getNumber(), " yelled in city ", number);
            }
            if (typeid(*blueWarrior) == typeid(Dragon)) {
                Broadcast::output(BroadcastType::Battle, blueWarrior->owner->getName(), " dragon ",
                                  blueWarrior->getNumber(), " yelled in city ", number);
            }
            return true;
        }
        return false;
    }

    /**
     * @brief 处理从某侧前进而来的武士。
     * 若 @c fromEast 参数为真，则该武士从东侧而来；
     * 否则该武士从西侧而来。
     * @param fromEast 是否从东侧前进而来。
     * @param warrior 武士。
     */
    void arrivedFrom(bool fromEast, Warrior* warrior) {
        // 如果是 Lion，需要减少忠诚度
        if (typeid(*warrior) == typeid(Lion)) {
            Lion* lion = dynamic_cast<Lion*>(warrior);
            if (lion->isEscaping()) {
                delete lion;
                return;
            } else
                lion->decreaseLoyalty();
        }
        // 如果是 Iceman，需要减少生命值
        if (typeid(*warrior) == typeid(Iceman)) {
            dynamic_cast<Iceman*>(warrior)->stepDecrease();
        }
        (fromEast ? blueWarrior : redWarrior) = warrior;
    }

public:
    // 包含此城市的地图
    friend class Map;

    /**
     * @brief 东侧城市。
     *
     */
    City* eastCity;

    /**
     * @brief 西侧城市。
     *
     */
    City* westCity;
    City(int number) : number(number) {}

    /**
     * @brief 处理武士从本城市向东侧出发。
     *
     */
    void marchToEast() {
        // 若本城市有红色武士且东侧有城市（非司令部）执行
        if (redWarrior && eastCity) {
            eastCity->arrivedFrom(false, redWarrior);
            redWarrior = nullptr;
        }
    }

    /**
     * @brief 处理武士从本城市向西侧出发。
     *
     */
    void marchToWest() {
        // 若本城市有蓝色武士且西侧有城市（非司令部）执行
        if (blueWarrior && westCity) {
            westCity->arrivedFrom(true, blueWarrior);
            blueWarrior = nullptr;
        }
    }

    /**
     * @brief 处理 Wolf 抢武器。
     *
     */
    void wolfGetArmament() {
        // 仅当双方武士见面时执行
        if (!redWarrior || !blueWarrior)
            return;
        // 若任意一方为 Wolf，则抢夺并输出
        if (typeid(*redWarrior) == typeid(Wolf)) {
            Wolf* redWolf = dynamic_cast<Wolf*>(redWarrior);
            std::string result = redWolf->requestArmaments(blueWarrior);
            if (result == "")
                return;
            Broadcast::output(BroadcastType::WolfGetArmament, "red wolf ", redWolf->getNumber(),
                              " took ", result, " from blue ", blueWarrior->getName(), ' ',
                              blueWarrior->getNumber(), " in city ", number);
        } else if (typeid(*blueWarrior) == typeid(Wolf)) {
            Wolf* blueWolf = dynamic_cast<Wolf*>(blueWarrior);
            std::string result = blueWolf->requestArmaments(redWarrior);
            if (result == "")
                return;
            Broadcast::output(BroadcastType::WolfGetArmament, "blue wolf ", blueWolf->getNumber(),
                              " took ", result, " from red ", redWarrior->getName(), ' ',
                              redWarrior->getNumber(), " in city ", number);
        }
    }

    /**
     * @brief 处理武士战斗相关事件。
     *
     */
    void battle() {
        // 仅当双方武士见面时执行
        if (!redWarrior || !blueWarrior)
            return;
        // 双方排列武器
        redWarrior->sortArmaments();
        blueWarrior->sortArmaments();
        // 确定先手
        if (number % 2) {
            redWarrior->attack(blueWarrior);
        }
        // 时刻检查局面并战斗
        while (true) {
            if (checkResult())
                return;
            blueWarrior->attack(redWarrior);
            if (checkResult())
                return;
            redWarrior->attack(blueWarrior);
        }
    }

    /**
     * @brief 输出当前城市的武士信息。
     *
     */
    void printWarriorInfo() {
        if (redWarrior) {
            Broadcast::output(BroadcastType::WarriorReport, "red ", redWarrior->getName(), ' ',
                              redWarrior->getNumber(), " has ", redWarrior->getArmamentDetail(),
                              "and ", redWarrior->getLife(), " elements");
        }
        if (blueWarrior) {
            Broadcast::output(BroadcastType::WarriorReport, "blue ", blueWarrior->getName(), ' ',
                              blueWarrior->getNumber(), " has ", blueWarrior->getArmamentDetail(),
                              "and ", blueWarrior->getLife(), " elements");
        }
    }

    /**
     * @brief 输出当前城市的前进信息。
     *
     */
    void printMarchResult() const;
};

void City::printMarchResult() const {
    if (redWarrior) {
        if (!eastCity) {
            // 若抵达司令部
            Broadcast::output(BroadcastType::WarriorMarch, "red ", redWarrior->getName(), ' ',
                              redWarrior->getNumber(), " reached blue headquarter with ",
                              redWarrior->getLife(), " elements and force ",
                              redWarrior->getForce());
            Broadcast::output(BroadcastType::WarriorMarch, "blue headquarter was taken");
            // 游戏即将结束，调整输出时间限制到现在
            timeLimit = Broadcast::hour * 60 + int(BroadcastType::WarriorMarch);
        } else {
            Broadcast::output(BroadcastType::WarriorMarch, "red ", redWarrior->getName(), ' ',
                              redWarrior->getNumber(), " marched to city ", number, " with ",
                              redWarrior->getLife(), " elements and force ",
                              redWarrior->getForce());
        }
    }
    if (blueWarrior) {
        if (!westCity) {
            // 若抵达司令部
            Broadcast::output(BroadcastType::WarriorMarch, "blue ", blueWarrior->getName(), ' ',
                              blueWarrior->getNumber(), " reached red headquarter with ",
                              blueWarrior->getLife(), " elements and force ",
                              blueWarrior->getForce());
            Broadcast::output(BroadcastType::WarriorMarch, "red headquarter was taken");
            // 游戏即将结束，调整输出时间限制到现在
            timeLimit = Broadcast::hour * 60 + int(BroadcastType::WarriorMarch);
        } else {
            Broadcast::output(BroadcastType::WarriorMarch, "blue ", blueWarrior->getName(), ' ',
                              blueWarrior->getNumber(), " marched to city ", number, " with ",
                              blueWarrior->getLife(), " elements and force ",
                              blueWarrior->getForce());
        }
    }
}

/**
 * @brief 包装所有城市的地图类。
 * 使用双向链表存储所有城市。
 */
class Map {
private:
    /**
     * @brief 西侧司令部城市。
     *
     */
    City* westHead;

    /**
     * @brief 东侧司令部城市。
     *
     */
    City* eastHead;

    /**
     * @brief 从西向东释放城市。
     * 释放双向链表。
     * @param city 释放其之后（东）的城市。
     */
    void removeCities(City* city) {
        if (city->eastCity) {
            removeCities(city->eastCity);
            delete city;
        }
    }

public:
    Map(int n) {
        // 一个城市没法玩
        if (n < 1)
            throw "Need more cities";
        westHead = new City(0);
        // 构建双向链表
        City* current = westHead;
        current->westCity = nullptr;
        for (int i = 0; i <= n; i++) {
            current->eastCity = new City(i + 1);
            current->eastCity->westCity = current;
            current = current->eastCity;
        }
        current->eastCity = nullptr;
        eastHead = current;
    }

    /**
     * @brief 向红方司令部城市添加一个武士。
     *
     * @param warrior 武士。
     */
    void addRed(Warrior* warrior) {
        westHead->redWarrior = warrior;
    }

    /**
     * @brief 向蓝方司令部城市添加一个武士。
     *
     * @param warrior 武士。
     */
    void addBlue(Warrior* warrior) {
        eastHead->blueWarrior = warrior;
    }

    /**
     * @brief 令所有城市中的武士前进，并输出信息。
     * 司令部占领信息也将被遍历。
     */
    void marchAll() {
        // 从西向东执行蓝色武士的前进过程
        City* current = westHead;
        while (current) {
            current->marchToWest();
            current = current->eastCity;
        }
        // 从东向西执行红色武士的前进过程
        current = eastHead;
        while (current) {
            current->marchToEast();
            current = current->westCity;
        }
        // 从西向东输出前进信息
        current = westHead;
        while (current) {
            current->printMarchResult();
            current = current->eastCity;
        }
    }

    /**
     * @brief 令所有 Wolf 开始抢夺武器。
     *
     */
    void allWolfGetArmament() {
        // 从西向东遍历城市中的 Wolf。
        City* current = westHead;
        while (current) {
            current->wolfGetArmament();
            current = current->eastCity;
        }
    }

    /**
     * @brief 令所有城市开始战斗。
     *
     */
    void battleAll() {
        // 从西向东开始战斗。
        City* current = westHead;
        while (current) {
            current->battle();
            current = current->eastCity;
        }
    }

    /**
     * @brief 令所有城市输出武士报告。
     *
     */
    void printAllWarriorsInfo() {
        // 从西向东输出报告。
        City* current = westHead;
        while (current) {
            current->printWarriorInfo();
            current = current->eastCity;
        }
    }
    
    /**
     * @brief 地图类的析构函数。
     * 调用双向链表的释放。
     */
    ~Map() {
        removeCities(westHead);
    }
};

}  // namespace WoW

/**
 * @brief 主函数。
 * 函数执行的入口点。
 * @return int 程序返回值。
 */
int main() {
#ifndef ONLINE_JUDGE
    std::freopen("WoW_in.txt", "r", stdin);
    std::freopen("WoW_out.txt", "w", stdout);
#endif
    // 测试组数
    int t;
    std::cin >> t;
    for (int j = 1; j <= t; j++) {
        // 输入基本信息
        int generalLife, cityNumber;
        std::cin >> generalLife >> cityNumber >> WoW::lionDecrease >> WoW::timeLimit;
        WoW::isOver = false;
        // 生成地图（包含城市）和两个司令部
        WoW::Map map(cityNumber);
        WoW::Headquarter red("red", generalLife, WoW::Headquarter::redGenerator);
        WoW::Headquarter blue("blue", generalLife, WoW::Headquarter::blueGenerator);
        // 输入武士信息
        for (auto& i : WoW::initialLife) {
            std::cin >> i;
        }
        for (auto& i : WoW::initialForce) {
            std::cin >> i;
        }
        std::cout << "Case " << j << ':' << std::endl;
        // 每一小时循环一次，直至到达时间限制
        for (WoW::Broadcast::hour = 0; !WoW::isOver; WoW::Broadcast::hour++) {
            map.addRed(red.generateWarrior());
            map.addBlue(blue.generateWarrior());
            red.checkEscapedLion();
            blue.checkEscapedLion();
            map.marchAll();
            map.allWolfGetArmament();
            map.battleAll();
            red.printInfo();
            blue.printInfo();
            map.printAllWarriorsInfo();
        }
    }
    return 0;
}