// 2022-07-04
// 15889 호 안에 수류탄이야!!
// https://www.acmicpc.net/problem/15889
/*
    그리디 (2,132KB, 8ms)
    시간 복잡도: ?
    풀이)
    - i번에게 수류탄이 도착할 수 있다면, i번의 위치 + 사거리가 다음 수류탄의 최대 거리이다.
    이는, 이 안에 있는 인원은 수류탄을 받을 수 있다는 것이다. 이들 또한 위와 같이 다음 인원에게 수류탄을 넘길 수 있다.
    이를 반복하여 마지막 전우에게 수류탄을 넘길 수 있는지를 확인한다.
    - 수류탄을 넘길 수 있는 가장 먼 위치를 mx에 저장.
    - 욱제를 시작으로 마지막 전우에게 수류탄을 넘길 수 있는지를 확인.
    만약 마지막 전우의 위치보다 mx가 큰 경우, 마지막 전우는 수류탄을 받을 수 있음.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 30'003 // max n

int main()
{
    FAST_IO;

    int n;
    cin >> n;

    int pos[MAX], power[MAX];
    for (int i = 0; i < n; i++)
        cin >> pos[i];
    for (int i = 0; i < n - 1; i++)
        cin >> power[i];

    int mx = pos[0]; // 수류탄을 넘길 수 있는 가장 먼 위치
    for (int cur = 0; cur < n - 1; cur++)
        if (pos[cur] <= mx) // cur번째 인원에게 수류탄이 도착할 수 있는가
            mx = max(mx, pos[cur] + power[cur]);

    cout << (pos[n - 1] <= mx ? "권병장님, 중대장님이 찾으십니다" : "엄마 나 전역 늦어질 것 같아");
}