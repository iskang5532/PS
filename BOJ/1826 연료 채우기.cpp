// 1826 연료 채우기
// https://www.acmicpc.net/problem/1826
/*
    그리디, 우선순위 큐 (2,336KB, 4ms)
    시간 복잡도: ?
    풀이)
    1. 주어진 연료를 이용하여 도달할 수 있는 주유소를 구하여 우선순위 큐 pq에 저장.
    pq는 연료의 양을 기준으로 내림차순 정렬.
    2. pq에 저장된 주유소 중 연료의 양이 가장 많은 주유소를 고른 후, 연료를 충전.
    해당 주유소에서 연료를 충전했으므로 cnt++.
    3. 충전된 연료를 이용해 다시 1.부터 시작.
    - 만약 연료를 이용하여 도달할 수 있는 주유소가 없을 경우, 목적지까지 도달할 수 없으므로 -1을 출력.
    참고)
    - 이론: https://travelbeeee.tistory.com/492
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

struct pii
{
    int l, p; // 거리 l, 연료 p
};

struct greater_l // 거리를 기준으로 오름차순 정렬
{
    bool operator()(const pii &p1, const pii &p2) { return p1.l > p2.l; }
};
struct less_p // 연료량을 기준으로 내림차순
{
    bool operator()(const pii &p1, const pii &p2) { return p1.p < p2.p; }
};

int main()
{
    FAST_IO;

    int n; // 주유소의 개수 (1 ≤ N ≤ 10,000)
    cin >> n;
    priority_queue<pii, vector<pii>, greater_l> pq; // 주유소를 거리 기준 오름차순 정렬하여 저장
    for (int i = 0; i < n; i++)
    {
        int a, b; // 시작점에서 주유소까지의 거리 a(1 ≤ a ≤ 1,000,000), 주유소의 남은 연료 b(1 ≤ b ≤ 100)
        cin >> a >> b;
        pq.push({a, b});
    }
    int l, p; // 마을까지의 거리 l(1 ≤ l ≤ 1,000,000), 기존 연료의 양 p(1 ≤ p ≤ 1,000,000)
    cin >> l >> p;

    int cnt = 0;
    priority_queue<pii, vector<pii>, less_p> pq2; // 현재 방문할 수 있는 주유소를 저장하며, 연료의 양 기준 내림차순 정렬
    while (p < l)
    {
        while (pq.size() && p >= pq.top().l) // 현재 연료로 방문할 수 있는 모든 주유소를 탐색
            pq2.push(pq.top()), pq.pop();

        if (pq2.empty()) // 방문할 수 있는 주유소가 없을 경우
        {
            cout << "-1";
            return 0;
        }

        p += pq2.top().p, pq2.pop(); // 기름 충전
        cnt++;
    }

    cout << cnt;
}