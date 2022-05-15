// 2022-05-11
// 20310 타노스
// https://www.acmicpc.net/problem/20310
/*
    그리디 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 가장 빠른 문자열을 만들기 위해서는 '0'이 앞서 있어야 한다.
    그러므로, 값을 제거할 때 앞에 있는 '1'을 우선적으로 제거하며, '0'을 제거할 때는 뒤에서부터 제거한다.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    string s;
    cin >> s;

    int cnt[200]{};
    for (const auto &c : s)
        cnt[c]++;
    cnt['0'] /= 2, cnt['1'] /= 2;

    for (auto itr = s.rbegin(); itr != s.rend() && cnt['0']; itr++)
        if ((*itr) == '0')
            *itr = '\0', cnt['0']--;
    for (auto itr = s.begin(); itr != s.end() && cnt['1']; itr++)
        if ((*itr) == '1')
            *itr = '\0', cnt['1']--;

    for (const auto &c : s)
        if (c != '\0')
            cout << c;
}