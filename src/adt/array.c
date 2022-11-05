// Implementasi modul array.h

#include <stdio.h>
#include <stdlib.h>
#include "array.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong */
void MakeEmpty (TabKata *T) {
/* I.S. sembarang */
/* F.S. Terbentuk tabel T kosong dengan kapasitas IdxMax-IdxMin+1 */
	// KAMUS
	// ALGORITMA
	(*T).Neff = 0;
}

/* ********** SELEKTOR ********** */
/* *** Banyaknya elemen *** */
int NbElmt (TabKata T) {
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */
/* *** Daya tampung container *** */
	// KAMUS
	// ALGORITMA
	return T.Neff;
}

int MaxNbEl (TabKata T) {
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */
	// KAMUS
	// ALGORITMA
	return IdxMax - IdxMin;
}

/* *** Selektor INDEKS *** */
IdxType GetFirstIdx (TabKata T) {
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen pertama */
	// KAMUS
	// ALGORITMA
	return IdxMin;
}

IdxType GetLastIdx (TabKata T) {
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen terakhir */
	// KAMUS
	// ALGORITMA
	return NbElmt(T) - 1;
}

/* *** Menghasilkan sebuah elemen *** */
ElType GetElmt (TabKata T, IdxType i) {
/* Prekondisi : Tabel tidak kosong, i antara FirstIdx(T)..LastIdx(T) */
/* Mengirimkan elemen tabel yang ke-i */
	// KAMUS
	// ALGORITMA
	return T.TK[i];
}

/* *** Selektor SET : Mengubah nilai TABEL dan elemen tabel *** */
/* Untuk type private/limited private pada bahasa tertentu */
void SetTab (TabKata Tin, TabKata *Tout) {
/* I.S. Tin terdefinisi, sembarang */
/* F.S. Tout berisi salinan Tin */
/* Assignment THsl -> Tin */
	// KAMUS
	IdxType i;
	// ALGORITMA
	for (i = 1; i <= NbElmt(Tin); i++) {
		SetEl(Tout, i, GetElmt(Tin,i));
	}
	SetNeff(Tout,NbElmt(Tin));
}

void SetEl (TabKata *T, IdxType i, ElType v) {
/* I.S. T terdefinisi, sembarang */
/* F.S. Elemen T yang ke-i bernilai v */
/* Mengeset nilai elemen tabel yang ke-i sehingga bernilai v */
	// KAMUS
	// ALGORITMA
	(*T).TK[i] = v;
	if (i > GetLastIdx(*T)) {
		(*T).Neff++;
	}
}

void SetNeff (TabKata *T, IdxType N) {
/* I.S. T terdefinisi, sembarang */
/* F.S. Nilai indeks efektif T bernilai N */
/* Mengeset nilai indeks elemen efektif sehingga bernilai N */
	// KAMUS
	// ALGORITMA
	(*T).Neff = N;
}


/* ********** Test Indeks yang valid ********** */
boolean IsIdxValid (TabKata T, IdxType i) {
/* Prekondisi : i sembarang */
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/
	// KAMUS
	// ALGORITMA
	return (i >= IdxMin && i <= IdxMax); 
}

boolean IsIdxEff (TabKata T, IdxType i) {
/* Prekondisi : i sembarang*/
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */
	// KAMUS
	// ALGORITMA
	return (i >= GetFirstIdx(T) && i <= GetLastIdx(T));
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean IsEmpty (TabKata T) {
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
/* *** Test tabel penuh *** */
	// KAMUS
	// ALGORITMA
	return NbElmt(T) == 0;
}

boolean IsFull (TabKata T) {
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */
	// KAMUS
	// ALGORITMA
	return NbElmt(T) == (IdxMax - IdxMin);
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
void TulisIsi (TabKata T) {
/* Proses : Menuliskan isi tabel dengan traversal */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong : indeks dan elemen tabel ditulis berderet ke bawah */
/* Jika isi tabel [1,2,3] maka akan diprint
0:1
1:2
2:3
*/
/* Jika T kosong : Hanya menulis "Tabel kosong" */
	// KAMUS
	IdxType i;
	// ALGORITMA
	if (!IsEmpty(T)) {
		for (i = GetFirstIdx(T); i < NbElmt(T); i++) {
			printf("  %d. ", i + 1);
			TulisWord(T.TK[i]);
			printf("\n");
		}
	} else {
		printf("Tabel kosong\n");
	}
}

boolean IsMember (TabKata T, ElType v) {
	for (int i = 0; i < T.Neff; i++) {
		if (IsWordEq(T.TK[i], v)) {
			return true;
		}
	}
	return false;
}