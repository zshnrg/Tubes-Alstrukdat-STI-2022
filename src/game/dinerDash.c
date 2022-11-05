#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "dinerDash.h"

#define UNDEF -999

void dinerDashPlay () {
    int served = 0, score = 0, m = 2;
    Makanan done;
    ListMakanan pesanan, dimasak, ready;
    createEmpty(&pesanan);
    createEmpty(&dimasak);
    createEmpty(&ready);

    insertMakanan(&pesanan, createMakanan(0));
    insertMakanan(&pesanan, createMakanan(1));

    system("cls");
    printf("[===================== Selamat Datang di =====================]\n");
    printf("                                                            _\n  _____  _                   _____            _            / )\n |  __ \\(_)                 |  __ \\          | |     |||| / /\n | |  | |_ _ __   ___ _ __  | |  | | __ _ ___| |__   ||||/ /\n | |  | | | '_ \\ / _ \\ '__| | |  | |/ _` / __| '_ \\  \\__(_/\n | |__| | | | | |  __/ |    | |__| | (_| \\__ \\ | | |  ||//\n |_____/|_|_| |_|\\___|_|    |_____/ \\__,_|___/_| |_|  ||/\n                                                     (|| \n                                                      \"\"");
    printf("\n[=============================================================]\n\n> Loading ");
    for (int i = 0; i < 3; i++) {
        printf("."); sleep(1);
    }

    while (served < 15 && pesanan.NEff <= 7) {
        if (m > 2) {
            if (IsWordEq(AccessCommand(currentWord, 0), toKata("COOK"))) {
                cook(&dimasak, getFood(pesanan, getFoodId(AccessCommand(currentWord, 1))));
            } else if (IsWordEq(AccessCommand(currentWord, 0), toKata("SERVE"))) {
                score += serve(&pesanan, &ready).Harga;
            }
            
            updateCooking(&dimasak, &ready);
        }
        sleep(2); system("cls"); 

        insertMakanan(&pesanan, createMakanan(m));
        printf("SALDO: %d\n\n", score);

        cetakPesanan(pesanan);
        cetakDimasak(dimasak);
        cetakMakananReady(ready);

        do {
            printf("\nMASUKKAN COMMAND: ");
            GetCommand();
        } while (!isCommandValid(currentWord, pesanan, dimasak, ready));
        m++;
    }
    system("cls");
    printf("Game over! Skor akhir: %d\n\n", score);
}

void createEmpty(ListMakanan *l) {
    (*l).NEff = 0;
}

Makanan createMakanan(int Id) {
    struct timeval t;
    gettimeofday(&t, NULL);
    srand(t.tv_usec);
    Makanan M;
    M.ID = Id;
    M.Durasi = (rand() % 4) + 1;
    M.Ketahanan = (rand() % 5) + 1;
    M.Harga = (rand() % 40001) + 10000;
    for (int i = 0; i < 3000000; i++);
    return M;
}

void insertMakanan(ListMakanan *l, Makanan v) {
    (*l).List[(*l).NEff] = v;
    (*l).NEff++;
}

void removeMakanan(ListMakanan *l, int Idx) {
    boolean found = false;
    for (int i = 0; i < (*l).NEff - 1; i++) {
        if ((*l).List[i].ID == Idx) found = true;
        if (found) {
            (*l).List[i] = (*l).List[i + 1];
        }
    }
    (*l).NEff--;
}

int getFoodId(Word comm) {
    int n = 0;
    if (comm.Length < 2 || comm.TabWord[0] != 'M') {
        return UNDEF;
    }
    for (int i = 1; i < comm.Length; i++) {
        n = n * 10;
        n += comm.TabWord[i] - '0';
    }
    return n;
}

Makanan getFood(ListMakanan l, int Idx) {
    for (int i = 0; i < l.NEff; i++) {
        if (l.List[i].ID == Idx) return l.List[i];
    }
}

int idMinMakanan(ListMakanan pesanan) {
    int min = pesanan.List[0].ID;
    for (int i = 0; i < pesanan.NEff; i++) {
        if (pesanan.List[i].ID < min) min = pesanan.List[i].ID;
    }
    return min;
}

boolean isKosong(ListMakanan l) {
    return l.NEff == 0;
}

