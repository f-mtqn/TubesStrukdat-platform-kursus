#include "modul.h"

//I.S.: Parameter id, judul, durasi, dan difficulty terdefinisi sebagai data input.
//F.S.: Mengembalikan pointer (address) ke elemen modul baru yang telah dialokasi di memori.
//      Field info terisi, sedangkan pointer next dan prev diinisialisasi nullptr.
adrModul alokasiModul(string id, string judul, int durasi, string difficulty) {
    adrModul p = new elmModul;
    p->info.idModul = id;
    p->info.judulModul = judul;
    p->info.durasi = durasi;
    p->info.difficulty = difficulty;
    p->next = nullptr;
    p->prev = nullptr;
    return p;
}
