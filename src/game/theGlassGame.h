#ifndef THE_GLASS_GAME
#define THE_GLASS_GAME

#include <stdio.h>
#include "../adt/boolean.h"
#include "../adt/bintree.h"
#include "../adt/mesinkata.h"

int playTheGlassGame();
/* Memainkan permainan The Glass Game dan mengembalikan nilai skor */

void generateGlass(BinTree *Glass, int n);
/* Membuat rangkaian lantai kaca
   I.S. Tree kosong
   F.S. Tree berisi path random dengan kedalaman n */

void printCharacter(Word leftOrRight, boolean isCracked);
/* Mencetak tampilan karakter ke layar
   I.S. sembarang
   F.S. Karakter ditampilkan ke layar */

#endif