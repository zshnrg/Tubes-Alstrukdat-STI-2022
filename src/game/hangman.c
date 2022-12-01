#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "hangman.h"

int playHangman() {
    srand(time(NULL));
    int score = 0, live = 10, count = 1;
    Word def = toKata("default.txt");

    Kamus K, played;
    createEmptyKamus(&K);

    readDictionary("default.txt", &K);
    clear();
    printGuideHangman();

    do {
        currentWord = toKata("START");
        do {
            printf("Selamat datang di Hangman! Gunakan command di bawah ini untuk memulai\n\n");
            printf("  START\t\t\tMemulai permainan Hangman\n  LOAD <file.txt>\tMemuat kamus baru dari file\n  SHOW DICTIONARY\tMenampilkan kata-kata yang dimuat\n  EDIT DICTIONARY\tMenambah atau menghapus kata pada kamus\n\n");
            if (!isMenuValid) printf("Menu tidak valid! Masukkan perintah lain\n");
            printf("> ");
            GetCommand();
            clear();
        } while (!isMenuValid(currentWord));
        
        if (IsWordEq(AccessCommand(currentWord, 0), toKata("LOAD"))) {
            loadKamus(&K, AccessCommand(currentWord, 1), &def);
            sleep(2);
            clear();
        } else if (IsWordEq(currentWord, toKata("SHOW DICTIONARY"))) {
            currentWord = toKata("BACK");
            do {
                printKamus(K);
                if (!IsWordEq(currentWord, toKata("BACK"))) printf("\nPerintah tidak valid.");
                printf("\nGunakan perintah BACK untuk kembali\n> ");
                GetCommand();
                clear();
            } while (!IsWordEq(currentWord, toKata("BACK")));
        } else if (IsWordEq(currentWord, toKata("EDIT DICTIONARY"))) {
            currentWord = toKata("DONE");
            do {
                printf("Gunakan perintah berikut\n\n  ADD <Kata>\t\tMenambahkan kata pada kamus\n  DELETE <Kata>\t\tMenghapus kata pada kamus\n  DONE\t\t\tSelesai mengedit kamus\n\n");
                printKamus(K);
                if (!(IsWordEq(toKata("ADD"), AccessCommand(currentWord, 0)) || IsWordEq(toKata("DELETE"), AccessCommand(currentWord, 0)) || IsWordEq(toKata("DONE"), currentWord))) {
                    printf("Perintah tidak valid! Gunakan perintah yang ada\n");
                }
                printf("\n> ");
                GetCommand();

                if (IsWordEq(toKata("ADD"), AccessCommand(currentWord, 0))) {
                    addKataToKamus(&K, AccessCommand(currentWord, 1));
                } else if (IsWordEq(toKata("DELETE"), AccessCommand(currentWord, 0))) {
                    delKataInKamus(&K, AccessCommand(currentWord, 1));
                }
                sleep(1);
                clear();
            } while (!IsWordEq(currentWord, toKata("DONE")));
        }
    } while (!IsWordEq(currentWord, toKata("START")));

    played = K;
    char save[50] = "";
    for (int i = 0; i < def.Length; i++) save[i] = def.TabWord[i];
    save[def.Length] = '\0';

    writeDictionary(save, K);

    Word Answer;
    while (live > 0 && played.Neff > 0) {
        Word Guess = toKata("");
        Answer = played.Kata[rand() % played.Neff];
        deleteKata(&played, Answer);
        do {
            boolean correct = false;
            do {
                printStatusHangman(count, live, Guess, Answer);
                printf("\n\n> Masukkan tebakan: ");
                GetCommand();
            } while (!isGuessValid(currentWord, Guess));
            addToGuess(currentWord, &Guess);
            for (int i = 0; i < Answer.Length; i++) {
                if (currentWord.TabWord[0] == Answer.TabWord[i] || currentWord.TabWord[0] - 'a' == Answer.TabWord[i] - 'A') correct = true;
            }
            if (!correct) {
                printf("\nKamu gagal menebak! Kini nyawamu berkurang\n");
                sleep(3);
                live--;
            } else {
                printf("\nBerhasil menebak satu huruf!\n");
                sleep(3);
            }
        } while (live > 0 && !isGuessed(Answer, Guess));
        if (isGuessed(Answer, Guess)) {
            printStatusHangman(count, live, Guess, Answer);
            printf("\n\nKamu berhasil menebak "); TulisWord(Answer); printf(".\nSkor kamu bertambah +%d", Answer.Length);
            score += Answer.Length;
            count++;
            sleep(3);
        }
    }

    clear();
    printf("============");
    printHangman(live);
    printf("============\n\n");
    if (played.Neff > 0) {
        printf("Permainan berakhir! Kata yang seharusnya kamu tebak adalah ");
        TulisWord(Answer);
    }
    else printf("Permainan berakhir! Semua kata dalam kamus telah kamu tebak");
    printf("\nSkor kamu: %d\n\n", score);
    sleep(3);

    return score;
}

