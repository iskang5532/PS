// 2023-03-22
// 15874 Caesar Cipher 
// https://www.acmicpc.net/problem/15874
/*
    구현, 문자열 (2,268KB, 8ms)
    시간 복잡도: ?
    풀이)
    - c가 시작점인 'a' 혹은 'A'에서부터 얼마나 떨어져 있는지를 구함.
    이후, 해당 값에 k를 더한 후, 26을 나누게 된다면 최종적으로 시작점에서부터 얼마나 떨어졌는지 구할 수 있음.
 */

#include <iostream>

using namespace std;

int main()
{
    int k, l;
    cin >> k >> l;
    cin.ignore();
    string s;
    getline(cin, s);

    for (const char &c : s)
        if ('a' <= c && c <= 'z')
            cout << char('a' + (c - 'a' + k) % 26);
        else if ('A' <= c && c <= 'Z')
            cout << char('A' + (c - 'A' + k) % 26);
        else
            cout << c;
}