// 16922 로마 숫자 만들기
// https://www.acmicpc.net/problem/16922
/*
    백트래킹(중복 조합) (2,020KB, 0ms)
    시간 복잡도: O(20H4 = 20+4-1C4 = 212,520)
    풀이)
    - dfs를 이용하여 로마 숫자를 n개 사용하여 만들 수 있는 모든 경우의 수를 파악.
    이때, IIV와 IVI, VII는 모두 같은 값이며 중복하여 탐색할 시 시간 초과가 날 수 있음. (n = 20일 경우, 4^20)
    그러므로 IVI와 같은 경우, V 이후에는 V 이상의 값, 즉 IVV 이상의 값이 나올 수 있도록 만들어준다.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 50 * 20 + 3

constexpr int num[4] = {1, 5, 10, 50};

int n;             // 사용할 문자의 개수 (1 ≤ N ≤ 20)
bool visited[MAX]; // visited[k] = true일 경우, n개를 이용해 수 k를 만들 수 있음
int k = 0;         // 숫자 dep개를 이용해 만든 수

void dfs(int dep, int pos)
{
    if (dep == n)
    {
        visited[k] = true;
        return;
    }

    for (int i = pos; i < 4; i++)
    {
        k += num[i];
        dfs(dep + 1, i);
        k -= num[i];
    }
}
int main()
{
    FAST_IO;

    cin >> n;

    dfs(0, 0);

    int ans = 0;
    for (int i = 0; i < MAX; i++)
        if (visited[i])
            ans++;

    cout << ans;
}