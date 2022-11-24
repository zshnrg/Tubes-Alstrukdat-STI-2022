#ifndef DICTIONARY_READER
#define DICTIONARY_READER

#include <stdio.h>
#include "../adt/dictionary.h"

void readDictionary(char* filesrc, Kamus *K);
/* Membaca file .txt dan menyimpan isinya ke dalam kamus kata
   I.S. Kamus mungkin kosong tapi tidak penuh
   F.S. Isi kamus berasal dari file .txt */

#endif