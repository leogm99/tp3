#ifndef TP3_CLIENT_COMMAND_H
#define TP3_CLIENT_COMMAND_H
#include "../common_src/Macros.h"
#include <map>
#include <vector>
#include <string>

class Command {
private:
    static std::map<std::string, uint8_t>
    createMap(){
        std::map<std::string, uint8_t> commands;
        commands["crear"] = CREAR;
        commands["listar"] = LISTAR;
        commands["unirse"] = UNIRSE;
        commands["jugar"] = JUGAR;
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
