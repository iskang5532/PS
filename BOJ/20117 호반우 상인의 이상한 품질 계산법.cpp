// 2022-08-28
// 20117 호반우 상인의 이상한 품질 계산법
// https://www.acmicpc.net/problem/20117
/*
    그리디, 정렬 (2,288KB, 12ms)
    시간 복잡도: ?
    풀이)
    - 입력된 값을 v[]에 저장한 후 정렬.
    - 가장 큰 값 v[r]과 가장 작은 값v[l]을 묶음.
    이때의 중앙값은 v[r]이 되므로 v[r]을 ans에 더함.
    또한, v[l]을 이용하여 중앙값을 구할 시 v[r]보다 더 큰 값을 존재하지 않음.
    이러한 방법으로 v[l+1]과 v[r-1], v[l+2]과 v[r-2], ...를 묶어 최대 중앙값을 구한 후 ans에 저장.
    - 입력된 수의 개수가 홀수일 수 있음. 이때는 v[n/2]의 값은 묶을 수 있는 짝이 없으므로 묶지 않고 단일로 사용.
    etc.) 왜맞
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 100'003 // max n

int main()
{
    FAST_IO;

    int n; // 1 ≤ n ≤ 100,000
    cin >> n;
    int v[MAX];
    for (int i = 0; i < n; i++)
        cin >> v[i];
    sort(v, v + n);

    int ans = 0;
    for (int r = n / 2; r < n; r++)
        ans += 2 * v[r];
    if (n & 1) // 홀수개인 경우
        ans += -v[n / 2];

    cout << ans;
}
