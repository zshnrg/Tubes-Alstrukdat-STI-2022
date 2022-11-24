#ifndef HANGMAN
#define HANGMAN

#include <stdio.h>
#include "../adt/dictionary.h"
#include "../driver/readDictionary.h"
#include "../driver/writeDictionary.h"

int playHangman();
/* Memulai game Hangman dan mengembalikan nilai skor */


void loadKamus(Kamus *K, Word file, Word *saveName);
/* Membaca kamus yang dipilih 
   I.S. Kamus sembarang dan file
   F.S. Kamus berisi kata pada file txt, jika file txt tidak ditemukan maka
        akan mengirimkan pesan gagal */

boolean isGuessValid(Word Comm, Word Guess);
/* Mengembalikan nilai true apabila masukan merupakan sebuah huruf */

boolean isGuessed(Word Answer, Word Guess);

boolean isMenuValid(Word Comm);
/* Mengembalikan nilai true apabila menu perintah valid */

void addToGuess(Word Comm, Word *Guess);
/* Menambahkan huruf yang ditebak ke daftar huruf yang sudah ditebak */

void addKataToKamus(Kamus *K, Word Kata);
/* Memasukkan kata ke dalam kamus
   I.S. sembarang
   F.S. Jika kata belum ada di dalam kamus dan kamus belum penuh,
        kata akan ditambahkan */

void delKataInKamus(Kamus *K, Word Kata);
/* Menghapus kata dalam kamus
   I.S. sembarang
   F.S. Jika kata ada dalam kamus, maka kata akan dihapuskan */

void printKamus(Kamus K);
/* Mencetak kamus yang sedang dimainkan
   I.S. Kamus tidak kosong
   F.S. Kamus ditampilkan di layar */

void printDashes(Word Guess, Word Answer);
/* Mencetak kolom tebakan
   I.S. Answer tidak kosong
   F.S. Kolom tebakan ditampilkan ke layar. Apabila huruf belum ditebak, maka 
        akan dicetak garis bawah */

void printHangman(int stage);
/* Mencetak hangman tergantung pada batas kesempatan
   I.S. stage bilangan bulat [0..10]
   F.S. hangman ditampilkan ke layar sesuai dengan kesempatan yang tersedia */

void printGuideHangman();
/* Menampilkan petunjuk permainan
   I.S. sembarang
   F.S. petunjuk permainan ditampilkan ke layar */

void printStatusHangman(int wordCount, int live, Word Guess, Word Answer);
/* Menampilkan status permainan
   I.S. sembarang
   F.S. status permainan ditampilkan ke layar */

#endif