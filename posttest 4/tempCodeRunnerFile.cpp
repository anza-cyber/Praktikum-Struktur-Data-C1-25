#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

string formatHarga(double harga) {
    long long angka = (long long)harga;
    string s       = to_string(angka);
    string hasil   = "";
    int count      = 0;
    for (int i = (int)s.size() - 1; i >= 0; i--) {
        if (count > 0 && count % 3 == 0) hasil = "." + hasil;
        hasil = s[i] + hasil;
        count++;
    }
    return "Rp " + hasil;
}

struct Kereta {
    int    nomorKereta;
    string namaKereta;
    string asal;
    string tujuan;
    string jamBerangkat;
    double hargaTiket;
};

struct NodePenumpang {
    string         nama;
    int            nomorKereta;
    NodePenumpang* next;  
};

struct NodeTransaksi {
    string         namaPenumpang;
    string         namaKereta;
    string         rute;
    double         harga;
    NodeTransaksi* next;   
};

const int MAX_KERETA = 50;
Kereta daftarKereta[MAX_KERETA];
int    jumlahKereta = 0;

NodePenumpang* qHead = nullptr;   
NodePenumpang* qTail = nullptr;   

bool queueKosong() {
    return qHead == nullptr;
}

void enqueue(const string& nama, int nomorKereta) {
    NodePenumpang* baru = new NodePenumpang;
    baru->nama         = nama;
    baru->nomorKereta  = nomorKereta;
    baru->next         = nullptr;

    if (queueKosong()) {
        qHead = qTail = baru;
    } else {
        qTail->next = baru;
        qTail       = baru;
    }
    cout << "  >> " << nama << " berhasil masuk antrian.\n";
}

NodePenumpang dequeue() {
    NodePenumpang kosong = {"", -1, nullptr};
    if (queueKosong()) {
        cout << "  [!] Queue underflow: antrian kosong.\n";
        return kosong;
    }
    NodePenumpang data = *qHead;   
    NodePenumpang* hapus = qHead;
    qHead = qHead->next;
    if (qHead == nullptr) qTail = nullptr;
    delete hapus;
    return data;
}

void peekQueue() {
    if (queueKosong()) {
        cout << "  [!] Antrian kosong.\n";
        return;
    }

    NodePenumpang* p = qHead;
    cout << "  Penumpang terdepan : " << p->nama
         << "  (Kereta no. " << p->nomorKereta << ")\n";
}

void tampilQueue() {
    if (queueKosong()) {
        cout << "  [!] Antrian kosong.\n";
        return;
    }
    cout << "\n+-----+----------------------+------------+\n";
    cout << "| No  | Nama Penumpang       | No. Kereta |\n";
    cout << "+-----+----------------------+------------+\n";
    int urut = 1;
    NodePenumpang* cur = qHead;
    while (cur != nullptr) {
        cout << "| " << left << setw(4)  << urut
             << "| " << left << setw(21) << cur->nama
             << "| " << left << setw(11) << cur->nomorKereta << "|\n";
        cur = cur->next;
        urut++;
    }
    cout << "+-----+----------------------+------------+\n";
}

NodeTransaksi* sTop = nullptr;   

bool stackKosong() {
    return sTop == nullptr;
}

void push(NodeTransaksi* t) {
    t->next = sTop;
    sTop    = t;
    cout << "  >> Transaksi " << t->namaPenumpang << " disimpan ke riwayat.\n";
}

void pop() {
    if (stackKosong()) {
        cout << "  [!] Stack underflow: riwayat kosong.\n";
        return;
    }
    NodeTransaksi* hapus = sTop;
    cout << "  >> Transaksi dibatalkan: "
         << hapus->namaPenumpang << " - " << hapus->namaKereta << "\n";
    sTop = sTop->next;
    delete hapus;
}

