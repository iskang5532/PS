/*
    1826 연료 채우기
    그리디, 우선순위 큐 (2,336KB, 4ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/1826
    etc.) DFS 식으로 풀려 했으나, TLE를 예상하고서 다른 방식을 생각. 그러나 모르겠어서 인터넷 참고.. 어려웠음.
    1) 주어진 연료를 이용해 도달할 수 있는 주유소를 구함.
    2) 주유소에서 연료를 가장 많이 주는 곳을 방문 (= cnt++)
    이후 1번부터 반복. 만약 초기 연료 혹은 충전된 연료가 목적지까지 도달할 수 있는 충분한 양인 경우, cnt 출력 후 종료.
    - 여기서 놀라운 점은, 1, 2, 3지점이 있으며 연료가 오름차순이라고 가정할 때, 3번 방문만으로 목적지에 도달할 수 없는 때도 있다.
    이때 기존에 도달할 수 있는 지점이었던 1, 2를 방문시킴으로 인해 방문 순서가 3-2가 아닌 2-3으로 재구성된다는 점이다.
    그렇기에 3번 방문의 경우와 2-3 방문의 경우와 같은 DFS를 할 필요가 없다.
    참고) 이론 https://travelbeeee.tistory.com/492
 */

#include <iostream>
#include <queue>
#include <algorithm> // sort

using namespace std;

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

struct pii
{
    int a, b; // 위치 a(1 ≤ a ≤ 1M), 충전 가능량 b(1 ≤ b ≤ 100)
};

struct greater_a // a값을 기준으로 오름차순
{
    bool operator()(const pii &p1, const pii &p2) { return p1.a > p2.a; }
};
struct less_b // b값을 기준으로 내림차순
{
    bool operator()(const pii &p1, const pii &p2) { return p1.b < p2.b; }
};

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n; // 주유소의 개수 (1 ≤ N ≤ 10,000)
    cin >> n;
    priority_queue<pii, vector<pii>, greater_a> pq; // 모든 주유소의 위치 (위치 a를 기준으로 오름차순)
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        pq.push({a, b});
    }
    int L, fuel;
    cin >> L >> fuel; // 마을까지의 거리 L(1 ≤ L ≤ 1M), 첫 연료의 양 fuel(1 ≤ fuel ≤ 1,000,000)

    priority_queue<pii, vector<pii>, less_b> pq2; // 현재 연료로 방문할 수 있는 주유소를 저장 (연료 b를 기준으로 내림차순)
    int cnt = 0;
    while (fuel < L) // 현재 연료로 도착 지점까지 갈 수 없는 경우, 탐색
    {
        while (!pq.empty() && fuel >= pq.top().a) // 현재 연료로 방문할 수 있는 모든 주유소 탐색
            pq2.push(pq.top()), pq.pop();

        if (pq2.empty()) // 만약 현재 방문할 수 있는 주유소가 없을 경우 (이는 이전에 모두 방문 또한  포함)
        {
            cout << "-1";
            return 0;
        }
        fuel += pq2.top().b, pq2.pop(); // 방문할 수 있는 가장 많은 연료를 주는 주유소 방문
        cnt++;
    }

    cout << cnt;
}