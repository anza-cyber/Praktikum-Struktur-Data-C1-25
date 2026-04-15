#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int sqrtManual(int n) {
    int i = 1;
    while (i * i <= n) i++;
    return i - 1;
}

string formatHarga(double harga) {
    long long angka = (long long)harga;
    string s = to_string(angka);
    string hasil = "";
    int count = 0;
    for (int i = s.size() - 1; i >= 0; i--) {
        if (count > 0 && count % 3 == 0) hasil = "." + hasil;
        hasil = s[i] + hasil;
        count++;
    }
    return "Rp " + hasil;
}

struct Kereta {
    int nomorKereta;
    string namaKereta;
    string asal;
    string tujuan;
    string jamBerangkat;
    double hargaTiket;
};

struct Penumpang {
    string nama;
    int nomorKereta;
};

struct Transaksi {
    string namaPenumpang;
    string namaKereta;
    string rute;
    double harga;
};

const int MAX = 50;

Kereta daftarKereta[MAX];
int jumlahKereta = 0;

Penumpang queueData[MAX];
int front = -1, rear = -1;

Transaksi stack[MAX];
int top = -1;

bool isFull() {
    return rear == MAX - 1;
}

bool isEmpty() {
    return front == -1 || front > rear;
}

void enqueue(Penumpang p) {
    if (isFull()) {
        cout << "Queue overflow\n";
        return;
    }
    if (front == -1) front = 0;
    rear++;
    *(queueData + rear) = p;
    cout << p.nama << " masuk antrian.\n";
}

Penumpang dequeue() {
    Penumpang kosong = {"", -1};
    if (isEmpty()) {
        cout << "Queue underflow\n";
        return kosong;
    }
    Penumpang p = *(queueData + front);
    front++;
    if (isEmpty()) front = rear = -1;
    return p;
}

void peekQueue() {
    if (isEmpty()) {
        cout << "Queue is empty\n";
        return;
    }
    Penumpang* p = queueData + front;
    cout << "Penumpang terdepan: " << p->nama << " (kereta no." << p->nomorKereta << ")\n";
}

void displayQueue() {
    if (isEmpty()) {
        cout << "Queue is empty\n";
        return;
    }
    cout << "\n--- Antrian Pembelian Tiket ---\n";
cout << "+----+----------------------+-----------+\n";
cout << "| No | Nama Penumpang       | No Kereta |\n";
cout << "+----+----------------------+-----------+\n";
    for (int i = front; i <= rear; i++) {
        Penumpang* p = queueData + i;
        cout << "| "  << left << setw(3)  << (i - front + 1)
             << "| "  << left << setw(20) << p->nama
             << "| "  << left << setw(9)  << p->nomorKereta << "|\n";
    }
    cout << "+----+---------------------+----------+\n";
}

bool isStackFull() {
    return top >= MAX - 1;
}

bool isStackEmpty() {
    return top < 0;
}

void push(Transaksi t) {
    if (isStackFull()) {
        cout << "Stack overflow\n";
        return;
    }
    top++;
    *(stack + top) = t;
    cout << "Transaksi " << t.namaPenumpang << " disimpan ke riwayat.\n";
}

void pop() {
    if (isStackEmpty()) {
        cout << "Stack underflow\n";
        return;
    }
    Transaksi* t = stack + top;
    cout << "Transaksi dibatalkan: " << t->namaPenumpang << " - " << t->namaKereta << "\n";
    top--;
}

void peekStack() {
    if (isStackEmpty()) {
        cout << "Stack is empty\n";
        return;
    }
    Transaksi* t = stack + top;
    cout << "Transaksi terakhir: " << t->namaPenumpang
         << " | " << t->namaKereta
         << " | " << t->rute
         << " | " << formatHarga(t->harga) << "\n";
}

