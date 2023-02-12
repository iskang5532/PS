// 2023-01-15
// 10995 별 찍기 - 20
// https://www.acmicpc.net/problem/10995
/*
    구현 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이) 0부터 n-1까지 반복하되, i가 홀수일 경우 띄어쓰기를 추가하여 출력.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    int n; // 1 ≤ n ≤ 100
    cin >> n;

    for (int i = 0; i < n; i++, cout << '\n'
                                     << (i & 1 ? " " : ""))
        for (int j = 0; j < n; j++)
            cout << '*' << ' ';
}