// 2023-01-26
// 27137 Square Designs
// https://www.acmicpc.net/problem/27137
/*
    구현 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 쓸때없은 공백이 출력되지 않도록 주의해야 함.
    예를 들어 m = 5, n = 1과 같은 입력이 주어졌을 때, 모든 n이 출력된 이후에 다음 줄에서는 m만 출력하며 m 이후에 공백이 출력되지 않아야 함.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

string get_board(int k)
{
    string ret;

    ret += "I";
    for (int i = 0; i < k; i++)
        ret += "-X";
    ret += "-I";

    return ret;
}

string get_sp(int k, bool flag = false)
{
    if (flag)
        return "          ";

    string ret;
    for (int i = 0; i < (k + 1) * 2 + 1; i++)
        ret += ' ';
    return ret;
}

string get_ed(int k)
{
    string s;

    s += '+';
    for (int i = 0; i < k * 2 + 1; i++)
        s += '-';
    s += '+';

    return s;
}

int main()
{
    FAST_IO;

    int m, n;
    cin >> m >> n;

    for (int a = 0, b = 0; a <= m + 1 || b <= n + 1; a++, b++, cout << endl)
    {
        if (a == 0 || a == m + 1)
            cout << get_ed(m);
        else if (a <= m)
            cout << get_board(m);
        else
            cout << get_sp(m);

        if (b <= n + 1)
        {
            cout << get_sp(6, true);

            if (b == 0 || b == n + 1)
                cout << get_ed(n);
            else if (b <= n)
                cout << get_board(n);
            else
                cout << get_sp(n);
        }
    }
}