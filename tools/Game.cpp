/* 地址寻址
 * 玩家: (+Size Value) 55 8B EC 83 E4 F8 83 EC 08 F3 0F 2A 45 10 56 8B F1 57 8B 3D
 * 世界: (+10   Value) 55 8B EC 83 7D 08 04 75 10 A1 XX XX XX XX 85 C0 74 07 C6 80 59 01 00 00 01 5D C2 04 00
 * 设置: (+Size Value) 89 45 F4 8B 11 FF 52 0C 8B 0D XX XX XX XX 8B D8 6A 03 68 XX XX XX XX 8B 11 FF 52 0C 8B 0D
 * 聊天: (+2    Value) 8B 0D XX XX XX XX 6A 00 6A 01 C6 41 20 00 E8 XX XX XX XX 6A 08 8D 8D 60 FF FF FF C7 85 60 FF FF FF 00 00 00 00 C7 85 64 FF FF FF 00 00 00 00 C7 85 68 FF FF FF 00 00 00 00 C6 45 F0 01
 * 血量: (+4    Value) 40 3F 00 00 00 00 90 E5
 * 隐藏特效: (+3 Address) F3 0F 11 44 24 24 F3 0F 58 84 24 80 00 00 00 50 F3 0F 11 43 24 E8 XX XX XX XX 8D 44 24 34 50
 * 自动攻击: (+1 Address) DF F1 DD D8 72 1F
 * 打破障碍: (+3 Address) 80 7F XX 00 0F 84 XX XX XX XX 8B 4B 08 E8 XX XX XX XX FF 75 0C 8B 4D 10 8B F0 FF 75 08 8B 45 14 83 EC 0C 8B 3E 8B D4 6A 01 89 0A 8B CE 89 42 04 8B 45 18
 * 视角遮挡: (+0 Address) 0F 29 01 C7 41 34 00 00 00 00 0F
 * 保持骑乘: (+0 Address) 74 XX 8B 07 8B CF 6A 00 6A 00 FF 50
 * 钓鱼地址: (+0 Address) 10 14 XX XX 00 00 00 00 FF 00 00 00 00
 * 视角固定: (+0 Address) 74 05 8B 01 FF 50 0C 8B E5
 * 地图放大: (+0 Address) 77 XX B8 XX XX XX XX F3 0F 10 08 F3 0F 11 89 XX XX XX XX 8B 89
 * 快速挖矿: (+1 Address) DF F1 DD D8 72 61
 * 快速挖矿（晶洞）: (+1 Address) DF F1 DD D8 72 35 8D
 * 账号地址: (-9 Address) FF 70 1C FF 70 18 8D 45 B0
 * 视野放大: (+3 Address) F3 0F 11 5F 2C
 * 穿墙: (+0 Address) 74 31 FF 73 14 8B 47 04 2B 07
 * 绕道: (+1 Address) DC 67 68 C6
 * 技能栏: 5X CF XX XX 55 CF XX XX 5X CF XX XX 55 CF XX XX FE FF FF FF 00 00 00 00 65 CF XX XX 0X 00 00 00 55 CF XX XX XX XX XX XX 55 CF XX XX 55 CF XX XX
 *            (-170H Value) 数量
 *            (+0 Value) 55释放,5D按下
 *            (+8 Value) 55未装备,5D装备
 *            (+28 Value) 00 右键 | 02 1技能 | 04 2技能 | 06 SHIFT | 08 未知 | 0A 药瓶 | 0C R物品 | 0E T物品
 */

#include "Memory.cpp"

template <typename T = Memory::Address>
class Object : public Memory
{
    friend class Game;

public:
    Object(const DWORD &pid, const Offsets &offsets = {}) : Memory(pid), offsets(offsets) {}
    Object(const Object<> &obj, const Offsets &offsets = {})
        : Memory(obj.pid, false), offsets(offsets), baseAddress(obj.baseAddress) {}

