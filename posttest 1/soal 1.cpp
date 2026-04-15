#include <iostream>
using namespace std;

/*
 * ============================================================
 *  ANALISIS KOMPLEKSITAS WAKTU - FindMin
 * ============================================================
 *
 * -----------------------------------------------------------
 * | Pseudocode                         | Cost  | Kali Jalan |
 * |---------------------------------------------------------|
 * | min ← A[0]                         |  c1   |     1      |
 * | for i ← 1 to n-1 do                |  c2   |     n      |
 * |  if A[i] < min then                |  c3   |    n-1     |
 * |    min ← A[i]                      |  c4   |  0 ~ n-1   |
 * | end if                             |   -   |     -      |
 * | end for                            |   -   |     -      |
 * | return min                         |  c5   |     1      |
 * |------------------------------------|-------|------------|
 *
 *  BEST CASE (array sudah urut naik → min tidak pernah diupdate):
 *    T_min(n) = c1 + c2*n + c3*(n-1) + c4*0 + c5
 *             = c1 + c2*n + c3*n - c3 + c5
 *             = (c2+c3)*n + (c1 - c3 + c5)
 *             = an + b          → O(n)
 *
 *  WORST CASE (array urut turun → min selalu diupdate setiap iterasi):
 *    T_max(n) = c1 + c2*n + c3*(n-1) + c4*(n-1) + c5
 *             = c1 + c2*n + c3*n - c3 + c4*n - c4 + c5
 *             = (c2+c3+c4)*n + (c1 - c3 - c4 + c5)
 *             = an + b          → O(n)
 *
 *  KESIMPULAN:
 *    Best Case  = O(n)
 *    Worst Case = O(n)
 *    Algoritma FindMin selalu linier karena WAJIB
 *    memeriksa setiap elemen sekali — tidak bisa dihindari.
 * ============================================================
 */

int FindMin(int A[], int n, int &indexMin) {
    int min = A[0];  
    indexMin = 0;

    for (int i = 1; i < n; i++) {   
        if (A[i] < min) {          
            min      = A[i];        
            indexMin = i;
        }
    }

    return min;  
}

int main() {

    int fib[] = {1, 1, 2, 3, 5, 8, 13, 21};
    int n     = 8;

    cout << endl;
    cout << "  ============================================" << endl;
    cout << "  |   Program Analisis Algoritma FindMin     |" << endl;
    cout << "  |   Kompleksitas Waktu - Array Fibonacci   |" << endl;
    cout << "  ============================================" << endl;

    cout << "\n  Array Fibonacci: [";
    for (int i = 0; i < n; i++) {
        cout << fib[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]" << endl;
    cout << "  Jumlah elemen (n) = " << n << endl;

    int indexMin = 0;
    int hasilMin = FindMin(fib, n, indexMin);

    cout << "\n  ============================================" << endl;
    cout << "  Hasil:" << endl;
    cout << "  Nilai Minimum  : " << hasilMin  << endl;
    cout << "  Indeks         : " << indexMin  << endl;
    cout << "  ============================================" << endl;

    cout << "\n  Analisis Kompleksitas   : " << endl;
    cout << "  - Best Case  (array naik) : O(n) = O(" << n << ")" << endl;
    cout << "  - Worst Case (array turun): O(n) = O(" << n << ")" << endl;
    cout << "  - Iterasi aktual          : " << n - 1 << " kali" << endl;
    cout << "  ============================================\n" << endl;

    return 0;
}