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
#include <iostream>

using namespace std;

const int mod = 1000000007;

void product_matrix(int64_t a[2][2], int64_t b[2][2]) {
    int64_t temp[2][2];
    temp[0][0] = ((a[0][0] * b[0][0] % mod) + (a[0][1] * b[1][0]) % mod) % mod;
    temp[0][1] = ((a[0][0] * b[0][1] % mod) + (a[0][1] * b[1][1]) % mod) % mod;
    temp[1][0] = ((a[1][0] * b[0][0] % mod) + (a[1][1] * b[1][0]) % mod) % mod;
    temp[1][1] = ((a[1][0] * b[0][1] % mod) + (a[1][1] * b[1][1]) % mod) % mod;
    a[0][0] = temp[0][0];
    a[0][1] = temp[0][1];
    a[1][0] = temp[1][0];
    a[1][1] = temp[1][1];
}

int64_t find_fibo(int64_t matrix[2][2], int64_t power, ofstream& f) {

    int64_t fibo_matrix[2][2] = {1, 1,
                                 1, 0 };

    int64_t result_matrix[2][2] = {1, 1,
                                   1, 0 };

	while (power) {
        
        if (power & 1) {
            product_matrix(result_matrix, matrix);
        }

        // f << "iteration with power : " << power << endl;
        product_matrix(matrix, matrix);
        
        power >>= 1;

        // f << "matrix :" << endl;
        // f << matrix[0][0] << " " << matrix[0][1] << endl;
        // f << matrix[1][0] << " " << matrix[1][1] << endl;
    }

    // f << "result matrix :" << endl;
    // f << result_matrix[0][0] << " " << result_matrix[0][1] << endl;
    // f << result_matrix[1][0] << " " << result_matrix[1][1] << endl;

	return result_matrix[0][1];
}


int64_t function(int64_t number, ofstream &f) {

    /* fibo matrix */
    int64_t matrix[2][2] = {1, 1,
                            1, 0};

    /* raise power */
    if(number > 3) {
        return find_fibo(matrix, number, f);
    }

    /* base case */
    if(number == 1) {
        return 1;
    }

    if(number == 2) {
        return 2;
    }

    if(number == 3) {
        return 3;
    }

    return 0;
}

int main() {
    ifstream fin("badgpt.in");
    ofstream fout("badgpt.out");
    
    char letter;
    int64_t number;

    int64_t result = 1;

    /* read letter and number */
    while(fin >> letter >> number) {
        
        if(letter == 'n' || letter == 'u')
            result = ( (result % mod) * (function(number, fout) % mod) ) % mod;
    
    }

    fout << result;
    return 0;
}
