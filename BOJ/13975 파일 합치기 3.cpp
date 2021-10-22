/*
    13975 파일 합치기 3
    우선순위 큐 (18,532KB, 708ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/13975
    etc.)
    1) 우선순위 큐를 이용해 입력된 값을 오름차순으로 정렬.
    2) 큐의 앞에서부터 두 개씩 값을 빼내어 더한 값을 저장하며 큐에 넣어 줌.
    3) 큐의 크기가 2 미만이 될 때까지 2번을 반복.
 */

#include <iostream>
#include <queue>

using namespace std;

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define INF 1234567890
typedef long long ll;
typedef pair<int, int> pii;

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int tc;
    cin >> tc;

    while (tc--)
    {
        ll ans = 0;

        int n; // 장의 수 (3 ≤ n ≤ 1M)
        cin >> n;
        priority_queue<ll, vector<ll>, greater<ll>> pq;
        for (int i = 0; i < n; i++)
        {
            int k;
            cin >> k;
            pq.push(k);
        }

        ll a, b, c;
        while (pq.size() >= 2) // 큐의 값이 2개 이상일 때만
        {
            a = pq.top(), pq.pop();
            b = pq.top(), pq.pop();

            c = a + b;
            ans += c, pq.push(c);
        }

        cout << ans << endl;
    }
}