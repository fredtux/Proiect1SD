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

vector<int> countSort(vector<int> &v, int exp, int &base){
    vector<int> result (v.size());
    vector<int> count(base, 0);
    int i;
    int n = v.size();

    for(i = 0; i < n; ++i){
        ++count[(v[i] / exp) % base];
    }

    for(i = 1; i < base; ++i){
        count[i] += count[i - 1];
    }

    for(i = n - 1; i >=0; --i){
        result[count[(v[i] / exp) % base] - 1] = v[i];
        --count[(v[i] / exp) % base];
    }

    return result;
}

void radixsort(vector<int> &v, int &base){
    int m = max_element(v);

    for(int exp = 1; m / exp > 0; exp *= base){
        v = countSort(v, exp, base);
    }
}

int main(){
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
        radixsort(arr, base);
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

