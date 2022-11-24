#include <stdio.h>
#include "help.h"

void help() {
    printf("=====================================[ HELP ]=====================================\n\n");
    printf("1.  SAVE <filename>\t Menyimpan list game yang dimiliki ke dalam file.\n");
    printf("2.  CREATE GAME\t\t Membuat game baru.\n");
    printf("3.  LIST GAME\t\t Menampilkan list game yang dapat dimainkan.\n");
    printf("4.  DELETE GAME\t\t Menghapus game yang ada pada list game.\n");
    printf("5.  QUEUE GAME\t\t Menambahkan game yang tersedia ke dalam antrean game.\n");
    printf("6.  PLAY GAME\t\t Memainkan game yang ada pada antrean.\n");
    printf("7.  SKIPGAME <n>\t Membuang sebangak n game pada antrean.\n");
    printf("8.  HISTORY <n> \t Menampilkan urutan permainan yang telah dimainkan.\n");
    printf("9.  RESET HISTORY <n>\t Menghapus urutan permainan yang telah dimainkan.\n");
    printf("9.  SCOREBOARD\t\t Menampilkan urutan skor tiap permainan.\n");
    printf("9.  RESET SCOREBOARD\t Menghapus urutan urutan skor permainan.\n");
    printf("10. QUIT \t\t Keluar dari BNMO.\n");
    printf("11. HELP \t\t Menambilkan list command yang tersedia.\n\n");
    printf("==================================================================================\n\n");
}