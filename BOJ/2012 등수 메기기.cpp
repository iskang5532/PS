// 2022-09-03
// 2012 등수 메기기
// https://www.acmicpc.net/problem/2012
/*
    그리디 (3,852KB, 84ms)
    시간 복잡도: ?
    풀이)
    - 등수를 부여할 때, 예상 등수가 높은 순서대로 값을 부여하게 된다면 불만도의 최소 합을 구할 수 있다.
    - 입력된 예상 등수를 v[]에 저장한 후 오름차순 정렬.
    이후, v[0]부터 v[n-1]까지 1등부터 n등을 부여한다.
    이때 발생하는 불만도인 |v[i] - (i+1)|을 ans에 더한다.
    - 주의할 점은, 불만도의 합이 int형 범위를 넘을 수 있다.
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

    int n; // 학생의 수 (1 ≤ n ≤ 500,000)
    cin >> n;
    int v[MAX];
    for (int i = 0; i < n; i++)
        cin >> v[i];

    sort(v, v + n);

    ll ans = 0;
    for (int i = 0; i < n; i++)
        ans += abs(v[i] - (i + 1));

    cout << ans;
}