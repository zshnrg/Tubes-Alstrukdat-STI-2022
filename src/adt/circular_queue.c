// Implementasi modul circular_queue.h

#include <stdio.h>
#include <stdlib.h>
#include "circular_queue.h"
#include "boolean.h"

/* ********* Prototype ********* */
boolean IsEmptyQ (Queue Q)
/* Mengirim true jika Q kosong: lihat definisi di atas */
{
    return (Q.HEAD == NIL) && (Q.TAIL == NIL);
}

boolean IsFullQ (Queue Q)
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
{
    return Length(Q) == MaxLength(Q);
}

int Length (Queue Q)
/* Mengirimkan banyaknya elemen Q, 0 jika kosong */
{
    if (IsEmptyQ(Q)) {
        return 0;
    } else {
        return (Q.TAIL - Q.HEAD + Q.MaxEl) % Q.MaxEl + 1;
    }
}

int MaxLength (Queue Q)
/* Mengirimkan kapasitas jumlah elemen Q */
{
    return Q.MaxEl;
}

/* *** Kreator *** */
Queue CreateQueue (int Max)
/* Proses : Melakukan alokasi memori, membuat sebuah Q kosong */
/* I.S. sembarang */
/* F.S. mengembalikan Q kosong dengan kondisi sbb: */
/*   Jika alokasi berhasil, Tab dialokasi berukuran Max */
/*   Jika alokasi gagal, Q kosong dengan MaxEl=0 */
{
    Queue Q;
    Q.Tab = (ElType*) malloc (Max * sizeof(ElType));
    if (Q.Tab != NULL) {
        Q.MaxEl = Max;
        Q.HEAD = NIL;
        Q.TAIL = NIL;
    } else {
        Q.MaxEl = 0;
    }
    return Q;
}

/* *** Destruktor *** */
void DeleteQueue (Queue * Q)
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. membebaskan memori Tab, Q.MaxEl di-set 0 */
{
    free((*Q).Tab);
    (*Q).MaxEl = 0;
}


/* *** Primitif Add/Delete *** */
void Push (Queue * Q, ElType X)
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru,
        TAIL "maju" dengan mekanisme circular buffer
        Jika Q kosong, HEAD dimulai dari 0 */
{
    if (IsEmptyQ(*Q)) {
        (*Q).HEAD = 0;
        (*Q).TAIL = 0;
    } else {
        (*Q).TAIL = ((*Q).TAIL + 1) % (*Q).MaxEl;
    }
    (*Q).Tab[(*Q).TAIL] = X;
}

ElType Pop (Queue * Q)
/* Proses: Menghapus indeks HEAD pada Q dengan aturan FIFO, lalu mengembalikan nilainya */
/* I.S. Q tidak mungkin kosong */
/* F.S. mengembalikan nilai Q pada indeks HEAD;
        HEAD "maju" dengan mekanisme circular buffer;
        Q mungkin kosong */
{
    ElType Head = Front(*Q);
    if (Length(*Q) == 1) {
        (*Q).HEAD = NIL;
        (*Q).TAIL = NIL;
    } else {
    (*Q).HEAD = ((*Q).HEAD + 1) % (*Q).MaxEl;
    }
    return Head;
}

ElType Front (Queue Q)
/* Proses: Mengembalikan nilai Q pada indeks HEAD tanpa penghapusan */
/* I.S. Q tidak mungkin kosong */
/* F.S. mengembalikan nilai Q pada indeks HEAD;
        Q pasti tetap tidak kosong */
{
    return (Q).Tab[(Q).HEAD];
}

void displayQueue(Queue Q)

{
    int count = 1;
    if (!IsEmptyQ(Q)) {
        int i = Q.HEAD;
        while (i != Q.TAIL) {
            printf("  %d. ", count);
            TulisWord(Q.Tab[i]);
            printf("\n");
            i = (i + 1) % Q.MaxEl;
            count++;
        }
        printf("  %d. ", count);
        TulisWord(Q.Tab[i]);
        printf("\n");
    } else {
        printf("  -\n");
    }
}

boolean IsMemberQ (Queue Q, ElType v) {
    ElType temp;
    if (!IsEmptyQ(Q)) {
        for (int i = 0; i < Length(Q); i++) {
            temp = Pop(&Q);
            if (IsWordEq(temp, v)) {
                return true;
            }
            Push(&Q, temp);
        }
    }
    return false;
}