#ifndef SKIP_GAME_H
#define SKIP_GAME_H

#include <stdio.h>
#include "./adt/array.h"
#include "./adt/queue.h"
#include "./adt/mesinkata.h"
#include "./adt/stack.h"
#include "./adt/scoreboardtype.h"

void skipGame (TabKata listGame, Queue* queueGame, Stack* historyGame, Scoreboard *SB, Word command);
/* Melewatkan permainan sebanyak n
I.S. queueGame terdefinisi, mungkin kosong
F.S. Memainkan game pada Top queueGame sekarang
*/

#endif