#include <stdio.h>
#include "dictionary.h"

void createEmptyKamus(Kamus *K) {
    (*K).Neff = 0;
}

void insertToKamus(Kamus *K, Word Kata) {
    if ((*K).Neff < 100) {
        (*K).Kata[(*K).Neff] = Kata;
        (*K).Neff++;
    }
    Kamus New; createEmptyKamus(&New);
    while ((*K).Neff != 0) {
        Word min = getWordMin(*K);
        deleteKata(K, min);
        (New).Kata[(New).Neff] = min;
        (New).Neff++;
    }
    (*K) = New;
}

void deleteKata(Kamus *K, Word Kata) {
    boolean found;
    for (int i = 0; i < (*K).Neff - 1; i++) {
        if (IsWordEq((*K).Kata[i], Kata)) {
            found = true;
        }
        if (found) {
            (*K).Kata[i] = (*K).Kata[i + 1];
        }
    }
    (*K).Neff--;
}

boolean isKataMember(Kamus K, Word Kata) {
    for (int i = 0; i < K.Neff; i++) {
        if (IsWordEq(K.Kata[i], Kata)) return true;
    }
    return false;
}

boolean isWordGreater(Word K1, Word K2) {
    int lMin = K1.Length;
    if (K1.Length > K2.Length) lMin = K2.Length;
    for (int i = 0; i < lMin; i++) {
        if (K1.TabWord[i] > K2.TabWord[i]) return true;
        else if (K1.TabWord[i] < K2.TabWord[i]) return false;
    }
    if (K1.Length > K2.Length) return true;
    else return false;
}

boolean isWordLess(Word K1, Word K2) {
    int lMin = K1.Length;
    if (K1.Length > K2.Length) lMin = K2.Length;
    for (int i = 0; i < lMin; i++) {
        if (K1.TabWord[i] < K2.TabWord[i]) return true;
        else if (K1.TabWord[i] > K2.TabWord[i]) return false;
    }
    if (K1.Length < K2.Length) return true;
    else return false;
}

Word getWordMin(Kamus K) {
    Word min = K.Kata[0];
    for (int i = 0; i < K.Neff; i++) {
        if (isWordLess(K.Kata[i], min)) min = K.Kata[i]; 
    }
    return min;
}