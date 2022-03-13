// 2961 도영이가 만든 맛있는 음식
// https://www.acmicpc.net/problem/2961
/*
    완전 탐색 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - n의 크기가 최대 10이며, 완전 탐색을 이용할 경우 O(2^10)이다.
    - 적절한 개수의 재료를 선택하여 신맛과 쓴맛을 구해준 후, 차이를 ans에 저장한다. (단, 이전 ans보다 최솟값이어야 함)
    1개부터 n개까지 모든 재료를 선택하여 ans를 구한 후 출력해준다.
 */

#include <iostream>
#include <algorithm> // abs

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define INF 0x7fffffff
#define MAX 13

struct pii
{
    int s, b; // 신맛, 쓴맛
};

int main()
{
    FAST_IO;

    int n; // 1 ≤ N ≤ 10
    cin >> n;
    pii v[MAX];
    for (int i = 0; i < n; i++)
        cin >> v[i].s >> v[i].b;

    int ans = INF;
    for (int bit = 1; bit < 1 << n; bit++)
    {
        int s = 1, b = 0; // 1 ≤ 1,000,000,000
        for (int i = 0; i < n; i++)
            if (bit & 1 << i)
                s *= v[i].s, b += v[i].b;

        ans = min(ans, abs(s - b));
    }

    cout << ans;
}