// 2023-03-04
// 27386 Class Field Trip
// https://www.acmicpc.net/problem/27386
/*
    문자열, 정렬 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력된 두 문자열을 합친 후 정렬하여 출력.
 */

#include <iostream>
#include <vector>
#include <algorithm> //

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    string s1, s2;
    cin >> s1 >> s2;

    string s = s1 + s2;

    sort(s.begin(), s.end());

    cout << s;
}