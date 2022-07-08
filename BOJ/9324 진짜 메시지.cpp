// 9324 진짜 메시지
// https://www.acmicpc.net/problem/9324
/*
    구현 (2,512KB, 28ms)
    시간 복잡도: ?
    풀이)
    - 현재까지 나온 문자의 개수를 저장할 cnt. (cnt[c] = k일 때, 문자 c는 k번 등장)
    - i번째 문자가 3번 이상 나왔을 경우, 다음 문자와 비교.
    만약 다를 경우, 올바른 변형이 아니므로 false. (문자열의 길이를 벗어날 수도 있으므로 널문자를 고려)
    만약 같을 경우, i+1번째 문자의 탐색을 하지 않도록 i를 한 칸 옮긴다.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

int main()
{
    FAST_IO;

    int tc; // 1 ≤ tc ≤ 100
    cin >> tc;
    while (tc--)
    {
        string s; // 1 ≤ s.len ≤ 100,000
        cin >> s;

        int cnt['Z' + 1]{};
        bool flag = true;
        for (int i = 0; i < s.length() && flag; i++)
            if (++cnt[s[i]] % 3 == 0) // 세 번 나왔는가?
            {
                if (s[i + 1] == '\0' || s[i + 1] != s[i]) // 다음 값과 다를 경우
                    flag = false;
                i++;
            }

        cout << (flag ? "OK" : "FAKE") << endl;
    }
}