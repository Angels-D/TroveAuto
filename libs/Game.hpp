/* Memory
 *    -> Author: Angels-D & AI
 *
 * Game
 *    -> Author: Angels-D
 *
 * LastChange
 *    -> 2025/09/13 19:30
 *    -> 1.0.0
 *
 * Build
 *    -> g++ -shared -static -Os -Wall -o Game.dll -x c++ ./libs/Game.hpp
 */

// Game.h

#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "Memory.hpp"

template <typename T = Memory::Address>
class Object : public Memory
{
    friend class Game;

public:
    typedef std::pair<int32_t, std::string> Signature;

    Object(const DWORD &pid, const Offsets &offsets = {}, const Signature &signature = {});
    template<typename N>
    Object(const Object<N> &obj, const Offsets &offsets = {}, const Signature &signature = {});

    operator T() const;
    T operator=(const T &data);
    bool operator==(const Object &obj) const;

    Object &UpdatePid(const DWORD &pid);
    Object &UpdateBaseAddress(const Address &baseAddress);
    Object &UpdateOffsets();
    Object &UpdateAddress();
    Object &UpdateData();
    Object<std::string> &UpdateData(const uint32_t &maxLen);

    T data;
    Address address;
    Address baseAddress;

protected:
    Offsets offsets;
    Signature signature;
};

class Game : public Object<>
{
public:
    static std::string moduleName;
    class World : public Object
    {

    public:
        static Offsets offsets;
        static Signature signature;
        class NodeInfo : public Object
        {
        public:
            static Offsets offsets;
            struct Data
            {
                static Offsets baseAddressOffsets;
                static Offsets stepOffsets;
                static Offsets sizeOffsets;
                Object baseAddress;
                Object step;
                Object size;
                std::vector<Address> nodes;
            } data;

        public:
            NodeInfo(const Object &obj);
            NodeInfo &UpdateAddress();
            NodeInfo &UpdateData();
        };

        class Player : public Object
        {
        public:
            static Offsets offsets;
            struct Data
            {
                static Offsets nameOffsets;
                static Offsets xOffsets;
                static Offsets yOffsets;
                static Offsets zOffsets;
                Object<std::string> name;
                Object<float> x, y, z;
            } data;

        public:
            Player(const Object &obj, const int &index);
            Player &UpdateAddress();
            Player &UpdateData();
        };

        class Entity : public Object
        {
        public:
            static Offsets offsets;
            struct Data
            {
                static Offsets levelOffsets;
                static Offsets nameOffsets;
                static Offsets isDeathOffsets;
                static Offsets healthOffsets;
                static Offsets xOffsets;
                static Offsets yOffsets;
                static Offsets zOffsets;
                Object level;
                Object<std::string> name;
                Object isDeath;
                Object<double> health;
                Object<float> x, y, z;
            } data;

        public:
            Entity(const Object &obj);
            Entity &UpdateAddress();
            Entity &UpdateData();
            bool CheckData();
        };

        struct Data
        {
            static Offsets playerCountOffsets;
            NodeInfo nodeInfo;
            std::vector<Entity> entitys;
            std::vector<Player> players;
        } data;

    public:
        World(const Object &obj);
        World &UpdateAddress();
        World &UpdateData();
    };

    class Player : public Object
    {
    public:
        static Offsets offsets;
        static Signature signature;
        class Camera : public Object
        {
        public:
            static Offsets offsets;
            struct Data
            {
                static Offsets xPerOffsets;
                static Offsets yPerOffsets;
                static Offsets zPerOffsets;
                static Offsets vOffsets;
                static Offsets hOffsets;
                Object<float> xPer, yPer, zPer;
                Object<float> v, h;
            } data;

        public:
            Camera(const Object &obj);
            Camera &UpdateAddress();
            Camera &UpdateData();
        };
        class Coord : public Object
        {
        public:
            static Offsets offsets;
            struct Data
            {
                static Offsets xOffsets;
                static Offsets yOffsets;
                static Offsets zOffsets;
                static Offsets xVelOffsets;
                static Offsets yVelOffsets;
                static Offsets zVelOffsets;
                Object<float> x, y, z;
                Object<float> xVel, yVel, zVel;
            } data;