void loadKamus(Kamus *K, Word file, Word *saveName) {
    Kamus Add;
    createEmptyKamus(&Add);

    char r[50] = "";
    for (int i = 0; i < file.Length; i++) {
        r[i] = file.TabWord[i];
    }
    r[file.Length] = '\0';

    readDictionary(r, &Add);
    
    if (Add.Neff == 0) {
        printf("Silakan coba file lain\n");
    } else {
        (*K) = Add;
        (*saveName) = file;
    }
}

boolean isGuessValid(Word Comm, Word Guess) {
    if (Comm.Length > 1) {
        printf("\nMasukan harus berupa sebuah karakter huruf!\n");
        sleep(3);
        return false;
    }
    if ((Comm.TabWord[0] - 'A' >= 0 && Comm.TabWord[0] - 'A' < 26) || (Comm.TabWord[0] - 'a' >= 0 && Comm.TabWord[0] - 'a' < 26)) {
        for (int i = 0; i < Guess.Length; i++) {
            if (Guess.TabWord[i] - 'A' == Comm.TabWord[0] - 'A' || Guess.TabWord[i] - 'A' == Comm.TabWord[0] - 'a') {
                printf("Huruf %c sudah pernah ditebak!", Comm.TabWord[0]);
                sleep(3);
                return false;
            }
        }
        return true;
    }
    printf("\nMasukan harus berupa sebuah karakter huruf, tidak boleh karakter lain!\n");
    sleep(3);
    return false;
}

boolean isGuessed(Word Answer, Word Guess) {
    int correct = 0;
    for (int i = 0; i < Answer.Length; i++) {
        for (int j = 0; j < Guess.Length; j++) {
            if (Answer.TabWord[i] == Guess.TabWord[j]) correct++;
        }
    }
    int countNonChar = 0;
    for (int i = 0; i < Answer.Length; i++) {
        if (!((Answer.TabWord[i] - 'A' >= 0 && Answer.TabWord[i] - 'A' < 26) || (Answer.TabWord[i] - 'a' >= 0 && Answer.TabWord[i] - 'a' < 26))) countNonChar++;
    }
    return correct == Answer.Length - countNonChar;
}

boolean isMenuValid(Word Comm) {
    return (IsWordEq(Comm, toKata("START"))) || (IsWordEq(Comm, toKata("SHOW DICTIONARY"))) || (IsWordEq(Comm, toKata("EDIT DICTIONARY"))) || (IsWordEq(AccessCommand(Comm, 0), toKata("LOAD")));
}

void addToGuess(Word Comm, Word *Guess) {
    if (Comm.TabWord[0] - 'A' < 26) {
        (*Guess).TabWord[(*Guess).Length] = Comm.TabWord[0];
    } else {
        (*Guess).TabWord[(*Guess).Length] = (Comm.TabWord[0] - 'a') + 'A';
    }
    (*Guess).Length++;
}

void addKataToKamus(Kamus *K, Word Kata) {
    if ((*K).Neff < 100) {
        if (isKataMember(*K, Kata)) {
            printf("Kata sudah ada dalam kamus!\n");
        } else {
            insertToKamus(K, Kata);
        }
    } else {
        printf("Kamus sudah penuh!\n");
    }
}

void delKataInKamus(Kamus *K, Word Kata) {
    if ((*K).Neff == 0) {
        printf("Kamus kosong.\n");
    } else {
        if (isKataMember(*K, Kata)) {
            deleteKata(K, Kata);
        } else {
            printf("Kata "); TulisWord(Kata); printf(" tidak ada dalam kamus.\n");
        }
    }
}

