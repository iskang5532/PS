//
// https://www.acmicpc.net/problem/
/*
    재귀 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - Fac(n)의 반환은 n!이다.
    - Fac(n)은 Fac(n-1)을 호출한다. 또한, Fac(n-1)은 n-1까지의 곱이며 Fac(n-1-1)을 호출한다.
    이를 n = 0까지 반복하며, n = 0일 때에는 1을 반환한다.
    - Fac(0) = Fac(1) = 1이 되며 Fac(2) = 2 * 1이 되며, Fac(3) = 3 * 2가 된다.
    최종적으로, Fac(n) = n!가 완성된다.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"

int Fac(int n)
{
    if (n == 0)
        return 1;
    return n * Fac(n - 1);
}

int main()
{
    FAST_IO;

    int n; // 0 ≤ N ≤ 12
    cin >> n;

    cout << Fac(n);
}

/*
    반복문 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이) 1부터 n까지의 값들을 곱한 후 출력
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"

int Fac(int n)
{
    int ret = 1;
    for (int i = 1; i <= n; i++)
        ret *= i;
    return ret;
}

int main()
{
    FAST_IO;

    int n; // 0 ≤ N ≤ 12
    cin >> n;

    cout << Fac(n);
}