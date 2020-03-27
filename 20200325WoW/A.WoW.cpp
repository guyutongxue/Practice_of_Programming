#include <algorithm>
#include <array>
#include <cassert>
#include <exception>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
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
std::array<int, 5> initialLife;

/**
 * @brief 武士的初始武力值。
 *
 */
std::array<int, 5> initialForce;

/**
 * @brief Lion 的忠诚度衰减参数。
 *
 */
int lionDecrease;

/**
 * @brief Arrow 的攻击力参数。
 *
 */
int arrowForce;

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
 * @brief "无穷大"。
 *
 */
const int& INFTY = std::numeric_limits<int>::max();

/**
 * @brief 标记输出的类型，用以决定分钟数。
 * 使用枚举值来标记分钟。
 */
enum class BroadcastType : int {
    WarrierBorn = 0,   /**< 武士被生成 */
    LionEscape = 5,    /**< Lion 逃跑 */
    WarrierMarch = 10, /**< 武士前进（含占领） */
    // GenerateElements = 20,  /**< 城市生成生命元 */
    CollectElements = 30,   /**< 单个武士获取生命元 */
    ArrowShot = 35,         /**< Arrow 放出 */
    BombUsed = 38,          /**< 武士使用 Bomb*/
    Battle = 40,            /**< 武士战斗（进攻、反击、战死、欢呼等） */
    HeadquarterReport = 50, /**< 司令部报告 */
    WarrierReport = 55      /**< 武士报告 */
};

/**
 * @brief 处理事件广播的静态类。
 * 所有事件的报告都将由此类中静态函数处理。
 */
class Broadcast {
private:
    /**
     * @brief 用于处理输出的字符串流。
     *
     */
    static std::stringstream ss;

    /**
     * @brief 生成内容的字符串形式。
     *
     * @tparam T 内容类型。
     * @param content 内容。
     */
    template <typename T>
    static void generateContent(T content) {
        ss << content;
    }

    /**
     * @brief 生成内容的字符串形式。
     *
     * @tparam T 解包得到的第一个内容参数。
     * @tparam Us 其余内容参数包。
     * @param content 解包得到的第一个内容。
     * @param pack 其余内容。
     */
    template <typename T, typename... Us>
    static void generateContent(T content, Us... pack) {
        generateContent(content);
        generateContent(pack...);
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

    /**
     * @brief 组合一些类型的数据，并以字符串形式并返回，但不输出。
     * 也不需要加上时间标签。
     * @tparam Ts 内容类型。
     * @param contents 内容。
     * @return std::string 组合的结果。
     */
    template <typename... Ts>
    static std::string combineString(Ts... contents) {
        // reset stringstream
        ss.str("");
        ss.clear();
        generateContent(contents...);
        return ss.str();
    }

    // 不允许声明 Broadcast 的任何对象
    virtual ~Broadcast() = 0;
};

int Broadcast::hour = 0;
std::stringstream Broadcast::ss;

class Warrier;

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
     * @brief 武器的耐久值。
     * 对于 Sword 是其攻击力；
     * 对于 Bomb 是 1；
     * 对于 Arrow 是 3。
     */
    int endurance;

    /**
     * @brief 武器的武力值。
     * 对于 Bomb 是无穷大。
     */
    int force = 0;

public:
    /**
     * @brief 生成武器基类。
     * 编号是必需的。
     * @param number 编号。
     */
    Armament(int number) : number(number) {}

    /**
     * @brief 判断武器是否可用。
     * 依据：耐久值是否为正。
     * @return true 武器仍可用。
     * @return false 武器不可用。
     */
    bool isAvailable() const {
        return endurance > 0;
    }
    int getNumber() const {
        return number;
    }
    int getForce() const {
        return force;
    }
    int getEndurance() const {
        return endurance;
    }

    /**
     * @brief 使用 Bomb 武器攻击。
     *
     * @param force 使用者武力值。
     * @param enemy 被攻击对象。
     * @return int 对使用者的伤害。
     */
    virtual int attack(Warrier* enemy) = 0;

    /**
     * @brief 获取武器名称。
     * 此函数通过多态实现不同武器的不同输出。
     * @return const char* 武器名称的 C 风格常量字符串。
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
    Sword(int force) : Armament(0) {
        this->force = endurance = force;
    }
    int attack(Warrier*) override;
    const char* getName() const override {
        return "sword";
    }
};

/**
 * @brief Bomb 武器类。
 * 用一次就废弃，使同归于尽。
 */
class Bomb : public Armament {
public:
    Bomb() : Armament(1) {
        endurance = 1;
        force = INFTY;
    }
    int attack(Warrier*) override;
    const char* getName() const override {
        return "bomb";
    }
};

/**
 * @brief Arrow 武器类。
 * 可以使用三次，对前方敌人造成伤害。
 */
class Arrow : public Armament {
public:
    Arrow() : Armament(2) {
        endurance = 3;
        force = arrowForce;
    }
    int attack(Warrier*) override;

    const char* getName() const override {
        return "arrow";
    }
};

class Headquarter;

/**
 * @brief 武士类。
 * 所有武士的共同属性、方法记录于此。
 */
class Warrier {
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
     * @brief 武士武力值。
     *
     */
    int force;

    Sword* sword = nullptr;
    Bomb* bomb = nullptr;
    Arrow* arrow = nullptr;

public:
    /**
     * @brief 当前武士所归属的司令部。
     *
     */
    Headquarter* owner;

