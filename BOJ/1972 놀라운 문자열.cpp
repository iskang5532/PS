// 2022-10-06
// 1972 놀라운 문자열
// https://www.acmicpc.net/problem/1972
/*
    완전 탐색, 셋 (2,028KB, 0ms)
    시간 복잡도: O(n(n+1)(n+2)/6)??
    풀이)
    - D-쌍을 이루는 문자열 s가 중복되면 안되므로, 중복을 구별할 수 있도록 셋 S를 사용.
    - s가 S에 존재하는지 확인.
    만약 존재하지 않을 경우, 현재까지는 유일한 쌍. 셋에 s를 추가.
    만약 존재할 경우, 유일한 쌍이 아님.
    etc.) 문자열 자료형을 선언하면서 두 문자를 넣는 방법은 없는가?
 */

#include <iostream>
#include <unordered_set>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

bool isValid(const string &word)
{
    for (int l = 1; l < word.length() - 1; l++) // 쌍의 길이
    {
        unordered_set<string> S;
        for (int st = 0; st < word.length() - l; st++)
        {
            string s = {word[st], word[st + l]};
            if (S.find(s) == S.end())
                S.insert(s);
            else
                return false;
        }
    }

    return true;
}

int main()
{
    FAST_IO;

    string word;
    while (cin >> word)
    {
        if (word == "*")
            break;

        cout << word << " is " << (isValid(word) ? "" : "NOT ") << "surprising." << endl;
    }
}
