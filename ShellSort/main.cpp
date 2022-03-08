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


void shellsort(vector<int> &v) {
    int gap = 1, i, j, k;

    while (gap < v.size())
        gap = 3 * gap + 1;
    gap /= 3;

    while (gap > 0) {
        for (j = 0; j < v.size(); ++j) {
            for (i = j; i < v.size(); i += gap) {
                for (k = i; k > j; k -= gap) {
                    if (k - gap >= j && v[k] < v[k - gap]) {
                        swap(v[k], v[k - gap]);
                    }
                }
            }
        }

        gap /= 3;
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

    for (i = 0; i < t; ++i) {
        arr.clear();

        fin >> n >> maxNum;

        for (j = 0; j < n; ++j) {
            fin >> tmp;
            arr.push_back(tmp);
        }

        stopwatch = clock();
        shellsort(arr);
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