//
// Created by leogm99 on 20/5/21.
//

#ifndef TP3_CLIENT_COMMAND_H
#define TP3_CLIENT_COMMAND_H
#include <map>
#include <vector>

static const uint8_t crear = 0x6e;
static const uint8_t listar = 0x6c;
static const uint8_t unirse = 0x6a;
static const uint8_t jugar = 0x70;

class Command {
private:
    static std::map<std::string, uint8_t>
    createMap(){
        std::map<std::string, uint8_t> commands;
        commands["crear"] = crear;
        commands["listar"] = listar;
        commands["unirse"] = unirse;
        commands["jugar"] = jugar;
        return commands;
    }

    // command value serialization
    std::map<std::string, uint8_t> validCommands;
    std::vector<uint8_t> actualCommand;

    // methods that serialize the interpreted command
    void dispatch(uint8_t command, std::stringstream& ss);
    void create(std::stringstream& ss);
    void list();
    void join(std::stringstream& ss);
    void play(std::stringstream& ss);

public:
    Command();
    Command(const Command& other) = delete;
    Command& operator=(const Command& other) = delete;

    Command(Command&& other) noexcept;
    Command& operator=(Command&& other) noexcept;

    void serializeCommand();
    std::vector<uint8_t> getCommand();
    ~Command();
};



#endif //TP3_CLIENT_COMMAND_H
