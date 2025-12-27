#include "mll.h"

//I.S.: Variabel L bertipe List sembarang (belum terinisialisasi).
//F.S.: Terbentuk list kosong. L.first bernilai nullptr.
void createList(List &L) {
    L.first = nullptr;
}

//I.S.: List L terdefinisi (mungkin kosong), P adalah pointer kursus yang sudah dialokasi dan valid.
//F.S.: Elemen P ditambahkan sebagai elemen pertama (head) pada List L. Next dari P tersambung ke elemen pertama sebelumnya (jika ada).
void insertFirstKursus(List &L, adrKursus P) {
    if (L.first == nullptr) {
        L.first = P;
    } else {
        P->next = L.first;
        L.first = P;
    }
}

//I.S.: P adalah pointer ke parent (Kursus) yang valid, C adalah pointer ke child (Modul) yang sudah dialokasi.
//F.S.: Elemen C ditambahkan ke dalam list child milik P pada posisi terakhir (Insert Last).
void insertModul(adrKursus P, adrModul C) {
    if (P->firstModul == nullptr) {
        P->firstModul = C;
    } else {
        adrModul Q = P->firstModul;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = C;
        C->prev = Q;
    }
}

//I.S.: List L terdefinisi, idKursus berisi string ID yang dicari.
//F.S.: Mengembalikan alamat elemen (pointer) jika idKursus ditemukan dalam List L, atau mengembalikan nullptr jika tidak ditemukan.
adrKursus searchKursus(List L, string idKursus) {
    adrKursus P = L.first;
    adrKursus found = nullptr;
    while (P != nullptr && found == nullptr) {
        if (P->info.idKursus == idKursus) {
            found = P;
        } else {
            P = P->next;
        }
    }
    return found;
}

//I.S.: List L terdefinisi, idKursus adalah ID dari kursus yang ingin dihapus.
//F.S.: Jika ditemukan, node kursus beserta seluruh modul (child) di dalamnya dihapus dari List L dan memori didealokasi.
//      Jika tidak ditemukan, list tetap dan pesan error tampil.
void hapusKursus(List &L, string idKursus) {
    adrKursus P = L.first;
    adrKursus prevP = nullptr;
    bool found = false;

    while (P != nullptr && !found) {
        if (P->info.idKursus == idKursus) {
            found = true;
        } else {
            prevP = P;
            P = P->next;
        }
    }

    if (found) {
        adrModul M = P->firstModul;
        while (M != nullptr) {
            adrModul hapus = M;
            M = M->next;
            hapus = nullptr;
        }
        P->firstModul = nullptr;

        if (P == L.first) {
            L.first = P->next;
        } else {
            prevP->next = P->next;
        }

        P = nullptr;
        cout << ">> SUKSES: Kursus dihapus." << endl;
    } else {
        cout << ">> ERROR: Kursus tidak ditemukan." << endl;
    }
    pauseScreen();
}

//I.S.: List L terdefinisi, idKursus dan idModul terdefinisi sebagai target penghapusan.
//F.S.: Jika kursus dan modul ditemukan, node modul dihapus dari list child milik kursus tersebut dan memori didealokasi.
//      Relasi list child (prev/next) diperbarui.
void hapusModul(List &L, string idKursus, string idModul) {
    adrKursus P = searchKursus(L, idKursus);
    if (P != nullptr) {
        adrModul M = P->firstModul;
        bool found = false;
        while (M != nullptr && !found) {
            if (M->info.idModul == idModul){
                found = true;
            } else {
                M = M->next;
            }
        }
        if (found) {
            if (M == P->firstModul) {
                P->firstModul = M->next;
                if (P->firstModul != nullptr){
                        P->firstModul->prev = nullptr;
                }
            } else if (M->next == nullptr) {
                M->prev->next = nullptr;
            } else {
                M->prev->next = M->next;
                M->next->prev = M->prev;
            }
            M = nullptr;
            cout << ">> SUKSES: Modul dihapus." << endl;
        } else {
            cout << ">> ERROR: Modul tidak ditemukan." << endl;
        }
    } else {
        cout << ">> ERROR: Kursus tidak ditemukan." << endl;
    }
    pauseScreen();
}