boolean isCommandValid(Word comm, ListMakanan pesanan, ListMakanan dimasak, ListMakanan ready) {
    if (IsWordEq(AccessCommand(currentWord, 0), toKata("COOK"))) {
        if (isMember(dimasak, getFoodId(AccessCommand(currentWord, 1)))) {
            printf("\n"); TulisWord(AccessCommand(currentWord, 1)); printf(" sedang dimasak.\n");
            return false;
        }
        if (dimasak.NEff == 5) {
            printf("\nTempat memasak penuh! Kamu hanya bisa memasak 5 Makanan dalam satu waktu.\n");
        }
        if (isMember(pesanan, getFoodId(AccessCommand(currentWord, 1)))) {
            return true;
        } else {
            printf("\n"); TulisWord(AccessCommand(currentWord, 1)); printf(" tidak ada dalam pesanan.\n");
            return false;
        }
    } else if (IsWordEq(AccessCommand(currentWord, 0), toKata("SERVE"))) {
        if (isMember(ready, getFoodId(AccessCommand(currentWord, 1)))) {
            int min = idMinMakanan(pesanan);
            if (getFoodId(AccessCommand(currentWord, 1)) > min) {
                printf("\n"); TulisWord(AccessCommand(currentWord, 1)); printf(" belum dapat diselesaikan karena M%d belum selesai", min);
                return false;
            }
            return true;
        } else {
            printf("\n"); TulisWord(AccessCommand(currentWord, 1)); printf(" tidak ada dalam daftar Makanan yang bisa disajikan.\n");
            return false;
        }
    } else {
        printf("Command tidak valid. Silakan coba lagi.\n");
        return false;
    }
}

boolean isMember(ListMakanan l, int Idx) {
    for (int i = 0; i < l.NEff; i++) {
        if (l.List[i].ID == Idx) {
            return true;
        }
    }
    return false;
}

boolean isDimasak(ListMakanan l, int Idx) {
    for (int i = 0; i < l.NEff; i++) {
        if (l.List[i].ID = Idx) return true;
    }
    return false;
}


void cook(ListMakanan* dimasak, Makanan v) {
    v.Durasi++;
    v.Ketahanan++;
    (*dimasak).List[(*dimasak).NEff] = v;
    (*dimasak).NEff++;
    printf("\nBerhasil memasak M%d\n", v.ID);
}

void updateCooking(ListMakanan *dimasak, ListMakanan *ready) {
    for (int i = 0; i < (*dimasak).NEff; i++) {
        (*dimasak).List[i].Durasi--;
        if ((*dimasak).List[i].Durasi == 0) {
            insertMakanan(ready, (*dimasak).List[i]);
            printf("Makanan M%d telah selesai dimasak\n", (*dimasak).List[i].ID);
            removeMakanan(dimasak, (*dimasak).List[i].ID);
        }
    }
    for (int i = 0; i < (*ready).NEff; i++) {
        (*ready).List[i].Ketahanan--;
        if ((*ready).List[i].Ketahanan == 0) {
            printf("Makanan M%d perlu dimasak ulang\n", (*ready).List[i].ID);
            removeMakanan(ready, (*ready).List[i].ID);
        }
    }
}

Makanan serve(ListMakanan *pesanan, ListMakanan *ready) {
    int target = getFoodId(AccessCommand(currentWord, 1));
    Makanan served = getFood(*ready, target);
    removeMakanan(ready, target);
    removeMakanan(pesanan, target);
    printf("\nBerhasil mengantar M%d\n", served.ID);
    return served;
}


void cetakPesanan(ListMakanan pesanan) {
    printf("Daftar pesanan\n");
    if (isKosong(pesanan)) printf("Makanan | Durasi memasak | Ketahanan | Harga\n--------+----------------+-----------+-------\n        |                |           |\n");
    else {
        printf("Makanan | Durasi memasak | Ketahanan | Harga\n--------+----------------+-----------+-------\n");
        for (int i = 0; i < pesanan.NEff; i++) {
            printf("M%d\t| %d\t\t | %d\t     | %d\n", pesanan.List[i].ID, pesanan.List[i].Durasi, pesanan.List[i].Ketahanan, pesanan.List[i].Harga);
        }
    }
    printf("\n");
}

void cetakDimasak(ListMakanan dimasak) {
    printf("Daftar Makanan yang sedang dimasak\n");
    if (isKosong(dimasak)) printf("Makanan | Sisa durasi memasak\n--------+------------------------\n        |\n");
    else {
        printf("Makanan | Sisa durasi memasak\n--------+------------------------\n");
        for (int i = 0; i < dimasak.NEff; i++) {
            printf("M%d\t| %d\n", dimasak.List[i].ID, dimasak.List[i].Durasi);
        }
    }
    printf("\n");
}

void cetakMakananReady(ListMakanan ready) {
    printf("Daftar Makanan yang dapat disajikan\n");
    if (isKosong(ready)) printf("Makanan | Sisa ketahanan makanan\n--------+-----------------------\n        |\n");
    else {
        printf("Makanan | Sisa ketahanan makanan\n--------+-----------------------\n");
        for (int i = 0; i < ready.NEff; i++) {
            printf("M%d\t| %d\n", ready.List[i].ID, ready.List[i].Ketahanan);
        }
    }
    printf("\n");
}