        public:
            Coord(const Object &obj);
            Coord &UpdateAddress();
            Coord &UpdateData();
        };
        class Fish : public Object
        {
        public:
            static Offsets offsets;
            static Signature signature;
            struct Data
            {
                static Offsets waterTakeOffsets;
                static Offsets lavaTakeOffsets;
                static Offsets chocoTakeOffsets;
                static Offsets plasmaTakeOffsets;
                static Offsets waterStatusOffsets;
                static Offsets lavaStatusOffsets;
                static Offsets chocoStatusOffsets;
                static Offsets plasmaStatusOffsets;
                Object waterTake, lavaTake, chocoTake, plasmaTake;
                Object waterStatus, lavaStatus, chocoStatus, plasmaStatus;
            } data;

        public:
            Fish(const Object &obj);
            Fish &UpdateAddress();
            Fish &UpdateData();
        };
        class Bag : public Object
        {
        public:
            static Offsets offsets;

            Bag(const Object &obj);
            Bag &UpdateAddress();
            Bag &UpdateData();
        };

    public:
        struct Data
        {
            static Offsets nameOffsets;
            static Offsets healthOffsets;
            static Offsets drawDistanceOffsets;
            static Offsets itemROffsets;
            static Offsets itemTOffsets;
            static Signature itemRSignature;
            static Signature itemTSignature;
            Object<std::string> name;
            Object<double> health;
            Object<float> drawDistance;
            Object itemR, itemT;
            Bag bag;
            Camera camera;
            Coord coord;
            Fish fish;
        } data;

    public:
        Player(const Object &obj);
        Player &UpdateAddress();
        Player &UpdateData();
    };

    struct Data
    {
        Player player;
        World world;
    } data;

public:
    Game(const DWORD &pid);
    Game &UpdateAddress(const DWORD &pid = 0);
};

// Game.cpp

