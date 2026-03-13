#include <istream>
using namespace;

void insertSort(int* A, int n){
    for (int i = 0; i < n; ++i) {
        int cur = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > cur){
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = cur;
    }
}
