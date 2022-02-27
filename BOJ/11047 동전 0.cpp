// 11047 동전 0
// https://www.acmicpc.net/problem/11047
/*
    그리디 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - k원을 만드는데 필요한 동전 개수의 최솟값을 구하기 위해서는, 입력된 동전 중 가치가 가장 큰 동전부터 사용한다면 만들 수 있다.
    100원을 만들기 위해서는 10원 10개, 50원 2개, 100원 1개로 가장 큰 동전을 먼저 사용하게 된다면 구할 수 있는 것을 알 수 있다.
    - 동전의 가치는 오름차순 정렬이 되어 있으므로, 가장 뒤의 값부터 확인.
    - 만약 확인중인 i번째 동전의 가치 v[i]를 이용해 k를 나눌 수 있다면, 나머지 연산을 이용해 사용 횟수를 구한 후 ans에 저장.
    또한, 사용된 값만큼 k에서 줄여준다.
    입력된 동전을 모두 확인하며 위 과정을 반복한 후, 구해진 ans를 출력한다.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 11

int main()
{
    FAST_IO;

    int n, k; // 동전의 종류 n, 원하는 값 k (1 ≤ N ≤ 10, 1 ≤ K ≤ 100,000,000)
    cin >> n >> k;
    int v[MAX]; // 동전의 가치 (1 ≤ Ai ≤ 1,000,000)
    for (int i = 0; i < n; i++)
        cin >> v[i];

    int ans = 0;
    for (int i = n - 1; i >= 0; --i) // i번째 동전의 가치 확인
        if (k / v[i])
            ans += k / v[i], k %= v[i];

    cout << ans;
}