std::string Game::moduleName = "Trove.exe";
Game::Signature Game::World::signature = {10, "55 8B EC 83 7D 08 04 75 10 A1 XX XX XX XX 85 C0 74 07 C6 80 59 01 00 00 01 5D C2 04 00"};
Memory::Offsets Game::World::offsets = {0x11FF5A4, 0x0};
Memory::Offsets Game::World::Data::playerCountOffsets = {0xFC, 0x2C};
Memory::Offsets Game::World::NodeInfo::offsets = {0x7C};
Memory::Offsets Game::World::NodeInfo::Data::baseAddressOffsets = {0x0};
Memory::Offsets Game::World::NodeInfo::Data::stepOffsets = {0x4};
Memory::Offsets Game::World::NodeInfo::Data::sizeOffsets = {0x8};
Memory::Offsets Game::World::Entity::offsets = {0x10, 0xC4, 0x4, 0x0};
Memory::Offsets Game::World::Entity::Data::levelOffsets = {0x58, 0xC4, 0x54, 0x120};
Memory::Offsets Game::World::Entity::Data::nameOffsets = {0x58, 0x64, 0x0};
Memory::Offsets Game::World::Entity::Data::isDeathOffsets = {0x58, 0x0};
Memory::Offsets Game::World::Entity::Data::healthOffsets = {0x58, 0xC4, 0x84, 0x80};
Memory::Offsets Game::World::Entity::Data::xOffsets = {0x58, 0xC4, 0x4, 0x80};
Memory::Offsets Game::World::Entity::Data::yOffsets = {0x58, 0xC4, 0x4, 0x84};
Memory::Offsets Game::World::Entity::Data::zOffsets = {0x58, 0xC4, 0x4, 0x88};
Memory::Offsets Game::World::Player::offsets = {0xFC, 0x0};
Memory::Offsets Game::World::Player::Data::nameOffsets = {0x1D0, 0x0};
Memory::Offsets Game::World::Player::Data::xOffsets = {0xC4, 0x4, 0x80};
Memory::Offsets Game::World::Player::Data::yOffsets = {0xC4, 0x4, 0x84};
Memory::Offsets Game::World::Player::Data::zOffsets = {0xC4, 0x4, 0x88};
Game::Signature Game::Player::signature = {0x14, "55 8B EC 83 E4 F8 83 EC 08 F3 0F 2A 45 10 56 8B F1 57 8B 3D"};
Memory::Offsets Game::Player::offsets = {0x11FF548, 0x0};
Game::Signature Game::Player::Data::itemRSignature = {-0x180, "FE FF FF FF 00 00 00 00 65 CF XX XX 0C 00 00 00 55 CF"};
Game::Signature Game::Player::Data::itemTSignature = {-0x180, "FE FF FF FF 00 00 00 00 65 CF XX XX 0C 00 00 00 55 CF"};
Memory::Offsets Game::Player::Data::nameOffsets = {0x0, 0x28, 0x1D0, 0x0};
Memory::Offsets Game::Player::Data::healthOffsets = {0x0, 0x28, 0x1A4, 0x80};
Memory::Offsets Game::Player::Data::drawDistanceOffsets = {0x14, 0x28};
Memory::Offsets Game::Player::Data::itemROffsets = {};
Memory::Offsets Game::Player::Data::itemTOffsets = {};
Memory::Offsets Game::Player::Camera::offsets = {0x4, 0x0};
Memory::Offsets Game::Player::Camera::Data::xPerOffsets = {0x24, 0x84, 0x0, 0x100};
Memory::Offsets Game::Player::Camera::Data::yPerOffsets = {0x24, 0x84, 0x0, 0x104};
Memory::Offsets Game::Player::Camera::Data::zPerOffsets = {0x24, 0x84, 0x0, 0x108};
Memory::Offsets Game::Player::Camera::Data::vOffsets = {0x2C};
Memory::Offsets Game::Player::Camera::Data::hOffsets = {0x28};
Memory::Offsets Game::Player::Coord::offsets = {0x0, 0x28, 0xC4, 0x4, 0x0};
Memory::Offsets Game::Player::Coord::Data::xOffsets = {0x80};
Memory::Offsets Game::Player::Coord::Data::yOffsets = {0x84};
Memory::Offsets Game::Player::Coord::Data::zOffsets = {0x88};
Memory::Offsets Game::Player::Coord::Data::xVelOffsets = {0xB0};
Memory::Offsets Game::Player::Coord::Data::yVelOffsets = {0xB4};
Memory::Offsets Game::Player::Coord::Data::zVelOffsets = {0xB8};
Game::Signature Game::Player::Fish::signature = {0x0, "10 14 XX XX 00 00 00 00 FF 00 00 00 00"};
Memory::Offsets Game::Player::Fish::offsets = {0x11FD39C, 0x68, 0x0};
Memory::Offsets Game::Player::Fish::Data::waterTakeOffsets = {0xE4, 0x3C4};
Memory::Offsets Game::Player::Fish::Data::lavaTakeOffsets = {0xE4, 0x898};
Memory::Offsets Game::Player::Fish::Data::chocoTakeOffsets = {0xE4, 0x62C};
Memory::Offsets Game::Player::Fish::Data::plasmaTakeOffsets = {0xE4, 0xB00};
Memory::Offsets Game::Player::Fish::Data::waterStatusOffsets = {0xF4, 0xBA0};
Memory::Offsets Game::Player::Fish::Data::lavaStatusOffsets = {0xF4, 0x938};
Memory::Offsets Game::Player::Fish::Data::chocoStatusOffsets = {0xF4, 0xE08};
Memory::Offsets Game::Player::Fish::Data::plasmaStatusOffsets = {0xF4, 0x6CC};
Memory::Offsets Game::Player::Bag::offsets = {};

Game *GameCreate(AobScan::DWORD dwPid, const char *gameTitle)
{
    return new Game(dwPid);
}

void GameDelete(Game *game)
{
    delete game;
}

