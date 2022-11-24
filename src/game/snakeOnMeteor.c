#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "snakeOnMeteor.h"


int playSnakeOnMeteor() {
    int score = 0, turn = 1;
    boolean isEndGame = false, isHit = false;

    List snake, snakeCopy;
    generateSnake(&snake);

    Point Obs1, Obs2, Food, Meteor, Crater;

    Obs1 = generateObstacle(snake);
    do {
        Obs2 = generateObstacle(snake);
    } while (isPointEqual(Obs1, Obs2));
    setPointNull(&Meteor);
    setPointNull(&Crater);
    Food = generateFood(snake, Obs1, Obs2, Meteor, Crater);

    system("cls");
    printGuideSoM();


    currentWord = toKata("W");
    do {
        if (isPointEqual(Info(First(snake)), Food)) {
            Food = generateFood(snake, Obs1, Obs2, Meteor, Crater);
            growSnake(&snake);
        }
        do {
            do {
                system("cls");
                printf("Peta Permainan\n");
                printMap(snake, Obs1, Obs2, Food, Meteor, Crater);
                if (isHit) printf("Anda terkena meteor! \n");
                else if (turn > 2) printf("Anda beruntung tidak terkena meteor! Silahkan lanjutkan permainan\n");
                
                printf("\nTURN %d\n", turn);
                if (isCmdValid(currentWord)) {
                    if (!isMoveValid(currentWord, snake, Meteor, false)) printf("Silahkan masukkan command lainnya\n");
                }
                if (!isCmdValid(currentWord)) printf("Command tidak valid! Silahkan input command menggunakan huruf W/A/S/D\n");
                printf("Silahkan masukkan command anda: ");
                GetCommand();
            } while (!isCmdValid(currentWord));
        } while (!isMoveValid(currentWord, snake, Meteor, true));

        moveSnake(&snake, currentWord);
        First(snakeCopy) = First(snake);

        if (turn > 1) {
            Crater = Meteor;
        }
        Meteor = generateMeteor(Obs1, Obs2, Food);
        
        turn++;

        isHit = isMeteorHit(&snake, Meteor);
        isEndGame = isCollide(snake, Obs1, Obs2) || IsEmptyList(snake);
    } while (!isEndGame);

    score = NumberElmt(snakeCopy) * 2;
    if (IsEmptyList(snake)) score -= 2;
    system("cls");
    
    printf("Peta Permainan\n");
    printMap(snakeCopy, Obs1, Obs2, Food, Meteor, Crater);
    if (isHit) printf("Kepala snake terkena meteor!\n\n");
    else printf("Snake menabrak!\n\n");
    sleep(2);

    system("cls");
    printf("Game berakhir. Skor: %d\n\n", score);

    return score;
}

void generateSnake(List *Snake) {
    CreateEmptyList(Snake);
    for (int i = (int) (MapSize / 2); i >= 0; i--) {
        InsVLast(Snake, createPoint(i, (int) (MapSize / 2)));
    }
}

Point generateFood(List Snake, Point Obstacle1, Point Obstacle2, Point Meteor, Point Crater) {
    Point F;
    address P;
    srand(time(NULL));
    do {
        srand(rand());
        F = createPoint(rand() % MapSize, rand() % MapSize);
        P = Search(Snake, F);
    } while (P != NULL || isPointEqual(Obstacle1, F) || isPointEqual(Obstacle2, F) || isPointEqual(Meteor, F) || isPointEqual(Crater, F));
    return F;
}

Point generateMeteor(Point Obstacle1, Point Obstacle2, Point Food) {
    Point M;
    srand(time(NULL));
    do {
        srand(rand());
        M = createPoint(rand() % MapSize, rand() % MapSize);
    } while (isPointEqual(Obstacle1, M) || isPointEqual(Obstacle2, M) || isPointEqual(Food, M));
    return M;
}

Point generateObstacle(List Snake) {
    Point O;
    address P;
    srand(time(NULL));
    do {
        srand(rand());
        O = createPoint(rand() % MapSize, rand() % MapSize);
        P = Search(Snake, O);
    } while (P != NULL);
    return O;
}

void growSnake(List* Snake) {
    address P = First(*Snake);
    while (Next(P) != NULL) {
        P = Next(P);
    }
    boolean add = false;
    int n = 0;
    Point tail;
    address found;
    while (n < 4 && !add) {
        if (n == 0) tail = createPoint(Info(P).x - 1, Info(P).y);
        if (n == 1) tail = createPoint(Info(P).x, Info(P).y - 1);
        if (n == 2) tail = createPoint(Info(P).x, Info(P).y + 1);
        if (n == 3) tail = createPoint(Info(P).x + 1, Info(P).y);
        found = Search(*Snake, tail);
        if (found == NULL) {
            InsVLast(Snake, tail);
            add = true;
        }
        n++;
    }
    if (!add) InsVLast(Snake, tail);
    
}

