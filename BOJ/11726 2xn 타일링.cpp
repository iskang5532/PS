/* 
 * 11726 2xn Ÿ�ϸ�
 * ���
 * �ð� ���⵵: O(logN)
 * ����: https://www.acmicpc.net/problem/11726
 * ETC) 4~5���� ������� ��, �Ǻ���ġ ������ ���·� �����Ѵٴ� ����� �� �� ����
 */

#include <iostream>

using namespace std;

#define endl "\n"
#define MAX 1000 // �ִ� n

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
                ret.arr[i][j] %= mod; // 10007�� ���� ���� ����
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
    n++; // �Ϲ����� �Ǻ���ġ�� ���, [2] == 1������, �� ������ [2] == 2�̹Ƿ� +1�� ���־� ������ ������

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