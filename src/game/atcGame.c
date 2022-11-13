#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "atcGame.h"

boolean isEnd;


int main() {
    playAtc();
}

void playAtc() {
    srand(time(NULL));
    boolean isEnd = false;

    Queue BandaraM, BandaraB;
    createBandara(&BandaraB);
    createBandara(&BandaraM);

    TabKata LandingM, LandingB;
    MakeEmpty(&LandingM);
    MakeEmpty(&LandingB);

    Langit L; L.NEff = 0;

    int countM = 0, countB = 0, score = 0;
    float diff = 1;

    Queue Pesawat;
    int x = rand();
    if (x % 2 == 0) {
        createPesawat(&Pesawat, countM, 'M');
        countM++;
    } else {
        createPesawat(&Pesawat, countB, 'B');
        countB++;
    }
    insertPesawat(&L, Pesawat);

    while (!isEnd) {
        system("cls");
        printf("SCORE: %d\n\n", score);
        printStatus(BandaraM, BandaraB, L);

        while (countM + countB < diff) {
            srand(rand());
            x = rand();
            if (x % 2 == 0) {
                createPesawat(&Pesawat, countM, 'M');
                countM++;
            } else {
                createPesawat(&Pesawat, countB, 'B');
                countB++;
            }
            insertPesawat(&L, Pesawat);
        }

        do {
            printf("MASUKKAN COMMAND: ");
            GetCommand();
            if (!isCommVal(currentWord, L)) {
                printf("\nCommand tidak valid.\n");
            }
        } while (!isCommVal(currentWord, L));

        if (!IsWordEq(currentWord, toKata("SKIP"))) {
            accPesawat(&L, currentWord);
        }
        updateStatus(&BandaraM, &BandaraB, &L, &LandingM, &LandingB); 

        if (NbElmt(LandingM) > 1 || NbElmt(LandingB) > 1) {
            isEnd = true;
        } else {
            if (NbElmt(LandingM) > 0) {
                insertLanding(&BandaraM, &LandingM);
                score += 100;
            } if (NbElmt(LandingB) > 0) {
                insertLanding(&BandaraB, &LandingB);
                score += 100;
            }
        }

        diff = diff * 1.1;
    }

}

void createPesawat (Queue *Pesawat, int ID, char color) {
    Word num = intToWord(ID);
    srand(rand());

    for (int i = num.Length; i > 0; i--) {
        num.TabWord[i] = num.TabWord[i-1];
    }
    num.Length++;
    num.TabWord[0] = color;

    int len = rand() % 9 + 6;
    *Pesawat = CreateQueue(len);
    for (int i = 1; i < len; i++) {
        Push(Pesawat, toKata("-"));
    }
    Push(Pesawat, num);
}

void createBandara(Queue *Bandara) {
    *Bandara = CreateQueue(10);
    for (int i = 0; i < 10; i++) {
        Push(Bandara, toKata("  -  "));
    }
}

void printLangit(Langit L) {
    ElType temp;
    for (int i = 0; i < L.NEff; i++) {
        printf("o- ");
        for (int j = 0; j < Length(L.Pesawat[i]); j++) {
            temp = Pop(&L.Pesawat[i]);
            if (IsWordEq(temp, toKata("-"))) {
                printf("  -  ");
            } else {
                if (temp.TabWord[0] == 'M') {
                    printf("\033[1;31m"); 
                } else {
                    printf("\033[1;35m");
                }
                printf("=[|=<");
                printf("\033[0m");
            }
            Push(&L.Pesawat[i], temp);
        }
        printf(" -o ");
        TulisWord(L.ID[i]);
        printf("\n\n");
    }
}

void printBandara(Queue B, char warna) {
    if (warna == 'M') {
        printf("\033[1;31m"); 
    } else{
        printf("\033[1;35m");
    }
    printf("+------------------------------------------------------+\n|                                                      |\n|  ");
    for (int i = 0; i < Length(B); i++) {
        ElType dump;
        dump = Pop(&B);
        if (IsWordEq(dump, toKata("  -  "))) {
            TulisWord(dump);
        } else {
            printf("=[|=<");
        }
        Push(&B, dump);
    }
    printf("  |\n|                                                      |\n+------------------------------------------------------+\n\n");
    printf("\033[0m");
}

