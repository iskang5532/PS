// 13975 파일 합치기 3
// https://www.acmicpc.net/problem/13975
/*
    그리디 (1,8532KB, 760ms)
    시간 복잡도: O(nlogn) (min heap)
    풀이)
    - 가장 작은 두 값을 더하여 답을 구할 수 있는 문제.
    - 항상 최솟값을 사용해야 하므로, 우선순위 큐를 사용해줌.
    - 큐에 존재하는 가장 작은 두 개의 값을 꺼낸 후, 두 파일의 크기 c를 ans에 저장하며 c를 큐에 넣어줌.
    - 주의해야 할 점은, 큐에 존재하는 두 개의 값을 이용해야 하므로, 큐의 크기가 2 이상일 때만 탐색해야 한다.
    참고)
    - 시간 복잡도: https://blog.naver.com/jinhan814/222609762108
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
using ll = long long;

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;
    while (tc--)
    {
        int k; // 소설을 구성하는 장의 수 K(3 ≤ K ≤ 1,000,000)
        cin >> k;
        priority_queue<ll, vector<ll>, greater<ll>> pq; // 수록한 파일의 크기 (1 ≤ vi ≤ 10,000)
        for (int i = 0, x; i < k; i++)
            cin >> x, pq.push(x);

        ll ans = 0;
        ll a, b, c;
        while (pq.size() >= 2)
        {
            a = pq.top(), pq.pop();
            b = pq.top(), pq.pop();

            c = a + b;

            ans += c;
            pq.push(c);
        }

        cout << ans << endl;
    }
}