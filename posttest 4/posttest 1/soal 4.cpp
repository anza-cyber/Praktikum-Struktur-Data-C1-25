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

void tampilArray(int* arr, int n) {
    int* ptr = arr;
    cout << "  +-------+--------+-------------+" << endl;
    cout << "  | Index | Nilai  | Alamat       |" << endl;
    cout << "  +-------+--------+-------------+" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  | [" << i << "]   | "
             << setw(6) << left << *ptr
             << " | " << ptr << " |" << endl;
        ptr++;
    }
    cout << "  +-------+--------+-------------+" << endl;
}

int main() {
    int prima[] = {2, 3, 5, 7, 11, 13, 17};
    int n = 7;

    cout << "\n  ============================================" << endl;
    cout << "    ARRAY & POINTER - Bilangan Prima          " << endl;
    cout << "  ============================================" << endl;

    cout << "\n  Sebelum dibalik:" << endl;
    tampilArray(prima, n);

    cout << "\n  Urutan: ";
    int* p = prima;
    for (int i = 0; i < n; i++) {
        cout << *p;
        if (i < n - 1) cout << " -> ";
        p++;
    }
    cout << endl;

    reverseArray(prima, n);

    cout << "\n  Sesudah dibalik:" << endl;
    tampilArray(prima, n);

    cout << "\n  Urutan: ";
    p = prima;
    for (int i = 0; i < n; i++) {
        cout << *p;
        if (i < n - 1) cout << " -> ";
        p++;
    }
    cout << endl;

    cout << "\n  ============================================" << endl;
    cout << "  Info Pointer:" << endl;
    cout << "  --------------------------------------------" << endl;
    cout << "  Alamat prima[0] : " << prima               << endl;
    cout << "  Alamat prima[1] : " << (prima + 1)         << endl;
    cout << "  Alamat prima[6] : " << (prima + 6)         << endl;
    cout << "  Ukuran int      : " << sizeof(int) << " bytes" << endl;
    cout << "  Total memori    : " << sizeof(int)*n << " bytes" << endl;
    cout << "  ============================================\n" << endl;

    return 0;
}