void moveSnake(List *Snake, Word comm) {
    address P = First(*Snake);
    if (IsWordEq(comm, toKata("W"))) {
        InsVFirst(Snake, createPoint(Info(P).x, (Info(P).y - 1 + MapSize) % MapSize));
    } else if (IsWordEq(comm, toKata("A"))) {
        InsVFirst(Snake, createPoint((Info(P).x - 1 + MapSize) % MapSize, Info(P).y));
    } else if (IsWordEq(comm, toKata("S"))) {
        InsVFirst(Snake, createPoint(Info(P).x, (Info(P).y + 1 + MapSize) % MapSize));
    } else {
        InsVFirst(Snake, createPoint((Info(P).x + 1 + MapSize) % MapSize, Info(P).y));
    }
    infotypeList dump;
    DelVLast(Snake, &dump);
}

boolean isCollide(List Snake, Point Obstacle1, Point Obstacle2) {
    address P = First(Snake);
    if (P != NULL) {
        if (isPointEqual(Info(P), Obstacle1) || isPointEqual(Info(P), Obstacle2)) {
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

boolean isMoveValid(Word comm, List Snake, Point Crater, boolean silent) {
    address P = First(Snake);
    address B = Next(P);
    if (IsWordEq(comm, toKata("W"))) {
        if ((Info(P).x == Info(B).x) && ((Info(P).y - 1 + MapSize) % MapSize == Info(B).y)) {
            if (!silent) printf("Anda tidak dapat bergerak ke tubuh anda sendiri!  ");
            return false;
        } else if ((Info(P).x == Crater.x) && ((Info(P).y - 1 + MapSize) % MapSize == Crater.y)) {
            if (!silent) printf("Meteor masih panas! Anda belum dapat kembali ke titik tersebut. ");
            return false;
        }
    } else if (IsWordEq(comm, toKata("A"))) {
        if (((Info(P).x - 1 + MapSize) % MapSize == Info(B).x) && (Info(P).y == Info(B).y)) {
            if (!silent) printf("Anda tidak dapat bergerak ke tubuh anda sendiri!  ");
            return false;
        } else if (((Info(P).x - 1 + MapSize) % MapSize == Crater.x) && (Info(P).y == Crater.y)) {
            if (!silent) printf("Meteor masih panas! Anda belum dapat kembali ke titik tersebut. ");
            return false;
        }
    } else if (IsWordEq(comm, toKata("S"))) {
        if ((Info(P).x == Info(B).x) && ((Info(P).y + 1) % MapSize == Info(B).y)) {
            if (!silent) printf("Anda tidak dapat bergerak ke tubuh anda sendiri!  ");
            return false;
        } else if ((Info(P).x == Crater.x) && ((Info(P).y + 1) % MapSize == Crater.y)) {
            if (!silent) printf("Meteor masih panas! Anda belum dapat kembali ke titik tersebut. ");
            return false;
        }
    } else {
        if (((Info(P).x + 1) % MapSize == Info(B).x) && (Info(P).y == Info(B).y)) {
            if (!silent) printf("Anda tidak dapat bergerak ke tubuh anda sendiri!  ");
            return false;
        } else if (((Info(P).x + 1) % MapSize == Crater.x) && (Info(P).y == Crater.y)) {
            if (!silent) printf("Meteor masih panas! Anda belum dapat kembali ke titik tersebut. ");
            return false;
        }
    } 
    return true;
}

void printMap(List Snake, Point Obs1, Point Obs2, Point Food, Point Meteor, Point Crater) {
    boolean isSnake;
    printf("o"); for (int o = 0; o < MapSize; o++) printf("-"); printf("o\n");
    for (int i = 0; i < MapSize; i++) {
        printf("|");
        for (int j = 0; j < MapSize; j++) {
            if (isPointEqual(createPoint(j, i), Obs1)) {
                printf("#");
            } else if (isPointEqual(createPoint(j, i), Obs2)) {
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
    printf("o"); for (int o = 0; o < MapSize; o++) printf("-"); printf("o\n");
}

void printGuideSoM() {
    for (int i = 8; i > 0; i--) {
        printf("\n _______               __                                _______         __                    \n|     __|.-----.---.-.|  |--.-----.    .-----.-----.    |   |   |.-----.|  |_.-----.-----.----.\n|__     ||     |  _  ||    <|  -__|    |  _  |     |    |       ||  -__||   _|  -__|  _  |   _|\n|_______||__|__|___._||__|__|_____|    |_____|__|__|    |__|_|__||_____||____|_____|_____|__|  \n                                                                                              \n===================================== Petunjuk Permainan =====================================\n\n1. Gunakan perintah W/A/S/D untuk menggerakkan ular.\n2. Arahkan ular untuk bisa mengambil makanan yang berwarna kuning.\n2. Dalam setiap putaran akan ada sebuah meteor yang jatuh secara acak menyebar pada peta.\n4. Meteor yang mengenai tubuh ular akan menyebabkan tubuh ular memendek satu petak.\n5. Apabila meteor mengenai kepala ular, maka ular akan langsung mati.\n6. Setelah meteor jatuh, jejak bekas meteor akan menjadi kawah yang tidak bisa dilewati oleh\n   ular selama satu putaran.\n7. Selain terkena meteor, ular juga dapat mati apabila menabrak obstacle atau tubuhnya sendiri.\n8. Selamat bermain!\n\n==============================================================================================\n\nPermainan akan dimulai dalam %d ...", i);
        sleep(1);
        system("cls");
    }
}