// 2022-10-16
// 5086 배수와 약수
// https://www.acmicpc.net/problem/5086
/*
    사칙연산 (2,020KB, 0ms)
    시간 복잡도: ?
*/

#include <iostream>

using namespace std;

int main()
{
    int a, b;
    while (cin >> a >> b)
    {
        if (a == 0 && b == 0)
            break;

        if (a < b && b % a == 0)
            cout << "factor" << '\n';
        else if (b < a && a % b == 0)
            cout << "multiple" << '\n';
        else
            cout << "neither" << '\n';
    }
}