void GameUpdate(Game *game, const DWORD &pid)
{
    game->UpdatePid(pid);
}

template <typename T>
Object<T>::Object(const DWORD &pid, const Memory::Offsets &offsets, const Signature &signature)
    : Memory(pid),
      offsets(offsets),
      signature(signature)
{
}

template <typename T>
template <typename N>
Object<T>::Object(const Object<N> &obj, const Memory::Offsets &offsets, const Signature &signature)
    : Memory(obj),
      address(obj.address),
      baseAddress(obj.baseAddress),
      offsets(offsets),
      signature(signature)
{
}

template <typename T>
Object<T>::operator T() const
{
    return data;
}

template <typename T>
T Object<T>::operator=(const T &data)
{
    WriteMemory(data, address);
    return Object::data = data;
}

template <typename T>
bool Object<T>::operator==(const Object &obj) const
{
    return obj.baseAddress == baseAddress;
}

template <typename T>
Object<T> &Object<T>::UpdatePid(const DWORD &pid)
{
    Update(pid);
    return *this;
}

template <typename T>
Object<T> &Object<T>::UpdateBaseAddress(const Address &baseAddress)
{
    Object::baseAddress = baseAddress;
    return *this;
}

template <typename T>
Object<T> &Object<T>::UpdateOffsets()
{
    std::vector<Address> results = AobScan(
        signature.second, true,
        std::thread::hardware_concurrency(),
        "", baseAddress);
    if (!results.empty())
    {
        if (offsets.empty())
            offsets.push_back(0);
        offsets[0] = {results[0] + signature.first - baseAddress};
    }
    return *this;
}

template <typename T>
Object<T> &Object<T>::UpdateAddress()
{
    address = GetAddress(baseAddress, offsets);
    return *this;
}

template <typename T>
Object<T> &Object<T>::UpdateData()
{
    data = Read<T>(address);
    return *this;
}

template <typename T>
Object<std::string> &Object<T>::UpdateData(const uint32_t &maxLen)
{
    data = Read(address, maxLen);
    return *this;
}

Game::World::NodeInfo::NodeInfo(const Object &obj)
    : Object(obj, offsets),
      data({{*this, Data::baseAddressOffsets},
            {*this, Data::stepOffsets},
            {*this, Data::sizeOffsets}})
{
}

Game::World::NodeInfo &Game::World::NodeInfo::UpdateAddress()
{
    Object::UpdateAddress();
    data.baseAddress.UpdateBaseAddress(address);
    data.step.UpdateBaseAddress(address);
    data.size.UpdateBaseAddress(address);
    return *this;
}

Game::World::NodeInfo &Game::World::NodeInfo::UpdateData()
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

Game::World::Entity::Entity(const Object &obj)
    : Object(obj, offsets),
      data({{*this, Data::levelOffsets},
            {*this, Data::nameOffsets},
            {*this, Data::isDeathOffsets},
            {*this, Data::healthOffsets},
            {*this, Data::xOffsets},
            {*this, Data::yOffsets},
            {*this, Data::zOffsets}})
{
}

Game::World::Entity &Game::World::Entity::UpdateAddress()
{
    Object::UpdateAddress();
    data.level.UpdateBaseAddress(address);
    data.name.UpdateBaseAddress(address);
    data.isDeath.UpdateBaseAddress(address);
    data.health.UpdateBaseAddress(address);
    data.x.UpdateBaseAddress(address);
    data.y.UpdateBaseAddress(address);
    data.z.UpdateBaseAddress(address);
    return *this;
}

Game::World::Entity &Game::World::Entity::UpdateData()
{
    data.level.UpdateAddress();
    data.name.UpdateAddress();
    data.isDeath.UpdateAddress();
    data.health.UpdateAddress();
    data.x.UpdateAddress();
    data.y.UpdateAddress();
    data.z.UpdateAddress();
    return *this;
}

bool Game::World::Entity::CheckData()
{
    Object::UpdateAddress();
    if (data.name.UpdateBaseAddress(address).UpdateAddress().address == 0)
        return false;
    return data.name.UpdateData(8).data.length() > 0;
}