    operator T() const
    {
        return data;
    }
    T operator=(const T &data)
    {
        WriteMemory(data);
        return Object::data = data;
    }
    Object &UpdatePid(const DWORD &pid)
    {
        Update(pid);
        return *this;
    }
    Object &UpdateBaseAddress(const Address &baseAddress)
    {
        Object::baseAddress = baseAddress;
        return *this;
    }
    Object &UpdateAddress()
    {
        address = GetAddress(baseAddress, offsets);
        return *this;
    }
    Object &UpdateData()
    {
        data = Read<T>(address);
        return *this;
    }
    Object &UpdateData(const uint32_t &maxLen)
    {
        data = Read(address, maxLen);
        return *this;
    }

public:
    T data;
    Address address;
    Address baseAddress;

protected:
    const Offsets offsets;
};

class Game : public Object<Memory::Address>
{
public:
    class World : public Object<Address>
    {
        static Offsets offsets;

    public:
        class NodeInfo : public Object<Address>
        {
            static Offsets offsets;

        public:
            struct Data
            {
                static Offsets baseAddressOffsets;
                static Offsets stepOffsets;
                static Offsets sizeOffsets;
                Object<Address> baseAddress;
                Object<Address> step;
                Object<Address> size;
                std::vector<Address> nodes;
            } data;

        public:
            NodeInfo(const Object &obj)
                : Object(obj, offsets), data({{*this, Data::baseAddressOffsets},
                                              {*this, Data::stepOffsets},
                                              {*this, Data::sizeOffsets}}) {}
            NodeInfo &UpdateAddress()
            {
                Object::UpdateAddress();
                data.baseAddress.UpdateBaseAddress(address);
                data.step.UpdateBaseAddress(address);
                data.size.UpdateBaseAddress(address);
                return *this;
            }
            NodeInfo &UpdateData()
            {
                data.baseAddress.UpdateAddress().UpdateData();
                data.step.UpdateAddress().UpdateData();
                data.size.UpdateAddress().UpdateData();
                data.nodes.clear();
                for (uint32_t i = 0; i < data.size.data; i++)
                {
                    Address address = data.baseAddress.data + i * data.step.data;
                    Address addressNext;
                    do
                    {
                        addressNext = ReadMemory<Address>(address);
                        if (addressNext != 1)
                            data.nodes.emplace_back(address);
                        address = addressNext & 0xFFFFFFFE;
                    } while ((addressNext & 0xFFFFFFFE) != 0);
                }
                return *this;
            }
        };

        class Player : public Object<Address>
        {
        public:
            const Address count()
            {
                return 0;
            }
        };

        class Entity : public Object<Address>
        {
            static Address key;
            static Offsets offsets;

        public:
            struct Data
            {
                static Offsets levelOffsets;
                static Offsets nameOffsets;
                static Offsets isDeathOffsets;
                static Offsets xOffsets;
                static Offsets yOffsets;
                static Offsets zOffsets;
                Object<Address> level;
                Object<std::string> name;
                Object<bool> isDeath;
                Object<float> x, y, z;
            } data;

        public:
            Entity(const Object &obj)
                : Object(obj, offsets), data({{*this, Data::levelOffsets},
                                              {*this, Data::nameOffsets},
                                              {*this, Data::isDeathOffsets},
                                              {*this, Data::xOffsets},
                                              {*this, Data::yOffsets},
                                              {*this, Data::zOffsets}}) {}
            Entity(const Entity &obj) : Object(obj, obj.offsets), data(obj.data) {}
            Entity &UpdateAddress()
            {
                Object::UpdateAddress();
                address ^= key;
                data.level.UpdateBaseAddress(address);
                data.name.UpdateBaseAddress(address);
                data.isDeath.UpdateBaseAddress(address);
                data.x.UpdateBaseAddress(address);
                data.y.UpdateBaseAddress(address);
                data.z.UpdateBaseAddress(address);
                return *this;
            }
            Entity &UpdateData()
            {
                data.level.UpdateAddress();
                data.name.UpdateAddress();
                data.isDeath.UpdateAddress();
                data.x.UpdateAddress();
                data.y.UpdateAddress();
                data.z.UpdateAddress();
                return *this;
            }
            bool CheckData()
            {
                Object::UpdateAddress();
                if (data.name.UpdateBaseAddress(address ^ key).UpdateAddress().address == 0)
                    return false;
                return data.name.UpdateData(10).data.length() > 0;
            }
        };

        struct Data
        {
            NodeInfo nodeInfo;
            std::vector<Entity> entitys;
        } data;

