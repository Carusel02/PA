#include <iostream>
#include <vector>

using namespace std;

const int mod = 1000000007;

int type1(int x, int y) {
    // Compute the number of type 1 signals.

	/* numbers of bits */
	int n = x + y;
	/* numbers of bits of 1 */
	int k = y;
	/* error */
	if (y > x + y)
		return -1;

	/* create dp matrix (n + 1) x (y + 1) */
	vector< vector<int> > dp(n + 1, vector<int>(y + 1, 0));

	/* base case */

	/* if k = 0 => dp[n][0] = 1 ; 0000000000...0 */
	dp[n][0] = 1;

	/* if n = 1 => dp[1][0] = 1 dp[1][1] = 1 */
	dp[0][0] = 0;
	dp[1][0] = 1;
	dp[1][1] = 1;
	dp[2][0] = 1;
	dp[2][1] = 2;
	dp[2][2] = 0;

	switch (n) {
		case 0:
			/* if we have length 0 , return 0 */
			return 0;
			break;
		case 1:
			/* if we have length 1 , return 1 */
			return 1;
			break;
		default:
			/* compute actual numbers of signals */
			for(int i = 3 ; i <= n ; i++) {
				/* for k = 0 of 1 it s only 1 number (00....0000) */
				dp[i][0] = 1;
				for(int j = 1 ; j <= k ; j++)
					dp[i][j] = (dp[i - 1][j] % mod + dp[i - 2][j - 1] % mod) % mod;
			}

			return dp[n][k];
			break;
	}

    return 0;
}

int type2(int x, int y) {
    // Compute the number of type 2 signals.

	/* number of bits */
	int n = x + y;
	/* number of bits of 1 */
	int k = y;
	/* error */
	if(y > x + y)
		return -1;

	/* create dp matrix (n + 1) x (y + 1) */
	vector< vector<int> > dp(n + 1, vector<int>(y + 1, 0));

	/* base case */

	/* if k = 0 => dp[n][0] = 1 ; 0000000000...0 */
	dp[n][0] = 1;

	/* if n = 1 => dp[1][0] = 1 dp[1][1] = 1 */
	dp[0][0] = 0;
	dp[1][0] = 1;
	dp[1][1] = 1;
	dp[2][0] = 1;
	dp[2][1] = 2;
	dp[2][2] = 1;
	dp[3][0] = 1;
	dp[3][1] = 3;
	dp[3][2] = 3;
	dp[3][3] = 0;

	switch (n) {
		case 0:
			/* if we have length 0 , return 0 */
			return 0;
			break;
		case 1:
			/* if we have length 1 , return 1 */
			return 1;
			break;
		default:
			/* compute actual numbers of signals */
			for (int i = 4 ; i <= n ; i++) {
				dp[i][0] = 1;
				for (int j = 1 ; j <= k ; j++)
						dp[i][j] = ((dp[i - 1][j] % mod + dp[i - 2][j - 1] % mod) % mod +
																	dp[i - 3][j - 2] % mod) % mod;
			}

			return dp[n][k];
			break;
	}
    return 0;
}

int main() {
    freopen("semnale.in", "r", stdin);
	freopen("semnale.out", "w", stdout);

	int sig_type, x, y;

	cin >> sig_type >> x >> y;

    switch (sig_type) {
		case 1:
			cout << type1(x, y);;
			break;
		case 2:
			cout << type2(x, y);
			break;
		default:
			cout << "wrong task number" << endl;
	}

    return 0;
}
