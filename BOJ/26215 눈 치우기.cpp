// 2022-12-11
// 26215 눈 치우기
// https://www.acmicpc.net/problem/26215
/*
    sol.1) 그리디, 투 포인터? (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 가장 큰 값과 가장 작은 값을 찾은 후, -1씩 수행.
    만약, 남은 수가 하나일 경우 남아 있는 값만 -1.
    - 항상 가장 큰 값과 가장 작은 값을 사용해야 하므로, 값을 제거할 때마다 정렬함.
    etc.) 여러 풀이를 이용했지만 엄청난 수의 WA. 결국 무지성 구현으로 성공
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 103 // max n

int main()
{
    FAST_IO;

    int n;
    cin >> n;
    int v[MAX]{};
    for (int i = 0; i < n; i++)
        cin >> v[i];

    sort(v, v + n);

    int ans = 0;
    for (int l = 0, r = n - 1; l <= r; ans++)
    {
        if (l == r)
            v[l]--;
        else
            v[l]--, v[r]--;

        sort(v, v + n);
        while (l < n && v[l] == 0)
            l++;
    }

    cout << (ans <= 1440 ? ans : -1);
}

/*
    sol.2) 수학 (2,020KB, 0ms)
    시간 복잡도: ?
    참고)
    - 수식: https://gall.dcinside.com/mgallery/board/view/?id=ps&no=30748&page=1
 */

#include <iostream>
#include <cmath> // ceil

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 103 // max n

int main()
{
    FAST_IO;

    int n;
    cin >> n;
    int mx = 0, sum = 0;
    for (int i = 0, k; i < n; i++)
        cin >> k, mx = max(mx, k), sum += k;

    int ans = max(mx, (int)ceil((double)sum / 2));
    cout << (ans <= 1440 ? ans : -1);
}