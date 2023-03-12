// 2023-03-12
// 1145 적어도 대부분의 배수
// https://www.acmicpc.net/problem/1145
/*
    완전 탐색 (2,020KB, 16ms)
    시간 복잡도: ?
    풀이)
    - 1부터 값을 정한 후, 입력된 다섯 개의 값 중 적어도 세 개의 배수인 값을 확인.
    - 세 개의 배수이므로, 최댓값은 100^3.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    int v[5];
    for (int i = 0; i < 5; i++)
        cin >> v[i];

    int ans = 0;
    for (int num = 1; num <= 1'000'000; num++)
    {
        int cnt = 0; // 유효한 개수
        for (int i = 0; i < 5; i++)
            if (num % v[i] == 0) // 배수인 경우
                cnt++;

        if (cnt >= 3) // 세 개 이상인 경우
        {
            ans = num;
            break;
        }
    }

    cout << ans;
}