/* 
 * 2225 합분해
 * DP
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/2225
 * ETC.) DP를 이용한 문제라는 것을 알았기 때문에 종이에 끄적여보고서 규칙을 알아냈다.
 * 만약, 풀이가 DP라는 것을 모르는 상태로 문제를 접했다면, 상당히 오래 걸렸을 거라 생각.
 * 참고: 
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

    // prev는 이전 배열(k-1 or col-1)의 값을, curr는 현재 배열(k)을 의미
    vector<int> prev(n + 1, 0), curr(n + 1, 0);

    for (int col = 1; col <= k; col++)
    {
        prev = curr; // curr값을 갱신하기 전에 prev에 값을 저장함

        curr[0] = 1; // // 맨 앞의 값을 1로 고정
        for (int row = 1; row <= n; row++)
            curr[row] = (curr[row - 1] + prev[row]) % MOD; // 왼쪽 값(row-1) + 위의 값(col-1)이 현재 (col, row)에 위치하는 값이 됨
    }

    cout << curr[n];
}