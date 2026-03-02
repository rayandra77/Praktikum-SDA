#include <iostream>
using namespace std;

struct mahasiswa {
    string nama;
    string nim;
    float ipk;

};

int main () {
    const int n = 5;
    mahasiswa mhs[n];

    cout << "Masukkan data mahasiswa:" << endl;

    for (int i = 0; i < n; i++) {
        cout << "\nMahasiswa ke-" << i + 1 << endl;
        cout << "Nama : ";
        getline(cin, mhs[i].nama);
        cout << "NIM  : ";
        cin >> mhs[i].nim;
        cout << "IPK  : ";
        cin >> mhs[i].ipk;
        cin.ignore();
    }

    int indeks_tertinggi = 0;
    for (int i = 1; i < n; i++) {
        if (mhs[i].ipk > mhs[indeks_tertinggi].ipk) {
            indeks_tertinggi = i;
        }
    }

    cout << "\nMahasiswa dengan IPK tertinggi:" << endl;
    cout << "Nama : " << mhs[indeks_tertinggi].nama << endl;
    cout << "NIM  : " << mhs[indeks_tertinggi].nim << endl;
    cout << "IPK  : " << mhs[indeks_tertinggi].ipk << endl;

    return 0;
}