    const int getLife() const {
        return life;
    }
    const int getNumber() const {
        return number;
    }
    const int getForce() const {
        return force;
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
     * @brief 获取武器指针。
     *
     * @tparam T 想要获取的武器种类。
     * @return Armament* 武器指针；若无返回 nullptr。
     */
    template <typename T>
    Armament* getArmament() const {
        static_assert(std::is_base_of<Armament, T>::value, "Should use Armament type.");
        if (typeid(T) == typeid(Sword))
            return sword;
        if (typeid(T) == typeid(Bomb))
            return bomb;
        if (typeid(T) == typeid(Arrow))
            return arrow;
        return nullptr;
    }

    /**
     * @brief 检查武士是否拥有武器。
     *
     * @tparam T 要检查的武器类型。
     * @return true 该武士拥有此武器。
     * @return false 该武士未拥有此武器。
     */
    template <typename T>
    bool checkArmament() const {
        static_assert(std::is_base_of<Armament, T>::value, "Should use Armament type.");
        if (typeid(T) == typeid(Sword))
            return sword;
        if (typeid(T) == typeid(Bomb))
            return bomb;
        if (typeid(T) == typeid(Arrow))
            return arrow;
        return false;
    }

    /**
     * @brief 武士受到伤害。
     *
     * @param force 伤害大小。
     */
    void loseLife(int force) {
        life -= force;
    }

    /**
     * @brief 武士增加生命值。
     * 用于司令部对其的奖励。
     * @param life 奖励的生命值。
     */
    void addLife(int life) {
        this->life += life;
    }

    virtual const char* getName() const = 0;

    /**
     * @brief 获取武士出生的详细记录。
     * 对于 Lion 和 Dragon 仍需要更多的属性被输出。
     * @return const std::string 输出的内容。
     */
    virtual const std::string getBornLog() const = 0;

    /**
     * @brief 武士的构造函数。
     *
     * @param number 武士编号。
     * @param owner 武士拥有者（司令部）。
     * @param force 武士的武力值。
     */
    Warrier(int number, Headquarter* owner, int force)
        : number(number), owner(owner), force(force) {}

    /**
     * @brief 武士攻击敌人。
     *
     * @param enemy 敌人。
     */
    virtual void attack(Warrier* enemy) {
        if (sword)
            sword->attack(enemy);
        enemy->loseLife(force);
        cleanArmaments();
    }

    /**
     * @brief 武士回击。
     *
     * @param enemy 敌人。
     */
    void counterattack(Warrier* enemy) {
        if (sword)
            sword->attack(enemy);
        enemy->loseLife(force / 2);
        cleanArmaments();
    }

    /**
     * @brief 武士清理武器。
     * 对于已经用光的武器，进行清空。
     */
    void cleanArmaments() {
        if (sword && !sword->isAvailable()) {
            delete sword;
            sword = nullptr;
        }
        if (bomb && !bomb->isAvailable()) {
            delete bomb;
            bomb = nullptr;
        }
        if (arrow && !arrow->isAvailable()) {
            delete arrow;
            arrow = nullptr;
        }
    }

    /**
     * @brief 获取武士所持有的武器详情。
     * 在输出武士报告时被调用。
     * @return std::string 字符串格式的武器详情。
     */
    std::string getArmamentDetail() const {
        std::string res;
        bool isFirst = true;
        if (arrow) {
            res += Broadcast::combineString((isFirst ? isFirst = false, "" : ","), "arrow(",
                                            arrow->getEndurance(), ")");
        }
        if (bomb) {
            res += Broadcast::combineString((isFirst ? isFirst = false, "" : ","), "bomb");
        }
        if (sword) {
            res += Broadcast::combineString((isFirst ? isFirst = false, "" : ","), "sword(",
                                            sword->getEndurance(), ")");
        }
        if (isFirst)
            res = "no weapon";
        return res;
    }

    /**
     * @brief 武士析构函数。
     * 需要释放所有所持有的武器。
     */
    ~Warrier() {
        delete sword;
        delete bomb;
        delete arrow;
    }
};

/**
 * @brief Dragon 武士类。
 * 士气值达到某条件时会欢呼。
 */
class Dragon : public Warrier {
private:
    /**
     * @brief Dragon 的士气值。
     *
     */
    double morale;

    /**
     * @brief 判断 Dragon 是否可以欢呼。
     * 当其为先手时才会设置为 true。
     */
    bool yell = false;

public:
    Dragon(int number, Headquarter* owner, double morale)
        : Warrier(number, owner, initialForce[0]), morale(morale) {
        life = initialLife[0];
        // 生成武器
        sword = number % 3 == 0 ? new Sword(force / 5) : nullptr;
        bomb = number % 3 == 1 ? new Bomb : nullptr;
        arrow = number % 3 == 2 ? new Arrow : nullptr;
        // 若 Sword 为 0，则清空
        cleanArmaments();
    }

    double getMorale() const {
        return morale;
    }

    /**
     * @brief 减少士气。
     *
     */
    void decreaseMorale() {
        morale -= 0.2;
    }

    /**
     * @brief 增加士气。
     *
     */
    void increaseMorale() {
        morale += 0.2;
    }

    /**
     * @brief 设置是否可能欢呼。
     * 仅当其应该是先手时才欢呼。
     * @param dest 设置值。
     */
    void setYell(bool dest) {
        yell = dest;
    }

    /**
     * @brief 判断是否欢呼。
     * 当设置为先手，且士气达到一定程度时才欢呼。
     * @return true 该欢呼。
     * @return false 不该欢呼。
     */
    bool shouldYell() {
        return yell && morale > 0.8;
    }

    const char* getName() const override {
        return "dragon";
    }

