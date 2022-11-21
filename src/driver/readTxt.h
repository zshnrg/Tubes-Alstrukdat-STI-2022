#ifndef READ_FILE_TXT
#define READ_FILE_TXT


/* MODUL .txt file reader */
#include "../adt/mesinkata.h"
#include "../adt/array.h"
#include "../adt/listlinier.h"

void readTxt(char* filesrc, TabKata* listGame, List* historyGame);
/* Membaca file .txt dan menyimpan isinya ke dalam array of Word
I.S. listGame terdefinisi mungkin kosong tetapi tidak penuh
F.S. Isi listGame bertambah dari isi file .txt
*/

#endif