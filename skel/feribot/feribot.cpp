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

vector<long long int> ReadVector(istream& is, int size) {
    vector<long long int> vec(size);
    for (auto& num : vec) {
        is >> num;
    }
    return vec;
}

long long int find(vector<long long int> vector, long long int minim, long long int maxim, int N, int K) {

    long long int i = 0;
    long long int j = 0;


    while(minim != maxim) {

        long long int C = (minim + maxim) / 2; // costul cel mai bun

        
        j = 0;

        long long int cost = 0; // costul ca sa ducem vapoare

        for(i = 0 ; i < N ; i++) {


            if(cost + vector[i] > C) {
                j++ ; // se duce un vapor
                cost = vector[i]; // se reseteaza costul
                // fout << "j : " << j << endl;
            } else {
                cost = cost + vector[i]; // se adauga in vapor
            }


            if(j >= K) { // daca am mai multe vapoare, ies
                break;
            }

        }



        if(i == N) { // daca s au parcurs toate elementele
            maxim = C;
        } else {
            minim = C + 1;
        }
        
    }


    return minim;
}

int main() {
    ifstream fin("feribot.in");
    ofstream fout("feribot.out");
    
    int N, K;
    fin >> N >> K;

    auto vector = ReadVector(fin, N);
    
    
    // make sum of all elements and find min
    long long int sum = 0;
    long long int max = vector[0];

    for(int i = 0 ; i < N ; i++) {
        sum += vector[i];
        if(vector[i] > max) {
            max = vector[i];
        }
    }

    // fout << "minim : " << min;
    // fout << "\n maxim : " << sum; 
    fout << find(vector, max, sum, N, K) << "\n";

    return 0;
}
