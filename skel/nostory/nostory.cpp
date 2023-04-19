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

/* taken from lab */
void merge_halves(int left, int right, vector<int>& v) {
	int mid = (left + right) / 2;
	vector<int> aux;
	int i = left, j = mid + 1;

        while (i <= mid && j <= right) {
		if (v[i] <= v[j]) {
			aux.push_back(v[i]);
			i++;
		} else {
			aux.push_back(v[j]);
			j++;
		}
	}

        while (i <= mid) {
		aux.push_back(v[i]);
		i++;
	}

        while (j <= right) {
		aux.push_back(v[j]);
		j++;
	}

	for (int k = left; k <= right; k++) {
		v[k] = aux[k - left];
	}
}

/* taken from lab */
void merge_sort(int left, int right, vector<int>& c) {
	if (left >= right) return;
	int mid = (left + right) / 2;
    merge_sort(left, mid, c);
	merge_sort(mid + 1, right, c);
	merge_halves(left, right, c);
}

int64_t SolveTask1(const vector<int>& a, const vector<int>& b) {
    /* alloc a vector with (2 * N) size */
    vector<int> c(2 * a.size());

    /* copy the first N items */
    for (int i = 0 ; i < (int)a.size() ; i++) {
        c[i] = a[i];
    }

    /* copy the second N items */
    for (int i = a.size() ; i < (int)a.size() * 2 ; i++) {
        c[i] = b[i - a.size()];
    }

    /* sort them using merge sort function from lab */
    merge_sort(0, a.size() * 2 - 1, c);

    /* calculate the score */
    int64_t score = 0;

    /* best score = biggest N numbers from 2 * N size array */
    for (int i = (int)c.size() - 1 ; i >= (int)a.size() ; i--) {
        score += c[i];
    }

    return score;
}

int64_t SolveTask2(vector<int>& a, vector<int>& b, int moves) {
    /* store the max from every pair */
    vector<int> maxim(a.size());
    /* store the min from every pair */
    vector<int> minim(a.size());

    /* declare actual score and size N */
    int64_t score = 0;
    int iteration = a.size();

    /* find max, min from every pair and actual score */
    for (int i = 0 ; i < iteration ; i++) {
        maxim[i] = max(a[i], b[i]);
        minim[i] = min(a[i], b[i]);
        score += maxim[i];
    }

    /* sort min and max from every pair */
    merge_sort(0, iteration - 1, maxim);
    merge_sort(0, iteration - 1, minim);

    /* declare best difference */
    int64_t add_points = 0;

    /* execute moves */
    for (int i = 0 ; i < moves ; i++)
        /* if our move is good add to difference */
        (minim[a.size() - 1 - i] - maxim[i] > 0) ?
        add_points += minim[a.size() - 1 - i] - maxim[i] : add_points;

    /* return new score formed by previos + best difference */
    return score + add_points;
}

vector<int> ReadVector(istream& is, int size) {
    vector<int> vec(size);
    for (auto& num : vec) {
        is >> num;
    }
    return vec;
}

int main() {
    ifstream fin("nostory.in");
    ofstream fout("nostory.out");

    /* read task */
    int task;
    fin >> task;

    int n, moves;
    if (task == 1) {
        fin >> n;
    } else {
        fin >> n >> moves;
    }

    auto a = ReadVector(fin, n);
    auto b = ReadVector(fin, n);

    auto res = task == 1 ? SolveTask1(a, b) : SolveTask2(a, b, moves);
    fout << res << "\n";

    return 0;
}
