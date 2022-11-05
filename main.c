#include <stdlib.h>
#include "console.h"

int main() {
    TabKata listGame;
    Queue queueGame;

    MakeEmpty(&listGame);
    queueGame = CreateQueue(50);
    system("cls");
    
    do {
        printf("ENTER COMMAND: ");
        GetCommand();
        system("cls");

        if (!IsWordEq(toKata("START"), currentWord)) printf("Command tidak valid. Mesin BNMO belum dijalankan! Gunakan command START untuk memulai\n\n");
    } while (!IsWordEq(toKata("START"), currentWord));

    start(&listGame);
    if (stateBNMO) {
        while (stateBNMO) {
            menuList(&listGame, &queueGame);
        }
    } else {
        printf("BNMO gagal dijalankan.\n");
    }
    system("cls");
}