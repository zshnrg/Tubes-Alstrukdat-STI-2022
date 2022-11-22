#ifndef PLAY_GAME_H
#define PLAY_GAME_H

#include <stdio.h>
#include "./adt/queue.h"
#include "./adt/stack.h"

/* List game buatan */
#include "./game/rng.h"
#include "./game/dinerDash.h"
#include "./game/atcGame.h"
#include "./game/towerOfHanoi.h"
#include "./game/snakeOnMeteor.h"

void printLoading(Word gameName);
/* Menampilkan ke layar proses loading game */

void playGame(Queue* queueGame, Stack* historyGame);
/* Memainkan game yang ada pada defaultGame
I.S. queueGame terdefinisi, mungkin kosong
F.S. Game teratas dimainkan
*/

#endif