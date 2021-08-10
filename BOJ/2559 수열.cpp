/* 
 * 2559 수열
 * Sliding Window
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/2559
 */

#include <iostream>
#include <queue>

using namespace std;

#define endl "\n"

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, k;
    cin >> n >> k;
    int sum = 0;  // k개의 합
    queue<int> q; // 입력된 값들을 저장 (슬라이딩 윈도우를 옮길 때 값을 제거해야 하는데, 그 때 사용)
    for (int i = 0; i < k; i++)
    {
        int num;
        cin >> num;

        sum += num; // k개의 값을 먼저 저장함
        q.push(num);
    }

    int answer = sum;           // 우선 k개의 값의 합이 최대라고 가정 (이후 윈도우가 움직일 때마다 조건을 만족 시 갱신)
    for (int i = k; i < n; i++) // 나머지 n - k개에 대해 입력을 받음
    {
        int num;
        cin >> num;

        sum += num, q.push(num);    // 윈도우가 한 칸 움직여 다음 출력을 더해줌
        sum += -q.front(), q.pop(); // 윈도우가 한 칸 움직여 뒷 값을 제거해줌

        answer = max(answer, sum); // 현재 값과 비교해 최댓값을 갱신
    }
    cout << answer;
}