#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "snakeOnMeteor.h"

int playSnakeOnMeteor() {
    int mapSize = 5;
    reset();

    clear();
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
            clear();
        } while (!(IsWordEq(currentWord, toKata("CHANGE MAP")) || IsWordEq(currentWord, toKata("START"))));

        if (IsWordEq(currentWord, toKata("CHANGE MAP"))) {
            int n = 5;
            do {
                clear();
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
        clear();
    } while (!IsWordEq(currentWord, toKata("START")));
    clear();

    printf("Membuat permainan, mohon tunggu ...\n\n");

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

    clear();
    printGuideSoM();


    boolean comm;
    do {
        if (isPointEqual(teleport(Info(First(snake)), mapSize), Food)) {
            Food = generateFood(snake, Obs, Meteor, Crater, mapSize);
            First(snakeCopy) = First(snake);
            growSnake(&snake, mapSize);
        }
        do {
            comm = false;
            do {
                clear();
                printf("Peta Permainan\n");
                #if defined (_WIN32)
                    printMap(snake, Obs, Food, Meteor, Crater, mapSize);
                #else
                    printBasicMap(snake, Obs, Food, Meteor, Crater, mapSize);
                #endif
                if (isHit) printf("Anda terkena meteor! \n");
                else if (turn > 2) printf("Anda beruntung tidak terkena meteor! Silahkan lanjutkan permainan\n");
                
                printf("\nTURN %d\n", turn);
                if (comm) {
                    if (isCmdValid(currentWord)) {
                        if (!isMoveValid(currentWord, snake, Meteor, false, mapSize)) printf("Silahkan masukkan command lainnya\n");
                    }
                    else printf("Command tidak valid! Silahkan input command menggunakan huruf W/A/S/D\n");
                }
                printf("Silahkan masukkan command anda: ");
                GetCommand();
                comm = true;
            } while (!isCmdValid(currentWord));
        } while (!isMoveValid(currentWord, snake, Meteor, true, mapSize));

        moveSnake(&snake, currentWord, mapSize);
        if (!IsEmptyList(snake)) First(snakeCopy) = First(snake);

        if (turn > 1) {
            Crater = Meteor;
        }
        Meteor = generateMeteor(Obs, Food, mapSize);
        
        turn++;

        isHit = isMeteorHit(&snake, Meteor, mapSize);
        isEndGame = isCollide(snake, Obs, mapSize) || IsEmptyList(snake);
    } while (!isEndGame);

    score = NumberElmt(snakeCopy) * 2;
    if (IsEmptyList(snake)) score -= 2;
    clear();
    
    printf("Peta Permainan\n");
    #if defined (_WIN32)
        printMap(snakeCopy, Obs, Food, Meteor, Crater, mapSize);
    #else
        printBasicMap(snakeCopy, Obs, Food, Meteor, Crater, mapSize);
    #endif
    if (isHit) printf("Kepala snake terkena meteor!\n\n");
    else printf("Snake menabrak!\n\n");
    fflush(stdout); sleep(2);

    clear();
    printf("Game berakhir. Skor: %d\n\n", score);

    return score;
}

void generateSnake(List *Snake, int mapSize) {
    srand(time(NULL));
    CreateEmptyList(Snake);
    InsVFirst(Snake, createPoint(rand() % (mapSize - 2) + 2, rand() % mapSize));
    growSnake(Snake, mapSize);
    growSnake(Snake, mapSize);
}

Point generateFood(List Snake, Point *Obs, Point Meteor, Point Crater, int mapSize) {
    Point F;
    address P;
    boolean found;
    boolean unique;
    srand(time(NULL));
    do {
        unique = true;
        srand(rand());
        F = createPoint(rand() % mapSize, rand() % mapSize);
        found = false;
        P = First(Snake);
        while (!found && P != NULL) {
            if (isPointEqual(F, teleport(Info(P), mapSize))) found = true;
            if (!found) P = Next(P);
        }
        for (int i = 0; i < (int) (mapSize * mapSize / 5 - 3); i++) {
            if (isPointEqual(Obs[i], F)) unique = false;
        }
    } while (P != NULL || !unique || isPointEqual(Meteor, F) || isPointEqual(Crater, F));
    return F;
}

Point generateMeteor(Point *Obs, Point Food, int mapSize) {
    Point M;
    boolean unique;
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
    if (!add) CreateEmptyList(Snake);
}