//I.S.: List L terdefinisi (bisa kosong atau berisi data).
//F.S.: Seluruh data kursus beserta detail modul-modulnya ditampilkan ke layar (output standar). State List L tidak berubah.
void showAllData(List L) {
    adrKursus P = L.first;
    if (P == nullptr) {
        cout << " [!] Data masih kosong." << endl;
    } else {
        while (P != nullptr) {
            cout << " [" << P->info.idKursus << "] " << P->info.namaKursus << endl;
            adrModul M = P->firstModul;
            if (M == nullptr) {
                cout << "     (Belum ada modul)" << endl;
            }
            while (M != nullptr) {
                cout << "     > " << M->info.idModul << " - " << M->info.judulModul;
                if (M->info.durasi > 60) {
                    cout << " (" << M->info.durasi / 60 << "j " << M->info.durasi % 60 << "m)";
                } else {
                    cout << " (" << M->info.durasi << "m)";
                }
                cout << " [" << M->info.difficulty << "]" << endl;
                M = M->next;
            }
            cout << " --------------------------------------" << endl;
            P = P->next;
        }
    }
}

//I.S.: List L terdefinisi, idKursus terdefinisi.
//F.S.: Mengembalikan nilai integer yang menyatakan jumlah modul yang dimiliki oleh kursus dengan idKursus.
//      Mengembalikan 0 jika kursus tidak ditemukan atau tidak memiliki modul.
int hitungJumlahModul(List L, string idKursus) {
    adrKursus P = searchKursus(L, idKursus);
    int count = 0;
    if (P != nullptr) {
        adrModul M = P->firstModul;
        while (M != nullptr) {
            count++;
            M = M->next;
        }
    }
    return count;
}

//I.S.: List L terdefinisi dan tidak kosong.
//F.S.: Menampilkan ke layar id kursus dan nama kursus dengan jumlah modul terbanyak dan yang paling sedikit.
void showMinMaxModul(List L) {
    if (L.first == nullptr) {
        cout << " [!] Data kosong, tidak ada statistik." << endl;
    } else {
        adrKursus P = L.first;
        adrKursus maxP = P;
        adrKursus minP = P;
        int maxCount = hitungJumlahModul(L, P->info.idKursus);
        int minCount = maxCount;

        P = P->next;
        while (P != nullptr) {
            int c = hitungJumlahModul(L, P->info.idKursus);

            if (c > maxCount) {
                maxCount = c;
                maxP = P;
            }
            if (c < minCount) {
                minCount = c;
                minP = P;
            }
            P = P->next;
        }

        cout << "========================================" << endl;
        cout << "           LAPORAN STATISTIK            " << endl;
        cout << "========================================" << endl;
        cout << " Modul Terbanyak: " << endl;
        cout << "  - Kursus : [" << maxP->info.idKursus << "] " << maxP->info.namaKursus << endl;
        cout << "  - Jumlah : " << maxCount << " Modul" << endl;
        cout << "----------------------------------------" << endl;
        cout << " Modul Tersedikit: " << endl;
        cout << "  - Kursus : [" << minP->info.idKursus << "] " << minP->info.namaKursus << endl;
        cout << "  - Jumlah : " << minCount << " Modul" << endl;
        cout << "========================================" << endl;
    }
}

//I.S.: Sembarang.
//F.S.: Layar output dibersihkan (mencetak baris baru).
void clearScreen() {
    cout << string(5, '\n');
}

//I.S.: Sembarang.
//F.S.: Program berhenti sejenak menunggu input sembarang dari user untuk melanjutkan eksekusi.
void pauseScreen() {
    string d;
    cout << "\nKetik apapun lalu Enter... ";
    cin >> d;
}

// I.S.: Sembarang.
// F.S.: Menampilkan pilihan menu utama.
void displayMenuUtama() {
    clearScreen();
    cout << "========================================" << endl;
    cout << "       PLATFORM KURSUS ONLINE (MLL)     " << endl;
    cout << "========================================" << endl;
    cout << " [1] Tambah/Hapus Kursus               " << endl;
    cout << " [2] Hubungkan Modul ke Kursus         " << endl;
    cout << " [3] Cari Kursus (Berdasarkan ID)      " << endl;
    cout << " [4] Tampilkan Modul Per Kursus        " << endl;
    cout << " [5] Tampilkan Semua Data              " << endl;
    cout << " [6] Hitung Jumlah Modul               " << endl;
    cout << " [7] Laporan Statistik (Min/Max)       " << endl;
    cout << " [8] Hapus Modul dari Kursus           " << endl;
    cout << " [0] Keluar                            " << endl;
    cout << "========================================" << endl;
    cout << " Pilih Menu > ";
}

