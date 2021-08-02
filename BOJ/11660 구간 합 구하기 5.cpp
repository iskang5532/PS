/* 
 * 11660 ���� �� ���ϱ� 5
 * DP
 * �ð� ���⵵: ?
 * ����: https://www.acmicpc.net/problem/11660
 * ETC.) �������� �ؿ� �ִ� �˰��� �з����� '���� ��'�̶� ���� ���� ���� ���� ����.
 * ù Ǯ�̴� �� ��ǥ�� �־��� ������ �׿� �´� ������ ���ϴ� ������ Ǯ������, �ð� �ʰ�.
 * �� ��° Ǯ�̴� �Էµ� ��� arr�� �̿��Ͽ� dp�� ����.
 * dp[col][row]�� ��, col���� 0�������� row������ ���� ��Ÿ��.  ex) dp[2][5] == arr[2][0] + arr[2][1] + ... + arr[2][5]
 * �� ��° Ǯ�̴� �� ��° Ǯ�̸� �ٵ������, �Է¹޴� ��İ��� �̿��� ��ٷ� dp�� ���� (���� �ڵ�)
 */

#include <iostream>
#include <vector>

using namespace std;

#define endl "\n"
#define MAX 1024 + 1

int solution(const int dp[][MAX], const int y1, const int x1, const int y2, const int x2)
{
    int answer = 0;
    for (int col = y1; col <= y2; col++)
        answer += (dp[col][x2] - dp[col][x1 - 1]); // x2������ �տ��� x1 - 1������ ���� ���� (= ���ϴ� ����)

    return answer;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, k; // 1 <= N <= 1024, 1 <= M <= 100k
    cin >> n >> k;

    int dp[MAX][MAX] = {0};
    for (int col = 1; col <= n; col++)
        for (int row = 1; row <= n; row++)
        {
            int num;
            cin >> num;
            dp[col][row] = dp[col][row - 1] + num; // ���� dp�� + �Է� ��
        }

    while (k--)
    {
        int y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;
        cout << solution(dp, y1, x1, y2, x2) << endl;
    }
}