#include <bits/stdc++.h>
using namespace std;
#define NMAX 100000000

int n, choice, type, dataType;

// ==================== SORTING ALGORITHMS ====================

template <typename T>
void bubblesort(T a[], int n) {
    for(int i = 0; i < n - 1; i++)
        for(int j = i + 1; j < n; j++)
            if(a[i] > a[j])
                swap(a[i], a[j]);
}

template <typename T>
void insertionSort(T a[], int n) {
    for (int i = 1; i < n; i++) {
        T key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

template <typename T>
void mergesort(T a[], int l, int r) {
    if (l >= r) return;
    int mid = (l + r) / 2;
    mergesort(a, l, mid);
    mergesort(a, mid + 1, r);

    vector<T> temp;
    int i = l, j = mid + 1;
    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) temp.push_back(a[i++]);
        else temp.push_back(a[j++]);
    }
    while (i <= mid) temp.push_back(a[i++]);
    while (j <= r) temp.push_back(a[j++]);
    for (int k = 0; k < (int)temp.size(); k++)
        a[l + k] = temp[k];
}

template <typename T>
int partition_qs(T a[], int low, int high) {
    T pivot = a[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (a[j] < pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[high]);
    return i + 1;
}

template <typename T>
void quicksort(T a[], int low, int high) {
    if (low < high) {
        int pi = partition_qs(a, low, high);
        quicksort(a, low, pi - 1);
        quicksort(a, pi + 1, high);
    }
}

template <typename T>
void heapify(T a[], int n, int i) {
    int largest = i;
    int left  = 2 * i + 1;
    int right = 2 * i + 2;
    if (left  < n && a[left]  > a[largest]) largest = left;
    if (right < n && a[right] > a[largest]) largest = right;
    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

template <typename T>
void heapsort(T a[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}

// ==================== DATA GENERATORS ====================

// --- INT ---
void gen_int_random(int a[])        { for (int i = 0; i < n; i++) a[i] = rand() % 100000; }
void gen_int_sorted(int a[])        { for (int i = 0; i < n; i++) a[i] = i; }
void gen_int_reverse(int a[])       { for (int i = 0; i < n; i++) a[i] = n - i; }
void gen_int_almost(int a[]) {
    for (int i = 0; i < n; i++) a[i] = i;
    int swaps = max(1, n * 2 / 100);
    for (int i = 0; i < swaps; i++) swap(a[rand() % n], a[rand() % n]);
}
void gen_int_half(int a[]) {
    for (int i = 0; i < n / 2; i++) a[i] = i;
    for (int i = n / 2; i < n; i++) a[i] = rand() % 100000;
}
void gen_int_flat(int a[])          { for (int i = 0; i < n; i++) a[i] = rand() % 5; }

// --- FLOAT ---
float frand() { return (float)(rand() % 10000000) / 100.0f; }

void gen_float_random(float a[])    { for (int i = 0; i < n; i++) a[i] = frand(); }
void gen_float_sorted(float a[])    { for (int i = 0; i < n; i++) a[i] = (float)i * 0.5f; }
void gen_float_reverse(float a[])   { for (int i = 0; i < n; i++) a[i] = (float)(n - i) * 0.5f; }
void gen_float_almost(float a[]) {
    for (int i = 0; i < n; i++) a[i] = (float)i * 0.5f;
    int swaps = max(1, n * 2 / 100);
    for (int i = 0; i < swaps; i++) swap(a[rand() % n], a[rand() % n]);
}
void gen_float_half(float a[]) {
    for (int i = 0; i < n / 2; i++) a[i] = (float)i * 0.5f;
    for (int i = n / 2; i < n; i++) a[i] = frand();
}
void gen_float_flat(float a[])      { for (int i = 0; i < n; i++) a[i] = (float)(rand() % 5) * 1.1f; }

// --- STRING ---
string randStr(int len = 6) {
    string s(len, ' ');
    for (char &c : s) c = 'a' + rand() % 26;
    return s;
}
string indexToStr(int i) {
    // zero-pads to 8 chars so lexicographic order == numeric order
    string s = to_string(i);
    return string(8 - s.size(), '0') + s;
}

void gen_str_random(string a[])     { for (int i = 0; i < n; i++) a[i] = randStr(); }
void gen_str_sorted(string a[])     { for (int i = 0; i < n; i++) a[i] = indexToStr(i); }
void gen_str_reverse(string a[])    { for (int i = 0; i < n; i++) a[i] = indexToStr(n - i); }
void gen_str_almost(string a[]) {
    for (int i = 0; i < n; i++) a[i] = indexToStr(i);
    int swaps = max(1, n * 2 / 100);
    for (int i = 0; i < swaps; i++) swap(a[rand() % n], a[rand() % n]);
}
void gen_str_half(string a[]) {
    for (int i = 0; i < n / 2; i++) a[i] = indexToStr(i);
    for (int i = n / 2; i < n; i++) a[i] = randStr();
}
void gen_str_flat(string a[])       { 
    const string pool[] = {"apple","banana","cherry","date","elderberry"};
    for (int i = 0; i < n; i++) a[i] = pool[rand() % 5];
}

// ==================== RUN SORT ====================

template <typename T>
void runSort(T a[]) {
    clock_t before = clock();
    if      (choice == 1) bubblesort(a, n);
    else if (choice == 2) mergesort(a, 0, n - 1);
    else if (choice == 3) insertionSort(a, n);
    else if (choice == 4) quicksort(a, 0, n - 1);
    else if (choice == 5) heapsort(a, n);
    clock_t duration = clock() - before;
    cout << "\nDuration: " << (float)duration / CLOCKS_PER_SEC << " seconds\n";
}

// ==================== MAIN ====================

int main() {
    srand(time(0));

    cout << "Enter N value: ";
    cin >> n;

    cout << "\nSelect data type:\n";
    cout << "1. Integer\n";
    cout << "2. Float\n";
    cout << "3. String\n\n";
    cin >> dataType;

    cout << "\nSelect list type:\n";
    cout << "1. Random\n";
    cout << "2. Sorted\n";
    cout << "3. Reverse Sorted\n";
    cout << "4. Almost Sorted (98%)\n";
    cout << "5. Half Sorted\n";
    cout << "6. Flat (few values)\n\n";
    cin >> type;

    cout << "\nSelect sorting algorithm:\n";
    cout << "1. BubbleSort\n";
    cout << "2. MergeSort\n";
    cout << "3. InsertionSort\n";
    cout << "4. QuickSort\n";
    cout << "5. HeapSort\n\n";
    cin >> choice;

    if (dataType == 1) {
        static int   ai[NMAX];
        if      (type == 1) gen_int_random(ai);
        else if (type == 2) gen_int_sorted(ai);
        else if (type == 3) gen_int_reverse(ai);
        else if (type == 4) gen_int_almost(ai);
        else if (type == 5) gen_int_half(ai);
        else if (type == 6) gen_int_flat(ai);
        runSort(ai);
    } else if (dataType == 2) {
        static float af[NMAX];
        if      (type == 1) gen_float_random(af);
        else if (type == 2) gen_float_sorted(af);
        else if (type == 3) gen_float_reverse(af);
        else if (type == 4) gen_float_almost(af);
        else if (type == 5) gen_float_half(af);
        else if (type == 6) gen_float_flat(af);
        runSort(af);
    } else if (dataType == 3) {
        static string as[NMAX];
        if      (type == 1) gen_str_random(as);
        else if (type == 2) gen_str_sorted(as);
        else if (type == 3) gen_str_reverse(as);
        else if (type == 4) gen_str_almost(as);
        else if (type == 5) gen_str_half(as);
        else if (type == 6) gen_str_flat(as);
        runSort(as);
    }

    return 0;
}