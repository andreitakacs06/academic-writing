#include <bits/stdc++.h>
using namespace std;

#define TIMEOUT_SECONDS 15.0
#define NMAX 1000000

// =============================================
//  SORTING ALGORITHMS
// =============================================

template <typename T>
void bubblesort(T a[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] > a[j])
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
    while (j <= r)   temp.push_back(a[j++]);
    for (int k = 0; k < (int)temp.size(); k++)
        a[l + k] = temp[k];
}

template <typename T>
int partition_qs(T a[], int low, int high) {
    // random pivot
    int randIndex = low + rand() % (high - low + 1);
    swap(a[randIndex], a[high]);

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
    while (low < high) {

        int randIndex = low + rand() % (high - low + 1);
        T pivot = a[randIndex];

        int lt = low, i = low, gt = high;

        while (i <= gt) {
            if (a[i] < pivot) {
                swap(a[lt], a[i]);
                lt++; i++;
            }
            else if (a[i] > pivot) {
                swap(a[i], a[gt]);
                gt--;
            }
            else {
                i++;
            }
        }
        if (lt - low < high - gt) {
            quicksort(a, low, lt - 1);
            low = gt + 1;
        } else {
            quicksort(a, gt + 1, high);
            high = lt - 1;
        }
    }
}

template <typename T>
void heapify(T a[], int n, int i) {
    int largest = i;
    int left    = 2 * i + 1;
    int right   = 2 * i + 2;
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

// =============================================
//  DATA GENERATORS - INT
// =============================================

void gen_int_random(int a[], int n)      { for (int i = 0; i < n; i++) a[i] = rand() % 100000; }
void gen_int_sorted(int a[], int n)      { for (int i = 0; i < n; i++) a[i] = i; }
void gen_int_reverse(int a[], int n)     { for (int i = 0; i < n; i++) a[i] = n - i; }
void gen_int_almost(int a[], int n) {
    for (int i = 0; i < n; i++) a[i] = i;
    int swaps = max(1, n * 2 / 100);
    for (int i = 0; i < swaps; i++) swap(a[rand() % n], a[rand() % n]);
}
void gen_int_half(int a[], int n) {
    for (int i = 0; i < n / 2; i++) a[i] = i;
    for (int i = n / 2; i < n; i++) a[i] = rand() % 100000;
}
void gen_int_flat(int a[], int n)        { for (int i = 0; i < n; i++) a[i] = rand() % 5; }

// =============================================
//  DATA GENERATORS - FLOAT
// =============================================

float frand() { return (float)(rand() % 10000000) / 100.0f; }

void gen_float_random(float a[], int n)  { for (int i = 0; i < n; i++) a[i] = frand(); }
void gen_float_sorted(float a[], int n)  { for (int i = 0; i < n; i++) a[i] = (float)i * 0.5f; }
void gen_float_reverse(float a[], int n) { for (int i = 0; i < n; i++) a[i] = (float)(n - i) * 0.5f; }
void gen_float_almost(float a[], int n) {
    for (int i = 0; i < n; i++) a[i] = (float)i * 0.5f;
    int swaps = max(1, n * 2 / 100);
    for (int i = 0; i < swaps; i++) swap(a[rand() % n], a[rand() % n]);
}
void gen_float_half(float a[], int n) {
    for (int i = 0; i < n / 2; i++) a[i] = (float)i * 0.5f;
    for (int i = n / 2; i < n; i++) a[i] = frand();
}
void gen_float_flat(float a[], int n)    { for (int i = 0; i < n; i++) a[i] = (float)(rand() % 5) * 1.1f; }

// =============================================
//  DATA GENERATORS - STRING
// =============================================

string randStr(int len = 6) {
    string s(len, ' ');
    for (char &c : s) c = 'a' + rand() % 26;
    return s;
}
string indexToStr(int i) {
    string s = to_string(i);
    return string(8 - s.size(), '0') + s;
}

void gen_str_random(string a[], int n)   { for (int i = 0; i < n; i++) a[i] = randStr(); }
void gen_str_sorted(string a[], int n)   { for (int i = 0; i < n; i++) a[i] = indexToStr(i); }
void gen_str_reverse(string a[], int n)  { for (int i = 0; i < n; i++) a[i] = indexToStr(n - i); }
void gen_str_almost(string a[], int n) {
    for (int i = 0; i < n; i++) a[i] = indexToStr(i);
    int swaps = max(1, n * 2 / 100);
    for (int i = 0; i < swaps; i++) swap(a[rand() % n], a[rand() % n]);
}
void gen_str_half(string a[], int n) {
    for (int i = 0; i < n / 2; i++) a[i] = indexToStr(i);
    for (int i = n / 2; i < n; i++) a[i] = randStr();
}
void gen_str_flat(string a[], int n) {
    const string pool[] = {"apple", "banana", "cherry", "date", "elderberry"};
    for (int i = 0; i < n; i++) a[i] = pool[rand() % 5];
}

// =============================================
//  STATIC ARRAYS  (allocated once, reused)
// =============================================

static int    ai[NMAX];
static float  af[NMAX];
static string as_arr[NMAX];

// =============================================
//  NAMES (for printing)
// =============================================

string algoName(int choice) {
    if (choice == 1) return "BubbleSort";
    if (choice == 2) return "MergeSort";
    if (choice == 3) return "InsertionSort";
    if (choice == 4) return "QuickSort";
    if (choice == 5) return "HeapSort";
    return "Unknown";
}

string typeName(int dataType) {
    if (dataType == 1) return "int";
    if (dataType == 2) return "float";
    if (dataType == 3) return "string";
    return "Unknown";
}

string distName(int type) {
    if (type == 1) return "random";
    if (type == 2) return "sorted";
    if (type == 3) return "reverse";
    if (type == 4) return "almost_sorted";
    if (type == 5) return "half_sorted";
    if (type == 6) return "flat";
    return "Unknown";
}

// =============================================
//  FILL ARRAY with chosen distribution
// =============================================

void fillInt(int type, int n) {
    if      (type == 1) gen_int_random(ai, n);
    else if (type == 2) gen_int_sorted(ai, n);
    else if (type == 3) gen_int_reverse(ai, n);
    else if (type == 4) gen_int_almost(ai, n);
    else if (type == 5) gen_int_half(ai, n);
    else if (type == 6) gen_int_flat(ai, n);
}

void fillFloat(int type, int n) {
    if      (type == 1) gen_float_random(af, n);
    else if (type == 2) gen_float_sorted(af, n);
    else if (type == 3) gen_float_reverse(af, n);
    else if (type == 4) gen_float_almost(af, n);
    else if (type == 5) gen_float_half(af, n);
    else if (type == 6) gen_float_flat(af, n);
}

void fillStr(int type, int n) {
    if      (type == 1) gen_str_random(as_arr, n);
    else if (type == 2) gen_str_sorted(as_arr, n);
    else if (type == 3) gen_str_reverse(as_arr, n);
    else if (type == 4) gen_str_almost(as_arr, n);
    else if (type == 5) gen_str_half(as_arr, n);
    else if (type == 6) gen_str_flat(as_arr, n);
}

// =============================================
//  RUN ONE SORT + MEASURE TIME
// =============================================

template <typename T>
double runSort(T a[], int n, int choice) {
    clock_t start = clock();

    if      (choice == 1) bubblesort(a, n);
    else if (choice == 2) mergesort(a, 0, n - 1);
    else if (choice == 3) insertionSort(a, n);
    else if (choice == 4) quicksort(a, 0, n - 1);
    else if (choice == 5) heapsort(a, n);

    return (double)(clock() - start) / CLOCKS_PER_SEC;
}

// =============================================
//  MAIN
// =============================================

int main() {
    srand(42); // fixed seed so results are reproducible

    int sizes[]   = {10, 100, 1000, 10000, 100000, 1000000};
    int numSizes  = 6;

    int dists[]   = {1, 2, 3, 4, 5, 6};
    int numDists  = 6;

    int dataTypes[] = {1, 2, 3};
    int numTypes    = 3;

    int algos[]   = {1, 2, 3, 4, 5};
    int numAlgos  = 5;

    ofstream outFile("results.csv");
    outFile << "Algorithm,DataType,Distribution,Size,Time(s)\n";

    int totalTests = numAlgos * numTypes * numDists * numSizes;
    int testsDone  = 0;

    cout << "====================================\n";
    cout << " SORTING ALGORITHM BENCHMARK\n";
    cout << " Timeout per test: " << TIMEOUT_SECONDS << " seconds\n";
    cout << " Total tests: " << totalTests << "\n";
    cout << "====================================\n\n";

    for (int ai_algo = 0; ai_algo < numAlgos; ai_algo++) {
        int choice = algos[ai_algo];

        for (int di = 0; di < numTypes; di++) {
            int dataType = dataTypes[di];

            for (int disti = 0; disti < numDists; disti++) {
                int type = dists[disti];

                for (int si = 0; si < numSizes; si++) {
                    int n = sizes[si];
                    testsDone++;

                    string algo = algoName(choice);
                    string dtyp = typeName(dataType);
                    string dist = distName(type);

                    cout << "[" << testsDone << "/" << totalTests << "] "
                         << algo << " | " << dtyp << " | " << dist << " | n=" << n
                         << " ... ";
                    cout.flush();

                    // O(n^2) algorithms: skip if too large to avoid waiting forever
                    bool isQuadratic = (choice == 1 || choice == 3);
                    if (isQuadratic && n >= 100000) {
                        cout << ">15s (skipped: O(n^2) too slow)\n";
                        outFile << algo << "," << dtyp << "," << dist << "," << n << ",TIMEOUT\n";
                        outFile.flush();
                        continue;
                    }
                    // Strings are slower to compare, skip O(n^2) even earlier
                    if (isQuadratic && dataType == 3 && n >= 10000) {
                        cout << ">15s (skipped: O(n^2) on strings too slow)\n";
                        outFile << algo << "," << dtyp << "," << dist << "," << n << ",TIMEOUT\n";
                        outFile.flush();
                        continue;
                    }

                    // Generate data
                    if      (dataType == 1) fillInt(type, n);
                    else if (dataType == 2) fillFloat(type, n);
                    else if (dataType == 3) fillStr(type, n);

                    // Run sort and measure
                    double elapsed = 0.0;
                    if      (dataType == 1) elapsed = runSort(ai, n, choice);
                    else if (dataType == 2) elapsed = runSort(af, n, choice);
                    else if (dataType == 3) elapsed = runSort(as_arr, n, choice);

                    // Print result
                    if (elapsed > TIMEOUT_SECONDS) {
                        cout << ">15s\n";
                        outFile << algo << "," << dtyp << "," << dist << "," << n << ",TIMEOUT\n";
                    } else {
                        cout << fixed << setprecision(4) << elapsed << "s\n";
                        outFile << algo << "," << dtyp << "," << dist << "," << n << ","
                                << fixed << setprecision(4) << elapsed << "\n";
                    }

                    outFile.flush();
                }
            }
        }
        cout << "------------------------------------\n";
    }

    cout << "\nResults saved to results.csv\n";
    outFile.close();
    return 0;
}
