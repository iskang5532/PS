// 2023-01-08
// 27111 출입 기록
// https://www.acmicpc.net/problem/27111
/*
    구현 (2,800KB, 40ms)
    시간 복잡도: ?
    풀이)
    - visited[]에 해당 번호의 방문 여부를 저장.
    - a와 b를 입력받은 후 visited에 저장된 값을 이용하여 ans의 증감 여부를 결정.
    만약 visited[a]가 b와 긑은 경우, 반대되는 출입 기록이 사라졌으므로 ans++.
    - n개의 a와 b를 모두 입력받은 후, visited에 저장된 모든 값을 확인.
    만약 visited[i] == true일 경우, 나간 기록이 사라졌으므로 ans++.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 200'003 // max n

int visited[MAX];

int main()
{
    FAST_IO;

    int n; // 기록의 개수 (1 ≤ n ≤ 200,000)
    cin >> n;

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        int a, b; // 번호 a, 출입 여부 b
        cin >> a >> b;

        if (visited[a] == b) // 출입 여부와 같은 경우 (= 반대되는 출입 기록이 사라짐)
            ans++;
        visited[a] = b;
    }

    for (int i = 0; i < MAX; i++)
        if (visited[i]) // 방문한 상태인 경우 (= 나간 기록이 없는 경우)
            ans++;

    cout << ans;
}