void moveSnake(List *Snake, Word comm, int mapSize) {
    address P = First(*Snake);
    if (IsWordEq(comm, toKata("W"))) {
        InsVFirst(Snake, createPoint(Info(P).x, Info(P).y - 1));
    } else if (IsWordEq(comm, toKata("A"))) {
        InsVFirst(Snake, createPoint(Info(P).x - 1, Info(P).y));
    } else if (IsWordEq(comm, toKata("S"))) {
        InsVFirst(Snake, createPoint(Info(P).x, Info(P).y + 1));
    } else {
        InsVFirst(Snake, createPoint(Info(P).x + 1, Info(P).y));
    }
    infotypeList dump;
    DelVLast(Snake, &dump);
}

boolean isCollide(List Snake, Point *Obs, int mapSize) {
    address P = First(Snake);
    if (P != NULL) {
        for (int i = 0; i < (int) (mapSize * mapSize / 5 - 3); i++) {
            if (isPointEqual(teleport(Info(P), mapSize), Obs[i])) return true;
        }
    }
    return false;
}

boolean isMeteorHit(List *Snake, Point Meteor, int mapSize) {
    if (isPointEqual(teleport(Info(First(*Snake)), mapSize), Meteor)) {
        CreateEmptyList(Snake);
        return true;
    } else {
        address P = First(*Snake);
        boolean found = false;
        while (P != NULL && !found) {
            if (isPointEqual(teleport(Info(P), mapSize), Meteor)) found = true;
            if (!found) P = Next(P);
        }
        if (P != NULL) {
            DelP(Snake, Info(P));
            return true;
        }
    }
    return false;
}

boolean isCmdValid(Word comm) {
    return IsWordEq(comm, toKata("W")) || IsWordEq(comm, toKata("A")) || IsWordEq(comm, toKata("S")) || IsWordEq(comm, toKata("D"));
}

boolean isMoveValid(Word comm, List Snake, Point Crater, boolean silent, int mapSize) {
    address P = First(Snake);
    address dump;
    DelLast(&Snake, &dump);
    Point new;
    if (IsWordEq(comm, toKata("W"))) {
        new = createPoint(Info(P).x, Info(P).y - 1);
        if (Search(Snake, new) != NULL) {
            if (!silent) printf("Anda tidak dapat bergerak ke tubuh anda sendiri!  ");
            InsertLast(&Snake, dump);
            return false;
        } else if (isPointEqual(teleport(new, mapSize), Crater)) {
            if (!silent) printf("Meteor masih panas! Anda belum dapat kembali ke titik tersebut. ");
            InsertLast(&Snake, dump);
            return false;
        }
    } else if (IsWordEq(comm, toKata("A"))) {
        Point new = createPoint(Info(P).x - 1, Info(P).y);
        if (Search(Snake, new) != NULL) {
            if (!silent) printf("Anda tidak dapat bergerak ke tubuh anda sendiri!  ");
            InsertLast(&Snake, dump);
            return false;
        } else if (isPointEqual(teleport(new, mapSize), Crater)) {
            if (!silent) printf("Meteor masih panas! Anda belum dapat kembali ke titik tersebut. ");
            InsertLast(&Snake, dump);
            return false;
        }
    } else if (IsWordEq(comm, toKata("S"))) {
        Point new = createPoint(Info(P).x, Info(P).y + 1);
        if (Search(Snake, new) != NULL) {
            if (!silent) printf("Anda tidak dapat bergerak ke tubuh anda sendiri!  ");
            InsertLast(&Snake, dump);
            return false;
        } else if (isPointEqual(teleport(new, mapSize), Crater)) {
            if (!silent) printf("Meteor masih panas! Anda belum dapat kembali ke titik tersebut. ");
            InsertLast(&Snake, dump);
            return false;
        }
    } else {
        Point new = createPoint(Info(P).x + 1, Info(P).y);
        if (Search(Snake, new) != NULL) {
            if (!silent) printf("Anda tidak dapat bergerak ke tubuh anda sendiri!  ");
            InsertLast(&Snake, dump);
            return false;
        } else if (isPointEqual(teleport(new, mapSize), Crater)) {
            if (!silent) printf("Meteor masih panas! Anda belum dapat kembali ke titik tersebut. ");
            InsertLast(&Snake, dump);
            return false;
        }
    } 
    InsertLast(&Snake, dump);
    return true;
}

Point teleport(Point P, int mapSize) {
    int x = P.x;
    int y = P.y;

    while (x < 0) x += mapSize;
    while (y < 0) y += mapSize;

    x = x % mapSize;
    y = y % mapSize;

    return createPoint(x, y);
}

