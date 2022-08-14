// 2022-08-11
// 18230 2xN 예쁜 타일링 성공
// https://www.acmicpc.net/problem/18230
/*
    그리디 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력받은 2x1 타일과 2x2타일을 내림차순 정렬.
    - 비딕의 크기에 맞춰 2x2 타일을 최대한 집어넣음. 만약 바닥의 크기가 홀수일 경우, 2x1 타일을 하나 추가.
    - 추가한 2x2 타일의 가장 작은 값과 2x1 타일의 가장 큰 두 값을 비교. (단, 바닥의 크기가 홀수일 경우 2x1은 두 번째 값([1])부터 비교)
    만약 2x1 타일의 합이 더 큰 경우, 2x2 대신 2x1의 두 타일을 사용.
    비교할 2x2 타일 혹은 2x1 타일 두 개가 없거나 2x2 타일이 더 큰 경우 종료.
    - 사용된 2x2 타일과 2x1 타일을 더한 후 출력.
    etc.) 헷갈림
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 2'003 // max n

int main()
{
    FAST_IO;

    int n, a, b; // 크기 n, 2x1 개수 a, 2x2 개수 b (1 ≤ n, a, b ≤ 2000, 2 × b + a ≥ n)
    cin >> n >> a >> b;

    int v1[MAX]{}, v2[MAX]{};
    for (int i = 0; i < a; i++)
        cin >> v1[i];
    for (int i = 0; i < b; i++)
        cin >> v2[i];

    sort(v1, v1 + a, greater<int>());
    sort(v2, v2 + b, greater<int>());

    int l = 0; // 사용하는 2x1 타일의 마지막 위치
    if (n & 1) // 타일의 크기가 홀수일 경우
        l++;

    int pos = n / 2 - 1; // 사용하는 2x2 타일의 마지막 위치
    while (l + 1 < a && pos >= 0)
    {
        if (v2[pos] < v1[l] + v1[l + 1]) // 2x1 타일 두 개가 더 큰 경우
            pos--, l += 2;
        else
            break;
    }

    int ans = 0;
    for (int i = 0; i < l; i++)
        ans += v1[i];
    for (int i = 0; i <= pos; i++)
        ans += v2[i];

    cout << ans;
}

// input:
// 2 2 2
// 100 100
// 100 100
// ans: 200

// input:
// 4 3 2
// 10 10 10
// 3 3
// ans: 23