    public:
        World(const Object &obj) : Object(obj, offsets), data({*this}) {}
        World &UpdateAddress()
        {
            Object::UpdateAddress();
            data.nodeInfo.UpdateBaseAddress(address);
            return *this;
        }
        World &UpdateData()
        {
            data.entitys.clear();
            Memory mem(pid);
            for (const Address &nodeAddress : data.nodeInfo.UpdateAddress().UpdateData().data.nodes)
            {
                Entity entity(*this);
                entity.UpdateBaseAddress(nodeAddress);
                if (entity.CheckData())
                    data.entitys.emplace_back(entity);
            }
            return *this;
        }
        void show()
        {
            for (uint32_t i = 0; i < data.entitys.size(); i++)
            {
                Entity::Data data = World::data.entitys[i].UpdateAddress().UpdateData().data;
                printf("[%02d] X: %+010.04f Y: %+010.04f Z: %+010.04f Level: 0x%08X isDeath: 0x%08X Name: %s\n",
                       i + 1, data.x.UpdateAddress().UpdateData().data,
                       data.y.UpdateAddress().UpdateData().data,
                       data.z.UpdateAddress().UpdateData().data,
                       data.level.UpdateAddress().UpdateData().data,
                       data.isDeath.UpdateAddress().UpdateData().data,
                       data.name.UpdateAddress().UpdateData(256).data.c_str());
            }
        }
    };

    struct Data
    {
        World world;
    } data;

public:
    Game(const DWORD &pid, const std::string moduleName)
        : Object(pid), moduleName(moduleName), data({*this})
    {
        baseAddress = GetModuleAddress(moduleName);
    }
    Game &UpdateAddress(const DWORD &pid = 0, const std::string moduleName = "")
    {
        if (pid && Game::pid != pid)
            UpdatePid(pid);
        if (moduleName.length() && Game::moduleName != moduleName)
            UpdateBaseAddress(GetModuleAddress(moduleName));
        data.world.UpdateBaseAddress(baseAddress);
        return *this;
    }

private:
    std::string moduleName;
};

std::string gameTitle = "Trove.exe";
Memory::Offsets Game::World::offsets = {0x108BDE0};
Memory::Offsets Game::World::NodeInfo::offsets = {0x0, 0x7C};
Memory::Offsets Game::World::NodeInfo::Data::baseAddressOffsets = {0x0};
Memory::Offsets Game::World::NodeInfo::Data::stepOffsets = {0x4};
Memory::Offsets Game::World::NodeInfo::Data::sizeOffsets = {0x8};
Memory::Address Game::World::Entity::key = 0x242733E7;
Memory::Offsets Game::World::Entity::offsets = {0x10, 0xC4, 0x0, 0x0};
Memory::Offsets Game::World::Entity::Data::levelOffsets = {0x58, 0xC4, 0x54, 0x120};
Memory::Offsets Game::World::Entity::Data::nameOffsets = {0x58, 0x64, 0x0};
Memory::Offsets Game::World::Entity::Data::isDeathOffsets = {0x58, 0x0};
Memory::Offsets Game::World::Entity::Data::xOffsets = {0x58, 0xC4, 0x4, 0x80};
Memory::Offsets Game::World::Entity::Data::yOffsets = {0x58, 0xC4, 0x4, 0x84};
Memory::Offsets Game::World::Entity::Data::zOffsets = {0x58, 0xC4, 0x4, 0x88};

int main(int argc, char *argv[])
{
    uint32_t pid;
    if (argc < 2)
        for (auto process : Memory::GetProcessPid(gameTitle))
        {
            pid = process;
            break;
        }
    else
        pid = std::stoi(argv[1]);

    Game game(pid, gameTitle);

    printf("ProcessName: %s\n", game.GetProcessName().c_str());

    game.UpdateAddress().data.world.UpdateAddress().UpdateData().show();

    for (auto address : game.AobScan("DF F1 DD D8 72 1F", true))
        printf("0x%08X ", address);
    printf("\n");

    game.FindAddress([game](const Memory::Address &start, const Memory::Address &end)
                     {
        bool find = game.ReadMemory(start,{}) == game.data.world.data.entitys[0].data.name.data;
        if(find) {printf("0x%X ", start);
            return std::pair(std::vector<DWORD>({start}),start);
        }
        else return std::pair(std::vector<DWORD>(),start); }, false, 32, "", game.baseAddress);
    return 0;
}