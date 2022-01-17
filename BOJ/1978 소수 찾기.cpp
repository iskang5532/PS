// 1978 소수 찾기
// https://www.acmicpc.net/problem/1978
/*
    에라토스테네스의 체 (2,0200KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 해당 값이 소수인지를 판별한 결과를 저장할 prime.
    - 아로트스테네스의 체를 이용해 1부터 1000까지의 수 중 소수를 찾음.
    2부터 sqrt(MAX)까지의 i를 탐색.
    i가 소수일 경우 i^2부터 (i^2) + i, (i^2) + 2i, (i^2) + 3i, ...의 값은 소수가 아님.
    - n개의 수를 받으며, 해당 수가 소수일 경우 ans++.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 1'000 + 1

int main()
{
    FAST_IO;

    bool prime[MAX]; // prime[i] = true일 시, i는 소수
    fill(&prime[0], &prime[0] + sizeof(prime) / sizeof(prime[0]), true);
    for (int i = 2; i * i <= MAX; i++) // == (i <= sqrt(MAX))
        if (prime[i])
            for (int val = i * i; val <= MAX; val += i)
                prime[val] = false;
    prime[1] = false;

    int n; // 1 ≤ n ≤ 100
    cin >> n;

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        int k; // 1≤ k ≤ 1,000
        cin >> k;
        if (prime[k])
            ans++;
    }
    cout << ans;
}