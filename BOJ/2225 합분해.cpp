/* 
 * 2225 �պ���
 * DP
 * �ð� ���⵵: ?
 * ����: https://www.acmicpc.net/problem/2225
 * ETC.) DP�� �̿��� ������� ���� �˾ұ� ������ ���̿� ���������� ��Ģ�� �˾Ƴ´�.
 * ����, Ǯ�̰� DP��� ���� �𸣴� ���·� ������ ���ߴٸ�, ����� ���� �ɷ��� �Ŷ� ����.
 * ����: 
 */

#include <iostream>
#include <vector>

using namespace std;

#define endl "\n"
#define MAX 200 + 1
#define MOD 1000000000

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, k; // 1 <= 200
    cin >> n >> k;

    // prev�� ���� �迭(k-1 or col-1)�� ����, curr�� ���� �迭(k)�� �ǹ�
    vector<int> prev(n + 1, 0), curr(n + 1, 0);

    for (int col = 1; col <= k; col++)
    {
        prev = curr; // curr���� �����ϱ� ���� prev�� ���� ������

        curr[0] = 1; // // �� ���� ���� 1�� ����
        for (int row = 1; row <= n; row++)
            curr[row] = (curr[row - 1] + prev[row]) % MOD; // ���� ��(row-1) + ���� ��(col-1)�� ���� (col, row)�� ��ġ�ϴ� ���� ��
    }

    cout << curr[n];
}