#ifndef MLL_H_INCLUDED
#define MLL_H_INCLUDED

#include "kursus.h"

struct List {
    adrKursus first;
};

void createList(List &L);
void insertFirstKursus(List &L, adrKursus P);
void insertModul(adrKursus P, adrModul C);
adrKursus searchKursus(List L, string idKursus);

void hapusKursus(List &L, string idKursus);
void hapusModul(List &L, string idKursus, string idModul);
void showAllData(List L);
int hitungJumlahModul(List L, string idKursus);
void showMinMaxModul(List L);

void clearScreen();
void pauseScreen();
void displayMenuUtama();

void showAvailableKursus(List L);
void menuKelolaKursus(List &L);
void menuHubungkanModul(List &L);
void menuCariKursus(List L);
void menuTampilkanModulPerKursus(List L);
void menuTampilkanData(List L);
void menuHitungModul(List L);
void menuLaporanStatistik(List L);

void menuHapusModul(List &L);

#endif
