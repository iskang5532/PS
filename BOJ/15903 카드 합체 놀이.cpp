// 2022-08-16
// 15903 카드 합체 놀이
// https://www.acmicpc.net/problem/15903
/*
    그리디, 우선순위 큐 (2,160KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 연산 후에 합한 값이 최솟값이 되어야 하는 문제.
    - 연산으로 만드는 값을 최솟값으로만 만든다면, 최종적으로 최솟값의 합이 나온다.
    - 값이 작은 두 개의 값을 계속해서 빼와야 하므로, 우선순위 큐 pq를 이용한다.
    - m번만큼 pq에서 두 개의 값 a, b를 꺼낸다.
    이후, a + b의 값을 pq에 두 번 넣는다.
    - m번의 연산이 완료된 이후, pq의 모든 값을 더한 후 출력한다.
    - 주의할 점은, 입력된 값의 크기가 최대 10e6이며 횟수가 최대 15,000이다. 즉, int형의 범위를 벗어날 수 있다.
    etc.) 생각보다 빠르게 풀림.
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using ll = long long;

priority_queue<ll, vector<ll>, greater<ll>> pq; // 1 ≤ k ≤ 1,000,000

int main()
{
    FAST_IO;

    int n, m; // 카드의 개수 n(2 ≤ n ≤ 1,000), 합체 횟수 m(0 ≤ m ≤ 15×n)
    cin >> n >> m;
    for (int i = 0, k; i < n; i++)
        cin >> k, pq.push(k);

    ll a, b;
    while (m--)
    {
        a = pq.top(), pq.pop(); // 가장 작은 두 값을 꺼냄
        b = pq.top(), pq.pop();

        pq.push(a + b), pq.push(a + b);
    }

    ll ans = 0;
    while (pq.size())
        ans += pq.top(), pq.pop();
    cout << ans;
}