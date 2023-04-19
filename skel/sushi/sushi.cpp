#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>
#include <stdlib.h>

using namespace std;

/* taken from lab */
int rucsac(int n, int W, vector<int> &w, vector<int> &p) {
    // dp este o matrice de dimensiune (n + 1) x (W + 1)
    // pentru că folosim dp[0][*] pentru mulțimea vidă
    //                   dp[*][0] pentru situația în care ghiozdanul are capacitate 0
    vector< vector<int> > dp(n + 1, vector<int>(W + 1, 0));
 
    // cazul de bază
    for (int cap = 0; cap <= W; ++cap) {
        dp[0][cap] = 0;
    }

    // cazul general
    for (int i = 1; i <= n; ++i) {
        for (int cap = 0; cap <= W; ++cap) {
            // nu folosesc obiectul i => e soluția de la pasul i - 1
            dp[i][cap] = dp[i-1][cap];
            // folosesc obiectul i, deci trebuie să rezerv w[i] unități în rucsac
            // înseamnă ca înainte trebuie să ocup maxim cap - w[i] unități
            if (cap - w[i] >= 0) {
                int sol_aux = dp[i-1][cap - w[i]] + p[i];
				// cout << "| SOL : " << sol_aux << "| ";
                dp[i][cap] = max(dp[i][cap], sol_aux);
            }
        }
    }

    return dp[n][W];
}

/* taken from lab */
int rucsac2(int n, int W, vector<int> &w, vector<int> &p, int Z) {
    // dp este o matrice de dimensiune (n + 1) x (W + 1)
    // pentru că folosim dp[0][*] pentru mulțimea vidă
    //                   dp[*][0] pentru situația în care ghiozdanul are capacitate 0
    vector<vector<vector<int> > > dp = vector< vector <vector<int> > >(n + 1, vector<vector<int> >(W + 1, vector<int>(Z + 1, 0)));

    // cazul de bază
    for (int cap = 0; cap <= W; ++cap) {
        dp[0][cap][0] = 0;
    }

    // cazul general
    for (int i = 1; i <= n; ++i) {
        for (int cap = 0; cap <= W; ++cap) {
			for(int k = 1 ; k <= Z ; ++k) {
				// nu folosesc obiectul i => e soluția de la pasul i - 1
				dp[i][cap][k] = dp[i-1][cap][k];
				// folosesc obiectul i, deci trebuie să rezerv w[i] unități în rucsac
				// înseamnă ca înainte trebuie să ocup maxim cap - w[i] unități
				if (cap - w[i] >= 0) {
					int sol_aux = dp[i-1][cap - w[i]][k - 1] + p[i];
					// cout << "| SOL : " << sol_aux << "| ";
					dp[i][cap][k] = max(dp[i][cap][k], sol_aux);
				}
			}
		}
    }

    return dp[n][W][Z];
}

int task1(int n, int m, int x, vector <int>& p, vector <vector <int> >& g) {

	vector<int> value(m + 1);

	// for every sushi type
	for(int i = 0 ; i < m ; i++) {
		// for every note that a person give
		for(int j = 0 ; j < n ; j++) {
			// make value (total notes) for every sushi
			value[i + 1] += g[j][i];
		}
	}

	vector<int> w(m + 1);
	for(int i = 1 ; i <= m ; i++) {
		w[i] = p[i - 1];
	}

	return rucsac(m, x * n, w, value);
}

int task2(int n, int m, int x, vector <int> &p, vector <vector <int> > &g) {
	
	/* double every sushy type */
	vector<int> value(2 * m + 1);

	// for every sushi type
	for(int i = 0 ; i < m ; i++) {
		// for every note that a person give
		for(int j = 0 ; j < n ; j++) {
			// make value (total notes) for every sushi
			value[i + 1] += g[j][i];
		}
	}

	vector<int> w(2 * m + 1);
	for(int i = 1 ; i <= m ; i++) {
		w[i] = p[i - 1];
	}

	for(int i = m + 1 ; i <= 2 * m ; i++) {
		value[i] = value[i - m];
		w[i] = w[i - m];
	}

	return rucsac(2 * m, x * n, w, value);
}

int task3(int n, int m, int x, vector <int> &p, vector <vector <int> > &g) {
		/* double every sushy type */
	vector<int> value(2 * m + 1);

	// for every sushi type
	for(int i = 0 ; i < m ; i++) {
		// for every note that a person give
		for(int j = 0 ; j < n ; j++) {
			// make value (total notes) for every sushi
			value[i + 1] += g[j][i];
		}
	}

	vector<int> w(2 * m + 1);
	for(int i = 1 ; i <= m ; i++) {
		w[i] = p[i - 1];
	}

	for(int i = m + 1 ; i <= 2 * m ; i++) {
		value[i] = value[i - m];
		w[i] = w[i - m];
	}

	return rucsac2(2 * m, x * n, w, value, n);
}

int main() {
	freopen("sushi.in", "r", stdin);
	freopen("sushi.out", "w", stdout);

	int task;  // task number

	int n;  // number of friends
	int m;  // number of sushi types
	int x;  // how much each of you is willing to spend

	vector <int> prices;  // prices of each sushi type
	// the grades you and your friends gave to each sushi type
	vector <vector <int> > grades;

	cin >> task;
	cin >> n >> m >> x;

	prices.assign(m, 0);
	grades.assign(n, vector <int> (m, 0));

	// price of each sushi
	for(int i = 0; i < m; ++i) {
		cin >> prices[i];
	}

	// each friends rankings of sushi types
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			cin >> grades[i][j];
		}
	}

	int ans = -1;

	switch(task) {
		case 1:
			ans = task1(n, m, x, prices, grades);
			break;
		case 2:
			ans = task2(n, m, x, prices, grades);
			break;
		case 3:
			ans = task3(n, m, x, prices, grades);
			break;
		default:
			cout << "wrong task number" << endl;
	}

	cout << ans << endl;

	return 0;
}