Game::World::Player::Player(const Object &obj, const int &index)
    : Object(obj, offsets),
      data({{*this, Data::nameOffsets},
            {*this, Data::xOffsets},
            {*this, Data::yOffsets},
            {*this, Data::zOffsets}})
{
    Object::offsets.emplace_back(index * 0x4);
    Object::offsets.emplace_back(0x0);
}

Game::World::Player &Game::World::Player::UpdateAddress()
{
    Object::UpdateAddress();
    data.name.UpdateBaseAddress(address);
    data.x.UpdateBaseAddress(address);
    data.y.UpdateBaseAddress(address);
    data.z.UpdateBaseAddress(address);
    return *this;
}
Game::World::Player &Game::World::Player::UpdateData()
{
    data.name.UpdateAddress();
    data.x.UpdateAddress();
    data.y.UpdateAddress();
    data.z.UpdateAddress();
    return *this;
}

Game::World::World(const Object &obj)
    : Object(obj, offsets, signature), data({*this})
{
}

Game::World &Game::World::UpdateAddress()
{
    Object::UpdateAddress();
    data.nodeInfo.UpdateBaseAddress(address);
    return *this;
}

Game::World &Game::World::UpdateData()
{
    const auto &nodes = data.nodeInfo.UpdateAddress().UpdateData().data.nodes;
    data.entitys.clear();
    data.entitys.reserve(nodes.size());
    for (const Address &nodeAddress : nodes)
    {
        Entity entity(*this);
        entity.UpdateBaseAddress(nodeAddress);
        if (entity.CheckData())
            data.entitys.emplace_back(*this).UpdateBaseAddress(nodeAddress);
    }
    Object playerCount(*this, Data::playerCountOffsets);
    playerCount.UpdateBaseAddress(address).UpdateAddress().UpdateData();
    data.players.clear();
    data.players.reserve(playerCount.data);
    for (uint32_t i = 0; i < playerCount.data; i++)
        data.players.emplace_back(*this, i).UpdateBaseAddress(address);
    return *this;
}

Game::Player::Camera::Camera(const Object &obj)
    : Object(obj, offsets),
      data({{*this, Data::xPerOffsets},
            {*this, Data::yPerOffsets},
            {*this, Data::zPerOffsets},
            {*this, Data::vOffsets},
            {*this, Data::hOffsets}})
{
}

Game::Player::Camera &Game::Player::Camera::UpdateAddress()
{
    Object::UpdateAddress();
    data.xPer.UpdateBaseAddress(address);
    data.yPer.UpdateBaseAddress(address);
    data.zPer.UpdateBaseAddress(address);
    data.v.UpdateBaseAddress(address);
    data.h.UpdateBaseAddress(address);
    return *this;
}

Game::Player::Camera &Game::Player::Camera::UpdateData()
{
    data.xPer.UpdateAddress();
    data.yPer.UpdateAddress();
    data.zPer.UpdateAddress();
    data.v.UpdateAddress();
    data.h.UpdateAddress();
    return *this;
}

Game::Player::Coord::Coord(const Object &obj)
    : Object(obj, offsets),
      data({{*this, Data::xOffsets},
            {*this, Data::yOffsets},
            {*this, Data::zOffsets},
            {*this, Data::xVelOffsets},
            {*this, Data::yVelOffsets},
            {*this, Data::zVelOffsets}})
{
}

Game::Player::Coord &Game::Player::Coord::UpdateAddress()
{
    Object::UpdateAddress();
    data.x.UpdateBaseAddress(address);
    data.y.UpdateBaseAddress(address);
    data.z.UpdateBaseAddress(address);
    data.xVel.UpdateBaseAddress(address);
    data.yVel.UpdateBaseAddress(address);
    data.zVel.UpdateBaseAddress(address);
    return *this;
}

Game::Player::Coord &Game::Player::Coord::UpdateData()
{
    data.x.UpdateAddress();
    data.y.UpdateAddress();
    data.z.UpdateAddress();
    data.xVel.UpdateAddress();
    data.yVel.UpdateAddress();
    data.zVel.UpdateAddress();
    return *this;
}

