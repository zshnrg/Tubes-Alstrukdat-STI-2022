#ifndef DINER_DASH_H
#define DINER_DASH_H

#include "../adt/mesinkata.h"

typedef struct {
    int ID;
    int Durasi;
    int Ketahanan;
    int Harga;
} Makanan;

typedef struct {
    Makanan List[NMax];
    int NEff;
} ListMakanan;

void dinerDashPlay();
/* Menjalankan game Diner DASH 
   I.S. sembarang
   F.S. Diner DASH selesai dijalankan */

void createEmpty(ListMakanan *l);
/* I.S. sembarang */
/* F.S. Terbentuk list makanan L kosong dengan kapasitas NMax */

Makanan createMakanan(int Id);
/* Membuat entri makanan random
   I.S. Id terdefinisi
   F.S. Makanan dibuat dengan ID sesuai parameter */

void insertMakanan(ListMakanan *l, Makanan v);
/* Memasukkan makanan ke dalam List Makanan
   I.S. l terdefinisi
   F.S. v merupakan anggota dari l */

void removeMakanan(ListMakanan *l, int Idx);
/* Membuang elemen ke Idx pada l
   I.S. Idx valid
   F.S. Elemen dengan id Idx dihapus dan elemen digeser ke kiri */

int getFoodId(Word comm);
/* Mengembalikan integer pada command ID */

Makanan getFood(ListMakanan l, int Idx);
/* Mengembalikan elemen Makanana pada List Makanan l, Idx pasti valid */

int idMinMakanan(ListMakanan pesanan);
/* Mengembalikan nilai ID minimum pada List Makanan pesanan */

boolean isKosong(ListMakanan l);
/* Bernilai true apabila l kosong */

boolean isCommandValid(Word comm, ListMakanan pesanan, ListMakanan dimasak, ListMakanan ready);
/* Bernilai true appabila command valid */

boolean isMember(ListMakanan l, int Idx);
/* Bernilai true apabila makanan dengan ID = Idx ada pada l */

void cook(ListMakanan* dimasak, Makanan v);
/* Menambahkan elemen v ke dalam List Makanan dimasak
   I.S. dimasak terdefinisi mungkin kosong
   F.S. v elemen dari dimasak */

void updateCooking(ListMakanan *dimasak, ListMakanan *ready);
/* Menghapus elemen pada list makanan apabila sudah selesai
   I.S. dimakan dan ready terdefinisi
   F.S. elemen Makanan yang selesai dimasak dipindah ke ready.
        Makanan yang hangus dikeluarkan dari ready */

Makanan serve(ListMakanan *pesanan, ListMakanan *ready);
/* Menyajikan makanan pada ready dan menghapus pada antrean pesanan.
   Mengembalikan hasil makanan yang diantarkan */

void cetakPesanan(ListMakanan pesanan);
/* Mencetak tabel pesanan pada layar
   I.S. list pesanan terdefinisi mungkin kosong
   F.S. tabel pesanan ditampilkan di layar */

void cetakDimasak(ListMakanan dimasak);
/* Mencetak tabel dimasak pada layar
   I.S. list dimasak terdefinisi mungkin kosong
   F.S. tabel dimasak ditampilkan di layar */

void cetakMakananReady(ListMakanan ready);
/* Mencetak tabel ready pada layar
   I.S. list ready terdefinisi mungkin kosong
   F.S. tabel ready ditampilkan di layar */

#endif