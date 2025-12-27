#include "kursus.h"

//I.S.: Parameter id dan nama terdefinisi sebagai data input.
//F.S.: Mengembalikan pointer (address) ke elemen kursus baru yang telah dialokasi di memori.
//      Field info terisi, sedangkan pointer next dan firstModul diinisialisasi nullptr.
adrKursus alokasiKursus(string id, string nama) {
    adrKursus p = new elmKursus;
    p->info.idKursus = id;
    p->info.namaKursus = nama;
    p->next = nullptr;
    p->firstModul = nullptr;
    return p;
}
