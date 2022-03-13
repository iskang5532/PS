// 24498 blobnom
// https://www.acmicpc.net/problem/24498
// 애디토리얼: https://docs.google.com/presentation/d/1wNCFroWIV962QsUwcpe2fUHjJ_2BYqJ-UGTVhvp0pJ8
/*
    그리디 (5,804KB, 136ms)
    시간 복잡도: ?
    풀이)
    - 양옆 탑의 높이를 감소시켜 현재 탑의 높이를 올린다. 이는 두 탑 중 하나가 아닌 둘 다 감소하므로, 높일 탑을 이용해 다른 탑을 추가로 높일 수는 없다.
    - 탐색해야 하는 값이 10^6으로 상당히 작다. 그러므로 모든 탑을 탐색하여 가장 높이 높이 수 있는 탑을 탐색한다.
    높일 수 있는 탑의 높이는 양옆 탑의 높이 중 더 작은 높이만큼 해당한다.
    - 주의할 점은, 탐색중인 칸이 첫 번째 혹은 마지막이 되서는 안된다.
    또한, n = 1 혹은 n = 2와 같이 옆이 존재하지 않는 경우는 탑을 더 이상 쌓을 수 없으므로, 기존 탑 중에서 가장 높은 탑의 높이를 출력해줘야 한다.
    이를 위해 입력 과정에서 가장 높은 탑의 높이를 저장한다.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 1'000'003

int main()
{
    FAST_IO;

    int n; // 1 ≤ n ≤ 1,000,000
    cin >> n;
    int v[MAX]; // 1 ≤ vi ≤ 10^9
    int ans = 0;
    for (int i = 0; i < n; i++)
        cin >> v[i], ans = max(ans, v[i]);

    for (int i = 1; i < n - 1; i++)
        ans = max(ans, v[i] + min(v[i - 1], v[i + 1]));

    cout << ans;
}