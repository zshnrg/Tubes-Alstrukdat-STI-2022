#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "snakeOnMeteor.h"

int playSnakeOnMeteor() {
    int mapSize = 5;

    system("cls");
    do {    
        currentWord = toKata("START");
        do {
            printf("Besar peta: %d x %d\n", mapSize, mapSize);
            printf("\nSelamat datang di Snake on Meteor! Gunakan perintah di bawah ini.\n");
            printf("| CHANGE MAP\t Mengganti luas peta permainan\n");
            printf("| START\t\t Memulai permainan\n\n");
            if (!(IsWordEq(currentWord, toKata("CHANGE MAP")) || IsWordEq(currentWord, toKata("START")))) printf("Perintah tidak valid!\n");
            printf("> ");
            GetCommand();
            system("cls");
        } while (!(IsWordEq(currentWord, toKata("CHANGE MAP")) || IsWordEq(currentWord, toKata("START"))));

        if (IsWordEq(currentWord, toKata("CHANGE MAP"))) {
            int n = 5;
            do {
                system("cls");
                printf("Lebar peta: %d x %d\n\n", mapSize, mapSize);
                if (n < 5) printf("Lebar peta tidak valid! Minimal lebar peta adalah 5\n");
                printf("Masukkan lebar peta baru: ");
                GetCommand();
                n = 0;
                for (int i = 0; i < currentWord.Length; i ++) {
                    n *= 10;
                    n += currentWord.TabWord[i] - '0';
                }
            } while (n < 5);
            mapSize = n;
        }
        system("cls");
    } while (!IsWordEq(currentWord, toKata("START")));
    system("cls");

    printf("Membuat permainan, mohon tunggu ...");

    // Game
    int score = 0, turn = 1;
    boolean isEndGame = false, isHit = false;

    List snake, snakeCopy;
    generateSnake(&snake, mapSize);

    Point Food, Meteor, Crater;
    Point Obs[100];

    generateObstacle(Obs, snake, mapSize);
    setPointNull(&Meteor);
    setPointNull(&Crater);
    Food = generateFood(snake, Obs, Meteor, Crater, mapSize);

    system("cls");
    printGuideSoM();


    currentWord = toKata("W");
    do {
        if (isPointEqual(Info(First(snake)), Food)) {
            Food = generateFood(snake, Obs, Meteor, Crater, mapSize);
            First(snakeCopy) = First(snake);
            growSnake(&snake, mapSize);
        }
        do {
            do {
                system("cls");
                printf("Peta Permainan\n");
                printMap(snake, Obs, Food, Meteor, Crater, mapSize);
                if (isHit) printf("Anda terkena meteor! \n");
                else if (turn > 2) printf("Anda beruntung tidak terkena meteor! Silahkan lanjutkan permainan\n");
                
                printf("\nTURN %d\n", turn);
                if (isCmdValid(currentWord)) {
                    if (!isMoveValid(currentWord, snake, Meteor, false, mapSize)) printf("Silahkan masukkan command lainnya\n");
                }
                if (!isCmdValid(currentWord)) printf("Command tidak valid! Silahkan input command menggunakan huruf W/A/S/D\n");
                printf("Silahkan masukkan command anda: ");
                GetCommand();
            } while (!isCmdValid(currentWord));
        } while (!isMoveValid(currentWord, snake, Meteor, true, mapSize));

        moveSnake(&snake, currentWord, mapSize);
        if (!IsEmptyList(snake)) First(snakeCopy) = First(snake);

        if (turn > 1) {
            Crater = Meteor;
        }
        Meteor = generateMeteor(Obs, Food, mapSize);
        
        turn++;

        isHit = isMeteorHit(&snake, Meteor);
        isEndGame = isCollide(snake, Obs, mapSize) || IsEmptyList(snake);
    } while (!isEndGame);

    score = NumberElmt(snakeCopy) * 2;
    if (IsEmptyList(snake)) score -= 2;
    system("cls");
    
    printf("Peta Permainan\n");
    printMap(snakeCopy, Obs, Food, Meteor, Crater, mapSize);
    if (isHit) printf("Kepala snake terkena meteor!\n\n");
    else printf("Snake menabrak!\n\n");
    sleep(2);

    system("cls");
    printf("Game berakhir. Skor: %d\n\n", score);

    return score;
}

void generateSnake(List *Snake, int mapSize) {
    CreateEmptyList(Snake);
    for (int i = (int) (mapSize / 2); i >= (int) (mapSize / 2) - 2; i--) {
        InsVLast(Snake, createPoint(i, (int) (mapSize / 2)));
    }
}

Point generateFood(List Snake, Point *Obs, Point Meteor, Point Crater, int mapSize) {
    Point F;
    address P;
    boolean unique;
    srand(time(NULL));
    do {
        unique = true;
        srand(rand());
        F = createPoint(rand() % mapSize, rand() % mapSize);
        P = Search(Snake, F);
        for (int i = 0; i < (int) (mapSize * mapSize / 5 - 3); i++) {
            if (isPointEqual(Obs[i], F)) unique = false;
        }
    } while (P != NULL || !unique || isPointEqual(Meteor, F) || isPointEqual(Crater, F));
    return F;
}

