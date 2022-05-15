// 2022-05-14
// 25193 곰곰이의 식단 관리
// https://www.acmicpc.net/problem/25193
/*
    수학 (2,020KB, 4ms)
    시간 복잡도: ?
 */

#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;

    int k = 0;
    for (int i = 0; i < n; i++)
    {
        char c;
        cin >> c;
        if (c != 'C')
            k++;
    }

    if (k == 0)
        cout << n;
    else
    {
        n -= k, k++;
        cout << (n / k) + (bool)(n % k);
    }
}