Game::Player::Fish::Fish(const Object &obj)
    : Object(obj, offsets, signature),
      data({{*this, Data::waterTakeOffsets},
            {*this, Data::lavaTakeOffsets},
            {*this, Data::chocoTakeOffsets},
            {*this, Data::plasmaTakeOffsets},
            {*this, Data::waterStatusOffsets},
            {*this, Data::lavaStatusOffsets},
            {*this, Data::chocoStatusOffsets},
            {*this, Data::plasmaStatusOffsets}})
{
}

Game::Player::Fish &Game::Player::Fish::UpdateAddress()
{
    Object::UpdateAddress();
    data.waterTake.UpdateBaseAddress(address);
    data.lavaTake.UpdateBaseAddress(address);
    data.chocoTake.UpdateBaseAddress(address);
    data.plasmaTake.UpdateBaseAddress(address);
    data.waterStatus.UpdateBaseAddress(address);
    data.lavaStatus.UpdateBaseAddress(address);
    data.chocoStatus.UpdateBaseAddress(address);
    data.plasmaStatus.UpdateBaseAddress(address);
    return *this;
}

Game::Player::Fish &Game::Player::Fish::UpdateData()
{
    data.waterTake.UpdateAddress();
    data.lavaTake.UpdateAddress();
    data.chocoTake.UpdateAddress();
    data.plasmaTake.UpdateAddress();
    data.waterStatus.UpdateAddress();
    data.lavaStatus.UpdateAddress();
    data.chocoStatus.UpdateAddress();
    data.plasmaStatus.UpdateAddress();
    return *this;
}

Game::Player::Bag::Bag(const Object &obj)
    : Object(obj, offsets)
{
}

Game::Player::Bag &Game::Player::Bag::UpdateAddress()
{
    return *this;
}

Game::Player::Bag &Game::Player::Bag::UpdateData()
{
    return *this;
}

Game::Player::Player(const Object &obj)
    : Object(obj, offsets, signature),
      data({{*this, Data::nameOffsets},
            {*this, Data::healthOffsets},
            {*this, Data::drawDistanceOffsets},
            {*this, Data::itemROffsets, Data::itemRSignature},
            {*this, Data::itemTOffsets, Data::itemTSignature},
            {*this},
            {*this},
            {*this},
            {*this}})
{
}

Game::Player &Game::Player::UpdateAddress()
{
    Object::UpdateAddress();
    data.name.UpdateBaseAddress(address);
    data.health.UpdateBaseAddress(address);
    data.drawDistance.UpdateBaseAddress(baseAddress);
    data.drawDistance.offsets.front() += offsets.front();
    data.itemR.UpdateBaseAddress(address);
    data.itemT.UpdateBaseAddress(address);
    data.bag.UpdateBaseAddress(address);
    data.camera.UpdateBaseAddress(address);
    data.coord.UpdateBaseAddress(address);
    data.fish.UpdateBaseAddress(baseAddress);
    return *this;
}
Game::Player &Game::Player::UpdateData()
{
    data.name.UpdateAddress();
    data.health.UpdateAddress();
    data.drawDistance.UpdateAddress();
    data.itemR.UpdateAddress();
    data.itemT.UpdateAddress();
    data.bag.UpdateAddress();
    data.camera.UpdateAddress();
    data.coord.UpdateAddress();
    data.fish.UpdateAddress();
    return *this;
}

Game::Game(const DWORD &pid)
    : Object(pid), data({{*this}, {*this}})
{
    baseAddress = GetModuleAddress(moduleName);
}
Game &Game::UpdateAddress(const DWORD &pid)
{
    if (pid && Game::pid != pid)
        UpdatePid(pid);
    UpdateBaseAddress(GetModuleAddress(moduleName));
    data.world.UpdateBaseAddress(baseAddress);
    data.player.UpdateBaseAddress(baseAddress);
    return *this;
}

#endif
