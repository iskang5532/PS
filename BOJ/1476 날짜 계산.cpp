// 1476 날짜 계산
// https://www.acmicpc.net/problem/1476
/*
    완전 탐색 (2,020KB, 0ms)
    시간 복잡도: O(k) (= 7980)
    풀이)
    - 입력되는 e, s, m의 값이 크지 않으므로 완전 탐색을 이용해 풀어준다. (모두 최댓값일 경우, 7980번만에 답을 구할 수 있음)
    - 나머지 연산을 이용해 최댓값을 넘지 않게 해준다.
    주의할 점은 e, s, m의 최솟값은 0이 아니므로 값에 -1을 해주며, 출력 시 -1을 없애주기 위해 +1을 해준다.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX_E 15
#define MAX_S 28
#define MAX_M 19

int main()
{
    FAST_IO;

    int e, s, m; // 1 ≤ E ≤ 15, 1 ≤ S ≤ 28, 1 ≤ M ≤ 19
    cin >> e >> s >> m;
    e--, s--, m--;

    for (int y = 0;; y++)
        if ((e == y % MAX_E) && (s == y % MAX_S) && (m == y % MAX_M))
        {
            cout << y + 1;
            break;
        }
}