#include <stdio.h>
#include "help.h"

void help() {
    printf("=====================================[ HELP ]=====================================\n\n");
    printf("1.  LOAD <filename>\t Membaca file yang berisikan list game.\n");
    printf("2.  SAVE <filename>\t Menyimpan list game yang dimiliki ke dalam file.\n");
    printf("3.  CREATE GAME\t\t Membuat game baru.\n");
    printf("4.  LIST GAME\t\t Menampilkan list game yang dapat dimainkan.\n");
    printf("5.  DELETE GAME\t\t Menghapus game yang ada pada list game.\n");
    printf("6.  QUEUE GAME\t\t Menambahkan game yang tersedia ke dalam antrean game.\n");
    printf("7.  PLAY GAME\t\t Memainkan game yang ada pada antrean.\n");
    printf("8.  SKIPGAME <n>\t Membuang sebangak n game pada antrean.\n");
    printf("9.  QUIT \t\t Keluar dari BNMO.\n");
    printf("10. HELP \t\t Menambilkan list command yang tersedia.\n\n");
    printf("==================================================================================\n\n");
}