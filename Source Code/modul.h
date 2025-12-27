#ifndef MODUL_H_INCLUDED
#define MODUL_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;

struct infotypeModul {
    string idModul;
    string judulModul;
    int durasi;
    string difficulty;  // Easy/Medium/Hard
};

typedef struct elmModul* adrModul;

struct elmModul {
    infotypeModul info;
    adrModul next;
    adrModul prev;
};

adrModul alokasiModul(string id, string judul, int durasi, string difficulty);

#endif