    const std::string getBornLog() const override {
        std::stringstream ss;
        ss << "\nIts morale is " << std::fixed << std::setprecision(2) << morale;
        return ss.str();
    }
};

/**
 * @brief Ninja 武士类。
 * 初始持有两把武器，且不会被自己伤害。
 */
class Ninja : public Warrier {
public:
    Ninja(int number, Headquarter* owner) : Warrier(number, owner, initialForce[1]) {
        life = initialLife[1];
        // 生成武器，此处使用了“反”的方法
        sword = number % 3 == 1 ? nullptr : new Sword(force / 5);
        bomb = number % 3 == 2 ? nullptr : new Bomb;
        arrow = number % 3 == 0 ? nullptr : new Arrow;
        cleanArmaments();
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
 * 前进会损失生命值，增加武力值。
 */
class Iceman : public Warrier {
private:
    bool evenStep = true;

public:
    Iceman(int number, Headquarter* owner) : Warrier(number, owner, initialForce[2]) {
        life = initialLife[2];
        sword = number % 3 == 0 ? new Sword(force / 5) : nullptr;
        bomb = number % 3 == 1 ? new Bomb : nullptr;
        arrow = number % 3 == 2 ? new Arrow : nullptr;
        cleanArmaments();
    }
    const char* getName() const override {
        return "iceman";
    }

    /**
     * @brief Iceman 损失生命值，增加武力值。
     * 每前进一步损失自身生命值的 [1/10]。
     * （函数名源自第三题，未做更改。）
     */
    void stepDecrease() {
        evenStep = !evenStep;
        if (evenStep) {
            life = (life <= 9 ? 1 : life - 9);
            force += 20;
        }
    }
    const std::string getBornLog() const override {
        return "";
    }
};

/**
 * @brief Lion 武士类。
 * 当忠诚度不足时会逃跑。
 */
class Lion : public Warrier {
private:
    /**
     * @brief 忠诚度。
     *
     */
    int loyalty;

    /**
     * @brief 记录战斗前生命值。
     * 用于死亡后给予对手。
     */
    int originalLife;

public:
    Lion(int number, Headquarter* owner, double loyalty)
        : Warrier(number, owner, initialForce[3]), loyalty(loyalty) {
        life = initialLife[3];
    }

    /**
     * @brief 保存此时的生命值为战斗前生命值。
     *
     */
    void saveOriginalLife() {
        originalLife = life;
    }

    /**
     * @brief 获取战斗前生命值。
     *
     * @return int 战斗前生命值。
     */
    int getOriginalLife() const {
        return originalLife;
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
class Wolf : public Warrier {
public:
    Wolf(int number, Headquarter* owner) : Warrier(number, owner, initialForce[4]) {
        life = initialLife[4];
    }

    /**
     * @brief Wolf 战胜后取走敌人武器。
     * （函数名来自第三题，未更改。）
     * @param enemy 对方敌人。
     */
    void requestArmaments(Warrier* enemy) {
        // 只有当自己没有且对方有的时候拿走。
        if (!sword && enemy->checkArmament<Sword>()) {
            // 不同于上次，这次复制一个相同的对象，并让敌人的武器自己消亡
            sword = new Sword(*dynamic_cast<Sword*>(enemy->getArmament<Sword>()));
        }
        if (!bomb && enemy->checkArmament<Bomb>()) {
            bomb = new Bomb(*dynamic_cast<Bomb*>(enemy->getArmament<Bomb>()));
        }
        if (!arrow && enemy->checkArmament<Arrow>()) {
            arrow = new Arrow(*dynamic_cast<Arrow*>(enemy->getArmament<Arrow>()));
        }
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
    class WarrierGenerator {
    public:
        /**
         * @brief 武士生成函数对象。
         * 确定以如何顺序生成武士。
         */
        const std::function<Warrier*(int, Headquarter*, int)> generateFunction;

        /**
         * @brief 武士生成器构造函数。
         * 使用函数对象（可为 Lambda 表达式）构造一个生成器。
         * 这个函数应接收 @c int, @c Headquarter*, @c int 三个参数，
         * 分别为要生成的武士编号、司令部指针和司令部的生命元数量。
         * 返回一个 @c Warrier* 为生成的武士。
         * @tparam T 函数对象类。
         * @param function 函数对象。
         */
        template <typename T>
        WarrierGenerator(const T& function) : generateFunction(function) {}

        /**
         * @brief 执行武士生成过程。
         * 直接通过仿函数的形式生成武士。
         * @param headquarter 要生成武士的司令部。
         * @return Warrier* 生成得到的武士。
         */
        Warrier* operator()(Headquarter* headquarter) const;
        ~WarrierGenerator() {}
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
    std::map<int, Warrier*> warrierList;

    /**
     * @brief 司令部所拥有的生命元个数。
     *
     */
    int life;

    /**
     * @brief 司令部即将生成的武士编号。
     *
     */
    int nextWarrierNumber = 1;

    /**
     * @brief 标记司令部是否应停止生成武士。
     *
     */
    // bool stopped = false;

    /**
     * @brief 司令部中含有的敌人数量。
     * 到达 2 时被摧毁。
     */
    int enemyNum = 0;

    /**
     * @brief 本司令部所使用的武士生成器。
     *
     */
    const WarrierGenerator warrierGenerator;

    /**
     * @brief 向该司令部添加一名武士。
     *
     * @param warrier 要被添加的武士。
     * @return int （弃用：当前同类型武士个数）
     */
    int addWarrier(Warrier* warrier);

    /**
     * @brief 从对面过来的敌方武士。
     * 若不存在，则为空。
     */
    Warrier* arrivedEnemyWarrier = nullptr;

public:
    /**
     * @brief 红方所用的武士生成器。
     *
     */
    const static WarrierGenerator redGenerator;

    /**
     * @brief 蓝方所用的武士生成器。
     *
     */
    const static WarrierGenerator blueGenerator;
    Headquarter(const std::string& name, int life, const WarrierGenerator warrierGenerator)
        : name(name), life(life), warrierGenerator(warrierGenerator) {}

    /**
     * @brief 司令部的析构函数。
     * 需要释放所有武士。此过程也会释放武士所拥有的全部武器。
     */
    ~Headquarter() {
        for (auto& i : warrierList) {
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
     * @brief 增加司令部生命元数量。
     *
     * @param num 要增加的数量。
     */
    void addLife(int num) {
        life += num;
    }

    /**
     * @brief 减少司令部生命元数量。
     * 用于奖励武士。
     * @param num 要减少的数量。
     */
    void reduceLife(int num) {
        life -= num;
    }

    /**
     * @brief 获取当前司令部所拥有的武士个数。
     *
     * @return int 武士个数。
     */
    int getNum() const {
        return warrierList.size();
    }

    /**
     * @brief 从该司令部中移走一名武士。
     * 同时命令该武士消亡。
     * @param number 要移走的武士编号。
     */
    void removeWarrier(int number);

    /**
     * @brief 令该司令部生成下一名武士。
     * 若生成符合规则，则添加到武士列表。
     * @return Warrier*
     */
    Warrier* generateWarrier();

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

    /**
     * @brief 敌人到达司令部，并返回是否摧毁。
     *
     * @return true 到达后司令部便被摧毁。
     * @return false 到达后司令部未被摧毁。
     */
    bool enemyArrived(Warrier* warrier) {
        arrivedEnemyWarrier = warrier;
        enemyNum++;
        return enemyNum == 2;
    }

    /**
     * @brief 打印存放在此处的敌军武士的信息。
     * 如果没有这个，会漏掉。
     */
    void printArrivedEnemyInfo() {
        if (arrivedEnemyWarrier) {
            Broadcast::output(BroadcastType::WarrierReport, arrivedEnemyWarrier->owner->getName(),
                              ' ', arrivedEnemyWarrier->getName(), ' ',
                              arrivedEnemyWarrier->getNumber(), " has ",
                              arrivedEnemyWarrier->getArmamentDetail());
        }
    }
};

int Sword::attack(Warrier* enemy) {
    enemy->loseLife(force);
    force *= .8f;
    endurance = force;
    return 0;
}

int Bomb::attack(Warrier* enemy) {
    enemy->loseLife(INFTY);
    endurance = 0;
    return INFTY;
}

int Arrow::attack(Warrier* enemy) {
    enemy->loseLife(arrowForce);
    endurance--;
    return 0;
}

Warrier* Headquarter::WarrierGenerator::operator()(Headquarter* owner) const {
    return generateFunction(owner->nextWarrierNumber, owner, owner->life);
}

const Headquarter::WarrierGenerator Headquarter::redGenerator = [](int no, Headquarter* owner,
                                                                   int life) -> Warrier* {
    switch (no % 5) {
        case 1: return new Iceman(no, owner);
        case 2: return new Lion(no, owner, life - initialLife[3]);
        case 3: return new Wolf(no, owner);
        case 4: return new Ninja(no, owner);
        case 0: return new Dragon(no, owner, 1. * (life - initialLife[0]) / initialLife[0]);
    }
    return nullptr;
};

const Headquarter::WarrierGenerator Headquarter::blueGenerator = [](int no, Headquarter* owner,
                                                                    int life) -> Warrier* {
    switch (no % 5) {
        case 1: return new Lion(no, owner, life - initialLife[3]);
        case 2: return new Dragon(no, owner, 1. * (life - initialLife[0]) / initialLife[0]);
        case 3: return new Ninja(no, owner);
        case 4: return new Iceman(no, owner);
        case 0: return new Wolf(no, owner);
    }
    return nullptr;
};

int Headquarter::addWarrier(Warrier* warrier) {
    warrierList.insert(std::pair<int, Warrier*>(nextWarrierNumber, warrier));
    nextWarrierNumber++;
    life -= warrier->getLife();
    return 0;
}

void Headquarter::removeWarrier(int number) {
    delete warrierList[number];
    warrierList.erase(number);
}

Warrier* Headquarter::generateWarrier() {
    // 尝试生成下一个武士
    Warrier* next = warrierGenerator(this);
    // 若无法生成（生命元不足），则令其消亡
    if (next->getLife() > life) {
        delete next;
        // 此题要求等待
        return nullptr;
    }
    addWarrier(next);
    Broadcast::output(BroadcastType::WarrierBorn, name, ' ', next->getName(), ' ',
                      next->getNumber(), " born", next->getBornLog());
    return next;
}

void Headquarter::checkEscapedLion() {
    for (auto i = warrierList.begin(); i != warrierList.end();) {
        // 若为 Lion 且应当逃跑，则移出列表并令其消亡
        if (typeid(*(i->second)) == typeid(Lion) && dynamic_cast<Lion*>(i->second)->isEscaping()) {
            Broadcast::output(BroadcastType::LionEscape, name, " lion ", i->first, " ran away");
            warrierList.erase(i++);
        } else
            i++;
    }
}

/**
 * @brief 城市类。
 * 处理城市中发生的所有事件。
 */
class City {
public:
    // 包含此城市的地图
    friend class Map;

private:
    enum class Flag {
        Nothing, /**< 暂无旗帜。*/
        Red,     /**< 红方旗帜。*/
        Blue     /**< 蓝方旗帜。*/
    };

    /**
     * @brief 城市编号。
     *
     */
    int number;

    /**
     * @brief 生命元数目。
     *
     */
    int elementNum = 0;

    /**
     * @brief 该城市所停留的红色武士。
     * 若不存在，则为空。
     */
    Warrier* redWarrier = nullptr;

    /**
     * @brief 该城市所停留的蓝色武士。
     * 若不存在，则为空。
     */
    Warrier* blueWarrier = nullptr;

    /**
     * @brief 该城市所树立的旗帜。
     *
     */
    Flag flag = Flag::Nothing;

    /**
     * @brief 上一局的对战结果。
     * 若双亡、平手，则设置为 Nothing。
     */
    Flag lastWinner = Flag::Nothing;

    /**
     * @brief 旗帜是否更换。
     * 若旗帜被更换，则应输出。
     */
    bool shouldFlagRaised = false;

    /**
     * @brief 标记是否发生战斗。
     * 此标记用于给予奖励。
     */
    bool hasBattled = false;

    /**
     * @brief 保存战斗前 Lion 的生命值。
     * 用于战败后进行生命值转移。
     */
    void saveLionStatus() {
        if (redWarrier && typeid(*redWarrier) == typeid(Lion)) {
            dynamic_cast<Lion*>(redWarrier)->saveOriginalLife();
        }
        if (blueWarrier && typeid(*blueWarrier) == typeid(Lion)) {
            dynamic_cast<Lion*>(blueWarrier)->saveOriginalLife();
        }
    }

    /**
     * @brief 模拟一场战斗，判断某方是否必死。
     * 若必死，则在调用方后续使用 Bomb。
     * @param me 己方（欲使用 Bomb 方）。
     * @param enemy 敌方。
     * @param isFirst 己方是否为先手。
     * @return true 必死（应使用 Bomb）。
     * @return false 不应使用 Bomb。
     */
    bool simulateBattle(const Warrier* me, const Warrier* enemy, bool isFirst) {
        if (isFirst) {
            // 若己方先攻击
            int myLife = me->getLife(), enemyLife = enemy->getLife();
            if (me->checkArmament<Sword>())
                enemyLife -= me->getArmament<Sword>()->getForce();
            enemyLife -= me->getForce();
            // 若能把敌人打死，则不能用 Bomb
            if (enemyLife <= 0)
                return false;
            // 敌方是 Ninja 不还手
            if (typeid(*enemy) == typeid(Ninja))
                return false;
            if (enemy->checkArmament<Sword>())
                myLife -= enemy->getArmament<Sword>()->getForce();
            myLife -= (enemy->getForce() / 2);
            // 若反击后仍存活，则不能用 Bomb
            return myLife <= 0;
        } else {
            // 若敌方先攻击
            int myLife = me->getLife(), enemyLife = enemy->getLife();
            if (enemy->checkArmament<Sword>())
                myLife -= enemy->getArmament<Sword>()->getForce();
            myLife -= enemy->getForce();
            // 若敌方攻击后仍存活，则不能用 Bomb
            return myLife <= 0;
        }
    }

    /**
     * @brief 处理战斗的结果。
     * 对于胜利者，获得战利品；对于失败者，令其消亡。
     * @param winner 胜利者。
     * @param loser 失败者。
     * @param isCounterattack 是否为回击。
     */
    void dealWithResult(Warrier* winner, Warrier* loser) {
        // 若 Wolf 获胜，拿走对方武器
        if (typeid(*winner) == typeid(Wolf)) {
            dynamic_cast<Wolf*>(winner)->requestArmaments(loser);
        }
        // 若 Lion 战败，则转移生命值
        if (typeid(*loser) == typeid(Lion)) {
            // 若之前是负值，则改为 0
            winner->addLife(std::max(0, dynamic_cast<Lion*>(loser)->getOriginalLife()));
        }
        // 将失败者移出所在司令部
        loser->owner->removeWarrier(loser->getNumber());
        // 若 Dragon 获胜
        if (typeid(*winner) == typeid(Dragon)) {
            Dragon* dragon = dynamic_cast<Dragon*>(winner);
            dragon->increaseMorale();
            if (dragon->shouldYell())
                cachedLog.push(Broadcast::combineString(winner->owner->getName(), " dragon ",
                                                        winner->getNumber(), " yelled in city ",
                                                        number));
        }
        // 获取战利品的代码移至 uploadElement
    }

    /**
     * @brief 判断战斗是否结束。
     * 当局面不再变化或者双方存在死亡战斗结束。
     * @param isPrecheck 若此函数以判断 Arrow 射死为目的，则设置为 true
     * @return true 战斗已结束。
     * @return false 战斗需继续。
     */
    bool checkResult(bool isPrecheck = false) {
        if (redWarrier->isDied() && blueWarrier->isDied()) {
            // 若双方皆死亡（这种情况只能发生在双方都被 Arrow 射死时）
            redWarrier->owner->removeWarrier(redWarrier->getNumber());
            redWarrier = nullptr;
            blueWarrier->owner->removeWarrier(blueWarrier->getNumber());
            blueWarrier = nullptr;
            // lastWinner = Flag::Nothing;
            // 这种情况下不算发生一场战斗
            hasBattled = false;
            return true;
        }
        if (redWarrier->isDied()) {
            // 若红方非 Arrow 死亡
            if (!isPrecheck)
                cachedLog.push(Broadcast::combineString("red ", redWarrier->getName(), ' ',
                                                        redWarrier->getNumber(),
                                                        " was killed in city ", number));
            dealWithResult(blueWarrier, redWarrier);
            redWarrier = nullptr;
            // 更换旗帜，若连胜两次
            if (lastWinner == Flag::Blue) {
                if (flag != Flag::Blue)
                    shouldFlagRaised = true;
                flag = Flag::Blue;
            }
            lastWinner = Flag::Blue;
            return true;
        } else if (blueWarrier->isDied()) {
            // 若蓝方非 Arrow 死亡
            if (!isPrecheck)
                cachedLog.push(Broadcast::combineString("blue ", blueWarrier->getName(), ' ',
                                                        blueWarrier->getNumber(),
                                                        " was killed in city ", number));
            dealWithResult(redWarrier, blueWarrier);
            blueWarrier = nullptr;
            // 更换旗帜，若连胜两次
            if (lastWinner == Flag::Red) {
                if (flag != Flag::Red)
                    shouldFlagRaised = true;
                flag = Flag::Red;
            }
            lastWinner = Flag::Red;
            return true;
        } else {
            return false;
        }
    }

    /**
     * @brief 处理从某侧前进而来的武士。
     * 若 @c fromEast 参数为真，则该武士从东侧而来；
     * 否则该武士从西侧而来。
     * @param fromEast 是否从东侧前进而来。
     * @param warrier 武士。
     */
    void arrivedFrom(bool fromEast, Warrier* warrier) {
        // 如果是 Lion，需要减少忠诚度
        if (typeid(*warrier) == typeid(Lion)) {
            Lion* lion = dynamic_cast<Lion*>(warrier);
            if (lion->isEscaping()) {
                delete lion;
                return;
            }
        }
        // 如果是 Iceman，需要减少生命值
        if (typeid(*warrier) == typeid(Iceman)) {
            dynamic_cast<Iceman*>(warrier)->stepDecrease();
        }
        (fromEast ? blueWarrier : redWarrier) = warrier;
    }

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

    /**
     * @brief 对于边界城市，指向其司令部。
     * 否则，为 nullptr。
     */
    Headquarter* headquarter = nullptr;

    /**
     * @brief 战争事件的输出队列。
     * 由于战争事件输出无法保证顺序，故使用此结构保证输出的顺序。
     * 每得到一样输出，就将 Broadcast::combineString() 得到的
     * 字符串推入队列，在全部事件结束（收集生命元）后输出。
     */
    std::queue<std::string> cachedLog;

    City(int number) : number(number) {}

    /**
     * @brief 生成城市的生命元。
     * 每小时的第 20 分钟发生。
     */
    void generateElements() {
        elementNum += 10;
    }

    /**
     * @brief 单个武士获取城市中的生命元。
     *
     */
    void getElements() {
        if (redWarrier && !blueWarrier) {
            redWarrier->owner->addLife(elementNum);
            Broadcast::output(BroadcastType::CollectElements, "red ", redWarrier->getName(), ' ',
                              redWarrier->getNumber(), " earned ", elementNum,
                              " elements for his headquarter");
            elementNum = 0;
        } else if (blueWarrier && !redWarrier) {
            blueWarrier->owner->addLife(elementNum);
            Broadcast::output(BroadcastType::CollectElements, "blue ", blueWarrier->getName(), ' ',
                              blueWarrier->getNumber(), " earned ", elementNum,
                              " elements for his headquarter");
            elementNum = 0;
        }
    }

    /**
     * @brief 处理武士从本城市向东侧出发。
     *
     */
    void marchToEast() {
        // 若本城市有红色武士且东侧有城市（非司令部）执行
        if (redWarrier && eastCity) {
            eastCity->arrivedFrom(false, redWarrier);
            redWarrier = nullptr;
        }
    }

    /**
     * @brief 处理武士从本城市向西侧出发。
     *
     */
    void marchToWest() {
        // 若本城市有蓝色武士且西侧有城市（非司令部）执行
        if (blueWarrier && westCity) {
            westCity->arrivedFrom(true, blueWarrier);
            blueWarrier = nullptr;
        }
    }

    /**
     * @brief 发射 Arrow 到两侧城市。
     *
     */
    void shootArrow() {
        if (redWarrier && redWarrier->checkArmament<Arrow>() && eastCity && eastCity->blueWarrier) {
            Armament* arrow = redWarrier->getArmament<Arrow>();
            arrow->attack(eastCity->blueWarrier);
            redWarrier->cleanArmaments();
            if (eastCity->blueWarrier->isDied()) {
                Broadcast::output(BroadcastType::ArrowShot, "red ", redWarrier->getName(), ' ',
                                  redWarrier->getNumber(), " shot and killed blue ",
                                  eastCity->blueWarrier->getName(), ' ',
                                  eastCity->blueWarrier->getNumber());
            } else {
                Broadcast::output(BroadcastType::ArrowShot, "red ", redWarrier->getName(), ' ',
                                  redWarrier->getNumber(), " shot");
            }
        }
        if (blueWarrier && blueWarrier->checkArmament<Arrow>() && westCity &&
            westCity->redWarrier) {
            Armament* arrow = blueWarrier->getArmament<Arrow>();
            arrow->attack(westCity->redWarrier);
            blueWarrier->cleanArmaments();
            if (westCity->redWarrier->isDied()) {
                Broadcast::output(BroadcastType::ArrowShot, "blue ", blueWarrier->getName(), ' ',
                                  blueWarrier->getNumber(), " shot and killed red ",
                                  westCity->redWarrier->getName(), ' ',
                                  westCity->redWarrier->getNumber());
            } else {
                Broadcast::output(BroadcastType::ArrowShot, "blue ", blueWarrier->getName(), ' ',
                                  blueWarrier->getNumber(), " shot");
            }
        }
    }

    /**
     * @brief 点燃 Bomb。
     * 模拟战斗，若持 Bomb 方必死则全死。
     */
    void igniteBomb() {
        bool isRedFirst = (flag == Flag::Nothing ? number % 2 : flag == Flag::Red);
        // 检测 isDied 是因为可能被刚才的 Arrow 射死而不用 Bomb
        if (redWarrier && !redWarrier->isDied() && blueWarrier && !blueWarrier->isDied()) {
            if (redWarrier->checkArmament<Bomb>() &&
                simulateBattle(redWarrier, blueWarrier, isRedFirst)) {
                Broadcast::output(BroadcastType::BombUsed, "red ", redWarrier->getName(), ' ',
                                  redWarrier->getNumber(), " used a bomb and killed blue ",
                                  blueWarrier->getName(), ' ', blueWarrier->getNumber());
                redWarrier->owner->removeWarrier(redWarrier->getNumber());
                redWarrier = nullptr;
                blueWarrier->owner->removeWarrier(blueWarrier->getNumber());
                blueWarrier = nullptr;
            } else if (blueWarrier->checkArmament<Bomb>() &&
                       simulateBattle(blueWarrier, redWarrier, !isRedFirst)) {
                Broadcast::output(BroadcastType::BombUsed, "blue ", blueWarrier->getName(), ' ',
                                  blueWarrier->getNumber(), " used a bomb and killed red ",
                                  redWarrier->getName(), ' ', redWarrier->getNumber());
                blueWarrier->owner->removeWarrier(blueWarrier->getNumber());
                blueWarrier = nullptr;
                redWarrier->owner->removeWarrier(redWarrier->getNumber());
                redWarrier = nullptr;
            }
        }
    }

    /**
     * @brief 处理武士战斗相关事件。
     *
     */
    void battle() {
        hasBattled = false;
        shouldFlagRaised = false;
        // 仅当双方武士见面时执行
        if (!redWarrier || !blueWarrier) {
            // 若之前被射死
            if (redWarrier && redWarrier->isDied()) {
                redWarrier->owner->removeWarrier(redWarrier->getNumber());
                redWarrier = nullptr;
            }
            if (blueWarrier && blueWarrier->isDied()) {
                blueWarrier->owner->removeWarrier(blueWarrier->getNumber());
                blueWarrier = nullptr;
            }
            return;
        }
        hasBattled = true;
        // 配置好先后手
        bool isRedFirst = (flag == Flag::Nothing ? number % 2 : flag == Flag::Red);
        Warrier* firstHand = isRedFirst ? redWarrier : blueWarrier;
        Warrier* secondHand = isRedFirst ? blueWarrier : redWarrier;
        // 设置 Dragon 的欢呼属性
        if (typeid(*firstHand) == typeid(Dragon)) {
            dynamic_cast<Dragon*>(firstHand)->setYell(true);
        }
        if (typeid(*secondHand) == typeid(Dragon)) {
            dynamic_cast<Dragon*>(secondHand)->setYell(false);
        }
        // 若被 Arrow 射死
        if (checkResult(true))
            return;
        firstHand->attack(secondHand);
        cachedLog.push(Broadcast::combineString(
            firstHand->owner->getName(), ' ', firstHand->getName(), ' ', firstHand->getNumber(),
            " attacked ", secondHand->owner->getName(), ' ', secondHand->getName(), ' ',
            secondHand->getNumber(), " in city ", number, " with ", firstHand->getLife(),
            " elements and force ", firstHand->getForce()));
        if (checkResult())
            return;
        // 不是 Ninja 就反击
        if (typeid(*secondHand) != typeid(Ninja)) {
            secondHand->counterattack(firstHand);
            cachedLog.push(Broadcast::combineString(
                secondHand->owner->getName(), ' ', secondHand->getName(), ' ',
                secondHand->getNumber(), " fought back against ", firstHand->owner->getName(), ' ',
                firstHand->getName(), ' ', firstHand->getNumber(), " in city ", number));
        }
        if (checkResult())
            return;
        // 减少 Dragon 的士气
        if (typeid(*redWarrier) == typeid(Dragon)) {
            Dragon* dragon = dynamic_cast<Dragon*>(redWarrier);
            dragon->decreaseMorale();
            if (dragon->shouldYell())
                cachedLog.push(Broadcast::combineString("red dragon ", dragon->getNumber(),
                                                        " yelled in city ", number));
        }
        if (typeid(*blueWarrier) == typeid(Dragon)) {
            Dragon* dragon = dynamic_cast<Dragon*>(blueWarrier);
            dragon->decreaseMorale();
            if (dragon->shouldYell())
                cachedLog.push(Broadcast::combineString("blue dragon ", dragon->getNumber(),
                                                        " yelled in city ", number));
        }
        // 减少 Lion 的忠诚度
        if (typeid(*redWarrier) == typeid(Lion)) {
            dynamic_cast<Lion*>(redWarrier)->decreaseLoyalty();
        }
        if (typeid(*blueWarrier) == typeid(Lion)) {
            dynamic_cast<Lion*>(blueWarrier)->decreaseLoyalty();
        }
        lastWinner = Flag::Nothing;
    }

    /**
     * @brief 输出当前城市的武士信息。
     *
     * @param isRed 若报告红色武士，则为 @c true ；否则为 @c false
     */
    void printWarrierInfo(bool isRed) {
        if (isRed && redWarrier) {
            Broadcast::output(BroadcastType::WarrierReport, "red ", redWarrier->getName(), ' ',
                              redWarrier->getNumber(), " has ", redWarrier->getArmamentDetail());
        }
        if (!isRed && blueWarrier) {
            Broadcast::output(BroadcastType::WarrierReport, "blue ", blueWarrier->getName(), ' ',
                              blueWarrier->getNumber(), " has ", blueWarrier->getArmamentDetail());
        }
    }

    /**
     * @brief 司令部给武士奖励。
     *
     * @param isRed 是否是红色司令部。
     */
    void giveReward(bool isRed) {
        if (isRed && hasBattled && lastWinner == Flag::Red) {
            if (redWarrier->owner->getLife() >= 8) {
                redWarrier->addLife(8);
                redWarrier->owner->reduceLife(8);
            }
        }
        if (!isRed && hasBattled && lastWinner == Flag::Blue) {
            if (blueWarrier->owner->getLife() >= 8) {
                blueWarrier->addLife(8);
                blueWarrier->owner->reduceLife(8);
            }
        }
    }

    /**
     * @brief 武士为其司令部收集生命元并上传。
     *
     */
    void uploadElements() {
        // 双方都被 Bomb 炸死，则不收集生命元。
        if (!redWarrier && !blueWarrier) {
            return;
        }
        if (lastWinner == Flag::Red && elementNum > 0) {
            // 红方胜利，且有生命元
            redWarrier->owner->addLife(elementNum);
            cachedLog.push(Broadcast::combineString("red ", redWarrier->getName(), ' ',
                                                    redWarrier->getNumber(), " earned ", elementNum,
                                                    " elements for his headquarter"));
            elementNum = 0;
        } else if (lastWinner == Flag::Blue && elementNum > 0) {
            // 蓝方胜利，且有生命元
            blueWarrier->owner->addLife(elementNum);
            cachedLog.push(Broadcast::combineString("blue ", blueWarrier->getName(), ' ',
                                                    blueWarrier->getNumber(), " earned ",
                                                    elementNum, " elements for his headquarter"));
            elementNum = 0;
        }
        // 若旗帜发生更换，则输出更换事件
        if (shouldFlagRaised) {
            const char* color = "";
            switch (flag) {
                case Flag::Blue: color = "blue"; break;
                case Flag::Red: color = "red"; break;
            }
            cachedLog.push(Broadcast::combineString(color, " flag raised in city ", number));
        }
        //
        while (!cachedLog.empty()) {
            Broadcast::output(BroadcastType::Battle, cachedLog.front());
            cachedLog.pop();
        }
    }

    /**
     * @brief 输出当前城市的前进信息。
     *
     */
    void printMarchResult() {
        if (redWarrier) {
            if (!eastCity) {
                // 若抵达司令部
                Broadcast::output(BroadcastType::WarrierMarch, "red ", redWarrier->getName(), ' ',
                                  redWarrier->getNumber(), " reached blue headquarter with ",
                                  redWarrier->getLife(), " elements and force ",
                                  redWarrier->getForce());
                if (headquarter->enemyArrived(redWarrier)) {
                    Broadcast::output(BroadcastType::WarrierMarch, "blue headquarter was taken");
                    // 游戏即将结束，调整输出时间限制到现在
                    timeLimit = Broadcast::hour * 60 + int(BroadcastType::WarrierMarch);
                }
                redWarrier = nullptr;
            } else {
                Broadcast::output(BroadcastType::WarrierMarch, "red ", redWarrier->getName(), ' ',
                                  redWarrier->getNumber(), " marched to city ", number, " with ",
                                  redWarrier->getLife(), " elements and force ",
                                  redWarrier->getForce());
            }
        }
        if (blueWarrier) {
            if (!westCity) {
                // 若抵达司令部
                Broadcast::output(BroadcastType::WarrierMarch, "blue ", blueWarrier->getName(), ' ',
                                  blueWarrier->getNumber(), " reached red headquarter with ",
                                  blueWarrier->getLife(), " elements and force ",
                                  blueWarrier->getForce());
                if (headquarter->enemyArrived(blueWarrier)) {
                    Broadcast::output(BroadcastType::WarrierMarch, "red headquarter was taken");
                    // 游戏即将结束，调整输出时间限制到现在
                    timeLimit = Broadcast::hour * 60 + int(BroadcastType::WarrierMarch);
                }
                blueWarrier = nullptr;
            } else {
                Broadcast::output(BroadcastType::WarrierMarch, "blue ", blueWarrier->getName(), ' ',
                                  blueWarrier->getNumber(), " marched to city ", number, " with ",
                                  blueWarrier->getLife(), " elements and force ",
                                  blueWarrier->getForce());
            }
        }
    }
};

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
    Map(int n, Headquarter* red, Headquarter* blue) {
        // 一个城市没法玩
        if (n < 1)
            throw "Need more cities";
        westHead = new City(0);
        // 构建双向链表
        City* current = westHead;
        westHead->headquarter = red;
        current->westCity = nullptr;
        for (int i = 0; i <= n; i++) {
            current->eastCity = new City(i + 1);
            current->eastCity->westCity = current;
            current = current->eastCity;
        }
        current->eastCity = nullptr;
        eastHead = current;
        eastHead->headquarter = blue;
    }

    /**
     * @brief 向红方司令部城市添加一个武士。
     *
     * @param warrier 武士。
     */
    void addRed(Warrier* warrier) {
        westHead->redWarrier = warrier;
    }

    /**
     * @brief 向蓝方司令部城市添加一个武士。
     *
     * @param warrier 武士。
     */
    void addBlue(Warrier* warrier) {
        eastHead->blueWarrier = warrier;
    }

    void generateAndGetElements() {
        // 从西向东遍历
        City* current = westHead;
        while (current) {
            current->generateElements();
            current->getElements();
            current = current->eastCity;
        }
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
     * @brief 令所有拥有 Arrow 的武士攻击。
     *
     */
    void shootAllArrow() {
        // 从西向东遍历
        City* current = westHead;
        while (current) {
            current->shootArrow();
            current = current->eastCity;
        }
    }

    /**
     * @brief 令所有拥有 Bomb 的武士攻击。
     *
     */
    void igniteAllBomb() {
        // 从西向东遍历
        City* current = westHead;
        while (current) {
            current->igniteBomb();
            current = current->eastCity;
        }
    }

    /**
     * @brief 令所有城市开始战斗。
     *
     */
    void battleAll() {
        // 先保存 Lion 的初始生命值
        City* current = westHead;
        while (current) {
            current->saveLionStatus();
            current = current->eastCity;
        }
        // 从西向东开始战斗
        current = westHead;
        while (current) {
            current->battle();
            current = current->eastCity;
        }
    }

    /**
     * @brief 发放奖励，回收生命元。
     *
     */
    void doElementsOperations() {
        // 从东向西发放红方奖励
        City* current = eastHead;
        while (current) {
            current->giveReward(true);
            current = current->westCity;
        }
        // 从西向东发放蓝方奖励
        current = westHead;
        while (current) {
            current->giveReward(false);
            current = current->eastCity;
        }
        // 从西向东回收城市生命元
        current = westHead;
        while (current) {
            current->uploadElements();
            current = current->eastCity;
        }
    }

    /**
     * @brief 令所有城市输出武士报告。
     *
     */
    void printAllWarriersInfo() {
        // 先报告红方
        City* current = westHead;
        while (current) {
            current->printWarrierInfo(true);
            current = current->eastCity;
        }
        eastHead->headquarter->printArrivedEnemyInfo();
        // 再报告蓝方
        current = westHead;
        westHead->headquarter->printArrivedEnemyInfo();
        while (current) {
            current->printWarrierInfo(false);
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
        std::cin >> generalLife >> cityNumber >> WoW::arrowForce >> WoW::lionDecrease >>
            WoW::timeLimit;
        WoW::isOver = false;
        // 生成地图（包含城市）和两个司令部
        WoW::Headquarter red("red", generalLife, WoW::Headquarter::redGenerator);
        WoW::Headquarter blue("blue", generalLife, WoW::Headquarter::blueGenerator);
        WoW::Map map(cityNumber, &red, &blue);
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
            map.addRed(red.generateWarrier());
            map.addBlue(blue.generateWarrier());
            red.checkEscapedLion();
            blue.checkEscapedLion();
            map.marchAll();
            map.generateAndGetElements();
            map.shootAllArrow();
            map.igniteAllBomb();
            map.battleAll();
            map.doElementsOperations();
            red.printInfo();
            blue.printInfo();
            map.printAllWarriersInfo();
        }
    }
    return 0;
}