/*
 * Acest schelet citește datele de intrare și scrie răspunsul generat de voi,
 * astfel că e suficient să completați cele două funcții.
 *
 * Scheletul este doar un punct de plecare, îl puteți modifica oricum doriți:
 * puteți schimba parametrii, reordona funcțiile etc.
 */

#include <cstdint>
#include <fstream>
#include <vector>

using namespace std;

vector<int64_t> ReadVector(istream& is, int size) {
    vector<int64_t> vec(size);
    for (auto& num : vec) {
        is >> num;
    }
    return vec;
}

int64_t find_C(vector<int64_t> vector, int64_t min, int64_t max, int N, int K) {
    /* binary search */
    while (min != max) {
        /* number of cars */
        int i = 0;
        /* number of feribots */
        int j = 0;
        /* best cost for now */
        int64_t C = (min + max) / 2;
        /* actual cost for sending feribots */
        int64_t c = 0;

        /* for every car */
        for (i = 0 ; i < N ; i++) {
            /* if we surpass the limit */
            if (c + vector[i] > C) {
                /* send a feribot */
                j++;
                /* reset the cost by moving weight on the next feribot */
                c = vector[i];
            } else {
                /* add to the feribot */
                c = c + vector[i];
            }

            /* if we surpass the number of feribots */
            if (j >= K)
                break;
        }

        /* if we iterate through all cars */
        if (i == N)
            /* update the maximum value with C cost */
            max = C;
        else
            /* increase the minimum value by adding 1 */
            min = C + 1;
    }

    /* return minim or maxim */
    return min;
}

int main() {
    ifstream fin("feribot.in");
    ofstream fout("feribot.out");

    /* read N (number of cars) and K (number of feribots) */
    int N, K;
    fin >> N >> K;

    /* read every G (weight) of cars */
    auto vector = ReadVector(fin, N);

    /* make sum of all weight and find max weight */
    int64_t sum = 0;
    int64_t max = vector[0];

    for (int i = 0 ; i < N ; i++) {
        sum += vector[i];
        if (vector[i] > max) {
            max = vector[i];
        }
    }

    /* call function find_C */
    fout << find_C(vector, max, sum, N, K) << "\n";

    return 0;
}
