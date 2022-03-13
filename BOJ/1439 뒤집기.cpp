// 1439 뒤집기
// https://www.acmicpc.net/problem/1439
/*
    그리디 (2,020KB, 0ms)
    시간 복잡도: O(n)
    풀이)
    - 0 또는 1이 연속되어 존재하는 횟수를 각각 세어준 후, 더 작은 값을 출력.
    - '0' = 48, '1' = 49
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    string s;
    cin >> s;

    int v[51];
    v['0'] = v['1'] = 0;

    char prev = '\0';
    for (const auto &c : s)
        if (prev != c) // 이전 값과 다름. 즉, 새로운 값
            prev = c, v[c]++;

    cout << min(v['0'], v['1']);
}