// 18511 큰 수 구성하기
// https://www.acmicpc.net/problem/18511
/*
    완전 탐색 (2,020KB, 4ms)
    시간 복잡도: ?
    풀이)
    - 입력된 k개의 수를 문자열 s에 추가하며 탐색.
    만약 수로 바꾼 s가 n보다 큰 경우, 반환. (= 조건 불충족)
    이때, 반환된 지점에서의 s는 n을 초과하기 직전의 값이다. 즉, 최댓값일 수도 있으므로, ans와 비교하여 넣어준다.
    ans에 첫 값이 바로 들어갈 수 있도록 0을 기본값으로 해준다.
    - 문자열을 이용한 풀이에서 주의해야 할 점은, stoi(s)에서 s의 값이 없을 경우, 에러가 난다.
    그러므로, 기본값을 넣어주거나 s에 값이 생기는 구간에서 stoi로 확인을 해줘야 한다.
    etc.) *10을 해주며 푸는 방법도 있지만, 문자열이 생각났으므로 문자열을 이용해 해결.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

int n, k; // 수 n(10 ≤ N ≤ 100,000,000), 원소의 개수 k(1 ≤ k ≤ 3)
int v[3]; // 1 ≤ vi ≤ 9
int ans = 0;

void dfs(const string &s = "0")
{
    if (stoi(s) > n) // s가 n보다 클 시, return
        return;

    for (int i = 0; i < k; i++) // k개의 수를 모두 이용
    {
        dfs(s + to_string(v[i])); // i번째 수를 추가하여 재귀
        ans = max(ans, stoi(s));
    }
}

int main()
{
    FAST_IO;

    cin >> n >> k;
    for (int i = 0; i < k; i++)
        cin >> v[i];

    dfs();

    cout << ans;
}