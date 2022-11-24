#ifndef DICTIONARY
#define DICTIONARY

#include "boolean.h"
#include "mesinkata.h"

#define kataMax 100

typedef struct {
    Word Kata[kataMax];
    int Neff;
} Kamus;

void createEmptyKamus(Kamus *K);
/* Membuat kamus kosong
   I.S. sembarang
   F.S. kamus kosong */

void insertToKamus(Kamus *K, Word Kata);
/* Memasukkan kata ke dalam kamus secara urut
   I.S. sembarang K mungkin kosong
   F.S. Kata dimasukkan ke dalam kamus secara terurut */

void deleteKata(Kamus *K, Word Kata);
/* Menghapus kata dalam kamus 
   I.S. Kamus tidak kosong
   F.S. Kata dihapus dari kamus */

boolean isKataMember(Kamus K, Word Kata);
/* Mengembalikan nilai true apabila kata terdapat dalam kamus */

boolean isWordGreater(Word K1, Word K2);
/* Mengembalikan nilai true apabila K1 lebih besar dari K2 secara abjad */

boolean isWordLess(Word K1, Word K2);
/* Mengembalikan nilai true apabila K1 lebih kecil dari K2 secara abjad */

Word getWordMin(Kamus K);
/* Mengembalikan kata paling minimum */

#endif