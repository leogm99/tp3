//
// Created by leogm99 on 12/6/21.
//

#ifndef TP3_MACROS_H
#define TP3_MACROS_H

#define BOARD "    1 . 2 . 3 .\n"\
"  +---+---+---+\n"\
"1 |   |   |   |\n"\
"  +---+---+---+\n"\
"2 |   |   |   |\n"\
"  +---+---+---+\n"\
"3 |   |   |   |\n"\
"  +---+---+---+\n"

#define MSGWON "Felicitaciones! Ganaste!\n"
#define MSGLOST "Has perdido. Segui intentando!\n"
#define MSGTIE "La partida ha terminado en empate\n"

#define CREAR 0x6e
#define LISTAR 0x6c
#define UNIRSE 0x6a
#define JUGAR 0x70

#define ERR_LEN 256
#define GAME_EXISTS "Game already exists\n"
#define GAME_NOT_EXIST "Game does not exist\n"
#define GAME_FULL "Game is already full\n"
#define GAME_INVAL "Game is invalid\n"
#define MOVE_INVAL "Move at column %d and row %d is not valid\n"

#define ADDR_INFO "Cannot get address information\n"
#define BIND_ERR "Cannot bind and listen on port %s\n"
#define LISTENER_CLOSED "Listener was closed\n"
#define CONNECT_ERR "Cannot connect on port %s\n"

#define HAS_GAME "You are already queued for %s\n"
#define INVAL_COMMAND "Command is not valid\n"


#endif