void peekStack() {
    if (stackKosong()) {
        cout << "  [!] Riwayat transaksi kosong.\n";
        return;
    }

    NodeTransaksi* t = sTop;
    cout << "  Transaksi terakhir : " << t->namaPenumpang
         << " | " << t->namaKereta
         << " | " << t->rute
         << " | " << formatHarga(t->harga) << "\n";
}

void tampilStack() {
    if (stackKosong()) {
        cout << "  [!] Riwayat transaksi kosong.\n";
        return;
    }
    cout << "\n+-----+--------------------+--------------------+--------------------+--------------+\n";
    cout << "| No  | Penumpang          | Kereta             | Rute               | Harga        |\n";
    cout << "+-----+--------------------+--------------------+--------------------+--------------+\n";
    int urut = 1;
    NodeTransaksi* cur = sTop;
    while (cur != nullptr) {
        cout << "| " << left << setw(4)  << urut
             << "| " << left << setw(19) << cur->namaPenumpang
             << "| " << left << setw(19) << cur->namaKereta
             << "| " << left << setw(19) << cur->rute
             << "| " << left << setw(13) << formatHarga(cur->harga) << "|\n";
        cur = cur->next;
        urut++;
    }
    cout << "+-----+--------------------+--------------------+--------------------+--------------+\n";
}

Kereta* cariKereta(Kereta* arr, int n, int nomor) {
    for (int i = 0; i < n; i++)
        if ((arr + i)->nomorKereta == nomor) return arr + i;
    return nullptr;
}

void tampilSemua(Kereta* arr, int n) {
    if (n == 0) {
        cout << "  Belum ada data kereta.\n";
        return;
    }
    cout << "\n+----+--------+----------------------+-------------+-------------+-------+--------------+\n";
    cout << "| No | Nomor  | Nama Kereta          | Asal        | Tujuan      | Jam   | Harga        |\n";
    cout << "+----+--------+----------------------+-------------+-------------+-------+--------------+\n";
    for (int i = 0; i < n; i++) {
        Kereta* p = arr + i;
        cout << "| "  << left << setw(3)  << i + 1
             << "| "  << left << setw(7)  << p->nomorKereta
             << "| "  << left << setw(21) << p->namaKereta
             << "| "  << left << setw(12) << p->asal
             << "| "  << left << setw(12) << p->tujuan
             << "| "  << left << setw(6)  << p->jamBerangkat
             << "| "  << left << setw(13) << formatHarga(p->hargaTiket) << "|\n";
    }
    cout << "+----+--------+----------------------+-------------+-------------+-------+--------------+\n";
}

void tambahKereta() {
    if (jumlahKereta >= MAX_KERETA) {
        cout << "  Data kereta sudah penuh!\n";
        return;
    }
    Kereta k;
    cout << "\n--- Tambah Kereta Baru ---\n";
    cout << "  Nomor Kereta  : "; cin >> k.nomorKereta;
    cin.ignore();
    cout << "  Nama Kereta   : "; getline(cin, k.namaKereta);
    cout << "  Kota Asal     : "; getline(cin, k.asal);
    cout << "  Kota Tujuan   : "; getline(cin, k.tujuan);
    cout << "  Jam Berangkat : "; getline(cin, k.jamBerangkat);
    cout << "  Harga Tiket   : "; cin >> k.hargaTiket;
    daftarKereta[jumlahKereta++] = k;
    cout << "  Data berhasil ditambahkan!\n";
}

void swapNodeData(Kereta* a, Kereta* b) {
    Kereta tmp = *a;   
    *a = *b;
    *b = tmp;
}

void linearSearch(Kereta* arr, int n) {
    string asal, tujuan;
    cin.ignore();
    cout << "\n--- Cari Kereta Berdasarkan Rute ---\n";
    cout << "  Kota Asal   : "; getline(cin, asal);
    cout << "  Kota Tujuan : "; getline(cin, tujuan);
    cout << "\n  Proses pencarian...\n";
    bool ketemu = false;
    for (int i = 0; i < n; i++) {
        Kereta* p = arr + i;
        if (p->asal == asal && p->tujuan == tujuan) {
            cout << "\n  [DITEMUKAN]\n";
            cout << "  Nama  : " << p->namaKereta << "\n";
            cout << "  Rute  : " << p->asal << " -> " << p->tujuan << "\n";
            cout << "  Jam   : " << p->jamBerangkat << "\n";
            cout << "  Harga : " << formatHarga(p->hargaTiket) << "\n";
            ketemu = true;
        }
    }
    if (!ketemu) cout << "  Rute tidak ditemukan.\n";
}