void printGuide() {
    
}

void printStatus(Queue M, Queue B, Langit L) {
    printf("Bandara Merah\n");
    printBandara(M, 'M');
    printf("Bandara Biru\n");
    printBandara(B, 'B');

    printf("[ Langit ]\n\n");
    printLangit(L);
}

void insertPesawat(Langit *L, Queue Pesawat) {
    ElType temp;
    (*L).Pesawat[(*L).NEff] = Pesawat;
    for (int i = 0; i < Length(Pesawat); i++) {
        temp = Pop(&Pesawat);
        if (!IsWordEq(temp, toKata("-"))) {
            (*L).ID[(*L).NEff] = temp;
        } 
        Push(&Pesawat, temp);
    }
    (*L).NEff++;
}

void insertLanding(Queue *Bandara, TabKata *Landing) {
    if (!IsEmpty(*Landing)) {
        ElType dump;
        dump = Pop(Bandara);
        Push(Bandara, (*Landing).TK[0]);
        MakeEmpty(Landing);
    }
}

void deletePesawat(Langit *L, Queue *Bandara, Word ID) {
    ElType dump;
    boolean found = false; 
    for (int i = 0; i < (*L).NEff - 1; i++) {
        if (IsWordEq((*L).ID[i], ID)) {
            found = true;
        }
        if (found) {
            (*L).Pesawat[i] = (*L).Pesawat[i + 1];
            (*L).ID[i] = (*L).ID[i + 1];
        }
    }
    (*L).NEff--;
    dump = Pop(Bandara);
    Push(Bandara, toKata("P"));
}

void updateStatus(Queue *M, Queue *B, Langit *L, TabKata *LandingM, TabKata *LandingB) {
    ElType dump;
    dump = Pop(M);
    dump = Pop(B);
    Push(M, toKata("  -  "));
    Push(B, toKata("  -  "));

    for (int i = 0; i < (*L).NEff; i++) {
        if (!IsWordEq((*L).Pesawat[i].Tab[(*L).Pesawat[i].HEAD], toKata("-"))) {
            if ((*L).Pesawat[i].Tab[0].TabWord[0] == 'M') {
                SetEl(LandingM, (*LandingM).Neff, (*L).ID[i]);
            } else {
                SetEl(LandingB, (*LandingB).Neff, (*L).ID[i]);
            }
            for (int j = i; j < (*L).NEff - 1; j ++) {
                (*L).Pesawat[j] = (*L).Pesawat[j + 1];
                (*L).ID[j] = (*L).ID[j + 1];
            }
            (*L).NEff--;
        } else {
            dump = Pop(&L->Pesawat[i]);
        }
    }
}

void accPesawat(Langit *L, Word comm) {
    ElType dump;
    for (int i = 0; i < (*L).NEff; i++) {
        if (IsWordEq((*L).ID[i], comm)) {
            while (IsWordEq((*L).Pesawat[i].Tab[(*L).Pesawat[i].HEAD], toKata("-"))) {
                dump = Pop(&L->Pesawat[i]);
            }
        }
    }
}

boolean isCommVal(Word comm, Langit L) {
    if (IsWordEq(currentWord, toKata("SKIP"))) {
        return true;
    } else {
        for (int i = 0; i < L.NEff; i++) {
            if (IsWordEq(currentWord, L.ID[i])) {
                return true;
            }
        }
        return false;
    }
}

Word intToWord(int n) {
    Word num; num.Length = 0;
    if (n == 0) {
        num.TabWord[num.Length] = '0'; num.Length++;
    } else {
        while (n != 0) {
            for (int i = num.Length; i > 0; i--) {
                num.TabWord[i] = num.TabWord[i-1];
            }
            num.Length++;
            num.TabWord[0] = (n % 10) + '0';
            n = n / 10;
        }
    }
    return num;
}