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

int64_t SolveTask1(const vector<int>& a, const vector<int>& b, ofstream& fout) {
    
    vector<int> c(2 * a.size());

    for(int i = 0 ; i < a.size() ; i++) {
        c[i] = a[i];
    }

    for(int i = a.size() ; i < a.size() * 2 ; i++) {
        c[i] = b[i - a.size()];
    }

    merge_sort(0, a.size() * 2 - 1, c);

    int64_t score = 0;

    for(int i = c.size() - 1 ; i >= a.size() ; i--) {
        score += c[i];
    }

    return score;
}

int64_t SolveTask2(vector<int>& a, vector<int>& b, int moves, ofstream& fout) {
    
    vector<int> maxim(a.size());
    vector<int> caracteristic(a.size());

    for(int i = 0 ; i < a.size() ; i++) {
        maxim[i] = max(a[i], b[i]);
        caracteristic[i] = 1;
    }
    
    // cat timp avem mutari
    while(moves != 0) {
        
        int minim = maxim[0];
        int position = 0;
        // find minimum difference
        for(int i = 0 ; i < maxim.size() ; i++) {
            // find position of minimum
            if(minim > maxim[i] && caracteristic[i] == 1) {
                minim = maxim[i];
                position = i;
            }
        }

        int greatest_score = 0;

        int change = 0;
        int change_list = 0;

        for(int i = 1 ; i < maxim.size() ; i++) {
            
            // dam skip
            if(i == position || caracteristic[i] == 0)
                continue;
            
            // calculam scorul pentru fiecare pereche modificata
            int actual_dif = maxim[position] + maxim[i];
            int schimb_1 = max(a[position], b[i]) + max(b[position], a[i]);
            int schimb_2 = max(a[i], a[position]) + max(b[i], b[position]);

            int verify1 = schimb_1 - actual_dif;
            int verify2 = schimb_2 - actual_dif;

            // daca e mai mare
            if(greatest_score < verify1) {
                greatest_score = verify1;
                change = i;
                change_list = 1;
            }

            if(greatest_score < verify2) {
                greatest_score = verify2;
                change = i;
                change_list = 0;
            }

        }


        if(change_list == 0) {
            int aux = a[change];
            a[change] = a[position];
            a[position] = aux;
            maxim[position] = max(a[position], b[position]);
            maxim[change] = max(a[change], b[change]);
            caracteristic[position] = 0;
            caracteristic[change] = 0;
        } else {
            int aux = a[change];
            a[change] = b[position];
            b[position] = aux;
            maxim[position] = max(a[position], b[position]);
            maxim[change] = max(a[change], b[change]);
            caracteristic[position] = 0;
            caracteristic[change] = 0;
        }

        moves--;

    }

    int64_t score = 0;
    for(int i = 0 ; i < maxim.size() ; i++) {
        score += maxim[i];
    }



   return score;
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

    auto res = task == 1 ? SolveTask1(a, b, fout) : SolveTask2(a, b, moves, fout);
    fout << "\n" << res << "\n";

    return 0;
}
