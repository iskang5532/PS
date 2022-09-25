// 2022-09-20
// 3460 이진수
// https://www.acmicpc.net/problem/3460
/*
    구현, 비트연산자 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력된 n의 첫 번째 비트(최우측 비트; LSB)를 확인 후, 비트를 우측으로 한칸 씩 옮김.
    만약 LSB가 1일 경우, 현재 탐색중인 비트의 위치인 i를 출력.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;
    while (tc--)
    {
        int n;
        cin >> n;

        for (int i = 0; i < 32; i++, n >>= 1)
            if (n & 1)
                cout << i << ' ';
        cout << endl;
    }
}
