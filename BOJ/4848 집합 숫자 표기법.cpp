// 2022-12-10
// 4848 집합 숫자 표기법
// https://www.acmicpc.net/problem/4848
/*
    재귀 (2,644KB, 48ms)
    시간 복잡도: ?
    풀이)
    - 수 n을 집합 s로 변환 시, s의 여는 괄호 '{'의 개수는 2^n개이다.
    즉, 집합의 여는 괄호의 개수를 센 후 log2를 취하면 수를 구할 수 있음.
    - 수를 집합으로 바꾸는 방법은 재귀를 이용함.
    - 0은 "{}"를 반환하며, 그 외의 값은 0부터 n까지의 값을 집합으로 변경하여 문자열에 저장.
    문자열에는 집합으로 바꾼 수 사이에 콤마로 나뉘어 있다. 그러므로 마지막 수가 아닐 경우, 문자열 뒤에 콤마를 추가한다.
    - 괄호는 앞에서부터 작은 값이다.
 */

#include <iostream>
#include <cmath> // log

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl '\n'

string _itos(int n) // 수를 집합으로 변환
{
    if (n == 0)
        return "{}";

    string ret = "{";
    for (int i = 0; i < n; i++)
    {
        ret += _itos(i);
        if (i < n - 1)
            ret += ',';
    }
    ret += '}';

    return ret;
}

int _stoi(const string &s) // 집합을 수로 변환
{
    int cnt = 0;
    for (const char &c : s)
        if (c == '{')
            cnt++;

    return log2(cnt);
}

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;
    while (tc--)
    {
        string s1, s2;
        cin >> s1 >> s2;

        int n = _stoi(s1) + _stoi(s2); // 입력된 두 집합을 수로 바꿔 더함

        cout << _itos(n) << endl;
    }
}