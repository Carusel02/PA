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
#include <bits/stdc++.h>

using namespace std;

/* preluat din laborator */
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

void merge_sort(int left, int right, vector<int>& c) {
	if (left >= right) return ;
	int mid = (left + right) / 2;
    
    merge_sort(left, mid, c);
	merge_sort(mid + 1, right, c);
	merge_halves(left, right, c);
}

int64_t SolveTask1(const vector<int>& a, const vector<int>& b) {
    
    vector<int> c(2 * a.size());
    

    for(int i = 0 ; i < (int)a.size() ; i++) {
        c[i] = a[i];
    }

    for(int i = a.size() ; i < (int)a.size() * 2 ; i++) {
        c[i] = b[i - a.size()];
    }

    merge_sort(0, a.size() * 2 - 1, c);

    int64_t score = 0;

    for(int i = (int)c.size() - 1 ; i >= (int)a.size() ; i--) {
        score += c[i];
    }

    return score;
}

int64_t SolveTask2(vector<int>& a, vector<int>& b, int moves) {
    
    vector<int> maxim(a.size());
    vector<int> minim(a.size());
    vector<int> add(a.size());
    int64_t score = 0;
    int iteration = a.size();

    // minim, maxim, scor actual
    for(int i = 0 ; i < iteration ; i++) {
        maxim[i] = max(a[i], b[i]);
        minim[i] = min(a[i], b[i]);
        score += maxim[i];
    }

    // sortam vectorii
    merge_sort(0, iteration - 1, maxim);
    merge_sort(0, iteration - 1, minim);

    int64_t add_points = 0;
    // execut o mutare buna
    for(int i = 0 ; i < moves ; i++)
        (minim[a.size() - 1 - i] - maxim[i] > 0) ? add_points += minim[a.size() - 1 - i] - maxim[i] : add_points;

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
