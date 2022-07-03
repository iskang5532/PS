// 2022-06-28
// 9237 이장님 초대
// https://www.acmicpc.net/problem/9237
/*
    그리디 (2,288KB, 12ms)
    시간 복잡도: ?
    풀이)
    - 가장 빠르게 묘목이 다 자라는 날짜를 구하기 위해서는 늦게 걸리는 묘목을 먼저 심으면 된다.
    - 입력된 묘목의 자라는 기간을 t[]에 저장한 후, 내림차순 정렬을 한다.
    이후, 묘목을 심는 날은 하루를 소모하므로, 묘목을 심을 때마다 해당 묘목이 다 자라게 되는 날을 늘려준다.
    - 묘목을 구입한 날이 1일째이며 묘목을 심는데 1일이 필요하다. 즉, 해당 나무가 다 자라게 되는 날짜는 ti + 2이다.
 */

#include <iostream>
#include <algorithm>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 100'003

int main()
{
    FAST_IO;

    int n; // 묘목의 수 (1 ≤ n ≤ 100,000)
    cin >> n;
    int t[MAX]; // 나무가 다 자라는데 걸리는 시간 (1 ≤ ti ≤ 1,000,000)
    for (int i = 0; i < n; i++)
        cin >> t[i];

    sort(t, t + n, greater<int>());
    int ans = 0;
    for (int i = 0; i < n; i++)
        ans = max(ans, t[i] + i + 2);

    cout << ans;
}