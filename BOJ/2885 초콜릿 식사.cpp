// 2885 초콜릿 식사
// https://www.acmicpc.net/problem/2885
/*
    비트마스킹 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력된 k보다 큰 2의 제곱수와 LSB와 MSB 사이에 비트가 몇 개 있는지를 출력해준다.
    - 2의 제곱수는 k의 msb를 구해준 후, 좌측으로 1 shift 시킨 값이다.
    - 비트의 개수는 MSB << 1 우측의 0의 개수를 구한 후, LSB 우측의 0의 개수를 빼준다면 비트의 개수를 구할 수 있다.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int get_msb(int k) // (정확히는 msb << 1를 반환)
{
    k--;
    k |= k >> 1;
    k |= k >> 2;
    k |= k >> 4;
    k |= k >> 8;
    k |= k >> 16;

    return k + 1;
}

int main()
{
    FAST_IO;

    int k; // 1 ≤ K ≤ 1,000,000
    cin >> k;

    int msb = get_msb(k);
    cout << msb << ' ' << __builtin_ctz(msb) - __builtin_ctz(k);
}