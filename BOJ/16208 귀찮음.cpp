// 16208 귀찮음
// https://www.acmicpc.net/problem/16208
/*
    그리디 (3,852KB, 48ms)
    시간 복잡도: ?
    풀이)
    - 그리디하게 낮은 값들을 먼저 계산할 경우, 정답을 얻을 수 있음.
    - 입력된 값을 저장할 v와 전체 값을 저장할 sum.
    - v는 오름차순 정렬한 후, 값을 하나씩 빼 막대를 만들어줌.
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 500'003
using ll = long long;

int main()
{
    FAST_IO;

    int n; // 1 ≤ n ≤ 500,000
    cin >> n;
    int v[MAX], sum = 0;
    for (int i = 0; i < n; i++)
        cin >> v[i], sum += v[i];

    sort(v, v + n);

    ll ans = 0;
    for (int i = 0; i < n; i++) // i번째 막대
    {
        sum -= v[i];
        ans += 1LL * sum * v[i];
    }

    cout << ans;
}