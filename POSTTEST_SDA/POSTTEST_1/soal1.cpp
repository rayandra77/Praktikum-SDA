#include <iostream>
using namespace std;

/*
ANALISIS KOMPLEKSITAS WAKTU - FindMin (Return Indeks)

Perhitungan Operasi:
1. min = 0                     : 1 kali
2. inisialisasi i = 1          : 1 kali
3. pengecekan i < n            : n kali
4. perbandingan A[i] < A[min]  : (n-1) kali
5. increment i (i++)           : (n-1) kali
6. update min = i              : 0 (best) / (n-1) (worst)
7. return min                  : 1 kali

Worst Case:
Terjadi jika array dalam keadaan menurun,
sehingga kondisi selalu true.

T(n) = 1 + 1 + n + (n-1) + (n-1) + (n-1) + 1
T(n) = 3 + n + 3(n-1)
T(n) = 3 + n + 3n - 3
T(n) = 4n

Worst Case = O(n)

Best Case:
Terjadi jika elemen pertama sudah paling kecil,
sehingga tidak pernah update min.

T(n) = 1 + 1 + n + (n-1) + (n-1) + 1
T(n) = 3 + n + 2(n-1)
T(n) = 3 + n + 2n - 2
T(n) = 3n + 1

Best Case = O(n)

KESIMPULAN:
Kompleksitas waktu algoritma bersifat linear,
karena jumlah operasi bertambah sebanding dengan n.

Best Case  = O(n)
Worst Case = O(n)
*/

int FindMin(int A[], int n) {

    int min = 0;

    for (int i = 1; i < n; i++) {
        if (A[i] < A[min]) {
            min = i;
        }
    }

    return min;
}

int main() {

    int A[8] = {1, 1, 2, 3, 5, 8, 13, 21};

    int indeks = FindMin(A, 8);

    cout << "Nilai minimum = " << A[indeks] << endl;
    cout << "Indeks minimum = " << indeks << endl;

    return 0;
}