// 2022-06-02
// 12904 A와 B
// https://www.acmicpc.net/problem/12904
/*
    그리디 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - s → t가 아닌 t → s가 될 수 있는지를 구함.
    - s에 'A'를 추가하는 연산은 t에서 'A'를 제거하는 연산이며, 문자열을 뒤집고 'B'를 추가하는 연산은 'B'를 제거하고 뒤집는 연산이다.
    이를 합산해보면, t의 마지막 문자는 항상 제거하게 되며 마지막 문자가 'B'인 경우 뒤집기가 추가된다.
    두 문자열의 길이가 같아질 때까지 연산을 수행한 후, 문자열을 비교하여 출력한다.
    - t의 마지막 문자가 'A'인 경우, 임의의 문자열 s는 'A'를 추가하는 연산밖에 할 수 없다.
    s에 'B'를 추가하게 될 경우, t의 마지막 문자는 'B'여야 하기 때문이다.
    etc.)
    - 참고하진 않았지만, 설명이 잘 되어있음. https://www.acmicpc.net/board/view/83783
 */

#include <iostream>
#include <algorithm> // reverse

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    string s, t; // (length: 1 ≤ S ≤ 999, 2 ≤ T ≤ 1000, S < T)
    cin >> s >> t;

    while (s.length() != t.length())
        if (t.back() == 'A')
            t.pop_back();
        else // 'B'
            t.pop_back(), reverse(t.begin(), t.end());

    cout << (s == t);
}

// 12  212 2122    22122   221222  222122

// 2
// 1221