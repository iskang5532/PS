/* 
 * 11726 2xn 타일링
 * 행렬
 * 시간 복잡도: O(logN)
 * 문제: https://www.acmicpc.net/problem/11726
 * ETC) 4~5까지 세어봤을 때, 피보나치 수열의 형태로 증가한다는 사실을 알 수 있음
 */

#include <iostream>

using namespace std;

#define endl "\n"
#define MAX 1000 // 최대 n

const int mod = 10007;

struct matrix
{
    int arr[2][2] = {0};

    friend matrix operator*(const matrix &m1, const matrix &m2)
    {
        matrix ret;

        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
            {
                for (int k = 0; k < 2; k++)
                    ret.arr[i][j] += m1.arr[i][k] * m2.arr[k][j];
                ret.arr[i][j] %= mod; // 10007을 나눈 값을 저장
            }

        return ret;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n;
    cin >> n;
    n++; // 일반적인 피보나치의 경우, [2] == 1이지만, 이 문제는 [2] == 2이므로 +1을 해주어 템포를 맞춰줌

    matrix answer = {{{1, 0}, {0, 1}}};
    matrix m = {{{1, 1}, {1, 0}}};

    if (n <= 1)
        cout << n << endl;
    while (n)
    {
        if (n & 1)
            answer = answer * m;

        m = m * m;
        n /= 2;
    }

    cout << answer.arr[0][1] << endl;
}