#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct Kereta {
    int nomor;
    string nama;
    string asal;
    string tujuan;
    int harga;
};

struct Tiket {
    string namaPenumpang;
    Kereta dataKereta;
    Tiket* next;
};

Tiket* front = NULL;
Tiket* rear = NULL;
Tiket* top = NULL;

void swap(Kereta* a, Kereta* b) {
    Kereta temp = *a;
    *a = *b;
    *b = temp;
}

void cetakHeader() {
    cout << "\n+---------+--------------------+-----------------+-----------------+------------+" << endl;
    cout << "| " << left << setw(8)  << "NOMOR" 
         << "| " << setw(19) << "NAMA KERETA" 
         << "| " << setw(16) << "ASAL" 
         << "| " << setw(16) << "TUJUAN" 
         << "| " << setw(10) << "HARGA" << " |" << endl;
    cout << "+---------+--------------------+-----------------+-----------------+------------+" << endl;
}

void cetakBarisKereta(Kereta* k) {
    cout << "| " << left << setw(8)  << k->nomor 
         << "| " << setw(19) << k->nama 
         << "| " << setw(16) << k->asal 
         << "| " << setw(16) << k->tujuan 
         << "| " << right << setw(10) << k->harga << " |" << endl;
}

void cetakFooter() {
    cout << "+---------+--------------------+-----------------+-----------------+------------+" << endl;
}

void tampilkanJadwal(Kereta* arr, int n) {
    if (n == 0) {
        cout << "\n[Peringatan] Belum ada data kereta.\n";
        return;
    }
    cetakHeader();
    for (int i = 0; i < n; i++) {
        cetakBarisKereta(arr + i);
    }
    cetakFooter();
}

void linearSearchRute(Kereta* arr, int n, string asal, string tujuan) {
    bool found = false;
    bool headerPrinted = false;
    for (int i = 0; i < n; i++) {
        if ((arr + i)->asal == asal && (arr + i)->tujuan == tujuan) {
            if (!headerPrinted) {
                cout << "\n--- Hasil Pencarian Rute " << asal << " ke " << tujuan << " ---";
                cetakHeader();
                headerPrinted = true;
            }
            cetakBarisKereta(arr + i);
            found = true;
        }
    }
    if (found) cetakFooter();
    else cout << "\n[Hasil] Jadwal rute tersebut tidak ditemukan.\n";
}

void enqueue(Tiket t) {
    Tiket* baru = new Tiket;
    *baru = t;
    baru->next = NULL;

    if (front == NULL) {
        front = rear = baru;
    } else {
        rear->next = baru;
        rear = baru;
    }

    cout << "[Sukses] " << t.namaPenumpang << " masuk ke antrean.\n";
}

void dequeue() {
    if (front == NULL) {
        cout << "[Error] Antrean Kosong!\n";
    } else {
        Tiket* diproses = front;

        cout << "\n[Proses Tiket] Penumpang: " << diproses->namaPenumpang;
        cout << " | Rute: " << diproses->dataKereta.asal << " -> " << diproses->dataKereta.tujuan << endl;

        Tiket* baru = new Tiket;
        *baru = *diproses;
        baru->next = top;
        top = baru;

        front = front->next;
        delete diproses;

        if (front == NULL) rear = NULL;
    }
}

void popRiwayat() {
    if (top == NULL) {
        cout << "[Error] Riwayat Kosong!\n";
    } else {
        cout << "[Batal] Transaksi terakhir atas nama " << top->namaPenumpang << " dihapus.\n";
        Tiket* hapus = top;
        top = top->next;
        delete hapus;
    }
}

void peek() {
    cout << "\n--- PEEK DATA ---" << endl;

    if (front != NULL)
        cout << "Depan Antrean: " << front->namaPenumpang << endl;
    else
        cout << "Depan Antrean: (Kosong)" << endl;

    if (top != NULL)
        cout << "Riwayat Terakhir: " << top->namaPenumpang << endl;
    else
        cout << "Riwayat Terakhir: (Kosong)" << endl;
}

void tampilSemuaAntrean() {
    if (front == NULL) { cout << "\n[Info] Antrean kosong.\n"; return; }
    cout << "\n--- SEMUA ANTREAN ---" << endl;

    Tiket* p = front;
    while (p != NULL) {
        cout << "- " << p->namaPenumpang << " [" << p->dataKereta.nama << "]" << endl;
        p = p->next;
    }
}

