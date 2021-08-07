/* 
 * 1715 카드 정렬하기
 * priority_queue (우선순위 큐)
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/1715
 * ETC.) 비교 횟수를 구하는 문제이다. 때문에 주의할 점은, 묶음이 하나일 때는 비교할 대상이 없기 때문에 0이다.
 */

#include <iostream>
#include <queue>

using namespace std;

#define endl "\n"

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n; // 100k
    cin >> n;

    // 묶음의 크기 혹은 횟수가 작은 두 값끼리의 더하기를 반복해야 최소 비교 횟수가 나옴
    priority_queue<int, vector<int>, greater<int>> pq; // 묶음의 크기 및 비교 횟수를 오름차순으로 저장
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        pq.push(k);
    }

    int answer = 0; // 비교 횟수
    if (n >= 2)     // 묶음이 2개 이상일 경우
    {
        answer += pq.top(), pq.pop(); // 정렬된 상위값 2개를 빼내어 더함
        answer += pq.top(), pq.pop();
        pq.push(answer); // 상위 두 묶음의 비교 횟수를 저장 (묶음이 3개 이상일 경우에 대한 값)

        while (pq.size() != 1) // 큐에 비교할 묶음이 2개 이상 남아 있는 경우 (= 묶음이 3개 이상. 남은 값 하나는 찌꺼기)
        {
            int _sum = 0;               // 상위 두 값의 비교 횟수를 저장할 변수
            _sum += pq.top(), pq.pop(); // 상위값 2개를 빼내어 더함
            _sum += pq.top(), pq.pop();
            pq.push(_sum);
            answer += _sum; // 이번에 진행한 비교 횟수를 저장
        }
    }

    cout << answer;
}