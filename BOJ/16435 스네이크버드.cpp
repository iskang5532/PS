// 2022-11-20
// 16435 스네이크버드
// https://www.acmicpc.net/problem/16435
/*
    그리디, 정렬 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 먹은 만큼 길이가 증가하며, 최대한 많이 먹어야 한다.
    - 높이가 낮은 과일 순으로 먹게 될 경우, 길이가 늘어나며 먹을 수 없었던 과일 또한 먹을 수 있게 된다.
    그러므로, 입력된 과일의 높이를 h[]에 저장 후, 오름차순 정렬하여 앞에서부터 과일을 하나씩 먹어가며 l을 늘려간다.
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 1'003 // max nzx

int main()
{
    FAST_IO;

    int n, l; // 과일의 개수 n(1 ≤ n ≤ 1,000), 스네이크버드의 초기 길이 l(1 ≤ l ≤ 10,000)
    cin >> n >> l;
    int h[MAX]{};
    for (int i = 0; i < n; i++)
        cin >> h[i];

    sort(h, h + n);

    for (int i = 0; i < n; i++)
        if (l >= h[i])
            l++;

    cout << l;
}