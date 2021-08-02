/* 
 * 17069 ���̺� �ű�� 2
 * DP
 * �ð� ���⵵: ?
 * ����: https://www.acmicpc.net/problem/17069
 * ETC) �밢�� �������� �� �� ������ �ֺ� ������ ���� ������ �ȵǸ�, Ƚ���� long long ����� �ϸ�, ���� ������ ���� ���� ����. (���ݴ� �� ���� �ɸ�)
 */

#include <iostream>
#include <vector>

using namespace std;

#define endl "\n"
#define MAX 32 + 1 // �� ĭ�� �߰��Ͽ� Ž�� ������ ��Ÿ�� ������ ������
#define WALL 1

long long solution(const vector<vector<int>> &arr, const int n)
{
    // vector<vector<vector<long long>>> visited(n + 1, vector<vector<long long>>(n + 1, vector<long long>(n + 1, 0)));

    // visited[n][m][k]�̸� (col, row)�� ��, ��ġ (n, m)���� k ���·� �̵���ų �� �ִ� Ƚ��.
    // k = 0�� ���� ����(��), k = 1�� ���� �밢��(\),  k = 2�� ���� ����(|) ������ ������
    long long visited[MAX][MAX][MAX] = {0};
    visited[0][1][0] = 1; // ó�� �����ϴ� ������.

    // ��� ��ġ�� ���ƴٴϸ� ���� ��ġ�������� ���� ��ġ�� �̵��� �� �ִ� ����� ���� �ѱ�
    for (int col = 0; col < n; col++)
        for (int row = 0; row < n; row++)
        {
            if (arr[col][row] == WALL) // ���� ���� Ȯ������ ���� ���� ��� (= �̵� ���� ����� ���� �ѱ�� �� ��)
                continue;

            long long cnt_0 = visited[col][row][0], // ���� ��ġ�������� k�� ���·� ������ �� �ִ� ����� ��
                cnt_1 = visited[col][row][1],
                      cnt_2 = visited[col][row][2];

            visited[col][row + 1][0] += cnt_0; // �� -> ��

            visited[col][row + 1][0] += cnt_1; // \ -> ��
            visited[col + 1][row][2] += cnt_1; // \ -> |

            visited[col + 1][row][2] += cnt_2; // | -> |

            if (arr[col][row + 1] == WALL || arr[col + 1][row + 1] == WALL || arr[col + 1][row] == WALL) // �밢�� �������� �־� �ϴµ� ���� ������ ���
                continue;
            visited[col + 1][row + 1][1] += cnt_0; // �� -> \'
            visited[col + 1][row + 1][1] += cnt_1; // \ -> \'
            visited[col + 1][row + 1][1] += cnt_2; // | -> \'
        }

    if (arr[n - 1][n - 1] == WALL) // ���� ���� ������ ���� ��� (= �̵� ������ ����� ����)
        return 0;
    else // �̵��� ������ ��� ���µ��� �� ������
        return (visited[n - 1][n - 1][0] + visited[n - 1][n - 1][1] + visited[n - 1][n - 1][2]);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n;
    cin >> n;

    vector<vector<int>> arr(MAX + 1, vector<int>(MAX + 1));
    for (int col = 0; col < n; col++)
        for (int row = 0; row < n; row++)
            cin >> arr[col][row];

    cout << solution(arr, n);
}