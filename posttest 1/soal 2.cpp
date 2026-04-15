#include <iostream>
#include <string>
using namespace std;

struct Mahasiswa {
    string nama;
    string nim;
    float ipk;
};

int main() {
    const int N = 5;
    Mahasiswa mhs[N];

    cout << "\n  ----------------------------------------" << endl;
    cout << "  |      Data Mahasiswa - Struct Array    |" << endl;
    cout << "  ----------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "\n  Mahasiswa ke-" << i+1 << endl;
        cout << "  Nama : ";
        getline(cin, mhs[i].nama);
        cout << "  NIM  : ";
        cin >> mhs[i].nim;
        cout << "  IPK  : ";
        cin >> mhs[i].ipk;
        cin.ignore();  
}

    int idxTertinggi = 0;
    for (int i = 1; i < N; i++) {
        if (mhs[i].ipk > mhs[idxTertinggi].ipk) {
            idxTertinggi = i;
        }
    }

    cout << "--------------------------------------------" << endl;
    cout << "|          Daftar Semua Mahasiswa          |" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "|  No  | Nama        | NIM      | IPK      |"  << endl;
    cout << "|------|-------------|----------|----------|" << endl;
    for (int i = 0; i < N; i++) {
        cout << "  " << i+1 << "  | "
             << mhs[i].nama << "\t\t| "
             << mhs[i].nim  << "  | "
             << mhs[i].ipk  << endl;
    }

    cout << "-------------------------------------------" << endl;
    cout << "  |        Mahasiswa IPK Tertinggi        |" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "  Nama : " << mhs[idxTertinggi].nama << endl;
    cout << "  NIM  : " << mhs[idxTertinggi].nim  << endl;
    cout << "  IPK  : " << mhs[idxTertinggi].ipk  << endl;
    cout << "-------------------------------------------"<< endl;

    return 0;
}