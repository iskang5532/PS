// 1644 소수의 연속합
// https://www.acmicpc.net/problem/1644
/*
    sol.1) 투 포인터 (1,7524KB, 1,368ms)
    시간 복잡도: ?
    풀이)
    - n까지의 정수 i를 탐색하며, 해당 정수가 소수인지를 판별.
    만약 소수일 경우, P[i] = true.
    - prime의 좌측 값을 탐색해줄 l과 우측 값을 탐색해줄 r, l부터 r까지의 합을 저장할 sum.
    만약 sum == n인 경우, ans++. (n을 만들 수 있는 경우의 수 +1)
    만약 sum < n인 경우, r의 위치를 한 칸 우측으로 옮기며 prime[r]을 sum에 더해줌. (sum 값이 부족하므로, 값을 넣어줘야 함.)
    만약 sum >= n인 경우, l의 값을 sum에서 빼준 후, 한 칸 우측으로 옮김. (sum 값이 충분하므로, 값을 빼주어 줄여야 함.)
    이후, l이 prime의 마지막 값을 탐색할 때까지 반복.
    - 주의할 점은, l 위치의 값 혹은 r 위치의 값을 확인할 때 OOB가 되지 않도록 로직을 짜줘야 함.
    etc.) 첫 풀이. 정말 아슬아슬하게 통과한듯.
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define MAX 4'000'000 + 1

bool isprime(int x) // x는 소수인가?
{
    for (int i = 2; i * i <= x; i++) // == (i <= sqrt(x))
        if (x % i == 0)
            return false;
    return true;
}

int main()
{
    FAST_IO;

    int n; // 1 ≤ N ≤ 4,000,000
    cin >> n;

    int P[MAX]; // P[i] = true일 시, i는 소수
    P[0] = 2;
    int SZ = 1;
    for (int i = 3; i <= n; i++)
        if (isprime(i))
            P[SZ] = i, SZ++;

    int ans = 0;
    int l = 0, r = 0;
    int sum = P[r];
    while (l < SZ)
    {
        if (sum == n)
            ans++;

        if (r + 1 < SZ && sum < n)
            r++, sum += P[r];
        else // if (l < SZ && sum > n)
            sum -= P[l], l++;
    }

    cout << ans;
}

/*
    sol.2) 투 포인터 (9,004KB, 24ms)
    시간 복잡도: O(nloglogn) (에라토스테네스의 체의 시간 복잡도)
    풀이)
    * 풀이는 sol.1)과 같으나, 소수를 구하는 과정이 다름.
    - 수 i가 소수인지 아닌지를 저장한 sieve. (sieve[i] = true일 경우, i는 소수)
    값 i는 2부터 sqrt(n)까지 탐색.
    만약 i가 소수일 경우, i^2부터 n까지 i만큼 더한 값의 소수 여부(= sieve)를 false로 해줌. (= (i^2), (i^2) + i, (i^2) + 2i, ...의 값은 소수가 아님 )
    - sieve에 저장된 모든 소수를 prime에 넣어줌.
    참고)
    - 에라토스테네스의 체: https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define MAX 4'000'000 + 1

int main()
{
    FAST_IO;

    int n; // 1 ≤ N ≤ 4,000,000
    cin >> n;

    bool sieve[MAX]; // sieve[i] = true일 때, i는 소수 (에라토스테네스의 체)
    fill(&sieve[0], &sieve[0] + sizeof(sieve) / sizeof(sieve[0]), true);
    for (int i = 2; i * i <= n; i++) // == (i <= sqrt(n))
        if (sieve[i])
            for (int val = i * i; val <= n; val += i) // (i^2), (i^2) + i, (i^2) + 2i, (i^2) + 3i, ...
                sieve[val] = false;

    vector<int> prime; // n까지의 정수 중 소수인 값을 저장.
    for (int i = 2; i <= n; i++)
        if (sieve[i])
            prime.push_back(i);

    if (n == 1)
        cout << '0';
    else
    {
        int ans = 0;
        int l = 0, r = 0;
        int sum = prime[r];
        while (l < prime.size())
        {
            if (sum == n)
                ans++;

            if (r + 1 < prime.size() && sum < n) // n보다 작은 경우 (+ OOB)
                r++, sum += prime[r];
            else // n보다 큰 경우
                sum -= prime[l], l++;
        }

        cout << ans;
    }
}