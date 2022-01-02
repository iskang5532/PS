// 1629 곱셈
// https://www.acmicpc.net/problem/1629
/*
    sol.1) 재귀 (2,016KB, 0ms)
    시간 복잡도: O(longN)
    풀이)
    - a^n을 구할 시, 절반의 값인 a^(n/2)를 구해준 후, *2를 해준다.
    또한, 2^(n/2)를 구하기 위해서 마찬가지로 절반의 값을 구해준다. (이를 재귀적으로 구현해준다.)
    위와 같이 구현할 시, O(n)이 아닌 O(longN)이 된다.
    - 만약 n == 1일 경우, a % MOD값을 반환해준다. (a 자체만으로 MOD 이상의 값일 수도 있음.)
    참고)
    - 이론: https://velog.io/@litien/BOJ-1629-%EA%B3%B1%EC%85%88
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
typedef long long ll;

int Power(int a, int n, int MOD) // a^n
{
    if (n == 1)
        return a % MOD;

    ll half = Power(a, n >> 1, MOD);
    ll ret = half * half % MOD;

    if (n & 1)
        ret = ret * a % MOD;

    return ret;
}

int main()
{
    FAST_IO;

    int a, b, c; // 1 ≤ a, b, c ≤ 2,147,483,647
    cin >> a >> b >> c;

    cout << Power(a, b, c);
}

/*
    sol.2) 거듭제곱 (2,020KB, 0ms)
    시간 복잡도: O(logN)
    풀이)
    - a^n일 때, n을 2진수로 생각한 후, 켜져 있는 비트마다 값을 곱해준다.
    단, 비트가 커질 때마다 곱해줘야 하는 값 또한 커지므로, 비트를 하나씩 옮길 때마다 곱해줄 값 또한 제곱을 해준다.
    참고)
    - 이론: https://blog.naver.com/jinhan814/222179331810
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
typedef long long ll;

int main()
{
    FAST_IO;

    ll a, b, c; // 1 ≤ a, b, c ≤ 2,147,483,647
    cin >> a >> b >> c;

    ll ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % c;

        b >>= 1;
        a = (a * a % c);
    }

    cout << ans;
}