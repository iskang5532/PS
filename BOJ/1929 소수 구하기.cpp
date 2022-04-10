// 1929 소수 구하기
// https://www.acmicpc.net/problem/1929
// 2022-04-09
/*
    에라토스테네스의 체 (2,9960KB, 12ms)
    시간 복잡도: ?
    풀이)
    - 해당 값이 소수인지를 저장할 isPrime[] (isPrime[i] = true일 경우, i는 소수)
    - 아로트스테네스의 체를 사용하여 m부터 n까지 소수를 찾음.
    i는 2부터 sqrt(MAX)까지 확인.
    만약 i가 소수일 경우 i^2부터 (i^2) + i, (i^2) + 2i, (i^2) + 3i, ...의 값은 소수가 아님.
 */

#include <iostream>
#include <cmath> // sqrt

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 1'000'003 // max m, n

bool isPrime[MAX];

int main()
{
    FAST_IO;

    int m, n; // 범위 m, n(1 ≤ M ≤ N ≤ 1,000,000)
    cin >> m >> n;

    fill(isPrime, isPrime + MAX, true);

    for (int i = 2; i <= sqrt(MAX); i++)
        if (isPrime[i])
            for (int next = i * i; next <= MAX; next += i)
                isPrime[next] = false;
    isPrime[1] = false;

    for (int i = m; i <= n; i++)
        if (isPrime[i])
            cout << i << endl;
}