//I.S.: List L terdefinisi.
//F.S.: Menampilkan submenu kelola kursus. Jika user memilih tambah/hapus, List L berubah sesuai operasi yang dilakukan.
void menuKelolaKursus(List &L) {
    string pil;
    clearScreen();
    cout << "========================================" << endl;
    cout << "             KELOLA KURSUS              " << endl;
    cout << "========================================" << endl;
    cout << " [1] Tambah Kursus Baru                " << endl;
    cout << " [2] Hapus Kursus                      " << endl;
    cout << " [0] Kembali                           " << endl;
    cout << "----------------------------------------" << endl;
    cout << " Pilih Menu > ";
    cin >> pil;

    if (pil == "1") {
        string id, nama;
        cout << "\n--- Input Data Kursus ---" << endl;
        cout << " ID Kursus   : ";
        cin >> id;
        cout << " Nama Kursus : ";
        cin >> nama;
        insertFirstKursus(L, alokasiKursus(id, nama));
        cout << "\n>> SUKSES: Kursus berhasil ditambahkan." << endl;
        pauseScreen();
    } else if (pil == "2") {
        string id;
        clearScreen();
        cout << "--- Daftar Kursus Saat Ini ---" << endl;
        showAllData(L);
        cout << "\n Masukkan ID Kursus yang akan dihapus: ";
        cin >> id;
        hapusKursus(L, id);
    }
}

//I.S.: List L terdefinisi.
//F.S.: Menampilkan submenu kelola modul. Jika user memilih tambah/hapus, list child di dalam elemen L berubah sesuai operasi.
void menuKelolaModul(List &L) {
    string pil;
    clearScreen();
    showAllData(L);
    cout << "========================================" << endl;
    cout << "              KELOLA MODUL              " << endl;
    cout << "========================================" << endl;
    cout << " [1] Tambah Modul ke Kursus            " << endl;
    cout << " [2] Hapus Modul dari Kursus           " << endl;
    cout << " [0] Kembali                           " << endl;
    cout << "----------------------------------------" << endl;
    cout << " Pilih Menu > ";
    cin >> pil;

    if (pil == "1") {
        string idK, idM, jdl, diff;
        int dur;
        cout << "\n--- Input Data Modul ---" << endl;
        cout << " ID Kursus Target : ";
        cin >> idK;
        adrKursus P = searchKursus(L, idK);
        if (P) {
            cout << " ID Modul         : ";
            cin >> idM;
            cout << " Judul Modul      : ";
            cin >> jdl;
            cout << " Durasi (menit)   : ";
            cin >> dur;
            cout << " Kesulitan (Easy/Medium/Hard): ";
            cin >> diff;

            if (diff == "Easy" || diff == "easy" || diff == "Medium" || diff == "medium" || diff == "Hard" || diff == "hard") {
                insertModul(P, alokasiModul(idM, jdl, dur, diff));
                cout << "\n>> SUKSES: Modul berhasil ditambahkan ke " << P->info.namaKursus << "." << endl;
            } else {
                cout << "\n>> GAGAL: Tingkat kesulitan tidak valid." << endl;
            }
        } else {
            cout << "\n>> GAGAL: Kursus dengan ID " << idK << " tidak ditemukan." << endl;
        }
        pauseScreen();
    } else if (pil == "2") {
        string idK, idM;
        cout << "\n--- Hapus Modul ---" << endl;
        cout << " ID Kursus : ";
        cin >> idK;
        cout << " ID Modul  : ";
        cin >> idM;
        hapusModul(L, idK, idM);
    }
}

//I.S.: List L terdefinisi.
//F.S.: Menampilkan seluruh data L ke layar lalu melakukan pause. List L tidak berubah.
void menuTampilkanData(List L) {
    clearScreen();
    showAllData(L);
    pauseScreen();
}

//I.S.: List L terdefinisi.
//F.S.: Menampilkan laporan statistik (min/max) ke layar lalu melakukan pause. List L tidak berubah.
void menuLaporanStatistik(List L) {
    clearScreen();
    showMinMaxModul(L);
    pauseScreen();
}

// I.S.: List L terdefinisi.
// F.S.: Menampilkan seluruh ID dan Nama kursus yang tersedia tanpa modulnya.
void showAvailableKursus(List L) {
    adrKursus P = L.first;
    if (P == nullptr) {
        cout << " [!] Data kursus kosong." << endl;
    } else {
        while (P != nullptr) {
            cout << " [" << P->info.idKursus << "] " << P->info.namaKursus << endl;
            P = P->next;
        }
    }
}

// I.S.: List L terdefinisi.
// F.S.: Menampilkan semua kursus, meminta input nama, lalu menampilkan data kursus jika nama sesuai.
void menuCariKursus(List L) {
    string id;
    clearScreen();
    showAvailableKursus(L);

    cout << "\nMasukkan ID Kursus: ";
    cin >> id;

    adrKursus P = searchKursus(L, id);

    if (P != nullptr) {
        cout << "\n[ Data Ditemukan ]" << endl;
        cout << "ID Kursus   : " << P->info.idKursus << endl;
        cout << "Nama Kursus : " << P->info.namaKursus << endl;
    } else {
        cout << "\n[!] ID Kursus tidak ditemukan." << endl;
    }
    pauseScreen();
}