void cariNomor(Kereta* arr, int n) {
    int target;
    cout << "\n--- Cari Kereta Berdasarkan Nomor ---\n";
    cout << "  Nomor Kereta : "; cin >> target;
    Kereta* p = cariKereta(arr, n, target);
    if (p == nullptr) {
        cout << "  Kereta dengan nomor " << target << " tidak ditemukan.\n";
    } else {
        cout << "\n  [DITEMUKAN]\n";
        cout << "  Nama  : " << p->namaKereta << "\n";
        cout << "  Rute  : " << p->asal << " -> " << p->tujuan << "\n";
        cout << "  Jam   : " << p->jamBerangkat << "\n";
        cout << "  Harga : " << formatHarga(p->hargaTiket) << "\n";
    }
}

void selectionSortHarga(Kereta* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if ((arr + j)->hargaTiket < (arr + minIdx)->hargaTiket)
                minIdx = j;
        if (minIdx != i)
            swapNodeData(arr + i, arr + minIdx);  // pakai dereferensi
    }
    cout << "  Data diurutkan berdasarkan harga (termurah).\n";
}

void merge(Kereta* arr, int kiri, int tengah, int kanan) {
    int n1 = tengah - kiri + 1;
    int n2 = kanan - tengah;
    Kereta* L = new Kereta[n1];
    Kereta* R = new Kereta[n2];
    for (int i = 0; i < n1; i++) L[i] = *(arr + kiri + i);
    for (int j = 0; j < n2; j++) R[j] = *(arr + tengah + 1 + j);
    int i = 0, j = 0, k = kiri;
    while (i < n1 && j < n2)
        *(arr + k++) = (L[i].namaKereta <= R[j].namaKereta) ? L[i++] : R[j++];
    while (i < n1) *(arr + k++) = L[i++];
    while (j < n2) *(arr + k++) = R[j++];
    delete[] L;
    delete[] R;
}

void mergeSort(Kereta* arr, int kiri, int kanan) {
    if (kiri < kanan) {
        int tengah = (kiri + kanan) / 2;
        mergeSort(arr, kiri, tengah);
        mergeSort(arr, tengah + 1, kanan);
        merge(arr, kiri, tengah, kanan);
    }
}

