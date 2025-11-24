# Sistem Manajemen Kursus & Modul
## Multi Linked-List Implementation in C++

Program ini mengimplementasikan struktur data Multi Linked-List (MLL) untuk mengelola kursus dan modul pembelajaran.

## Struktur Data

### Model MLL-00
- **List Parent (Kursus)**: Singly Linked List
- **List Child (Modul)**: Doubly Linked List
- **Relasi**: 1-to-N (satu kursus memiliki banyak modul)

## Fitur Program

### 1. Tambah Kursus Baru
Menambahkan kursus baru dengan nama kursus dan instruktur.

### 2. Tambah Modul Baru
Menambahkan modul baru ke dalam kursus yang sudah ada.

### 3. Cari Kursus
Mencari kursus berdasarkan nama dan menampilkan informasinya.

### 4. Hubungkan Modul ke Kursus
Membuat dan menghubungkan modul baru ke kursus tertentu.

### 5. Tampilkan Modul dari Kursus
Menampilkan semua modul yang ada dalam kursus tertentu.

### 6. Hapus Kursus (Cascade)
Menghapus kursus beserta semua modul yang ada di dalamnya.

### 7. Hapus Modul dari Kursus
Menghapus modul tertentu dari sebuah kursus.

### 8. Tampilkan Semua Kursus & Modul
Menampilkan daftar lengkap semua kursus beserta modul-modulnya.

### 9. Hitung Jumlah Modul dalam Kursus
Menghitung dan menampilkan jumlah modul dalam kursus tertentu.

### 10. Tampilkan Kursus Terbanyak/Tersedikit
Menampilkan kursus yang memiliki modul paling banyak dan paling sedikit.

## Struktur File

- `modul.h` & `modul.cpp` - ADT untuk Modul (Doubly Linked List)
- `kursus.h` & `kursus.cpp` - ADT untuk Kursus (Singly Linked List)
- `mll.h` & `mll.cpp` - Operasi Multi Linked-List
- `main.cpp` - Program utama dengan menu interaktif

## Contoh Penggunaan

1. Pilih menu **1** untuk menambah kursus baru
2. Masukkan nama kursus dan instruktur
3. Pilih menu **2** atau **4** untuk menambahkan modul ke kursus
4. Pilih menu **8** untuk melihat semua kursus dan modulnya

## Aturan Teknis

✅ Menggunakan ADT dengan file header (.h) dan implementasi (.cpp) terpisah
✅ Tidak menggunakan `break` atau `return` di dalam loop
✅ Semua fungsi menggunakan parameter (tidak ada variabel global)
✅ Modul menggunakan Doubly Linked List (pointer prev dan next)
✅ Kursus menggunakan Singly Linked List (pointer next saja)
✅ Pointer relasi langsung di dalam elemen Parent (MLL-00)

## Author
- Farabi Arafat Muttaqien
- Raissa Putri Athaya
