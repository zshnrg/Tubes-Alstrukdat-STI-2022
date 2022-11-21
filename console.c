#include <stdio.h>
#include <stdlib.h>
#include "./console.h"

void menuList(TabKata *listGame, Queue *queueGame, List *historyGame) {
    printf("> ENTER COMMAND: ");
    GetCommand();
    system("cls");


    if (IsWordEq(toKata("START"), currentWord) || IsWordEq(toKata("LOAD"), currentWord)) {
        printf("BNMO sudah dijalankan. Masukkan command HELP untuk bantuan\n\n");
    } else if (IsWordEq(toKata("SAVE"), AccessCommand(currentWord, 0))) {
        save(*listGame, *historyGame, AccessCommand(currentWord, 1));
    } else if (IsWordEq(toKata("CREATE GAME"), currentWord)) {
        createGame(listGame);
    } else if (IsWordEq(toKata("LIST GAME"), currentWord)) {
        listGamePrint(*listGame);
    } else if (IsWordEq(toKata("DELETE GAME"), currentWord)) {
        deleteGame(listGame, *queueGame);
    } else if (IsWordEq(toKata("QUEUE GAME"), currentWord)) {
        queueGameList(*listGame, queueGame);
    } else if (IsWordEq(toKata("PLAY GAME"), currentWord)) {
        playGame(queueGame, historyGame);
    } else if (IsWordEq(toKata("SKIP GAME"), AccessCommand(currentWord, 0))) {
        skipGame(queueGame, historyGame, AccessCommand(currentWord, 2));
    } else if (IsWordEq(toKata("QUIT"), currentWord)) {
        quit(*listGame, *historyGame);
    } else if (IsWordEq(toKata("HELP"), currentWord)) {
        help();
    } else if (IsWordEq(toKata("HISTORY"), AccessCommand(currentWord, 0))) {
        history(*historyGame, AccessCommand(currentWord, 1));
    } else if (IsWordEq(toKata("RESET HISTORY"), currentWord)) {
        resetHistory(historyGame);
    } else {
        printf("Command tidak dikenali, silahkan masukkan command yang valid.\nGunakan HELP untuk menunjukan list command.\n\n");
    }
}