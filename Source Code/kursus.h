#ifndef KURSUS_H_INCLUDED
#define KURSUS_H_INCLUDED

#include "modul.h"

struct infotypeKursus {
    string idKursus;
    string namaKursus;
};

typedef struct elmKursus* adrKursus;

struct elmKursus {
    infotypeKursus info;
    adrKursus next;
    adrModul firstModul;
};

adrKursus alokasiKursus(string id, string nama);

#endif
