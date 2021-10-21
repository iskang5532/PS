/*
    10830 행렬 제곱
    분할 정복을 이용한 거듭제곱 (2,024KB, 0ms)
    시간 복잡도: O(logN)
    문제: https://www.acmicpc.net/problem/10830
    etc.)
    - 주어진 제곱수 b를 하나 하나씩 할 경우 TLE.
    그러므로 b가 2^n꼴일 때를 이용. (거듭제곱 이용)
    - 입력된 행렬 A를 제곱시키며 b를 반으로 나눔. (= A*A, 한 번의 제곱을 matrix에 저장)
    만약 b가 홀수일 경우, 행렬 A와 정답을 저장할 행렬 ans를 곱함. (ans*A, 현재까지의 제곱 횟수가 저장된 matrix를 이용)
 */

#include <iostream>
#include <vector>

using namespace std;

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MOD 1000
typedef long long ll;

void matrix_mul(vector<vector<int>> &m1, const vector<vector<int>> &m2, int n)
{
    vector<vector<int>> ret(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
                ret[i][j] += m1[i][k] * m2[k][j];
            ret[i][j] %= MOD;
        }

    m1 = ret;
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    ll n, b; // 행렬의 크기 (2 ≤ N ≤  5, 1 ≤ B ≤ 10^11)
    cin >> n >> b;
    vector<vector<int>> matrix(n, vector<int>(n));
    for (auto &row : matrix)
        for (auto &col : row)
            cin >> col;
    vector<vector<int>> ans(n, vector<int>(n, 0)); // 정답을 저장할 행렬 (default: 단위 행렬)
    for (int i = 0; i < n; i++)
        ans[i][i] = 1;

    while (b)
    {
        if (b & 1)
            matrix_mul(ans, matrix, n); // ans * A

        matrix_mul(matrix, matrix, n); //  A * A
        b >>= 1;
    }

    for (auto &row : ans)
    {
        for (auto &col : row)
            cout << col << " ";
        cout << endl;
    }
}