void displayStack() {
    if (isStackEmpty()) {
        cout << "Stack is empty\n";
        return;
    }
    cout << "\n--- Riwayat Transaksi ---\n";
    cout << "+----+--------------------+--------------------+--------------------+--------------+\n";
    cout << "| No | Penumpang          | Kereta             | Rute               | Harga        |\n";
    cout << "+----+--------------------+--------------------+--------------------+--------------+\n";
    for (int i = top; i >= 0; i--) {
        Transaksi* t = stack + i;
        cout << "| "  << left << setw(3)  << (top - i + 1)
             << "| "  << left << setw(19) << t->namaPenumpang
             << "| "  << left << setw(19) << t->namaKereta
             << "| "  << left << setw(19) << t->rute
             << "| "  << left << setw(13) << formatHarga(t->harga) << "|\n";
    }
    cout << "+----+--------------------+--------------------+--------------------+--------------+\n";
}

Kereta* cariKereta(Kereta* arr, int n, int nomor) {
    for (int i = 0; i < n; i++)
        if ((arr + i)->nomorKereta == nomor) return arr + i;
    return nullptr;
}

void tampilSemua(Kereta* arr, int n) {
    if (n == 0) {
        cout << "Belum ada data kereta.\n";
        return;
    }
    cout << "\n+----+-------+----------------------+-------------+-------------+-------+--------------+\n";
    cout << "| No | Nomor | Nama Kereta          | Asal        | Tujuan      | Jam   | Harga        |\n";
    cout << "+----+-------+----------------------+-------------+-------------+-------+--------------+\n";
    for (int i = 0; i < n; i++) {
        Kereta* p = arr + i;
        cout << "| "  << left << setw(3)  << i+1
             << "| "  << left << setw(6)  << p->nomorKereta
             << "| "  << left << setw(21) << p->namaKereta
             << "| "  << left << setw(12) << p->asal
             << "| "  << left << setw(12) << p->tujuan
             << "| "  << left << setw(6)  << p->jamBerangkat
             << "| "  << left << setw(12) << formatHarga(p->hargaTiket) << "|\n";
    }
    cout << "+----+-------+----------------------+-------------+-------------+-------+--------------+\n";
}

void tambahKereta() {
    if (jumlahKereta >= MAX) {
        cout << "Data kereta sudah penuh!\n";
        return;
    }
    Kereta k;
    cout << "\n--- Tambah Kereta Baru ---\n";
    cout << "Nomor Kereta   : "; cin >> k.nomorKereta;
    cin.ignore();
    cout << "Nama Kereta    : "; getline(cin, k.namaKereta);
    cout << "Kota Asal      : "; getline(cin, k.asal);
    cout << "Kota Tujuan    : "; getline(cin, k.tujuan);
    cout << "Jam Berangkat  : "; getline(cin, k.jamBerangkat);
    cout << "Harga Tiket    : "; cin >> k.hargaTiket;
    daftarKereta[jumlahKereta++] = k;
    cout << "Data berhasil ditambahkan!\n";
}

void linearSearch(Kereta* arr, int n) {
    string asal, tujuan;
    cin.ignore();
    cout << "\n--- Linear Search Berdasarkan Rute ---\n";
    cout << "Masukkan Kota Asal  : "; getline(cin, asal);
    cout << "Masukkan Kota Tujuan: "; getline(cin, tujuan);
    cout << "\nProses pencarian:\n";
    bool ketemu = false;
    for (int i = 0; i < n; i++) {
        Kereta* p = arr + i;
        cout << "  Iterasi " << i+1 << " -> cek: " << p->asal << " - " << p->tujuan;
        if (p->asal == asal && p->tujuan == tujuan) {
            cout << " [COCOK!]\n";
            cout << "\nKereta ditemukan:\n";
            cout << "  Nama    : " << p->namaKereta << "\n";
            cout << "  Rute    : " << p->asal << " -> " << p->tujuan << "\n";
            cout << "  Jam     : " << p->jamBerangkat << "\n";
            cout << "  Harga   : " << formatHarga(p->hargaTiket) << "\n";
            ketemu = true;
        } else {
            cout << " [tidak cocok]\n";
        }
    }
    if (!ketemu) cout << "Rute tidak ditemukan.\n";
}