// I.S.: List L terdefinisi.
// F.S.: Menampilkan ID dan Nama kursus, meminta input data modul baru dan ID kursus target, lalu menghubungkannya.
void menuHubungkanModul(List &L) {
    string idK, idM, jdl, diff;
    int dur;
    clearScreen();
    cout << "--- Tambahkan Modul ---" << endl;
    showAvailableKursus(L);

    cout << "\n[ Input Data Modul Baru ]" << endl;
    cout << "ID Modul  : ";
    cin >> idM;
    cout << "Judul     : ";
    cin >> jdl;
    cout << "Durasi    : ";
    cin >> dur;
    cout << "Diff (Easy/Medium/Hard): ";
    cin >> diff;

    cout << "\nMasukkan ID Kursus untuk disambungkan: ";
    cin >> idK;

    adrKursus P = searchKursus(L, idK);
    if (P != nullptr) {
        insertModul(P, alokasiModul(idM, jdl, dur, diff));
        cout << "\n>> SUKSES: Modul berhasil dihubungkan ke " << P->info.namaKursus << "." << endl;
    } else {
        cout << "\n>> GAGAL: ID Kursus tidak ditemukan." << endl;
    }
    pauseScreen();
}

// I.S.: List L terdefinisi.
// F.S.: Menampilkan daftar ID dan Nama kursus, meminta input ID, lalu menampilkan detail modul khusus kursus tersebut.
void menuTampilkanModulPerKursus(List L) {
    string id;
    clearScreen();
    cout << "--- Cari Kursus untuk Ditampilkan ---" << endl;
    showAvailableKursus(L);
    cout << "\nMasukkan ID Kursus: ";
    cin >> id;

    adrKursus P = searchKursus(L, id);
    if (P != nullptr) {
        cout << "\nDetail Kursus: [" << P->info.idKursus << "] " << P->info.namaKursus << endl;
        adrModul M = P->firstModul;
        if (M == nullptr) {
            cout << " (Belum ada modul)" << endl;
        } else {
            while (M != nullptr) {
                cout << "  > " << M->info.idModul << " - " << M->info.judulModul << " (" << M->info.durasi << "m)" << endl;
                M = M->next;
            }
        }
    } else {
        cout << "\n[!] ID Kursus tidak ditemukan." << endl;
    }
    pauseScreen();
}

// I.S.: List L terdefinisi.
// F.S.: Menampilkan daftar kursus, meminta input ID, dan menampilkan jumlah modul di kursus tersebut.
void menuHitungModul(List L) {
    string id;
    clearScreen();
    cout << "--- Hitung Jumlah Modul ---" << endl;
    showAvailableKursus(L);
    cout << "\nMasukkan ID Kursus: ";
    cin >> id;

    int jumlah = hitungJumlahModul(L, id);
    adrKursus P = searchKursus(L, id);

    if (P != nullptr) {
        cout << "\nKursus: " << P->info.namaKursus << endl;
        cout << "Jumlah Modul: " << jumlah << endl;
    } else {
        cout << "\n[!] ID Kursus tidak ditemukan." << endl;
    }
    pauseScreen();
}

// I.S.: List L terdefinisi.
// F.S.: Menampilkan daftar kursus dan modul, meminta input ID, lalu menghapus modul dari list jika ditemukan.
void menuHapusModul(List &L) {
    string idK, idM;
    clearScreen();
    cout << "========================================" << endl;
    cout << "           HAPUS MODUL KURSUS           " << endl;
    cout << "========================================" << endl;

    showAvailableKursus(L);

    if (L.first != nullptr) {
        cout << "\n Masukkan ID Kursus Target : ";
        cin >> idK;

        adrKursus P = searchKursus(L, idK);

        if (P != nullptr) {
            cout << " Daftar Modul di " << P->info.namaKursus << ":" << endl;
            adrModul M = P->firstModul;
            if (M == nullptr) {
                cout << "  (Kursus ini belum memiliki modul)" << endl;
            } else {
                while (M != nullptr) {
                    cout << "  - " << M->info.idModul << " (" << M->info.judulModul << ")" << endl;
                    M = M->next;
                }
                cout << "\n Masukkan ID Modul yang akan dihapus: ";
                cin >> idM;

                hapusModul(L, idK, idM);
            }
        } else {
            cout << "\n>> ERROR: ID Kursus tidak ditemukan." << endl;
            pauseScreen();
        }
    } else {
        pauseScreen();
    }
}

