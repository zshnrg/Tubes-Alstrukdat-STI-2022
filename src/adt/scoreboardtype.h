#ifndef SCOREBOARD_ADT
#define SCOREBOARD_ADT

#include <stdio.h>
#include "set.h"
#include "map.h"
#include "boolean.h"

typedef struct {
    Set Nama;
    Map Score;
} Scoreboard;

int getValFromIdx(Scoreboard SB, int Idx);
/* Mengembalikan nilai value pada Map */

void sortSet(Scoreboard *SB);
/* Mengurutkan Set berdasarkan value pada Map 
   I.S. sembarang 
   F.S. isi Set terurut berdasarkan Map */



#endif