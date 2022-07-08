// 2022-07-07
// 12915 대회 개최
// https://www.acmicpc.net/problem/12915
/*
    그리디 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력된 em과 mh중 더 작은 값을 우선으로 옮김.
    또한, em과 mh와 인접한 두 값을 중 더 작은 값에 우선으로 값을 옮김.
    주의할 점은, 인접한 두 값 또한 같을 경우, 외곽에 있는 값(e or h)에 옮김.
    - em 혹은 mh를 다 옮겼을 경우, 나머지 한쪽 또한 위와 같이 옮김.
    - e, m, h를 하나씩 감소시키며 카운팅.
    etc.) 이분탐색?? ㄴㅇㄱ
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    int e, em, m, mh, h; // (0 ≤ e, em, m, mh, h ≤ 100,000)
    cin >> e >> em >> m >> mh >> h;

    while (em && mh)
    {
        if (em > mh)
            (e <= m ? e++ : m++), em--; // 외곽을 먼저 채움
        else
            (h <= m ? h++ : m++), mh--;
    }
    while (em--)
        (e < m ? e++ : m++); // == (e <= m)
    while (mh--)
        (h < m ? h++ : m++);

    int ans = 0;
    while (e-- && m-- && h--)
        ans++;

    cout << ans;
}

// 3 3 1 5 9    6
// 9 1 1 100 8     10