void printKamus(Kamus K) {
    if (K.Neff == 0) {
        printf("Kamus kosong.\n\n");
    } else {
        printf("Berikut adalah isi kamus\n\n");
        int MaxLen = 0;
        for (int i = 0; i < K.Neff; i++) {
            if (K.Kata[i].Length + 3 > MaxLen) MaxLen = K.Kata[i].Length + 3;
        }
        for (int i = 0; i < K.Neff; i++) {
            TulisWord(K.Kata[i]);
            if (!(i % 3 == 2)) {
                for (int j = K.Kata[i].Length; j < MaxLen; j++) printf(" ");
            } else printf("\n");
            if (i == K.Neff - 1 && !(i % 3 == 2)) printf("\n");
        }
    }
}

void printDashes(Word Guess, Word Answer) {
    for (int i = 0; i < Answer.Length; i++) {
        if (Answer.TabWord[i] - 'A' >= 0 && Answer.TabWord[i] - 'A' < 26) {
            boolean found = false;
            for (int j = 0; j < Guess.Length; j++) {
                if (Answer.TabWord[i] == Guess.TabWord[j]) {
                    printf("%c", Answer.TabWord[i]);
                    found = true;
                }
            }
            if (!found) printf("_");
        } else {
            printf("%c", Answer.TabWord[i]);
        }
        printf(" ");
    }
}

void printHangman(int stage) {
    if (stage == 10) printf("\n  \n  \n  \n  \n  \n  \n  \n  ");
    else if (stage == 9) printf("\n  \n  \n  \n  \n  \n  \n  \n  /\\");
    else if (stage == 8) printf("\n  \n  \n  |\n  |\n  |\n  |\n  |\n  /\\");
    else if (stage == 7) printf("\n   _____\n  /\n  |\n  |\n  |\n  |\n  |\n  /\\");
    else if (stage == 6) printf("\n   _____\n  /\n  |   O\n  |\n  |\n  |\n  |\n  /\\");
    else if (stage == 5) printf("\n   _____\n  /\n  |   O\n  |   |\n  |   |\n  |\n  |\n  /\\");
    else if (stage == 4) printf("\n   _____\n  /\n  |   O\n  |  /|\n  |   |\n  |\n  |\n  /\\");
    else if (stage == 3) printf("\n   _____\n  /\n  |   O\n  |  /|\\\n  |   |\n  |\n  |\n  /\\");
    else if (stage == 2) printf("\n   _____\n  /\n  |   O\n  |  /|\\\n  |   |\n  |  /\n  |\n  /\\");
    else if (stage == 1) printf("\n   _____\n  /\n  |   O\n  |  /|\\\n  |   |\n  |  / \\\n  |\n  /\\");
    else printf("\n   _____\n  /   |\n  |   O\n  |  /|\\\n  |   |\n  |  / \\\n  |\n  /\\");
    printf("\n");
}

void printGuideHangman() {
    for (int i = 8; i > 0; i--) {
        printf("\n    _______                                         \n   |   |   |.---.-.-----.-----.--------.---.-.-----.\n   |       ||  _  |     |  _  |        |  _  |     |\n   |___|___||___._|__|__|___  |__|__|__|___._|__|__|\n                        |_____|                     \n\n================= Petunjuk Permainan =================\n\n1. Permainan ini mengharuskan kamu untuk menebak kata\n   dengan menebak hurufnya satu per satu.\n2. Kamu memiliki 10 kesempatan untuk menebak huruf.\n3. Sebelum kamu bermain kamu dapat memilih kamus kata\n   yang ingin digunakan. Selain itu, kamu juga dapat\n   menambahkan/menghapus kata yang ingin dimainkan.\n\n======================================================\n\nPermainan akan dimulai dalam %d ...", i);
        sleep(1);
        clear();
    }
}

void printStatusHangman(int wordCount, int live, Word Guess, Word Answer) {
    clear();
    printf("Kata ke-%d\n============", wordCount);
    printHangman(live);
    printf("\n============\nKesempatan: %d\n\n[ ", live);
    printDashes(Guess, Answer);
    printf("]\nTebakanmu: ");
    TulisWord(Guess);
}