void printMap(List Snake, Point *Obs, Point Food, Point Meteor, Point Crater, int mapSize) {
    boolean isSnake;
    for (int row = 0; row < mapSize; row++) {
        // Top border
        if (row == 0) {
            printf("\xda");
            for (int col = 0; col < mapSize; col++) {
                if (col == mapSize - 1) printf("\xc4\xc4\xc4\xc4\xc4\xc4\xbf\n");
                else printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc2");
            }
        }
        else {
            printf("\xc3");
            for (int col = 0; col < mapSize; col++) {
                if (col == mapSize - 1) printf("\xc4\xc4\xc4\xc4\xc4\xc4\xb4\n");
                else printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc5");
            }
        }
        // Cell content
        for (int line = 0; line < 3; line++) {
            for (int col = 0; col < mapSize; col++) {
                printf("\xb3");
                boolean isObstacle = false;
                for (int k = 0; k < (int) (mapSize * mapSize / 5 - 3); k++) {
                    if (isPointEqual(createPoint(col, row), Obs[k])) isObstacle = true;
                }
                if (isObstacle) {
                    if (line == 0) printf("\xdb\xdb\xb2\xb2\xb1\xb1");
                    else if (line == 1) printf("\xb1\xb1\xdb\xdb\xb2\xb2");
                    else printf("\xb2\xb2\xb1\xb1\xdb\xdb");
                } else if (isPointEqual(createPoint(col, row), Food)) {
                    yellow();
                    if (line == 0) printf("      ");
                    else if (line == 1) printf("  \xdb\xdb  ");
                    else printf("      ");
                } else if (isPointEqual(createPoint(col, row), Meteor)) {
                    red();
                    if (line == 0) printf("\xd9 \xdc\xdc \xc0");
                    else if (line == 1) printf(" \xdb\xdb\xdb\xdb ");
                    else printf("\xbf \xdf\xdf \xda");
                } else if (isPointEqual(createPoint(col, row), Crater)) {
                    if (line == 0) printf("\xd9 \xc2\xc2 \xc0");
                    else if (line == 1) printf(" \xc3\xc5\xc5\xb4 ");
                    else printf("\xbf \xc1\xc1 \xda");
                } else {
                    boolean isSnake = false;
                    address target = First(Snake);
                    while (target != NULL && !isSnake) {
                        if (isPointEqual(createPoint(col, row), teleport(Info(target), mapSize))) isSnake = true;
                        if (!isSnake) target = Next(target);
                    }
                    if (isSnake) {
                        green();
                        address next = Next(target);
                        address before;
                        if (target != First(Snake)) {
                            before = First(Snake);
                            while (Next(before) != target && before != NULL) {
                                before = Next(before);
                            }
                        }

                        if (target == First(Snake)) {
                            if (next != NULL) {
                                if (Info(next).x == Info(target).x) {
                                    if (Info(next).y < Info(target).y) {
                                        if (line == 2) printf(" \xdf\xdb\xdb\xdf ");
                                        else if (line == 0) printf("  \xdb\xdb  ");
                                    } else {
                                        if (line == 0) printf(" \xdc\xdb\xdb\xdc ");
                                        else if (line == 2) printf("  \xdb\xdb  ");
                                    }
                                    if (line == 1) printf(" \xdb\xdb\xdb\xdb ");
                                } else if (Info(next).y == Info(target).y) {
                                    if (Info(next).x < Info(target).x) {
                                        if (line == 2) printf("  \xdf\xdf\xdf ");
                                        else if (line == 0) printf("  \xdc\xdc\xdc ");
                                    } else {
                                        if (line == 2) printf(" \xdf\xdf\xdf  ");
                                        else if (line == 0) printf(" \xdc\xdc\xdc  ");
                                    }
                                    if (line == 1) printf("\xdb\xdb\xdb\xdb\xdb\xdb");
                                } else if (Info(next).y < Info(target).y) {
                                    if (Info(next).x < Info(target).x) {
                                        if (line == 0) printf("\xdb\xdb\xdc\xdc  ");
                                        else if (line == 1) printf(" \xdb\xdb\xdb\xdb\xdc");
                                        else printf("  \xdf\xdb\xdb\xdf");
                                    } else {
                                        if (line == 0) printf("  \xdc\xdc\xdb\xdb");
                                        else if (line == 1) printf("\xdc\xdb\xdb\xdb\xdb ");
                                        else printf("\xdf\xdb\xdb\xdf  ");
                                    }
                                } else {
                                    if (Info(next).x < Info(target).x) {
                                        if (line == 0) printf("  \xdc\xdb\xdb\xdc");
                                        else if (line == 1) printf(" \xdb\xdb\xdb\xdb\xdf");
                                        else printf("\xdb\xdb\xdf\xdf  ");
                                    } else {
                                        if (line == 0) printf("\xdc\xdb\xdb\xdc  ");
                                        else if (line == 1) printf("\xdf\xdb\xdb\xdb\xdb ");
                                        else printf("  \xdf\xdf\xdb\xdb");
                                    }
                                }
                            } else {
                                if (line == 0) printf("  \xdc\xdc  ");
                                else if (line == 1) printf(" \xdb\xdb\xdb\xdb ");
                                else printf("  \xdf\xdf  ");
                            }
                        } else if (next != NULL) {
                            if (line == 0) {
                                if (Info(before).y < Info(target).y || Info(next).y < Info(target).y) {
                                    if ((Info(before).x < Info(target).x && Info(before).y < Info(target).y) || (Info(next).x < Info(target).x && Info(next).y < Info(target).y)) printf("\xdb\xdb");
                                    else printf("  ");

                                    if ((Info(before).x == Info(target).x && Info(before).y < Info(target).y) || (Info(next).x == Info(target).x && Info(next).y < Info(target).y)) printf("\xdb\xdb");
                                    else if ((Info(before).x < Info(target).x && Info(before).y < Info(target).y) || (Info(next).x < Info(target).x && Info(next).y < Info(target).y)) {
                                        printf("\xdc");
                                        if ((Info(before).x > Info(target).x && Info(before).y < Info(target).y) || (Info(next).x > Info(target).x && Info(next).y < Info(target).y)) printf("\xdc");
                                        else printf(" ");
                                    }
                                    else if ((Info(before).x > Info(target).x && Info(before).y < Info(target).y) || (Info(next).x > Info(target).x && Info(next).y < Info(target).y)) printf(" \xdc");
                                    else printf("  ");

                                    if ((Info(before).x > Info(target).x && Info(before).y < Info(target).y) || (Info(next).x > Info(target).x && Info(next).y < Info(target).y)) printf("\xdb\xdb");
                                    else printf("  ");
                                } else {
                                    printf("      ");
                                }
                            } else if (line == 1) {
                                if (Info(before).x < Info(target).x || Info(next).x < Info(target).x) {
                                    if ((Info(before).y == Info(target).y && Info(before).x < Info(target).x) || (Info(next).y == Info(target).y && Info(next).x < Info(target).x)) printf("\xdb\xdb");
                                    else if (Info(before).x < Info(target).x && Info(next).x < Info(target).x) printf(" \xdb");
                                    else if ((Info(before).y < Info(target).y && Info(before).x < Info(target).x) || (Info(next).y < Info(target).y && Info(next).x < Info(target).x)) printf(" \xdf");
                                    else printf(" \xdc");
                                } else {
                                    printf("  ");
                                }

                                printf("\xdb\xdb");

                                if (Info(before).x > Info(target).x || Info(next).x > Info(target).x) {
                                    if ((Info(before).y == Info(target).y && Info(before).x > Info(target).x) || (Info(next).y == Info(target).y && Info(next).x > Info(target).x)) printf("\xdb\xdb");
                                    else if (Info(before).x > Info(target).x && Info(next).x > Info(target).x) printf("\xdb ");
                                    else if ((Info(before).y < Info(target).y && Info(before).x > Info(target).x) || (Info(next).y < Info(target).y && Info(next).x > Info(target).x)) printf("\xdf ");
                                    else printf("\xdc ");
                                } else {
                                    printf("  ");
                                }
                            } else {
                                if (Info(before).y > Info(target).y || Info(next).y > Info(target).y) {
                                    if ((Info(before).x < Info(target).x && Info(before).y > Info(target).y) || (Info(next).x < Info(target).x && Info(next).y > Info(target).y)) printf("\xdb\xdb");
                                    else printf("  ");

                                    if ((Info(before).x == Info(target).x && Info(before).y > Info(target).y) || (Info(next).x == Info(target).x && Info(next).y > Info(target).y)) printf("\xdb\xdb");
                                    else if ((Info(before).x < Info(target).x && Info(before).y > Info(target).y) || (Info(next).x < Info(target).x && Info(next).y > Info(target).y)) {
                                        printf("\xdf");
                                        if ((Info(before).x > Info(target).x && Info(before).y > Info(target).y) || (Info(next).x > Info(target).x && Info(next).y > Info(target).y)) printf("\xdf");
                                        else printf(" ");
                                    }
                                    else if ((Info(before).x > Info(target).x && Info(before).y > Info(target).y) || (Info(next).x > Info(target).x && Info(next).y > Info(target).y)) printf(" \xdf");
                                    else printf("  ");

                                    if ((Info(before).x > Info(target).x && Info(before).y > Info(target).y) || (Info(next).x > Info(target).x && Info(next).y > Info(target).y)) printf("\xdb\xdb");
                                    else printf("  ");
                                } else {
                                    printf("      ");
                                }
                            }
                        } else {
                            if (Info(before).x == Info(target).x) {
                                
                                if (Info(before).y < Info(target).y) {
                                    if (line == 0) printf("  \xdb\xdb  ");
                                    else if (line == 1) printf("  \xde\xdd  ");
                                    else printf("      ");
                                } else {
                                    if (line == 0) printf("      ");
                                    else if (line == 1) printf("  \xde\xdd  ");
                                    else printf("  \xdb\xdb  ");
                                }
                            } else if (Info(before).y == Info(target).y) {
                                if (line == 1) {
                                    if (Info(before).x < Info(target).x) printf("\xdb\xdb\xfe\xfe  ");
                                    else printf("  \xfe\xfe\xdb\xdb");
                                } else printf("      ");
                            } else if (Info(before).y < Info(target).y) {
                                if (Info(before).x < Info(target).x) {
                                    if (line == 0) printf("\xdb\xdb\xdc   ");
                                    if (line == 1) printf(" \xdf\xdb   ");
                                } else {
                                    if (line == 0) printf("   \xdc\xdb\xdb");
                                    if (line == 1) printf("   \xdb\xdf ");
                                }
                                if (line == 2) printf("      ");
                            } else {
                                if (Info(before).x < Info(target).x) {
                                    if (line == 2) printf("\xdb\xdb\xdf   ");
                                    if (line == 1) printf(" \xdc\xdb   ");
                                } else {
                                    if (line == 2) printf("   \xdf\xdb\xdb");
                                    if (line == 1) printf("   \xdb\xdc ");
                                }
                                if (line == 0) printf("      ");
                            }
                        }
                    } else {
                        printf("      ");
                    }
                }
                reset();
            }
            printf("\xb3\n");
        }
        
    }
    // Bottom border
    printf("\xc0");
    for (int col = 0; col < mapSize; col++) {
        if (col == mapSize - 1) printf("\xc4\xc4\xc4\xc4\xc4\xc4\xd9\n");
        else printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc1");
    }
}

