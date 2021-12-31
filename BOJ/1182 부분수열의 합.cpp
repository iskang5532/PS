// 1182 부분수열의 합
// https://www.acmicpc.net/problem/1182
/*
    sol.1) 완전 탐색 (2,020KB, 56ms)
    시간 복잡도: O(2^n * n)
    풀이)
    - n을 2진수로 바꿔 생각하며, 각 비트마다 사용 여부를 결정.
    만약 pos번째 비트가 true일 경우 pos번째 수를 sum에 저장하며, sum == s일 경우 ans++
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 20 + 1

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n, s; // 정수의 개수 n(1 ≤ N ≤ 20), 합 s(|S| ≤ 1,000,000)
    cin >> n >> s;
    int arr[MAX];
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int ans = 0;
    for (int i = 1; i < (1 << n); i++) // 2^n
    {
        int sum = 0;
        for (int pos = 0; pos < n; pos++)
            if (i >> pos & 1) // pos번째 비트가 true인가?
                sum += arr[pos];

        if (sum == s)
            ans++;
    }

    cout << ans;
}

/*
    sol.2) DFS (2,020KB, 4ms)
    시간 복잡도: O(2^n)
    풀이)
    - 재귀를 이용하여 구현했으며, sum에 arr[cnt] 추가한 경우와 하지 않은 경우로 나뉨.
    - n개의 수를 확인한 경우, 더해진 sum과 s를 비교.
    - 첫 번째 재귀는 모든 수를 포함하지 않는다. 즉, sum == 0이 되는데, 만약 s == 0일 경우 ans++가 됨.
    그러므로 s == 0일 때, s--를 해줌.
    참고)
    - 이론: https://blog.naver.com/jinhan814/222579884777
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 20 + 1

int n, s; // 정수의 개수 n(1 ≤ N ≤ 20), 합 s(|S| ≤ 1,000,000)
int arr[MAX];

int dfs(int cnt, int sum)
{
    if (cnt == n)
        return sum == s;

    return dfs(cnt + 1, sum) + dfs(cnt + 1, sum + arr[cnt]); // 더한 경우 및 더하지 않은 경우
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    cin >> n >> s;
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    cout << dfs(0, 0) - !s;
}