void tampilSemuaRiwayat() {
    if (top == NULL) { cout << "\n[Info] Riwayat kosong.\n"; return; }
    cout << "\n--- SEMUA RIWAYAT ---" << endl;

    Tiket* p = top;
    int i = 1;
    while (p != NULL) {
        cout << i + 1 << ". " << p->namaPenumpang << " | " << p->dataKereta.nama << endl;
        p = p->next;
    }
}

int main() {
    int maxData = 100;
    Kereta* daftarKereta = new Kereta[maxData]; 
    int jumlahKereta = 10;

    daftarKereta[0] = {105, "Gajayana", "Malang", "Jakarta", 600000};
    daftarKereta[1] = {101, "Argo Bromo", "Jakarta", "Surabaya", 500000};
    daftarKereta[2] = {102, "Bengawan", "Solo", "Jakarta", 74000};
    daftarKereta[3] = {110, "Majapahit", "Malang", "Jakarta", 250000};
    daftarKereta[4] = {108, "Bima", "Surabaya", "Jakarta", 550000};
    daftarKereta[5] = {103, "Serayu", "Purwokerto", "Jakarta", 67000};
    daftarKereta[6] = {107, "Taksaka", "Yogyakarta", "Jakarta", 450000};
    daftarKereta[7] = {104, "Lodaya", "Bandung", "Solo", 230000};
    daftarKereta[8] = {109, "Turangga", "Surabaya", "Bandung", 480000};
    daftarKereta[9] = {106, "Matarmaja", "Malang", "Jakarta", 150000};

    int pilihan;
    do {
        cout << "\n======================================";
        cout << "\n   SISTEM MANAJEMEN KERETA API";
        cout << "\n======================================";
        cout << "\n1. Tampilkan Semua Jadwal";
        cout << "\n2. Tambah Data Kereta Baru";
        cout << "\n3. Cari Berdasarkan Rute (Linear)";
        cout << "\n4. Cari Berdasarkan Nomor (Jump)";
        cout << "\n5. Urutkan Nama A-Z (Merge Sort)";
        cout << "\n6. Urutkan Harga Termurah (Selection)";
        cout << "\n7. Masuk Antrean Beli Tiket (Enqueue)";
        cout << "\n8. Proses Tiket Terdepan (Dequeue)";
        cout << "\n9. Tampilkan Semua Antrean (Queue)";
        cout << "\n10. Tampilkan Semua Riwayat (Stack)";
        cout << "\n11. Batalkan Transaksi Terakhir (Pop)";
        cout << "\n12. Tampilkan antrian terdepan & riwayat terakhir (Peek)";
        cout << "\n0. Keluar";
        cout << "\nPilihan Menu: ";
        cin >> pilihan;
        
        switch (pilihan) {
            case 1:
                tampilkanJadwal(daftarKereta, jumlahKereta);
                break;
            case 2:
                cout << "Nomor: "; cin >> (daftarKereta + jumlahKereta)->nomor;
                cin.ignore();
                cout << "Nama: "; getline(cin, (daftarKereta + jumlahKereta)->nama);
                cout << "Asal: "; getline(cin, (daftarKereta + jumlahKereta)->asal);
                cout << "Tujuan: "; getline(cin, (daftarKereta + jumlahKereta)->tujuan);
                cout << "Harga: "; cin >> (daftarKereta + jumlahKereta)->harga;
                jumlahKereta++;
                break;
            case 3: {
                string a, t;
                cin.ignore();
                cout << "Asal: "; getline(cin, a);
                cout << "Tujuan: "; getline(cin, t);
                linearSearchRute(daftarKereta, jumlahKereta, a, t);
                break;
            }
            case 7: {
                string np; int nk;
                cout << "Nama Penumpang: "; cin.ignore(); getline(cin, np);
                cout << "Pilih Nomor Kereta: "; cin >> nk;
                bool found = false;
                for(int i=0; i<jumlahKereta; i++) {
                    if(daftarKereta[i].nomor == nk) {
                        Tiket t = {np, daftarKereta[i], NULL};
                        enqueue(t); found = true; break;
                    }
                }
                if(!found) cout << "[Error] Nomor kereta tidak valid!\n";
                break;
            }
            case 8:
                dequeue();
                break;
            case 9:
                tampilSemuaAntrean();
                break;
            case 10:
                tampilSemuaRiwayat();
                break;
            case 11:
                popRiwayat();
                break;
            case 12:
                peek();
                break;
            case 0:
                cout << "\nProgram selesai. Sampai jumpa!\n";
                break;
            default:
                cout << "\nPilihan tidak valid!\n";
                break;
        }
    } while (pilihan != 0);

    delete[] daftarKereta;
    return 0;
}