void printBasicMap(List Snake, Point *Obs, Point Food, Point Meteor, Point Crater, int mapSize) {
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
                yellow();
                printf("o");
            } else if (isPointEqual(createPoint(j, i), Meteor)) {
                red();
                printf("0");
            } else if (isPointEqual(createPoint(j, i), Crater)) {
                white();
                printf("o");
            } else {
                isSnake = false;
                green();
                address P = First(Snake);
                while (P != NULL) {
                    if (isPointEqual(createPoint(j, i), teleport(Info(P), mapSize))) {
                        if (P == First(Snake)) printf("0");
                        else printf("O");
                        isSnake = true;
                    }
                    P = Next(P);
                }
                reset();
                if (!isSnake) printf(" ");
            }
            reset();
        }
        printf("|\n");
    }
    printf("o"); for (int o = 0; o < mapSize; o++) printf("-"); printf("o\n");
}

void printGuideSoM() {
    for (int i = 5; i > 0; i--) {
        printf("\n _______               __                                _______         __                    \n|     __|.-----.---.-.|  |--.-----.    .-----.-----.    |   |   |.-----.|  |_.-----.-----.----.\n|__     ||     |  _  ||    <|  -__|    |  _  |     |    |       ||  -__||   _|  -__|  _  |   _|\n|_______||__|__|___._||__|__|_____|    |_____|__|__|    |__|_|__||_____||____|_____|_____|__|  \n                                                                                              \n===================================== Petunjuk Permainan =====================================\n\n1. Gunakan perintah W/A/S/D untuk menggerakkan ular.\n2. Arahkan ular untuk bisa mengambil makanan yang berwarna kuning.\n2. Dalam setiap putaran akan ada sebuah meteor yang jatuh secara acak menyebar pada peta.\n4. Meteor yang mengenai tubuh ular akan menyebabkan tubuh ular memendek satu petak.\n5. Apabila meteor mengenai kepala ular, maka ular akan langsung mati.\n6. Setelah meteor jatuh, jejak bekas meteor akan menjadi kawah yang tidak bisa dilewati oleh\n   ular selama satu putaran.\n7. Selain terkena meteor, ular juga dapat mati apabila menabrak obstacle.\n8. Selamat bermain!\n\n==============================================================================================\n\nPermainan akan dimulai dalam %d ...", i);
        fflush(stdout); sleep(1);
        clear();
    }
}