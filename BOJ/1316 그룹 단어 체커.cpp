// 1316 그룹 단어 체커
// https://www.acmicpc.net/problem/1316
/*
    구현 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 배열 cnt를 선언하여 현재 문자의 확인 여부를 저장함.
    문자열은 소문자 알파벳으로만 들어오므로 -'a'를 이용해 int형으로 바꾼 후 배열에 접근.
    - 현재 확인중인 문자가 연속적일 수도 있으므로, 이전에 확인한 문자를 저장시켜 예외 처리. (c == prev ? continue)
    - 문자가 연속적인 경우가 아니며 이전에 확인한 적이 있을 시, false.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"

bool isValid(const string &&str)
{
    bool cnt[26]; // cnt[0] = true인 경우, 현재 단어에서 'a'가 나온 적이 있음. (= 확인한 적이 있음)
    fill(&cnt[0], &cnt[0] + sizeof(cnt) / sizeof(cnt[0]), false);

    char prev = '\0'; // 이전에 조사한 문자
    for (const auto &c : str)
    {
        if (c == prev) // 문자가 연속적인가?
            continue;

        if (cnt[c - 'a'])
            return false;

        cnt[c - 'a'] = true;
        prev = c;
    }

    return true;
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n; // 단어의 개수 n(1 ≤ n ≤ 100)
    cin >> n;

    int ans = 0;
    while (n--)
    {
        string str;
        cin >> str;

        if (isValid(move(str)))
            ans++;
    }
    cout << ans;
}