void jumpSearch(Kereta* arr, int n) {
    int target;
    cout << "\n--- Mengurutkan Berdasarkan Nomor Kereta ---\n";
    cout << "Masukkan Nomor Kereta: "; cin >> target;

    for (int i = 0; i < n-1; i++) {
        int minIdx = i;
        for (int j = i+1; j < n; j++) {
            if ((arr+j)->nomorKereta < (arr+minIdx)->nomorKereta)
                minIdx = j;
        }
        if (minIdx != i) {
            Kereta* a = arr + i;
            Kereta* b = arr + minIdx;
            Kereta temp = *a; *a = *b; *b = temp;
        }
    }

    int step = sqrtManual(n);
    int prev = 0;
    bool ketemu = false;
    cout << "Data sudah diurutkan berdasarkan nomor. Mulai mengurutkan...\n";

    int batas = step < n ? step : n;
    while (prev < n && (arr + batas - 1)->nomorKereta < target) {
        cout << "  Jump ke indeks " << batas - 1
             << " -> nomor " << (arr + batas - 1)->nomorKereta << "\n";
        prev = step;
        step += sqrtManual(n);
        batas = step < n ? step : n;
        if (prev >= n) break;
    }

    int akhir = step < n ? step : n;
    for (int i = prev; i < akhir; i++) {
        Kereta* p = arr + i;
        cout << "  Cek indeks " << i << " -> nomor " << p->nomorKereta;
        if (p->nomorKereta == target) {
            cout << " [KETEMU!]\n";
            cout << "\nKereta ditemukan:\n";
            cout << "  Nama    : " << p->namaKereta << "\n";
            cout << "  Rute    : " << p->asal << " -> " << p->tujuan << "\n";
            cout << "  Jam     : " << p->jamBerangkat << "\n";
            cout << "  Harga   : " << formatHarga(p->hargaTiket) << "\n";
            ketemu = true;
            break;
        } else {
            cout << " [tidak cocok]\n";
        }
    }
    if (!ketemu) cout << "Kereta dengan nomor " << target << " tidak ditemukan.\n";
}

void merge(Kereta* arr, int kiri, int tengah, int kanan) {
    int n1 = tengah - kiri + 1;
    int n2 = kanan - tengah;
    Kereta* L = new Kereta[n1];
    Kereta* R = new Kereta[n2];
    for (int i = 0; i < n1; i++) L[i] = *(arr + kiri + i);
    for (int j = 0; j < n2; j++) R[j] = *(arr + tengah + 1 + j);
    int i = 0, j = 0, k = kiri;
    while (i < n1 && j < n2) {
        if (L[i].namaKereta <= R[j].namaKereta) *(arr + k) = L[i++];
        else *(arr + k) = R[j++];
        k++;
    }
    while (i < n1) *(arr + k++) = L[i++];
    while (j < n2) *(arr + k++) = R[j++];
    delete[] L; delete[] R;
}

void mergeSort(Kereta* arr, int kiri, int kanan) {
    if (kiri < kanan) {
        int tengah = (kiri + kanan) / 2;
        mergeSort(arr, kiri, tengah);
        mergeSort(arr, tengah + 1, kanan);
        merge(arr, kiri, tengah, kanan);
    }
}

void selectionSort(Kereta* arr, int n) {
    for (int i = 0; i < n-1; i++) {
        int minIdx = i;
        for (int j = i+1; j < n; j++) {
            if ((arr+j)->hargaTiket < (arr+minIdx)->hargaTiket)
                minIdx = j;
        }
        if (minIdx != i) {
            Kereta* a = arr + i;
            Kereta* b = arr + minIdx;
            Kereta tmp = *a; *a = *b; *b = tmp;
        }
    }
    cout << "Data berhasil diurutkan berdasarkan harga (termurah).\n";
}

