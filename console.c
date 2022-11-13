#include <stdio.h>
#include <stdlib.h>
#include "./console.h"

void menuList(TabKata *listGame, Queue *queueGame) {
    printf("ENTER COMMAND: ");
    GetCommand();
    system("cls");


    if (IsWordEq(toKata("START"), currentWord)) {
        printf("BNMO sudah dijalankan. Masukkan command HELP untuk bantuan\n\n");
    } else if (IsWordEq(toKata("LOAD"), AccessCommand(currentWord, 0))) {
        load(listGame, AccessCommand(currentWord, 1));
    } else if (IsWordEq(toKata("SAVE"), AccessCommand(currentWord, 0))) {
        save(*listGame, AccessCommand(currentWord, 1));
    } else if (IsWordEq(toKata("CREATE GAME"), currentWord)) {
        createGame(listGame);
    } else if (IsWordEq(toKata("LIST GAME"), currentWord)) {
        listGamePrint(*listGame);
    } else if (IsWordEq(toKata("DELETE GAME"), currentWord)) {
        deleteGame(listGame, *queueGame);
    } else if (IsWordEq(toKata("QUEUE GAME"), currentWord)) {
        queueGameList(*listGame, queueGame);
    } else if (IsWordEq(toKata("PLAY GAME"), currentWord)) {
        playGame(queueGame);
    } else if (IsWordEq(toKata("SKIPGAME"), AccessCommand(currentWord, 0))) {
        skipGame(queueGame, AccessCommand(currentWord, 1));
    } else if (IsWordEq(toKata("QUIT"), currentWord)) {
        quit(*listGame);
    } else if (IsWordEq(toKata("HELP"), currentWord)) {
        help();
    } else {
        printf("Command tidak dikenali, silahkan masukkan command yang valid.\nGunakan HELP untuk menunjukan list command.\n\n");
    }
}