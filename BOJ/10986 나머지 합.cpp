/* 
 * 10986 나머지 합
 * 누적합, 수학
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/10986
 * ETC.) 무식하게 기존 누적합 방식으로 풀어 봤지만, 시간 초과가 남
 * 10.13) 나중에 다시 풀어보기로
 * 참고: https://blog.naver.com/jhc9639/221411875667 (설명 및 코드)
 * https://www.acmicpc.net/board/view/63744 (long long 문법에 대한 고찰)
 */

#include <iostream>
#include <vector>

using namespace std;

#define endl "\n"
typedef long long ll;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, m; // 수의 개수 (1 ≤ n ≤ 1M), 나눌 값 (2 ≤ m ≤ 1k)
    cin >> n >> m;

    vector<int> pSum(n + 1);
    pSum[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        int k; // 0 ≤ k ≤ 1G
        cin >> k;

        pSum[i] = (pSum[i - 1] + k) % m; // 보기 편하게 사전에 m의 나머지 값을 저장
    }

    // 부분합을 구하는 방법은 pSum[i] - pSum[j - 1]이었으며, 이 값에서 % m == 0인 값을 찾아야 한다.
    // 이는 곧 누적합의 값에 대한 개수를 세어 주면 된다. (pSum[j - 1]또한 누적합)
    // 이 개수들, 즉  서로 같은 값을 빼게 된다면 조건(% m == 0)을 만족시킬 수 있다. (자세한 건 블로그 참고)
    vector<int> cnt(m); // m으로 나머지를 구했기 때문에 최대 m까지 존재
    for (const auto &elem : pSum)
        cnt[elem]++;

    ll answer = 0; // 최대 n(n-1) ÷ 2 (계산 과정에서 int 범위를 벗어남)
    for (const auto i : cnt)
        answer += (1LL * i * (i - 1)) >> 1; // i개 중 2개(좌측, 우측)를 뽑는 경우의 수

    cout << answer;
}