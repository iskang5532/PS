// 2022-05-06
// 6137 문자열 생성
// https://www.acmicpc.net/problem/6137
/*
    그리디, 투 포인터 (2,0240B, 0ms)
    시간 복잡도: ?
    풀이)
    - 양쪽의 값을 비교하며 답을 구함.
    - 만약 양쪽의 값이 같을 경우, 다음 값을 확인. 이는 두 값이 다를 때까지 혹은 서로 맞물릴 때까지 반복.
    - 양쪽 값을 서로 비교한 후, 더 빠른 쪽의 값을 먼저 없앰.
    etc.) 앞서 값을 연속으로 지우는 풀이를 이용했는데, WA. 반례를 몰라 다른 풀이를 이용
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 2'003

int main()
{
    FAST_IO;

    int n; // 문자열의 길이 (1 ≤ n ≤ 2,000)
    cin >> n;

    char c[MAX];
    for (int i = 0; i < n; i++)
        cin >> c[i];

    string ans;
    int lo = 0, hi = n - 1;
    while (lo <= hi)
    {
        int l = lo, r = hi;
        while (l < r && c[l] == c[r])
            l++, r--;

        if (c[l] <= c[r])
            ans += c[lo], lo++;
        else
            ans += c[hi], hi--;
    }

    for (int i = 0; i < ans.length(); i++)
    {
        cout << ans[i];
        if ((i + 1) % 80 == 0)
            cout << '\n';
    }
}

// 7%
// 6
// zbfcbz

// 18%
// 4
// abba