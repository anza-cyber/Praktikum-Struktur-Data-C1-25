#include <iostream>
#include <iomanip>
using namespace std;

void reverseArray(int* arr, int n) {

    int* kiri  = arr;
    int* kanan = arr + (n - 1);

    while (kiri < kanan) {
        int temp = *kiri;
        *kiri    = *kanan;
        *kanan   = temp;
        kiri++;
        kanan--;
    }
}

int main() {

    int prima[] = {2, 3, 5, 7, 11, 13, 17};
    int n = 7;

    cout << "\n  ----------------------------------------" << endl;
    cout << "  |   ARRAY & POINTER - BILANGAN PRIMA   |" << endl;
    cout << "  ----------------------------------------" << endl;

    cout << "\n  Sebelum dibalik:" << endl;
    cout << "  +-------+--------+---------------+" << endl;
    cout << "  | Index | Nilai  | Alamat        |" << endl;
    cout << "  +-------+--------+---------------+" << endl;

    for (int i = 0; i < n; i++) {
        cout << "  | arr+" << i << "  |  "
             << setw(5) << left << *(prima + i)
             << " | " << (prima + i) << "  |" << endl;
    }
    
    cout << "  +-------+--------+---------------+" << endl;

    cout << "\n  Urutan: ";
    for (int i = 0; i < n; i++) {
        cout << *(prima + i);
        if (i < n-1) cout << " -> ";
    }
    cout << endl;

    reverseArray(prima, n);

    cout << "\n  Sesudah dibalik:" << endl;
    cout << "  +-------+--------+---------------+" << endl;
    cout << "  | Index | Nilai  | Alamat        |" << endl;
    cout << "  +-------+--------+---------------+" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  | arr+" << i << "  |  "
             << setw(5) << left << *(prima + i)
             << " | " << (prima + i) << "  |" << endl;
    }
    cout << "  +-------+--------+---------------+" << endl;

    cout << "\n  Urutan: ";
    for (int i = 0; i < n; i++) {
        cout << *(prima + i);
        if (i < n-1) cout << " -> ";
    }
    cout << endl;

    cout << "\n  ----------------------------------------" << endl;
    cout << "  Info memori:" << endl;
    cout << "  Alamat awal  : " << prima                        << endl;
    cout << "  Alamat akhir : " << (prima + n - 1)              << endl;
    cout << "  Ukuran int   : " << sizeof(int) << " bytes"      << endl;
    cout << "  Total pakai  : " << sizeof(int)*n << " bytes"    << endl;
    cout << "  ----------------------------------------\n"      << endl;

    return 0;
}