// 2022-08-14
// 2839 설탕 배달
// https://www.acmicpc.net/problem/2839
/*
    그리디 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 값이 최소가 되기 위해서는 5kg을 최대한 많이 이용해야 한다.
    그러므로 먼저 5kg을 최대한 많이 사용해본다.
    - 3kg으로 맞출 수 있는 무게가 될 때까지 5kg을 하나씩 뺀다.
    만약 5kg을 모두 뺐음에도 3kg으로 맞출 수 없을 경우, -1을 출력.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    int n; // 3 ≤ N ≤ 5000
    cin >> n;

    int ans = 0;
    ans += n / 5, n %= 5; // 우선 5kg으로 맞춤
    while (n && ans)
    {
        if (n % 3 == 0) // 3kg으로 맞출 수 있을 경우
            break;

        n += 5, ans--; // 5kg을 하나씩 뺌
    }

    if (ans == 0 && n % 3 != 0) // 남아 있는 값을 3kg으로 맞출 수 없을 경우
        cout << -1;
    else
        cout << ans + n / 3;
}