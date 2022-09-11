// 2022-09-08
// 1758 알바생 강호
// https://www.acmicpc.net/problem/1758
/*
    그리디, 정렬 (2,288KB, 12ms)
    시간 복잡도: ?
    풀이)
    - 커피를 늦게 받는 손님이 주는 팁은 음수가 될 수 없다.
    즉, 낮은 팁을 주는 사람을 최대한 늦게 받아서 음수가 되어야 할 팁을 0으로 만들어 이득을 만든다.
    - 입력된 수를 v[]에 저장한 후, 내림차순 정렬.
    이후 v[0]부터 v[n-1]까지 순서를 제외한 팁을 ans에 저장한다. 단, 순서를 제외한 팁이 0 이하일 경우 0을 저장한다.
    - 주의할 점은, 더한 값이 int형 범위를 벗어날 수 있다.
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using ll = long long;
#define MAX 100'003 // max n

int main()
{
    FAST_IO;

    int n; // 사람의 수 (1 ≤ n ≤ 100,000)
    cin >> n;
    int v[MAX];
    for (int i = 0; i < n; i++)
        cin >> v[i];

    sort(v, v + n, greater<>());

    ll ans = 0;
    for (int i = 0; i < n; i++)
        ans += max(v[i] - i, 0);

    cout << ans;
}