void menuAntrianRiwayat() {
    int sub;
    do {
        cout << "\n+-------------------------------+\n";
        cout << "|   Menu Antrian & Riwayat      |\n";
        cout << "+-------------------------------+\n";
        cout << "| 1. Tambah penumpang           |\n";
        cout << "| 2. Proses terdepan            |\n";
        cout << "| 3. Peek antrian & riwayat     |\n";
        cout << "| 4. Tampil semua antrian       |\n";
        cout << "| 5. Tampil riwayat transaksi   |\n";
        cout << "| 6. Batalkan transaksi         |\n";
        cout << "| 0. Kembali                    |\n";
        cout << "+-------------------------------+\n";
        cout << "  Pilihan: "; cin >> sub;

        if (sub == 1) {
            string nama;
            int    nomor;
            tampilSemua(daftarKereta, jumlahKereta);
            cin.ignore();
            cout << "  Nama penumpang : "; getline(cin, nama);
            cout << "  Nomor kereta   : "; cin >> nomor;
            if (cariKereta(daftarKereta, jumlahKereta, nomor) == nullptr)
                cout << "  [!] Nomor kereta tidak ditemukan.\n";
            else
                enqueue(nama, nomor);

        } else if (sub == 2) {
            NodePenumpang p = dequeue();
            if (p.nomorKereta == -1) continue;

            Kereta* k = cariKereta(daftarKereta, jumlahKereta, p.nomorKereta);
            if (k != nullptr) {
                cout << "\n  Tiket berhasil diproses!\n";
                cout << "  Penumpang : " << p.nama << "\n";
                cout << "  Kereta    : " << k->namaKereta << "\n";
                cout << "  Rute      : " << k->asal << " -> " << k->tujuan << "\n";
                cout << "  Jam       : " << k->jamBerangkat << "\n";
                cout << "  Harga     : " << formatHarga(k->hargaTiket) << "\n";

                NodeTransaksi* t = new NodeTransaksi;
                t->namaPenumpang = p.nama;
                t->namaKereta    = k->namaKereta;
                t->rute          = k->asal + " -> " + k->tujuan;
                t->harga         = k->hargaTiket;
                t->next          = nullptr;
                push(t);
            }

        } else if (sub == 3) {
            peekQueue();
            peekStack();

        } else if (sub == 4) {
            tampilQueue();

        } else if (sub == 5) {
            tampilStack();

        } else if (sub == 6) {
            pop();

        } else if (sub != 0) {
            cout << "  Pilihan tidak valid.\n";
        }

    } while (sub != 0);
}

void isiDataAwal() {
    daftarKereta[0] = {101, "Argo Bromo Anggrek", "Surabaya",   "Jakarta",    "07:00", 350000};
    daftarKereta[1] = {205, "Gajayana",           "Malang",     "Jakarta",    "16:00", 420000};
    daftarKereta[2] = {312, "Bima",               "Surabaya",   "Bandung",    "18:30", 280000};
    daftarKereta[3] = {408, "Lodaya",             "Bandung",    "Solo",       "09:15", 175000};
    daftarKereta[4] = {515, "Taksaka",            "Yogyakarta", "Jakarta",    "20:00", 310000};
    jumlahKereta = 5;
}

int main() {
    isiDataAwal();

    int pilihan;
    do {
        cout << "\n+==========================================+\n";
        cout << "|    SISTEM MANAJEMEN KEBERANGKATAN        |\n";
        cout << "|             KERETA API                   |\n";
        cout << "+==========================================+\n";
        cout << "| 1. Tampil Semua Jadwal Kereta            |\n";
        cout << "| 2. Tambah Data Kereta Baru               |\n";
        cout << "| 3. Cari Kereta Berdasarkan Rute          |\n";
        cout << "| 4. Cari Kereta Berdasarkan Nomor         |\n";
        cout << "| 5. Urutkan Berdasarkan Nama (A-Z)        |\n";
        cout << "| 6. Urutkan Berdasarkan Harga (Termurah)  |\n";
        cout << "| 7. Menu Antrian & Riwayat Transaksi      |\n";
        cout << "| 0. Keluar                                |\n";
        cout << "+==========================================+\n";
        cout << "  Pilihan: "; cin >> pilihan;

        switch (pilihan) {
            case 1:
                tampilSemua(daftarKereta, jumlahKereta);
                break;
            case 2:
                tambahKereta();
                break;
            case 3:
                linearSearch(daftarKereta, jumlahKereta);
                break;
            case 4:
                cariNomor(daftarKereta, jumlahKereta);
                break;
            case 5:
                mergeSort(daftarKereta, 0, jumlahKereta - 1);
                cout << "  Data diurutkan berdasarkan nama (A-Z).\n";
                tampilSemua(daftarKereta, jumlahKereta);
                break;
            case 6:
                selectionSortHarga(daftarKereta, jumlahKereta);
                tampilSemua(daftarKereta, jumlahKereta);
                break;
            case 7:
                menuAntrianRiwayat();
                break;
            case 0:
                cout << "  Program selesai. Terima kasih!\n";
                break;
            default:
                cout << "  Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);

    while (!queueKosong()) dequeue();
    while (!stackKosong()) pop();

    return 0;
}