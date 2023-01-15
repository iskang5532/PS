// 2023-01-14
// 27159 노 땡스!
// https://www.acmicpc.net/problem/27159
/*
    구현 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 첫 번째 점수의 합을 저장할 ans.
    - i+1의 값부터 확인.
    만약 이전 값 i와의 격차가 1이 아닌 경우, 새로운 그룹이 시작됐으므로 i+1의 값을 ans에 저장.
    - v[0]은 항상 새로운 그룹의 가장 작은 값이므로 ans에 저장.
    - 하나의 카드만으로 그룹을 이룰 수 있음에 주의.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 35

int main()

{
    FAST_IO;

    int n; // 카드의 개수 (1 ≤ n ≤ 33)
    cin >> n;
    int v[MAX]{};
    for (int i = 0; i < n; i++)
        cin >> v[i];

    int ans = v[0];
    for (int i = 1; i < n; i++)
        if (v[i] - 1 == v[i - 1])
            continue;
        else
            ans += v[i];
    cout << ans;
}