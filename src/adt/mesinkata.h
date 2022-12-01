/* File: mesinkata.h */
/* Definisi Mesin Kata: Model Akuisisi Versi I */

#ifndef __MESINKATA_H__
#define __MESINKATA_H__

#include <stdio.h>
#include "boolean.h"
#include "mesinkarakter.h"

#define NMax 50
#define BLANK '\n'
#define Separator ' '

typedef struct
{
   char TabWord[NMax]; /* container penyimpan kata, indeks yang dipakai [0..NMax-1] */
   int Length;
} Word;

/* State Mesin Kata */
extern boolean EndWord;
extern Word currentWord;

void IgnoreBlanks();
/* Mengabaikan satu atau beberapa BLANK
   I.S. : currentChar sembarang
   F.S. : currentChar ≠ BLANK atau currentChar = MARK */

void STARTWORD(FILE* input);
/* I.S. : currentChar sembarang
   F.S. : EndWord = true, dan currentChar = MARK;
          atau EndWord = false, currentWord adalah kata yang sudah diakuisisi,
          currentChar karakter pertama sesudah karakter terakhir kata */

void ADVWORD();
/* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi
   F.S. : currentWord adalah kata terakhir yang sudah diakuisisi,
          currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika currentChar = MARK, EndWord = true.
   Proses : Akuisisi kata menggunakan procedure SalinWord */

void CopyWord();
/* Mengakuisisi kata, menyimpan dalam currentWord
   I.S. : currentChar adalah karakter pertama dari kata
   F.S. : currentWord berisi kata yang sudah diakuisisi;
          currentChar = BLANK atau currentChar = MARK;
          currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */

boolean isEndWord();

void GetCommand();

Word AccessCommand(Word comm, int Idx);

void TulisWord(Word kata);

boolean IsWordEq (Word kata1, Word kata2);

boolean IsWordNumber (Word kata);

Word toKata(char *str); 
/*  Fungsi yang menerima sebuah paramater str bertipe string
    Kemudian mengembalikan elemen bertipe Word yang merupakan hasil transformasi string str */

Word intToWord(int n);

int stringLength(char *str);
/*  Fungsi yang menerima sebuah parameter str bertipe string
    Kemudian mengembalikan panjang dari string tersebut */

#endif