Point generateMeteor(Point *Obs, Point Food, int mapSize) {
    Point M;
    boolean unique;
    srand(time(NULL));
    do {
        unique = true;
        srand(rand());
        M = createPoint(rand() % mapSize, rand() % mapSize);
        for (int i = 0; i < (int) (mapSize * mapSize / 5 - 3); i++) {
            if (isPointEqual(Obs[i], M)) unique = false;
        }
    } while (!unique || isPointEqual(Food, M));
    return M;
}

void generateObstacle(Point *Obs, List Snake, int mapSize) {
    Point O;
    address P;
    int obsCount = 0;
    srand(time(NULL));
    while (obsCount < (int) (mapSize * mapSize / 5 - 3)) {
        boolean unique;
        do {
            unique = true;
            srand(rand());
            O = createPoint(rand() % mapSize, rand() % mapSize);
            P = Search(Snake, O);
            for (int i = 0; i < obsCount; i++) {
                if (isPointEqual(Obs[i], O)) unique = false;
            }
        } while (P != NULL || !unique);
        Obs[obsCount] = O;
        obsCount++;
        sleep(2);
    }
}

void growSnake(List* Snake, int mapSize) {
    address P = First(*Snake);
    while (Next(P) != NULL) {
        P = Next(P);
    }
    boolean add = false;
    int n = 0;
    Point tail;
    address found;
    while (n < 4 && !add) {
        if (n == 0) tail = createPoint((Info(P).x - 1 + mapSize) % mapSize, Info(P).y);
        if (n == 1) tail = createPoint(Info(P).x, (Info(P).y - 1 + mapSize) % mapSize);
        if (n == 2) tail = createPoint(Info(P).x, (Info(P).y + 1) % mapSize);
        if (n == 3) tail = createPoint((Info(P).x + 1) % mapSize, Info(P).y);
        found = Search(*Snake, tail);
        if (found == NULL) {
            InsVLast(Snake, tail);
            add = true;
        }
        n++;
    }
    if (!add) CreateEmptyList(Snake);
}

void moveSnake(List *Snake, Word comm, int mapSize) {
    address P = First(*Snake);
    if (IsWordEq(comm, toKata("W"))) {
        InsVFirst(Snake, createPoint(Info(P).x, (Info(P).y - 1 + mapSize) % mapSize));
    } else if (IsWordEq(comm, toKata("A"))) {
        InsVFirst(Snake, createPoint((Info(P).x - 1 + mapSize) % mapSize, Info(P).y));
    } else if (IsWordEq(comm, toKata("S"))) {
        InsVFirst(Snake, createPoint(Info(P).x, (Info(P).y + 1 + mapSize) % mapSize));
    } else {
        InsVFirst(Snake, createPoint((Info(P).x + 1 + mapSize) % mapSize, Info(P).y));
    }
    infotypeList dump;
    DelVLast(Snake, &dump);
}

boolean isCollide(List Snake, Point *Obs, int mapSize) {
    address P = First(Snake);
    if (P != NULL) {
        boolean isObs = false;
        for (int i = 0; i < (int) (mapSize * mapSize / 5 - 3); i++) {
            if (isPointEqual(Info(P), Obs[i])) isObs = true;
        }
        if (isObs) {
            return true;
        } else {
            while (Next(P) != NULL) {
                P = Next(P);
                if (isPointEqual(Info(P), Info(First(Snake)))) {
                    return true;
                }
            }
        }
    }
    return false;
}

boolean isMeteorHit(List *Snake, Point Meteor) {
    if (isPointEqual(Info(First(*Snake)), Meteor)) {
        CreateEmptyList(Snake);
        return true;
    } else {
        address P = First(*Snake);
        infotypeList dump;
        while (P != NULL) {
            if (isPointEqual(Info(P), Meteor)) {
                DelVLast(Snake, &dump);
                return true;
            }
            P = Next(P);
        }
    }
    return false;
}

boolean isCmdValid(Word comm) {
    return IsWordEq(comm, toKata("W")) || IsWordEq(comm, toKata("A")) || IsWordEq(comm, toKata("S")) || IsWordEq(comm, toKata("D"));
}

