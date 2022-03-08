#include <fstream>
#include <vector>
#include <climits>
#include <unordered_map>
#include <time.h>

using namespace std;

bool verify(vector<int> &v) {
    int i;
    for (i = 1; i < v.size(); i++) {
        if (v[i] < v[i - 1])
            return false;
    }

    return true;
}

ofstream &operator<<(ofstream &out, unordered_map<int, double> m) {
    for (auto it = m.begin(); it != m.end(); ++it)
        out << "Test " << it->first + 1 << ": " << it->second << "\n";
}

void insertionsort(vector<int> &v, int l, int r) {
    int i, j;

    for (i = l + 1; i <= r; ++i) {
        for (j = i; j > l + 1; --j) {
            if (j - 1 >= 0 && v[j] < v[j - 1]) {
                swap(v[j], v[j - 1]);
            }
        }
    }
}

void merge(vector<int> &v, int l, int m, int r) {
    int i = l, j = m + 1;
    int end1 = m;
    int end2 = r;
    vector<int> result(r - l + 1);
    int ri = 0;

    while (i <= end1 && j <= end2) {
        if (v[i] <= v[j]) {
            result[ri] = v[i];
            ++i;
        } else {
            result[ri] = v[j];
            ++j;
        }

        ++ri;
    }

    while (i <= end1) {
        result[ri] = v[i];
        ++i;
        ++ri;
    }

    while (j <= end2) {
        result[ri] = v[j];
        ++j;
        ++ri;
    }

    for (i = l, ri = 0; i <= r; ++i)
        v[i] = result[ri++];
}

void mergesort(vector<int> &v, int l, int r) {
    if (l >= r)
        return;

    int m = l + (r - l) / 2;

    mergesort(v, l, m);
    mergesort(v, m + 1, r);
    merge(v, l, m, r);
}

int min(int a, int b) {
    return a < b ? a : b;
}

void timsort(vector<int> &v) {
    int run = 32, size, left, mid, right, i;

    for (i = 0; i < v.size(); i += run) {
        insertionsort(v, i, min((i + run), v.size() - 1));
    }

    for (size = run; size < v.size(); size *= 2) {
        for (left = 0; left < v.size(); left += 2 * size) {
            mid = left + size - 1;
            right = min((left + 2 * size - 1), v.size() - 1);

            if (mid < right) {
                mergesort(v, left, right);
            }
        }
    }

}

int main() {
    vector<int> arr;
    unordered_map<int, double> results;
    int i, j, tmp;

    clock_t stopwatch;
    double timePassed;

    ifstream fin("teste_generale.in");
    ofstream fout("raport.out");

    int n, maxNum, t;

    fin >> t;
    int base = 10;

    for (i = 0; i < t; ++i) {
        arr.clear();

        fin >> n >> maxNum;

        for (j = 0; j < n; ++j) {
            fin >> tmp;
            arr.push_back(tmp);
        }

        stopwatch = clock();
        timsort(arr);
        timePassed = double(clock() - stopwatch) / CLOCKS_PER_SEC;

        if (verify(arr))
            results[i] = timePassed;
        else
            results[i] = -1.0;
    }

    fin.close();

    fout << results;
    fout.close();

    return 0;
}