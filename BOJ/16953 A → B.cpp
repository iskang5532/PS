// 16953 A → B
// https://www.acmicpc.net/problem/16953
/*
    그리디 (2,156KB, 4ms)
    시간 복잡도: ?
    풀이)
    - 큐에 저장된 값에 두 가지 연산을 이용하여 b까지 가는데 필요한 연산 횟수 cnt를 구함.
    - 첫 큐에 들어갈 값은 a.
    큐에 저장된 값 k에 두 가지 연산을 수행.
    만약 연산된 값 next_k가 b 이하인 경우, next_k와 k까지의 연산 횟수 + 1을 큐에 넣음.
    만약 값 k가 b와 같을 경우, cnt를 출력.
    만약 큐에 저장된 모든 값을 사용하였음에도 b를 만들지 못한 경우, -1을 출력.
    etc.) cnt를 배열로 따로 만들어 풀어 봤으나, segfault 및 bad alloc..
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define INF 98754321
using ll = long long;
using pii = pair<int, int>; // k, cnt

ll Push_Back(const int k, const char c) { return stoll(to_string(k) + c); } // 1을 k의 가장 오른쪽에 추가

int main()
{
    FAST_IO;

    int a, b; // 1 ≤ A < B ≤ 10^9
    cin >> a >> b;

    int ans = INF;
    queue<pii> q;
    q.push({a, 0}); // {k, cnt}: 수 k까지의 연산 횟수는 cnt
    while (q.size())
    {
        auto [k, cnt] = q.front();
        q.pop();
        if (k == b)
        {
            ans = cnt;
            break;
        }

        { // 1. k * 2
            int next_k = k << 1;
            if (next_k <= b)
                q.push({next_k, cnt + 1});
        }
        { // 2. k.push_back('1')
            ll next_k = Push_Back(k, '1');
            if (next_k <= b)
                q.push({next_k, cnt + 1});
        }
    }

    cout << (ans == INF ? -1 : ans + 1); // 연산의 최솟값에 1을 더한 값
}