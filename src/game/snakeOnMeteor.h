#ifndef SNAKE_ON_METEOR
#define SNAKE_ON_METEOR

#include <stdio.h>
#include "../adt/listlinier.h"
#include "../adt/mesinkata.h"

#define MapSize 5

int playSnakeOnMeteor();
/* Memainkan game Snake on Meteor dan mengembalikan skor game */

void generateSnake(List *Snake);
/* Membuat snake dengan panjang 2 badan
   I.S. sembarang
   F.S. snake berhasil digenerate */

Point generateFood(List Snake, Point Obstacle1, Point Obstacle2, Point Meteor, Point Crater);
/* Membuat makanan di luar tubuh snake */

Point generateMeteor(Point Obstacle1, Point Obstacle2, Point Food);
/* Membuat meteor sembarang */

Point generateObstacle(List Snake);
/* Membuat obstacle random */

void growSnake(List* Snake);
/* Menumbukan badan snake
   I.S. sembarang
   F.S. panjang tubuh snake bertambah
        - Secara umum bertambah pada absis sebelum tail
        - jika tidak bisa bertambah pada ordinat sebelum tail
        - jika tidak bisa bertambah pada ordinat setelah tail */

void moveSnake(List *Snake, Word comm);
/* Mengubah posisi snake
   I.S. sembarang, command pasti valid
   F.S. posisi snake berubah */

boolean isCollide(List Snake, Point Obstacle1, Point Obstacle2);
/* Mengembalikan nilai true apabila ular menabrak obstacle atau badannya sendiri */

boolean isMeteorHit(List *Snake, Point Meteor);
/* Mengembalikan nilai true jika meteor mengenai kepala ular
   Jika meteor mengenai badan, maka badan akan berkurang 1 */

boolean isCmdValid(Word comm);
/* Mengembalikan nilai true apabila command valid */

boolean isMoveValid(Word comm, List Snake, Point Crater, boolean silent);
/* Mengembalikan nilai true apabila ular bisa bergerak (tidak menabrak bekas meteor) */

void printMap(List Snake, Point Obs1, Point Obs2, Point Food, Point Meteor, Point Crater);
/* Menampilkan status peta permainan ke layar
   I.S. sembarang
   F.S. Peta ditampilkan ke layar */

void printGuideSoM();
/* Mencetak panduan permainan
   I.S. sembarang
   F.S. Panduan tercetak pada layar */

#endif