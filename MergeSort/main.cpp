#include <fstream>
#include <vector>
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

    for (i = 0; i < t; ++i) {
        arr.clear();

        fin >> n >> maxNum;

        for (j = 0; j < n; ++j) {
            fin >> tmp;
            arr.push_back(tmp);
        }

        stopwatch = clock();
        mergesort(arr, 0, arr.size() - 1);
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