void menuAntrianRiwayat() {
    int sub;
    do {
        cout << "\n--- Menu Antrian & Riwayat ---\n";
        cout << "1. Tambah penumpang ke antrian \n";
        cout << "2. Proses penumpang terdepan \n";
        cout << "3. Cek penumpang terdepan & transaksi terakhir \n";
        cout << "4. Tampil semua antrian\n";
        cout << "5. Tampil semua riwayat transaksi\n";
        cout << "6. Batalkan transaksi terakhir \n";
        cout << "0. Kembali\n";
        cout << "Pilihan: "; cin >> sub;

        if (sub == 1) {
            Penumpang p;
            tampilSemua(daftarKereta, jumlahKereta);
            cin.ignore();
            cout << "Nama penumpang : "; getline(cin, p.nama);
            cout << "Nomor kereta   : "; cin >> p.nomorKereta;
            if (cariKereta(daftarKereta, jumlahKereta, p.nomorKereta) == nullptr)
                cout << "Nomor kereta tidak ditemukan!\n";
            else
                enqueue(p);

        } else if (sub == 2) {
            Penumpang p = dequeue();
            if (p.nomorKereta == -1) continue;
            Kereta* k = cariKereta(daftarKereta, jumlahKereta, p.nomorKereta);
            if (k != nullptr) {
                cout << "\nTiket berhasil diproses!\n";
                cout << "  Penumpang : " << p.nama << "\n";
                cout << "  Kereta    : " << k->namaKereta << "\n";
                cout << "  Rute      : " << k->asal << " -> " << k->tujuan << "\n";
                cout << "  Jam       : " << k->jamBerangkat << "\n";
                cout << "  Harga     : " << formatHarga(k->hargaTiket) << "\n";
                Transaksi t;
                t.namaPenumpang = p.nama;
                t.namaKereta    = k->namaKereta;
                t.rute          = k->asal + " -> " + k->tujuan;
                t.harga         = k->hargaTiket;
                push(t);
            }

        } else if (sub == 3) {
            peekQueue();
            peekStack();

        } else if (sub == 4) {
            displayQueue();

        } else if (sub == 5) {
            displayStack();

        } else if (sub == 6) {
            pop();

        } else if (sub != 0) {
            cout << "Pilihan tidak valid!\n";
        }

    } while (sub != 0);
}

void isiDataAwal() {
    daftarKereta[0] = {101, "Argo Bromo Anggrek", "Surabaya",   "Jakarta", "07:00", 350000};
    daftarKereta[1] = {205, "Gajayana",           "Malang",     "Jakarta", "16:00", 420000};
    daftarKereta[2] = {312, "Bima",               "Surabaya",   "Bandung", "18:30", 280000};
    daftarKereta[3] = {408, "Lodaya",             "Bandung",    "Solo",    "09:15", 175000};
    daftarKereta[4] = {515, "Taksaka",            "Yogyakarta", "Jakarta", "20:00", 310000};
    jumlahKereta = 5;
}

int main() {
    isiDataAwal();

    int pilihan;
    do {
        cout << "\n====================================\n";
        cout << "  SISTEM MANAJEMEN KEBERANGKATAN\n";
        cout << "            KERETA API\n";
        cout << "====================================\n";
        cout << "1. Tampil Semua Jadwal Kereta\n";
        cout << "2. Tambah Data Kereta Baru\n";
        cout << "3. Cari Kereta Berdasarkan Rute \n";
        cout << "4. Cari Kereta Berdasarkan Nomor \n";
        cout << "5. Urutkan Berdasarkan Nama Kereta A-Z ";
        cout << "6. Urutkan Berdasarkan Harga Termurah \n";
        cout << "7. Menu Antrian & Riwayat Transaksi\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: "; cin >> pilihan;

        switch (pilihan) {
            case 1: tampilSemua(daftarKereta, jumlahKereta); break;
            case 2: tambahKereta(); break;
            case 3: linearSearch(daftarKereta, jumlahKereta); break;
            case 4: jumpSearch(daftarKereta, jumlahKereta); break;
            case 5:
                mergeSort(daftarKereta, 0, jumlahKereta - 1);
                cout << "Data berhasil diurutkan berdasarkan nama (A-Z).\n";
                tampilSemua(daftarKereta, jumlahKereta);
                break;
            case 6:
                selectionSort(daftarKereta, jumlahKereta);
                tampilSemua(daftarKereta, jumlahKereta);
                break;
            case 7: menuAntrianRiwayat(); break;
            case 0: cout << "Program selesai. Terima kasih!\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 0);

    return 0;
}