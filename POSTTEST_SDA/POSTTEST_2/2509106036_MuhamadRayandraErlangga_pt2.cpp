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

void jumpSearchNomor(Kereta* arr, int n, int x) {
    int step = 2; 
    int prev = 0;
    cout << "\n--- Proses Jump Search Nomor " << x << " ---\n";
    
    while (arr[min(step, n) - 1].nomor < x) {
        cout << "Iterasi: Lompat ke indeks " << min(step, n) - 1 << " (Nomor: " << arr[min(step, n) - 1].nomor << ")\n";
        prev = step;
        step += 2;
        if (prev >= n) {
            cout << "Hasil: Nomor tidak ditemukan.\n";
            return;
        }
    }

    while (arr[prev].nomor < x) {
        cout << "Iterasi: Pengecekan linear di indeks " << prev << " (Nomor: " << arr[prev].nomor << ")\n";
        prev++;
        if (prev == min(step, n)) {
            cout << "Hasil: Nomor tidak ditemukan.\n";
            return;
        }
    }

    if (arr[prev].nomor == x) {
        cout << "Iterasi: BERHASIL!\n";
        cetakHeader();
        cetakBarisKereta(arr + prev);
        cetakFooter();
    } else {
        cout << "Hasil: Nomor tidak ditemukan.\n";
    }
}

void merge(Kereta* arr, int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    Kereta L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].nama <= R[j].nama) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSortNama(Kereta* arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortNama(arr, l, m);
        mergeSortNama(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void selectionSortHarga(Kereta* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if ((arr + j)->harga < (arr + minIdx)->harga) minIdx = j;
        }
        swap(&arr[minIdx], &arr[i]);
    }
    cout << "\nData berhasil diurutkan berdasarkan harga termurah.\n";
}

void sortNomorInternal(Kereta* arr, int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j].nomor > arr[j+1].nomor) swap(&arr[j], &arr[j+1]);
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
        cout << "\n0. Keluar";
        cout << "\nPilihan Menu: ";
        cin >> pilihan;
        
        switch (pilihan) {
            case 1:
                tampilkanJadwal(daftarKereta, jumlahKereta); break;
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
                string a, t; cin.ignore();
                cout << "Asal: "; getline(cin, a);
                cout << "Tujuan: "; getline(cin, t);
                linearSearchRute(daftarKereta, jumlahKereta, a, t);
                break;
            }
            case 4: {
                int no;
                sortNomorInternal(daftarKereta, jumlahKereta);
                cout << "Cari Nomor: "; cin >> no;
                jumpSearchNomor(daftarKereta, jumlahKereta, no);
                break;
            }
            case 5: 
                mergeSortNama(daftarKereta, 0, jumlahKereta - 1);
                cout << "\nData berhasil diurutkan berdasarkan nama (A-Z).\n";
                break;
            case 6:
                selectionSortHarga(daftarKereta, jumlahKereta);
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