// 11966 2의 제곱인가?
// https://www.acmicpc.net/problem/11966
/*
    비트 연산 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    n와 n-1을 and 연산을 이용해 LSB(가장 우측의 1)와 LSB 우측 비트를 0으로 만들어 준다.
    이후, 해당 값이 0일 경우 LSB 하나만 켜져 있는 값, 즉 2의 제곱수이므로 1을 출력.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

bool isSquareNumber(int n)
{
    return (n & (n - 1)) == 0 ? true : false;
}

int main()
{
    FAST_IO;

    int n;
    cin >> n;

    cout << (isSquareNumber(n) ? "1" : "0");
}