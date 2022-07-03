// 2022-07-03
// 21600 계단
// https://www.acmicpc.net/problem/21600
/*
    그리디 (2,680KB, 12ms)
    시간 복잡도: ?
    풀이)
    - 히스토그램에서 i번째 영역에서 만들 수 있는 최대 계단 높이를 h[]에 저장한 후, 가장 큰 값을 출력.
    - 계단의 높이는 1씩 높아짐.
    만약 이전 계단의 높이보다 현재 영역의 높이가 더 큰 경우, 계단을 더 쌓을 수 있음.
    만약 이전 계단의 높이보다 현재 영역의 높이가 더 작은 경우, 계단을 더 쌓을 수 없음.
    이는, 현재 영역의 크기가 곧 계단의 높이가 됨. (계단은 높지만, 만들 수 있는 계단의 높이는 현재 영역이 최대이므로)
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 100'003

int main()
{
    FAST_IO;

    int n;
    cin >> n;

    int v[MAX];
    for (int i = 1; i <= n; i++)
        cin >> v[i];

    int ans = 0;
    int h[MAX]{}; // h[i] = k일 때, i에서의 최대 계단 높이는 k (i까지가 아닌, i에서의)
    for (int i = 1; i <= n; i++)
    {
        if (v[i] > h[i - 1]) // 이전 계단의 높이보다 현재 영역이 더 큰 경우
            h[i] = h[i - 1] + 1;
        else
            h[i] = v[i];

        ans = max(ans, h[i]);
    }

    cout << ans;
}