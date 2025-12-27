#include <iostream>
#include "mll.h"

using namespace std;

int main(){

    List L;
    createList(L);

    // data dummy
    adrKursus k3 = alokasiKursus("K03", "Basis_Data");
    insertFirstKursus(L, k3);
    insertModul(k3, alokasiModul("M-BD-01", "ERD_Concept", 55, "Medium"));
    insertModul(k3, alokasiModul("M-BD-02", "SQL_Query", 95, "Hard"));

    adrKursus k2 = alokasiKursus("K02", "Algoritma_Dasar");
    insertFirstKursus(L, k2);
    insertModul(k2, alokasiModul("M-ALG-1", "Flowchart", 40, "Easy"));
    insertModul(k2, alokasiModul("M-ALG-2", "Looping", 60, "Medium"));
    insertModul(k2, alokasiModul("M-ALG-3", "Array", 70, "Medium"));

    adrKursus k1 = alokasiKursus("K01", "Struktur_Data");
    insertFirstKursus(L, k1);

    string pil = "";

    while (pil != "0") {
        displayMenuUtama();
        cin >> pil;

        if (pil == "1") {
            menuKelolaKursus(L);
        } else if (pil == "2") {
            menuHubungkanModul(L);
        } else if (pil == "3") {
            menuCariKursus(L);
        } else if (pil == "4") {
            menuTampilkanModulPerKursus(L);
        } else if (pil == "5") {
            menuTampilkanData(L);
        } else if (pil == "6") {
            menuHitungModul(L);
        } else if (pil == "7") {
            menuLaporanStatistik(L);
        } else if (pil == "8") {
            menuHapusModul(L);
        } else if (pil == "0") {
            cout << "Terima kasih sudah menggunakan program kami..." << endl;
        } else {
            cout << "Maaf, tidak ada pilihan itu" << endl;
            pauseScreen();
        }
    }
    return 0;
}
