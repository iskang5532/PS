// 2022-10-17
// 2607 비슷한 단어
// https://www.acmicpc.net/problem/2607
/*
    구현 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 기준이 되는 문자열 속 문자의 개수를 저장할 c1[], 비교할 문자열 속 문자의 개수를 저장할 c2[].
    - 문자는 더하거나, 빼거나, 하나의 문자를 다른 문자로 바꿀 수 있다.
    즉, 다음과 같다.
    1. c1과 c2를 비교할 때, c1 혹은 c2의 차이가 1이 한 번 발생하였을 경우, 문자를 더하거나 빼서 맞출 수 있다.
    2. c1과 c2를 비교할 때, c1과 c2가 각각 1씩 더 큰 상황이 한 번 발생하였을 경우, 문자를 바꾸어 맞출 수 있다.
    - c1과 c2를 비교.
    만약 c1 > c2일 경우, l에 c1 - c2를 저장.
    만약 c1 < c2일 경우, r에 c2 - c1을 저장.
    l과 r 모두 2 미만일 경우, 비교 문자열은 기준 문자열과 비슷한 단어이다.
    etc.)
    - 문제를 잘못 이해함.
    참고)
    - if문: https://gyong0117.tistory.com/m/89
 */

#include <iostream>
#include <algorithm>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int c1['z']; // 기준 문자열 속 문자의 개수를 저장

bool isValid(const string &s)
{
    int c2['z']{}; // 비교 문자열 속 문자의 개수를 저장
    for (const auto &c : s)
        c2[c]++;

    int l = 0, r = 0; // 초과된 문자의 개수를 저장
    for (int i = 'A'; i < 'Z'; i++)
        if (c1[i] > c2[i]) // 기준 문자열의 문자가 더 많은 경우
            l += c1[i] - c2[i];
        else if (c1[i] < c2[i]) // 입력 문자열의 문자가 더 많은 경우
            r += c2[i] - c1[i];

    return (l < 2 && r < 2) ? true : false;
    // if (l - 1 == 0 && r - 1 == 0) // trans
    //     return true;
    // if ((l == 1 && r == 0) || (l == 0 && r == 1)) // del
    //     return true;
}

int main()
{
    FAST_IO;

    int n; // 단어의 개수 (1 ≤ n ≤ 100)
    cin >> n;
    string s; // 기준 문자열
    cin >> s;

    for (const auto &c : s)
        c1[c]++;

    int ans = 0;
    for (int i = 0; i < n - 1; i++)
    {
        string s; // 비교 문자열
        cin >> s;

        if (isValid(s))
            ans++;
    }

    cout << ans;
}