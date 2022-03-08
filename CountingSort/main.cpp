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

int max_element(vector<int> &v) {
    int max = INT_MIN;

    for (auto &x: v) {
        if (x > max)
            max = x;
    }

    return max;
}

int min_element(vector<int> &v) {
    int min = INT_MAX;

    for (auto &x: v) {
        if (x < min)
            min = x;
    }

    return min;
}

vector<int> countingSort(vector<int> &arr) {
    int max = max_element(arr);
    int min = min_element(arr);
    int range = max - min + 1;

    vector<int> count(range + 1, 0);
    vector<int> result(arr.size());
    int i;

    for (i = 0; i < arr.size(); ++i)
        ++count[arr[i] - min];

    for (i = 1; i < range; ++i)
        count[i] += count[i - 1];

    for (i = 0; i < arr.size(); ++i) {
        result[count[arr[i] - min] - 1] = arr[i];
        --count[arr[i] - min];
    }

    return result;
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
        arr = countingSort(arr);
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