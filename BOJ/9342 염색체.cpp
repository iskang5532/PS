// 2022-05-08
// 9342 염색체
// https://www.acmicpc.net/problem/9342
/*
    sol.1) 구현, 문자열 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 조건에 맞춰 구현.
    - 첫 글자는 아무 글자가 와도 됨. 다만, 'A'일 경우, 다음 글자는 'F'여야 하지만 'A'일 수도 있음. (연속해서 존재할 수 있으므로)
    그러므로, 첫 글자가 'A'인지 확인.
    - 값의 연속이 끊길 경우, 현재 값(이전과 다른 값)이 ch에 존재하는지 확인.
    만약 없을 경우, ALL에서 탐색.
     - 만약 ALL에 존재할 경우, 마지막 값인지 확인.
     - 만약 존재하지 않을 경우 false.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

char ALL[] = {'A', 'B', 'C', 'D', 'E', 'F'};
char ch[] = {'A', 'F', 'C'};

bool isValid(string s)
{
    int cnt = 0;     // ch[cnt]
    bool ed = false; // 마지막 글자인가
    for (int i = (s.front() != 'A'); i < s.length(); i++)
    {
        if (!('A' <= s[i] && s[i] <= 'F') || ed)
            return false;

        if (s[i] != ch[cnt])
        {
            cnt++;
            if (cnt != 3 && s[i] != ch[cnt]) // 다음 글자는 ch[]에 존재하는가
                return false;
            else if (cnt == 3)
            {
                for (const auto &c : ALL)
                    if (s[i] == c)
                        ed = true;
                if (!ed)
                    return false;
            }
        }
    }

    return true;
}

int main()
{
    FAST_IO;

    int t; // 1 ≤ t ≤ 20
    cin >> t;
    while (t--)
    {
        string s;
        cin >> s;

        cout << (isValid(s) ? "Infected!" : "Good") << endl;
    }
}

/*
    sol.2) 경규 표현식 (2,176KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 조건에 맞는 정규 표현식을 생성한 후, 입력된 문자열을 regex_match에 집어넣어 패턴을 만족하는지 확인.
    etc.) 정규표현식 넘나 어려운것
    참고)
    - 정규 표현식 코드: https://blog.naver.com/jinhan814/222093508967
 */

#include <iostream>
#include <regex>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

int main()
{
    FAST_IO;

    regex r(R"(^[A-F]?A+F+C+[A-F]?$)");
    /*
        ^[A-F]  A~F로 시작할 수도, 아닐 수도 있음
        A+      가 1번 이상 반복
        F+      가 1번 이상 반복
        C+      C가 1번 이상 반복
        [A-F]   A~F가 나올 수도, 아닐 수도 있음
        $       표현식 종료
    */

    int t; // 1 ≤ t ≤ 20
    cin >> t;
    while (t--)
    {
        string s;
        cin >> s;

        cout << (regex_match(s, r) ? "Infected!" : "Good") << endl;
    }
}