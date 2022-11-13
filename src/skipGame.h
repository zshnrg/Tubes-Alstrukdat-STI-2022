#ifndef SKIP_GAME_H
#define SKIP_GAME_H

#include <stdio.h>
#include "./adt/queue.h"
#include "./adt/mesinkata.h"

void skipGame (Queue* queueGame, Word command);
/* Melewatkan permainan sebanyak n
I.S. queueGame terdefinisi, mungkin kosong
F.S. Memainkan game pada Top queueGame sekarang
*/

#endif