boolean isMoveValid(Word comm, List Snake, Point Crater, boolean silent, int mapSize) {
    address P = First(Snake);
    address B = Next(P);
    if (IsWordEq(comm, toKata("W"))) {
        if ((Info(P).x == Info(B).x) && ((Info(P).y - 1 + mapSize) % mapSize == Info(B).y)) {
            if (!silent) printf("Anda tidak dapat bergerak ke tubuh anda sendiri!  ");
            return false;
        } else if ((Info(P).x == Crater.x) && ((Info(P).y - 1 + mapSize) % mapSize == Crater.y)) {
            if (!silent) printf("Meteor masih panas! Anda belum dapat kembali ke titik tersebut. ");
            return false;
        }
    } else if (IsWordEq(comm, toKata("A"))) {
        if (((Info(P).x - 1 + mapSize) % mapSize == Info(B).x) && (Info(P).y == Info(B).y)) {
            if (!silent) printf("Anda tidak dapat bergerak ke tubuh anda sendiri!  ");
            return false;
        } else if (((Info(P).x - 1 + mapSize) % mapSize == Crater.x) && (Info(P).y == Crater.y)) {
            if (!silent) printf("Meteor masih panas! Anda belum dapat kembali ke titik tersebut. ");
            return false;
        }
    } else if (IsWordEq(comm, toKata("S"))) {
        if ((Info(P).x == Info(B).x) && ((Info(P).y + 1) % mapSize == Info(B).y)) {
            if (!silent) printf("Anda tidak dapat bergerak ke tubuh anda sendiri!  ");
            return false;
        } else if ((Info(P).x == Crater.x) && ((Info(P).y + 1) % mapSize == Crater.y)) {
            if (!silent) printf("Meteor masih panas! Anda belum dapat kembali ke titik tersebut. ");
            return false;
        }
    } else {
        if (((Info(P).x + 1) % mapSize == Info(B).x) && (Info(P).y == Info(B).y)) {
            if (!silent) printf("Anda tidak dapat bergerak ke tubuh anda sendiri!  ");
            return false;
        } else if (((Info(P).x + 1) % mapSize == Crater.x) && (Info(P).y == Crater.y)) {
            if (!silent) printf("Meteor masih panas! Anda belum dapat kembali ke titik tersebut. ");
            return false;
        }
    } 
    return true;
}

void printMap(List Snake, Point *Obs, Point Food, Point Meteor, Point Crater, int mapSize) {
    boolean isSnake;
    printf("o"); for (int o = 0; o < mapSize; o++) printf("-"); printf("o\n");
    for (int i = 0; i < mapSize; i++) {
        printf("|");
        for (int j = 0; j < mapSize; j++) {
            boolean isObstacle = false;
            for (int k = 0; k < (int) (mapSize * mapSize / 5 - 3); k++) {
                if (isPointEqual(createPoint(j, i), Obs[k])) isObstacle = true;
            }
            if (isObstacle) {
                printf("#");
            } else if (isPointEqual(createPoint(j, i), Food)) {
                printf("\033[1;33m");
                printf("o");
                printf("\033[0m");
            } else if (isPointEqual(createPoint(j, i), Meteor)) {
                printf("\033[1;31m");
                printf("0");
                printf("\033[0m");
            } else if (isPointEqual(createPoint(j, i), Crater)) {
                printf("\033[1;37m");
                printf("o");
                printf("\033[0m");
            } else {
                isSnake = false;
                printf("\033[1;32m");
                address P = First(Snake);
                while (P != NULL) {
                    if (isPointEqual(createPoint(j, i), Info(P))) {
                        if (P == First(Snake)) printf("0");
                        else printf("O");
                        isSnake = true;
                    }
                    P = Next(P);
                }
                printf("\033[0m");
                if (!isSnake) printf(" ");
            }
        }
        printf("|\n");
    }
    printf("o"); for (int o = 0; o < mapSize; o++) printf("-"); printf("o\n");
}

void printGuideSoM() {
    for (int i = 8; i > 0; i--) {
        printf("\n _______               __                                _______         __                    \n|     __|.-----.---.-.|  |--.-----.    .-----.-----.    |   |   |.-----.|  |_.-----.-----.----.\n|__     ||     |  _  ||    <|  -__|    |  _  |     |    |       ||  -__||   _|  -__|  _  |   _|\n|_______||__|__|___._||__|__|_____|    |_____|__|__|    |__|_|__||_____||____|_____|_____|__|  \n                                                                                              \n===================================== Petunjuk Permainan =====================================\n\n1. Gunakan perintah W/A/S/D untuk menggerakkan ular.\n2. Arahkan ular untuk bisa mengambil makanan yang berwarna kuning.\n2. Dalam setiap putaran akan ada sebuah meteor yang jatuh secara acak menyebar pada peta.\n4. Meteor yang mengenai tubuh ular akan menyebabkan tubuh ular memendek satu petak.\n5. Apabila meteor mengenai kepala ular, maka ular akan langsung mati.\n6. Setelah meteor jatuh, jejak bekas meteor akan menjadi kawah yang tidak bisa dilewati oleh\n   ular selama satu putaran.\n7. Selain terkena meteor, ular juga dapat mati apabila menabrak obstacle atau tubuhnya sendiri.\n8. Selamat bermain!\n\n==============================================================================================\n\nPermainan akan dimulai dalam %d ...", i);
        sleep(1);
        system("cls");
    }
}