// 2022-06-30
// 2785 체인
// https://www.acmicpc.net/problem/2785
/*
    그리디 (3,852KB, 80ms)
    시간 복잡도: ?
    풀이)
    - 최소한의 고리를 이용해야 함. 이를 위해, 묶을 수 있는 고리의 개수를 최소로 만듦.
    즉, 고리를 사용함으로 인하여 묶어야 할 고리의 개수가 줄도록 만듦.
    - 입력된 체인을 v에 저장한 후 오름차순 정렬.
    - 작은 체인의 위치를 l, 긴 체인의 위치를 r.
    - l의 고리를 하나 소모하여 r과 인접한 체인을 묶음.
    고리 개수 v[l]--, 묶을 체인의 위치 r--, 사용한 고리의 개수 ans++.
    이후 모든 체인이 묶일 때까지 반복.
 */

#include <iostream>
#include <algorithm>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 500'003 // max n

int main()
{
    FAST_IO;

    int n;
    cin >> n;

    int v[MAX];
    for (int i = 0; i < n; i++)
        cin >> v[i];
    sort(v, v + n);

    int ans = 0;
    for (int l = 0, r = n - 1; l < r;)
    {
        v[l]--, r--, ans++; // 고리 하나를 이용
        if (v[l] == 0)
            l++;
    }

    cout << ans++;
}